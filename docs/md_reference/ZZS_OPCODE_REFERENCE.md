# Another Mind (PSX) - ZZS Script Opcode Reference Manual

## 1. Overview & Virtual Machine Architecture

The `.ZZS` script format (compressed as `.ZZZ` on disc and extracted to `assets/jp/progdata/scripts/`) contains compiled bytecode for Squaresoft's *Another Mind* (1998, PSX). The script virtual machine is implemented in [`src/main/script.c`](file:///home/halkun/reverse/anothermind/anothermind-decomp/src/main/script.c) and analyzed in the Ghidra disassembly [`docs/notes/SLPS_016.55.c`](file:///home/halkun/reverse/anothermind/anothermind-decomp/docs/notes/SLPS_016.55.c).

The script engine manages:
* **Instruction Pointer (`scriptInstructionPointer`)**: Advances byte-by-byte through the active script bytecode block.
* **Call Stack (`scriptCallStack`)**: 16-level call frame stack storing return bytecode pointers and frame contexts.
* **Thread Engine (`scriptThreadTable`)**: Allows concurrent script execution threads (e.g. background animations, flashing lights) alongside dialogue progression.
* **Variable Pools**:
  * `rawMemoryPool` (0x0): 8-bit temporary expression registers (scratchpad).
  * `scriptVar8` / `I[]` (0x1): 8-bit local scenario variables (e.g. loop counters, step IDs).
  * `scriptVar16` / `G[]` (0x2): 16-bit global scenario variables (e.g. story flags, affection points).
  * `globalVariableTable` / `F[]` (0x3): Global bitflag array (single-bit booleans).
  * Taiwa registers (0x7): Dynamic dialogue evaluation outputs (`taiwaJn`, `taiwaJv`, etc.).

---

## 2. File Layout & Header Structure

Every `.ZZS` file has a fixed 10-byte header, followed by a 16-bit jump block relocation table, followed immediately by bytecode:

```
+---------------------------------------------------------------------------------+
| Offset (Hex) | Size (Bytes) | Description                                       |
+--------------+--------------+---------------------------------------------------+
| 0x00 - 0x03  | 4            | Compiler Version / Date Stamp (e.g. 09 04 15 09)  |
| 0x04 - 0x05  | 2            | Reserved / Compiler Flags (0x0000)                |
| 0x06 - 0x07  | 2            | Total Script Data Size (Big-Endian uint16)        |
| 0x08 - 0x09  | 2            | Block / Jump Label Count N (Big-Endian uint16)    |
| 0x0A - ...   | N * 2        | Block Offset Table (Array of BE uint16 offsets)   |
| Base =       | Remainder    | Script Bytecode Stream (starts with Opcode 0x29)  |
| 0x0A + N * 2 |              |                                                   |
+---------------------------------------------------------------------------------+
```

### Relocation Table (`scriptBlockTable`)
* The table contains `N` big-endian 16-bit offsets relative to `Base` (`0x0A + N * 2`).
* When the script interpreter executes a jump or subroutine call (e.g. `JUMP`, `CALL`, `SJUMP`), the target operand index directly indexes `scriptBlockTable[index]`, making bytecode blocks relocatable.

---

## 3. Addressing Modes & Parameter Descriptors

Most opcodes that accept parameters take one or more **nibble-packed descriptor bytes**, decoded at runtime by `decodeScriptOperand(flags, operandByte)`:

* In a single descriptor byte:
  * **Bits 0..3 (Low Nibble)**: Addressing mode for Operand 1 (`flags = 1`).
  * **Bits 4..7 (High Nibble)**: Addressing mode for Operand 2 (`flags = 2`).
* If an opcode accepts 3 or 4 operands, a second descriptor byte follows immediately (`flags = 3` for low nibble, `flags = 4` for high nibble).
* If an opcode accepts 5 or 6 operands, a third descriptor byte follows (`flags = 5` for low nibble, `flags = 6` for high nibble).

### Addressing Mode Table

| Mode (Nibble) | Target Data Source | Size in Stream | Description |
|:---:|:---|:---:|:---|
| `0x0` | `rawMemoryPool[idx]` | 1 byte | Reads 8-bit temporary scratchpad variable |
| `0x1` | `scriptVar8[idx]` (`I[idx]`) | 1 byte | Reads 8-bit local script variable |
| `0x2` | `scriptVar16[idx]` (`G[idx]`) | 2 bytes (BE) | Reads 16-bit global script variable |
| `0x3` | `globalVariableTable[bit]` (`F[bit]`) | 2 bytes (BE) | Reads 1-bit boolean flag (`bit >> 3` byte, `bit & 7` bit) |
| `0x4` | 16-bit Immediate Constant | 2 bytes (BE) | Direct 16-bit signed integer |
| `0x5` | 8-bit Immediate Constant | 1 byte | Direct 8-bit signed integer |
| `0x6` | 16-bit Immediate Constant | 2 bytes (BE) | Direct 16-bit signed integer (alternative encoding) |
| `0x7` | Taiwa Noun / Register | 1 byte sub-id | Dynamic register from NLP dialogue engine (see below) |
| `0x8` | 16-bit Immediate Constant | 2 bytes (BE) | Direct 16-bit signed integer (alternative encoding) |
| `0x9` | 16-bit Immediate Constant | 2 bytes (BE) | Direct 16-bit signed integer (alternative encoding) |

#### Mode `0x7` Sub-Register Selectors
When addressing mode `0x7` is selected, the engine reads a 1-byte selector:
* `0`: `taiwaJn` (Subject / Topic Word ID selected by the player)
* `1`: `taiwaJv` (Verb / Action Word ID selected by the player)
* `2`: Direct Object Word ID
* `3`: Indirect Object Word ID
* `4`: Location / Complement Word ID

---

## 4. Master Opcode Table (140 Opcodes)

The table below lists all 140 active opcodes registered in `InitOpcodeHandlerTable` (`0x8001BE64`). Opcodes not listed in this table route to `Cmd_errorUnknownOpcode` and trigger a fatal engine fault.

