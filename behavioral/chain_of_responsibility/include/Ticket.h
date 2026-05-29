#pragma once

#include <string>

using namespace std;

enum class Priority { LOW, MEDIUM, HIGH, CRITICAL, NONE};

struct Ticket {
    int id;
    std::string desc;
    Priority prior;
};