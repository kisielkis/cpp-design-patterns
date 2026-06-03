#pragma once

#include <memory>
#include <iostream>
#include "State.h"

class Context {
    private:
        std::shared_ptr<State> currentState_;
    public:
        Context(std::shared_ptr<State> initialState) : currentState_(initialState) {}

        void setState(std::shared_ptr<State> state) {
            currentState_ = state;
        }

        std::shared_ptr<State> getState() const {
            return currentState_;
        }

        void processOrder() {
            if (currentState_) {
                std::cout << "Current: " << currentState_->getDescription() << std::endl;
                currentState_->handle(this);
            }
        }
};
