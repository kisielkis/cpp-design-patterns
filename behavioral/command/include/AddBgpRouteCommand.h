#pragma once

#include <string>
#include <iostream>

#include "Command.h"

using namespace std;

class AddBgpRouteCommand : public Command {
    private:
        string network;
        string nextHop;
        int asNumber;

    public:
        AddBgpRouteCommand(const string &net, const string &hop, int as)
            : network(net), nextHop(hop), asNumber(as) {};

        bool execute() override {
            cout << " add BGP route network=" << network
                 << " nextHop=" << nextHop
                 << " AS=" << asNumber << endl;
            return true;
        }

        bool rollback() override {
            cout << " rollback BGP route network=" << network
                 << " nextHop=" << nextHop
                 << " AS=" << asNumber << endl;
            return true;
        }
};
