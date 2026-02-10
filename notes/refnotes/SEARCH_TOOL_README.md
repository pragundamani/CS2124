# C++ Quick Reference Search Tool

A fast command-line tool to search through your C++ notes while coding.

## 🚀 Quick Start

```bash
# Search for a topic
./ref vector

# Search for multiple keywords
./ref smart pointer

# List all available topics
./ref --list

# Get help
./ref
```

## 📖 Usage Examples

### Basic Searches
```bash
./ref loop          # Find information about loops
./ref function      # Function basics
./ref class         # OOP classes
./ref pointer       # Pointer basics
```

### Common Topics
```bash
# Data structures
./ref vector
./ref map
./ref array
./ref string

# Memory management
./ref pointer
./ref "smart pointer"
./ref new
./ref delete

# OOP
./ref constructor
./ref inheritance
./ref virtual
./ref polymorphism

# Modern C++
./ref lambda
./ref auto
./ref move
./ref optional
```

### Specific Problems
```bash
./ref "pass by reference"    # How to pass by reference
./ref "file io"              # File input/output
./ref exception              # Exception handling
./ref template               # Generic programming
./ref recursion              # Recursive functions
```

## 🎯 Features

- **Fast indexed search** - Common topics return instantly
- **Full-text fallback** - Searches all notes if not in index
- **Syntax highlighting** - Color-coded output for readability
- **Context display** - Shows relevant code examples
- **Multi-keyword search** - Search for related concepts together
- **Portable** - Uses relative paths, works anywhere

## 📚 Indexed Topics

The tool has quick access to 100+ topics including:

**Basics:** variables, types, operators, loops, conditions, functions  
**Containers:** vector, map, set, array, list, deque, queue, stack  
**Memory:** pointer, reference, new, delete, smart pointers, RAII  
**OOP:** class, constructor, destructor, inheritance, polymorphism  
**Advanced:** template, lambda, exception, move semantics, ranges  
**Patterns:** factory, singleton, observer, two-pointer, sliding window  
**Algorithms:** sort, find, count, reverse, transform, binary search  
**Strings:** operations, conversion, manipulation  
**File I/O:** reading, writing, streams  

## 🔧 How It Works

1. **Indexed Search**: Common topics are pre-indexed for instant lookup
2. **Full-Text Search**: Falls back to searching all notes
3. **Smart Display**: Shows section headers, line numbers, and code examples
4. **Color Coding**: Makes output easy to scan quickly

## 💡 Tips

- Use quotes for multi-word searches: `./ref "move semantics"`
- Start broad, then get specific: `./ref class` → `./ref constructor`
- Use `--list` to discover available topics
- Keywords are case-insensitive
- Multiple keywords show results for each

## 🚀 Advanced Usage

### Python API
You can also use it directly in Python:
```python
from search_notes import smart_search

smart_search(['vector', 'push_back'])
```

### Adding to PATH
For global access, add an alias to your shell config:
```bash
# In ~/.bashrc or ~/.zshrc
alias cppref='python3 /path/to/CS2124/notes/search_notes.py'

# Then use from anywhere
cppref vector
```

### Custom Keywords
Edit `search_notes.py` and add to the `topic_index` dictionary:
```python
topic_index = {
    'your_keyword': [('filename.md', 'Section Name')],
    # ...
}
```

## 📝 Examples in Action

**Example 1: Quick vector reference**
```bash
$ ./ref vector
🔍 Quick Reference for: 'vector'

📄 File: advanced_basics.md
📌 Section: Vectors (std::vector)

vector<int> v;
v.push_back(1);
v.push_back(2);
cout << v.size() << "\n";  // 2
```

**Example 2: Memory management help**
```bash
$ ./ref "smart pointer"
🔍 Quick Reference for: 'smart pointer'

📄 File: intermediate.md
📌 Section: Smart Pointers Introduction

unique_ptr<int> ptr = make_unique<int>(42);
// Automatic cleanup - no delete needed!
```

**Example 3: Multiple related topics**
```bash
$ ./ref inheritance virtual
# Shows both inheritance AND virtual function sections
```

## 🐛 Troubleshooting

**No results found?**
- Check spelling
- Try alternative terms (e.g., "ptr" → "pointer")
- Use `--list` to see available topics
- Try a broader search term

**Script won't run?**
```bash
# Make sure it's executable
chmod +x search_notes.py ref

# Check Python version (needs 3.6+)
python3 --version
```

**Colors not showing?**
- Terminal must support ANSI colors
- Most modern terminals do by default

## 📂 File Organization

```
notes/
├── search_notes.py    # Main search script
├── ref                # Convenient wrapper script
├── basics.md          # Beginner notes
├── advanced_basics.md # Intermediate notes
├── common_patterns.md # Practical examples
├── intermediate.md    # OOP and memory
├── advanced.md        # Advanced features
├── expert.md          # Expert topics
└── README.md          # Learning path guide
```

## 🎓 Integration with Learning

This tool is designed to complement your learning:
- **While coding**: Quick reference for syntax
- **During practice**: Look up examples
- **Solving problems**: Find relevant patterns
- **Code review**: Refresh best practices

## 🔄 Updates

To add new topics to the index, edit `search_notes.py`:
1. Find the `topic_index` dictionary
2. Add your entry: `'keyword': [('file.md', 'Section')]`
3. Save and the change takes effect immediately

## 📞 Support

If you find a bug or want to suggest a feature:
1. Check if the topic exists: `./ref --list`
2. Try alternative search terms
3. Edit `search_notes.py` to add custom mappings

---

**Happy Coding! 🚀**

*Quick, focused, and always at your fingertips - just like C++ should be.*
