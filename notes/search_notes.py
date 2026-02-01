#!/usr/bin/env python3
"""
C++ Notes Quick Reference Search Tool
Search through C++ notes for topics, concepts, and code examples.
Usage: python search_notes.py <keyword> [keyword2] ...
"""

import os
import sys
import re
from pathlib import Path

# ANSI color codes for better readability
class Colors:
    HEADER = '\033[95m'
    BLUE = '\033[94m'
    CYAN = '\033[96m'
    GREEN = '\033[92m'
    YELLOW = '\033[93m'
    RED = '\033[91m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'
    END = '\033[0m'

def get_notes_directory():
    """Get the directory containing the notes files (relative to this script)."""
    script_dir = Path(__file__).parent
    return script_dir

def load_notes_index():
    """Create an index of topics to files and sections."""
    notes_dir = get_notes_directory()
    
    # Map of keywords to (file, section) tuples
    topic_index = {
        # Basics
        'hello world': [('basics.md', 'Hello World')],
        'compilation': [('basics.md', 'Compilation Process')],
        'main': [('basics.md', 'Basic Program Skeleton')],
        'cout': [('basics.md', 'Hello World'), ('basics.md', 'Input & Output')],
        'cin': [('basics.md', 'Basic Input')],
        'print': [('basics.md', 'Hello World')],
        'input': [('basics.md', 'Basic Input')],
        'variables': [('basics.md', 'Variable Declaration')],
        'types': [('basics.md', 'Primitive Data Types'), ('basics.md', 'Type Casting')],
        'int': [('basics.md', 'Variable Declaration')],
        'double': [('basics.md', 'Variable Declaration')],
        'string': [('basics.md', 'Variable Declaration'), ('common_patterns.md', 'String Operations')],
        'bool': [('basics.md', 'Variable Declaration')],
        'char': [('basics.md', 'Variable Declaration')],
        'auto': [('basics.md', 'Type Inference'), ('expert.md', 'Auto and Decltype')],
        'const': [('basics.md', 'Constants')],
        'constexpr': [('basics.md', 'Constants'), ('expert.md', 'Constexpr Functions')],
        'cast': [('basics.md', 'Type Casting')],
        'operators': [('basics.md', 'Operators')],
        'arithmetic': [('basics.md', 'Arithmetic Operators')],
        'comparison': [('basics.md', 'Comparison Operators')],
        'logical': [('basics.md', 'Logical Operators')],
        'bitwise': [('basics.md', 'Bitwise Operators')],
        'if': [('basics.md', 'If Statement')],
        'else': [('basics.md', 'If-Else Statement')],
        'switch': [('basics.md', 'Switch Statement')],
        'ternary': [('basics.md', 'Ternary Operator')],
        'loop': [('basics.md', 'Loops')],
        'while': [('basics.md', 'While Loop')],
        'for': [('basics.md', 'For Loop')],
        'do while': [('basics.md', 'Do-While Loop')],
        'break': [('basics.md', 'Break and Continue')],
        'continue': [('basics.md', 'Break and Continue')],
        'namespace': [('basics.md', 'Namespaces')],
        'using': [('basics.md', 'Namespaces')],
        'include': [('basics.md', 'Preprocessor Directives')],
        'define': [('basics.md', 'Preprocessor Directives')],
        
        # Functions
        'function': [('advanced_basics.md', 'Functions')],
        'return': [('advanced_basics.md', 'Function Declaration and Definition')],
        'void': [('advanced_basics.md', 'Void Functions')],
        'parameter': [('advanced_basics.md', 'Function Parameters')],
        'pass by value': [('advanced_basics.md', 'Pass by Value')],
        'pass by reference': [('advanced_basics.md', 'Pass by Reference')],
        'reference': [('advanced_basics.md', 'Pass by Reference'), ('intermediate.md', 'Pointers vs References')],
        'overload': [('advanced_basics.md', 'Function Overloading')],
        'default parameter': [('advanced_basics.md', 'Default Parameters')],
        'inline': [('advanced_basics.md', 'Inline Functions')],
        
        # Recursion
        'recursion': [('advanced_basics.md', 'Recursion')],
        'recursive': [('advanced_basics.md', 'Recursion')],
        'factorial': [('advanced_basics.md', 'Factorial')],
        'fibonacci': [('advanced_basics.md', 'Fibonacci Sequence')],
        'base case': [('advanced_basics.md', 'Recursion')],
        
        # Arrays and Vectors
        'array': [('advanced_basics.md', 'Arrays')],
        'vector': [('advanced_basics.md', 'Vectors'), ('common_patterns.md', 'Vector Patterns')],
        'push_back': [('advanced_basics.md', 'Common Operations')],
        'pop_back': [('advanced_basics.md', 'Common Operations')],
        'size': [('advanced_basics.md', 'Accessing Elements')],
        'capacity': [('advanced_basics.md', 'Size vs Capacity')],
        'iterator': [('advanced_basics.md', 'Iterating Through Vectors'), ('advanced.md', 'Iterators')],
        '2d vector': [('advanced_basics.md', 'Vectors of Vectors'), ('common_patterns.md', '2D Vectors for Matrices')],
        
        # Pointers and Memory
        'pointer': [('intermediate.md', 'Pointers & Memory')],
        'address': [('intermediate.md', 'Pointer Basics')],
        'dereference': [('intermediate.md', 'Declaration and Dereferencing')],
        'nullptr': [('intermediate.md', 'Null Pointers'), ('expert.md', 'nullptr')],
        'new': [('intermediate.md', 'Dynamic Memory Allocation')],
        'delete': [('intermediate.md', 'new and delete Operators')],
        'memory leak': [('intermediate.md', 'Memory Leaks and Prevention')],
        'smart pointer': [('intermediate.md', 'Smart Pointers Introduction')],
        'unique_ptr': [('intermediate.md', 'unique_ptr')],
        'shared_ptr': [('intermediate.md', 'shared_ptr')],
        'weak_ptr': [('intermediate.md', 'weak_ptr')],
        'raii': [('intermediate.md', 'RAII Principle')],
        
        # OOP
        'class': [('intermediate.md', 'Object-Oriented Programming Basics')],
        'object': [('intermediate.md', 'Classes vs Structs')],
        'constructor': [('intermediate.md', 'Constructors')],
        'destructor': [('intermediate.md', 'Destructors')],
        'this': [('intermediate.md', 'this Pointer')],
        'public': [('intermediate.md', 'Access Specifiers')],
        'private': [('intermediate.md', 'Access Specifiers')],
        'protected': [('intermediate.md', 'Access Specifiers')],
        'static': [('intermediate.md', 'Static Members')],
        'const member': [('intermediate.md', 'Const Member Functions')],
        'inheritance': [('advanced.md', 'Inheritance')],
        'polymorphism': [('advanced.md', 'Virtual Functions and Polymorphism')],
        'virtual': [('advanced.md', 'Virtual Functions and Polymorphism')],
        'override': [('advanced.md', 'Virtual Functions and Polymorphism')],
        'abstract': [('advanced.md', 'Abstract Classes and Pure Virtual Functions')],
        'interface': [('advanced.md', 'Abstract Classes and Pure Virtual Functions')],
        
        # Containers
        'map': [('intermediate.md', 'std::map')],
        'set': [('intermediate.md', 'std::set')],
        'unordered_map': [('intermediate.md', 'std::unordered_map')],
        'unordered_set': [('intermediate.md', 'std::unordered_set')],
        'deque': [('intermediate.md', 'std::deque')],
        'list': [('intermediate.md', 'std::list')],
        'queue': [('intermediate.md', 'std::deque')],
        'stack': [('common_patterns.md', 'Vector Patterns')],
        
        # Algorithms
        'sort': [('advanced_basics.md', 'Sorting'), ('common_patterns.md', 'Sorting a Vector')],
        'find': [('advanced_basics.md', 'Searching')],
        'count': [('advanced_basics.md', 'Counting')],
        'reverse': [('advanced_basics.md', 'Reversing')],
        'accumulate': [('advanced_basics.md', 'Accumulation')],
        'transform': [('advanced.md', 'Transform Operations')],
        'binary_search': [('advanced_basics.md', 'Binary Search'), ('advanced_basics.md', 'Searching')],
        
        # Strings
        'string operations': [('common_patterns.md', 'String Operations')],
        'substr': [('common_patterns.md', 'String Operations')],
        'find': [('common_patterns.md', 'String Operations')],
        'replace': [('common_patterns.md', 'String Operations')],
        'stoi': [('common_patterns.md', 'String to Number Conversion')],
        'to_string': [('common_patterns.md', 'String to Number Conversion')],
        
        # File I/O
        'file': [('common_patterns.md', 'File I/O')],
        'ifstream': [('common_patterns.md', 'Reading from a File')],
        'ofstream': [('common_patterns.md', 'Writing to Files')],
        'fstream': [('common_patterns.md', 'File Stream Types')],
        'getline': [('basics.md', 'Reading Strings with Spaces'), ('common_patterns.md', 'Reading Patterns')],
        
        # Templates
        'template': [('intermediate.md', 'Templates Basics'), ('advanced.md', 'Advanced Templates')],
        'generic': [('intermediate.md', 'Function Templates')],
        'typename': [('intermediate.md', 'Function Templates')],
        
        # Exception Handling
        'exception': [('intermediate.md', 'Exception Handling')],
        'try': [('intermediate.md', 'try-catch Blocks')],
        'catch': [('intermediate.md', 'try-catch Blocks')],
        'throw': [('intermediate.md', 'Throw Statements')],
        
        # Modern C++
        'lambda': [('advanced.md', 'Lambda Expressions')],
        'move': [('advanced.md', 'Move Semantics & Rvalue References')],
        'rvalue': [('advanced.md', 'Rvalue References')],
        'optional': [('expert.md', 'std::optional')],
        'variant': [('expert.md', 'std::variant')],
        'any': [('expert.md', 'std::any')],
        'ranges': [('expert.md', 'Ranges Library')],
        
        # Design Patterns
        'factory': [('expert.md', 'Factory Pattern')],
        'singleton': [('expert.md', 'Singleton Pattern')],
        'observer': [('expert.md', 'Observer Pattern')],
        'strategy': [('expert.md', 'Strategy Pattern')],
        
        # Common Patterns
        'two pointer': [('common_patterns.md', 'Two-Pointer Technique')],
        'sliding window': [('common_patterns.md', 'Sliding Window Pattern')],
        'frequency': [('common_patterns.md', 'Frequency Counting with Maps')],
        'duplicate': [('common_patterns.md', 'Finding Duplicates')],
    }
    
    return topic_index

