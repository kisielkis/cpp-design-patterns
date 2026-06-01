#pragma once

#include <string>
#include <iostream>

#include "Command.h"

using namespace std;

class AddVlanCommand : public Command {
    private:
        string VlanTag;
    public:
        AddVlanCommand(const string &Vlan) : VlanTag(Vlan) {};

        bool execute() override {
            cout << " add VlanTag=" << VlanTag << endl;
            return true;
        }
         bool rollback() override {
            cout << " rollback VlanTag=" << VlanTag << endl;
            return true;
        }
};