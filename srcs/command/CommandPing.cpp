#include "Command.hpp"

#define RPL_PING(source, token) ":" + source + " PONG :" + token

void Command::ping(void)
{
    // string source = _server.get_server_name();
    string source = "127.0.0.1";
    string token = _parser.get_message();
    string response = RPL_PING(source, token);
    cout << response << endl;
    send(_user.get_fd(), response.c_str(), response.size(), 0);
}