#include "Command.hpp"

void Command::ping(void)
{
    if (_parser.get_args().size() != 1)
    {
        string error_message = "PING :Not enough parameters\r\n";
        send(_user.get_fd(), error_message.c_str(), error_message.size(), 0);
        return ;
    }
    string response;
    response += "PONG ";
    response += _parser.get_args().at(0);
    response += "\r\n";
    send(_user.get_fd(), response.c_str(), response.size(), 0);
}