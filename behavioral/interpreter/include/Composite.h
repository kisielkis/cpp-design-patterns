#pragma once

#include <memory>

#include "Rule.h"

struct And : Rule {
    std::shared_ptr<Rule> left, right;
    And(std::shared_ptr<Rule> l, std::shared_ptr<Rule> r) : left(std::move(l)), right(std::move(r)) {}

    bool evaluate( const Packet &pkt) const override {
        return left->evaluate(pkt) && right->evaluate(pkt);
    }
};

struct Or : Rule {
    std::shared_ptr<Rule> left, right;
    Or(std::shared_ptr<Rule> l, std::shared_ptr<Rule> r) : left(std::move(l)), right(std::move(r)) {}

    bool evaluate( const Packet &pkt) const override {
        return left->evaluate(pkt) || right->evaluate(pkt);
    }
};

struct Not : Rule {
    std::shared_ptr<Rule> rule;
    Not(std::shared_ptr<Rule> ru) : rule(std::move(ru)) {}

    bool evaluate( const Packet &pkt) const override {
        return !rule->evaluate(pkt);
    }
};
