#include "Command.hpp"

void Command::ping(void)
{
    // if (_parser.get_args().size() != 1)
    // {
    //     string error_message = "PING :Not enough parameters\r\n";
    //     send(_user.get_fd(), error_message.c_str(), error_message.size(), 0);
    //     return ;
    // }
    // string response = "whatyouwant!ishikawatsubasa@localhost PONG :whatyouwant";
    string response;
    response += USER_IDENTIFIER(_user.get_nickname(), _user.get_username());
    response += " PONG ";
    response += _user.get_nickname();
    response += "\r\n";

    // cout << "Response: " << response << endl;

    send(_user.get_fd(), response.c_str(), response.size(), 0);
}
