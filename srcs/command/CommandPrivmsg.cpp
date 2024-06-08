#include "Command.hpp"

// privmsg <nickname> <message>
static void send_message_to_user(Server &_server, Parser &_parser, User &_user) {
	if (_server.findUserByNick(_parser.get_args().at(0)) == NULL)
		throw runtime_error(err_401(_user, _parser.get_args().at(0)));

	string message = USER_IDENTIFIER(_user.get_nickname(), _user.get_username());
	message += _user.get_nickname() + " PRIVMSG " + _parser.get_args().at(0) + " ";
	for (size_t i = 1; i < _parser.get_args().size(); i++) {
		message += _parser.get_args().at(i);
		if (i != _parser.get_args().size() - 1)
			message += " ";
	}
	message += "\r\n";
	send(_server.findUserByNick(_parser.get_args().at(0))->get_fd(), message.c_str(), message.size(), 0);
}

static void send_message_to_channel(Server &_server, Parser &_parser, User &_user) {
	Channel* channel = _server.findChannelByName(_parser.get_args().at(0));
	if (channel == NULL)
		throw runtime_error(err_401(_user, _parser.get_args().at(0)));

	if (channel->is_client(_user.get_fd()) == false)
		throw runtime_error(err_442(_user, channel->get_channel_name()));

	set<int> clients = channel->get_clients();
	for (set<int>::iterator it = clients.begin(); it != clients.end(); ++it) {
		if (*it == _user.get_fd())
			continue;
		string message = USER_IDENTIFIER(_user.get_nickname(), _user.get_username());
		message += _user.get_nickname() + " PRIVMSG " + channel->get_channel_name() + " ";
		for (size_t i = 1; i < _parser.get_args().size(); i++) {
			message += _parser.get_args().at(i);
			if (i != _parser.get_args().size() - 1)
				message += " ";
		}
		message += "\r\n";
		send(*it, message.c_str(), message.size(), 0);
	}
}

static void announce(Server &_server, Parser &_parser, User &_user) {
	if (_parser.get_args().size() < 2)
		throw runtime_error(err_411(_user));
	string userID = USER_IDENTIFIER("bot", "bot");
	string message = userID + "bot PRIVMSG " + _parser.get_args().at(0) + " ";
	for (size_t i = 2; i < _parser.get_args().size(); i++) {
		message += _parser.get_args().at(i);
		if (i != _parser.get_args().size() - 1)
			message += " ";
	}
	message += "\r\n";
	set<User *> users = _server.get_users();
	for (set<User *>::iterator it = users.begin(); it != users.end(); ++it)
		send((*it)->get_fd(), message.c_str(), message.size(), 0);
}

static void channel_list(Server &_server, Parser &_parser, User &_user) {
	string userID = USER_IDENTIFIER("bot", "bot");
	string message = userID + "bot PRIVMSG " + _parser.get_args().at(0) + " ";
	set<Channel *> channels = _server.get_channels();
	for (set<Channel *>::iterator it = channels.begin(); it != channels.end(); ++it) {
		string channel_message = message;
		channel_message += (*it)->get_channel_name();
		channel_message += "\r\n";
		send(_user.get_fd(), channel_message.c_str(), channel_message.size(), 0);
	}
}

static void join_channel_list(Server &_server, Parser &_parser, User &_user) {
	string userID = USER_IDENTIFIER("bot", "bot");
	string message = userID + "bot PRIVMSG " + _parser.get_args().at(0) + " ";
	set<Channel *> channels = _server.get_channels();
	for (set<Channel *>::iterator it = channels.begin(); it != channels.end(); ++it) {
		string channel_message = message;
		channel_message += (*it)->get_channel_name();
		channel_message += "\r\n";
		if ((*it)->is_client(_user.get_fd()) == true || (*it)->is_operator(_user.get_fd()) == true)
			send(_user.get_fd(), channel_message.c_str(), channel_message.size(), 0);
	}
}

static void invite_channel_list(Server &_server, Parser &_parser, User &_user) {
	string userID = USER_IDENTIFIER("bot", "bot");
	string message = userID + "bot PRIVMSG " + _parser.get_args().at(0) + " ";
	set<Channel *> channels = _server.get_channels();
	for (set<Channel *>::iterator it = channels.begin(); it != channels.end(); ++it) {
		string channel_message = message;
		channel_message += (*it)->get_channel_name();
		channel_message += "\r\n";
		if ((*it)->is_invited(_user.get_fd()) == true)
			send(_user.get_fd(), channel_message.c_str(), channel_message.size(), 0);
	}
}

static void channel(Server &_server, Parser &_parser, User &_user) {
	if (_parser.get_args().size() != 3)
		throw runtime_error(err_461(_user, "bot"));
	if (_parser.get_args().at(2) == "list")
		channel_list(_server, _parser, _user);
	else if (_parser.get_args().at(2) == "join")
		join_channel_list(_server, _parser, _user);
	else if (_parser.get_args().at(2) == "invite")
		invite_channel_list(_server, _parser, _user);
	else
		throw runtime_error(err_696(_user));
}

static void help_bot(Parser &_parser, User &_user) {
	if (_parser.get_args().size() != 2)
		throw runtime_error(err_461(_user, "bot"));

	string userID = USER_IDENTIFIER("bot", "bot");

	string announce_msg = userID + "bot PRIVMSG " + _parser.get_args().at(0) + " announce <message>\r\n";
	send(_user.get_fd(), announce_msg.c_str(), announce_msg.size(), 0);

	string channel_msg = userID + "bot PRIVMSG " + _parser.get_args().at(0) + " channel list | channel join | channel invite \r\n";
	send(_user.get_fd(), channel_msg.c_str(), channel_msg.size(), 0);
}

/*
* privmsg bot :sendfile nick path
* privmsg bot :getfile filename path
*/
void Command::send_bot() {
	if (_parser.get_args().at(1) == "announce" || _parser.get_args().at(1) == ":announce")
		announce(_server, _parser, _user);
	else if (_parser.get_args().at(1) == "channel" || _parser.get_args().at(1) == ":channel")
		channel(_server, _parser, _user);
	else if (_parser.get_args().at(1) == "help" || _parser.get_args().at(1) == ":help")
		help_bot(_parser, _user);
	else if (_parser.get_args().at(1) == "sendfile" || _parser.get_args().at(1) == ":sendfile") {
		sendfile();
	}
	else if (_parser.get_args().at(1) == "getfile" || _parser.get_args().at(1) == ":getfile") {
		getfile();
	}
	else
		throw runtime_error(err_696(_user));
}

void Command::privmsg()
{
	// check if the user in the channel
	try {
		if (_user.get_ready_to_connect() == false)
			throw runtime_error(err_451(_user));
		if (_parser.get_args().size() < 2)
			throw runtime_error(err_411(_user));
		if (_parser.get_args().at(0).at(0) == '#')
			send_message_to_channel(_server, _parser, _user);
		else if (_parser.get_args().at(0) == "bot")
			send_bot();
		else
			send_message_to_user(_server, _parser, _user);
	}
	catch (const exception &e) {
		send(_user.get_fd(), e.what(), strlen(e.what()), 0);
	}
}
