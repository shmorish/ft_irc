#include "Command.hpp"

void help_help(User &_user) {
    string res = "HELP :HELP <command>\r\n";
    send(_user.get_fd(), res.c_str(), res.size(), 0);
}

void help_invite(User &_user) {
    string res = "INVITE :INVITE <#channel> <nickname>\r\n";
    send(_user.get_fd(), res.c_str(), res.size(), 0);
}

void help_join(User &_user) {
    string res = "JOIN :JOIN <#channel>\r\n";
    send(_user.get_fd(), res.c_str(), res.size(), 0);
}

void help_kick(User &_user) {
    string res = "KICK :KICK <#channel> <nickname>\r\n";
    send(_user.get_fd(), res.c_str(), res.size(), 0);
}

void help_mode(User &_user) {
    string res = "MODE :MODE <#channel> <mode>\r\n";
    send(_user.get_fd(), res.c_str(), res.size(), 0);
}

void help_part(User &_user) {
    string res = "PART :PART <#channel>\r\n";
    send(_user.get_fd(), res.c_str(), res.size(), 0);
}

void help_pass(User &_user) {
    string res = "PASS :PASS <password>\r\n";
    send(_user.get_fd(), res.c_str(), res.size(), 0);
}

void help_ping(User &_user) {
    string res = "PING :PING <server>\r\n";
    send(_user.get_fd(), res.c_str(), res.size(), 0);
}

void help_privmsg(User &_user) {
    string res = "PRIVMSG :PRIVMSG <nickname> <message>\r\n";
    send(_user.get_fd(), res.c_str(), res.size(), 0);
}

void help_quit(User &_user) {
    string res = "QUIT :QUIT <message>\r\n";
    send(_user.get_fd(), res.c_str(), res.size(), 0);
}

void help_sendfile(User &_user) {
    string res = "SENDFILE :SENDFILE <nickname> <filename>\r\n";
    send(_user.get_fd(), res.c_str(), res.size(), 0);
}

void help_time(User &_user) {
    string res = "TIME :TIME\r\n";
    send(_user.get_fd(), res.c_str(), res.size(), 0);
}

void help_topic(User &_user) {
    string res = "TOPIC :TOPIC <#channel> <topic>\r\n";
    send(_user.get_fd(), res.c_str(), res.size(), 0);
}

void help_user(User &_user) {
    string res = "USER :USER <username> <hostname> <servername> <realname>\r\n";
    send(_user.get_fd(), res.c_str(), res.size(), 0);
}

void help_getfile(User &_user) {
    string res = "GETFILE :GETFILE <filename>\r\n";
    send(_user.get_fd(), res.c_str(), res.size(), 0);
}

void help_nick(User &_user) {
    string res = "NICK :NICK <nickname>\r\n";
    send(_user.get_fd(), res.c_str(), res.size(), 0);
}

void send_how_to_connect(User &_user) {
    string res = "You need to connect to the server first\r\n";
    send(_user.get_fd(), res.c_str(), res.size(), 0);
    help_pass(_user);
    help_nick(_user);
    help_user(_user);
}

void send_how_to_use(User &_user) {
    help_join(_user);
    help_part(_user);
    help_privmsg(_user);
    help_quit(_user);
    help_ping(_user);
    help_kick(_user);
    help_mode(_user);
    help_topic(_user);
    help_invite(_user);
    help_sendfile(_user);
    help_getfile(_user);
    help_time(_user);
    help_help(_user);
}

void Command::help() {
    if (_parser.get_args().size() == 0) {
        if (_user.get_ready_to_connect() == false)
            send_how_to_connect(_user);
        else
            send_how_to_use(_user);
        return;
    }
    string command = _parser.get_args().at(0);
    transform(command.begin(), command.end(), command.begin(), ::toupper);
    if (command == "HELP") help_help(_user);
    else if (command == "INVITE")
        help_invite(_user);
    else if (command == "JOIN")
        help_join(_user);
    else if (command == "KICK")
        help_kick(_user);
    else if (command == "MODE")
        help_mode(_user);
    else if (command == "NICK")
        help_nick(_user);
    else if (command == "PART")
        help_part(_user);
    else if (command == "PASS")
        help_pass(_user);
    else if (command == "PING")
        help_ping(_user);
    else if (command == "PRIVMSG")
        help_privmsg(_user);
    else if (command == "QUIT")
        help_quit(_user);
    else if (command == "SENDFILE")
        help_sendfile(_user);
    else if (command == "TIME")
        help_time(_user);
    else if (command == "TOPIC")
        help_topic(_user);
    else if (command == "USER")
        help_user(_user);
    else if (command == "GETFILE")
        help_getfile(_user);
}