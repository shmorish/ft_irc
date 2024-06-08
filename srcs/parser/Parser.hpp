#ifndef PARSER_HPP
#define PARSER_HPP

#include "utils.hpp"

typedef enum CommandType {
    PASS,
    NICK,
    USER,
    JOIN,
    PART,
    PRIVMSG,
    QUIT,
    PING,
    PONG,
    TIME,
    KICK,
    MODE,
    TOPIC,
    INVITE,
    CAP,
    DCC,
    SENDFILE,
    GETFILE,
    HELP,
    VERSION,
    BAN,
} CommandType;

class Parser {
public:
    Parser(string &message, int fd, const string &password);
    ~Parser();
    CommandType get_command();
    string get_password();
    string get_message();
    vector<string> get_args();

private:
    string _message;
    int _fd;
    string _password;
    CommandType _command;
    void    check_command(string &command);
    vector<string> args;
};

#endif