| Hex | Dec | C Handler Symbol | Compiler Mnemonic | Parameter Format | Functional Category |
|:---:|:---:|:---|:---|:---|:---|
| `0x01` | 1 | `Cmd_handleScriptBlock` | `JUMP` | `desc(1), block_idx` | Flow Control |
| `0x02` | 2 | `Cmd_call` | `CALL` | `desc(1), block_idx, label[8]` | Flow Control |
| `0x03` | 3 | `Cmd_return` | `RETURN` | *none* | Flow Control |
| `0x04` | 4 | `Cmd_sjump` | `SJUMP` | `desc(1), script_id` | Flow Control |
| `0x05` | 5 | `Cmd_wait` | `WAIT` | `desc(1), frames` | Flow Control |
| `0x06` | 6 | `Cmd_bg` | `BG` | `desc(2), bg_id, effect_id` | Backgrounds & Visuals |
| `0x07` | 7 | `Cmd_bg2` | `BG2` | `desc(2), desc(1), bg_id, effect_id, wait` | Backgrounds & Visuals |
| `0x08` | 8 | `Cmd_if` | `IF` | `uint16_be target_block` | Conditionals |
| `0x09` | 9 | `Cmd_face_a` | `FACE_A` | `desc(2), slot, face_id` | Character Portraits |
| `0x0A` | 10 | `Cmd_facer_a` | `FACER_A` | `desc(2), slot, mode` | Character Portraits |
| `0x0B` | 11 | `Cmd_pset_a` | `PSET_A` | `desc(2), desc(1), slot, pose, z_order` | Character Portraits |
| `0x0C` | 12 | `Cmd_mset_a` | `MSET_A` | `desc(2), desc(2), desc(1), slot, x, y, w, h` | Character Portraits |
| `0x0D` | 13 | `Cmd_enter` | `ENTER` | *none* | Flow Control |
| `0x0E` | 14 | `Cmd_exec` | `EXEC` | *none* | Flow Control |
| `0x0F` | 15 | `Cmd_exit` | `EXIT` | *none* | Flow Control |
| `0x10` | 16 | `Cmd_effectB` | `EFFECTB` | *none* | Backgrounds & Visuals |
| `0x11` | 17 | `Cmd_se` | `SE` | `desc(1), se_id` | Audio & Sound |
| `0x12` | 18 | `Cmd_seStop` | `SESTOP` | `desc(1), se_id` | Audio & Sound |
| `0x13` | 19 | `Cmd_cdplay` | `CDPLAY` | `desc(1), track_id` | Audio & Sound |
| `0x14` | 20 | `Cmd_mspeed` | `MSPEED` | `desc(1), speed` | Dialogue & Text UI |
| `0x15` | 21 | `Cmd_seekB` | `SEEKB` | `desc(2), target, speed` | Backgrounds & Visuals |
| `0x16` | 22 | `Cmd_seekF` | `SEEKF` | `desc(2), target, speed` | Backgrounds & Visuals |
| `0x17` | 23 | `Cmd_backF` | `BACKF` | `desc(2), target, speed` | Backgrounds & Visuals |
| `0x18` | 24 | `Cmd_din` | `DIN` | *none* | Dialogue & Text UI |
| `0x19` | 25 | `Cmd_dout` | `DOUT` | *none* | Dialogue & Text UI |
| `0x1A` | 26 | `Cmd_nin` | `NIN` | `desc(1), speaker_id` | Dialogue & Text UI |
| `0x1B` | 27 | `Cmd_nout` | `NOUT` | *none* | Dialogue & Text UI |
| `0x1C` | 28 | `Cmd_talk` | `TALK` | *none* | Dialogue & Text UI |
| `0x1D` | 29 | `Cmd_ifv` | `IFV` | `count, [val_desc, val, block_be]...` | Conditionals |
| `0x1E` | 30 | `Cmd_ifs` | `IFS` | `count, [val_desc, val, block_be]...` | Conditionals |
| `0x1F` | 31 | `Cmd_ifo` | `IFO` | `count, [val_desc, val, block_be]...` | Conditionals |
| `0x20` | 32 | `Cmd_ifvar` | `IFVAR` | `count, [val_desc, val, block_be]...` | Conditionals |
| `0x23` | 35 | `Cmd_jsel` | `JSEL` | `count, [desc, jutsugo_id]...` | Dialogue & Text UI |
| `0x24` | 36 | `Cmd_mdel_s` | `MDEL_S` | `desc(1) spk, desc(1) pred, cnt, [nouns]...` | Dialogue & Text UI |
| `0x27` | 39 | `Cmd_watch` | `WATCH` | `uint8_t var_idx` | System & Metadata |
| `0x28` | 40 | `Cmd_watchflag` | `WATCHFLAG` | `uint16_be flag_idx` | System & Metadata |
| `0x29` | 41 | `Cmd_aurthor` | `AUTHOR` | `char author[8]` | System & Metadata |
| `0x2A` | 42 | `Cmd_place` | `PLACE` | `desc(1), place_id` | System & Metadata |
| `0x2B` | 43 | `Cmd_time` | `TIME` | `desc(2), hour, minute` | System & Metadata |
| `0x2C` | 44 | `Cmd_date` | `DATE` | `desc(2), month, day` | System & Metadata |
| `0x2D` | 45 | `Cmd_chapter` | `CHAPTER` | `desc(1), chapter_id` | System & Metadata |
| `0x2E` | 46 | `Cmd_scene` | `SCENE` | `desc(1), scene_id` | System & Metadata |
| `0x2F` | 47 | `Cmd_tagon` | `TAGON` | *none* | System & Metadata |
| `0x30` | 48 | `Cmd_tagoff` (`func_80028FA4`) | `TAGOFF` | *none* | System & Metadata |
| `0x31` | 49 | `Cmd_brainon` | `BRAINON` | *none* | System & Metadata |
| `0x32` | 50 | `Cmd_brainoff` | `BRAINOFF` | *none* | System & Metadata |
| `0x33` | 51 | `Cmd_movie` | `MOVIE` | `desc(1), movie_id` | Full-Motion Video |
| `0x34` | 52 | `Cmd_movieF` | `MOVIEF` | `desc(1), movie_id` | Full-Motion Video |
| `0x35` | 53 | `Cmd_movieF2` | `MOVIEF2` | `desc(2), desc(1), id, mode, wait` | Full-Motion Video |
| `0x36` | 54 | `Cmd_movieFstop` | `MOVIEFSTOP` | *none* | Full-Motion Video |
| `0x37` | 55 | `Cmd_movieFblock` | `MOVIEFBLOCK` | *none* | Full-Motion Video |
| `0x38` | 56 | `Cmd_movieFstate` | `MOVIEFSTATE` | `uint8_t state` | Full-Motion Video |
| `0x39` | 57 | `Cmd_movieFframe` | `MOVIEFFRAME` | `uint16_be frame` | Full-Motion Video |
| `0x3A` | 58 | `Cmd_movieFloop` | `MOVIEFLOOP` | `desc(1), loop_flag` | Full-Motion Video |
| `0x3B` | 59 | `Cmd_getRandom` | `GETRANDOM` | `desc(2), dest_var, max_val` | System & Metadata |
| `0x3D` | 61 | `Cmd_logicalAnd` | `LOGICAL_AND` | `desc(2), dest_var` | Math & Logic |
| `0x3E` | 62 | `Cmd_logicalOr` | `LOGICAL_OR` | `desc(2), dest_var` | Math & Logic |
| `0x3F` | 63 | `Cmd_bitwiseAnd` | `BITWISE_AND` | `desc(2), dest_var` | Math & Logic |
| `0x40` | 64 | `Cmd_bitwiseOr` | `BITWISE_OR` | `desc(2), dest_var` | Math & Logic |
| `0x41` | 65 | `Cmd_bitwiseXor` | `BITWISE_XOR` | `desc(2), dest_var` | Math & Logic |
| `0x42` | 66 | `Cmd_logicalNot` | `LOGICAL_NOT` | `desc(1), dest_var` | Math & Logic |
| `0x43` | 67 | `Cmd_negate` | `NEGATE` | `desc(1), dest_var` | Math & Logic |
| `0x44` | 68 | `Cmd_add` | `ADD` | `desc(2), dest_var` | Math & Logic |
| `0x45` | 69 | `Cmd_subtract` | `SUBTRACT` | `desc(2), dest_var` | Math & Logic |
| `0x46` | 70 | `Cmd_multiply` | `MULTIPLY` | `desc(2), dest_var` | Math & Logic |
| `0x47` | 71 | `Cmd_divide` | `DIVIDE` | `desc(2), dest_var` | Math & Logic |
| `0x48` | 72 | `Cmd_modulo` | `MODULO` | `desc(2), dest_var` | Math & Logic |
| `0x49` | 73 | `Cmd_setVariable` | `SETVARIABLE` | `type_desc, target_var, src_val` | Math & Logic |
| `0x4A` | 74 | `Cmd_shiftLeft` | `SHIFT_LEFT` | `desc(2), dest_var` | Math & Logic |
| `0x4B` | 75 | `Cmd_shiftRight` | `SHIFT_RIGHT` | `desc(2), dest_var` | Math & Logic |
| `0x4C` | 76 | `Cmd_equal` | `EQUAL` | `desc(2), dest_var` | Math & Logic |
| `0x4D` | 77 | `Cmd_notEqual` | `NOT_EQUAL` | `desc(2), dest_var` | Math & Logic |
| `0x4E` | 78 | `Cmd_lessThan` | `LESS_THAN` | `desc(2), dest_var` | Math & Logic |
| `0x4F` | 79 | `Cmd_lessThanOrEqual`| `LESS_THAN_OR_EQUAL` | `desc(2), dest_var` | Math & Logic |
| `0x50` | 80 | `Cmd_greaterThan` | `GREATER_THAN` | `desc(2), dest_var` | Math & Logic |
| `0x51` | 81 | `Cmd_graterThanOrEqualTo` | `GREATER_THAN_OR_EQUAL` | `desc(2), dest_var` | Math & Logic |
| `0x52` | 82 | `Cmd_thread` | `THREAD` | `desc(1), block_idx` | Flow Control |
| `0x53` | 83 | `Cmd_threadret` | `THREADRET` | *none* | Flow Control |
| `0x54` | 84 | `Cmd_threadstop` | `THREADSTOP` | *none* | Flow Control |
| `0x55` | 85 | `Cmd_facelight` | `FACELIGHT` | `count, [slot, mode]...` | Character Portraits |
| `0x56` | 86 | `Cmd_inputName` | `INPUTNAME` | `desc(1), slot_idx` | System & Metadata |
| `0x57` | 87 | `Cmd_kbg` | `KBG` | `desc(2), bg_id, effect_id` | Backgrounds & Visuals |
| `0x58` | 88 | `Cmd_kbg2` | `KBG2` | `desc(2), desc(1), bg_id, eff, wait` | Backgrounds & Visuals |
| `0x59` | 89 | `Cmd_tset` | `TSET` | `desc(2), layout_x, layout_y` | Dialogue & Text UI |
| `0x5A` | 90 | `Cmd_pmove_a` | `PMOVE_A` | `desc(2), desc(2), slot, x, y, spd` | Character Portraits |
| `0x5B` | 91 | `Cmd_bp` | `BP` | *none* | Flow Control |
| `0x5C` | 92 | `Cmd_faceEffect` | `FACEEFFECT` | `count, [slot, eff]...` | Character Portraits |
| `0x5D` | 93 | `Cmd_vardel_j` | `VARDEL_J` | `desc(1), jutsugo_id` | Dialogue & Text UI |
| `0x5E` | 94 | `Cmd_ifc` | `IFC` | `count, [val_desc, val, block_be]...` | Conditionals |
| `0x5F` | 95 | `Cmd_ifo2` | `IFO2` | `count, [val_desc, val, block_be]...` | Conditionals |
| `0x60` | 96 | `Cmd_newsel` | `NEWSEL` | `count, [desc, news_id]...` | Newspaper System |
| `0x61` | 97 | `Cmd_getnews_80029820` | `GETNEWS` | `desc(1), news_id` | Newspaper System |
| `0x62` | 98 | `Cmd_getnews_80025CCC` | `GETNEWS2` | `desc(1), news_id` | Newspaper System |
| `0x63` | 99 | `Cmd_ifc2` | `IFC2` | `count, [val_desc, val, block_be]...` | Conditionals |
| `0x64` | 100 | `Cmd_ifs2` | `IFS2` | `count, [val_desc, val, block_be]...` | Conditionals |
| `0x65` | 101 | `Cmd_loaddict` | `LOADDICT` | `desc(2), slot(0/1), file_id` | Dialogue & Text UI |
| `0x66` | 102 | `Cmd_watch16` | `WATCH16` | `uint16_be var_idx` | System & Metadata |
| `0x67` | 103 | `Cmd_newsput` | `NEWSPUT` | `desc(1), news_id` | Newspaper System |
| `0x68` | 104 | `Cmd_vibrateMode` | `VIBRATEMODE` | `desc(1), mode` | System & Metadata |
| `0x69` | 105 | `Cmd_ltalk` | `LTALK` | `desc(1), arg` | Dialogue & Text UI |
| `0x6A` | 106 | `Cmd_loadse` | `LOADSE` | `desc(1), se_bank_id` | Audio & Sound |
| `0x6B` | 107 | `Cmd_loadwaveSE` | `LOADWAVESE` | `desc(2), se_id, mode` | Audio & Sound |
| `0x6C` | 108 | `Cmd_chapterTitle`| `CHAPTERTITLE` | `desc(1), title_id` | System & Metadata |
| `0x6D` | 109 | `Cmd_secut` | `SECUT` | *none* | Audio & Sound |
| `0x6E` | 110 | `Cmd_movieflash` | `MOVIEFLASH` | `desc(2), mode, frames` | Full-Motion Video |
| `0x6F` | 111 | `Cmd_loadwavemusic` | `LOADWAVEMUSIC` | `desc(1), music_id` | Audio & Sound |
| `0x70` | 112 | `Cmd_music` | `MUSIC` | *none* | Audio & Sound |
| `0x71` | 113 | `Cmd_musiccut` | `MUSICCUT` | *none* | Audio & Sound |
| `0x72` | 114 | `Cmd_doutWithFaceSlotXX` | `DOUT_RESET` | *none* | Dialogue & Text UI |
| `0x73` | 115 | `Cmd_ninjump` | `NINJUMP` | `desc(2), speaker_id, jump_target` | Dialogue & Text UI |
| `0x74` | 116 | `Cmd_preDinXX` | `PREDIN` | *none* | Dialogue & Text UI |
| `0x75` | 117 | `Cmd_loadmusic` | `LOADMUSIC` | `desc(1), bgm_id` | Audio & Sound |
| `0x76` | 118 | `Cmd_allSE` | `ALLSE` | `desc(2), desc(1), vol, pan, fade` | Audio & Sound |
| `0x77` | 119 | `Cmd_allmuisc` | `ALLMUSIC` | `desc(2), desc(2), vol, pan, fade, spd` | Audio & Sound |
| `0x78` | 120 | `Cmd_allStream` | `ALLSTREAM` | `desc(2), desc(1), vol, pan, fade` | Audio & Sound |
| `0x79` | 121 | `Cmd_loadwaveStream` | `LOADWAVESTREAM` | `desc(1), stream_id` | Audio & Sound |
| `0x7A` | 122 | `Cmd_movie2` | `MOVIE2` | `desc(2), desc(2), desc(1), 5 args` | Full-Motion Video |
| `0x7B` | 123 | `Cmd_nincall` | `NINCALL` | `desc(2), speaker_id, return_block`| Dialogue & Text UI |
| `0x7C` | 124 | `Cmd_loadkanji` | `LOADKANJI` | `desc(1), kanji_bank_id` | Dialogue & Text UI |
| `0x7D` | 125 | `Cmd_vibrateflash` | `VIBRATEFLASH` | *none* | System & Metadata |
| `0x7E` | 126 | `Cmd_mwin` | `MWIN` | `count, [slot, x, y, w, h]...` | Dialogue & Text UI |
| `0x7F` | 127 | `Cmd_print_a` | `PRINT_A` | `desc(1) slot, text_stream... 0x06` | Dialogue & Text UI |
| `0x80` | 128 | `Cmd_endTitle` | `ENDTITLE` | `desc(1), end_id` | System & Metadata |
| `0x81` | 129 | `Cmd_newsquit` | `NEWSQUIT` | *none* | Newspaper System |
| `0x82` | 130 | `Cmd_ninwait` | `NINWAIT` | `desc(1), frames` | Dialogue & Text UI |
| `0x83` | 131 | `Cmd_byuu` | `BYUU` | *none* | Dialogue & Text UI |
| `0x84` | 132 | `Cmd_ve` | `VE` | `desc(1), voice_id` | Audio & Sound |
| `0x85` | 133 | `Cmd_soundmode` | `SOUNDMODE` | `desc(1), mode(stereo/mono)` | Audio & Sound |
| `0x86` | 134 | `Cmd_menuMode` | `MENUMODE` | `desc(1), mode` | System & Metadata |
| `0x87` | 135 | `Cmd_oneSE` | `ONESE` | `desc(2), desc(2), desc(1), 5 args` | Audio & Sound |
| `0x88` | 136 | `Cmd_seloop` | `SELOOP` | `desc(1), se_id` | Audio & Sound |
| `0x89` | 137 | `Cmd_menuOpen` | `MENUOPEN` | `desc(1), menu_id` | System & Metadata |
| `0x8A` | 138 | `Cmd_dinbrainoff`| `DINBRAINOFF` | *none* | Dialogue & Text UI |
| `0x8B` | 139 | `Cmd_sse` | `SSE` | `desc(1), se_id` | Audio & Sound |
| `0x8C` | 140 | `Cmd_vestop` | `VESTOP` | *none* | Audio & Sound |
| `0x8D` | 141 | `Cmd_movieflash2`| `MOVIEFLASH2` | `desc(2), desc(2), desc(2), 6 args` | Full-Motion Video |
| `0x8E` | 142 | `Cmd_channelMute`| `CHANNELMUTE` | `desc(1), channel_mask` | Audio & Sound |
| `0x8F` | 143 | `Cmd_finale` | `FINALE` | *none* | Audio & Sound |
| `0xFC` | 252 | `Cmd_present` | `PRESENT` | *none* | Flow Control |
| `0xFF` | 255 | `Cmd_end` | `END` | *none* | Flow Control |

