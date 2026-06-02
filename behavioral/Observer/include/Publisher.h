#pragma once

#include <string>
#include <memory>

#include "Subscriber.h"

class Publisher {
    public:
        virtual ~Publisher() = default;
        virtual void publish(const std::string &msg) = 0;
        virtual bool subscribe(const std::shared_ptr<Subscriber> &user) = 0;
        virtual bool unSubscribe(const std::shared_ptr<Subscriber> &user) = 0;
};