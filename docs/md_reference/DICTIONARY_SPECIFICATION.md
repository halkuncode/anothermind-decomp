# Another Mind (PSX) - Dictionary & Dialogue Parser Specification (.DCT, .BBB, .KAT)

## 1. Overview

In Squaresoft's *Another Mind* (1998, PSX), the player interacts with protagonist Nanami through the **Taiwa (対話) natural-language dialogue engine**. Rather than selecting simple branching options, the player types or selects Japanese words and phrases to ask questions, offer advice, or prompt reactions.

All files in `assets/jp/progdata/dictionary/` (Group 02, 40 files) drive this NLP (Natural Language Processing) subsystem, organized into 4 subfolders matching physical disc mastering layout:

| Subfolder | File Count | Purpose | Engine Loader Routine |
|---|---|---|---|
| **`common/`** | 2 files (`KATSU.KAT`, `NAME.BBB`) | Global conjugation tables and character name database | `LoadPortraitTextGridData` / `LoadPortraitLoopCutData` |
| **`chapters/`** | 20 files (`JDICT01`–`0A`, `MDICT01`–`0A`) | Chapter 1 through 10 dialogue dictionaries | `LoadDictionaryData($a0=0/1)` |
| **`branches/`** | 14 files (`JDICTB1`–`B7`, `MDICTB1`–`B7`) | Branch route dialogue dictionaries | `LoadDictionaryData($a0=0/1)` |
| **`demo/`** | 4 files (`JDICTTD`/`MDICTTD`, `JDICT06B`/`MDICT06B`) | Tutorial/demo and Chapter 6 alternate dictionaries | `LoadDictionaryData($a0=0/1)` |

All strings in these files use Another Mind's custom 1-byte / 2-byte Kanji character encoding (banks `0x1B`–`0x1F`), fully documented in [`docs/notes/encoding.txt`](file:///home/halkun/reverse/anothermind/anothermind-decomp/docs/notes/encoding.txt).

---

## 2. `.DCT` File Format (Dictionary Tables)

