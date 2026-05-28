# Chain of Responsibility

## Task: Service Ticket Handling System

### Scenario

A company has a three-level support system. A ticket arrives at Level 1 — if the support agent can't handle it, they pass it up. And so on.

| Handler          | Handles  | Passes To         |
| ---------------- | -------- | ----------------- |
| HelpDesk         | LOW      | TechnicalSupport  |
| TechnicalSupport | MEDIUM   | Developer         |
| Developer        | HIGH     | Manager           |
| Manager          | CRITICAL | — (end of chain) |

### Requirements

1. **Abstract SupportHandler class** with methods:

   - `setNext()` — sets the next handler in the chain
   - `handle()` — processes the ticket or passes it forward
2. **Each handler decides**: either handle the ticket or pass it to the next handler
3. **If no one handles it** — print information about missing handler
4. **Build the chain in main()** and process several tickets

### Example Output

```
[Ticket #1] Priority: LOW      → HelpDesk handled it.
[Ticket #2] Priority: HIGH     → HelpDesk passed. TechnicalSupport passed. Developer handled it.
[Ticket #3] Priority: CRITICAL → HelpDesk passed. TechnicalSupport passed. Developer passed. Manager handled it.
```
