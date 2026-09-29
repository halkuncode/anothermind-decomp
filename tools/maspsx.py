#!/usr/bin/env python3
"""Wrapper for maspsx that applies project-specific assembly cleanups
(such as pruning dead epilogues after infinite loops) before passing to maspsx.
"""

import subprocess
import sys
from pathlib import Path

MASPSX_SCRIPT = Path(__file__).resolve().parent / "maspsx" / "maspsx.py"


def strip_dead_epilogue(lines: list[str]) -> list[str]:
    clean_lines = []
    skip_to_end = False
    last_label = None

    for line in lines:
        stripped = line.strip()
        if stripped.endswith(":") and not stripped.startswith("."):
            last_label = stripped[:-1]
        elif last_label and stripped == f"j\t{last_label}":
            clean_lines.append(line)
            skip_to_end = True
            continue
        elif skip_to_end:
            if (
                stripped.startswith(".end\t")
                or stripped.startswith(".ent\t")
                or (stripped.endswith(":") and not stripped.startswith("LM"))
            ):
                skip_to_end = False
            else:
                continue
        clean_lines.append(line)

    return clean_lines


def main():
    in_text = sys.stdin.read()
    lines = in_text.splitlines(keepends=True)
    clean_lines = strip_dead_epilogue(lines)
    filtered_text = "".join(clean_lines)

    proc = subprocess.run(
        [sys.executable, str(MASPSX_SCRIPT)] + sys.argv[1:],
        input=filtered_text,
        text=True,
        capture_output=True,
    )

    if proc.stderr:
        sys.stderr.write(proc.stderr)
    if proc.stdout:
        sys.stdout.write(proc.stdout)

    sys.exit(proc.returncode)


if __name__ == "__main__":
    main()
