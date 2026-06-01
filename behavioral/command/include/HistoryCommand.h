#pragma once

#include <memory>
#include <stack>

#include "Command.h"

class HistoryCommand {
    private:
        std::stack<std::unique_ptr<Command>> stackHistory;
    public:
        void push(std::unique_ptr<Command>&& cmd) {
            stackHistory.push(move(cmd));
        }

        bool rollbackLast() {
            if (stackHistory.empty()) {
                return false;
            }
            stackHistory.top()->rollback();
            stackHistory.pop();
            return true;
        }
        
        void rollbackAll() {
            while(!stackHistory.empty()) {
                stackHistory.top()->rollback();
                stackHistory.pop();
            }
        }
};