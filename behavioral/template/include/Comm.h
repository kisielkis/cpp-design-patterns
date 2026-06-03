#pragma once

#include <string>
#include <iostream>

class CommMedia {
    protected:
        std::string STX = "STX";
        std::string ETX = "ETX";
        std::string buffer;
        std::string name;
        std::string checksum;
    public:
        CommMedia(std::string nm) : name(nm) {}
        virtual void send(const std::string &msg) = 0;
        virtual std::string &receive() = 0;

        virtual void pack(const std::string &msg) {
            calcChecksum(msg);
            buffer = STX + msg + checksum + ETX;
        }

        virtual void calcChecksum(const std::string &msg) {
            checksum = msg[0] + msg[msg.size()-1];
        }

};

class BtComm : public CommMedia {
    public:
        BtComm(std::string commName) : CommMedia(commName) {}
        void send(const std::string &msg) {
            pack(msg);
            std::cout << "SEND via BT: "<< buffer << std::endl;
        }

        std::string &receive() {
            return std::string("");
        }

        void pack(const std::string &msg) {
            CommMedia::pack(msg);
            buffer = "BT" + buffer;
        }
};

class WiFiComm : public CommMedia {
    public:
        WiFiComm(std::string commName) : CommMedia(commName) {}
        void send(const std::string &msg) {
            pack(msg);
            std::cout << "SEND via WiFi: "<< buffer << std::endl;
        }

        std::string &receive() {
            return std::string("");
        }

        virtual void calcChecksum(const std::string &msg) {
            checksum = "XX";
        }
};