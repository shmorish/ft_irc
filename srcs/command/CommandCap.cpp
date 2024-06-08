#include "Command.hpp"

void Command::cap() {
    string mes = "CAP * LS :\r\n";
    send(_user.get_fd(), mes.c_str(), mes.size(), 0);
}
