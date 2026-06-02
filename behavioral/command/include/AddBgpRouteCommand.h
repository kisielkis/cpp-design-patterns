#pragma once

#include <string>
#include <iostream>

#include "Command.h"

class AddBgpRouteCommand : public Command {
    private:
        std::string network;
        std::string nextHop;
        int asNumber;

    public:
        AddBgpRouteCommand(const std::string &net, const std::string &hop, int as)
            : network(net), nextHop(hop), asNumber(as) {};

        bool execute() override {
            std::cout << " add BGP route network=" << network
                 << " nextHop=" << nextHop
                 << " AS=" << asNumber << std::endl;
            return true;
        }

        bool rollback() override {
            std::cout << " rollback BGP route network=" << network
                 << " nextHop=" << nextHop
                 << " AS=" << asNumber << std::endl;
            return true;
        }
};
