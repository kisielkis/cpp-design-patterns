#include <gtest/gtest.h>
#include <memory>

#include "Rule.h"
#include "Parser.h"
#include "Composite.h"

class InterpreterTest : public ::testing::Test {
protected:
    Packet pkt1{"10.0.0.5", "192.168.1.1", 22, "tcp"};
    Packet pkt2{"10.0.0.5", "192.168.1.1", 80, "tcp"};
    Packet pkt3{"1.2.3.4", "192.168.1.1", 443, "tcp"};
};

class TerminalExpressionsTest : public ::testing::Test {
protected:
    Packet tcp_packet{"10.0.0.5", "192.168.1.1", 22, "tcp"};
    Packet udp_packet{"10.0.0.5", "192.168.1.1", 53, "udp"};
};

class NonTerminalExpressionsTest : public ::testing::Test {
protected:
    Packet pkt{"10.0.0.5", "192.168.1.1", 443, "tcp"};
};

// Terminal Expression Tests

TEST_F(TerminalExpressionsTest, MatchProtocol_TCP_Succeeds) {
    auto rule = std::make_shared<MatchProtocol>("tcp");
    EXPECT_TRUE(rule->evaluate(tcp_packet));
}

TEST_F(TerminalExpressionsTest, MatchProtocol_UDP_Fails) {
    auto rule = std::make_shared<MatchProtocol>("tcp");
    EXPECT_FALSE(rule->evaluate(udp_packet));
}

TEST_F(TerminalExpressionsTest, MatchProtocol_UDP_Succeeds) {
    auto rule = std::make_shared<MatchProtocol>("udp");
    EXPECT_TRUE(rule->evaluate(udp_packet));
}

TEST_F(InterpreterTest, MatchPort_Port22_Succeeds) {
    auto rule = std::make_shared<MatchPort>(22);
    EXPECT_TRUE(rule->evaluate(pkt1));
}

TEST_F(InterpreterTest, MatchPort_Port22_Fails) {
    auto rule = std::make_shared<MatchPort>(22);
    EXPECT_FALSE(rule->evaluate(pkt2));
}

TEST_F(InterpreterTest, MatchPort_Port443_Succeeds) {
    auto rule = std::make_shared<MatchPort>(443);
    EXPECT_TRUE(rule->evaluate(pkt3));
}

TEST_F(InterpreterTest, MatchSrcIp_10_0_0_5_Succeeds) {
    auto rule = std::make_shared<MatchSrcIp>("10.0.0.5");
    EXPECT_TRUE(rule->evaluate(pkt1));
    EXPECT_TRUE(rule->evaluate(pkt2));
}

TEST_F(InterpreterTest, MatchSrcIp_10_0_0_5_Fails) {
    auto rule = std::make_shared<MatchSrcIp>("10.0.0.5");
    EXPECT_FALSE(rule->evaluate(pkt3));
}

TEST_F(InterpreterTest, MatchDstIp_192_168_1_1_Succeeds) {
    auto rule = std::make_shared<MatchDstIp>("192.168.1.1");
    EXPECT_TRUE(rule->evaluate(pkt1));
    EXPECT_TRUE(rule->evaluate(pkt2));
    EXPECT_TRUE(rule->evaluate(pkt3));
}

TEST_F(InterpreterTest, MatchDstIp_Different_IP_Fails) {
    auto rule = std::make_shared<MatchDstIp>("10.0.0.1");
    EXPECT_FALSE(rule->evaluate(pkt1));
}

// Non-Terminal Expression Tests

TEST_F(NonTerminalExpressionsTest, And_BothTrue_Succeeds) {
    auto left = std::make_shared<MatchPort>(443);
    auto right = std::make_shared<MatchSrcIp>("10.0.0.5");
    auto rule = std::make_shared<And>(left, right);
    EXPECT_TRUE(rule->evaluate(pkt));
}

TEST_F(NonTerminalExpressionsTest, And_LeftFalse_Fails) {
    auto left = std::make_shared<MatchPort>(22);
    auto right = std::make_shared<MatchSrcIp>("10.0.0.5");
    auto rule = std::make_shared<And>(left, right);
    EXPECT_FALSE(rule->evaluate(pkt));
}

TEST_F(NonTerminalExpressionsTest, And_RightFalse_Fails) {
    auto left = std::make_shared<MatchPort>(443);
    auto right = std::make_shared<MatchSrcIp>("1.2.3.4");
    auto rule = std::make_shared<And>(left, right);
    EXPECT_FALSE(rule->evaluate(pkt));
}

TEST_F(NonTerminalExpressionsTest, Or_LeftTrue_Succeeds) {
    auto left = std::make_shared<MatchPort>(443);
    auto right = std::make_shared<MatchSrcIp>("1.2.3.4");
    auto rule = std::make_shared<Or>(left, right);
    EXPECT_TRUE(rule->evaluate(pkt));
}

TEST_F(NonTerminalExpressionsTest, Or_RightTrue_Succeeds) {
    auto left = std::make_shared<MatchPort>(22);
    auto right = std::make_shared<MatchSrcIp>("10.0.0.5");
    auto rule = std::make_shared<Or>(left, right);
    EXPECT_TRUE(rule->evaluate(pkt));
}

