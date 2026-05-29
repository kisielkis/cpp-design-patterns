#pragma once

#include <string>

#include "SupportHandler.h"

class Manager : public SupportHandler {
    public:
        std::string Handle(Priority priority) override {
            if (priority == Priority::CRITICAL) {
                return "Handle CRITICAL priority by Manager";
            } else {
                return SupportHandler::Handle(priority);
            }
        }
};