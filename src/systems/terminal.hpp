#pragma once

#include <array>
#include <map>
#include <string>
#include <vector>
#include <functional>
#include <exception>
#include "utils/string_utils.hpp"

#include "core/updatable.hpp"
#include "data/world_map.hpp"

class Terminal;
typedef std::function<std::list<std::string>(const Terminal&, std::vector<std::string>)> TerminalCommandPointer;

class IncorrectTerminalInputError : public std::runtime_error {
private:
    std::list<std::string> _info;
public:
    IncorrectTerminalInputError(std::list<std::string> info) throw() : std::runtime_error(info.front().c_str()) {
        _info = info;
    }

    IncorrectTerminalInputError(std::string info) throw() : IncorrectTerminalInputError(std::list<std::string> { info }) {
    }

    virtual char const* what() const throw() {
        return exception::what();
    }

    std::list<std::string> getInfo() {
        return _info;
    }
};

class Terminal : public Updatable {
private:
    // Contains current input at position 0 and the last 9 inputs
    std::array<std::string, 10> _inputs;
    std::map<std::string, TerminalCommandPointer> _commands;
    std::list<std::string> _output;
    std::string _greetingMessage = "TTerminal Quatro Version 4.12";
    bool _wasError = false;
    
    // Moves current input as first input in _inputs list
    void addToInputs(std::string input) {
        if (input == _inputs[0])
            return;

        for (int i = _inputs.size() - 1; i >= 1; i--) {
            _inputs[i] = _inputs[i - 1];
        }

        _inputs[0] = input;
    }

    TerminalCommandPointer getCommandFunction(std::string signature) {
        std::string upper = StringUtilites::upperCase(signature);

        if (_commands.count(upper))
            return _commands[upper];
        throw IncorrectTerminalInputError(std::list<std::string> { "Unknown command: ", StringUtilites::lowerCase(signature) });
    }

    void initCommands();
public:
    Terminal() {
        initCommands();

        for (int i = 0; i < _inputs.size(); i++)
            _inputs[i] = "";
    } 

    void handleInput(std::string input) {
        if (input.empty())
            return;

        addToInputs(input);
        try {
            std::vector<std::string> tokens;
            tokens.reserve(6);
            std::stringstream stringStream(input);
    
            std::string token;
            while (getline(stringStream, token, ' '))
                tokens.push_back(token);
    
            auto function = getCommandFunction(tokens.front());
            _output = function(*this, std::vector<std::string>(tokens.begin() + 1, tokens.end()));
            _wasError = false;
        }
        catch (IncorrectTerminalInputError error) {
            _output = error.getInfo();
            _wasError = true;
        }
    }

    std::string getGreetingMessage() { return _greetingMessage; }
    std::list<std::string> getOutput() { return _output; }
    std::string getInput(unsigned int index) { return (index >= _inputs.size() || index < 0) ? "" : _inputs[index]; }
    bool getWasError() { return _wasError; }
};