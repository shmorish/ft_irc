#include "Command.hpp"

static void	is_correct_input(const vector<string> &args, User _user) {
	if (args.size() != 3)
		throw runtime_error(err_461(_user, "KICK"));
	else if (args.at(0).at(0) != '#')
		throw runtime_error(err_461(_user, "KICK"));
}

// KICK #channel_name <client_name>
void	Command::kick() {
	try {
		is_correct_input(_parser.get_args(), _user);
		string channel_name = _parser.get_args().at(0);
		string client_name = _parser.get_args().at(1);
		Channel *channel = _server.findChannelByName(channel_name);
		if(channel == NULL)
			throw runtime_error(err_403(_user, channel_name));
		if(_server.findUserByNick(client_name) == NULL)
			throw runtime_error(err_401(_user, client_name));
		int client_fd = _server.findUserByNick(client_name)->get_fd();
		if (channel->is_client(client_fd) == false)
			throw runtime_error(err_401(_user, client_name));
		if (channel->is_operator(_user.get_fd()) == false)
			throw runtime_error(err_482(_user, channel_name));
		// 第一引数Userがkickする人の方
		string res = success_response(_user, "PART", channel_name);
		_server.sendMsgToChannel(channel_name, res);
		res = success_response(_user, "KICK", channel_name);
		_server.sendMsgToChannel(channel_name, res);
		_server.sendMsgToChannel(channel_name, res);
		channel->remove_client(client_fd);
		channel->remove_can_talk_in_mod_channel(client_fd);
		channel->remove_operator(client_fd);
	} catch(const exception &e) {
		send(_user.get_fd(), e.what(), strlen(e.what()), 0);
	}
}
