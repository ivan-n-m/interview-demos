# QBRecord / RecordCollection Project

## Project Summary

This project implements a simple in-memory **database-like collection** in C++ for managing records with unique IDs. It demonstrates clean class design, indexing, searching, and testing practices.

### Features

- **Record Structure (**`QBRecord`**)**
- - Each record contains `id`, `value`, `name`, and `description`.
  - Supports default and parameterized constructors.
- **Record Collection (**`RecordCollection`**)**
- - Add records with duplicate ID prevention.
  - Delete records by ID efficiently using an internal index.
  - Search records:
  - - By specific column (`findByColumn`)
    - Using custom predicates (`find` and `findIndices`)
  - Safe access:
  - - `getRecord` throws on invalid index
    - `tryGet` returns `std::optional` for safe access
- **Templates and Predicates**
- - Generic template functions allow flexible queries.
  - `findIndices` returns indexes for fast access to results.
- **Unit and Performance Testing**
- - Unit tests cover:
  - - Adding records
    - Duplicate ID handling
    - Deleting records
    - Searching and edge cases
  - Performance tests demonstrate behavior with large datasets (e.g., 100k records).

### Design Considerations

- **Memory and Padding**
- - `QBRecord` fields are ordered to minimize padding (largest types first).
- **Safety**
- - `tryGet` prevents exceptions from invalid indices.
- **Efficiency**
- - Index map (`unordered_map`) enables O(1) deletion and search by ID.
- **Extensibility**
- - Column-based search can be extended for substring searches or more advanced filters.

### Build Instructions

1. **Requirements**
2. - C++20 compatible compiler (e.g., GCC, Clang, MSVC)
   - CMake or simple command-line compilation
   - Optional: Visual Studio Code for IDE support
3. **Compilation Example (CLI)**

```javascript
g++ -std=c++20 main.cpp RecordCollection.cpp -o record_db
./record_db
```

1. **Compilation Example (VSCode / CMake)**
2. - Configure project to use C++20
   - Include all `.h` and `.cpp` files
   - Build and run using VSCode build tasks

### Testing

- **Unit Tests**
- - Automatically executed in `main.cpp`
  - Check core functionalities and edge cases
- **Performance Tests**
- - Measure insertion, search, and deletion times
  - Demonstrates scaling behavior

### Notes for Evaluation

- Code correctness and memory safety are verified via unit tests.
- Performance measurements are included to illustrate efficiency.
- Clear documentation with Doxygen-style comments is p
 Build Instructions (VSCode)

[](https://github.com/ivan-n-m/GameOfLife#build-instructions-vscode)

This project can be built in different ways on multiple platforms. Here, we present a **portable solution using VSCode**, which can be easily installed on **Windows**, **Linux**, and **macOS**.

### Prerequisites

[](https://github.com/ivan-n-m/GameOfLife#prerequisites)

- **C++20 compiler** (required for all platforms):
- - **Windows:** MinGW64 or MSVC toolchain
  - **Linux:** g++ or clang++ supporting C++20
  - **macOS:** clang++ supporting C++20 (Xcode Command Line Tools recommended)

### Windows (default)

[](https://github.com/ivan-n-m/GameOfLife#windows-default)

By default, this project is set up to build on **Windows** using **MinGW64**.

- Default compiler path:
- VSCode configuration files:
- - `.vscode/c_cpp_properties.json` → compiler path, include paths, C++ standard
  - `.vscode/tasks.json` → build task
  - `.vscode/launch.json` → optional debug configuration
- To build:
- 1. Open the project folder in VSCode.
  2. Press **Ctrl+Shift+B** or select **Terminal → Run Build Task → Build Debug**.The default build task uses the following command:
  3. To run the program:
  4. - `input.txt` should contain the initial Life 1.06 coordinates.
- **Customizing compiler path:**&#x49;f your MinGW64 is installed in a different location, update the `"compilerPath"` field in `c_cpp_properties.json`:
- **Customizing build output:**&#x54;o change the output executable path, edit the `"args"` array in `tasks.json`:








rovided.
- Templates are used for generic searching and index retrieval.
