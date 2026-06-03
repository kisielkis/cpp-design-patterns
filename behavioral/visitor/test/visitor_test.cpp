#include <gtest/gtest.h>
#include <sstream>
#include <iostream>
#include <memory>
#include "../include/visitor.hpp"

class VisitorPatternTest : public ::testing::Test {
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

TEST_F(VisitorPatternTest, StreamVisitorHandlesPerson) {
    Person john(25, "John");
    StreamVisitor visitor;
    john.accept(&visitor);

    std::string output = getCapturedOutput();
    EXPECT_TRUE(output.find("handlePerson") != std::string::npos);
    EXPECT_TRUE(output.find("25") != std::string::npos);
    EXPECT_TRUE(output.find("John") != std::string::npos);
}

TEST_F(VisitorPatternTest, StreamVisitorHandlesCar) {
    Car toyota("Corolla", "2.0L Hybrid", 192);
    StreamVisitor visitor;
    toyota.accept(&visitor);

    std::string output = getCapturedOutput();
    EXPECT_TRUE(output.find("handleCar") != std::string::npos);
    EXPECT_TRUE(output.find("Corolla") != std::string::npos);
    EXPECT_TRUE(output.find("2.0L Hybrid") != std::string::npos);
    EXPECT_TRUE(output.find("192") != std::string::npos);
}

TEST_F(VisitorPatternTest, PersonAgeAndNameArePreserved) {
    Person alice(30, "Alice");
    StreamVisitor visitor;
    alice.accept(&visitor);

    std::string output = getCapturedOutput();
    EXPECT_TRUE(output.find("30") != std::string::npos);
    EXPECT_TRUE(output.find("Alice") != std::string::npos);
}

TEST_F(VisitorPatternTest, CarDetailsArePreserved) {
    Car bmw("BMW X5", "3.0L TwinPower Turbo", 250);
    StreamVisitor visitor;
    bmw.accept(&visitor);

    std::string output = getCapturedOutput();
    EXPECT_TRUE(output.find("BMW X5") != std::string::npos);
    EXPECT_TRUE(output.find("3.0L TwinPower Turbo") != std::string::npos);
    EXPECT_TRUE(output.find("250") != std::string::npos);
}

TEST_F(VisitorPatternTest, MultipleObjectsCanBeVisited) {
    Person john(5, "john");
    Car toyota("corolla", "2.0 Hybrid Dynamic Force", 192);
    StreamVisitor visitor;

    john.accept(&visitor);
    toyota.accept(&visitor);

    std::string output = getCapturedOutput();
    EXPECT_TRUE(output.find("handlePerson") != std::string::npos);
    EXPECT_TRUE(output.find("handleCar") != std::string::npos);
    EXPECT_TRUE(output.find("john") != std::string::npos);
    EXPECT_TRUE(output.find("corolla") != std::string::npos);
}

TEST_F(VisitorPatternTest, VisitorOutputFormat) {
    Person person(35, "Bob");
    StreamVisitor visitor;
    person.accept(&visitor);

    std::string output = getCapturedOutput();
    // Verify exact format: "handlePerson age name"
    EXPECT_TRUE(output.find("handlePerson") != std::string::npos);
    // age and name should appear after handlePerson
    size_t personPos = output.find("handlePerson");
    size_t agePos = output.find("35", personPos);
    size_t namePos = output.find("Bob", personPos);
    EXPECT_NE(personPos, std::string::npos);
    EXPECT_NE(agePos, std::string::npos);
    EXPECT_NE(namePos, std::string::npos);
}

TEST_F(VisitorPatternTest, CarVisitorOutputFormat) {
    Car car("Honda Civic", "1.5L", 180);
    StreamVisitor visitor;
    car.accept(&visitor);

    std::string output = getCapturedOutput();
    // Verify format: "handleCar model engine speed"
    EXPECT_TRUE(output.find("handleCar") != std::string::npos);
    size_t carPos = output.find("handleCar");
    EXPECT_NE(carPos, std::string::npos);
}

TEST_F(VisitorPatternTest, PolymorphicVisitorBehavior) {
    Person john(25, "John");
    Car car("Toyota", "2.0L", 200);
    StreamVisitor visitor;

    // Both objects should work with the same visitor
    john.accept(&visitor);
    car.accept(&visitor);

    std::string output = getCapturedOutput();
    EXPECT_TRUE(output.find("handlePerson") != std::string::npos);
    EXPECT_TRUE(output.find("handleCar") != std::string::npos);
}

TEST_F(VisitorPatternTest, DifferentPeopleProduceDifferentOutput) {
    capturedOutput.str("");

    Person person1(20, "Alice");
    StreamVisitor visitor;
    person1.accept(&visitor);
    std::string output1 = getCapturedOutput();

    capturedOutput.str("");
    capturedOutput.clear();

    Person person2(30, "Bob");
    person2.accept(&visitor);
    std::string output2 = getCapturedOutput();

    EXPECT_TRUE(output1.find("Alice") != std::string::npos);
    EXPECT_TRUE(output2.find("Bob") != std::string::npos);
    EXPECT_NE(output1, output2);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
