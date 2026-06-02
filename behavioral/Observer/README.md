# Observer

## Task: Chat Group Notification System

### Scenario

A chat application with multiple chat groups. When someone publishes a message in a group, all subscribers (observers) are automatically notified. Users can subscribe to (join) or unsubscribe from (leave) chat groups at any time.

This demonstrates the **Observer Pattern** where:
- **ChatGroup** is the **Subject** (publisher) — maintains state and notifies observers
- **ChatUser** is the **Observer** (subscriber) — updates when subject changes
- Loose coupling: users don't need to know about groups directly

### Requirements

1. **Abstract Publisher interface** with methods:
   - `publish(msg)` — broadcasts message to all subscribers
   - `subscribe(user)` — adds observer to notify list
   - `unSubscribe(user)` — removes observer from notify list

2. **Abstract Subscriber interface** with methods:
   - `notify(publisherName, msg)` — receives notification from publisher
   - `getName()` — returns subscriber identifier

3. **ChatGroup concrete class** that:
   - Maintains list of subscribers
   - Broadcasts messages to all active subscribers
   - Handles subscription/unsubscription

4. **ChatUser concrete class** that:
   - Implements notify to print received messages
   - Can subscribe to multiple groups

5. **Observer Pattern behavior**:
   - Users subscribe to groups
   - When group publishes, all subscribers get notified
   - Users can unsubscribe anytime
   - Groups don't depend on user implementation (loose coupling)

### Example Output

```
START:
John received msg from: Fishing club msg: The bream season is starting
Franco received msg from: Fishing club msg: The bream season is starting
Enzo received msg from: Automobile club msg: Niki Lauda is a legend.
Ferruccio received msg from: Automobile club msg: Niki Lauda is a legend.

John received msg from: Fishing club msg: Trout season is starting.
Franco received msg from: Fishing club msg: Trout season is starting.
END
```

## Building & Testing

### With g++

```bash
cd behavioral/Observer
g++ -std=c++17 -Wall -I include -o app src/main.cpp && ./app
```

### With CMake + Tests

```bash
cd behavioral/Observer
mkdir build_tests
cd build_tests
cmake -DBUILD_TESTS=ON ..
cmake --build .
./test/Debug/observer_tests.exe    # Windows
./test/observer_tests              # Linux/macOS
```
