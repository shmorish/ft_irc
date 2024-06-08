#include "Command.hpp"

void Command::quit() {
    send(_user.get_fd(), "Goodbye\n", 8, 0);
    set<Channel *> channels = _server.get_channels();
    for (set<Channel *>::iterator it = channels.begin(); it != channels.end(); ++it) {
        (*it)->remove_client(_user.get_fd());
        (*it)->remove_invited(_user.get_fd());
        (*it)->remove_can_talk_in_mod_channel(_user.get_fd());
        (*it)->remove_operator(_user.get_fd());
        (*it)->remove_banned(_user.get_fd());
        if ((*it)->get_clients().size() == 0) {
            delete *it;
            _server.get_channels().erase(*it);
        }
    }
    close(_user.get_fd());
    _server.removeUser(&_user);
}
