#pragma once
#include "Machine.h"
#include <vector>
#include <string>

class UI {
private:
    Machine machine;
    bool fileOrInstructions;

public:
    std::vector<std::string> getFile();
    std::string getInstructions();
    void displayMenu();
};