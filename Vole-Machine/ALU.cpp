#include "ALU.h"
#include <sstream>
#include <iomanip>
#include <array>
#include "StorageUnit.h"

void ALU::addTwoComp(int Reg1, int Reg2, std::array<StorageUnit, 16>& registers) {
    int value1 = std::stoi(registers[Reg1].getValue(), nullptr, 16); // Convert hex to int
    int value2 = std::stoi(registers[Reg2].getValue(), nullptr, 16);
    int result = value1 + value2;

    if (result > 127) {
        result -= 256;
    }
    else if (result < -128) {
        result += 256;
    }

    std::stringstream stream;
    stream << std::hex << (result & 0xFF);
    registers[Reg1].setValue(stream.str());
}

void ALU::addFloatingPoint(int Reg1, int Reg2, std::array<StorageUnit, 16>& registers) {
    
}

std::string ALU::hexToDec() {
    
    return "";
}
