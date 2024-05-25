#include "Command.hpp"

// privmsg <nickname> <message>
static void title(Server &_server, Parser &_parser, User &_user) {
  if (_server.findUserByNick(_parser.get_args().at(0)) == NULL)
    throw runtime_error("User not found\n");
  string message = _user.get_nickname() + " says: ";
  for (size_t i = 1; i < _parser.get_args().size(); i++) {
    message += _parser.get_args().at(i);
    if (i != _parser.get_args().size() - 1)
      message += " ";
  }
  message += "\n";
  send(_server.findUserByNick(_parser.get_args().at(0))->get_fd(), message.c_str(), message.size(), 0);
}

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
            title(_server, _parser, _user);
        }

    }
    catch (const exception &e) {
        send(_user.get_fd(), e.what(), strlen(e.what()), 0);
    }
}
