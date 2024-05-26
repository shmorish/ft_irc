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
		if(/*自分がこのチャンネルにいなかったら*/)
				throw runtime_error("User not found in this channel");
		if(_parser.get_args().size() == 2)
			// 自分自身がこのチャンネルに参加しているかどうかを確認
			// 自分自身がこのチャンネルのオペレーターかどうかを確認
			// <topic>が有効なものかどうかを確認
			_server.findChannelByName(_parser.get_args().at(0))->set_topic(_parser.get_args().at(1).substr(1));
	}catch(const exception &e){
		send(_user.get_fd(), e.what(), strlen(e.what()), 0);
	}
}
