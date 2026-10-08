# Another Mind - Asset Filename Conventions & Directory Layout

This document details the naming conventions, compression types, and organizational structure of all game assets extracted from the PlayStation release of **Another Mind** (Square, 1998, SLPS-01655).

All extracted assets reside in `assets/jp/progdata/` and correspond directly to the disc directory structure indexed by `CDPOS.DAT`.

---

## 1. File Compression & Extensions

The game files on disc use proprietary Squaresoft LZSS compression (identified by the magic byte header `0xC3 0xFF [4-byte uncompressed size]`). The asset pipeline decompresses them during `make assets` using the following file extension mappings:

| Disc Extension | Extracted Extension | Description | Format Details |
|---|---|---|---|
| `.STR` | `.STR` | PlayStation CD-XA FMV video streams | Uncompressed Mode 2 Form 2 XA audio/video stream |
| `.TIZ` | `.TIM` | LZSS-compressed PlayStation TIM images | Standard PSX TIM (4-bit, 8-bit paletted, or 16-bit direct color) |
| `.ANZ` | `.ANM` | LZSS-compressed facial portrait animation sequences | Custom Squaresoft multi-frame portrait animation |
| `.ZZZ` | `.ZZS` | LZSS-compressed scenario bytecode scripts | Another Mind virtual machine bytecode |
| `.BIZ` | `.BIN` | LZSS-compressed binary menu/scenario data | Binary data structures and schedule tables |
| `.DCT` | `.DCT` | Uncompressed dictionary / vocabulary tables | Text-input Japanese dialogue parsing tables |
| `.KAT` | `.KAT` | Uncompressed grammatical conjugation table | Japanese verb/adjective conjugation (活用, Katsuyou) |
| `.DAT` | `.DAT` | Uncompressed audio / SPU soundbank data | SPU ADPCM samples and sound effect collections |
| `.SNG` | `.SNG` | Uncompressed music sequence track data | Sequence data for the SPU sound engine |
| `.VIB` | `.VIB` | Uncompressed vibration motor data | DualShock controller vibration track synchronized to FMV |

---

## 2. Directory Layout & Naming Conventions

Game assets are grouped into 10 functional categories defined by boundary offsets in the executable (`D_8004B440`):

```
assets/jp/progdata/
├── video/          # Group 00: FMV video cutscenes (.STR)
├── system/         # Group 01: Core UI, fonts, title cards, vibration (.TIM, .VIB, .BIN)
├── dictionary/     # Group 02: Dialogue parsing dictionaries (.DCT, .KAT, .BBB)
├── dialogue/       # Group 03: Dialogue boxes, fonts, chapter banners (.TIM)
├── menus/          # Group 04: Subsystem UI, newspapers, schedule data (.TIM, .BIN)
├── scripts/        # Group 05: VM scenario bytecode organized by author (.ZZS)
├── backgrounds/    # Group 06: Photographic stills organized by chapter (.TIM)
├── animations/     # Group 07: Live-action actor portrait animations (.ANM)
├── audio/          # Group 08: SPU sound effects, music, and wave banks (.DAT, .SNG)
└── dummy/          # Group 09: Outer-edge disc padding (.BIN)
```

---

### Group 00: `video` (66 files)
**Target**: `assets/jp/progdata/video/*.STR`

Full-motion video (FMV) sequences recorded using real-world live-action footage:

| Pattern | Meaning | Examples |
|---|---|---|
| `DEMO0.STR` | Attract / opening demonstration movie | `DEMO0.STR` |
| `KARI.STR` | Placeholder / temporary test stream (*kari* = 仮 / provisional in Japanese) | `KARI.STR` |
| `M<Chap>_<Scene>.STR` | Main story movie cutscene: Chapter (`01`–`10`) and Scene number | `M01_01.STR`, `M02_08.STR`, `M10_14.STR` |
| `B<Chap>_<Scene>.STR` | Branching / alternate scenario movies (e.g. Chapter 3, 4, 6) | `B03_01.STR`, `B04_01.STR`, `B06_01.STR` |
| `M<Chap>_FB.STR` | Flashback movie sequence | `M08_FB.STR`, `M09_FB.STR` |

---

### Group 01: `system` (61 files)
**Target**: `assets/jp/progdata/system/`

Core system presentation, typography, and hardware control:

