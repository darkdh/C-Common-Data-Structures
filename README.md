#C-Common-Data-Structures
+ Build Status
   - [![Build Status](https://travis-ci.org/ZSShen/C-Common-Data-Structures.svg?branch=master)](https://travis-ci.org/ZSShen/C-Common-Data-Structures)  Travis CI (integration testing)
   - [![Coverage Status](https://coveralls.io/repos/ZSShen/C-Common-Data-Structures/badge.png?branch=master)](https://coveralls.io/r/ZSShen/C-Common-Data-Structures?branch=master)  Coveralls (code coverage testing)

##Introduction
Though STL is convenient, the know-how is more valuable.   

This project implements some classic data structures using C.   
It is not only a memo but also a verification for some advanced   
or theoretical structures.

##Usage
### 1. Source Building
   
#### 1.1 Source Tree
+ The contained data structures and the relevant building tools.   
    - Makefile
    - Tree   
        * BinarySearchTree   
        * RedBlackTree   
    - List   
        * SinglyLinkedList   
    - Array   
        * DynamicArray   
    - Map   
        * OrderedMap   
    - Heap   
        * BinaryHeap   
        * BinomialHeap   
    - Queue   
        * PriorityQueue   
    - Misc   
        * interface_generator.py   

+ The source files for a single structure.
    - DataStructure
        * data_structure.c
        * data_structure.h
        * test_program.c
        * Makefile
   
#### 1.2 Building Entire Source
    Generally, each data structure is wrapped in a single C structure and   
    is built as an object file. To verify its correctness, we must rely  
    on the test program which sets up several unit test functions.   

    Therefore, there is a major Makefile at the top of source tree:   
        For the normal build, execute `make all`.   
        For the debug build (memory inspection), executre `make all DEBUG=true`.   

#### 1.3 Building Specific Structure

### 2. Binary Execution
