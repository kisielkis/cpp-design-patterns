#include <iostream>

#include "AdminUser.h"
#include "ChatRoom.h"
#include "LogedUser.h"
#include "User.h"

int main() {
    using namespace std;
    ChatRoom chat;
    shared_ptr<User> userAla = make_shared<User>("Ala");
    shared_ptr<AdminUser> adminAdam = make_shared<AdminUser>("Heniek");
    shared_ptr<LogedUser> logedUserBen = make_shared<LogedUser>("Ben");
    shared_ptr<LogedUser> logedUserJohn = make_shared<LogedUser>("John");

    chat.addParticipant(userAla);
    chat.addParticipant(adminAdam);
    chat.addParticipant(logedUserBen);
    chat.addParticipant(logedUserJohn);

    cout << "START:" << endl;
    
    chat.sendMsg("hello", logedUserBen);
    chat.removeParticipant(logedUserJohn);
    chat.sendMsg("welcome", userAla);
    chat.sendMsg("Hi", adminAdam);

    cout << "END" << endl;
    return 0;
}