| Pattern | Meaning | Examples |
|---|---|---|
| `CHAP<N>_F.TIM` | Chapter title card Japanese text (*F* = Font / Japanese subtitle) | `CHAP1_F.TIM` through `CHAP9_F.TIM` |
| `CHAP<N>_G.TIM` | Chapter title card graphical title (*G* = Graphic / English banner) | `CHAP1_G.TIM` through `CHAP9_G.TIM` |
| `M<Chap>_<Scene>.VIB` | DualShock vibration motor keyframe track synced to the matching movie cutscene | `M01_04.VIB`, `M04_01.VIB`, `M08_05.VIB` |
| `B06_01.VIB`, `DEFAULT.VIB` | Branch and default vibration tracks | `B06_01.VIB`, `DEFAULT.VIB` |
| `TITLE*.TIM` | Title screen backdrops and layered menus | `TITLE.TIM`, `TITLE2.TIM`, `TITLE3.TIM`, `TITLEO.TIM` |
| `TANM<0-A>.TIM`, `TANMLOGO.TIM` | Title screen animated logo sequence (*T-ANM*) | `TANM0.TIM`–`TANMA.TIM`, `TANMLOGO.TIM` |
| `BG_HITO.TIM`, `BG_MANO.TIM` | Protagonist system backdrops (*Hito* = 人, *Mano* = 真野 Hitomi Mano) | `BG_HITO.TIM`, `BG_MANO.TIM` |
| `KANJI.TIM`, `KATAKANA.TIM`, `EISUU.TIM`, `NAMEFONT.TIM` | System typography bitmaps (Kanji, Katakana, Alphanumerics, Name Entry) | `KANJI.TIM`, `EISUU.TIM`, `NAMEFONT.TIM` |
| `TCURSOL.TIM` | Title cursor graphic | `TCURSOL.TIM` |
| `SQUARE.TIM` | Squaresoft startup company logo | `SQUARE.TIM` |
| `FEPLIST.BIN` | Front-End Processor (FEP) Japanese text conversion candidate lookup table | `FEPLIST.BIN` |
| `LIST2.TXT` | Internal asset directory manifest file | `LIST2.TXT` |

---

### Group 02: `dictionary` (40 files)
**Target**: `assets/jp/progdata/dictionary/`

Natural language dialogue parsing dictionary tables for Another Mind's interactive dialogue input system:

| Pattern | Meaning | Examples |
|---|---|---|
| `JDICT<XX>.DCT` | Japanese vocabulary dictionary for dialogue parser: `01`–`0A` = Chapters 1–10; `B1`–`B7` = Branch paths; `TD` = Tutorial / Demo | `JDICT01.DCT`, `JDICT0A.DCT`, `JDICTB1.DCT`, `JDICTTD.DCT` |
| `MDICT<XX>.DCT` | Morphological / grammar dictionary paired with each `JDICT` table | `MDICT01.DCT`, `MDICT0A.DCT`, `MDICTB1.DCT`, `MDICTTD.DCT` |
| `KATSU.KAT` | Grammatical inflection / conjugation rules table (*Katsuyou* = 活用) | `KATSU.KAT` |
| `NAME.BBB` | Proper noun and character name recognition database | `NAME.BBB` |

---

### Group 03: `dialogue` (53 files)
**Target**: `assets/jp/progdata/dialogue/`

Dialogue interface chrome, message boxes, and narrative typography:

| Pattern | Meaning | Examples |
|---|---|---|
| `MESCON<XX>.TIM` | Message Control window chrome per chapter: `01`–`0A`, branches `B1`–`B9`, `TD` | `MESCON01.TIM`, `MESCONB1.TIM`, `MESCONTD.TIM` |
| `KABE<NN>.TIM` | Message box backdrop textures (*Kabe* = 壁 / panel frame) | `KABE01.TIM` through `KABE09.TIM` |
| `BRE<NN>.TIM` | Brain Effect animation / thought ripple frames | `BRE01.TIM` through `BRE06.TIM` |
| `BRAIN01.TIM` | Brain / psychic link monitor visual | `BRAIN01.TIM` |
| `SYO_<NN>.TIM`, `SYO_END.TIM` | Chapter title banners displayed during scenario transitions (*Shousetsu* = 章 / chapter) | `SYO_01.TIM` through `SYO_09.TIM`, `SYO_END.TIM` |
| `FONT.TIM`, `FONT0.TIM`, `FONT2.TIM` | In-game narrative dialogue fonts | `FONT.TIM`, `FONT0.TIM`, `FONT2.TIM` |
| `NAME.TIM`, `MESMENU.TIM`, `MESNEWS.TIM` | Speaker nameplate frame, dialogue menu chrome, and news viewer frame | `NAME.TIM`, `MESMENU.TIM`, `MESNEWS.TIM` |

