# cpp-design-patterns

Repository contains implementations of classic design patterns in **C++**.
Each pattern is a separate folder with working code and a short description of the problem it solves.

This project was created as a personal exercise and it could be used as tutorial or course. Code is concise, without unnecessary abstractions.

---

## Structure

```
cpp-design-patterns/
├── behavioral/
│   └── chain_of_responsibility/
├── creational/
└── structural/
```

---

## Patterns

### Behavioral

| Pattern                                                       | Description                                                   | Status |
| ------------------------------------------------------------- | ------------------------------------------------------------- | ------ |
| [Chain of Responsibility](./behavioral/chain_of_responsibility/) | Chain of handlers — request travels until someone handles it | ✅     |

### Creational

| Pattern | Description | Status |
| ------- | ----------- | ------ |
| —      | —          | 🔜     |

### Structural

| Pattern | Description | Status |
| ------- | ----------- | ------ |
| —      | —          | 🔜     |

---

## Build & Run

### Option 1: Using CMake (Recommended)

**Build all patterns:**

```bash
cmake -S . -B build
cmake --build build
./build/behavioral/chain_of_responsibility/Debug/chain_of_responsibility.exe
```

**Build single pattern independently:**

```bash
cd behavioral/chain_of_responsibility
cmake -S . -B build
cmake --build build
./build/Debug/chain_of_responsibility.exe
```

**Build with Google Test:**

```bash
cmake -S . -B build_tests -DBUILD_TESTS=ON
cmake --build build_tests
cd build_tests
ctest --output-on-failure
```

### Option 2: Manual Compilation

Each pattern can be compiled directly without CMake:

```bash
cd behavioral/chain_of_responsibility
g++ -std=c++17 -Wall -I include -o app src/main.cpp && ./app
```

---

**Requirements:** C++17 compiler (GCC 7+, Clang 5+, MSVC 2017+). No external dependencies.

---

## Environment

- Standard: **C++17**
- Compiler: GCC / Clang / MSVC
- Build System: **CMake 3.16+** (optional — manual compilation also supported)
- Testing: **Google Test** (optional, enabled with `-DBUILD_TESTS=ON`)

---

## Author

Marcin Kisielewski
[GitHub](https://github.com/twoj-nick) · [LinkedIn](https://linkedin.com/in/twoj-profil)
