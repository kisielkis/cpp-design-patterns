#pragma once

#include <iostream>

#include "ChatParticipant.h"

class LogedUser : public ChatParticipant {
    public:
        LogedUser(const std::string &name) : ChatParticipant(name) {}

        void receive(const std::string &msg) {
            std::cout << "LogedUser received:" << msg << std::endl;
        }
};