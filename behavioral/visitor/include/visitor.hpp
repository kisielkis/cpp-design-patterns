#pragma once

#include <iostream>
#include <string>

class Visitor;

class Element {
    public:
        virtual ~Element() = default;
        virtual void accept(Visitor *visitor) = 0;
};

class Visitor {
    public:
        virtual ~Visitor() = default;
        virtual void visit(class Person *person) = 0;
        virtual void visit(class Car *car) = 0;
};

class StreamVisitor : public Visitor {
    public:
        void visit(Person *person) override;
        void visit(Car *car) override;
};

class Person : public Element {
    private:
        int age;
        std::string name;
    public:
        Person(int ag, const std::string &nam) : age(ag), name(nam) {}

        int getAge() const { return age; }
        const std::string& getName() const { return name; }

        void accept(Visitor *visitor) override {
            visitor->visit(this);
        }
};

class Car : public Element {
    private:
        std::string model;
        std::string engine;
        int maxSpeed;
    public:
        Car(const std::string &mod, const std::string &eng, int speed)
            : model(mod), engine(eng), maxSpeed(speed) {}

        const std::string& getModel() const { return model; }
        const std::string& getEngine() const { return engine; }
        int getMaxSpeed() const { return maxSpeed; }

        void accept(Visitor *visitor) override {
            visitor->visit(this);
        }
};

inline void StreamVisitor::visit(Person *person) {
    std::cout << "handlePerson " << person->getAge() << " " << person->getName() << "\n";
}

inline void StreamVisitor::visit(Car *car) {
    std::cout << "handleCar " << car->getModel() << " " << car->getEngine() << " " << car->getMaxSpeed() << "\n";
}