TEST_F(NonTerminalExpressionsTest, Or_BothFalse_Fails) {
    auto left = std::make_shared<MatchPort>(22);
    auto right = std::make_shared<MatchSrcIp>("1.2.3.4");
    auto rule = std::make_shared<Or>(left, right);
    EXPECT_FALSE(rule->evaluate(pkt));
}

TEST_F(NonTerminalExpressionsTest, Not_RuleTrue_Fails) {
    auto rule_to_negate = std::make_shared<MatchPort>(443);
    auto rule = std::make_shared<Not>(rule_to_negate);
    EXPECT_FALSE(rule->evaluate(pkt));
}

TEST_F(NonTerminalExpressionsTest, Not_RuleFalse_Succeeds) {
    auto rule_to_negate = std::make_shared<MatchPort>(22);
    auto rule = std::make_shared<Not>(rule_to_negate);
    EXPECT_TRUE(rule->evaluate(pkt));
}

// Parser Tests

TEST_F(InterpreterTest, Parse_PortRule) {
    auto rule = parse("port 443");
    EXPECT_TRUE(rule->evaluate(pkt3));
    EXPECT_FALSE(rule->evaluate(pkt1));
}

TEST_F(InterpreterTest, Parse_SrcIpRule) {
    auto rule = parse("src_ip 10.0.0.5");
    EXPECT_TRUE(rule->evaluate(pkt1));
    EXPECT_FALSE(rule->evaluate(pkt3));
}

TEST_F(InterpreterTest, Parse_DstIpRule) {
    auto rule = parse("dst_ip 192.168.1.1");
    EXPECT_TRUE(rule->evaluate(pkt1));
}

TEST_F(InterpreterTest, Parse_ProtocolRule) {
    auto rule = parse("protocol tcp");
    EXPECT_TRUE(rule->evaluate(pkt1));
}

TEST_F(InterpreterTest, Parse_NotRule) {
    auto rule = parse("not(port 80)");
    EXPECT_TRUE(rule->evaluate(pkt1));
}

TEST_F(InterpreterTest, Parse_OrRule_Simple) {
    auto rule = parse("or(port 22,port 443)");
    EXPECT_TRUE(rule->evaluate(pkt1));   // port 22 matches
    EXPECT_FALSE(rule->evaluate(pkt2));  // port 80 doesn't match either
    EXPECT_TRUE(rule->evaluate(pkt3));   // port 443 matches
}

TEST_F(InterpreterTest, Parse_AndRule_Simple) {
    auto rule = parse("and(src_ip 10.0.0.5,port 22)");
    EXPECT_TRUE(rule->evaluate(pkt1));   // both conditions true
    EXPECT_FALSE(rule->evaluate(pkt2));  // port wrong
    EXPECT_FALSE(rule->evaluate(pkt3));  // src_ip wrong
}

TEST_F(InterpreterTest, Parse_ComplexRule_AndWithOr) {
    auto rule = parse("and(src_ip 10.0.0.5,or(port 22,port 443))");
    EXPECT_TRUE(rule->evaluate(pkt1));   // src=10.0.0.5 AND port=22
    EXPECT_FALSE(rule->evaluate(pkt2));  // src=10.0.0.5 BUT port=80
    EXPECT_FALSE(rule->evaluate(pkt3));  // port=443 BUT src!=10.0.0.5
}

TEST_F(InterpreterTest, Parse_NestedOr_InAnd) {
    auto rule = parse("and(src_ip 10.0.0.5,or(port 80,port 443))");
    EXPECT_FALSE(rule->evaluate(pkt1));  // src OK but port 22 not in OR
    EXPECT_TRUE(rule->evaluate(pkt2));   // src OK and port 80 in OR
}

TEST_F(InterpreterTest, Parse_ComplexRule_MultipleNesting) {
    auto rule = parse("and(protocol tcp,or(port 22,port 443))");
    EXPECT_TRUE(rule->evaluate(pkt1));   // tcp AND (22 OR 443)
    EXPECT_FALSE(rule->evaluate(pkt2));  // tcp BUT not (22 OR 443)
}

// Edge Cases

TEST_F(InterpreterTest, Parse_InvalidRule_ThrowsException) {
    EXPECT_THROW(parse("unknown 123"), std::runtime_error);
}

TEST(StandaloneTest, EmptyPacket_AllFieldsSet) {
    Packet p{"", "", 0, ""};
    auto rule = std::make_shared<MatchSrcIp>("");
    EXPECT_TRUE(rule->evaluate(p));
}

TEST(StandaloneTest, MultipleRules_IndependentEvaluation) {
    Packet p{"10.0.0.1", "192.168.1.1", 443, "tcp"};
    auto rule1 = std::make_shared<MatchPort>(443);
    auto rule2 = std::make_shared<MatchPort>(443);

    EXPECT_TRUE(rule1->evaluate(p));
    EXPECT_TRUE(rule2->evaluate(p));
}
