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
├── scripts/        # Group 05: VM scenario bytecode organized by chapter & subsystem (.ZZS)
├── backgrounds/    # Group 06: Photographic stills organized by chapter & scene (.TIM)
├── animations/     # Group 07: Live-action actor portrait animations organized by scene reel (.ANM)
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
**Target**: `assets/jp/progdata/dictionary/<category>/`  
**Specification**: See [`docs/md_reference/DICTIONARY_SPECIFICATION.md`](file:///home/halkun/reverse/anothermind/anothermind-decomp/docs/md_reference/DICTIONARY_SPECIFICATION.md) for full binary layout, struct definitions, and parser routines.

Natural language dialogue parsing dictionary tables for Another Mind's interactive dialogue input system, organized into 4 subfolders based on physical disc mastering order:

| Subfolder | File Pattern | Count | Description | Examples |
|---|---|---|---|---|
| `common/` | `KATSU.KAT`, `NAME.BBB` | 2 files | Global conjugation tables (`KATSU.KAT`) and character / proper noun database (`NAME.BBB`) | `common/KATSU.KAT`, `common/NAME.BBB` |
| `chapters/` | `JDICT<01-0A>.DCT`, `MDICT<01-0A>.DCT` | 20 files | Vocabulary and grammar dictionaries for Chapters 1 through 10 | `chapters/JDICT01.DCT`, `chapters/MDICT01.DCT` |
| `branches/` | `JDICTB<1-7>.DCT`, `MDICTB<1-7>.DCT` | 14 files | Vocabulary and grammar dictionaries for Branch scenarios 1 through 7 | `branches/JDICTB1.DCT`, `branches/MDICTB1.DCT` |
| `demo/` | `JDICTTD.DCT`, `MDICTTD.DCT`, `JDICT06B.DCT`, `MDICT06B.DCT` | 4 files | Interactive demo / tutorial dictionaries and Chapter 6 alternate route | `demo/JDICTTD.DCT`, `demo/JDICT06B.DCT` |

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

Virtual machine bytecode controlling cutscenes, dialogue branches, and scenario state. Following the physical mastering order on disc, scripts are organized into chapter and system directories:

#### Chapter Directory Organization

| Directory | Script Count | Content & Naming Patterns |
|---|---|---|
| `common/` | 13 files | Flow control & system routines: `DEFAULT.ZZS`, `TUTOS.ZZS`, `TUTOD.ZZS`, `FTALK1.ZZS`–`FTALK8.ZZS`, `MENUSAVE.ZZS` |
| `chapter_01/` | 25 files | Chapter 1 master (`CHAPTER1.ZZS`), intermission (`BREAK1.ZZS`), main story dialogue (`DIA0101`–`DIA0118`), Branch 1 (`DIAB101`–`DIAB105`) |
| `chapter_02/` | 44 files | Chapter 2 master (`CHAPTER2.ZZS`), intermission (`BREAK2.ZZS`), main story dialogue (`DIA0201`–`DIA0240`), Branch 2 (`DIAB201`–`DIAB202`) |
| `chapter_03/` | 45 files | Chapter 3 master (`CHAPTER3.ZZS`), intermission (`BREAK3.ZZS`), main story dialogue (`DIA0301`–`DIA0340`), Branch 3 (`DIAB300`–`DIAB302`) |
| `chapter_04/` | 16 files | Chapter 4 master (`CHAPTER4.ZZS`), intermission (`BREAK4.ZZS`), main story dialogue (`DIA0400`–`DIA0410`), Branch 4 (`DIAB400`–`DIAB402`) |
| `chapter_05/` | 43 files | Chapter 5 master (`CHAPTER5.ZZS`), intermission (`BREAK5.ZZS`), main story dialogue (`DIA0501`–`DIA0531`), Branch 5 (`DIAB501`–`DIAB510`) |
| `chapter_06/` | 62 files | Chapter 6 master (`CHAPTER6.ZZS`), intermission (`BREAK6.ZZS`), main story dialogue (`DIA0601`–`DIA0650`), Branch 6 (`DIAB601`–`DIAB610`) |
| `chapter_07/` | 26 files | Chapter 7 master (`CHAPTER7.ZZS`), intermission (`BREAK7.ZZS`), main story dialogue (`DIA0701`–`DIA0724`) |
| `chapter_08/` | 19 files | Chapter 8 master (`CHAPTER8.ZZS`), intermission (`BREAK8.ZZS`), main story dialogue (`DIA0801`–`DIA0817`) |
| `chapter_09/` | 7 files | Chapter 9 master (`CHAPTER9.ZZS`), intermission (`BREAK9.ZZS`), main story dialogue (`DIA0901`–`DIA0905`) |
| `chapter_10/` | 2 files | Chapter 10 master (`CHAPTERA.ZZS`), intermission (`BREAKA.ZZS`) |
| `chapter_11/` | 1 file | Chapter 11 master controller (`CHAPTERB.ZZS`) |
| `chapter_12/` | 1 file | Chapter 12 master controller (`CHAPTERC.ZZS`) |
| `chapter_13/` | 1 file | Epilogue / Credits master controller (`CHAPTERD.ZZS`) |
| `demo/` | 5 files | Attract mode / interactive demo dialogue scripts (`DIADM01.ZZS`–`DIADM05.ZZS`) |
| `omake/` | 5 files | Post-game bonus content and character omake: `OMAKE1.ZZS`, `OMAKE2.ZZS`, `HITOMI.ZZS`, `MUKAI.ZZS`, `CHAPT.ZZS` |
| `debug/` | 28 files | Developer scratch and test routines: `BUCHI1`–`5`, `DRAGON1`–`5`, `MINORI1`–`4`, `FUJII`, `KURI`, `KOKU`, `HAYASHI`, `MUTO`, `TTEST`, `DEMO` |

#### Script Filename Conventions
- `CHAPTER<1-D>.ZZS`: Primary chapter entry-point controllers (`CHAPTERA` = Chapter 10, `B` = 11, `C` = 12, `D` = 13).
- `BREAK<1-A>.ZZS`: Chapter break / intermission save point scripts.
- `DIA<Chap><Scene>.ZZS`: Scene dialogue script bytecode (`DIA0101`–`DIA0905`).
- `DIAB<Branch><Scene>.ZZS`: Branching scenario dialogue scripts (`DIAB101`–`DIAB610`).
- `DIADM<N>.ZZS`: Demo mode dialogue scripts.
- `FTALK<N>.ZZS`: Free-talk / Taiwa conversation subsystem routines.

---

### Group 06: `backgrounds` (1,219 files)
**Target**: `assets/jp/progdata/backgrounds/<chapter>/<image>.TIM`

High-resolution digitized photographic stills (all standard 320×160 16-bit PSX TIMs).

#### Chapter Directory Organization

| Subfolder | File Count | Description & Naming Patterns |
|---|---|---|
| `chapter_00_common/` | 200 files | True shared assets, organized into 4 functional subfolders:<br>• `faces/` (66 files): Face-bust dialogue portraits (`KAO0001`–`0066`, 顔 = Face)<br>• `cutins/` (24 files): Dramatic action reaction cut-ins (`RRR0001`–`0025`)<br>• `ending/` (70 files): End-game credits and staff roll stills (`MEE0001`–`09`, `R0000`–`48`, `INPO00`–`15`)<br>• `system/` (40 files): Title, UI, and test cards (`BLACK`, `WHITE`, `TITLELOG`, `MS01`–`MS08`, `G_OVER01`, `BUG`, `TEST_*`, `TUTO01`–`02`) |
| `chapter_01/` | 49 files | Scene number `1xxx` and opening stills: `ADD1001`, `B1003_1`–`3`, `DEN1014`, `KAI1015`–`16`, `KAN1001`, `KEI1002`, `KEN1009`, `MON1024`, `NUR1012`, `REI1009`–`21`, `ROW0001`–`02`, `M01_04`, `M01_09` |
| `chapter_02/` | 164 files | Scene number `2xxx` and school/hospital stills: `ADD2000`–`03`, `BUN2084`–`85`, `COP2086`–`87`, `EX2000B`–`K`, `KIT2038`, `MA2002`, `MI2005`, `TA2049_1`–`3`, `TA20492B`–`F`, `YAI0001`–`09`, `M02_02`, `M02_11` |
| `chapter_03/` | 125 files | Scene number `3xxx`: `BUS3010`, `BUS3012`, `EKI3001`–`05`, `GIN3001`–`02`, `HIR3003`, `KAI3002`, `RYO3020`, `M03_04`, `M03_05`, `M03_09` |
| `chapter_04/` | 213 files | Scene number `4xxx` and investigation stills, with sequential scene subfolders:<br>• `tui/` (40 files): High-speed pursuit / highway chase sequence (`TUI0001`–`05`, `KKK0000`–`34`)<br>• `scene_02/` (57 files): Chapter 4 Scene 2 series (`M4S2_01`–`57`)<br>• Root `chapter_04/` (116 files): Town & investigation stills (`ARA4001`–`4112`, `HIT4002`, `HO4024`, `EX4000`–`4210`, `JIN4001`) |
| `chapter_05/` | 68 files | Scene number `5xxx`: `ASA5016`, `HIR5001`, `KAI5002`, `KOU5001`, `YOL5020`, `M05_02`, `M05_04` |
| `chapter_06/` | 124 files | Chapter 6 confrontation & pursuit stills, with scene subfolders:<br>• `jet/` (50 files): Jet / high-speed vehicle action cut-ins (`JET0000`–`49`)<br>• `brain/` (15 files): Psychic link / thought cut-ins (`BRA0001`–`16`)<br>• Root `chapter_06/` (59 files): Scenario stills (`TUE0001`–`22`, `TUH0001`–`07`, `TUM`, `TUY`, `RIN`, `HNE`, `POK0001`–`04`) |
| `chapter_07/` | 52 files | Scene number `7xxx`: `AIS7046`, `ARI7001`, `HIL7020`, `JIN7001`, `KOB7001`, `TAT7001` |
| `chapter_08/` | 83 files | Scene number `8xxx`: `ADD8000`–`20`, `CHI8020`, `KAI8028`, `KOG8002`, `LIV8031`, `SAA0001`, `M08_02`, `M08_05` |
| `chapter_09/` | 101 files | Scene number `9xxx`: `ABL9026`, `ADD9000`, `BAC9020`, `KAI9001`, `KIR0001`, `NAT0001`–`08`, `RCO0001`–`03`, `M09_05`, `M09_06` |
| `chapter_10/` | 23 files | Scene number `10xxx`: `AL10010`, `DEN10014`–`15`, `KI10016`–`20`, `MIC10021`–`23`, `RI10012`, `M10_02`, `M10_12` |
| `chapter_11/` | 9 files | Scene number `11xxx` and office/club stills: `ATU11001`, `OFI11002`, `SHI11003`, `HAI11004`, `BOO0001`–`04`, `BIL0001` |
| `chapter_12/` | 8 files | Scene number `12xxx` and epilogue stills: `NAT12001`–`03`, `TAB12004`, `ROW12005`, `MET12006`, `NBI0001`–`02` |

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
**Target**: `assets/jp/progdata/animations/<scene>/<character>/<animation>.ANM`

Portrait facial animations and emotional expressions of the live-action cast. Following the physical mastering order on disc, animations are organized into 16 scene reels with character subfolders inside each scene:

#### Scene Directory Organization

| Scene Directory | Anchor / Lead | Characters Present in Scene | File Count |
|---|---|---|---|
| `common/` | Static effect assets | `NULL.TIM`, `NOISE.ANM` | 2 files |
| `scene_002/` | Hitomi (`H002`) | `hitomi/`, `rk/` | 31 files |
| `scene_017/` | Hitomi (`H017`) | `hitomi/`, `masato/`, `kazuo/`, `kurata/`, `hiura/`, `kan/`, `ke/`, `p/`, `u/` | 49 files |
| `scene_018/` | Hitomi (`H018`) | `hitomi/` | 30 files |
| `scene_019/` | Masato (`M019`) | `masato/`, `mayumi/`, `nurse/`, `yoshida/`, `kaneko/`, `hitoshi/`, `kitani/`, `b/`, `nn/`, `sk/` | 116 files |
| `scene_029/` | Hitomi (`H029`) | `hitomi/` | 3 files |
| `scene_039/` | Hitomi (`H039`) | `hitomi/` | 20 files |
| `scene_042/` | Hitomi (`H042`) | `hitomi/` | 28 files |
| `scene_043/` | Masato (`M043`) | `masato/`, `shun/`, `nanami/`, `mayumi/`, `nurse/`, `shimada/`, `okada/`, `ju/`, `nj/`, `os/` | 119 files |
| `scene_044/` | Masato (`M044`) | `masato/`, `nanami/`, `shun/` | 65 files |
| `scene_046/` | Masato (`M046`) | `masato/`, `arai/` | 41 files |
| `scene_068/` | Hitomi (`H068`) | `hitomi/`, `akane/`, `bn/`, `kg/`, `st/` | 28 files |
| `scene_085/` | Hitomi (`H085`) | `hitomi/` | 6 files |
| `scene_086/` | Hitomi (`H086`) | `hitomi/`, `ritsuko/`, `reiko/`, `sahara/`, `hiura/`, `mukai/`, `bri/`, `is/`, `kazuo/`, `ry/`, `yk/` | 108 files |
| `scene_115/` | Hitomi (`H115`) | `hitomi/`, `kurata/`, `kiba/`, `bl/`, `ca/`, `kg/`, `sue/`, `wa/` | 56 files |
| `scene_130/` | Hitomi (`H130`) | `hitomi/` | 46 files |
| `scene_173_night/` | Hitomi Night (`HN173`) | `hitomi/` | 64 files |


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
