#include <iostream>
#include "Context.h"

int main() {
    using namespace std;

    auto context = make_shared<Context>(make_shared<NewOrderState>());

    cout << "=== State Pattern: Order Processing ===" << endl << endl;

    context->processOrder();
    cout << endl;

    context->processOrder();
    cout << endl;

    context->processOrder();
    cout << endl;

    context->processOrder();

    cout << endl << "=== Process Complete ===" << endl;

    return 0;
}
