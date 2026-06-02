#pragma once

#include <string>

class ChatParticipant {
    private:
        const std::string name;

    public:
        ChatParticipant(const std::string &userName) : name(userName) {};
        virtual ~ChatParticipant() = default;

        const std::string& getName() const { return name; }
        virtual bool isLogged() const noexcept { return false; }
        virtual void receive(const std::string &msg) = 0;
};