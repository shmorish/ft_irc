#include "Command.hpp"

static void	is_correct_input(const vector<string> &args){
	if (args.size() < 2)
		throw runtime_error("Too few arguments");
	if (args.size() > 2)
		throw runtime_error("Too many arguments");
	if (args.at(0).at(0) != '#')
		throw runtime_error("Channel name must start with #");

}

void	Command::kick(){
	// KICK #channel_name <client_name>
	try{
		is_correct_input(_parser.get_args());
		if(_parser.get_args().at(0).at(0) == '#'){
			if(_server.findChannelByName(_parser.get_args().at(0)) == NULL)
				throw runtime_error("Channel not found");
			if(_server.findUserByNick(_parser.get_args().at(1)) == NULL)
				throw runtime_error("User not found");
			// if(_server.findChannelByName(_parser.get_args().at(0))->findClientByNick(_parser.get_args().at(1)) == NULL)
			// 	throw runtime_error("User not in channel");
			// if(_server.findChannelByName(_parser.get_args().at(0))->findOperatorByNick(_user.get_nickname()) == NULL)
			// 	throw runtime_error("You are not operator");
			_server.findChannelByName(_parser.get_args().at(0))->remove_client(_server.findUserByNick(_parser.get_args().at(1))->get_fd());
		}
	}catch(const exception &e){
		send(_user.get_fd(), e.what(), strlen(e.what()), 0);
	}
}
