#include "Command.hpp"

static void is_correct_input(const vector<string> &args, User _user){
	if (args.size() < 1 || args.size() > 2)
		throw runtime_error(err_461(_user, "TOPIC"));
	if (args.at(0).at(0) != '#')
		throw runtime_error(err_476(_user));
}

void    Command::topic(){
	// TOPIC #channel_name
	// TOPIC #channel_name :<topic>
	try{
		is_correct_input(_parser.get_args(), _user);
		if(_server.findChannelByName(_parser.get_args().at(0)) == NULL)
			throw runtime_error(err_476(_user));
		Channel *channel = _server.findChannelByName(_parser.get_args().at(0));
		if(channel->is_client(_user.get_fd()) == false)
			throw runtime_error(err_442(_user, channel->get_channel_name()));
		if(_parser.get_args().size() == 1){
			string topic = channel->get_topic();
			if (topic == "")
				throw runtime_error(err_331(_user, channel->get_channel_name()));
			topic = channel->get_channel_name() + ":" + topic + "\r\n";
			send(_user.get_fd(), topic.c_str(), topic.size(), 0);
		}
		if(_parser.get_args().size() == 2){
			if((channel->get_mode() & Channel::TopicOpOnly) && channel->is_operator(_user.get_fd()) == false)
				throw runtime_error(err_482(_user, channel->get_channel_name()));
			channel->set_topic(_parser.get_args().at(1).substr(0));
		}
	}catch(const exception &e){
		send(_user.get_fd(), e.what(), strlen(e.what()), 0);
	}
}
