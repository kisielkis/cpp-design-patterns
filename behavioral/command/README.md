# Command

## Task: Network Configuration Commands with Undo

### Scenario

A network administrator needs to configure various network settings (MTU, VLAN, BGP routes). Each configuration change must be:
- **Executable** — apply the setting
- **Reversible** — undo/rollback the change
- **Traceable** — maintain history of all commands executed

Commands are queued in history and can be individually rolled back or all rolled back at once.

### Requirements

1. **Abstract Command class** with methods:
   - `execute()` — performs the command action
   - `rollback()` — reverts the command

2. **Concrete command implementations** for:
   - `SetMtuCommand` — sets Maximum Transmission Unit size
   - `AddVlanCommand` — adds a VLAN tag
   - `AddBgpRouteCommand` — adds a BGP route (network, next hop, AS number)

3. **HistoryCommand class** to:
   - Store executed commands in a stack
   - `push()` — adds a command to history
   - `rollbackLast()` — undoes the last command
   - `rollbackAll()` — undoes all commands in reverse order

4. **Execute commands and test rollback functionality** in main()

### Example Output

```
START:
 set MTU size=20
 rollback MTU size=20
 add BGP route network=10.0.0.0/8 nextHop=192.168.0.10 AS=65001
 add VlanTag=12345678
 rollback VlanTag=12345678
 rollback BGP route network=10.0.0.0/8 nextHop=192.168.0.10 AS=65001
END
```

## Building & Testing

### With g++

```bash
cd behavioral/command
g++ -std=c++17 -Wall -I include -o app src/main.cpp && ./app
```

### With CMake + Tests

```bash
cd behavioral/command
mkdir build_tests
cd build_tests
cmake -DBUILD_TESTS=ON ..
cmake --build .
./test/Debug/command_tests.exe    # Windows
./test/command_tests              # Linux/macOS
```