---

## 5. Detailed Opcode Specifications by Functional Group

### Group 1: Flow Control & Multithreading

#### `0x01` (`Cmd_handleScriptBlock` / `JUMP`)
* **Format**: `0x01 [desc] [block_index]`
* **How it works**:
  Unconditionally branches to a script block target indexed in `scriptBlockTable[block_index]`. If debug logging is enabled, logs `JUMP <block_index>`.

#### `0x02` (`Cmd_call` / `CALL`)
* **Format**: `0x02 [desc] [target_block_index] [8-byte ASCII label]`
* **How it works**:
  Pushes the current `scriptInstructionPointer` onto the 16-level call stack `scriptCallStack[callDepth++]`. Records the 8-byte ASCII label in `g_ActiveScriptLabel` for debugging, and branches to `scriptBlockTable[target_block_index]`.

#### `0x03` (`Cmd_return` / `RETURN`)
* **Format**: `0x03`
* **How it works**:
  Pops the caller's bytecode address from `scriptCallStack[--callDepth]`. If `callDepth == 0`, raises a fatal runtime error `"return: don't know where to return"`.

#### `0x04` (`Cmd_sjump` / `SJUMP`)
* **Format**: `0x04 [desc] [script_id]`
* **How it works**:
  Performs an inter-file scenario transition. Queues the target script ID from Group 05 (`scripts/`) into `nextScriptId`, terminates execution of the current `.ZZS` file, and triggers `LoadStoryScript` upon the next frame loop.

