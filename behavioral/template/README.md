# Template Method Pattern

## Problem Statement

Different communication media (Bluetooth, WiFi, Serial, etc.) need to transmit data, but each media has a different underlying protocol. However, the overall transmission workflow is similar for all:
1. Calculate a checksum for the message
2. Pack the message with frame delimiters (STX/ETX) and checksum
3. Send via the appropriate medium

Rather than duplicating this workflow in each concrete communication class, the Template Method pattern provides a reusable skeleton in the base class, letting subclasses override specific steps.

## Requirements

1. **CommMedia** (abstract base class)
   - Pure virtual `send(msg)` method — subclasses implement actual transmission
   - Pure virtual `receive()` method — subclasses implement reception
   - Concrete `pack(msg)` method — orchestrates checksum calculation and framing
   - Concrete `calcChecksum(msg)` method — can be overridden by subclasses for custom algorithms
   - Protected members: `STX`, `ETX`, `buffer`, `checksum`, `name`

2. **BtComm** (Bluetooth implementation)
   - Implements `send()` — calls `pack()` then outputs formatted message
   - Overrides `pack()` — adds "BT" prefix to frame
   - Default checksum calculation

3. **WiFiComm** (WiFi implementation)
   - Implements `send()` — calls `pack()` then outputs formatted message
   - Overrides `calcChecksum()` — uses fixed "XX" checksum
   - Uses base `pack()` implementation

4. **Supporting members**
   - `STX`, `ETX` — frame delimiters (Start/End of Text)
   - `buffer` — final packed message
   - `checksum` — computed checksum value

## Expected Output

```
START:
[BT] Packing and sending: Hello
SEND via BT: STXHelloHeLLXBT
[WiFi] Packing and sending: Hello
SEND via WiFi: STXHelloXXETX
[BT] Packing and sending: Test
SEND via BT: STXTestTsLLXBT
[WiFi] Packing and sending: Test
SEND via WiFi: STXTestXXETX
END
```

## Compilation

### Direct Compilation (no CMake)

```bash
# Using g++ (primary)
cd behavioral/template
g++ -std=c++17 -Wall -o app src/main.cpp && ./app

# Using MSVC
cl /std:c++17 /W4 src/main.cpp /Fe:app.exe && app.exe
```

### CMake Build

#### Build Main Application

```bash
cd behavioral/template
cmake -B build
cmake --build build
./build/Debug/template.exe      # Windows
./build/template                # Linux/Mac
```

#### Build with Google Tests

```bash
cd behavioral/template
cmake -B build_tests -DBUILD_TESTS=ON
cmake --build build_tests
./build_tests/test/Debug/template_tests.exe   # Windows
./build_tests/test/template_tests             # Linux/Mac
```

The test suite includes:
- CommMedia pack/checksum workflow tests
- BtComm frame formatting (BT prefix) validation
- WiFiComm custom checksum (XX fixed) validation
- Inheritance chain verification

## Key Concepts

- **Template Method Pattern**: Defines the skeleton of an algorithm in the base class, deferring specific steps to subclasses
- **Code Reuse**: Common workflow (`pack` orchestration) is not duplicated across subclasses
- **Hook Methods**: Subclasses override specific steps (`calcChecksum`, `send`) without reimplementing the entire workflow
- **Inversion of Control**: The base class controls the sequence; subclasses fill in the details
- **Open/Closed Principle**: Easy to add new communication media without modifying existing classes