---

### Group 04: `menus` (239 files)
**Target**: `assets/jp/progdata/menus/<category>/`

Game sub-screens, investigation notebook dossiers, newspapers, and memory card management organized into 6 functional subfolders:

| Subfolder | File Pattern | Count | Description | Examples |
|---|---|---|---|---|
| `credits/` | `SROLL<NN>.TIM` | 56 files | Staff credit roll and investigation summary scroll graphics | `SROLL00.TIM` through `SROLL55.TIM` |
| `investigation/` | `M_CHR*.TIM`, `M_MAP*.TIM`, `M_SCRAP.BIN`, `CLIP.TIM`, `TAG.TIM`, `M_*.BIN` | 20 files | Character profile dossiers, crime scene maps, clipboard UI, and menu engine binaries | `M_CHR1.TIM`–`M_CHR8.TIM`, `M_MAP1.TIM`–`M_MAP4.TIM`, `CLIP.TIM` |
| `memory_card/` | `MB_<ACTION>.TIM` | 29 files | Memory Card save / load interface chrome (*Memory Box*) | `MB_ADRS.TIM`, `MB_ICON.TIM`, `MB_LOAD.TIM`, `MB_SAVE.TIM` |
| `news/` | `NEWS<NN>.TIM`, `D<Chap>N<Scene>.TIM` | 112 files | In-game newspaper clippings, headlines, and daily case evidence | `NEWS00.TIM`–`NEWS53.TIM`, `D00N00.TIM`–`D12N08.TIM` |
| `schedule/` | `WEEK<NN>.BIN`, `SYODATA.BIN` | 17 files | Scenario investigation calendar and chapter sequence tables | `WEEK00.BIN` through `WEEK15.BIN`, `SYODATA.BIN` |
| `terminal/` | `T_<GADGET>.TIM`, `RING.TIM` | 5 files | Telephone / pager communication interface and gadgets | `T_DEN01.TIM` (電話), `T_KUMA.TIM`, `T_RAZI.TIM`, `RING.TIM` |

---

### Group 05: `scripts` (343 files)
**Target**: `assets/jp/progdata/scripts/<author>/<script>.ZZS`

Virtual machine bytecode controlling cutscenes, dialogue branches, and scenario state.

#### Author Directory Organization
The script compiler embedded an author attribution header starting with opcode `0x29` followed by an 8-byte ASCII username. The extractor routes each script into its author's directory:

| Author Directory | Script Count | Prominent Content |
|---|---|---|
| `fujii/` | 99 files | Main scenario branches, Chapter 6, investigation sequences |
| `Iwabuchi/` | 84 files | Chapter 1, Chapter 7, Chapter 8, character events |
| `dragon/` | 75 files | Chapter 2, Chapter 5, high-tension branch scenarios |
| `okkey/` | 18 files | Sub-scenarios, event mini-games |
| `Kurihara/` | 13 files | Branch routes, ending variations |
| `muhuhu/` | 11 files | Scenario events, character sub-plots |
| `koku/` | 8 files | Chapter 3, Chapter 9, Chapter 10 (*CHAPTERA*) |
| `yoshi/` | 7 files | `DEFAULT.ZZS`, system scripts, flow control |
| `kabira/` | 4 files | Chapter 4 scenarios |
| `mminori/` | 4 files | Scenario sequences |
| `take/` | 3 files | Scenario sequences |
| `minori/` | 2 files | Scenario sequences |
| `kiyo/` | 1 file | Scenario sequence |
| `mutoh/` | 1 file | Scenario sequence |
| `testyosh/` | 1 file | Engine test script |
| `buchi/` | 1 file | Alternate handle for Iwabuchi |
| `Fujii/` | 1 file | Capitalized handle for Fujii |
| `scripts/` (root) | 10 files | Global/common scripts without an author header (`KABIRA.ZZS`, `HAYASHI.ZZS`, etc.) |

