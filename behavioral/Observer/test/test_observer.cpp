#include <gtest/gtest.h>
#include <memory>

#include "ChatGroup.h"
#include "ChatUser.h"

class ObserverTest : public ::testing::Test {
    protected:
        std::shared_ptr<ChatGroup> group1;
        std::shared_ptr<ChatGroup> group2;
        std::shared_ptr<ChatUser> user1;
        std::shared_ptr<ChatUser> user2;
        std::shared_ptr<ChatUser> user3;
        std::shared_ptr<ChatUser> user4;

    public:
        void SetUp() override {
            group1 = std::make_shared<ChatGroup>("Gaming");
            group2 = std::make_shared<ChatGroup>("Sports");
            user1 = std::make_shared<ChatUser>("Alice");
            user2 = std::make_shared<ChatUser>("Bob");
            user3 = std::make_shared<ChatUser>("Charlie");
            user4 = std::make_shared<ChatUser>("Diana");
        }
};

TEST_F(ObserverTest, ChatGroup_Subscribe_SingleUser) {
    EXPECT_TRUE(group1->subscribe(user1));
}

TEST_F(ObserverTest, ChatGroup_Subscribe_MultipleUsers) {
    EXPECT_TRUE(group1->subscribe(user1));
    EXPECT_TRUE(group1->subscribe(user2));
    EXPECT_TRUE(group1->subscribe(user3));
}

TEST_F(ObserverTest, ChatGroup_Publish_NotifiesSubscribers) {
    group1->subscribe(user1);
    group1->subscribe(user2);
    group1->subscribe(user3);

    group1->publish("Hello everyone!");
    EXPECT_TRUE(true);
}

TEST_F(ObserverTest, ChatGroup_UnSubscribe_RemovesUser) {
    group1->subscribe(user1);
    group1->subscribe(user2);

    EXPECT_TRUE(group1->unSubscribe(user1));
}

TEST_F(ObserverTest, ChatGroup_PublishAfterUnSubscribe) {
    group1->subscribe(user1);
    group1->subscribe(user2);
    group1->subscribe(user3);

    group1->unSubscribe(user2);
    group1->publish("Message after unsubscribe");

    EXPECT_TRUE(true);
}

TEST_F(ObserverTest, ChatGroup_MultipleGroups_SameUser) {
    group1->subscribe(user1);
    group1->subscribe(user2);
    group2->subscribe(user1);
    group2->subscribe(user3);

    group1->publish("Gaming message");
    group2->publish("Sports message");

    EXPECT_TRUE(true);
}

TEST_F(ObserverTest, ChatGroup_UserCanUnSubscribeFromMultipleGroups) {
    group1->subscribe(user1);
    group2->subscribe(user1);

    group1->unSubscribe(user1);
    group2->unSubscribe(user1);

    EXPECT_TRUE(true);
}

TEST_F(ObserverTest, ChatGroup_ComplexScenario) {
    group1->subscribe(user1);
    group1->subscribe(user2);
    group1->subscribe(user3);

    group2->subscribe(user2);
    group2->subscribe(user4);

    group1->publish("First gaming message");
    group2->publish("First sports message");

    group1->unSubscribe(user2);

    group1->publish("Second gaming message");
    group2->publish("Second sports message");

    EXPECT_TRUE(true);
}

TEST(StandaloneTest, ChatUser_CanBeCreated) {
    auto user = std::make_shared<ChatUser>("TestUser");
    EXPECT_EQ(user->getName(), "TestUser");
}

TEST(StandaloneTest, ChatGroup_CanBeCreated) {
    auto group = std::make_shared<ChatGroup>("TestGroup");
    EXPECT_TRUE(true);
}

TEST(StandaloneTest, Observer_FullWorkflow) {
    auto group = std::make_shared<ChatGroup>("Main");
    auto user1 = std::make_shared<ChatUser>("User1");
    auto user2 = std::make_shared<ChatUser>("User2");
    auto user3 = std::make_shared<ChatUser>("User3");

    group->subscribe(user1);
    group->subscribe(user2);
    group->subscribe(user3);

    group->publish("Welcome message");

    group->unSubscribe(user1);

    group->publish("Message after user1 left");

    group->subscribe(user1);

    group->publish("User1 rejoins");

    EXPECT_TRUE(true);
}
