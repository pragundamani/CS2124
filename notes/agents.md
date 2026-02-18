# agents.md - Notes Workspace Workflow

## Objective
Standardize how this repo handles:
- image storage in `imgs/`
- C++ lecture breakdown markdown files
- C++ source placement in `source/` (aside from most recent lec)
- image references inside C++ where needed

## 1) Move Images to `imgs/`
Rules:
- All diagram/image assets must live in `imgs/`.
- Do not keep image files in the repo root.
- Keep filenames lowercase and without spaces.

Supported image extensions:
- `.svg`, `.png`, `.jpg`, `.jpeg`, `.webp`, `.gif`, `.bmp`

Example targets:
- `imgs/lec8.svg`
- `imgs/lec8.1.png`

## 2) Break Down C++ Files into Markdown
For each lecture source file `lecN.cpp`, create a markdown breakdown file:
- `lecN_breakdown.md`

Required sections (use what exists in that file):
- `## Includes`
- `## Class <Name>` for each class
- `## Helper Functions` if present
- `## Function <Name>` for notable non-main functions
- `## main`
- `## Operator Overload` or `## Operator Overloads` if present

Formatting rules:
- Put C++ snippets in fenced blocks with language tag `cpp`.
- Keep code in source order.
- Keep comments from source code.

## 3) Move C++ Files to `source/`
Rules:
- Keep all lecture `.cpp` files in `source/`.
- Root directory should not contain lecture `.cpp` files.

Expected pattern:
- `source/lec4.cpp`
- `source/lec5.cpp`
- `source/lec6.cpp`
- `source/lec7.cpp`
- `source/lec8.cpp`

## 4) Attach Images in C++ Files Where Needed
When a C++ file has diagram anchors (for example `img0`, `img1`), use explicit image tag comments.

Required format:
```cpp
// img0: imgs/<file>
// img1: imgs/<file>
```

Placement:
- Prefer placing image tags near the related code section.
- Keep numbering sequential: `img0`, `img1`, `img2`, ...
- No numbering gaps.

Example:
```cpp
// img0: imgs/lec8.svg
// img1: imgs/lec8.1.png
```

## Validation Checklist
- No image files outside `imgs/`.
- `lecN_breakdown.md` exists for each `source/lecN.cpp`.
- No lecture `.cpp` files in root.
- C++ image tags (if used) point to files under `imgs/`.
