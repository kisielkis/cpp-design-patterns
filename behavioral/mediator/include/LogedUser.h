#pragma once

#include <iostream>

#include "ChatParticipant.h"

class LogedUser : public ChatParticipant {
    public:
        LogedUser(const std::string &name) : ChatParticipant(name) {}

        bool isLogged() const noexcept override { return true; }
        void receive(const std::string &msg) override {
            std::cout << "LogedUser received:" << msg << std::endl;
        }
};