#### Script Filename Conventions
- `CHAPTER<1-A>.ZZS`: Primary chapter entry-point scripts (`CHAPTERA` = Chapter 10).
- `S<Chap>_<Sec>.ZZS`: Scene / section scripts within chapters (e.g. `S1_01.ZZS`, `S2_04.ZZS`).
- `<NAME>.ZZS`: Character-focused or author-named scenarios (`HAYASHI.ZZS`, `KURI.ZZS`, `UCHI.ZZS`).
- `DEBUG.ZZS`, `TEST.ZZS`, `DEFAULT.ZZS`: Developer test routines and fallback loops.

---

### Group 06: `backgrounds` (1,219 files)
**Target**: `assets/jp/progdata/backgrounds/<chapter>/<image>.TIM`

High-resolution digitized photographic stills (all standard 320×160 16-bit PSX TIMs).

#### Chapter Directory Organization

| Subfolder | File Count | Description & Naming Patterns |
|---|---|---|
| `chapter_00_common/` | 394 files | Face bust shots (`KAO0001`–`0066`, 顔 = Face), cut-in action stills (`JET0001`–`0050`, `KKK0001`–`0035`, `RRR0001`–`0024`), non-numeric title & system stills (`TITLELOG`, `BLACK`, `WHITE`, `BUG`, `CUTIN`, `DOWNTOWN`, `H_GAKKO`, `H_HAWAI`, `H_PARK`, `H_RASSEN`, `INPOxx`) |
| `chapter_01/` | 47 files | Scene number `1xxx`: `ADD1001`, `B1003_1`–`3`, `DEN1014`, `KAI1015`–`16`, `KAN1001`, `KEI1002`, `KEN1009`, `MON1024`, `NUR1012`, `REI1009`–`21`, `M01_04`, `M01_09` |
| `chapter_02/` | 155 files | Scene number `2xxx`: `ADD2000`–`03`, `BUN2084`–`85`, `COP2086`–`87`, `EX2000B`–`K`, `KIT2038`, `MA2002`, `MI2005`, `TA2049_1`–`3`, `TA20492B`–`F`, `M02_02`, `M02_11` |
| `chapter_03/` | 125 files | Scene number `3xxx`: `BUS3010`, `BUS3012`, `EKI3001`–`05`, `GIN3001`–`02`, `HIR3003`, `KAI3002`, `RYO3020`, `M03_04`, `M03_05`, `M03_09` |
| `chapter_04/` | 176 files | Scene number `4xxx`: `ARA4001`, `AKU4079`, `EX4201`–`09`, `JIN4001`, `M4S2_01`–`57` (Chapter 4 Scene 2 series), `S4_MIR01`–`03` (Scene 4 Mirror) |
| `chapter_05/` | 68 files | Scene number `5xxx`: `ASA5016`, `HIR5001`, `KAI5002`, `KOU5001`, `YOL5020`, `M05_02`, `M05_04` |
| `chapter_07/` | 52 files | Scene number `7xxx`: `AIS7046`, `ARI7001`, `HIL7020`, `JIN7001`, `KOB7001`, `TAT7001` |
| `chapter_08/` | 81 files | Scene number `8xxx`: `ADD8000`–`20`, `CHI8020`, `KAI8028`, `KOG8002`, `LIV8031`, `M08_02`, `M08_05` |
| `chapter_09/` | 88 files | Scene number `9xxx`: `ABL9026`, `ADD9000`, `BAC9020`, `KAI9001`, `M09_05`, `M09_06` |
| `chapter_10/` | 23 files | Scene number `10xxx`: `AL10010`, `DEN10014`–`15`, `KI10016`–`20`, `MIC10021`–`23`, `RI10012`, `M10_02`, `M10_12` |
| `chapter_11/` | 4 files | Scene number `11xxx`: `ATU11001`, `OFI11002`, `SHI11003`, `HAI11004` |
| `chapter_12/` | 6 files | Scene number `12xxx`: `NAT12001`–`03`, `TAB12004`, `ROW12005`, `MET12006` |

#### Location / Subject Prefixes
The 2–4 letter prefix before the scene number designates the setting or subject:
- `EKI` = Station (駅)
- `GIN` = Bank (銀行)
- `KAI` = Stairs / Hallway (階段 / 会議)
- `DEN` = Phone / Utility (電話 / 電柱)
- `MON` = Gate / Entrance (門)
- `LIV` = Living room
- `BUS` = Bus / Transit
- `ARA` / `ASA` / `AIS` = Neighborhood or street names

