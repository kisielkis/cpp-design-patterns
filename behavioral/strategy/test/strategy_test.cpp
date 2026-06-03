#include <gtest/gtest.h>
#include <memory>
#include <set>
#include "../include/LoadBalancer.h"

class StrategyTest : public ::testing::Test {
protected:
    std::vector<Backend> backends = {
        {"Server1", 0},
        {"Server2", 0},
        {"Server3", 0}
    };

    Request createRequest(uint32_t ip, const std::string& path) {
        return {ip, path};
    }
};

TEST_F(StrategyTest, SmallestLoadStrategySelectsMinLoad) {
    backends[0].activeConnection = 5;
    backends[1].activeConnection = 2;  // Smallest
    backends[2].activeConnection = 8;

    SmallestLoadStrategy strategy;
    Backend& selected = strategy.select(backends, createRequest(123, "api"));

    EXPECT_EQ(selected.name, "Server2");
    EXPECT_EQ(selected.activeConnection, 2);
}

TEST_F(StrategyTest, SmallestLoadStrategySelectsFirstWhenEqual) {
    backends[0].activeConnection = 3;
    backends[1].activeConnection = 3;
    backends[2].activeConnection = 3;

    SmallestLoadStrategy strategy;
    Backend& selected = strategy.select(backends, createRequest(123, "api"));

    EXPECT_EQ(selected.name, "Server1");
}

TEST_F(StrategyTest, SmallestLoadStrategySelectsZeroLoad) {
    backends[0].activeConnection = 1;
    backends[1].activeConnection = 0;  // Zero load
    backends[2].activeConnection = 5;

    SmallestLoadStrategy strategy;
    Backend& selected = strategy.select(backends, createRequest(123, "api"));

    EXPECT_EQ(selected.name, "Server2");
}

TEST_F(StrategyTest, RandomLoadStrategySelectsValidBackend) {
    RandomLoad strategy;

    for (int i = 0; i < 100; ++i) {
        Backend& selected = strategy.select(backends, createRequest(i, "test"));

        bool found = false;
        for (const auto& backend : backends) {
            if (selected.name == backend.name) {
                found = true;
                break;
            }
        }
        EXPECT_TRUE(found) << "RandomLoad selected invalid backend: " << selected.name;
    }
}

TEST_F(StrategyTest, RandomLoadStrategyDistributesAcrossServers) {
    RandomLoad strategy;
    std::set<std::string> selectedServers;

    for (int i = 0; i < 100; ++i) {
        Backend& selected = strategy.select(backends, createRequest(i, "test"));
        selectedServers.insert(selected.name);
    }

    // With 100 samples, we should hit all 3 servers (statistically very likely)
    EXPECT_EQ(selectedServers.size(), 3);
}

TEST_F(StrategyTest, LoadBalancerRoutesWithSmallestLoadStrategy) {
    LoadBalancer balancer(backends, std::make_unique<SmallestLoadStrategy>());

    Request req1{111, "api"};
    Backend& b1 = balancer.route(req1);
    EXPECT_EQ(b1.activeConnection, 1);
    EXPECT_EQ(b1.name, "Server1");

    Request req2{222, "api"};
    Backend& b2 = balancer.route(req2);
    EXPECT_EQ(b2.activeConnection, 1);
    EXPECT_EQ(b2.name, "Server2");  // Different server because Server1 now has 1 connection
}

TEST_F(StrategyTest, LoadBalancerCanSwitchStrategies) {
    LoadBalancer balancer(backends, std::make_unique<SmallestLoadStrategy>());

    Request req1{111, "api"};
    Backend& b1 = balancer.route(req1);
    EXPECT_EQ(b1.name, "Server1");  // Smallest load (all are 0)

    balancer.setStrategy(std::make_unique<RandomLoad>());

    Request req2{222, "api"};
    Backend& b2 = balancer.route(req2);
    // Just verify it's a valid backend
    EXPECT_NE(b2.name, "");
}

TEST_F(StrategyTest, LoadBalancerIncrementsConnectionCount) {
    LoadBalancer balancer(backends, std::make_unique<SmallestLoadStrategy>());

    // Route 4 requests - should distribute: Server1(2), Server2(1), Server3(1)
    Request req1{100, "test"};
    Backend& b1 = balancer.route(req1);
    EXPECT_EQ(b1.activeConnection, 1);

    Request req2{101, "test"};
    Backend& b2 = balancer.route(req2);
    EXPECT_EQ(b2.activeConnection, 1);

    Request req3{102, "test"};
    Backend& b3 = balancer.route(req3);
    EXPECT_EQ(b3.activeConnection, 1);

    // Fourth request goes back to first server (smallest load)
    Request req4{103, "test"};
    Backend& b4 = balancer.route(req4);
    EXPECT_EQ(b4.activeConnection, 2);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
