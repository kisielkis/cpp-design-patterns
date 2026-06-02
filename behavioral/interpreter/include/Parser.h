#pragma once
#include <stdexcept>
#include <memory>

#include "Rule.h"
#include "Composite.h"

inline std::shared_ptr<Rule> parse(const std::string &expr) {
    if ( expr.compare(0, 9, "protocol ") == 0) {
        return std::make_shared<MatchProtocol>(expr.substr(9));
    }

    if (expr.compare(0, 5, "port ") == 0) {
        return std::make_shared<MatchPort>(std::stoi(expr.substr(5)));
    }

    if ( expr.compare(0, 7, "src_ip ") == 0) {
        return std::make_shared<MatchSrcIp>(expr.substr(7));
    }

    if ( expr.compare(0, 7, "dst_ip ") == 0) {
        return std::make_shared<MatchDstIp>(expr.substr(7));
    }

    if ( expr.compare(0, 4, "not(") == 0) {
        auto inner = expr.substr(4, expr.size() - 5);
        return std::make_shared<Not>(parse(inner));
    }

    if ( expr.compare(0, 4, "and(") == 0) {
         auto inner = expr.substr(4, expr.size() - 5);
         int depth = 0;
         size_t split = 0;
         for (size_t i =0; i < inner.size(); i++) {
            if (inner[i] == '(') depth++;
            if (inner[i] == ')') depth--;
            if (inner[i] == ',' && depth == 0) {
                split = i;
                break;
            } 
         }
         return std::make_shared<And>(
            parse(inner.substr(0,split)), 
            parse(inner.substr(split+1))
        );
    }

    if ( expr.compare(0, 3, "or(") == 0) {
         auto inner = expr.substr(3, expr.size() - 4);
         int depth = 0;
         size_t split = 0;
         for (size_t i =0; i < inner.size(); i++) {
            if (inner[i] == '(') depth++;
            if (inner[i] == ')') depth--;
            if (inner[i] == ',' && depth == 0) {
                split = i;
                break;
            } 
         }
         return std::make_shared<Or>(
            parse(inner.substr(0,split)), 
            parse(inner.substr(split+1))
        );
    }

    throw std::runtime_error("Unknown rule: " + expr);
}