#include "Command.hpp"

void Command::part()
{
    try {
        if (_parser.get_args().size() < 1) {
            throw runtime_error("Too few arguments\n");
        }
        if (_parser.get_args().at(0).at(0) != '#') {
            throw runtime_error("Invalid channel name\n");
        }
        Channel* channel = _server.findChannelByName(_parser.get_args().at(0));
        if (channel == NULL) {
            throw runtime_error("Channel not found\n");
        }
        if (channel->is_client(_user.get_fd()) == false) {
            throw runtime_error("You are not in this channel\n");
        }
        channel->remove_client(_user.get_fd());
        channel->remove_invited(_user.get_fd());
        channel->remove_operator(_user.get_fd());
        send(_user.get_fd(), "You have left the channel\n", 26, 0);
    }
    catch (const exception &e) {
        send(_user.get_fd(), e.what(), strlen(e.what()), 0);
    }
}