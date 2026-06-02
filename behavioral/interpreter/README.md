# Interpreter

## Task: Packet Filtering Rule Engine

### Scenario

A network firewall needs to evaluate packets against a set of rules. Instead of hardcoding filter logic, the system uses a **rule expression language** that can be parsed into a tree of rules. Each rule can match packet properties (source IP, destination port, protocol) and can be combined with logical operators (AND, OR, NOT).

The **Interpreter pattern** allows building complex rule expressions from simple building blocks and evaluating them against packet data.

Example rule: `"and(src_ip 10.0.0.5,or(port 22,port 443))"`
- Match packets from source IP 10.0.0.5 AND destined to port 22 or 443

### Requirements

1. **Abstract Expression (Rule)** with methods:
   - `evaluate(const Packet &pkt)` — returns true if packet matches the rule

2. **Terminal Expressions** (leaf nodes):
   - `MatchProtocol` — matches packet protocol (tcp, udp, etc.)
   - `MatchPort` — matches destination port
   - `MatchSrcIp` — matches source IP address
   - `MatchDstIp` — matches destination IP address

3. **Non-terminal Expressions** (composite nodes):
   - `And` — evaluates to true if both left and right rules match
   - `Or` — evaluates to true if either left or right rule matches
   - `Not` — evaluates to true if the wrapped rule doesn't match

4. **Context**:
   - `Packet` — contains src_ip, dst_ip, dst_port, protocol

5. **Interpreter (Parser)**:
   - `parse(const std::string &expr)` — parses expression string into Rule tree
   - Supports prefixes: "protocol ", "port ", "src_ip ", "dst_ip "
   - Supports operators: "and(...)", "or(...)", "not(...)"
   - Can handle nested expressions

### Example Output

```
START
pkt1 (block?): 1
pkt2 (block?): 0
pkt3 (block?): 0
END
```

With rule: `"and(src_ip 10.0.0.5,or(port 22,port 443))"`
- pkt1: src=10.0.0.5, dst_port=22  → matches (both conditions true)
- pkt2: src=10.0.0.5, dst_port=80  → doesn't match (port not 22 or 443)
- pkt3: src=1.2.3.4, dst_port=443  → doesn't match (source IP wrong)

## Building & Testing

### With g++

```bash
cd behavioral/interpreter
g++ -std=c++17 -Wall -I include -o app src/main.cpp && ./app
```

### With CMake + Tests

```bash
cd behavioral/interpreter
mkdir build_tests
cd build_tests
cmake -DBUILD_TESTS=ON ..
cmake --build .
./test/Debug/interpreter_tests.exe    # Windows
./test/interpreter_tests              # Linux/macOS
```
