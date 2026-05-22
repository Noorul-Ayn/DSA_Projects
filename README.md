# DSA Projects — C Implementations

**Student:** Hauwa Muhammad Bello  
**GitHub:** https://github.com/Noorul-Ayn/DSA_Projects  
**Course:** Data Structures and Algorithms  

---

## Overview

This repository contains four C implementations of core Data 
Structures and Algorithms concepts, including sorting, linked 
lists, binary trees, and binary search trees.

---

## Question 1 — Student Records Sorter

**File:** `question1/sort_students.c`

### Description
Reads student records from a flat file (students.txt), stores 
them in an array of structs, sorts them using the Quick Sort 
algorithm, and writes the sorted output to sorted_students.txt.

### Features
- Reads pipe-delimited student records from file
- Stores records in array of structs
- Sorts by grade ascending using Quick Sort
- Tie-breaking by first name lexicographically
- Writes sorted output to sorted_students.txt

### Data Structure
Array of Student structs:
- First name (string)
- Last name (string)
- Student ID (string)
- Grade (float)

### How to Compile & Run
```bash
cd question1
gcc -o sort_students sort_students.c
./sort_students
```

### Time Complexity
| Case | Complexity |
|------|------------|
| Best | O(n log n) |
| Average | O(n log n) |
| Worst | O(n²) |

---

## Question 2 — Bus Route Navigator

**File:** `question2/bus_route.c`

### Description
Models a bus route using a doubly linked list where each node 
represents a bus stop. Provides a menu-driven interface for 
forward and backward traversal with a 3-second delay between stops.

### Features
- Doubly linked list with forward and backward links
- Menu-driven navigation interface
- 3-second delay between stops using sleep()
- Dynamic insertion of new stops at end of route
- Graceful exit with full memory cleanup

### Data Structure
Doubly Linked List Node:
- Stop number (integer)
- Stop name (string)
- Pointer to next node
- Pointer to previous node

### How to Compile & Run
```bash
cd question2
gcc -o bus_route bus_route.c
./bus_route
```

### Time Complexity
| Operation | Complexity |
|-----------|------------|
| Add stop at end | O(1) |
| Traverse forward | O(n) |
| Traverse backward | O(n) |

---

## Question 3 — Binary Tree Explorer

**File:** `question3/binary_tree.c`

### Description
Constructs a binary tree from an array of 68 distinct integers 
using level-order (BFS) insertion. Supports querying the root, 
leaf nodes, parent, siblings, and grandchildren of any node.

### Features
- Level-order BFS insertion guaranteeing complete binary tree
- Print root node
- Print all leaf nodes
- Find parent of any node
- Find siblings of any node
- Find grandchildren of any node
- Graceful handling of invalid node selections

### Data Structure
Binary Tree Node:
- Data (integer)
- Pointer to left child
- Pointer to right child

Queue (linked list) used for BFS traversal.

### How to Compile & Run
```bash
cd question3
gcc -o binary_tree binary_tree.c
./binary_tree
```

### Time Complexity
| Operation | Complexity |
|-----------|------------|
| Insert node | O(n) |
| Search node | O(n) |
| Print leaves | O(n) |

---

## Question 4 — Student BST Search System

**File:** `question4/student_bst.c`

### Description
Reads student academic records from a pipe-delimited text file, 
constructs a Binary Search Tree (BST) using last name as the key, 
and supports efficient searching by last name.

### Features
- Reads and parses pipe-delimited records (Firstname|Lastname|Grade)
- BST construction using last name as key
- Duplicate last names inserted into right subtree
- Search by last name retrieves all matching records
- In-order traversal prints all records sorted by last name
- Robust file validation (empty files, malformed records)
- Graceful exit with full memory cleanup

### Data Structure
BST Node:
- First name (string)
- Last name (string) — BST key
- Grade (float)
- Pointer to left child
- Pointer to right child

### How to Compile & Run
```bash
cd question4
gcc -o student_bst student_bst.c
./student_bst
```

### Time Complexity
| Case | Complexity |
|------|------------|
| Best | O(1) |
| Average | O(log n) |
| Worst | O(n) |

---

## Repository Structure

```
DSA_Projects/
├── README.md
├── question1/
│   ├── sort_students.c
│   ├── students.txt
│   └── sorted_students.txt
├── question2/
│   └── bus_route.c
├── question3/
│   └── binary_tree.c
└── question4/
    ├── student_bst.c
    └── students.txt
```
