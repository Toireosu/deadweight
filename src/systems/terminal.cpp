#include "systems/terminal.hpp"
#include "systems/terminal_commands.hpp"

void Terminal::initCommands() {
    _commands["JUMP"] = TerminalCommands::jump;
    _commands["SCAN"] = TerminalCommands::scan;
    _commands["TRANSACT"] = TerminalCommands::Jobs::transact;
    _commands["COMMS"] = TerminalCommands::comms;
    _commands["BALANCE"] = TerminalCommands::balance;
    _commands["HELP"] = TerminalCommands::help;
    _commands["JOBLIST"] = TerminalCommands::Jobs::list;
    _commands["JOBINFO"] = TerminalCommands::Jobs::info;
    _commands["STORAGE"] = TerminalCommands::storage;
}