#### `0x05` (`Cmd_wait` / `WAIT`)
* **Format**: `0x05 [desc] [frames]`
* **How it works**:
  Suspends script interpreter advancement for `frames` V-Blank cycles (`waitFrameCounter = frames`). The engine continues rendering animations and backgrounds while waiting.

#### `0x0D` (`Cmd_enter` / `ENTER`), `0x0E` (`Cmd_exec` / `EXEC`), `0x0F` (`Cmd_exit` / `EXIT`)
* **Format**: `0x0D`, `0x0E`, `0x0F`
* **How it works**:
  Controls character entrance and exit sequences. `ENTER` sets character slot visibility flags, `EXEC` begins concurrent character entrance movement interpolation, and `EXIT` removes character portraits from active render lists.

#### `0x52` (`Cmd_thread` / `THREAD`)
* **Format**: `0x52 [desc] [block_index]`
* **How it works**:
  Allocates an asynchronous secondary execution thread in `scriptThreadTable` starting at `scriptBlockTable[block_index]`. Allows background scripts (e.g. ambient lighting loops or sound timers) to run parallel to main dialogue.

#### `0x53` (`Cmd_threadret` / `THREADRET`), `0x54` (`Cmd_threadstop` / `THREADSTOP`)
* **Format**: `0x53`, `0x54`
* **How it works**:
  `THREADRET` returns from a thread subroutine. `THREADSTOP` terminates the calling thread and frees its slot in `scriptThreadTable`.

