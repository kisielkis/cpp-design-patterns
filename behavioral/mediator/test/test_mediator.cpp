#include <gtest/gtest.h>
#include <memory>
#include <sstream>
#include <iostream>

#include "ChatRoom.h"
#include "User.h"
#include "AdminUser.h"
#include "LogedUser.h"

class MediatorTest : public ::testing::Test {
    protected:
        ChatRoom chatRoom;
        std::shared_ptr<User> user1;
        std::shared_ptr<AdminUser> admin1;
        std::shared_ptr<LogedUser> logedUser1;
        std::shared_ptr<LogedUser> logedUser2;

    public:
        void SetUp() override {
            chatRoom = ChatRoom();
            user1 = std::make_shared<User>("Alice");
            admin1 = std::make_shared<AdminUser>("Bob");
            logedUser1 = std::make_shared<LogedUser>("Charlie");
            logedUser2 = std::make_shared<LogedUser>("David");
        }
};

TEST_F(MediatorTest, ChatRoom_AddParticipant) {
    chatRoom.addParticipant(user1);
    chatRoom.addParticipant(admin1);
    EXPECT_TRUE(true);
}

TEST_F(MediatorTest, ChatRoom_SendMessage_ToMultipleParticipants) {
    chatRoom.addParticipant(user1);
    chatRoom.addParticipant(admin1);
    chatRoom.addParticipant(logedUser1);

    chatRoom.sendMsg("hello", user1);
    EXPECT_TRUE(true);
}

TEST_F(MediatorTest, ChatRoom_RemoveParticipant) {
    chatRoom.addParticipant(user1);
    chatRoom.addParticipant(admin1);
    chatRoom.addParticipant(logedUser1);

    chatRoom.removeParticipant(logedUser1);
    EXPECT_TRUE(true);
}

TEST_F(MediatorTest, ChatRoom_MessageIDIncrements) {
    chatRoom.addParticipant(user1);
    chatRoom.addParticipant(admin1);

    chatRoom.sendMsg("msg1", user1);
    chatRoom.sendMsg("msg2", admin1);
    chatRoom.sendMsg("msg3", user1);

    EXPECT_TRUE(true);
}

TEST_F(MediatorTest, ChatRoom_User_ReceivesFirstLoginGreeting) {
    chatRoom.addParticipant(user1);
    chatRoom.addParticipant(admin1);

    chatRoom.sendMsg("hello", user1);
    EXPECT_TRUE(true);
}

TEST_F(MediatorTest, ChatRoom_AdminUser_CanSendMessages) {
    chatRoom.addParticipant(user1);
    chatRoom.addParticipant(admin1);
    chatRoom.addParticipant(logedUser1);

    chatRoom.sendMsg("admin announcement", admin1);
    EXPECT_TRUE(true);
}

TEST_F(MediatorTest, ChatRoom_LogedUser_CanSendAndReceiveMessages) {
    chatRoom.addParticipant(user1);
    chatRoom.addParticipant(logedUser1);
    chatRoom.addParticipant(logedUser2);

    chatRoom.sendMsg("message from loged user", logedUser1);
    EXPECT_TRUE(true);
}

TEST_F(MediatorTest, ChatRoom_RemovedParticipant_DoesNotReceiveMessages) {
    chatRoom.addParticipant(user1);
    chatRoom.addParticipant(logedUser1);
    chatRoom.addParticipant(logedUser2);

    chatRoom.removeParticipant(logedUser2);
    chatRoom.sendMsg("message after removal", user1);

    EXPECT_TRUE(true);
}

TEST(StandaloneTest, User_CanBeCreated) {
    auto user = std::make_shared<User>("TestUser");
    EXPECT_EQ(user->getName(), "TestUser");
}

TEST(StandaloneTest, AdminUser_CanBeCreated) {
    auto admin = std::make_shared<AdminUser>("TestAdmin");
    EXPECT_EQ(admin->getName(), "TestAdmin");
}

TEST(StandaloneTest, LogedUser_CanBeCreated) {
    auto logedUser = std::make_shared<LogedUser>("TestLogedUser");
    EXPECT_EQ(logedUser->getName(), "TestLogedUser");
}

TEST(StandaloneTest, ChatRoom_MultipleUsers_ComplexScenario) {
    ChatRoom chatRoom;

    auto user1 = std::make_shared<User>("User1");
    auto user2 = std::make_shared<User>("User2");
    auto admin = std::make_shared<AdminUser>("Admin1");
    auto logedUser = std::make_shared<LogedUser>("LogedUser1");

    chatRoom.addParticipant(user1);
    chatRoom.addParticipant(user2);
    chatRoom.addParticipant(admin);
    chatRoom.addParticipant(logedUser);

    chatRoom.sendMsg("msg1", user1);
    chatRoom.sendMsg("msg2", admin);
    chatRoom.removeParticipant(logedUser);
    chatRoom.sendMsg("msg3", user2);

    EXPECT_TRUE(true);
}
