#pragma once

#include <string>
#include <memory>

#include "ChatParticipant.h"

// abstract class
class ChatMediator {
    public:
        virtual ~ChatMediator() = default;
        virtual void sendMsg(const std::string &msg , const std::shared_ptr<ChatParticipant> &sender) = 0;
        virtual void addParticipant(const std::shared_ptr<ChatParticipant> &user) = 0;
        virtual void removeParticipant(const std::shared_ptr<ChatParticipant> &user) = 0;
};
