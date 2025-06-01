#include "systems/terminal.hpp"
#include "systems/terminal_commands.hpp"

void Terminal::initCommands() {
    _commands["JUMP"] = TerminalCommands::jump;
    _commands["SCAN"] = TerminalCommands::scan;
    _commands["TRANSACT"] = TerminalCommands::transact;
    _commands["COMMS"] = TerminalCommands::comms;
    _commands["BALANCE"] = TerminalCommands::balance;
    _commands["HELP"] = TerminalCommands::help;
}