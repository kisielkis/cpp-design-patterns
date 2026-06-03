# Visitor Pattern

## Problem Statement

Different types of objects (Person, Car, etc.) need to have new operations performed on them without modifying their classes. For example, you might want to serialize, validate, transform, or analyze these objects. Rather than adding methods to each class, the Visitor pattern allows you to define new operations in a separate visitor class that "visits" each object and performs the operation.

The workflow is:
1. A visitor interface defines how to visit different object types
2. Concrete visitors implement specific operations (e.g., StreamVisitor for output)
3. Objects accept a visitor and call the appropriate visit method
4. New operations can be added by creating new visitors without modifying existing classes

## Requirements

1. **Element** (abstract base class)
   - Pure virtual `accept(Visitor *visitor)` method
   - Subclasses implement to support visitor operations

2. **Visitor** (abstract visitor interface)
   - Pure virtual `visit(Person *person)` method — handles Person visitation
   - Pure virtual `visit(Car *car)` method — handles Car visitation
   - Subclasses implement specific operations

3. **StreamVisitor** (concrete visitor)
   - Implements `visit(Person*)` — outputs person data
   - Implements `visit(Car*)` — outputs car data

4. **Person** (concrete element)
   - Inherits from Element
   - Constructor: `Person(int age, const string &name)`
   - Method `accept(Visitor *visitor)` — implements `visitor->visit(this)`
   - Getters: `getAge()`, `getName()`
   - Stores: age, name

5. **Car** (concrete element)
   - Inherits from Element
   - Constructor: `Car(const string &model, const string &engine, int speed)`
   - Method `accept(Visitor *visitor)` — implements `visitor->visit(this)`
   - Getters: `getModel()`, `getEngine()`, `getMaxSpeed()`
   - Stores: model, engine, maxSpeed

## Expected Output

```
START
handlePerson 5 john
handleCar corolla 2.0 Hybrid Dynamic Force 192
END
```

## Compilation

### Direct Compilation (no CMake)

```bash
# Using g++ (primary)
cd behavioral/visitor
g++ -std=c++17 -Wall -o app src/main.cpp && ./app

# Using MSVC
cl /std:c++17 /W4 src/main.cpp /Fe:app.exe && app.exe
```

### CMake Build

#### Build Main Application

```bash
cd behavioral/visitor
cmake -B build
cmake --build build
./build/Debug/visitor.exe      # Windows
./build/visitor                # Linux/Mac
```

#### Build with Google Tests

```bash
cd behavioral/visitor
cmake -B build_tests -DBUILD_TESTS=ON
cmake --build build_tests
./build_tests/test/Debug/visitor_tests.exe   # Windows
./build_tests/test/visitor_tests             # Linux/Mac
```

The test suite includes:
- Visitor interface implementation verification
- StreamVisitor output handling for Person
- StreamVisitor output handling for Car
- Multiple object visitation
- Visitor pattern polymorphism

## Key Concepts

- **Visitor Pattern**: Represents an operation to be performed on elements of an object structure, letting you define new operations without changing the classes of the elements
- **Double Dispatch**: Uses two levels of polymorphism (visitor interface + visitable object interface) to achieve the correct behavior
- **Separation of Concerns**: Operations are separated from object structures; new operations don't require modifying existing classes
- **Extensibility**: New visitors can be added easily by implementing the Visitor interface
- **Open/Closed Principle**: Open for extension (new visitors), closed for modification (existing classes remain unchanged)
