#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>

struct Backend {
    std::string name;
    int activeConnection;
};

struct Request {
    uint32_t clientIp;
    std::string path;
};

struct IstrategyInterface {
    virtual ~IstrategyInterface() = default;
    virtual Backend& select(std::vector<Backend> &backends, const Request &req) = 0;
};

struct SmallestLoadStrategy : public IstrategyInterface {
    Backend& select(std::vector<Backend> &backends, const Request &req) override {
        return *std::min_element(backends.begin(), backends.end(), 
            [] (const Backend &a, const Backend &b) {
                return a.activeConnection < b.activeConnection;
            }
        );
    }
};

struct RandomLoad : public IstrategyInterface {
    Backend& select(std::vector<Backend> &backends, const Request &req) override {
        static std::mt19937 gen(std::random_device{}());
        std::uniform_int_distribution<> dis(0, backends.size() - 1);
        return backends[dis(gen)];
    }
};

class LoadBalancer {
    private:
        std::vector<Backend> backends_;
        std::unique_ptr<IstrategyInterface> strategy_;
    public:
        LoadBalancer(std::vector<Backend> backends, std::unique_ptr<IstrategyInterface> strategy) :
            backends_(move(backends)),
            strategy_(move(strategy)) {}

        void setStrategy(std::unique_ptr<IstrategyInterface> strategy) {
            strategy_ = move(strategy);
        }

        Backend &route(const Request &req) {
            Backend &ret = strategy_->select(backends_, req);
            ret.activeConnection++;
            return ret;
        }

};