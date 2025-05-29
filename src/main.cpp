#include <iostream>

#include "systems/terminal.hpp"

int main() {
    Terminal terminal;
    std::cout << terminal.getGreetingMessage() << std::endl;
    std::cout << terminal.getOutput() << std::endl;
    terminal.handleInput("Test input");
    std::cout << terminal.getOutput() << std::endl;
    terminal.handleInput("jump carbora");
    std::cout << terminal.getOutput() << std::endl;
    std::cout << terminal.getInput(0) << std::endl;
    std::cout << terminal.getInput(1) << std::endl;
    std::cout << terminal.getInput(8) << std::endl;
    std::cout << terminal.getInput(11) << std::endl;
    terminal.handleInput("scan carbora");
    std::cout << terminal.getOutput() << std::endl;
    terminal.handleInput("transact 0");
    std::cout << terminal.getOutput() << std::endl;
    terminal.handleInput("balance");
    std::cout << terminal.getOutput() << std::endl;
    terminal.handleInput("comms kelly");
    std::cout << terminal.getOutput() << std::endl;


    return 0;
}