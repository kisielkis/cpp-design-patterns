#pragma once

#include <string>

class Subscriber {
    public:
        virtual ~Subscriber() = default;
        virtual void notify(const std::string &publisherName, const std::string &msg) = 0;
        virtual std::string getName() = 0;
};