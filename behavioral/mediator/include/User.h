#pragma once

#include <iostream>

#include "ChatParticipant.h"

class User : public ChatParticipant {
    public:
        User(const std::string &name) : ChatParticipant(name) {}

        void receive(const std::string &msg) {
            std::cout << "User received:" << msg << std::endl;
        }
};