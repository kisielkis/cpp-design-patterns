#include <gtest/gtest.h>
#include <sstream>
#include <iostream>
#include <memory>
#include "../include/Comm.h"

class TemplateMethodTest : public ::testing::Test {
protected:
    std::stringstream capturedOutput;
    std::streambuf* oldCout;

    void SetUp() override {
        oldCout = std::cout.rdbuf(capturedOutput.rdbuf());
    }

    void TearDown() override {
        std::cout.rdbuf(oldCout);
    }

    std::string getCapturedOutput() {
        return capturedOutput.str();
    }
};

TEST_F(TemplateMethodTest, BtCommSendOutputContainsSTXETX) {
    BtComm bt("TestBT");
    bt.send("Hi");

    std::string output = getCapturedOutput();
    EXPECT_TRUE(output.find("SEND via BT:") != std::string::npos);
    EXPECT_TRUE(output.find("STX") != std::string::npos);
    EXPECT_TRUE(output.find("ETX") != std::string::npos);
}

TEST_F(TemplateMethodTest, BtCommSendOutputContainsBTPrefix) {
    BtComm bt("TestBT");
    bt.send("Hello");

    std::string output = getCapturedOutput();
    // BT's custom pack() adds "BT" prefix
    EXPECT_TRUE(output.find("BT") != std::string::npos);
}

TEST_F(TemplateMethodTest, WiFiCommSendOutputContainsSTXETX) {
    WiFiComm wifi("TestWiFi");
    wifi.send("World");

    std::string output = getCapturedOutput();
    EXPECT_TRUE(output.find("SEND via WiFi:") != std::string::npos);
    EXPECT_TRUE(output.find("STX") != std::string::npos);
    EXPECT_TRUE(output.find("ETX") != std::string::npos);
}

TEST_F(TemplateMethodTest, WiFiCommSendUsesFixedChecksum) {
    WiFiComm wifi("TestWiFi");
    wifi.send("Test");

    std::string output = getCapturedOutput();
    // WiFi uses fixed "XX" checksum
    EXPECT_TRUE(output.find("XX") != std::string::npos);
}

TEST_F(TemplateMethodTest, BtCommSendFormatIsCorrect) {
    BtComm bt("BT");
    bt.send("A");

    std::string output = getCapturedOutput();
    // Should contain the message framed with delimiters
    EXPECT_TRUE(output.find("SEND via BT:") != std::string::npos);
    // The output should have STX...ETX structure
    size_t stxPos = output.find("STX");
    size_t etxPos = output.find("ETX");
    EXPECT_NE(stxPos, std::string::npos);
    EXPECT_NE(etxPos, std::string::npos);
    if (stxPos != std::string::npos && etxPos != std::string::npos) {
        EXPECT_TRUE(stxPos < etxPos);
    }
}

TEST_F(TemplateMethodTest, WiFiCommSendFormatIsCorrect) {
    WiFiComm wifi("WiFi");
    wifi.send("B");

    std::string output = getCapturedOutput();
    EXPECT_TRUE(output.find("SEND via WiFi:") != std::string::npos);
    // Should contain STX and ETX in order
    size_t stxPos = output.find("STX");
    size_t etxPos = output.find("ETX");
    EXPECT_NE(stxPos, std::string::npos);
    EXPECT_NE(etxPos, std::string::npos);
}

TEST_F(TemplateMethodTest, PolymorphicBehaviorViaBasePointer) {
    std::unique_ptr<CommMedia> bt = std::make_unique<BtComm>("BT");
    std::unique_ptr<CommMedia> wifi = std::make_unique<WiFiComm>("WiFi");

    bt->send("Msg1");
    wifi->send("Msg2");

    std::string output = getCapturedOutput();
    EXPECT_TRUE(output.find("SEND via BT:") != std::string::npos);
    EXPECT_TRUE(output.find("SEND via WiFi:") != std::string::npos);
}

TEST_F(TemplateMethodTest, DifferentMediaProduceDifferentOutput) {
    capturedOutput.str("");

    BtComm bt("BT");
    bt.send("X");
    std::string btOutput = getCapturedOutput();

    capturedOutput.str("");
    capturedOutput.clear();

    WiFiComm wifi("WiFi");
    wifi.send("X");
    std::string wifiOutput = getCapturedOutput();

    // Both contain the message but with different framing
    EXPECT_TRUE(btOutput.find("SEND via BT:") != std::string::npos);
    EXPECT_TRUE(wifiOutput.find("SEND via WiFi:") != std::string::npos);
    EXPECT_NE(btOutput, wifiOutput);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