#### `0x5B` (`Cmd_bp` / `BP`)
* **Format**: `0x5B`
* **How it works**:
  Debug breakpoint hook. If connected to a PSX DTL-H developer station, pauses execution and invokes the TTY debugger.

#### `0xFC` (`Cmd_present` / `PRESENT`)
* **Format**: `0xFC`
* **How it works**:
  Frame presentation sync marker. Forces the VM to yield until the GPU finishes drawing the active display buffer and page flip occurs.

#### `0xFF` (`Cmd_end` / `END`)
* **Format**: `0xFF`
* **How it works**:
  Terminates execution of the current scenario script and returns control to the master chapter sequencer.

---

### Group 2: Conditionals & Evaluation Ladders

#### `0x08` (`Cmd_if` / `IF`)
* **Format**: `0x08 [uint16_be target_block_index]`
* **How it works**:
  Evaluates the boolean result of the preceding mathematical or logical expression (`rawMemoryPool[0]`). If non-zero (true), branches to `scriptBlockTable[target_block_index]`; otherwise, continues to the next instruction.

#### `0x1D` (`Cmd_ifv` / `IFV`), `0x1E` (`Cmd_ifs` / `IFS`), `0x1F` (`Cmd_ifo` / `IFO`), `0x5E` (`Cmd_ifc` / `IFC`)
* **Format**: `0x1D [uint8_t count] { [desc] [value] [uint16_be target_block] }...`
* **How it works**:
  The **Taiwa Evaluation Ladder**. Compares the player's dialogue input result against a table of candidate Word IDs:
  * `0x1D` (`IFV`): Compares Verb ID (`taiwaJv`).
  * `0x1E` (`IFS`): Compares Subject / Topic ID (`taiwaJn`).
  * `0x1F` (`IFO`): Compares Object ID.
  * `0x5E` (`IFC`): Compares Complement / Context ID.
  If a match is found, branches directly to that entry's `target_block`. If no entry matches after `count` iterations, falls through to the next bytecode instruction.

#### `0x20` (`Cmd_ifvar` / `IFVAR`)
* **Format**: `0x20 [uint8_t count] { [desc] [value] [uint16_be target_block] }...`
* **How it works**:
  Multi-way branch table comparing a variable against multiple literal integer values.

#### `0x5F` (`Cmd_ifo2` / `IFO2`), `0x63` (`Cmd_ifc2` / `IFC2`), `0x64` (`Cmd_ifs2` / `IFS2`)
* **Format**: `0x5F / 0x63 / 0x64 [uint8_t count] { [desc] [value] [uint16_be target_block] }...`
* **How it works**:
  Secondary Taiwa evaluation ladders for complex branch sentences containing secondary subjects, indirect objects, or secondary verbs.

---

### Group 3: Backgrounds, Stills & Visual Effects

#### `0x06` (`Cmd_bg` / `BG`)
* **Format**: `0x06 [desc] [bg_id] [transition_effect_id]`
* **How it works**:
  Loads background TIM image `bg_id` from Group 06 (`backgrounds/`) into VRAM and initiates transition `transition_effect_id` (e.g. cut, fade, dissolve, wipe).

#### `0x07` (`Cmd_bg2` / `BG2`)
* **Format**: `0x07 [desc1] [desc2] [bg_id] [transition_effect_id] [wait_frames]`
* **How it works**:
  Extended background command. Loads background image, initiates transition, and automatically halts the VM for `wait_frames` until the transition finishes.

#### `0x10` (`Cmd_effectB` / `EFFECTB`)
* **Format**: `0x10`
* **How it works**:
  Waits for any active background transition or palette cycle effect to reach completion.

#### `0x15` (`Cmd_seekB` / `SEEKB`), `0x16` (`Cmd_seekF` / `SEEKF`), `0x17` (`Cmd_backF` / `BACKF`)
* **Format**: `0x15 / 0x16 / 0x17 [desc] [target_pos] [speed]`
* **How it works**:
  Seeks and pans background images or frame sequences backward or forward across wide pan vistas (e.g. crime scenes or hallway pans).

#### `0x57` (`Cmd_kbg` / `KBG`), `0x58` (`Cmd_kbg2` / `KBG2`)
* **Format**: `0x57 [desc] [kbg_id] [effect_id]` / `0x58 [desc1] [desc2] [kbg_id] [effect_id] [wait]`
* **How it works**:
  Loads keyframe cutin backgrounds (*Kiri-BG* / 切り替え背景) used for dramatic close-ups or evidence inspect screens.

---

### Group 4: Full-Motion Video (STR / MDEC Playback)

#### `0x33` (`Cmd_movie` / `MOVIE`)
* **Format**: `0x33 [desc] [movie_id]`
* **How it works**:
  Streams full-screen PlayStation MDEC video `movie_id` from Group 00 (`video/`). The CD drive streams sectors directly to the MDEC chip while audio streams to SPU channels 1/2.

#### `0x34` (`Cmd_movieF` / `MOVIEF`), `0x35` (`Cmd_movieF2` / `MOVIEF2`)
* **Format**: `0x34 [desc] [movie_id]` / `0x35 [desc1] [desc2] [movie_id] [mode] [wait]`
* **How it works**:
  Plays an integrated foreground movie with transparency/matte channel support, allowing video elements (e.g. flickering TV screen, rainy window) over background scenes.

#### `0x36` (`Cmd_movieFstop` / `MOVIEFSTOP`), `0x37` (`Cmd_movieFblock` / `MOVIEFBLOCK`)
* **Format**: `0x36`, `0x37`
* **How it works**:
  `MOVIEFSTOP` halts video streaming immediately. `MOVIEFBLOCK` suspends the VM until the current video reaches its last frame.

#### `0x38` (`Cmd_movieFstate` / `MOVIEFSTATE`), `0x39` (`Cmd_movieFframe` / `MOVIEFFRAME`), `0x3A` (`Cmd_movieFloop` / `MOVIEFLOOP`)
* **Format**: `0x38 [state]`, `0x39 [uint16_be frame]`, `0x3A [desc] [loop_flag]`
* **How it works**:
  Controls playback states: sets looping flags, queries frame decoders, and jumps directly to a specific timestamp frame.

#### `0x6E` (`Cmd_movieflash` / `MOVIEFLASH`), `0x8D` (`Cmd_movieflash2` / `MOVIEFLASH2`)
* **Format**: `0x6E [desc] [mode] [frames]` / `0x8D [desc1] [desc2] [desc3] [6 args]`
* **How it works**:
  Triggers rapid strobe/white-out flash transitions synchronized with movie keyframes.

#### `0x7A` (`Cmd_movie2` / `MOVIE2`)
* **Format**: `0x7A [desc1] [desc2] [desc3] [movie_id] [offset_frames] [fade_y] [fade_h] [mode]`
* **How it works**:
  Advanced letterboxed video stream with custom vertical crop and alpha fade parameters.

