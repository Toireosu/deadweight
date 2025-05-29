#include <array>
#include <map>
#include <string>
#include <vector>
#include <functional>
#include <sstream>

class IncorrectTerminalInputError : public std::runtime_error {
public:
    IncorrectTerminalInputError(char const* const message) throw() : std::runtime_error(message) {
    }
    virtual char const* what() const throw() {
        return exception::what();
    }
};

class Terminal {
private:
    // Contains current input at position 0 and the last 9 inputs
    std::array<std::string, 10> _inputs;
    std::map<std::string, std::function<bool(std::vector<std::string>)>> _commands;
public: 
    Terminal() {
        // _tokens.insert("JUMP", ;
        // _tokens[1] = "SCAN";
        // _tokens[3] = "TRANSACT";
        // _tokens[4] = "COMMS";
        // _tokens[5] = "BALANCE";
        // _tokens[6] = "HELP";

        for (int i = 0; i < _inputs.size(); i++)
            _inputs[i] = "";
    }

    // Moves current input as first input in _inputs list
    void addToInputs(std::string input) {
        for (int i = _inputs.size() - 1; i >= 1; i--) {
            _inputs[i] = _inputs[i - 1];
        }

        _inputs[0] = input;
    }

    void handleInput(std::string input) {
        addToInputs(input);

        auto tokens = std::vector<std::string>(6);
        std::stringstream stringStream(input);

        std::string token;
        while (getline(stringStream, token, ' '))
            tokens.push_back(token);
    }
};