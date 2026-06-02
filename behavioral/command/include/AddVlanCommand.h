#pragma once

#include <string>
#include <iostream>

#include "Command.h"


class AddVlanCommand : public Command {
    private:
        std::string VlanTag;
    public:
        AddVlanCommand(const std::string &Vlan) : VlanTag(Vlan) {};

        bool execute() override {
            std::cout << " add VlanTag=" << VlanTag << std::endl;
            return true;
        }
         bool rollback() override {
            std::cout << " rollback VlanTag=" << VlanTag << std::endl;
            return true;
        }
};