def search_in_file(filepath, keyword):
    """Search for keyword in a file and return matching sections with context."""
    results = []
    
    try:
        with open(filepath, 'r', encoding='utf-8') as f:
            lines = f.readlines()
        
        current_section = ""
        section_lines = []
        
        for i, line in enumerate(lines):
            # Track current section (headers starting with #)
            if line.startswith('#'):
                if section_lines and keyword.lower() in '\n'.join(section_lines).lower():
                    results.append({
                        'section': current_section,
                        'content': section_lines[:20],  # First 20 lines of section
                        'line_num': i - len(section_lines)
                    })
                current_section = line.strip('#').strip()
                section_lines = [line]
            else:
                section_lines.append(line)
        
        # Check last section
        if section_lines and keyword.lower() in '\n'.join(section_lines).lower():
            results.append({
                'section': current_section,
                'content': section_lines[:20],
                'line_num': len(lines) - len(section_lines)
            })
    
    except Exception as e:
        print(f"Error reading {filepath}: {e}")
    
    return results

def display_result(filename, section, content, line_num):
    """Display a search result with formatting."""
    print(f"\n{Colors.BOLD}{Colors.BLUE}{'='*80}{Colors.END}")
    print(f"{Colors.BOLD}{Colors.GREEN}📄 File:{Colors.END} {filename}")
    print(f"{Colors.BOLD}{Colors.CYAN}📌 Section:{Colors.END} {section}")
    print(f"{Colors.BOLD}{Colors.YELLOW}📍 Line:{Colors.END} {line_num}")
    print(f"{Colors.BOLD}{Colors.BLUE}{'-'*80}{Colors.END}")
    
    # Display content with syntax highlighting for code blocks
    in_code_block = False
    for line in content:
        if line.strip().startswith('```'):
            in_code_block = not in_code_block
            print(f"{Colors.CYAN}{line.rstrip()}{Colors.END}")
        elif in_code_block:
            print(f"{Colors.GREEN}{line.rstrip()}{Colors.END}")
        elif line.startswith('#'):
            print(f"{Colors.BOLD}{Colors.YELLOW}{line.rstrip()}{Colors.END}")
        else:
            print(line.rstrip())

