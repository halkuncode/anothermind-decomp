# Another Mind (PSX) - Taiwa (対話) System Architecture Specification

## 1. Overview & Design Philosophy

In Squaresoft's *Another Mind* (1998, PSX), the player does not control protagonist Hitomi Mano directly. Instead, the player exists as an internal psychic presence—an "Another Mind"—communicating with Hitomi and Nanami through the **Taiwa (対話, *Dialogue / Interactive Inquiry*) subsystem**.

Rather than selecting pre-written branching menu choices common in typical visual novels, Another Mind implements a **natural language sentence construction interface**. The player constructs complete thoughts by selecting grammatical constituents across distinct parts of speech:

```
[ Subject / Topic (主語) ]  +  [ Object / Target (目的語) ]  +  [ Predicate / Verb (述語) ]
       "私 (I)"            +     "病院へ (to hospital)"      +         "行った (went)"
```

The game engine validates the grammatical and contextual viability of the sentence using binary dictionaries (`.DCT`, `.BBB`, `.KAT`), dynamically prunes illegal or irrelevant combinations using constraint opcodes (`JSEL`, `MDEL_S`, `VARDEL_J`), and branches narrative logic through an evaluation ladder (`IFS`, `IFO`, `IFV`, `IFC`).

---

## 2. The 3-Box Sentence Builder Interface

### Visual Screen Layout
When the script interpreter executes `TALK` (`0x1C`) or `LTALK` (`0x69`), the dialogue interface suspends scenario bytecode advancement and renders three selectable candidate windows across the lower half of the screen:

```
+---------------------------------------------------------------------------------------+
|                                  BACKGROUND SCENE                                     |
|                                                                                       |
|   [ Nanami Portrait ]                         [ Hitomi Portrait ]                     |
|                                                                                       |
+---------------------------------------------------------------------------------------+
|  BOX 1: Topic / Subject (主語) |  BOX 2: Object / Target (目的語) |  BOX 3: Verb (述語)|
|  ----------------------------- |  ------------------------------ |  ----------------- |
|  > 私 (I)                      |  > 病院へ (To the hospital)     |  > 行った (Went)    |
|    桐生 (Kiryu)                |    事件について (About incident)|    聞いた (Asked)   |
|    看護婦 (The nurse)          |    手紙を (The letter)          |    見た (Saw)       |
|    犯人 (The culprit)          |    車を (The car)               |    知らない (Unknown)|
+---------------------------------------------------------------------------------------+
|  Resulting Sentence: "私は病院へ行った" (I went to the hospital.)                      |
|  [ Circle ]: Confirm Sentence       [ X ]: Cancel / Back      [ D-Pad ]: Navigate     |
+---------------------------------------------------------------------------------------+
```

### Positioning Configuration (`Cmd_tset` / `TSET`)
The screen coordinates of the 3-box interface are established by Opcode `0x59` (`Cmd_tset`):
```
TSET  <layout_x>  <layout_y>
```
* `layout_x`: Horizontal anchor offset (typically centered for full-party discussions, or left-aligned when portrait dossiers are displayed).
* `layout_y`: Vertical baseline on the 320x240 frame buffer.

---

## 3. Data Architecture: The Supporting Dictionaries

The Taiwa engine relies on four binary data formats in `assets/jp/progdata/dictionary/` (Group 02):

```
                                  +---------------------+
                                  |      NAME.BBB       |  Proper Nouns &
                                  | (Character Database)|  Speaker Names
                                  +----------+----------+
                                             |
+-------------------+             +----------v----------+             +--------------------+
|   JDICT<XX>.DCT   |             |   Taiwa UI Engine   |             |     KATSU.KAT      |
| (Type 0: Words &  +------------->   (3-Box Builder)   <-------------+ (Inflection Table: |
|   Semantic Tags)  |             +----------+----------+             |  Conjugations)     |
+-------------------+                        |                        +--------------------+
                                             |
                                  +----------v----------+
                                  |    MDICT<XX>.DCT    |  Morphological
                                  | (Grammar Trie / POS)|  Validation
                                  +---------------------+
```

1. **`JDICT<XX>.DCT` (Type 0: Vocabulary)**:
   - Stores all recognized words for the active chapter.
   - Each entry contains Word ID, text string, Part of Speech (POS), and two passes of weighted semantic association tags.
