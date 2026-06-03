#include "State.h"
#include "Context.h"

void NewOrderState::handle(Context* context) {
    std::cout << "Transitioning to: Processing" << std::endl;
    context->setState(std::make_shared<ProcessingState>());
}

void ProcessingState::handle(Context* context) {
    std::cout << "Transitioning to: In Transit" << std::endl;
    context->setState(std::make_shared<InTransitState>());
}

void InTransitState::handle(Context* context) {
    std::cout << "Transitioning to: Delivered" << std::endl;
    context->setState(std::make_shared<DeliveredState>());
}

void DeliveredState::handle(Context* context) {
    std::cout << "Order completed. No further transitions." << std::endl;
}