def smart_search(keywords):
    """Smart search that uses index and falls back to full-text search."""
    notes_dir = get_notes_directory()
    topic_index = load_notes_index()
    
    results_found = False
    
    # First, try indexed search
    for keyword in keywords:
        keyword_lower = keyword.lower()
        
        # Check if keyword is in index
        if keyword_lower in topic_index:
            results_found = True
            print(f"\n{Colors.BOLD}{Colors.HEADER}🔍 Quick Reference for: '{keyword}'{Colors.END}")
            
            for filename, section in topic_index[keyword_lower]:
                filepath = notes_dir / filename
                if filepath.exists():
                    results = search_in_file(filepath, section)
                    for result in results:
                        display_result(filename, result['section'], 
                                     result['content'], result['line_num'])
    
    # If no indexed results, do full-text search
    if not results_found:
        print(f"\n{Colors.BOLD}{Colors.HEADER}🔍 Full-text search for: {', '.join(keywords)}{Colors.END}")
        
        note_files = ['basics.md', 'advanced_basics.md', 'common_patterns.md', 
                      'intermediate.md', 'advanced.md', 'expert.md']
        
        for filename in note_files:
            filepath = notes_dir / filename
            if filepath.exists():
                for keyword in keywords:
                    results = search_in_file(filepath, keyword)
                    if results:
                        results_found = True
                        for result in results:
                            display_result(filename, result['section'], 
                                         result['content'], result['line_num'])
    
    return results_found

