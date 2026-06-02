# Mediator

## Task: Chat Room Messaging System

### Scenario

A chat application needs to manage communication between multiple users. Instead of users communicating directly with each other (which creates complex dependencies), all messages go through a central **ChatRoom** (mediator). The mediator handles message routing, filtering, and logging.

Users in the chat room:

- Send messages through the mediator (ChatRoom)
- Receive messages from other participants
- Can join (addParticipant) or leave (removeParticipant) the chat

### Requirements

1. **Abstract ChatMediator interface** with methods:

   - `sendMsg()` — sends message from one participant to others
   - `addParticipant()` — adds user to the chat room
   - `removeParticipant()` — removes user from the chat room
2. **ChatRoom concrete class** that:

   - Maintains list of participants
   - Routes messages to all participants except sender
   - Tracks message IDs sequentially
   - Special handling for first-time users (sends "First LOGIN!" greeting)
3. **Abstract ChatParticipant base class** with:

   - `name` — user identifier
   - `receive()` — receives message from mediator
4. **Concrete participant types**:

   - `User` — standard user
   - `AdminUser` — administrator with special privileges
   - `LogedUser` — regular logged-in user
5. **Functionality**:

   - Create chat room and add participants
   - Send messages that are routed to all except sender
   - Remove participants and continue chatting
   - All communication goes through mediator

### Example Output

```
START:
User received:hello
AdminUser received:hello
LogedUser received:hello
User received:First LOGIN!
AdminUser received:welcome
LogedUser received:welcome
User received:Hi
LogedUser received:Hi
END
```

## Building & Testing

### With g++

```bash
cd behavioral/mediator
g++ -std=c++17 -Wall -I include -o app src/main.cpp && ./app
```

### With CMake + Tests 

```bash
cd behavioral/mediator
mkdir build_tests
cd build_tests
cmake -DBUILD_TESTS=ON ..
cmake --build .
./test/Debug/mediator_tests.exe    # Windows
./test/mediator_tests              # Linux/macOS
```
