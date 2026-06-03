# Strategy Pattern

## Problem Statement

A load balancer needs to distribute incoming requests among multiple backend servers using different algorithms. The algorithm should be selectable at runtime without modifying the load balancer code itself. Different scenarios may require different strategies:
- Smallest Load: route to the server with fewest active connections
- Random: distribute evenly across all servers
- Future strategies (round-robin, weighted, etc.) should be easy to add

## Requirements

1. **IstrategyInterface** (abstract base)
   - Pure virtual `select(backends, request)` method
   - Returns reference to selected Backend

2. **SmallestLoadStrategy** (concrete strategy)
   - Selects backend with minimum `activeConnection` count
   - Implements load-aware routing

3. **RandomLoad** (concrete strategy)
   - Randomly selects a backend from available options
   - Provides uniform distribution

4. **LoadBalancer** (context class)
   - Stores current strategy as `std::unique_ptr<IstrategyInterface>`
   - `route(request)` delegates to strategy and increments selected backend's connection count
   - `setStrategy(strategy)` allows runtime algorithm switching

5. **Backend** (entity)
   - Stores server name and active connection count

6. **Request** (entity)
   - Contains client IP and request path

## Expected Output

```
START:
client: 123 req: api route to: Thor contains active conn: 1
client: 456 req: api route to: Thor contains active conn: 2
client: 789 req: api route to: Thor contains active conn: 3
client: 111 req: rrr route to: Freya contains active conn: 4
client: 222 req: rrr route to: Odin contains active conn: 5
client: 333 req: ddd route to: Thor contains active conn: 4
client: 444 req: ddd route to: [random backend] contains active conn: [varies]
New strategy! Random Load
client: 123 req: api route to: [random backend] contains active conn: [varies]
client: 456 req: api route to: [random backend] contains active conn: [varies]
client: 789 req: api route to: [random backend] contains active conn: [varies]
client: 111 req: rrr route to: [random backend] contains active conn: [varies]
client: 222 req: rrr route to: [random backend] contains active conn: [varies]
client: 333 req: ddd route to: [random backend] contains active conn: [varies]
client: 444 req: ddd route to: [random backend] contains active conn: [varies]
END
```

## Compilation

### Direct Compilation (no CMake)

```bash
# Using g++ (primary)
cd behavioral/strategy
g++ -std=c++17 -Wall -o app src/main.cpp && ./app

# Using MSVC
cl /std:c++17 /W4 src/main.cpp /Fe:app.exe && app.exe
```

### CMake Build

#### Build Main Application

```bash
cd behavioral/strategy
cmake -B build
cmake --build build
./build/Debug/strategy.exe      # Windows
./build/strategy                # Linux/Mac
```

#### Build with Google Tests

```bash
cd behavioral/strategy
cmake -B build_tests -DBUILD_TESTS=ON
cmake --build build_tests
./build_tests/test/Debug/strategy_tests.exe   # Windows
./build_tests/test/strategy_tests             # Linux/Mac
```

The test suite includes:
- SmallestLoadStrategy selection tests
- RandomLoad distribution tests
- LoadBalancer routing and strategy switching tests
- Connection counter increment validation

All 8 tests verify correct load balancing behavior and strategy polymorphism.

## Key Concepts

- **Strategy Pattern**: Encapsulates algorithms in separate classes with a common interface
- **Runtime Selection**: Strategies can be swapped without client code changes
- **Polymorphism**: LoadBalancer uses base class pointer, doesn't care about concrete strategy
- **Open/Closed Principle**: Easy to add new strategies without modifying existing code
