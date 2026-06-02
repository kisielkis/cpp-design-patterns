#pragma once

#include <iostream>

#include "ChatParticipant.h"

class User : public ChatParticipant {
    public:
        User(const std::string &name) : ChatParticipant(name) {}

        bool isLogged() const noexcept override { return false; }
        void receive(const std::string &msg) override {
            std::cout << "User received:" << msg << std::endl;
        }
};