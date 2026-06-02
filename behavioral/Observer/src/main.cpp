#include <iostream>
#include <memory>

#include "ChatGroup.h"
#include "ChatUser.h"

int main() {
    using namespace std;

    auto firstGroup = make_shared<ChatGroup>("Fishing club");
    auto secondGroup = make_shared<ChatGroup>("Automobile club");

    auto user1 = make_shared<ChatUser>("Enzo");
    auto user2 = make_shared<ChatUser>("Ferruccio");
    auto user3 = make_shared<ChatUser>("John");
    auto user4 = make_shared<ChatUser>("Franco");

    firstGroup->subscribe(user2);
    firstGroup->subscribe(user3);
    firstGroup->subscribe(user4);

    secondGroup->subscribe(user1);
    secondGroup->subscribe(user2);
    
    cout << "START:" << endl;
    firstGroup->publish("The bream season is starting");
    secondGroup->publish("Niki Lauda is a legend.");

    firstGroup->unSubscribe(user2);

    firstGroup->publish("Trout season is starting.");
   
    cout << "END" << endl;
    return 0;
}