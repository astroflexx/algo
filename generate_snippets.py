#!/usr/bin/env python3

import json
import os
import sys

REPO = os.path.dirname(os.path.abspath(__file__))
OUT = os.path.expanduser("~/.config/nvim/snippets/cpp.json")
SKIP_DIRS = {".git", ".vscode"}

snippets = {}

for root, dirs, files in os.walk(REPO):
    dirs[:] = [d for d in dirs if d not in SKIP_DIRS]
    for filename in sorted(files):
        if not filename.endswith(".cpp"):
            continue

        stem = filename[:-4]
        if stem in snippets:
            sys.exit(f"error: duplicate snippet name '{stem}'")

        with open(os.path.join(root, filename)) as f:
            lines = [line.rstrip() for line in f]

        description = stem
        for line in lines:
            stripped = line.strip()
            if stripped.startswith("//"):
                description = stripped.lstrip("/").strip() or stem
                break
            if stripped:
                break

        snippets[stem] = {
            "prefix": stem,
            "body": lines,
            "description": description,
        }
        print(f"  {stem}", file=sys.stderr)

os.makedirs(os.path.dirname(OUT), exist_ok=True)
with open(OUT, "w") as f:
    json.dump(snippets, f, indent=4)
    f.write("\n")

print(f"wrote {len(snippets)} snippets -> {OUT}", file=sys.stderr)
