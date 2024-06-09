#include "Command.hpp"

// BAN #channel_name <client_name> [reason]
void Command::ban() {
    try {
        if (_parser.get_args().size() != 3)
            throw runtime_error(err_461(_user, "BAN"));
        string channel_name = _parser.get_args().at(0);
        Channel *channel = _server.findChannelByName(channel_name);
        if (channel == NULL)
            throw runtime_error(err_403(_user, channel_name));
        string banned_nickname = _parser.get_args().at(1);
        User *banned_user = _server.findUserByNick(banned_nickname);
        kick();
        channel->add_banned(banned_user->get_fd());
    } catch (const exception &e) {
        send(_user.get_fd(), e.what(), strlen(e.what()), 0);
    }
}