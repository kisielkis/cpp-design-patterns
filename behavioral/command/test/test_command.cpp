#include <gtest/gtest.h>
#include <memory>

#include "Command.h"
#include "SetMtuCommand.h"
#include "AddBgpRouteCommand.h"
#include "AddVlanCommand.h"
#include "HistoryCommand.h"

class CommandTest : public ::testing::Test {
    protected:
        HistoryCommand history;

    public:
        void SetUp() override {
            history = HistoryCommand();
        }
};

TEST_F(CommandTest, SetMtuCommand_ExecuteReturnsTrue) {
    auto cmd = std::make_unique<SetMtuCommand>(1500);
    EXPECT_TRUE(cmd->execute());
}

TEST_F(CommandTest, SetMtuCommand_RollbackReturnsTrue) {
    auto cmd = std::make_unique<SetMtuCommand>(1500);
    cmd->execute();
    EXPECT_TRUE(cmd->rollback());
}

TEST_F(CommandTest, AddBgpRouteCommand_ExecuteReturnsTrue) {
    auto cmd = std::make_unique<AddBgpRouteCommand>("10.0.0.0/8", "192.168.1.1", 65001);
    EXPECT_TRUE(cmd->execute());
}

TEST_F(CommandTest, AddBgpRouteCommand_RollbackReturnsTrue) {
    auto cmd = std::make_unique<AddBgpRouteCommand>("10.0.0.0/8", "192.168.1.1", 65001);
    cmd->execute();
    EXPECT_TRUE(cmd->rollback());
}

TEST_F(CommandTest, AddVlanCommand_ExecuteReturnsTrue) {
    auto cmd = std::make_unique<AddVlanCommand>("100");
    EXPECT_TRUE(cmd->execute());
}

TEST_F(CommandTest, AddVlanCommand_RollbackReturnsTrue) {
    auto cmd = std::make_unique<AddVlanCommand>("100");
    cmd->execute();
    EXPECT_TRUE(cmd->rollback());
}

TEST_F(CommandTest, HistoryCommand_PushAndRollbackLast) {
    auto cmd = std::make_unique<SetMtuCommand>(2000);
    EXPECT_TRUE(cmd->execute());
    history.push(std::move(cmd));

    EXPECT_TRUE(history.rollbackLast());
}

TEST_F(CommandTest, HistoryCommand_RollbackLastReturnsFalse_WhenEmpty) {
    EXPECT_FALSE(history.rollbackLast());
}

TEST_F(CommandTest, HistoryCommand_PushMultipleCommands) {
    auto cmd1 = std::make_unique<SetMtuCommand>(1500);
    auto cmd2 = std::make_unique<AddVlanCommand>("200");

    EXPECT_TRUE(cmd1->execute());
    EXPECT_TRUE(cmd2->execute());

    history.push(std::move(cmd1));
    history.push(std::move(cmd2));

    EXPECT_TRUE(history.rollbackLast());
}

TEST_F(CommandTest, HistoryCommand_RollbackAllExecutesInReverseOrder) {
    auto cmd1 = std::make_unique<SetMtuCommand>(1500);
    auto cmd2 = std::make_unique<AddBgpRouteCommand>("172.16.0.0/12", "192.168.1.254", 65000);
    auto cmd3 = std::make_unique<AddVlanCommand>("300");

    EXPECT_TRUE(cmd1->execute());
    EXPECT_TRUE(cmd2->execute());
    EXPECT_TRUE(cmd3->execute());

    history.push(std::move(cmd1));
    history.push(std::move(cmd2));
    history.push(std::move(cmd3));

    history.rollbackAll();
}

TEST(StandaloneTest, SetMtuCommand_DifferentSizes) {
    auto cmd1 = std::make_unique<SetMtuCommand>(500);
    auto cmd2 = std::make_unique<SetMtuCommand>(9000);

    EXPECT_TRUE(cmd1->execute());
    EXPECT_TRUE(cmd2->execute());
}

TEST(StandaloneTest, AddBgpRouteCommand_MultipleRoutes) {
    auto cmd1 = std::make_unique<AddBgpRouteCommand>("10.0.0.0/8", "192.168.1.1", 65001);
    auto cmd2 = std::make_unique<AddBgpRouteCommand>("172.16.0.0/12", "192.168.1.2", 65002);

    EXPECT_TRUE(cmd1->execute());
    EXPECT_TRUE(cmd2->execute());
}

TEST(StandaloneTest, AddVlanCommand_DifferentVlans) {
    auto cmd1 = std::make_unique<AddVlanCommand>("100");
    auto cmd2 = std::make_unique<AddVlanCommand>("200");
    auto cmd3 = std::make_unique<AddVlanCommand>("300");

    EXPECT_TRUE(cmd1->execute());
    EXPECT_TRUE(cmd2->execute());
    EXPECT_TRUE(cmd3->execute());
}
