#include "Command.hpp"

// 341 345 346 347 + error のresponseの対応

static void is_correct_input(const vector<string> &args, User _user){
    if (args.size() != 2)
        throw runtime_error(err_461(_user, "INVITE"));
    if (_user.get_ready_to_connect() == false)
        throw runtime_error(err_451(_user));
    if (args.at(0).at(0) != '#')
        throw runtime_error(err_403(_user, args.at(0)));
}

void    Command::invite()
{
    // INVETE #channel_name nickname
    try{
        is_correct_input(_parser.get_args(), _user);
        Channel* channel = _server.findChannelByName(_parser.get_args().at(0));
        if(channel == NULL)
            throw runtime_error(err_403(_user, _parser.get_args().at(0)));
        if(channel->is_operator(_user.get_fd()) == false)
            throw runtime_error(err_482(_user, channel->get_channel_name()));
        if(channel->channel_is_full() == true)
            throw runtime_error(err_471(_user, channel->get_channel_name()));
        User* user = _server.findUserByNick(_parser.get_args().at(1));
        if (user == NULL)
            throw runtime_error("No such user");
        if (channel->get_clients().find(user->get_fd()) != channel->get_clients().end())
        {
            channel->add_client(user->get_fd());
            string res = success_response(*user, "JOIN", channel->get_channel_name());
            send(user->get_fd(), res.c_str(), res.size(), 0);
        } else /*なぜか機能していない*/
            throw runtime_error("He is already in this channel");
    }catch(const exception &e){
        send(_user.get_fd(), e.what(), strlen(e.what()), 0);
    }
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

