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

## Compilation

Each example compiles independently:

```bash
cd behavioral/chain_of_responsibility
g++ -std=c++17 -Wall -o app main.cpp && ./app
```

No external dependencies. Requires a compiler with C++17 support (GCC 7+, Clang 5+, MSVC 2017+).

---

## Environment

- Standard: **C++17**
- Compiler: GCC / Clang / MSVC
- No CMake — intentionally, to avoid obscuring the pattern code

---

## Author

Marcin Kisielewski
[GitHub](https://github.com/twoj-nick) · [LinkedIn](https://linkedin.com/in/twoj-profil)
