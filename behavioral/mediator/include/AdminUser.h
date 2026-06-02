#pragma once

#include <iostream>

#include "ChatParticipant.h"

class AdminUser : public ChatParticipant {
    public:
        AdminUser(const std::string &name) : ChatParticipant(name) {}

        void receive(const std::string &msg) {
            std::cout << "AdminUser received:" << msg << std::endl;
        }
};