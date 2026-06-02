#pragma once

#include <algorithm>
#include <vector>
#include <iostream>

#include "Publisher.h"

class ChatGroup : public Publisher {
    private:
        std::string chatName;
        std::vector<std::shared_ptr<Subscriber>> participants;

    public:
        ChatGroup(const std::string &name) : chatName(name) {}

        void publish(const std::string &msg) override {
            for (const auto &user : participants) {
                user->notify(chatName, msg);
            }
            std::cout << std::endl;
        }

        bool subscribe(const std::shared_ptr<Subscriber> &user) override {
            auto found = std::find(participants.begin(), participants.end(), user);
            if (found != participants.end()) {
                return false;
            }
            participants.push_back(user);
            return true;
        }

        bool unSubscribe(const std::shared_ptr<Subscriber> &user) override {
            auto oldSize = participants.size();
            participants.erase(std::remove_if(participants.begin(), participants.end(), [user] (const std::shared_ptr<Subscriber> &up) { return up->getName() == user->getName(); })
                , participants.end());
            return participants.size() < oldSize;
        }
};