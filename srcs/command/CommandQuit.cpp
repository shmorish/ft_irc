#include "Command.hpp"

void Command::quit()
{
    send(_user.get_fd(), "Goodbye\n", 8, 0);
    close(_user.get_fd());
    _server.removeUser(&_user);
}