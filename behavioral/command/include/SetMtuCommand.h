#pragma once
#include "Command.h"

#include <iostream>

using namespace std;

class SetMtuCommand : public Command {
    private:
        int mtuSize;

    public:
        SetMtuCommand(int mtu) : mtuSize(mtu) {};
        
        void setMtuSize(int mtu) {
            mtuSize = mtu;
        }

        bool execute () override {
            cout << " set MTU size=" << mtuSize << endl;
            return true;
        }

        bool rollback () override {
            cout << " rollback MTU size=" << mtuSize << endl;
            return true;
        }
};