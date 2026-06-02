#include <iostream>

#include "Rule.h"
#include "Parser.h"

int main() {
    using namespace std;
    auto rule = parse("and(src_ip 10.0.0.5,or(port 22,port 443))");

    Packet pkt1 {"10.0.0.5", "192.168.1.1", 22,  "tcp"};
    Packet pkt2 {"10.0.0.5", "192.168.1.1", 80,  "tcp"};
    Packet pkt3 {"1.2.3.4",  "192.168.1.1", 443, "tcp"};

    cout << "START" << "\n";
    std::cout << "pkt1 (block?): " << rule->evaluate(pkt1) << "\n"; // 1
    std::cout << "pkt2 (block?): " << rule->evaluate(pkt2) << "\n"; // 0
    std::cout << "pkt3 (block?): " << rule->evaluate(pkt3) << "\n"; // 0
    cout << "END";

    return 0;
}