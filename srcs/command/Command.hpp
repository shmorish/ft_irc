#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "Channel.hpp"
#include "File.hpp"
#include "Parser.hpp"
#include "Server.hpp"
#include "User.hpp"
#include "utils.hpp"

class Server;
class Parser;
class User;
class File;

class Command {
public:
    Command(Server &server, Parser &parser, User &user);
    ~Command();

private:
    void pass();
    void nick();
    void user();
    void join();
    void part();
    void privmsg();
    void quit();
    void ping();
    void pong(){};
    void show_time();
    void kick();
    void mode();
    void topic();
    void invite();
    void cap();
    void dcc();
    void sendfile();
    void getfile();
    void help();
    void version();
    void ban();
    void send_bot();

    Server &_server;
    Parser &_parser;
    User &_user;

    void mode_command_o(Channel *channel);
    void mode_command_l(Channel *channel);
    void mode_command_t(Channel *channel);
    void mode_command_m(Channel *channel);
    void mode_command_v(Channel *channel);
    void mode_command_k(Channel *channel);
    void mode_command_i(Channel *channel);
};

#endif
