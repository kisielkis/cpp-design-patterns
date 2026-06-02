#pragma once

#include <string>
#include <iostream>

class ChatUser : public Subscriber {
    private:
        std::string name;
    public:
        ChatUser(std::string nm) : name(nm) {}

        void notify(const std::string &publisherName, const std::string &msg) override {
            std::cout << name << " received msg from: " << publisherName << " msg: " << msg << std::endl;
        }

        std::string getName() override {
            return name;
        }
};