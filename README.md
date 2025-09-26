# Bank Account Management System

## Overview

This project implements a Bank Account Management System using various hash map collision resolution techniques in C++. It demonstrates different approaches to handling collisions, including:

- **Chaining**
- **Linear Probing**
- **Quadratic Probing**
- **Cubic Probing**
- **Comparator-based Hashing**

Each technique is implemented in a separate module for scalability and maintainability.

## Features

- Add, search, update, and delete bank accounts efficiently.
- Modular design for easy extension and maintenance.
- Demonstrates multiple collision resolution strategies.
- Well-documented code for learning and experimentation.

## Getting Started

### Prerequisites

- C++ compiler (e.g., GCC, Clang, MSVC)
- CMake (optional, for building)

### Building

1. Clone the repository.
2. Compile all `.cpp` files together, or use CMake for easier management.

Example (using g++):
```sh
g++ -std=c++11 *.cpp -o bank_account_manager
```

### Running

Execute the compiled binary:
```sh
./bank_account_manager
```

Follow the on-screen instructions to manage bank accounts.

## Scalability

- **Modular Design:** Each collision resolution strategy is in its own file/class, making it easy to add new methods or scale the system.
- **Extensible:** New account types or hashing strategies can be added with minimal changes.
- **Performance:** Hash maps provide fast access; different strategies can be benchmarked for large datasets.

## File Structure

- `BaseClass.h` - Common interface for hash map implementations.
- `Chaining.cpp/h` - Chaining collision resolution.
- `LinearProbing.cpp/h` - Linear probing.
- `QuadraticProbing.cpp/h` - Quadratic probing.
- `CubicProbing.cpp/h` - Cubic probing.
- `Comp.cpp/h` - Comparator-based hashing.
- `problem_statement.pdf` - Project requirements.
- `README.md` - Project documentation.

## Contributing

Feel free to fork the repository and submit pull requests for improvements or new features.

## License

This project is open-source and available under the MIT License.
# Banking-Hashmap-Collision-Resolution
Implemented a high-performance banking database system in C++ using custom hashing techniques. Built and compared collision resolution strategies (Chaining, Linear, Quadratic, Cubic Probing) to efficiently manage large-scale account data. Highlights skills in data structures, algorithms, and performance optimization.
