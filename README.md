# CP-Templates

A comprehensive collection of algorithms and data structures for competitive programming in C++.

## 📋 Table of Contents

- [About](#about)
- [Templates](#templates)
  - [DSU (Disjoint Set Union)](#dsu-disjoint-set-union)
  - [Segment Trees](#segment-trees)
  - [Graphs](#graphs)
  - [Strings](#strings)
  - [Trie](#trie)
  - [Math](#math)
- [Usage](#usage)
- [Template Base](#template-base)

## About

This repository contains implementations of common algorithms and data structures used in competitive programming. All templates are written in C++ and follow a consistent coding style.

## Templates

### DSU (Disjoint Set Union)

- **BaseDSU.cpp**: Standard Disjoint Set Union with path compression and union by size
  - `find(int a)`: Find the representative of set containing `a`
  - `merge(int a, int b)`: Union two sets
  - `sameSet(int a, int b)`: Check if two elements are in the same set
  - `getSetSize(int a)`: Get the size of the set containing `a`

- **RollbackDSU.cpp**: DSU with rollback capability (useful for offline queries)
  - Supports undoing the last merge operations

- **WeightedDSU.cpp**: DSU with weights/distances on edges
  - Useful for problems requiring relative positions or distances

### Segment Trees

- **BaseST.cpp**: Basic Segment Tree with point updates and range queries
  - `build(const vi& a)`: Build tree from array
  - `update(int pos, int val)`: Update single element
  - `query(int l, int r)`: Query sum in range [l, r]

- **LazyST.cpp**: Lazy Propagation Segment Tree for range updates
  - `build(const vi& a)`: Build tree from array
  - `update(int l, int r, int add)`: Add value to range [l, r]
  - `query(int l, int r)`: Query sum in range [l, r]

### Graphs

- **Dijkstra.cpp**: Shortest path from single source (non-negative weights)
  - `addEdge(int u, int v, int w)`: Add directed edge
  - `solve(int src)`: Compute shortest paths from source
  - `getPath(int dest)`: Reconstruct shortest path to destination

- **FloydWarshall.cpp**: All-pairs shortest paths
  - `addEdge(int u, int v, int w)`: Add edge
  - `solve()`: Compute all-pairs shortest paths
  - `hasNegativeCycle()`: Detect negative cycles
  - Time complexity: O(n³)

- **Kosaraju.cpp**: Find Strongly Connected Components
  - `addEdge(int u, int v)`: Add directed edge
  - `findSCC()`: Find all SCCs
  - Returns component ID for each node

- **Tarjan.cpp**: Alternative SCC algorithm (single DFS)
  - `addEdge(int u, int v)`: Add directed edge
  - `findSCC()`: Find all SCCs using Tarjan's algorithm

- **KosarajuCondensation.cpp**: SCC + Condensation Graph
  - `addEdge(int u, int v)`: Add directed edge
  - `findSCC()`: Find all SCCs
  - `buildCondensation()`: Build DAG of SCCs
  - Useful for DP on DAGs after finding SCCs

### Strings

- **KMP.cpp**: Knuth-Morris-Pratt pattern matching
  - `computePrefixFunction(const string& s)`: Compute prefix function (π array)
  - `KMP(const string& text, const string& pattern)`: Find all occurrences of pattern in text
  - Time complexity: O(n + m)

### Trie

- **Trie.cpp**: Standard Trie for strings
  - `insert(const string& s)`: Insert string
  - `search(const string& s)`: Check if string exists
  - `startsWith(const string& prefix)`: Check if any string starts with prefix

- **BinaryTrie.cpp**: Trie for binary representations (XOR problems)
  - `insert(int x)`: Insert number
  - `remove(int x)`: Remove number
  - `maxXor(int x)`: Find maximum XOR with x
  - Configurable bit length (default 30 bits)

### Math

- **Criba.cpp**: Sieve of Eratosthenes
  - Generate all prime numbers up to n
  - Time complexity: O(n log log n)

- **PascalsTriangle.cpp**: Pascal's Triangle / Binomial Coefficients
  - Precompute binomial coefficients
  - Useful for combinatorics problems

## Usage

Each template is self-contained and can be copied directly into your solution. Most templates follow this pattern:

```cpp
#include <bits/stdc++.h>
using namespace std;

// Copy the struct/functions here

signed main() {
    // Your code using the template
    return 0;
}
```

### Example: Using Dijkstra

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

// [Copy Dijkstra.cpp code here]

signed main() {
    int n = 5; // number of nodes
    Dijkstra graph(n);
    
    graph.addEdge(0, 1, 4);
    graph.addEdge(0, 2, 1);
    graph.addEdge(2, 1, 2);
    graph.addEdge(1, 3, 1);
    graph.addEdge(2, 3, 5);
    
    graph.solve(0); // compute from node 0
    
    cout << "Distance to node 3: " << graph.dist[3] << '\n';
    
    return 0;
}
```

### Example: Using KMP

```cpp
#include <bits/stdc++.h>
using namespace std;

// [Copy KMP.cpp code here]

int main() {
    string text = "ababcababa";
    string pattern = "aba";
    
    vector<int> matches = KMP(text, pattern);
    
    cout << "Pattern found at positions: ";
    for (int pos : matches) {
        cout << pos << " ";
    }
    cout << '\n';
    
    return 0;
}
```

## Template Base

The file `template.cpp` contains a comprehensive competitive programming template with:
- Common includes and namespace imports
- Useful macros and type definitions
- Helper functions (gcd, lcm, ceil_div)
- Fast I/O setup
- Multi-testcase structure

You can use this as a starting point for any competitive programming problem.

## Contributing

Feel free to add more templates or improve existing ones. Make sure to:
- Follow the existing code style
- Test your implementation
- Add documentation in this README

## License

This repository is intended for educational and competitive programming purposes.