---

### Group 5: Character Portraits & Live Animation

#### `0x09` (`Cmd_face_a` / `FACE_A`)
* **Format**: `0x09 [desc] [slot_idx] [face_id]`
* **How it works**:
  Binds character animation asset `face_id` (from Group 07 `animations/`) to display slot `slot_idx` (0..3).

#### `0x0A` (`Cmd_facer_a` / `FACER_A`)
* **Format**: `0x0A [desc] [slot_idx] [mode]`
* **How it works**:
  Resets and unloads the character portrait from slot `slot_idx`.

#### `0x0B` (`Cmd_pset_a` / `PSET_A`)
* **Format**: `0x0B [desc1] [desc2] [slot_idx] [pose_id] [z_priority]`
* **How it works**:
  Sets the current expression/pose index for character `slot_idx` and assigns its rendering z-depth.

#### `0x0C` (`Cmd_mset_a` / `MSET_A`)
* **Format**: `0x0C [desc1] [desc2] [desc3] [slot_idx] [x] [y] [width] [height]`
* **How it works**:
  Configures the screen coordinates and clipping bounding box for character portrait `slot_idx`.

#### `0x55` (`Cmd_facelight` / `FACELIGHT`)
* **Format**: `0x55 [uint8_t count] { [slot_idx] [blend_mode] }...`
* **How it works**:
  Adjusts GPU blending modes (semi-transparency, additive tint, dark silhouette) for character slots.

#### `0x5A` (`Cmd_pmove_a` / `PMOVE_A`)
* **Format**: `0x5A [desc1] [desc2] [slot_idx] [target_x] [target_y] [speed]`
* **How it works**:
  Smoothly interpolates character `slot_idx` from its current coordinates to `(target_x, target_y)` at `speed` pixels per frame.

#### `0x5C` (`Cmd_faceEffect` / `FACEEFFECT`)
* **Format**: `0x5C [uint8_t count] { [slot_idx] [effect_id] }...`
* **How it works**:
  Applies special visual distortions (e.g. shock vibration, screen shake, ghosting) to character portraits.

---

### Group 6: Dialogue, Text Presentation & Taiwa (NLP) Subsystem

#### `0x14` (`Cmd_mspeed` / `MSPEED`)
* **Format**: `0x14 [desc] [speed_delay]`
* **How it works**:
  Configures typewriter character display delay (0 = instantaneous, higher = slower).

#### `0x18` (`Cmd_din` / `DIN`), `0x19` (`Cmd_dout` / `DOUT`)
* **Format**: `0x18`, `0x19`
* **How it works**:
  `DIN` (Dialogue In) draws the dialogue box chrome and initializes text tracking. `DOUT` (Dialogue Out) closes the dialogue box, resets character tracking state, and clears the text display buffers.

#### `0x1A` (`Cmd_nin` / `NIN`), `0x1B` (`Cmd_nout` / `NOUT`)
* **Format**: `0x1A [desc] [speaker_id]`, `0x1B`
* **How it works**:
  `NIN` (Nameplate In) opens the speaker nameplate window displaying character `speaker_id` (from `NAME.BBB`). `NOUT` closes the nameplate.

#### `0x1C` (`Cmd_talk` / `TALK`), `0x69` (`Cmd_ltalk` / `LTALK`)
* **Format**: `0x1C` / `0x69 [desc] [arg]`
* **How it works**:
  Suspends script execution and transfers control to the **Taiwa UI subsystem**. The player selects Subject, Object, and Verb words from the dictionary. Upon confirmation, results are stored into `taiwaJn` and `taiwaJv`, and script execution resumes.

#### `0x23` (`Cmd_jsel` / `JSEL`)
* **Format**: `0x23 [uint8_t count] { [desc] [jutsugo_id] }...`
* **How it works**:
  Registers available predicate (*Jutsugo* / 述語) verb candidates into the Taiwa selection menu pool.

#### `0x24` (`Cmd_mdel_s` / `MDEL_S`)
* **Format**: `0x24 [desc1] [desc2] [speaker_id] [predicate_id] [count] { [noun_id] }...`
* **How it works**:
  Prunes/deletes specific noun candidates associated with a speaker and predicate from active memory.

#### `0x59` (`Cmd_tset` / `TSET`)
* **Format**: `0x59 [desc] [layout_x] [layout_y]`
* **How it works**:
  Configures screen coordinate positions `(layout_x, layout_y)` for the Taiwa 3-box sentence layout interface.

#### `0x5D` (`Cmd_vardel_j` / `VARDEL_J`)
* **Format**: `0x5D [desc] [jutsugo_id]`
* **How it works**:
  Clears a specific predicate candidate from the player's Taiwa selection pool.

#### `0x65` (`Cmd_loaddict` / `LOADDICT`)
* **Format**: `0x65 [desc] [slot] [file_id]`
* **How it works**:
  Invokes `LoadDictionaryData` to load chapter vocabulary from Group 02 (`dictionary/`):
  * `slot = 0`: Loads `JDICT<XX>.DCT` (vocabulary & semantic association tags).
  * `slot = 1`: Loads `MDICT<XX>.DCT` (morphological transition trie).

#### `0x73` (`Cmd_ninjump` / `NINJUMP`), `0x7B` (`Cmd_nincall` / `NINCALL`), `0x82` (`Cmd_ninwait` / `NINWAIT`)
* **Format**:
  * `0x73 [desc] [speaker_id] [target_block]`
  * `0x7B [desc] [speaker_id] [return_block]`
  * `0x82 [desc] [frames]`
* **How it works**:
  Combined speaker nameplate operations that integrate branching, subroutine calls, or timed waits.

#### `0x7C` (`Cmd_loadkanji` / `LOADKANJI`)
* **Format**: `0x7C [desc] [kanji_bank_id]`
* **How it works**:
  Loads dynamic 16x16 Kanji glyph textures from Group 01 (`system/`) into VRAM page `(768, 256)`.

#### `0x7E` (`Cmd_mwin` / `MWIN`)
* **Format**: `0x7E [uint8_t count] { [slot] [x] [y] [w] [h] }...`
* **How it works**:
  Customizes dialogue box window positions and borders per character speaker.

#### `0x7F` (`Cmd_print_a` / `PRINT_A`)
* **Format**: `0x7F [desc] [character_slot] [encoded text stream...] 0x06`
* **How it works**:
  The primary dialogue text rendering command. Renders characters onto the active message window at the typing speed defined by `MSPEED`.
  * Control codes: `0x00` = Wait for button, `0x01` = Newline, `0x04` = Clear box, `0x05` = Timed auto-delay, `0x06` = End of text stream, `0x19 <id>` = Insert name macro.
  * Encoded using Another Mind's custom 1-byte/2-byte Kanji character encoding.

#### `0x83` (`Cmd_byuu` / `BYUU`)
* **Format**: `0x83`
* **How it works**:
  Triggers the protagonist's psychic thought prompt sound and screen shimmer.

