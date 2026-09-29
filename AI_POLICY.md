# AI Policy

- The Encyclopedia Galactica defines a robot as a mechanical apparatus designed to do the work of a man.
- The marketing division of the Sirius Cybernetics Corporation defines a robot as "Your Plastic Pal Who’s Fun to Be With."
-  The Hitchhiker’s Guide to the Galaxy defines the marketing division of the Sirius Cybernetics Corporation as "a bunch of mindless jerks who’ll be the first against the wall when the revolution comes."

## Preamble
Humans use tools to help. Our arms are only so strong and fingers so nimble, and so we invent tools to make us better at what we do and make things better for others. However, there is a concern when the tools are left, literally, to their own devices. 

"Vibe Coding" is not a new thing. It's better known by its more professional name "Programming by Coincidence" or better "Coding by Accident". This has been a known anti-pattern since the term was coined way back in 1999. In a nutshell, it's coding without any idea of how anything works. If something does happen to function, it was only through sheer persistence to make the tool stop complaining about errors it finds. There are all kinds of problems with this that don't need enumeration here, but the idea is if you are not deliberately coding with a goal, then you are not coding at all. 

When open source projects get a PR from an LLM, it's easy to dismiss it as "Clanker Garbage", but that doesn't really explain the problem. People can lean on the social, economic, or environmental reasons why LLMs are "bad", but when a "Vibe Coded" PR is seen, a simple code review exposes the problem as clear as day. Wandering through the PR, it often shows a careless disregard for... well anything really. The foundations carefully set up by others were trashed without any reason or care. A lack of understanding of the core mission of the project is evident in almost every line of code, and every decision in its future direction is absolutely thoughtless.

However, we don't blame the LLM for making sub-par code. A tool is only as good as the operator, and you can't be mad at a lawn mower for cutting off your own hand.

This repository enforces strict rules regarding the use of Large Language Models (LLMs) and generative AI coding tools to ensure code quality, maintainability, and clear authorship.

## 1. Permitted and Prohibited Uses

- **Permitted:**
  - **IDE Autocomplete:** Standard line-level completions and syntax assistance.
  - **Reverse Engineering Assistance:** Brainstorming meaningful symbols, deciphering cryptic labels, and suggesting placeholder names based on context clues.
  - **Targeted Lookups:** Asking models to explain compiler quirks, calling conventions, or unfamiliar MIPS assembly patterns.

- **Prohibited:**
  - **Unreviewed Submissions:** Submitting agent- or LLM-generated code without a line-by-line manual code review.
  - **Uncontained Scope:** Letting an autonomous agent run wild across the repository and make sweeping, disparate changes. Keep contributions targeted and contained to a specific function or subsystem.
  - **Programming by Coincidence ("Vibe Coding"):** Submitting code that happens to match binary output purely by trial-and-error without understanding the underlying logic and hardware behavior.

## 2. Human-Driven PR Creation
- Pull requests must be manually opened and submitted by a human contributor.
- Do not automate PR submission with agents. Never submit auto-generated PR descriptions or unread agent transcripts; write a clear, human-authored description of your changes.

## 3. Mandatory AI Disclosure
- Every Pull Request must explicitly disclose whether and how AI tooling was utilized in producing the changes.

## 4. Reviewer Gate ("Explain Every Line")
- You own every line of code you submit. Contributors must be able to thoroughly explain the logic, types, and mechanics of their code during peer review.
- If you cannot explain how your code works or why a particular implementation was chosen, the PR will be rejected.


