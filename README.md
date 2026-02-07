# CP-Templates

A comprehensive collection of algorithms and data structures for competitive programming (primarily in C++).

## 📋 Table of Contents

- [About](#about)
- [Templates](#templates)
  - [DSU (Disjoint Set Union)](#dsu-disjoint-set-union)
  - [Segment Trees](#segment-trees)
  - [Graphs](#graphs)
  - [Strings](#strings)
  - [Trie](#trie)
  - [Math](#math)
- [Template Base](#template-base)
- [Contributing](#contributing)

## About

This repository contains implementations of common algorithms and data structures used in competitive programming. Each template includes comprehensive documentation directly in the source code explaining:
- What arguments it receives
- Which parameters will be modified
- Where results are stored
- Time and space complexity

**Note:** Some templates may have been initially written with AI assistance, but all have been reviewed and tested to ensure correct functionality.

## Templates

Each file contains detailed usage documentation at the top of the code. Simply open the file to see how to use it.

### DSU (Disjoint Set Union)

- **BaseDSU.cpp**: Standard Disjoint Set Union with path compression and union by size
- **RollbackDSU.cpp**: DSU with rollback capability (useful for offline queries)
- **WeightedDSU.cpp**: DSU with weights/distances on edges

### Segment Trees

- **BaseST.cpp**: Basic Segment Tree with point updates and range queries
- **LazyST.cpp**: Lazy Propagation Segment Tree for range updates

### Graphs

- **Dijkstra.cpp**: Single-source shortest paths (non-negative weights)
- **FloydWarshall.cpp**: All-pairs shortest paths
- **Kosaraju.cpp**: Find Strongly Connected Components
- **Tarjan.cpp**: Alternative SCC algorithm (single DFS)
- **KosarajuCondensation.cpp**: SCC with condensation graph (DAG of SCCs)

### Strings

- **KMP.cpp**: Knuth-Morris-Pratt pattern matching

### Trie

- **Trie.cpp**: Standard Trie for strings
- **BinaryTrie.cpp**: Binary Trie for XOR operations

### Math

- **Criba.cpp**: Sieve of Eratosthenes
- **PascalsTriangle.cpp**: Pascal's Triangle / Binomial Coefficients

## Template Base

The file `template.cpp` contains a comprehensive competitive programming template with:
- Common includes and namespace imports
- Useful macros and type definitions
- Helper functions (gcd, lcm, ceil_div)
- Fast I/O setup
- Multi-testcase structure

You can use this as a starting point for any competitive programming problem.

## Contributing

Contributions are welcome! You can:
- Add new templates (in C++ or other languages)
- Improve existing implementations
- Fix bugs or optimize code
- Add more test cases

**Guidelines for contributions:**
- Follow the existing code style for the language you're using
- Add comprehensive documentation at the top of your code explaining usage
- Test your implementation thoroughly
- Make sure your code compiles and runs correctly
- Each template should be self-contained and easy to copy

**Language Support:**
- Primary language: C++
- Other languages are welcome! Feel free to add implementations in Python, Java, Rust, or any other language.

## License

This repository is intended for educational and competitive programming purposes.
