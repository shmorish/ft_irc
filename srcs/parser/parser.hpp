#ifndef PARSER_HPP
#define PARSER_HPP

#include "utils.hpp"

typedef enum CommandType {
    NICK,
    USER,
    JOIN,
    PART,
    PRIVMSG,
    QUIT,
    PING,
    PONG,
} CommandType;

class Parser {
public:
    Parser(string &message, int fd, const string &password);
    ~Parser();
private:
    string _message;
    int _fd;
    string _password;
    CommandType _command;
    void    check_command(string &command);
};

#endif