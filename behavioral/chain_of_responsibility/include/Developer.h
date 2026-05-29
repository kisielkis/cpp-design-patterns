#pragma once

#include <string>

#include "SupportHandler.h"

class Developer : public SupportHandler {
    public:
        std::string Handle(Priority priority) override {
            if (priority == Priority::HIGH) {
                return "Handle High priority by Developer";
            } else {
                return SupportHandler::Handle(priority);
            }
        }
};