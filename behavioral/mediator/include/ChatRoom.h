#pragma once

#include <memory>
#include <vector>
#include <algorithm>
#include <iostream>
#include "ChatMediator.h"
#include "User.h"

class ChatRoom : public ChatMediator {
    private:
        std::vector<std::shared_ptr<ChatParticipant>> participiants;
        int messageIdCounter;

    public:
        ChatRoom() : messageIdCounter(0) {};

        void sendMsg(const std::string &msg , const std::shared_ptr<ChatParticipant> &user) override {
            auto *ptr = dynamic_cast<User*>(user.get());
            if (ptr != nullptr) {
                user->receive("First LOGIN!");
            }
            messageIdCounter++;
            std::string packetMsg = std::to_string(messageIdCounter) + " from "+ user->getName() + ":" + msg ;
            for (const auto &t_user : participiants) {
                if (t_user == user) {
                    continue;
                }
                {
                    t_user->receive(packetMsg);
                }
            }
            std::cout << std::endl;
        }

        void addParticipant(const std::shared_ptr<ChatParticipant> &user) override {
            participiants.push_back(user);
        }

        void removeParticipant(const std::shared_ptr<ChatParticipant> &user) override {
            participiants.erase(
                std::remove(participiants.begin(), participiants.end(), user),
                participiants.end()
            );
        }
};