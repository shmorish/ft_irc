#include "Command.hpp"

void Command::sendfile() {
    try {
        if (_user.get_ready_to_connect() == false)
            throw runtime_error(err_451(_user));
    } catch (exception &e) {
        send(_user.get_fd(), e.what(), strlen(e.what()), 0);
    }
}