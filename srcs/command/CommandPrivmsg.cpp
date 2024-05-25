#include "Command.hpp"

void Command::privmsg()
{
    // check if the user in the channel
    try {
        if (_parser.get_args().size() < 2) {
            throw runtime_error("Too few arguments\n");
        }
        if (_parser.get_args().at(0).at(0) == '#') {
            // privmsg <channel_name> <message>
            // channel
            // is joined
            if (_server.findChannelByName(_parser.get_args().at(0)) == NULL) {
                throw runtime_error("Channel not found\n");
            }
            // if (_server.findChannelByName(_parser.get_args().at(0))->findUserByFd(_user.get_fd()) == NULL) {
            //     throw runtime_error("You are not in the channel\n");
            // }

        } else {
            // privmsg <nickname> <message>
            // nickname
        }
         
    }
    catch (const exception &e) {
        send(_user.get_fd(), e.what(), strlen(e.what()), 0);
    }
}
        