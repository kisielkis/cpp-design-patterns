#include <gtest/gtest.h>
#include <memory>

#include "Context.h"

class StatePatternTest : public ::testing::Test {
    protected:
        std::shared_ptr<Context> context;

        void SetUp() override {
            context = std::make_shared<Context>(std::make_shared<NewOrderState>());
        }
};

TEST_F(StatePatternTest, InitialStateIsNewOrderState) {
    auto state = context->getState();
    EXPECT_EQ(state->getDescription(), "New Order Received");
}

TEST_F(StatePatternTest, StateTransitionsToProcessing) {
    context->processOrder();
    auto state = context->getState();
    EXPECT_EQ(state->getDescription(), "Processing Order");
}

TEST_F(StatePatternTest, StateTransitionsToInTransit) {
    context->processOrder();  // NewOrder -> Processing
    context->processOrder();  // Processing -> InTransit
    auto state = context->getState();
    EXPECT_EQ(state->getDescription(), "Order In Transit");
}

TEST_F(StatePatternTest, StateTransitionsToDelivered) {
    context->processOrder();  // NewOrder -> Processing
    context->processOrder();  // Processing -> InTransit
    context->processOrder();  // InTransit -> Delivered
    auto state = context->getState();
    EXPECT_EQ(state->getDescription(), "Order Delivered");
}

TEST_F(StatePatternTest, FinalStateRemainsDelivered) {
    context->processOrder();  // NewOrder -> Processing
    context->processOrder();  // Processing -> InTransit
    context->processOrder();  // InTransit -> Delivered
    context->processOrder();  // Delivered (no transition)
    auto state = context->getState();
    EXPECT_EQ(state->getDescription(), "Order Delivered");
}

TEST_F(StatePatternTest, AllStatesHaveValidDescriptions) {
    auto newOrder = std::make_shared<NewOrderState>();
    EXPECT_FALSE(newOrder->getDescription().empty());

    auto processing = std::make_shared<ProcessingState>();
    EXPECT_FALSE(processing->getDescription().empty());

    auto inTransit = std::make_shared<InTransitState>();
    EXPECT_FALSE(inTransit->getDescription().empty());

    auto delivered = std::make_shared<DeliveredState>();
    EXPECT_FALSE(delivered->getDescription().empty());
}

TEST_F(StatePatternTest, CanSetStateDirectly) {
    auto deliveredState = std::make_shared<DeliveredState>();
    context->setState(deliveredState);
    EXPECT_EQ(context->getState()->getDescription(), "Order Delivered");
}

TEST_F(StatePatternTest, StateSequenceIsCorrect) {
    std::vector<std::string> expectedSequence = {
        "New Order Received",
        "Processing Order",
        "Order In Transit",
        "Order Delivered"
    };

    for (size_t i = 0; i < expectedSequence.size(); ++i) {
        EXPECT_EQ(context->getState()->getDescription(), expectedSequence[i])
            << "Mismatch at step " << i;
        if (i < expectedSequence.size() - 1) {
            context->processOrder();
        }
    }
}
