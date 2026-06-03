#include <iostream>

#include "Comm.h"

int main() {
    using namespace std;
    CommMedia *ptr = new BtComm("Bt1");
    CommMedia *ptrWiFI = new WiFiComm("WiFi1");

    cout << "START:" << endl;
    ptr->send("Hello");
    ptrWiFI->send("Welcome");
    cout << "END" << endl;

    delete ptr;
    delete ptrWiFI;
    return 0;
}
