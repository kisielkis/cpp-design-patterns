#include <iostream>
#include "visitor.hpp"

int main() {
    using namespace std;

    Person john(5, "john");
    Car toyota("corolla", "2.0 Hybrid Dynamic Force", 192);
    StreamVisitor visitor;

    cout << "START" << "\n";

    john.accept(&visitor);
    toyota.accept(&visitor);

    cout << "END";
    return 0;
}
