#pragma once

#include "systems/terminal.hpp"
#include "data/job.hpp"

class TerminalCommands {
public:
    static std::list<std::string> storage(Terminal& terminal, std::vector<std::string> parameters) {
        if (!parameters.empty())
            throw IncorrectTerminalInputError("Too many parameters");

        auto response = std::list<std::string>();

        auto storage = terminal.getVessel()->getStorage();
        if (storage.empty()) {
            response.push_back("Empty");
            return response;
        }

        
        int nameTabSize = 4;
        int massTabSize = 4;
        int indexTabSize = 3;
        for (auto storable : storage) {
            if (storable->getName().size() > nameTabSize)
                nameTabSize = storable->getName().size();
            if (storable->getMass() / 10 > massTabSize)
                massTabSize = storable->getMass() / 10; 
        }

        auto tabFunc = [](std::string in, int size)->std::string {
            std::stringstream ss;
            ss << in;
            
            for (int i = in.size(); i < size; i++)
                ss << " ";

            return ss.str();
        };

        std::string breakStr = " | ";

        std::stringstream ss;
        ss << tabFunc("NUM", indexTabSize) << breakStr;
        ss << tabFunc("NAME", nameTabSize) << breakStr;
        ss << tabFunc("MASS", massTabSize);

        response.push_back(ss.str());

        int i = 0;
        for (auto storable : storage) {
            std::stringstream ss;
            ss << tabFunc(std::to_string(i), indexTabSize) << breakStr;
            ss << tabFunc(storable->getName(), nameTabSize) << breakStr;
            ss << tabFunc((std::stringstream() << storable->getMass() << "kg").str(), massTabSize);

            response.push_back(ss.str());
            i++;
        }

        return response;
    }

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

    static std::list<std::string> joblist(Terminal& terminal, std::vector<std::string> parameters) {
        if (parameters.size() != 0)
            throw IncorrectTerminalInputError("Too many parameters for command 'jobs'");
        
        auto world = WorldMap::getWorldByCoords(terminal.getVessel()->getCoords());
        std::list<std::string> ret;

        if (world == nullptr) {
            ret.push_back("Timeout: Couldn't reach jobs server...");
            return ret;
        }
        
        auto jobs = world->fetchJobs();

        int i = 0;
        for (auto job : jobs) {
            ret.push_back((std::stringstream() << i << ": " << job->getName()).str());
        }
        
        return ret;
    }
};