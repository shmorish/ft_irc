#include "Command.hpp"

void Command::version()
{
    string res = USER_IDENTIFIER(_user.get_nickname(), _user.get_username());
    res += " 351 ";
    res += _user.get_nickname();
    res += " :Version ";
    res += SERVER_VERSION;
    res += "\r\n";
    send(_user.get_fd(), res.c_str(), res.size(), 0);
}