2. **`MDICT<XX>.DCT` (Type 1: Morphological Grammar Trie)**:
   - Encodes legal syntactic transitions between words (e.g. noun particles `は`, `が`, `を`, `に` connecting to valid verb classes).
3. **`NAME.BBB` (Character Database)**:
   - Maps speaker IDs (referenced by `NIN` and `MDEL_S`) to character names, pronouns, and portrait profiles.
4. **`KATSU.KAT` (Verb Inflection / Conjugation Rules)**:
   - Maps base verb stems to inflectional paradigms (past, negative, polite, interrogative).

The active chapter dictionaries are dynamically swapped into RAM via opcode `0x65` (`Cmd_loaddict`):
```
LOADDICT  slot=0  file_id=chapters/JDICT01.DCT   ; Load Vocabulary
LOADDICT  slot=1  file_id=chapters/MDICT01.DCT   ; Load Grammar Trie
```

---

## 4. Constraint & Filtering Engine: `JSEL`, `MDEL_S`, and `VARDEL_J`

A major challenge of natural language systems in adventure games is combinatorial explosion: if a player can combine any noun with any verb, hundreds of absurd sentences could be generated that the writers never authored responses for. 

Another Mind solves this through **dynamic grammatical and semantic constraint opcodes** executed immediately before the prompt:

```
             Chapter Dictionary (Hundreds of Words)
                              │
     [1. JSEL]                ▼
     Selects legal Verbs for this prompt ──► jutsugoBuffer (Max Verbs)
                              │
     [2. VARDEL_J]            ▼
     Prunes Verbs based on Story Flags ──► Removes inactive actions
                              │
     [3. MDEL_S]              ▼
     Prunes Nouns incompatible with ────► Removes nonsensical nouns
     the chosen Verb and Speaker          per (Speaker, Verb) pair
                              │
                              ▼
                Clean, Context-Relevant 3-Box UI
```

---

### A. `JSEL` (`0x23`): Predicate / Verb Selection (述語選択)

* **Etymology**: *Jutsugo Select* (述語選択 = Predicate Selection).
* **Binary Format**:
  ```
  0x23  <count: uint8>  { <desc: uint8>  <jutsugo_id: uint16> }...
  ```