def list_topics():
    """List all indexed topics."""
    topic_index = load_notes_index()
    
    print(f"\n{Colors.BOLD}{Colors.HEADER}📚 Available Topics:{Colors.END}\n")
    
    categories = {
        'Basics': ['hello world', 'variables', 'types', 'operators', 'if', 'loop', 'for', 'while'],
        'Functions': ['function', 'return', 'parameter', 'recursion', 'overload'],
        'Data Structures': ['array', 'vector', 'map', 'set', 'list', 'string'],
        'Pointers & Memory': ['pointer', 'reference', 'new', 'delete', 'smart pointer'],
        'OOP': ['class', 'constructor', 'inheritance', 'polymorphism', 'virtual'],
        'Advanced': ['template', 'lambda', 'exception', 'move', 'ranges'],
        'Patterns': ['factory', 'singleton', 'observer', 'two pointer', 'sliding window'],
    }
    
    for category, topics in categories.items():
        print(f"{Colors.BOLD}{Colors.CYAN}{category}:{Colors.END}")
        for topic in topics:
            if topic in topic_index:
                print(f"  • {topic}")
        print()

def main():
    if len(sys.argv) < 2:
        print(f"{Colors.BOLD}C++ Quick Reference Search Tool{Colors.END}")
        print(f"\n{Colors.YELLOW}Usage:{Colors.END}")
        print(f"  python {sys.argv[0]} <keyword> [keyword2] ...")
        print(f"  python {sys.argv[0]} --list    (show all topics)")
        print(f"\n{Colors.YELLOW}Examples:{Colors.END}")
        print(f"  python {sys.argv[0]} vector")
        print(f"  python {sys.argv[0]} pointer memory")
        print(f"  python {sys.argv[0]} lambda")
        print(f"  python {sys.argv[0]} \"smart pointer\"")
        print(f"\n{Colors.YELLOW}Quick Topics:{Colors.END}")
        print(f"  Basics: variables, types, loop, if, function")
        print(f"  Containers: vector, map, set, array, string")
        print(f"  Memory: pointer, reference, new, delete, smart pointer")
        print(f"  OOP: class, constructor, inheritance, virtual")
        print(f"  Advanced: template, lambda, exception, move")
        return 1
    
    if sys.argv[1] == '--list':
        list_topics()
        return 0
    
    keywords = sys.argv[1:]
    
    results_found = smart_search(keywords)
    
    if not results_found:
        print(f"\n{Colors.RED}❌ No results found for: {', '.join(keywords)}{Colors.END}")
        print(f"\n{Colors.YELLOW}💡 Suggestions:{Colors.END}")
        print(f"  • Try different keywords (e.g., 'ptr' → 'pointer')")
        print(f"  • Use --list to see all available topics")
        print(f"  • Check spelling")
        return 1
    
    print(f"\n{Colors.BOLD}{Colors.GREEN}✅ Search complete!{Colors.END}\n")
    return 0

if __name__ == '__main__':
    sys.exit(main())