The game script interpreter invokes `Cmd_loaddict` (opcode `0x19` in [`src/main/script.c`](file:///home/halkun/reverse/anothermind/anothermind-decomp/src/main/script.c)) whenever a scenario or chapter changes. `Cmd_loaddict` takes two operands:
* **`Slot`**: `0` for `JDICT`, `1` for `MDICT`
* **`FileID`**: The file index within Group 02 (e.g. `FileID 2` = `chapters/JDICT01.DCT`, `FileID 3` = `chapters/MDICT01.DCT`)

`Cmd_loaddict` calls `LoadDictionaryData` in [`asm/jp/nonmatchings/main/script/LoadDictionaryData.s`](file:///home/halkun/reverse/anothermind/anothermind-decomp/asm/jp/nonmatchings/main/script/LoadDictionaryData.s).

```
Group 02 Dictionary File IDs:
  File 000: common/KATSU.KAT
  File 001: common/NAME.BBB
  File 002: chapters/JDICT01.DCT    File 003: chapters/MDICT01.DCT
  File 004: chapters/JDICT02.DCT    File 005: chapters/MDICT02.DCT
  ...
  File 020: chapters/JDICT0A.DCT    File 021: chapters/MDICT0A.DCT  (Chapter 10)
  File 022: branches/JDICTB1.DCT    File 023: branches/MDICTB1.DCT  (Branch routes 1–7)
  File 036: demo/JDICTTD.DCT        File 037: demo/MDICTTD.DCT      (Tutorial / Demo)
  File 038: demo/JDICT06B.DCT       File 039: demo/MDICT06B.DCT     (Chapter 6 Alternate)
```

---

### A. `JDICT<XX>.DCT` (Type 0: Vocabulary & Semantic Dictionary)

`JDICT` stores the legal vocabulary recognized in that chapter, together with grammatical part of speech and semantic topic IDs that trigger specific conversational responses in the script VM.

#### Binary Stream Layout

A `JDICT` file consists of a continuous stream of variable-length word records, terminated by a 16-bit big-endian `0x0000` EOF marker:

```
+---------------------------------------------------------------------------------------------------+
| Field                     | Size (Bytes)    | Description                                         |
+---------------------------+-----------------+-----------------------------------------------------+
| Word ID                   | 2 (Big Endian)  | 1-based Record / Word index (0x0000 = EOF)          |
| Word String               | Variable + 1    | Null-terminated word string (1-byte / 2-byte Kanji) |
| Part of Speech (POS)      | 1               | Grammatical classification byte (Noun, Verb, etc.)  |
| Group 0 Semantic Tags     | Stream + 2      | Pairs of (uint16_be TagID, uint8_t Weight) + 0x0000 |
| Group 0 Flag              | 1               | Offset 0x4E attribute flag                          |
| Group 1 Semantic Tags     | Stream + 2      | Pairs of (uint16_be TagID, uint8_t Weight) + 0x0000 |
| Group 1 Flag              | 1               | Offset 0x4F attribute flag                          |
| Extended Tail Attributes  | 3               | Flags written to struct offsets 0x50, 0x51, 0x52    |
+---------------------------------------------------------------------------------------------------+
```

#### Parsing Loop in `LoadDictionaryData`:
1. Read `uint16_be WordID`. If `WordID == 0`, exit loop (EOF).
2. Read characters into `entry->word_str` until a `0x00` byte is encountered. Multi-byte Kanji prefixes (`0x1B`–`0x1F` and `0x19`) consume the subsequent byte.
3. Read `uint8_t POS` into `entry->pos` (offset `0x11`).
4. Read semantic tag lists for Pass 0 and Pass 1:
   - Loop reading `uint16_be TagID`. If `TagID == 0`, break.
   - Otherwise, read `uint8_t Weight` into `entry->semantic_wts[i]` (offset `0x3A + i`).
   - Store `TagID` into `entry->semantic_ids[i]` (offset `0x12 + 2*i`).
   - Read 1 byte into `entry->flags_4e[pass]` (offset `0x4E + pass`).
5. Read 3 bytes into `entry->tail[0..2]` (offsets `0x50`, `0x51`, `0x52`).

#### In-Memory Runtime Struct (`D_800C8A08`)
In the game engine, each word record expands into a fixed **86-byte (`0x56`)** struct:

```c
typedef struct {
    char        word_str[17];     // +0x00: Null-terminated Japanese word
    uint8_t     pos;              // +0x11: Part of Speech classification
    uint16_t    semantic_ids[10]; // +0x12: Associated concept / topic trigger IDs
    uint8_t     semantic_wts[10]; // +0x3A: Topic weights / priorities
    uint8_t     flags_4e[2];      // +0x4E: Pass status flags
    uint8_t     tail_flags[3];    // +0x50: Extended flags (e.g. 0x11, 0x00, 0xFF)
    uint8_t     pad;              // +0x53: Alignment padding to 0x56
} JDictEntry; // sizeof == 0x56 (86 bytes)
```

---

### B. `MDICT<XX>.DCT` (Type 1: Morphological Grammar Trie)

`MDICT` provides the morphological syntax rules (which word classes, particles, or auxiliary endings can legally follow another word in player dialogue input). It forms a Directed Acyclic Graph (DAG) / transition network.

#### Binary Stream Layout

Terminated by a 16-bit big-endian `0x0000` EOF marker:

```
+---------------------------------------------------------------------------------------------------+
| Field                     | Size (Bytes)    | Description                                         |
+---------------------------+-----------------+-----------------------------------------------------+
| Node ID                   | 2 (Big Endian)  | 1-based Grammar State / Node index (0x0000 = EOF)   |
| Grammar Attribute         | 1               | State flags (e.g. start node, terminal node)        |
| Morpheme / Prefix String  | Variable + 1    | Null-terminated prefix string (empty for root node) |
| Follower Transition List  | Stream + 2      | Array of uint16_be Node IDs terminated by 0x0000    |
+---------------------------------------------------------------------------------------------------+
```

#### Parsing Loop in `LoadDictionaryData`:
1. Read `uint16_be NodeID`. If `NodeID == 0`, exit loop (EOF).
2. Read `uint8_t Attr` into `node->attr` (offset `0x11`).
3. Read characters into `node->prefix_str` until `0x00`. Multi-byte Kanji are handled identically to `JDICT`.
4. Read `uint16_be NextNodeID` until `NextNodeID == 0x0000`. Each ID is appended to `node->next_nodes[]` (offset `0x12 + 2*i`).

#### In-Memory Runtime Struct (`D_800CEF80`)
In engine memory, each grammar node expands into a fixed **38-byte (`0x26`)** struct:

```c
typedef struct {
    char        prefix_str[17];   // +0x00: Null-terminated prefix / morpheme token
    uint8_t     attr;             // +0x11: Node attribute flags
    uint16_t    next_nodes[10];   // +0x12: Legal transition target Node IDs (0-terminated)
} MDictNode; // sizeof == 0x26 (38 bytes)
```

---

## 3. `.BBB` File Format (`NAME.BBB`)

`NAME.BBB` (1,940 bytes) is the **Cast & Proper Noun Entity Database**. It allows the parser to recognize character names, surnames, and nicknames typed by the player and map them to runtime character IDs (`0x01`–`0x5E`).

Loaded during script initialization by `LoadPortraitLoopCutData` (decompiled function in [`src/main/script.c`](file:///home/halkun/reverse/anothermind/anothermind-decomp/src/main/script.c)) into table `D_800D1C58`.

#### File Stream Structure

The file contains **94 entity records**, terminated by a single `0x00` byte at offset 1939:

```
+---------------------------------------------------------------------------------------------------+
| Field                     | Size (Bytes)    | Description                                         |
+---------------------------+-----------------+-----------------------------------------------------+
| Entity ID                 | 1               | Character / Entity ID (0x01–0x5E, 0x00 = EOF)       |
| Slot 0: Primary Name      | 1 + N*chars + M | Count (u8) + [Kanji chars] + [Count * uint16_be IDs]|
| Slot 1: Given Name        | 1 + M           | Count (u8) + [Count * uint16_be IDs]                |
| Slot 2: Nickname / Alias  | 1 + M           | Count (u8) + [Count * uint16_be IDs]                |
+---------------------------------------------------------------------------------------------------+
```

#### Recognition Slots:
Each entity record has **3 recognition slots**:
1. **Slot 0 (Full Name / Surname)**: Contains the character count, followed by the encoded Kanji characters (e.g. `1B 00 1B 01` = `"葉山"`), followed by `Count` big-endian 16-bit semantic association IDs.
2. **Slot 1 (Given Name / Reading)**: Contains the element count, followed by `Count` big-endian 16-bit association IDs.
3. **Slot 2 (Nickname / Casual Reference)**: Contains the element count, followed by `Count` big-endian 16-bit association IDs.

#### Sample Entity Decoding:
| ID | Primary Name (Slot 0) | Japanese Cast Character | Role / Description |
|:---:|:---|:---|:---|
| `0x01` | 葉山 | 葉山 (Hayama) | Nanami's family / surname |
| `0x02` | 瞳 | 瞳 (Hitomi) | Nanami Hitomi (Protagonist) |
| `0x03` | 真野 | 真野 (Mano) | Mano Shunpei's surname |
| `0x04` | 俊平 | 俊平 (Shunpei) | Mano Shunpei (Co-protagonist) |
| `0x05` | 高木 | 高木 (Takagi) | Takagi Mariko's surname |
| `0x06` | 真理子 | 真理子 (Mariko) | Takagi Mariko (Friend) |
| `0x07` | 向井 | 向井 (Mukai) | Mukai Natsuko's surname |
| `0x08` | 夏子 | 夏子 (Natsuko) | Mukai Natsuko (Classmate) |
| `0x09` | 鳴海 | 鳴海 (Narumi) | Narumi Kenichi's surname |
| `0x0A` | 健一 | 健一 (Kenichi) | Narumi Kenichi (Detective) |
| `0x0B` | 猿渡 | 猿渡 (Sawatari) | Sawatari Jun |
| `0x0C` | 純 | 純 (Jun) | Sawatari Jun |
| `0x0D` | 明円 | 明円 (Myoen) | Myoen Teruo |
| `0x0E` | 輝夫 | 輝夫 (Teruo) | Myoen Teruo |
| `0x0F` | 桐原 | 桐原 (Kirihara) | Kirihara Ikuo |
| `0x10` | 育生 | 育生 (Ikuo) | Kirihara Ikuo |
| `0x12` | 冴子 | 冴子 (Saeko) | Saeko |
| `0x13` | 亜月 | 亜月 (Azuki) | Azuki |
| `0x15` | 黒川 | 黒川 (Kurokawa) | Kurokawa Daisuke |

#### In-Memory Runtime Struct (`D_800D1C58`):
Each entity expands into a **44-byte (`0x2C`)** struct:
```c
typedef struct {
    char        name_str[10];     // +0x00: Primary Kanji name string
    uint16_t    entity_ids[10];   // +0x0A: Semantic entity & cross-reference IDs
    uint8_t     slot_counts[3];   // +0x28: Count of elements in Slot 0, Slot 1, Slot 2
    uint8_t     pad;              // +0x2B: Padding
} NameEntity; // sizeof == 0x2C (44 bytes)
```

---

## 4. `.KAT` File Format (`KATSU.KAT`)

`KATSU.KAT` (419 bytes) is the **Grammatical Inflection Table** (*Katsuyou* = 活用 in Japanese).

Because Japanese verbs and adjectives conjugate heavily based on tense, politeness, and mood (e.g. 行く $\rightarrow$ 行かない, 行きます, 行けば, 行こう), `KATSU.KAT` provides the suffix matching rules that strip inflections and stem words back to their dictionary base form (`JDICT`).

Loaded by `LoadPortraitTextGridData` (decompiled function in [`src/main/script.c`](file:///home/halkun/reverse/anothermind/anothermind-decomp/src/main/script.c)) into table `D_800D50E0`.

#### Binary Stream Layout

The file contains **31 conjugation rule entries**, followed by a terminating byte `0x01` at offset 418:

```
+---------------------------------------------------------------------------------------------------+
| Field                     | Size (Bytes)    | Description                                         |
+---------------------------+-----------------+-----------------------------------------------------+
| Rule 0 (4 Forms)          | Variable        | 4 null-terminated inflected suffix strings          |
| Rule 1 (4 Forms)          | Variable        | 4 null-terminated inflected suffix strings          |
| ...                       | ...             | ...                                                 |
| Rule 30 (4 Forms)         | Variable        | 4 null-terminated inflected suffix strings          |
| EOF Terminator            | 1               | Byte 0x01                                           |
+---------------------------------------------------------------------------------------------------+
```

#### Rule Structure:
Each rule defines **4 null-terminated inflection suffixes**:
1. **Form 0: Continuative / Stem** (連用形 - *Ren'youkei*, e.g. stem for polite *-masu* form)
2. **Form 1: Negative / Irrealis** (未然形 - *Mizenkei*, e.g. stem for *-nai* form)
3. **Form 2: Conditional / Hypothetical** (仮定形 - *Kateikei*, e.g. stem for *-ba* form)
4. **Form 3: Volitional / Imperative** (命令・意志形 - *Meireikei/Ishikei*, e.g. stem for *-ou* / imperative)

#### In-Memory Runtime Struct (`D_800D50E0`):
In engine memory, each rule is stored as a fixed **60-byte (`0x3C`)** record ($4 \times 15$ bytes):

```c
typedef struct {
    char form_renyou[15];   // +0x00: Continuative suffix (Ren'youkei)
    char form_mizen[15];    // +0x0F: Negative / Irrealis suffix (Mizenkei)
    char form_katei[15];    // +0x1E: Conditional suffix (Kateikei)
    char form_meirei[15];   // +0x2D: Imperative / Volitional suffix (Meireikei)
} KatsuyouRule; // sizeof == 0x3C (60 bytes)
```

The 31 rules cover standard Japanese grammatical conjugations:
* **Godan Verbs** (五段活用): Ka-column (書く), Sa-column (話す), Ta-column (待つ), Na-column (死ぬ), Ba-column (呼ぶ), Ma-column (読む), Ra-column (走る), Wa-column (買う)
* **Ichidan Verbs** (上一段・下一段活用): E.g. 見る, 食べる, 逃げる
* **Irregular Verbs** (変格活用): *Kuru* (来る), *Suru* (する)
* **Adjectives & Auxiliary Stems** (形容詞・助動詞活用): E.g. ない, たい, らしい, かった

---

## 5. Technical Summary Table

| Asset File | Record Count | Terminating Byte | In-Memory Struct | Array Base Address | Primary Engine Function |
|---|---|---|---|---|---|
| **`JDICT<XX>.DCT`** | 100–300 words / file | `0x0000` (16-bit) | 86 bytes (`0x56`) | `0x800C8A08` | `LoadDictionaryData($a0=0)` |
| **`MDICT<XX>.DCT`** | 50–200 nodes / file | `0x0000` (16-bit) | 38 bytes (`0x26`) | `0x800CEF80` | `LoadDictionaryData($a0=1)` |
| **`NAME.BBB`** | 94 entities | `0x00` (8-bit) | 44 bytes (`0x2C`) | `0x800D1C58` | `LoadPortraitLoopCutData` |
| **`KATSU.KAT`** | 31 rules | `0x01` (8-bit) | 60 bytes (`0x3C`) | `0x800D50E0` | `LoadPortraitTextGridData` |

---

## 6. The Taiwa Engine: Connecting ZZS Bytecode to the Dictionaries

### The "Boxes" Part-of-Speech Input Model

Rather than choosing from pre-baked sentences, Another Mind presents the player with **modular grammatical selection boxes** based on standard Japanese Subject-Object-Verb (SOV) sentence structure:

```
[ Box 1: Subject (主語) ]  ──>  [ Box 2: Object / Topic (目的語) ]  ──>  [ Box 3: Verb / Action (動詞) ]
  • 私 (I)                        • 学校 (School)                           • 行く (Go)
  • あなた (You)                  • 病院 (Hospital)                         • 行かない (Don't go)
  • 瞳 (Hitomi)                   • 写真 (Photograph)                       • 探す (Search)
  • 俊平 (Shunpei)                • 真実 (The Truth)                        • 待つ (Wait)
```

The player selects a candidate word for each part of speech in turn:
1. **Box 1 (Subject / Shugo)**: Player picks who the action applies to (e.g. *"I"*).
2. **Box 2 (Object / Setting / Mokutekigo)**: Player picks the destination or subject matter (e.g. *"to the store"*).
3. **Box 3 (Verb / Action / Doushi)**: Player picks the action (e.g. *"went"*).
The resulting full sentence (*"I went to the store"*) is passed to the script VM to branch the story.

---

### How the Dictionary Files Power the Selection Boxes

The dictionary subsystem does not just store text—it actively constrains and validates what the player can form:

```
                          ┌──────────────────────────┐
                          │   NAME.BBB (Entities)    │
                          │   94 Cast Character IDs  │
                          └─────────────┬────────────┘
                                        │ (Populates Cast Names)
                                        ▼
┌─────────────────────────┐   ┌──────────────────────────┐   ┌──────────────────────────┐
│  Box 1: Subject (主語)  │──>│ Box 2: Object (目的語)   │──>│   Box 3: Verb (動詞)     │
└────────────┬────────────┘   └─────────────┬────────────┘   └────────────┬─────────────┘
             │                              │                             │
             │               ┌──────────────┴───────────┐                 │
             └──────────────>│   MDICT<XX>.DCT (Trie)   │<────────────────┘
                             │  Validates Legal Next    │
                             │  Grammar Transition Edges│
                             └──────────────┬───────────┘
                                            │
                             ┌──────────────┴───────────┐    ┌──────────────────────────┐
                             │   JDICT<XX>.DCT (Vocab)  │<───┤    KATSU.KAT (Katsuyou)  │
                             │  Word IDs, POS (00/01/02)│    │  Strips Verb Conjugation │
                             │  & Semantic Topic Tags   │    │  Suffixes to Base Form   │
                             └──────────────┬───────────┘    └──────────────────────────┘
                                            │
                                            ▼
                             ┌──────────────────────────┐
                             │  Resolved Taiwa Result   │
                             │  Subject ID -> D_800628E8│
                             │  Object ID  -> D_800628EA│
                             │  Verb ID    -> D_800628EC│
                             └──────────────┬───────────┘
                                            │
                                            ▼
                             ┌──────────────────────────┐
                             │  ZZS Script Conditional  │
                             │  Ladder: IFS, IFO, IFV   │
                             └──────────────────────────┘
```

1. **`NAME.BBB`**: Feeds cast member names and surnames into Box 1 (and Box 2 when asking about a character).
2. **`JDICT<XX>.DCT`**: Supplies the vocabulary candidate list filtered by Part of Speech (`POS = 0x00` for nouns/objects, `0x01` for verbs, `0x02` for particles/directions).
3. **`MDICT<XX>.DCT`**: Acts as a state-machine filter. When a player picks a word in Box 1, `MDICT` traverses its transition DAG to ensure that Box 2 only displays words that make grammatical and contextual sense following that subject.
4. **`KATSU.KAT`**: When verbs appear in various inflections (past, negative, polite), `KATSU.KAT` stems the suffix so the game logic compares against the canonical word ID.

---

### How `Cmd_tset` and the ZZS Bytecode Control the Sentence Flow

The interaction between the ZZS script bytecode, the UI, and the dictionary follows a three-step cycle: **Template Selection (`tset`)** $\rightarrow$ **Player Slot Selection (`talk`)** $\rightarrow$ **Conditional Evaluation (`ifs`/`ifo`/`ifv`)**.

#### 1. Template Selection: `Cmd_tset(template_id, layout_x)`
Instead of dumping hundreds of unrelated words from `JDICT` onto the screen, `Cmd_tset` (`0x59`) pre-selects an author-defined **sentence frame** (or Mad-Libs style template) for that specific prompt:

```
tset(110, 110);   // Arg 1: Template #110, Arg 2: Box X-coordinate 110px
```

* **`arg1` (Sentence Frame / Template ID $\rightarrow$ `D_80130CA0`)**:
  Selects which topic cluster and grammar root in `MDICT` is loaded. This defines the overall structure of the sentence (e.g. `[Subject] [Destination] [Action]`) and limits candidate words in each slot to those relevant to the current scenario branch.
* **`arg2` (UI Layout Offset $\rightarrow$ `D_80130CA2`)**:
  Sets the horizontal alignment (`g_TaiwaBarX`) of the selection boxes so they do not overlap character portraits or message boxes.
* **Special Case `tset(65535, 65535)` / `tset(-1, -1)`**:
  Passing `-1` resets the engine variables `D_80130CA0` and `D_80130CA2`, clearing custom topic filters and returning the UI layout to default centering.

#### 2. Slot Filling: `Cmd_talk`
`Cmd_talk` (`0x1C`) halts the script VM and renders the selection boxes on screen:
1. **Box 1 (Subject)** displays candidate actors from `NAME.BBB` and pronouns from `JDICT` seeded by the template.
2. The player's choice in Box 1 traverses the `MDICT` transition DAG to dynamically populate legal **Box 2 (Object/Destination)** candidates.
3. The player's choice in Box 2 further traverses `MDICT` to populate legal **Box 3 (Verb/Action)** candidates.
4. If the player picks a conjugated ending, `KATSU.KAT` stems the suffix back to the base verb ID.

#### 3. Return & Evaluation Ladder (`Cmd_ifs`, `Cmd_ifo`, `Cmd_ifv`)
When the player confirms the sentence with 〇, the engine writes the chosen slot IDs into memory and resumes the script interpreter:
* `D_800628E8`: Selected Subject ID (e.g., `SUBJECT_PLAYER`)
* `D_800628EA`: Selected Object ID (e.g., `OBJECT_STORE`)
* `D_800628EC`: Selected Verb ID (e.g., `VERB_WENT_TO`)

The script immediately evaluates these return values through an opcode ladder:

| Opcode | Name | Function in Sentence Evaluation |
|:---:|:---|:---|
| `0x1E` | `Cmd_ifs` | **If Subject in [List]**: Evaluates Box 1; jumps to label on match |
| `0x1F` | `Cmd_ifo` | **If Object in [List]**: Evaluates Box 2; jumps to label on match |
| `0x1D` | `Cmd_ifv` | **If Verb in [List]**: Evaluates Box 3; jumps to label on match |
| `0x5E` | `Cmd_ifc` | **If Complement in [List]**: Evaluates secondary modifiers / conditions |

```c
// Decompiled equivalent of ZZS script logic after Cmd_talk:
Cmd_tset(110, 110); // 1. Pick pre-made sentence template #110
Cmd_talk();         // 2. Halt VM; player picks Subject, Object, Verb from boxes

// 3. On return: evaluate the player's chosen values
if (Taiwa_Subject == SUBJECT_PLAYER) {
    if (Taiwa_Object == OBJECT_STORE) {
        if (Taiwa_Verb == VERB_WENT_TO) {
            goto label_went_to_store;  // Handled branch: "I went to the store"
        } else if (Taiwa_Verb == VERB_DID_NOT_GO) {
            goto label_did_not_go;     // Handled branch: "I didn't go to the store"
        }
    }
}

// Fallthrough fallback: unexpected or unhandled template combination
Cmd_print_a("Wait... what does that have to do with this, Hitomi?");
```

---

### Real Script Examples: The Tutorial Scripts (`TUTOS.ZZS` & `TUTOD.ZZS`)

The two tutorial scripts in `assets/jp/progdata/scripts/common/` contain the canonical introduction to the Taiwa system:

#### 1. In-Game Explanation of Sentence Construction (`TUTOS.ZZS` at offset `0x0469`)

In `TUTOS.ZZS`, the tutorial explicitly teaches the player how sentence boxes work using a full example sentence:

> **Japanese In-Game Dialogue (`Cmd_print_a` at `0x0469`):**  
> 「頭の中の少女に話しかけることでストーリーが進行していきます。  
> 彼女に話しかけるには、彼女に対話文を投げかける必要があります。  
> この対話文をどのように作るのか  
> **【君は】【学校に】【行ったか】**  
> という例を用いて説明します。  
> これは **「君は」「学校に」「行ったか」** という３つの部分を組み合わせることで成立している文です。  
> ゲーム中にある言葉を組み合わせて対話文を作ることになります。」

> **English Translation:**  
> *"The story progresses by speaking to the girl inside your head.  
> To speak to her, you need to form and address dialogue sentences to her.  
> To explain how to construct a dialogue sentence, we will use the example:  
> **[You] [to school] [did you go?]** (*Did you go to school?*).  
> This sentence is composed by combining three parts: **'You'** (Subject), **'to school'** (Object/Destination), and **'did you go?'** (Action/Verb).  
> Throughout the game, you will combine words from the dictionary to create your dialogue."*

#### Dictionary Mapping for the Tutorial Sentence:
* **Box 1: Subject (`君は` / You)**:
  - Base word: `君` (Word ID `0x0009` in `JDICT`, Kanji encoding `0x1B 0x92`) + Topic particle `は` (`0x92`).
* **Box 2: Object / Destination (`学校に` / to school)**:
  - Base word: `学校` (Word in `JDICT`, Kanji encoding `0x1B 0xA0 0x1B 0x18`) + Direction particle `に` (`0x8A`).
* **Box 3: Verb / Action (`行ったか` / did you go?)**:
  - Base verb: `行` (*Iku* / to go, Word ID `0x0003` in `JDICTTD.DCT`, Kanji encoding `0x1B 0x4F`).
  - Inflected via `KATSU.KAT` Rule 0 / 1 (Godan Ka-row past/question: 行く $\rightarrow$ 行った $\rightarrow$ 行ったか).

---

#### 2. Interactive Sentence Branching (`TUTOD.ZZS` at offset `0x00d2`)

In `TUTOD.ZZS` (paired with `JDICTTD.DCT` / `MDICTTD.DCT`), the game executes a real test prompt to verify player comprehension:

```
Bytecode offset [0x00d2]:
  [0x00d2] 0x59 (Cmd_tset)  0x44 (imm16, imm16)  0x006E  0x006E
  [0x00d8] 0x1C (Cmd_talk)  // Engine displays Taiwa boxes and halts VM

  // The conditional IFV ladder follows immediately:
  [0x00d9] 0x1D (Cmd_ifv)   Count=1  Value=0x0004 (Verb 4) -> Jump Label 23
  [0x00f0] 0x1D (Cmd_ifv)   Count=1  Value=0x0005 (Verb 5) -> Jump Label 24
  [0x0107] 0x02 (Cmd_call)  "cc"     // Default fallback branch
```

1. **`Cmd_tset` (`0x59`)**: Prepares the UI parameters (`0x006E`).
2. **`Cmd_talk` (`0x1C`)**: The 3 selection boxes appear. The player selects their test sentence.
3. **`Cmd_ifv` checks**:
   - If the player chose **Verb ID 4** (`ナヒグス`), the engine branches to **Label 23**.
   - If the player chose **Verb ID 5** (`ロムヴギ`), the engine branches to **Label 24**.
   - If an unrecognized combination was entered, execution falls through to `Cmd_call "cc"`, prompting the player to try again.


