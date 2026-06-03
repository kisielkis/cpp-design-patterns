#include <iostream>
#include "LoadBalancer.h"

int main() {
    using namespace std;
    
    std::vector<Backend> backend = {
            {"Freya", 3},
            {"Odin", 4},
            {"Thor", 0},
    };

    LoadBalancer balancer(backend, std::make_unique<SmallestLoadStrategy>());

    std::vector<Request> req = {
        {123,"api"},
        {456,"api"},
        {789,"api"},
        {111,"rrr"},
        {222,"rrr"},
        {333,"ddd"},
        {444,"ddd"},
    };

    cout << "START:" << endl;
    for (auto pt : req) {
        cout << "client: " << pt.clientIp << " req: " << pt.path;
        Backend &host = balancer.route(pt);
        cout << " route to: " << host.name << " contains active conn: " << host.activeConnection <<endl;
    }
    balancer.setStrategy(std::make_unique<RandomLoad>());
    cout << "New strategy! Random Load" << endl;
    for (auto pt : req) {
        cout << "client: " << pt.clientIp << " req: " << pt.path;
        Backend &host = balancer.route(pt);
        cout << " route to: " << host.name << " contains active conn: " << host.activeConnection <<endl;
    }
    cout << "END" << endl;
    return 0;
}