---

### Group 7: Audio, SPU Sound Effects & Streaming

#### `0x11` (`Cmd_se` / `SE`), `0x12` (`Cmd_seStop` / `SESTOP`), `0x6D` (`Cmd_secut` / `SECUT`)
* **Format**: `0x11 [desc] [se_id]`, `0x12 [desc] [se_id]`, `0x6D`
* **How it works**:
  `SE` triggers playback of sound effect `se_id`. `SESTOP` gently fades out the sound. `SECUT` stops all active SPU voice channels immediately.

#### `0x13` (`Cmd_cdplay` / `CDPLAY`)
* **Format**: `0x13 [desc] [track_num]`
* **How it works**:
  Sends a play command to the CD drive controller to play CD-DA Red Book audio track `track_num`.

#### `0x6A` (`Cmd_loadse` / `LOADSE`), `0x6B` (`Cmd_loadwaveSE` / `LOADWAVESE`)
* **Format**: `0x6A [desc] [se_bank_id]`, `0x6B [desc] [audio_id] [mode]`
* **How it works**:
  Loads sound effect sample banks from Group 08 (`audio/`) into SPU RAM.

#### `0x70` (`Cmd_music` / `MUSIC`), `0x71` (`Cmd_musiccut` / `MUSICCUT`), `0x75` (`Cmd_loadmusic` / `LOADMUSIC`)
* **Format**: `0x70`, `0x71`, `0x75 [desc] [bgm_id]`
* **How it works**:
  Controls Squaresoft Akao music sequence playback. `LOADMUSIC` transfers sequence data to memory, `MUSIC` starts sequencer playback, and `MUSICCUT` halts music.

#### `0x6F` (`Cmd_loadwavemusic` / `LOADWAVEMUSIC`), `0x79` (`Cmd_loadwaveStream` / `LOADWAVESTREAM`)
* **Format**: `0x6F [desc] [music_id]`, `0x79 [desc] [stream_id]`
* **How it works**:
  Loads and manages ADPCM streaming audio for vocal themes and ambient audio loops.

#### `0x76` (`Cmd_allSE` / `ALLSE`), `0x77` (`Cmd_allmuisc` / `ALLMUSIC`), `0x78` (`Cmd_allStream` / `ALLSTREAM`)
* **Format**:
  * `0x76 [desc1] [desc2] [vol] [pan] [fade_time]`
  * `0x77 [desc1] [desc2] [vol] [pan] [fade_time] [speed]`
  * `0x78 [desc1] [desc2] [vol] [pan] [fade_time]`
* **How it works**:
  Global mixing controls for mastering volume, stereo panning, and fade-in/fade-out curves.

#### `0x84` (`Cmd_ve` / `VE`), `0x8C` (`Cmd_vestop` / `VESTOP`)
* **Format**: `0x84 [desc] [voice_id]`, `0x8C`
* **How it works**:
  Plays and stops vocal voice acting samples (*Voice Effect*).

#### `0x87` (`Cmd_oneSE` / `ONESE`), `0x88` (`Cmd_seloop` / `SELOOP`), `0x8B` (`Cmd_sse` / `SSE`)
* **Format**:
  * `0x87 [desc1] [desc2] [desc3] [se_id] [vol] [pan] [pitch] [priority]`
  * `0x88 [desc] [se_id]`
  * `0x8B [desc] [se_id]`
* **How it works**:
  `ONESE` fires a single-shot sound effect with custom spatial pan and pitch shift. `SELOOP` loops continuously until stopped. `SSE` plays a sound synchronized with character mouth flaps.

#### `0x8E` (`Cmd_channelMute` / `CHANNELMUTE`), `0x8F` (`Cmd_finale` / `FINALE`)
* **Format**: `0x8E [desc] [channel_mask]`, `0x8F`
* **How it works**:
  `CHANNELMUTE` mutes specific SPU channels. `FINALE` executes a grand fade-out of all music and sound for dramatic scene finales.

---

### Group 8: Scenario Metadata, Hardware & System UI

#### `0x27` (`Cmd_watch` / `WATCH`), `0x28` (`Cmd_watchflag` / `WATCHFLAG`), `0x66` (`Cmd_watch16` / `WATCH16`)
* **Format**: `0x27 [uint8_t var_idx]`, `0x28 [uint16_be flag_idx]`, `0x66 [uint16_be var_idx]`
* **How it works**:
  Attaches an on-screen debug inspector watch to variable `I[var_idx]`, bitflag `F[flag_idx]`, or global `G[var_idx]`.

#### `0x29` (`Cmd_aurthor` / `AUTHOR`)
* **Format**: `0x29 [8-byte ASCII string]`
* **How it works**:
  Always placed immediately at the beginning of `.ZZS` bytecode. Stores the author's initials/name (e.g. `TAKEDA  `, `KURI    `, `BUCHI   `, `MINORI  `).

#### `0x2A` (`Cmd_place` / `PLACE`), `0x2B` (`Cmd_time` / `TIME`), `0x2C` (`Cmd_date` / `DATE`)
* **Format**:
  * `0x2A [desc] [place_id]`
  * `0x2B [desc] [hour] [minute]`
  * `0x2C [desc] [month] [day]`
* **How it works**:
  Sets the in-game calendar timestamp and location metadata displayed on investigation dossier screens and notebook headers.

#### `0x2D` (`Cmd_chapter` / `CHAPTER`), `0x2E` (`Cmd_scene` / `SCENE`)
* **Format**: `0x2D [desc] [chapter_id]`, `0x2E [desc] [scene_id]`
* **How it works**:
  Updates the global scenario progress index.

#### `0x2F` (`Cmd_tagon` / `TAGON`), `0x30` (`Cmd_tagoff` / `TAGOFF`)
* **Format**: `0x2F`, `0x30`
* **How it works**:
  Toggles the display of character profile dossier evidence tags (*Tag* / 附箋).

#### `0x31` (`Cmd_brainon` / `BRAINON`), `0x32` (`Cmd_brainoff` / `BRAINOFF`)
* **Format**: `0x31`, `0x32`
* **How it works**:
  Toggles the psychic link monitor wave UI (*Brain On/Off*) in the corner of the screen.

#### `0x3B` (`Cmd_getRandom` / `GETRANDOM`)
* **Format**: `0x3B [desc] [dest_var] [max_val]`
* **How it works**:
  Generates a pseudo-random integer between `0` and `max_val - 1` and writes it to `dest_var`.

#### `0x56` (`Cmd_inputName` / `INPUTNAME`)
* **Format**: `0x56 [desc] [slot_idx]`
* **How it works**:
  Opens the PlayStation character name entry keyboard interface, allowing the player to enter a custom name stored in `NAME.BBB`.

#### `0x68` (`Cmd_vibrateMode` / `VIBRATEMODE`), `0x7D` (`Cmd_vibrateflash` / `VIBRATEFLASH`)
* **Format**: `0x68 [desc] [mode]`, `0x7D`
* **How it works**:
  `VIBRATEMODE` toggles DualShock vibration motor support. `VIBRATEFLASH` triggers a simultaneous controller rumble and screen white flash.

