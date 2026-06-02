#pragma once
#include "Command.h"

#include <iostream>

class SetMtuCommand : public Command {
    private:
        int mtuSize;

    public:
        SetMtuCommand(int mtu) : mtuSize(mtu) {};
        
        void setMtuSize(int mtu) {
            mtuSize = mtu;
        }

        bool execute () override {
            std::cout << " set MTU size=" << mtuSize << std::endl;
            return true;
        }

        bool rollback () override {
            std::cout << " rollback MTU size=" << mtuSize << std::endl;
            return true;
        }
};