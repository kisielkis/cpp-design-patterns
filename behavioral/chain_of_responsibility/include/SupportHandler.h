#pragma once

#include <string>
#include <memory>

#include "Ticket.h"


/**
 * pure virtual - abstract class
 */
class Handler {
    public:
        virtual std::shared_ptr<Handler> SetNext(const std::shared_ptr<Handler> &handler) = 0;
        virtual std::string Handle(Priority priority) = 0;
};

class SupportHandler : public Handler {
    private:
        std::shared_ptr<Handler> next_handler;

    public:
        std::shared_ptr<Handler> SetNext(const std::shared_ptr<Handler> &handler) override {
            this->next_handler = handler;
            return handler;
        }

        std::string Handle(Priority priority) override {
            if (this->next_handler) {
                return this->next_handler->Handle(priority);
            }
            return "NOT HANDLED";
        }
};
