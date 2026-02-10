# Quick Start Guide - C++ Notes + Search Tool

## 🎯 You Have

1. **6 comprehensive note files** (8,488 lines)
   - `basics.md` - Start here
   - `advanced_basics.md` - Functions, arrays, vectors
   - `common_patterns.md` - Practical examples
   - `intermediate.md` - OOP, memory, templates
   - `advanced.md` - Advanced OOP, STL, multithreading
   - `expert.md` - Modern C++, patterns, optimization

2. **12-week learning schedule** (`schedule.md`)
   - Designed for Python developers
   - 10-15 hours/week
   - Projects and checkpoints

3. **Quick reference search tool** (`./ref`)
   - Search topics instantly
   - 100+ indexed keywords
   - Color-coded output

## 🚀 Get Started Right Now

### 1. Start Learning (Week 1)
```bash
# Read the first lesson
cat basics.md | head -100

# Follow the schedule
cat schedule.md | less
```

### 2. While Coding - Quick Reference
```bash
# Look up topics instantly
./ref vector
./ref pointer
./ref class
./ref "smart pointer"

# See all available topics
./ref --list
```

### 3. Common Searches
```bash
# I need to...
./ref "file io"              # Read/write files
./ref loop                   # Write a loop
./ref function               # Create a function
./ref vector                 # Use dynamic arrays
./ref map                    # Key-value pairs
./ref pointer                # Work with pointers
./ref constructor            # Initialize objects
./ref inheritance            # Extend classes
./ref exception              # Handle errors
./ref lambda                 # Anonymous functions
```

## 📚 Learning Path

```
Week 1-2  → basics.md + advanced_basics.md (Functions)
Week 3    → common_patterns.md (Strings, Files, Vectors)
Week 4    → intermediate.md (Pointers & Memory) ⚠️ Critical!
Week 5-6  → intermediate.md (OOP, Containers)
Week 7-8  → intermediate.md (Templates, Exceptions)
Week 9    → advanced.md (Inheritance, Polymorphism)
Week 10   → advanced.md (Lambdas, Move Semantics)
Week 11   → expert.md (Modern C++, Patterns)
Week 12   → Build final project!
```

## 💻 Typical Workflow

### Morning (Learning)
```bash
# 1. Check today's lesson in schedule.md
# 2. Read the relevant notes file
# 3. Code along with examples
# 4. Complete practice exercises
```

### While Coding (Reference)
```bash
# Stuck? Quick search!
./ref <topic>

# Example: "How do I add to a vector?"
./ref vector
# Shows: push_back, insert, emplace_back, etc.
```

### Evening (Practice)
```bash
# Work on weekly project
# Use ./ref for quick lookups
# Build something real!
```

## 🎓 First Day Checklist

- [x] ✅ Notes are ready
- [x] ✅ Search tool works (`./ref --list`)
- [ ] Read `basics.md` - Program Structure
- [ ] Set up C++ compiler (g++ or clang)
- [ ] Write Hello World
- [ ] Complete Week 1, Day 1 exercises
- [ ] Try the search tool: `./ref cout`

## 🔥 Pro Tips

1. **Code Every Day**: Even 30 minutes counts
2. **Type Examples**: Don't copy-paste, type them out
3. **Use the Search Tool**: `./ref` is your friend
4. **Build Projects**: Apply what you learn
5. **Read Errors**: Compiler errors teach you
6. **Compare to Python**: Leverage what you know

## 📖 Quick Reference Commands

```bash
# Essential commands
./ref --list                 # See all topics
./ref <keyword>              # Search a topic
./ref <word1> <word2>        # Multiple searches
./ref "exact phrase"         # Phrase search

# Most useful searches
./ref basics                 # Get started
./ref vector                 # Most common container
./ref pointer                # Critical concept
./ref class                  # OOP basics
./ref smart pointer          # Modern memory management
./ref lambda                 # Modern functions
```

## 🆘 Common Questions

**Q: Where do I start?**
A: Read `schedule.md` for the full plan, or jump into `basics.md` now.

**Q: How do I search for something?**
A: `./ref <keyword>` - Try `./ref vector` as a test.

**Q: I'm from Python, what's different?**
A: Check `schedule.md` - it has Python → C++ comparisons throughout.

**Q: How do I compile C++ code?**
A: `g++ -std=c++17 program.cpp -o program && ./program`

**Q: What if ./ref doesn't work?**
A: Make sure it's executable: `chmod +x ref search_notes.py`

## 🎯 Your First Hour

1. **Install compiler** (5 min)
   ```bash
   # Ubuntu/Debian
   sudo apt install g++
   
   # macOS
   xcode-select --install
   ```

2. **Hello World** (10 min)
   ```cpp
   #include <iostream>
   int main() {
       std::cout << "Hello, C++!\n";
       return 0;
   }
   ```
   ```bash
   g++ hello.cpp -o hello && ./hello
   ```

3. **Try the search tool** (5 min)
   ```bash
   ./ref --list
   ./ref cout
   ./ref vector
   ```

4. **Read basics.md** (40 min)
   - Program structure
   - Variables and types
   - Your first exercises

## 🚀 You're Ready!

Everything is set up. The journey from Python to C++ mastery starts now.

**Next Steps:**
1. Open `schedule.md` - Your roadmap
2. Start Week 1, Day 1
3. Use `./ref` whenever you need help
4. Code every day
5. Build projects

**Good luck! 🎓**

*"The only way to learn programming is by writing programs." - Dennis Ritchie*
