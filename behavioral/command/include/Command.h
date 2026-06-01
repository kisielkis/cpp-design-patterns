#pragma once


// abstract class
class Command {
    public:
        virtual ~Command() {};
        virtual bool execute() = 0;
        virtual bool rollback() = 0;
};