# State Pattern

## Problem

An object (e.g., Order) needs to change its behavior based on its internal state. The behavior should change dynamically at runtime, and the object should delegate to different implementations based on the current state.

**Challenge:** Managing complex conditional logic (if/switch statements) based on state leads to tight coupling and difficult maintenance.

## Solution

The **State Pattern** encapsulates state-specific behavior into separate classes. The context object delegates to the current state, which can transition the context to a new state.

### Key Components

- **Context** — maintains a reference to a State object; delegates requests to the current state
- **State** — abstract interface defining behavior for a specific state
- **ConcreteState** — implements behavior for a particular state; may trigger transitions

## Implementation

### Structure

```
Context (Order)
  └─ currentState: State
      ├─ NewOrderState
      ├─ ProcessingState
      ├─ InTransitState
      └─ DeliveredState
```

### Workflow

1. Context is created with an initial state
2. Client calls `context->processOrder()`
3. Context delegates to `currentState->handle(context)`
4. State performs its logic and may transition the context to the next state
5. Next call to `processOrder()` uses the new state

## Benefits

✓ Eliminates large conditional blocks (if/switch)
✓ State-specific logic is encapsulated in separate classes
✓ Easy to add new states without modifying existing code
✓ State transitions are explicit and managed by states themselves

## Example Output

```
=== State Pattern: Order Processing ===

Current: New Order Received
Transitioning to: Processing

Current: Processing Order
Transitioning to: In Transit

Current: Order In Transit
Transitioning to: Delivered

Current: Order Delivered
Order completed. No further transitions.

=== Process Complete ===
```

## Compilation

### Google Test

```bash
cmake -B build -DBUILD_TESTS=ON
cmake --build build --config Debug
./build/test/Debug/state_tests.exe
```

### Manual Run

```bash
cd behavioral/state
g++ -std=c++17 -Wall -o app src/main.cpp src/State.cpp -I include && ./app
```

Or with CMake:

```bash
cmake -B build && cmake --build build
./build/Debug/state
```
