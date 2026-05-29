#pragma once

#include <string>

#include "SupportHandler.h"

class TechnicalSupport : public SupportHandler {
    public:
        std::string Handle(Priority priority) override {
            if (priority == Priority::MEDIUM) {
                return "Handle Medium priority by TechnicalSupport";
            } else {
                return SupportHandler::Handle(priority);
            }
        }
};