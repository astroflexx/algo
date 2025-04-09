# Generates cpp.json with snippets for VSCode

import os
import json
import sys
import shutil

snippets = {}

for subdir in os.walk("."):
    if subdir[0] == "." or ".git" in subdir[0]:
        continue
    for filename in subdir[2]:
        name, extension = filename.split(".")
        if extension != "cpp":
            continue

        if name in snippets:
            print(f"error: duplicate snippet {name}", file=sys.stderr)
            exit(0)

        path = subdir[0] + "/" + filename
        with open(path, "r") as f:
            snippet = {
                "prefix": name,
                "body": ["$0"] + [line.rstrip() for line in f.readlines()],
                "description": name,
            }
            snippets[name] = snippet

        print(f"generated snippet {name}", file=sys.stderr)

with open("cpp.json", "w") as f:
    f.write(json.dumps(snippets, indent=4))

print("done", file=sys.stderr)

shutil.copyfile(
    "cpp.json", r"C:\Users\venka\AppData\Roaming\Code\User\snippets\cpp.json"
)
