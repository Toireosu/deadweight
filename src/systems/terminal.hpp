#pragma once

#include <array>
#include <map>
#include <string>
#include <vector>
#include <functional>
#include <exception>
#include "utils/string_utils.hpp"

typedef std::function<std::string(std::vector<std::string>)> TerminalCommandPointer;

class IncorrectTerminalInputError : public std::runtime_error {
private:
    std::string _info;
public:
    IncorrectTerminalInputError(char const* const info) throw() : std::runtime_error(info) {
        _info = info;
    }

    virtual char const* what() const throw() {
        return exception::what();
    }

    std::string getInfo() {
        return _info;
    }
};

class Terminal {
private:
    // Contains current input at position 0 and the last 9 inputs
    std::array<std::string, 10> _inputs;
    std::map<std::string, TerminalCommandPointer> _commands;
    std::string _output;
    std::string _greetingMessage = "TTerminal Quatro Version 4.12";
    
    // Moves current input as first input in _inputs list
    void addToInputs(std::string input) {
        for (int i = _inputs.size() - 1; i >= 1; i--) {
            _inputs[i] = _inputs[i - 1];
        }

        _inputs[0] = input;
    }

    TerminalCommandPointer getCommandFunction(std::string signature) {
        std::string upper = StringUtilites::upperCase(signature);

        if (_commands.count(upper))
            return _commands[upper];
        throw IncorrectTerminalInputError("Unknown command");
    }

    static std::string jump(std::vector<std::string> parameters) {
        if (parameters.empty())
            throw IncorrectTerminalInputError("Missing parameters");

        return (std::stringstream() << "Setting course to " << parameters[0]).str();
    }    

    static std::string scan(std::vector<std::string> parameters) {
        if (parameters.empty())
            throw IncorrectTerminalInputError("Missing parameters");

        return (std::stringstream() << "The weather on " << parameters[0] << " is cloudy").str();
    }    

    static std::string transact(std::vector<std::string> parameters) {
        if (parameters.empty())
            throw IncorrectTerminalInputError("Missing parameters");

        return (std::stringstream() << "Accepted job " << parameters[0]).str();
    }

    static std::string comms(std::vector<std::string> parameters) {
        if (parameters.empty())
            throw IncorrectTerminalInputError("Missing parameters");

        return (std::stringstream() << "There is no one there...").str();
    }

    static std::string balance(std::vector<std::string> parameters) {
        return (std::stringstream() << "You have 0.000 VBucks...").str();
    }

    static std::string help(std::vector<std::string> parameters) {
        return (std::stringstream() << "Under construction..").str();
    }


    void initCommands() {
        _commands["JUMP"] = jump;
        _commands["SCAN"] = scan;
        _commands["TRANSACT"] = transact;
        _commands["COMMS"] = comms;
        _commands["BALANCE"] = balance;
        _commands["HELP"] = jump;
    }

public:
    Terminal() {
        initCommands();

        for (int i = 0; i < _inputs.size(); i++)
            _inputs[i] = "";
    } 

    void handleInput(std::string input) {
        addToInputs(input);
        try {
            std::vector<std::string> tokens;
            tokens.reserve(6);
            std::stringstream stringStream(input);
    
            std::string token;
            while (getline(stringStream, token, ' '))
                tokens.push_back(token);
    
            auto function = getCommandFunction(tokens.front());
            _output = function(std::vector<std::string>(tokens.begin() + 1, tokens.end()));
        }
        catch (IncorrectTerminalInputError error) {
            std::stringstream ss;
            ss << error.getInfo();
            ss << ": ";
            ss << input;
            _output = ss.str(); 
        }
    }

    std::string getGreetingMessage() { return _greetingMessage; }
    std::string getOutput() { return _output; }
    std::string getInput(unsigned int index) { return (index >= _inputs.size()) ? "" : _inputs[index]; }
};