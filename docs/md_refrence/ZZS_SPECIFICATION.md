# Another Mind (PSX) - ZZS Script Format & Text Encoding Specification

## 1. Overview
The `.ZZS` format (stored as compressed `.ZZZ` assets on disc, extracted into `assets/jp/progdata/scripts/`) represents compiled scenario bytecode for Squaresoft's *Another Mind* (1998, PSX).

The engine executes this bytecode via an interpreter implemented in [`src/main/script.c`](file:///home/halkun/reverse/anothermind/anothermind-decomp/src/main/script.c) and analyzed in [`docs/notes/SLPS_016.55.c`](file:///home/halkun/reverse/anothermind/anothermind-decomp/docs/notes/SLPS_016.55.c).

---

## 2. ZZS File Structure

Every `.ZZS` file consists of:
1. A **10-byte fixed header**
2. A **16-bit Jump Block / Label Offset Table**
3. The **Bytecode Stream**

```
+-----------------------------------------------------------+
| Offset (Hex) | Size (Bytes) | Description                 |
+--------------+--------------+-----------------------------+
| 0x00 - 0x03  | 4            | Compiler Version / Date     |
|              |              | (Month, Day, Hour, Min)     |
| 0x04 - 0x05  | 2            | Reserved / Flags (0x0000)   |
| 0x06 - 0x07  | 2            | Total File Size (Big Endian)|
| 0x08 - 0x09  | 2            | Label Count N (Big Endian)  |
| 0x0A - ...   | N * 2        | Label Offset Table (BE uint)|
| Base =       | Remainder    | Script Bytecode Stream      |
| 0x0A + N * 2 |              |                             |
+-----------------------------------------------------------+
```

### Jump Block / Label Offset Table
- `N` represents the number of jump targets defined in the script.
- Each entry is a 16-bit big-endian unsigned integer representing an offset **relative to `Base`** (`0x0A + N * 2`).
- Script jump opcodes (such as `0x01 JUMP`, `0x04 SJUMP`, `0x02 CALL`) reference an index in this table (`scriptBlockTable[index]`), making intra-file jumps relocatable.

---

## 3. Bytecode Operands & Addressing Modes

Opcodes that take parameters use an operand descriptor byte parsed by `decodeScriptOperand`:
- The descriptor byte encodes addressing modes in **4-bit nibbles**:
  - Low nibble: Operand 1 mode
  - High nibble: Operand 2 mode
  - If a 3rd or 4th operand exists, subsequent descriptor bytes follow.

| Mode (Nibble) | Data Type / Addressing Mode | Size in Stream | Description |
|:---:|:---|:---:|:---|
| `0x0` | 8-bit Global Variable | 1 byte | Reads `rawMemoryPool[idx]` |
| `0x1` | 8-bit Local Variable | 1 byte | Reads `scriptVar8[idx]` |
| `0x2` | 16-bit Variable | 2 bytes (BE) | Reads `scriptVar16[idx]` |
| `0x3` | Boolean Bitflag | 2 bytes (BE) | `globalVariableTable[bit / 8] & (1 << (bit % 8))` |
| `0x4` | Immediate 16-bit Integer | 2 bytes (BE) | Raw 16-bit value |
| `0x5` | Immediate 8-bit Integer | 1 byte | Raw 8-bit value |
| `0x6` | Immediate 16-bit Integer | 2 bytes (BE) | Raw 16-bit value |
| `0x7` | Taiwa Noun ID | 0 bytes | Dynamic lookup via `getTaiwaNoun()` |
| `0x8` | Immediate 16-bit Integer | 2 bytes (BE) | Raw 16-bit value |
| `0x9` | Immediate 16-bit Integer | 2 bytes (BE) | Raw 16-bit value |

---

## 4. Key Bytecode Opcodes

The opcode handler jump table is initialized in `InitOpcodeHandlerTable` (`0x8001BE64`):

| Opcode | Handler Name | Functionality |
|:---|:---|:---|
| `0x01` | `Cmd_handleScriptBlock` | Jump / block entrypoint with label string |
| `0x02` | `Cmd_call` | Call script subroutine |
| `0x03` | `Cmd_return` | Return from script subroutine |
| `0x04` | `Cmd_sjump` | Simple jump |
| `0x05` | `Cmd_wait` | Wait frames |
| `0x06` | `Cmd_bg` | Set background graphic |
| `0x08` | `Cmd_if` | Conditional branch |
| `0x09` | `Cmd_face_a` | Display character portrait/expression |
| `0x0A` | `Cmd_facer_a` | Reset/remove character portrait |
| `0x0B` | `Cmd_pset_a` | Position character portrait slot |
| `0x0C` | `Cmd_mset_a` | Set message box configuration |
| `0x0D` | `Cmd_enter` | Character enters dialogue scene |
| `0x0E` | `Cmd_exec` | Execute external routine |
| `0x0F` | `Cmd_exit` | Character leaves scene |
| `0x10` | `Cmd_effectB` | Screen visual effect |
| `0x11` | `Cmd_se` | Play sound effect |
| `0x12` | `Cmd_seStop` | Stop sound effect |
| `0x13` | `Cmd_cdplay` | Play CD-DA audio track |
| `0x14` | `Cmd_mspeed` | Set message display typing speed |
| `0x18` | `Cmd_din` | Dialogue In (open dialogue box) |
| `0x19` | `Cmd_dout` | Dialogue Out (close dialogue box) |
| `0x1A` | `Cmd_nin` | News In (display notebook/news mode) |
| `0x1B` | `Cmd_nout` | News Out (exit notebook/news mode) |
| `0x1C` | `Cmd_talk` | Initiate Taiwa (Talk/Inquiry) prompt |
| `0x29` | `Cmd_aurthor` | Script metadata: Author name (followed by 8-byte ASCII) |
| `0x2A` | `Cmd_place` | Set scene location metadata |
| `0x2B` | `Cmd_time` | Set scene timestamp (hour, min) |
| `0x2C` | `Cmd_date` | Set scene date (month, day) |
| `0x2D` | `Cmd_chapter` | Set chapter ID |
| `0x33` | `Cmd_movie` | Play STR video cutscene |
| `0x44` | `Cmd_add` | Arithmetic add |
| `0x45` | `Cmd_subtract` | Arithmetic subtract |
| `0x49` | `Cmd_setVariable` | Set variable value |
| `0x4C` | `Cmd_equal` | Comparison equal (`==`) |
| `0x4D` | `Cmd_notEqual` | Comparison not equal (`!=`) |
| `0x52` | `Cmd_thread` | Spawn concurrent script thread |
| `0x56` | `Cmd_inputName` | Open player name entry screen |
| `0x68` | `Cmd_vibrateMode` | Set vibration mode |
| `0x6C` | `Cmd_chapterTitle` | Display chapter title sequence |
| `0x70` | `Cmd_music` | Play BGM track |
| `0x71` | `Cmd_musiccut` | Stop BGM track |
| `0x7C` | `Cmd_loadkanji` | Load dynamic Kanji font bank TIM into VRAM `(768, 256)` |
| `0x7F` | `Cmd_print_a` | **Print dialogue / message string** |

---

## 5. Text & Dialogue Encoding (`Cmd_print_a`)

The dialogue opcode `0x7F` (`Cmd_print_a`) has the following format:
```
0x7F  <slot_operand_descriptor>  <slot_id>  <stream_of_characters_and_controls>  0x06
```

### Control Codes Inside Dialogue Streams
| Byte | Name | Meaning |
|:---:|:---|:---|
| `0x00` | `[WAIT]` | Pause text, wait for user ○ button confirmation |
| `0x01` | `\n` | Newline |
| `0x04` | `[PAGE]` | Clear text box / page break |
| `0x05` | `[AUTO]` | Automatic timed delay without requiring button press |
| `0x06` | `[END]` | End of `Cmd_print_a` text stream |
| `0x10 - 0x17` | `[BOX:n]` | Change dialogue box style/color (`n = byte - 0x10`) |
| `0x19 <id>` | `[NAME:id]` | Insert player-defined name macro (`0`: protagonist, etc.) |

---

### Character Representation

Text is encoded using a **hybrid single-byte / banked multi-byte scheme**:

#### 1. Standard Single-Byte (ASCII): `0x20` to `0x5F`
- Direct 1:1 mapping with standard ASCII:
  - `0x20`: Space (` `)
  - `0x21 - 0x2F`: Standard ASCII symbols (`! " # $ % & ' ( ) * + , - . /`)
  - `0x30 - 0x39`: Numbers `0` - `9`
  - `0x3F`: `?`
  - `0x41 - 0x5A`: Uppercase Latin letters `A` - `Z` (e.g. `CONFIG`, `OFF`, `DUAL SHOCK` in tutorial)

#### 2. Single-Byte Kana & Punctuation: `0x60` to `0xFF`
- Kana and common Japanese punctuation occupy single-byte codes:
  - `0x5D`: Full stop (`。`)
  - `0x5C`: Comma (`、`)
  - Examples verified from tutorial:
    - `0x75`: ウ
    - `0x78`: お
    - `0x83`: コ
    - `0x85`: サ
    - `0x86`: し
    - `0x88`: す
    - `0x8F`: タ
    - `0x98`: な
    - `0x9A`: に
    - `0xA0`: の
    - `0xA2`: は
    - `0xAC`: ま
    - `0xB1`: ム
    - `0xB5`: モ
    - `0xB6`: や
    - `0xC0`: る
    - `0xC8`: を
    - `0xCB`: ン
    - `0xD5`: ゲ
    - `0xEB`: ド
    - `0xF5`: ボ

#### 3. Banked Kanji: 2-Byte Sequences (`0x1B` .. `0x1F`)
When the decoder encounters bytes `0x1B` through `0x1F`, it treats the next byte `XX` as a 0-indexed lookup into a 256-character Kanji bank matching [`docs/notes/encoding.txt`](file:///home/halkun/reverse/anothermind/anothermind-decomp/docs/notes/encoding.txt):

Each bank contains **16 lines of 16 characters (256 characters per bank)**:
- **Bank `0x1B XX`**: Lines 15 – 30 of `encoding.txt` (Characters `0x1B00` to `0x1BFF`)
  - `1B 00`: 葉
  - `1B 01`: 山
  - `1B 02`: 瞳
  - `1B 03`: 真
  - `1B 04`: 野
  - `1B 05`: 俊
  - `1B 06`: 平
- **Bank `0x1C XX`**: Lines 31 – 46 of `encoding.txt` (Characters `0x1C00` to `0x1CFF`)
- **Bank `0x1D XX`**: Lines 47 – 62 of `encoding.txt` (Characters `0x1D00` to `0x1DFF`)
- **Bank `0x1E XX`**: Lines 63 – 78 of `encoding.txt` (Characters `0x1E00` to `0x1EFF`)
- **Bank `0x1F XX`**: Lines 79 – 94 of `encoding.txt` (Characters `0x1F00` to `0x1FFF`)

#### 4. Dynamic Kanji Banking (`Cmd_loadkanji`)
- The PSX GPU VRAM allocation places standard Kana/ASCII at VRAM `(768, 0)` (`KATAKANA.TIM` / `EISUU.TIM`, 256x256).
- The Kanji texture page sits at VRAM `(768, 256)` (`KANJI.TIM`, 256x256).
- When a scenario transitions to new dialogue vocabulary, the script issues opcode `0x7C` (`Cmd_loadkanji(kanjiSet)`), loading a new Kanji texture tile map into VRAM slot `(768, 256)`.

---

## 6. Translation Implications for English Translation

1. **Space Savings**: English text uses standard ASCII `0x20` – `0x7E`, which takes **1 byte per letter** instead of the 2-byte Kanji sequences (`0x1B XX`). An English script will easily fit inside the original file size boundaries.
2. **Font Layout**: `EISUU.TIM` already contains standard full-width and half-width Latin letters at `(768, 0)`.
3. **Control Code Safety**: Ensure translators preserve control codes (`0x00` [WAIT], `0x01` [\n], `0x04` [PAGE], `0x05` [AUTO], `0x06` [END], `0x10..0x17` [BOX], `0x19` [NAME]).
4. **Relocation Table**: Any modification in string byte length requires recalculating the label offsets in the 16-bit header table (`0x0A + N*2`).

