#include "Command.hpp"

static void help_pass(User &_user) {
    string res = "PASS :PASS <password>\r\n";
    res += "    The password is used to connect to the server\r\n";
    send(_user.get_fd(), res.c_str(), res.size(), 0);
}

static void help_nick(User &_user) {
    string res = "NICK :NICK <nickname>\r\n";
    res += "    The nickname is used to identify you on the server\r\n";
    send(_user.get_fd(), res.c_str(), res.size(), 0);
}

static void help_user(User &_user) {
    string res = "USER :USER <username> <hostname> <servername> <realname>\r\n";
    res += "    The username is used to identify you on the server\r\n";
    send(_user.get_fd(), res.c_str(), res.size(), 0);
}

static void help_join(User &_user) {
    string res = "JOIN :JOIN <#channel>\r\n";
    res += "    The channel is used to join a channel\r\n";
    send(_user.get_fd(), res.c_str(), res.size(), 0);
}

static void help_part(User &_user) {
    string res = "PART :PART <#channel>\r\n";
    res += "    The channel is used to leave a channel\r\n";
    send(_user.get_fd(), res.c_str(), res.size(), 0);
}

static void help_privmsg(User &_user) {
    string res;
    res += "PRIVMSG :PRIVMSG <nickname> <message>\r\n";
    res += "    The nickname is used to send a private message to a user\r\n";
    res += "\r\n";
    res += "PRIVMSG :PRIVMSG <#channel> <message>\r\n";
    res += "    The channel is used to send a message to a channel\r\n";
    res += "\r\n";
    res += "PRIVMSG :PRIVMSG bot announce <message>\r\n";
    res += "    The bot is used to send a message to all users in server\r\n";
    res += "\r\n";
    res += "PRIVMSG :PRIVMSG bot <channel list | channel join | channel invite>\r\n";
    res += "    The bot is used to see the list of channels, joining channel, or invited channel\r\n";
    res += "\r\n";
    res += "PRIVMSG :PRIVMSG bot sendfile <nickname> <filename_path>\r\n";
    res += "    The bot is used to send a file to a user\r\n";
    res += "\r\n";
    res += "PRIVMSG :PRIVMSG bot getfile <nickname> <filename_path>\r\n";
    res += "    The bot is used to get a file from a user\r\n";
    send(_user.get_fd(), res.c_str(), res.size(), 0);
}

static void help_quit(User &_user) {
    string res = "QUIT :QUIT <message>\r\n";
    res += "    The message is used to leave the server\r\n";
    send(_user.get_fd(), res.c_str(), res.size(), 0);
}

static void help_ping(User &_user) {
    string res = "PING :PING <server>\r\n";
    res += "    The server is used to check the connection with the server\r\n";
    send(_user.get_fd(), res.c_str(), res.size(), 0);
}

static void help_time(User &_user) {
    string res = "TIME :TIME\r\n";
    res += "    The time is used to check the time of the server\r\n";
    send(_user.get_fd(), res.c_str(), res.size(), 0);
}

static void help_kick(User &_user) {
    string res = "KICK :KICK <#channel> <nickname>\r\n";
    res += "    The channel is used to kick a user from a channel\r\n";
    send(_user.get_fd(), res.c_str(), res.size(), 0);
}

static void help_mode(User &_user) {
    string res = "MODE :MODE <#channel> <mode>\r\n";
    res += "    The channel is used to change the mode of a channel\r\n";
    res += "    <Modes>\r\n";
    res += "        o : Give operator status to a user\r\n";
    res += "        l : Only operators can change the channel limit\r\n";
    res += "        t : Only operators can change the topic\r\n";
    res += "        k : Set a password to join the channel\r\n";
    res += "        i : Set the channel to invite only\r\n";
    send(_user.get_fd(), res.c_str(), res.size(), 0);
}

static void help_topic(User &_user) {
    string res = "TOPIC :TOPIC <#channel> <topic>\r\n";
    res += "    The channel is used to change the topic of a channel\r\n";
    send(_user.get_fd(), res.c_str(), res.size(), 0);
}

static void help_invite(User &_user) {
    string res = "INVITE :INVITE <#channel> <nickname>\r\n";
    res += "    The channel is used to invite a user to a channel\r\n";
    send(_user.get_fd(), res.c_str(), res.size(), 0);
}

static void help_version(User &_user) {
    string res = "VERSION :VERSION\r\n";
    res += "    The version is used to check the version of the server\r\n";
    send(_user.get_fd(), res.c_str(), res.size(), 0);
}

static void help_help(User &_user) {
    string res = "HELP :HELP <command>\r\n";
    send(_user.get_fd(), res.c_str(), res.size(), 0);
}

static void send_how_to_connect(User &_user) {
    string res = "You need to connect to the server first\r\n";
    send(_user.get_fd(), res.c_str(), res.size(), 0);
    help_pass(_user);
    help_nick(_user);
    help_user(_user);
}

static void send_how_to_use(User &_user) {
    string res = "You can use the following commands:\r\n";
    send(_user.get_fd(), res.c_str(), res.size(), 0);
    help_join(_user);
    help_part(_user);
    help_privmsg(_user);
    help_quit(_user);
    help_ping(_user);
    help_kick(_user);
    help_mode(_user);
    help_topic(_user);
    help_invite(_user);
    help_time(_user);
    help_version(_user);
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
    else if (command == "TIME")
        help_time(_user);
    else if (command == "TOPIC")
        help_topic(_user);
    else if (command == "USER")
        help_user(_user);
}