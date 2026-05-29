#pragma once

#include <string>

#include "SupportHandler.h"

class HelpDesk : public SupportHandler {
    public:
        std::string Handle(Priority priority) override {
            if (priority == Priority::LOW) {
                return "Handle LOW priority by HelpDesk";
            } else {
                return SupportHandler::Handle(priority);
            }
        }
};