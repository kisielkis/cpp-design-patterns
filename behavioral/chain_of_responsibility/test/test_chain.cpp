#include <gtest/gtest.h>
#include <memory>

#include "HelpDesk.h"
#include "TechnicalSupport.h"
#include "Developer.h"
#include "Manager.h"

class FullChainTest : public ::testing::Test {
    protected:
        std::shared_ptr<HelpDesk> head;

    public:
        void SetUp() override {
            head = std::make_shared<HelpDesk>();
            auto tech = std::make_shared<TechnicalSupport>();
            auto dev = std::make_shared<Developer>();
            auto man = std::make_shared<Manager>();

            head->SetNext(tech)->SetNext(dev)->SetNext(man);
        }
};

TEST_F(FullChainTest, Low_HandledByHelpDesk) {
    EXPECT_EQ(head->Handle(Priority::LOW), "Handle LOW priority by HelpDesk");
}

TEST_F(FullChainTest, Medium_HandledByTechnicalSupport) {
    EXPECT_EQ(head->Handle(Priority::MEDIUM), "Handle Medium priority by TechnicalSupport");
}

TEST_F(FullChainTest, High_HandledByDeveloper) {
    EXPECT_EQ(head->Handle(Priority::HIGH), "Handle High priority by Developer");
}

TEST_F(FullChainTest, Critical_HandledByManager) {
    EXPECT_EQ(head->Handle(Priority::CRITICAL), "Handle CRITICAL priority by Manager");
}

TEST_F(FullChainTest, None_NotHandled) {
    EXPECT_EQ(head->Handle(Priority::NONE), "NOT HANDLED");
}

TEST(StandaloneTest, HelpDesk_HandlesOwnPriority) {
    auto desk = std::make_shared<HelpDesk>();
    EXPECT_EQ(desk->Handle(Priority::LOW), "Handle LOW priority by HelpDesk");
}

TEST(StandaloneTest, HelpDesk_ReturnsNotHandled_WhenNoNext) {
    auto desk = std::make_shared<HelpDesk>();
    EXPECT_EQ(desk->Handle(Priority::HIGH), "NOT HANDLED");
}

TEST(PartialChainTest, StopsAtEndOfChain) {
    auto desk = std::make_shared<HelpDesk>();
    auto tech = std::make_shared<TechnicalSupport>();
    desk->SetNext(tech);

    EXPECT_EQ(desk->Handle(Priority::HIGH), "NOT HANDLED");
}

TEST(PartialChainTest, DelegatesWithinChain) {
    auto desk = std::make_shared<HelpDesk>();
    auto tech = std::make_shared<TechnicalSupport>();
    desk->SetNext(tech);

    EXPECT_EQ(desk->Handle(Priority::MEDIUM), "Handle Medium priority by TechnicalSupport");
}
