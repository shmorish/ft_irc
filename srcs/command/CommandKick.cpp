#include "Command.hpp"

static void	is_correct_input(const vector<string> &args){
	if (args.size() < 2)
		throw runtime_error("Too few arguments\n");
	if (args.size() > 2)
		throw runtime_error("Too many arguments\n");
	if (args.at(0).at(0) != '#')
		throw runtime_error("Channel name must start with #\n");

}

void	Command::kick(){
	// KICK #channel_name <client_name>
	try{
		is_correct_input(_parser.get_args());
		if(_server.findChannelByName(_parser.get_args().at(0)) == NULL)
			throw runtime_error("Channel not found\n");
		if(_server.findUserByNick(_parser.get_args().at(1)) == NULL)
			throw runtime_error("User not found\n");
		if (_server.findChannelByName(_parser.get_args().at(0))->is_client(_user.get_fd()) == false)
			throw runtime_error("User not in channel\n");
		if (_server.findChannelByName(_parser.get_args().at(0))->is_operator(_user.get_fd()) == false)
			throw runtime_error("You are not operator\n");
		_server.findChannelByName(_parser.get_args().at(0))->remove_client(_server.findUserByNick(_parser.get_args().at(1))->get_fd());
	} catch(const exception &e) {
		send(_user.get_fd(), e.what(), strlen(e.what()), 0);
	}
}