* **Engine Implementation**:
  In [`docs/notes/SLPS_016.55.c`](file:///home/halkun/reverse/anothermind/anothermind-decomp/docs/notes/SLPS_016.55.c) (`func_jsel`):
  ```c
  oldJutsugoCount = numJutsugoEntries;
  numOperands = *scriptInstructionPointer++;
  for (i = 0; i < numOperands; i++) {
      decodedJutsugoId = decodeScriptOperand(1, *scriptInstructionPointer++);
      // Check if already in buffer; if not, append:
      jutsugoBuffer[numJutsugoEntries++] = decodedJutsugoId;
  }
  ```
* **How it Works**:
  Instead of presenting every verb in the chapter dictionary, `JSEL` explicitly defines which verbs/predicates the player can choose from for this specific inquiry.
* **Compiler Syntax**:
  ```
  JSEL  J<id1>, J<id2>, J<id3>
  ```
  *(e.g. `JSEL J12, J45, J89` adds "went", "saw", "asked" to Box 3).*

---

### B. `MDEL_S` (`0x24`): Speaker-Conditioned Noun Masking (名詞削除 / 話者)

* **Etymology**: *Meishi Delete / Speaker* (名詞削除 / 話者 = Noun Exclusion by Speaker).
* **Binary Format**:
  ```
  0x24  <desc1: uint8>  <speaker_id: uint16>
        <desc2: uint8>  <predicate_id: uint16>
        <count: uint8>  { <desc: uint8>  <noun_id: uint16> }...
  ```
* **Engine Implementation**:
  In [`docs/notes/SLPS_016.55.c`](file:///home/halkun/reverse/anothermind/anothermind-decomp/docs/notes/SLPS_016.55.c) (`func_mdel_s` and `FUN_8002ba98`):
  * Maintains a table of up to **10 `MDEL` rules** (`max: 10`).
  * Each rule associates a `(speakerId, predicateId)` pair with up to **20 excluded Noun IDs** (`max: 20`).
  * When `FUN_8002ba98` builds the noun candidate list for the UI:
    ```c
    if (meishiEntryCount != 0) {
        for (i = 0; i < meishiEntryCount; i++) {
            if (meishiVerbIds[i] == currentPredicate && meishiSpeakerIds[i] == currentSpeaker) {
                if (IsNounInList(meishiNounLists[i], candidateNounId)) {
                    // Excluded! Skip this noun:
                    return; // Does NOT add noun to candidate box
                }
            }
        }
    }
    // Add noun to UI candidate box...
    ```
* **How it Works**:
  Semantic filtering. Prevents asking nonsensical questions to specific people. For example:
  * When speaking to **Speaker 4 (The Nurse)** with verb **J12 ("Stole")**:
    `MDEL_S 4 J12 (M5, M8, M22)` removes "The Gun", "The Car", and "The Examination Sheet" from the noun box if they are irrelevant or impossible in that context.
* **Compiler Syntax**:
  ```
  MDEL_S  <speakerId>  J<predicateId> ( M<noun1>, M<noun2>, ... )
  ```

---

### C. `VARDEL_J` (`0x5D`): Variable-Conditioned Predicate Filtering (変数削除 / 述語)

* **Etymology**: *Variable Delete / Jutsugo* (変数削除 / 述語 = Predicate Filtering by Game Variable).
* **Binary Format**:
  ```
  0x5D  <desc: uint8>   <predicate_id: uint16>
        <count: uint8>  { <desc: uint8>  <var_condition: uint8> }...
  ```
* **Engine Implementation**:
  In [`docs/notes/SLPS_016.55.c`](file:///home/halkun/reverse/anothermind/anothermind-decomp/docs/notes/SLPS_016.55.c) (`func_vardel_j` and `FUN_8002bef8`):
  * Maintains up to **10 `VARDEL` rules** (`max: 10`).
  * Each rule maps a predicate ID to up to **3 game variable conditions** (`max: 3`).
  * When `FUN_8002bef8` renders predicate choices into the UI:
    ```c
    if (vardelEntryCount != 0) {
        for (i = 0; i < vardelEntryCount; i++) {
            if (vardelPredicateTable[i] == candidatePredicateId) {
                if (CheckVariableConditions(vardelVarList[i])) {
                    // Condition met! Prune this verb from active choices:
                    goto skip_predicate;
                }
            }
        }
    }
    // Add predicate to Box 3...
    ```
* **How it Works**:
  Dynamic scenario progression. Once a clue has been discovered or an inquiry line exhausted, `VARDEL_J` removes the action verb from future menus so the player cannot get stuck in repetitive loops.
* **Compiler Syntax**:
  ```
  VARDEL_J  J<predicateId> ( V<var1>, V<var2>, ... )
  ```

---

## 5. The Interactive Execution Cycle (`TALK` / `LTALK`)

When the script executes `TALK` (`0x1C`) or `LTALK` (`0x69`), the VM enters the interactive cycle:

```
  Script Interpreter                Taiwa UI Subsystem                     Player
         │                                   │                                │
         ├──── Opcode 0x1C (TALK) ──────────►│                                │
         │    (Script Suspends)              ├───── Render 3 Boxes ──────────►│
         │                                   │                                │
         │                                   │◄──── D-Pad / Nav Words ────────┤
         │                                   │      (Real-time Preview)       │
         │                                   │                                │
         │                                   │◄──── Press Circle (OK) ────────┤
         │                                   │                                │
         │                                   ├─ Validate syntax (MDICT)       │
         │                                   ├─ Populate registers:           │
         │                                   │    taiwaJn = Subject Word ID   │
         │                                   │    taiwaJv = Verb Word ID      │
         │                                   │    taiwaSlot = Word Count      │
         │                                   │                                │
         │◄── Resume Script Execution ───────┤                                │
         ▼                                   ▼                                ▼
   Evaluation Ladder (IFS / IFO / IFV / IFC)
```

### Taiwa State Machine (`taiwaActive`)
1. **State `0` (Inactive)**: Standard script bytecode execution.
2. **State `1` (Init Prompt)**: Invokes `FUN_8002bef8` (predicate filtering) and `FUN_8002ba98` (noun filtering), allocates GPU primitive buffers (`initTaiwaPrimitiveSystem`), and draws initial box chrome (`drawTaiwaSelectionBoxes`).
3. **State `2` (Player Navigation)**: Tracks controller D-Pad input. Cursor movements across boxes update highlight tiles (`drawTaiwaHighlightTileGrid`, `drawTaiwaHighlightBars`).
4. **State `3` (Validation)**: Consults `MDICT` transition tables. If an incompatible particle/noun combination is selected, plays error buzzer sound.
5. **State `4` (Return)**: Writes confirmed Word IDs to engine registers and resumes script bytecode advancement.

---

## 6. The Evaluation Ladder: Script Reaction Routing

Once the player submits a sentence, the script interpreter resumes at an **Evaluation Ladder**:

```
                       taiwaJn (Subject) & taiwaJv (Verb)
                                       │
                ┌──────────────────────▼──────────────────────┐
                │ Opcode 0x1E (IFS): Match Subject/Topic ID?  │
                └──────────────┬──────────────────────────────┘
                               │
               ┌───────────────┴───────────────┐
             Match                           No Match
               │                               │
┌──────────────▼─────────────┐   ┌─────────────▼─────────────┐
│ Opcode 0x1F (IFO):         │   │ Check next candidate or   │
│ Match Object ID?           │   │ fallthrough               │
└──────────────┬─────────────┘   └─────────────┬─────────────┘
               │                               │
       ┌───────┴───────┐                       │
     Match           No Match                  │
       │               │                       │
┌──────▼─────────────┐ │                       │
│ Opcode 0x1D (IFV): │ │                       │
│ Match Verb ID?     │ │                       │
└──────┬─────────────┘ │                       │
       │               │                       │
   ┌───┴───┐           │                       │
 Match   No Match      │                       │
   │       │           │                       │
   ▼       ▼           ▼                       ▼
Branch   Branch      Branch                 Branch
Label A  Label B     Label C             DEFAULT LABEL
(Exact   (Partial    (Wrong Verb)     ("I don't understand...")
Success) Topic)
```

### The Evaluation Opcodes
* **`IFS` (`0x1E`)**: Compares `taiwaJn` against a list of candidate Subject Word IDs.
* **`IFO` (`0x1F`)**: Compares the Object Word ID against candidate Object Word IDs.
* **`IFV` (`0x1D`)**: Compares `taiwaJv` against candidate Verb Word IDs.
* **`IFC` (`0x5E`)**: Compares Context / Complement Word IDs.
* **`IFS2` (`0x64`) / `IFO2` (`0x5F`) / `IFC2` (`0x63`)**: Extended secondary ladders for complex compound sentences.

Each ladder opcode has the format:
```
OPCODE  <count: uint8>  { <desc: uint8>  <word_id: uint16>  <target_block: uint16_be> }...
```
If a match is found, the interpreter jumps immediately to `target_block`. If no match occurs after checking `count` entries, it executes the next instruction in sequence.

---

## 7. Concrete Example: Tutorial Dialogue Walkthrough

Below is a complete, annotated disassembly trace from `assets/jp/progdata/scripts/common/TUTOS.ZZS`:

```assembly
; ==============================================================================
; PHASE 1: Load Dictionaries & Establish UI Layout
; ==============================================================================
LOADDICT    slot=0, id=chapters/JDICT01.DCT    ; Load Chapter 1 Vocabulary
LOADDICT    slot=1, id=chapters/MDICT01.DCT    ; Load Chapter 1 Grammar Trie
TSET        x=64, y=140                        ; Position 3-Box UI at (64, 140)

; ==============================================================================
; PHASE 2: Define Constraints & Populate Selection Pools
; ==============================================================================
; Enable Predicate choices: J10 ("Go"), J14 ("See"), J22 ("Ask")
JSEL        J10, J14, J22

; If Flag F14 (KnowsAboutMurder) is false, remove J22 ("Ask")
VARDEL_J    J22 ( V14 )

; When questioning Speaker 2 (Hitomi), if action is J10 ("Go"):
; Exclude Noun M88 ("Crime Scene") and M92 ("Underground Vault")
MDEL_S      2  J10 ( M88, M92 )

; ==============================================================================
; PHASE 3: Prompt Player for Input
; ==============================================================================
DIN                                            ; Open dialogue chrome
NIN         speaker=2                          ; Nameplate: Hitomi
PRINT_A     slot=0, "何をしに行けばいいの？\n"   ; "Where should I go?"
WAIT        frames=30
TALK                                           ; SUSPEND SCRIPT -> Open 3-Box UI

; ==============================================================================
; PHASE 4: Evaluate Player's Constructed Sentence
; ==============================================================================
; Check Subject: Did the player pick M01 ("I / 私")?
IFS         count=1, M01, @label_subject_matched
JUMP        @label_fallback_subject

@label_subject_matched:
; Check Object: Where did the player tell her to go?
IFO         count=2, M40, @label_hospital, M45, @label_school
JUMP        @label_fallback_object

@label_hospital:
; Check Verb: Did the player choose J10 ("Go") or J14 ("Investigate")?
IFV         count=1, J10, @branch_go_hospital
JUMP        @label_fallback_verb

; ==============================================================================
; PHASE 5: Script Reaction Blocks
; ==============================================================================
@branch_go_hospital:
DOUT                                           ; Close dialogue chrome
PRINT_A     slot=0, "わかった、病院へ行ってみる。\n" ; "Got it, I'll go to the hospital."
SJUMP       script_id=chapter_01/DIA0105.ZZS   ; Proceed to Hospital Scene

@label_fallback_verb:
PRINT_A     slot=0, "そんなこと、今はできないよ。\n" ; "I can't do that right now."
JUMP        @retry_talk

@label_fallback_subject:
PRINT_A     slot=0, "誰のことを言っているの？\n"   ; "Who are you talking about?"
JUMP        @retry_talk
```

---

## 8. Taiwa System Capacities & Limits

| Parameter / Buffer | Maximum Limit | Engine Check / Error Message | Location in Disassembly |
|---|---|---|---|
| **Max `MDEL_S` Rules** | 10 rules | `"too many mdel commands\nmax: 10"` | `func_mdel_s` (0x80023B00) |
| **Max Excluded Nouns per `MDEL`** | 20 nouns | `"too many meishi in mdel\nmax: 20"` | `func_mdel_s` (0x80023BA8) |
| **Max `VARDEL_J` Rules** | 10 rules | `"too many vardel commands\nmax: 10"` | `func_vardel_j` (0x80023D40) |
| **Max Variables per `VARDEL`** | 3 variables | `"too many var in vardel\nmax: 3"` | `func_vardel_j` (0x80023DE0) |
| **Active Predicate Buffer (`jutsugoBuffer`)** | 32 entries | Fixed RAM array | `D_800C9E80` |
| **Active Sentence Slots** | 3 components | Subject, Object, Predicate | `taiwaJn`, `taiwaJv`, `taiwaSlot` |
| **Call Stack Depth** | 16 frames | `"stack overflow in script"` | `scriptCallStack` |

---

## 9. Summary & Cross-References

* [`docs/md_reference/DICTIONARY_SPECIFICATION.md`](file:///home/halkun/reverse/anothermind/anothermind-decomp/docs/md_reference/DICTIONARY_SPECIFICATION.md): Detailed binary formats for `.DCT`, `.BBB`, `.KAT`, and runtime struct memory layouts.
* [`docs/md_reference/ZZS_OPCODE_REFERENCE.md`](file:///home/halkun/reverse/anothermind/anothermind-decomp/docs/md_reference/ZZS_OPCODE_REFERENCE.md): Full manual of all 140 ZZS opcodes including `TSET`, `TALK`, `JSEL`, `MDEL_S`, `VARDEL_J`, `IFS`, `IFO`, `IFV`, `IFC`.
* [`docs/md_reference/ZZS_SPECIFICATION.md`](file:///home/halkun/reverse/anothermind/anothermind-decomp/docs/md_reference/ZZS_SPECIFICATION.md): File structure, header encoding, and Kanji text streaming.
* [`src/main/script.c`](file:///home/halkun/reverse/anothermind/anothermind-decomp/src/main/script.c): Script VM implementation.
* [`docs/notes/SLPS_016.55.c`](file:///home/halkun/reverse/anothermind/anothermind-decomp/docs/notes/SLPS_016.55.c): Ghidra disassembly reference.

