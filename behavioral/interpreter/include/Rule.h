#pragma once

#include <string>
#include <memory>

struct Packet {
    std::string src_ip;
    std::string dst_ip;
    int dst_port;
    std::string protocol;
};

struct Rule {
    virtual bool evaluate( const Packet &pkt) const = 0;
    virtual ~Rule() = default;
};

struct MatchProtocol : Rule {
    std::string proto;
    explicit MatchProtocol(std::string p) : proto(std::move(p)) {};

    bool evaluate( const Packet &pkt) const override {
        return proto == pkt.protocol;
    }
};

struct MatchPort : Rule {
    int port;
    explicit MatchPort(int p) : port(p) {}

    bool evaluate( const Packet &pkt) const override {
        return port == pkt.dst_port;
    }
};

struct MatchSrcIp : Rule {
    std::string source_ip;
    explicit MatchSrcIp(std::string ip) : source_ip(std::move(ip)) {}

    bool evaluate( const Packet &pkt) const override {
        return pkt.src_ip == source_ip;
    }
};

struct MatchDstIp : Rule {
    std::string destination_ip;
    explicit MatchDstIp(std::string ip) : destination_ip(std::move(ip)) {}

    bool evaluate( const Packet &pkt) const override {
        return pkt.dst_ip == destination_ip;
    }
};
