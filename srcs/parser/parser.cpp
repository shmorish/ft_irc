#include "parser.hpp"

CommandType Parser::get_command(){
    return this->_command;
}

void    Parser::check_command(string &command)
{
    transform(command.begin(), command.end(), command.begin(), ::toupper);
    if (command == "PASS")
        _command = PASS;
    else if (command == "NICK")
        _command = NICK;
    else if (command == "USER")
        _command = USER;
    else if (command == "JOIN")
        _command = JOIN;
    else if (command == "PART")
        _command = PART;
    else if (command == "PRIVMSG")
        _command = PRIVMSG;
    else if (command == "QUIT")
        _command = QUIT;
    else if (command == "PING")
        _command = PING;
    else if (command == "PONG")
        _command = PONG;
    else
        throw runtime_error("Invalid command: " + command);
}

Parser::Parser(string &message, int fd, const string &password) : _message(message), _fd(fd), _password(password)
{
    DEBUG_MSG("Message =", _message);
    DEBUG_MSG("FD      =", _fd);
    DEBUG_MSG("Password=", _password);
    (void)_fd;

    cout << "Message: " << _message << endl;

    // istringstream iss(_message);
    // string command_token;
    // iss >> command_token;
    // check_command(command_token);
    // cout << "Command: " << command_token << endl;
    // while (iss >> command_token) {
    //     cout << "Token: " << command_token << endl;
    // }
}

Parser::~Parser()
{
}