---

### Group 07: `animations` (811 files)
**Target**: `assets/jp/progdata/animations/<character>/<animation>.ANM`

Portrait facial animations and emotional expressions of the live-action cast, organized into subfolders named by each character:

#### Character Subdirectory Organization

| Subfolder | Cast Member / Character | File Count |
|---|---|---|
| `hitomi/` | Hitomi Mano (真野 ひろみ - Protagonist) | 232 files |
| `masato/` | Nanami Masato / Male Lead | 117 files |
| `hitomi_night/` | Hitomi (Night attire / alternate outfit) | 64 files |
| `mayumi/` | Mayumi (including `R_MY` reflection takes) | 41 files |
| `shun/` | Shun / Secondary character | 33 files |
| `nurse/` | Nurse (村井 薫 - Murai Kaoru) | 27 files |
| `nanami/` | Nanami (鳴海 健一 - Narumi Kenichi) | 26 files |
| `kurata/` | Kurata (桐原 育夫 - Kirihara Ikuo) | 21 files |
| `ritsuko/` | Ritsuko (渡瀬 鈴 - Watase Rin) | 20 files |
| `reiko/` | Reiko (渡瀬 玲 / 亜月 レイカ) | 17 files |
| `arai/` | Arai (青西 高嗣 / 荒井) | 14 files |
| `akane/` | Akane (阿久津 安弘 - Akutsu Yasuhiro) | 13 files |
| `kaneko/` | Kaneko (金田 俊樹 - Kaneda Toshiki) | 13 files |
| `hitoshi/` | Hitoshi | 12 files |
| `kitani/` | Kitani | 12 files |
| `yoshida/` | Yoshida | 12 files |
| `shimada/` | Shimada | 10 files |
| `sahara/`, `kiba/`, `mukai/`, `hiura/`, `okada/`, `kazuo/`, `bri/`, `nj/`, `kg/`, `nn/`, `rk/`, `ry/`, `st/`, `ju/`, `os/`, `bl/`, `kan/`, `sk/`, `u/`, `yk/`, `b/`, `bn/`, `ca/`, `is/`, `p/`, `sue/`, `wa/`, `ke/` | Supporting cast and extras (28 folders) | 136 files |
| `common/` | Static effect assets (`NOISE.ANM`, `NULL.TIM`) | 2 files |

#### Emotion & Variation Suffixes
Following the character code and shot index, letters denote specific emotional states:
- `I`: Ikari (怒り - Anger / annoyance)
- `N`: Normal / Nakigao (泣き顔 / 平常 - Neutral or tearful expression)
- `D`: Doki (驚き / 動悸 - Shock / surprise / heartbeat reaction)
- `C`: Choushoku / Smile (笑顔 / 微笑み - Smiling / friendly)
- `A`, `B`: Animation take or alternative loop variant

---

### Group 08: `audio` (287 files)
**Target**: `assets/jp/progdata/audio/`

SPU sound effects, background music, and audio wave banks:

| Pattern | Count | Meaning | Examples |
|---|---|---|---|
| `EFFECT<NN>.DAT` | 18 files | SPU sound effect collections / soundbanks | `EFFECT00.DAT`, `EFFECT02.DAT`, `EFFECT62.DAT` |
| `MUSIC<NN>.DAT` | 51 files | Background music sequence data and instrument assignments | `MUSIC01.DAT` through `MUSIC51.DAT` |
| `SONG<NN>.SNG` | 7 files | Music sequence playback tracks | `SONG01.SNG` through `SONG07.SNG` |
| `WAVE<NNNN>.DAT` | 210 files | Raw SPU VAG ADPCM audio sample banks | `WAVE0001.DAT` through `WAVE0210.DAT` |

---

### Group 09: `dummy` (1 file)
**Target**: `assets/jp/progdata/dummy/`

| Filename | Sector (LBA) | Description |
|---|---|---|
| `DUMMY.BIN` | 243934 | Disc dummy file (13.5 MB) intentionally placed at the physical outer edge of the CD-ROM to push readable data towards the inner tracks, improving read speed and laser seek stability on PlayStation hardware. |
