#pragma once

#include <string>
#include <memory>

class Context;

class State {
    public:
        virtual ~State() = default;
        virtual void handle(Context* context) = 0;
        virtual std::string getDescription() const = 0;
};

class NewOrderState : public State {
    public:
        void handle(Context* context) override;
        std::string getDescription() const override {
            return "New Order Received";
        }
};

class ProcessingState : public State {
    public:
        void handle(Context* context) override;
        std::string getDescription() const override {
            return "Processing Order";
        }
};

class InTransitState : public State {
    public:
        void handle(Context* context) override;
        std::string getDescription() const override {
            return "Order In Transit";
        }
};

class DeliveredState : public State {
    public:
        void handle(Context* context) override;
        std::string getDescription() const override {
            return "Order Delivered";
        }
};
