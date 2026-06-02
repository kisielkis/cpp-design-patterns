#pragma once

#include <iostream>

#include "ChatParticipant.h"

class AdminUser : public ChatParticipant {
    public:
        AdminUser(const std::string &name) : ChatParticipant(name) {}

        bool isLogged() const noexcept override { return true; }
        void receive(const std::string &msg) override {
            std::cout << "AdminUser received:" << msg << std::endl;
        }
};