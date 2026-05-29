#pragma once

#include <string>

#include "Ticket.h"


/**
 * pure virtual - abstract class
 */
class Handler {
    public:
        virtual Handler *SetNext(Handler *handler) = 0;
        virtual std::string Handle(Priority priority) = 0;
};

class SupportHandler : public Handler {
    private:
        Handler *next_handler;

    public:
        Handler *SetNext(Handler *handler) override {
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
