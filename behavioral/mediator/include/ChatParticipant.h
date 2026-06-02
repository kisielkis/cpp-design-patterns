#pragma once

#include <string>

class ChatParticipant {
    private:
        const std::string name;

    public:
        ChatParticipant(const std::string &userName) : name(userName) {};
        const std::string& getName() const {return name;}

        virtual void receive(const std::string &msg) = 0;
};