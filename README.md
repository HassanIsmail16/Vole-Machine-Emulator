# Vole-Machine-Emulator
## Description
This is a vole machine emulator based on the Von Neumann Architecture. It consists of memory, CPU (CU, ALU, registers), and a user interface.
Instruction are stored in memory. Each instruction consists of 4 hexadecimal digits, and each memory cell stores 2 hexadecimal digits, meaning that each 2 memory cells make an instruction.
A program counter loops over all memory cells and fetches instructions from them, which can then be executed.

## How to Run
You can run the program directly from the executable, which can be found in the [latest release in the repository](https://github.com/HassanIsmail16/Vole-Machine-Emulator/releases/tag/Latest). 
You can also build it directly using Visual Studio with the **Desktop Development with C++ pack**, the **.NET Desktop Development pack**, and the **C++/CLI support for v143 build tools** component. 
The Visual Studio project solution file is called "Vole-Machine.sln" and can be found in the repository.

## How to Use
### Writing instructions
Instructions can be written directly in the memory list cells in the user interface, by loading them from a file using the "Load From File" button in the UI, or using the "Batch Add Code" button in the UI.
![image](https://github.com/user-attachments/assets/366332e4-bf41-4256-8206-54d1a703867e)

### List of Instructions
- **1RXY** -> Load content of memory cell "XY" into register "R"
- **2RXY** -> Load "XY" into register "R"
- **3RXY** -> Copy content of register "R" into memory cell "XY"
  - **3R00** -> Write content of register "R" to memory cell "00" (write to screen)
- **4xRS** -> Copy content of register "R" into register "S"
- **5RST** -> Add contents of registers "S" and "T" and store them in two's complement notation into register "R"
- **6RST** -> Add contents of registers "S" and "T" and store them in floating point notation into register "R"
- **7RST** -> Bitwise OR (⌄) the contents of registers "S" and "T" and store them in register "R"
- **8RST** -> Bitwise AND (^) the contents of registers "S" and "T" and store them in register "R"
- **9RST** -> Bitwise XOR (⊕) the contents of registers "S" and "T" and store them in register "R"
- **ARxX** -> Rotate the content of register "R" cyclically right "X" steps
- **BRXY** -> Jump to instruction in memory cell "XY" if the contents of registers "R" and "0" are equal
- **Cxxx** -> Halt execution
- **DRXY** -> Jump to instruction in memory cell "XY" if the content of register "R" is greater than (>) that of register "0"

### Running instructions
You can execute instructions by pressing "Fetch", (optionally) "Decode", then "Execute"; pressing the "Step" button; the "Play" button, or the "Run Until Halt" button.


## Notes
- Invalid instructions are ignored
- To print to screen in hexadecimal form, choose the "Print HEX" option in the screen settings, and to print in ASCII form, choose the "Print ASCII" option
- You can select an address for the program counter to be set at by clicking on the memory list address you want in the UI
  - If you want to select an odd address, you can toggle the option "Odd Selection" in memory list settings
- If you want to change the address at which execution starting or instruction loading from file starts, you can change it in the textbox "Starting Address" in memory list settings
- The program works only on Windows
