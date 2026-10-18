# What is Source Code Reconstruction?

**Source Code Reconstruction** is a software preservation and digital archaeology effort dedicated to recovering, reconstructing, and documenting the original source code of legacy software.

By pairing modern decompilation techniques with the original period-accurate compilers and toolchains, source code reconstruction aims to reconstruct readable, compilable C code that builds byte-for-byte identically to the original retail binary.

---

### Project Scope & Purpose

#### 1. A Code Recovery Effort
During the video game industry's rapid transition from the PlayStation 1 to PlayStation 2 development in the late 1990s and early 2000s, source code management standards were vastly different from today. As development servers were migrated or decommissioned, **much of Squaresoft's original PlayStation-era source code was permanently lost, damaged, or discarded**.

This project exists to recover that lost history: reconstructing the internal architecture, game engine logic, script interpreters, and dialogue state machines of *Another Mind* so they can be studied, preserved, and archived for historical research.

#### 2. Not a PC Port
This project is **not** an effort to port the game to PC, modern consoles, or alternate platforms. It does not produce a standalone desktop application, nor does it distribute proprietary assets. Every line of recovered C code is designed to compile targeting the original Sony PlayStation 1 hardware (`SLPS-016.55`).

#### 3. Not a Translation Project
This project is **not** an English localization or fan translation effort. While having recovered source code can certainly aid the preservation and ROM hacking communities in understanding file formats and text encoding, the primary objective remains the faithful, 1:1 reconstruction of the original Japanese codebase.
