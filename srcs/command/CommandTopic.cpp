#include "Command.hpp"

static void is_correct_input(const vector<string> &args){
	if (args.size() < 2)
		throw runtime_error("Too few arguments");
	if (args.size() > 3)
		throw runtime_error("Too many arguments");
	if (args.at(0).at(0) != '#')
		throw runtime_error("Channel name must start with #");
}

void    Command::topic(){
	// TOPIC #channel_name
	// TOPIC #channel_name :<topic>
	try{
		is_correct_input(_parser.get_args());
		if(_server.findChannelByName(_parser.get_args().at(0)) == NULL)
			throw runtime_error("Channel not found");
		Channel *channel = _server.findChannelByName(_parser.get_args().at(0));
		if(channel->is_client(_user.get_fd()) == false)
			throw runtime_error("User not found in this channel");
		if(_parser.get_args().size() == 2){
			string topic = _server.findChannelByName(_parser.get_args().at(0))->get_topic();
			send(_user.get_fd(), topic.c_str(), topic.size(), 0);
		}
		if(_parser.get_args().size() == 3){
			if(channel->is_operator(_user.get_fd()) == false)
				throw runtime_error("You are not operator");
			_server.findChannelByName(_parser.get_args().at(0))->set_topic(_parser.get_args().at(1).substr(1));
		}
	}catch(const exception &e){
		send(_user.get_fd(), e.what(), strlen(e.what()), 0);
	}
}
