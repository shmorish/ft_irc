#include "Command.hpp"

void    Command::invite()
{
    // INVETE #channel_name nickname
    try{
        if(_parser.get_args().size() < 2)
            throw runtime_error("Too few arguments");
        if(_parser.get_args().size() > 2)
            throw runtime_error("Too many arguments");
        if(_parser.get_args().at(0).at(0) == '#'){
            if(_server.findChannelByName(_parser.get_args().at(0)) == NULL)
                throw runtime_error("Channel not found");
            // 自分自身がこのチャンネルに参加しているかどうかを確認
            // 自分自身がこのチャンネルのオペレーターかどうかを確認
            if (_server.findChannelByName(\
                _parser.get_args().at(0))->get_clients().find(_user.get_fd()) == \
                _server.findChannelByName(_parser.get_args().at(0))->get_clients().end())
            {
                //ivite user to channel
            }   
        }
    }catch(const exception &e){
        send(_user.get_fd(), e.what(), strlen(e.what()), 0);
    }
        
    // Channel *channel = _server.get_channel(channel_name);
    // if (channel == NULL)
    //     throw runtime_error("Channel not found");
    // if (channel->is_operator(_user.get_nickname()) == false)
    //     throw runtime_error("You are not channel operator");
    // User *user = _server.get_user(nickname);
    // if (user == NULL)
    //     throw runtime_error("User not found");
    // if (channel->is_invited(user->get_nickname()) == true)
    //     throw runtime_error("User is already invited");
    // channel->add_invited(user->get_nickname());
    // user->add_invited_channel(channel->get_channel_name());
    // _server.send_reply(_user.get_fd(), RPL_INVITING, user->get_nickname());
    // _server.send_reply(user->get_fd(), RPL_INVITED, channel->get_channel_name());
}