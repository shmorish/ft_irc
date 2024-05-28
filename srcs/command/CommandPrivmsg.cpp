#include "Command.hpp"

// privmsg <nickname> <message>
static void send_message_to_user(Server &_server, Parser &_parser, User &_user) {
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

static void send_message_to_channel(Server &_server, Parser &_parser, User &_user) {
	Channel* channel = _server.findChannelByName(_parser.get_args().at(0));
	if (channel == NULL)
		throw runtime_error("Channel not found\n");
	if (channel->is_client(_user.get_fd()) == false)
		throw runtime_error("You are not in this channel\n");

	set<int> clients = channel->get_clients();
	for (std::set<int>::iterator it = clients.begin(); it != clients.end(); ++it) {
		string message = _user.get_nickname() + " says: ";
		for (size_t i = 0; i < _parser.get_args().size(); i++) {
			message += _parser.get_args().at(i);
		if (i != _parser.get_args().size() - 1)
			message += " ";
		}
		message += "\n";
		send(*it, message.c_str(), message.size(), 0);
	}
}


void Command::privmsg()
{
	// check if the user in the channel
	try {
		if (_parser.get_args().size() < 2) {
			throw runtime_error("Too few arguments\n");
		}
		if (_parser.get_args().at(0).at(0) == '#') {
			send_message_to_channel(_server, _parser, _user);
		} else {
			send_message_to_user(_server, _parser, _user);
		}

	}
	catch (const exception &e) {
		send(_user.get_fd(), e.what(), strlen(e.what()), 0);
	}
}