#### `0x6C` (`Cmd_chapterTitle` / `CHAPTERTITLE`), `0x80` (`Cmd_endTitle` / `ENDTITLE`)
* **Format**: `0x6C [desc] [title_id]`, `0x80 [desc] [end_id]`
* **How it works**:
  Displays chapter title card animations (`CHAP<N>_G.TIM`) or the game ending sequence.

#### `0x86` (`Cmd_menuMode` / `MENUMODE`), `0x89` (`Cmd_menuOpen` / `MENUOPEN`)
* **Format**: `0x86 [desc] [mode]`, `0x89 [desc] [menu_id]`
* **How it works**:
  Controls access and opens sub-screens (Notebook, Map, Evidence Dossier, Save/Load).

---

### Group 9: Newspaper / Clue Notebook Subsystem

#### `0x60` (`Cmd_newsel` / `NEWSEL`)
* **Format**: `0x60 [uint8_t count] { [desc] [news_id] }...`
* **How it works**:
  Opens the newspaper headline selector, populating `count` article candidates from Group 04 (`menus/news/`).

#### `0x61` (`Cmd_getnews` / `GETNEWS`), `0x62` (`Cmd_getnews` / `GETNEWS2`)
* **Format**: `0x61 / 0x62 [desc] [news_id]`
* **How it works**:
  Queries whether article `news_id` has been inspected by the player.

#### `0x67` (`Cmd_newsput` / `NEWSPUT`)
* **Format**: `0x67 [desc] [news_id]`
* **How it works**:
  Marks newspaper clipping `news_id` as discovered and adds it to the player's notebook dossier.

#### `0x81` (`Cmd_newsquit` / `NEWSQUIT`)
* **Format**: `0x81`
* **How it works**:
  Closes the newspaper reading viewer and returns to the scenario script.

---

### Group 10: Variable Assignments & Mathematical Operations

All equation operations take a **2-byte header**:
1. `operandTypeByte`: packed descriptor specifying addressing modes for LHS (low nibble) and RHS (high nibble).
2. `destinationIndex`: index into `rawMemoryPool[destinationIndex]` where the 16-bit signed result is stored.

#### Binary Arithmetic Opcodes
* **`0x44` (`Cmd_add` / `ADD`)**: `dest = lhs + rhs`
* **`0x45` (`Cmd_subtract` / `SUBTRACT`)**: `dest = lhs - rhs`
* **`0x46` (`Cmd_multiply` / `MULTIPLY`)**: `dest = lhs * rhs`
* **`0x47` (`Cmd_divide` / `DIVIDE`)**: `dest = lhs / rhs`
* **`0x48` (`Cmd_modulo` / `MODULO`)**: `dest = lhs % rhs`
* **`0x4A` (`Cmd_shiftLeft` / `SHIFT_LEFT`)**: `dest = lhs << rhs`
* **`0x4B` (`Cmd_shiftRight` / `SHIFT_RIGHT`)**: `dest = lhs >> rhs`

#### Logical & Bitwise Opcodes
* **`0x3D` (`Cmd_logicalAnd` / `LOGICAL_AND`)**: `dest = (lhs != 0) && (rhs != 0)`
* **`0x3E` (`Cmd_logicalOr` / `LOGICAL_OR`)**: `dest = (lhs != 0) || (rhs != 0)`
* **`0x3F` (`Cmd_bitwiseAnd` / `BITWISE_AND`)**: `dest = lhs & rhs`
* **`0x40` (`Cmd_bitwiseOr` / `BITWISE_OR`)**: `dest = lhs | rhs`
* **`0x41` (`Cmd_bitwiseXor` / `BITWISE_XOR`)**: `dest = lhs ^ rhs`
* **`0x42` (`Cmd_logicalNot` / `LOGICAL_NOT`)**: Unary logical NOT: `dest = (lhs == 0)`
* **`0x43` (`Cmd_negate` / `NEGATE`)**: Unary arithmetic negation: `dest = -lhs`

#### Comparison Opcodes
* **`0x4C` (`Cmd_equal` / `EQUAL`)**: `dest = (lhs == rhs)`
* **`0x4D` (`Cmd_notEqual` / `NOT_EQUAL`)**: `dest = (lhs != rhs)`
* **`0x4E` (`Cmd_lessThan` / `LESS_THAN`)**: `dest = (lhs < rhs)`
* **`0x4F` (`Cmd_lessThanOrEqual` / `LESS_THAN_OR_EQUAL`)**: `dest = (lhs <= rhs)`
* **`0x50` (`Cmd_greaterThan` / `GREATER_THAN`)**: `dest = (lhs > rhs)`
* **`0x51` (`Cmd_graterThanOrEqualTo` / `GREATER_THAN_OR_EQUAL`)**: `dest = (lhs >= rhs)`

#### Variable Assignment (`0x49` `Cmd_setVariable`)
* **Format**: `0x49 [typeByte] [target_var_id] [value_bytes...]`
* **How it works**:
  Stores an evaluated value or constant into a persistent variable:
  * `typeByte & 0xF == 1`: Writes 8-bit value to `scriptVar8[target_var_id]` (`I[var] = val`).
  * `typeByte & 0xF == 2`: Writes 16-bit value to `scriptVar16[target_var_id]` (`G[var] = val`).
  * `typeByte & 0xF == 3`: Writes boolean bit to `globalVariableTable[target_var_id]` (`F[bit] = val`).
  * `typeByte & 0xF == 0`: Writes 8-bit value to `rawMemoryPool[target_var_id]`.

---

## 6. Related Specifications & Decompilation Sources

* [`docs/md_reference/ZZS_SPECIFICATION.md`](file:///home/halkun/reverse/anothermind/anothermind-decomp/docs/md_reference/ZZS_SPECIFICATION.md): High-level overview of script files and dialogue text encoding.
* [`docs/md_reference/DICTIONARY_SPECIFICATION.md`](file:///home/halkun/reverse/anothermind/anothermind-decomp/docs/md_reference/DICTIONARY_SPECIFICATION.md): Taiwa 3-box sentence engine, dictionary formats (`.DCT`, `.BBB`, `.KAT`), and evaluation ladders.
* [`docs/md_reference/asset_filenames.md`](file:///home/halkun/reverse/anothermind/anothermind-decomp/docs/md_reference/asset_filenames.md): Complete directory structure and file naming conventions.
* [`src/main/script.c`](file:///home/halkun/reverse/anothermind/anothermind-decomp/src/main/script.c): Target C decompilation source for the script interpreter.
* [`docs/notes/SLPS_016.55.c`](file:///home/halkun/reverse/anothermind/anothermind-decomp/docs/notes/SLPS_016.55.c): Ghidra pseudo-C disassembly and reference symbols.

