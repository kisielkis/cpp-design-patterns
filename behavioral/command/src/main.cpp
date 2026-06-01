#include <iostream>

#include "SetMtuCommand.h"
#include "AddBgpRouteCommand.h"
#include "AddVlanCommand.h"
#include "HistoryCommand.h"

int main() {
    using namespace std;

    cout << "START:" << endl;

    HistoryCommand history;

    unique_ptr<Command> cmdMtu = make_unique<SetMtuCommand>(20);
    auto cmdBgp = make_unique<AddBgpRouteCommand>("10.0.0.0/8", "192.168.0.10", 65001);
    auto cmdVlan = make_unique<AddVlanCommand>("12345678");

    if(cmdMtu->execute()) {
        history.push(move(cmdMtu));
    }
    history.rollbackLast();
    if(cmdBgp->execute()) {
        history.push(move(cmdBgp));
    }
    if(cmdVlan->execute()) {
        history.push(move(cmdVlan));
    }
    history.rollbackAll();
    cout << "END" << endl;
    return 0;
}