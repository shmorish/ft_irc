#include "Command.hpp"

bool invalid_char(string str) {
	string invalid = "[]\\`_^{|} ,:;<>@$%&!*()+?\"'";
	for (size_t i = 0; i < str.size(); i++) {
		if (invalid.find(str[i]) != string::npos)
			return true;
	}
	return false;
}

static void is_valid_channel_name(const vector<string> &args){
	if (args.empty() == true) {
		throw runtime_error("channel is empty\n");
	}
	if (args.size() != 1) {
		throw runtime_error("wrong number of arguments\n");
	}
	if (args.at(0).size() > 200) {
		throw runtime_error("channel is too long\n");
	}
	if (args.at(0).at(0) != '#') {
		throw runtime_error("channel must start with #\n");
	}
	if (invalid_char(args.at(0))) {
		throw runtime_error("channel contains invalid characters\n");
	}
}

void Command::join()
{
	try {
		is_valid_channel_name(_parser.get_args());
		if(_user.get_ready_to_connect() == false) {
			throw runtime_error("You are not connected\n");
		}
	} catch (const exception &e) {
    
		send(_user.get_fd(), e.what(), strlen(e.what()), 0);
		// cerr << e.what() << endl;
		return ;
	}

	if (_server.findChannelByName(_parser.get_args().at(0)) == NULL) {
		_server.get_channels().insert(new Channel(_parser.get_args().at(0)));
		_server.findChannelByName(_parser.get_args().at(0))->add_client(_user.get_fd());
		_server.findChannelByName(_parser.get_args().at(0))->add_operator(_user.get_fd());
		string message = "You have created and joined the channel\n";
		send(_user.get_fd(), "You have joined the channel\n", 28, 0);
	}
	else {
		try {
			set<int> channels = _server.findChannelByName(_parser.get_args().at(0))->get_clients();
			for (set<int>::iterator it = channels.begin(); it != channels.end(); it++)
				if (*it == _user.get_fd())
					throw runtime_error("You are already in this channel\n");

			if (_server.findChannelByName(_parser.get_args().at(0))->channel_is_full())
				throw runtime_error("Channel is full\n");

			_server.findChannelByName(_parser.get_args().at(0))->add_client(_user.get_fd());
			send(_user.get_fd(), "You have joined the channel\n", 28, 0);
		} catch (const exception &e) {
			send(_user.get_fd(), e.what(), strlen(e.what()), 0);
      // cerr << e.what() << endl;
		}
	}
}
