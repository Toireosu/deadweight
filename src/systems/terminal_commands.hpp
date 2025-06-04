#pragma once

#include "systems/terminal.hpp"

class TerminalCommands {
public:
    static std::list<std::string> jump(Terminal& terminal, std::vector<std::string> parameters) {
        if (parameters.empty())
            throw IncorrectTerminalInputError("Missing parameters");

        if (parameters.size() == 1) {
            // Handle jump world name
            auto world = WorldMap::getWorldByName(parameters.front());
            if (world == nullptr) {
                throw IncorrectTerminalInputError((std::stringstream() << parameters[0] << " is not a known world.").str());
            }

            terminal.getVessel()->jump(world->getCoords());
            return std::list<std::string> { (std::stringstream() << "Initiating jump to " << world->getName()).str() };
        }
        if (parameters.size() == 2) {
            // Jump coordinates
            try {
                unsigned short x = std::stoi(parameters.at(0));
                unsigned short y = std::stoi(parameters.at(1));

                terminal.getVessel()->jump(SpaceCoords(x, y));
                return std::list<std::string> { (std::stringstream() << "Initiating jump to " << x << " " << y).str() };
            }
            catch (std::exception e) {
                throw IncorrectTerminalInputError("Could not parse");
            }
        }

        throw IncorrectTerminalInputError("Too many parameters");
    }    

    static std::list<std::string> scan(Terminal& terminal, std::vector<std::string> parameters) {
        if (parameters.empty())
            throw IncorrectTerminalInputError("Missing parameters");

        if (parameters.size() == 1) {
            // Handle scan world name
            auto world = WorldMap::getWorldByName(parameters.front());
            if (world == nullptr) {
                throw IncorrectTerminalInputError((std::stringstream() << parameters[0] << " is not a known world.").str());
            }

            return std::list<std::string> { world->scan() };
        }

        // TODO: Scan coordinates

        throw IncorrectTerminalInputError("Too many parameters");
    }    

    static std::list<std::string> transact(Terminal& terminal, std::vector<std::string> parameters) {
        if (parameters.empty())
            throw IncorrectTerminalInputError("Missing parameters");

        return std::list<std::string> { (std::stringstream() << "Accepted job " << parameters[0]).str() };
    }

    static std::list<std::string> comms(Terminal& terminal, std::vector<std::string> parameters) {
        if (parameters.empty())
            throw IncorrectTerminalInputError("Missing parameters");

        return std::list<std::string> { "There is no one there..." };
    }

    static std::list<std::string> balance(Terminal& terminal, std::vector<std::string> parameters) {
        return std::list<std::string> { (std::stringstream() << "You have 0.000 VBucks...").str() };
    }

    static std::list<std::string> help(Terminal& terminal, std::vector<std::string> parameters) {
        static std::list<std::string> _commandList {
            "= List of Commands =",
            "- jump [world] [x, y]",
            "- scan [world] [x, y]",
            "- transact [job_name] [job_index]"
        };
        
        return _commandList;
    }
};