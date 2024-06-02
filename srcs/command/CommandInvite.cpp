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
    // INVITE #channel_name nickname
    try {
        is_correct_input(_parser.get_args(), _user);
        string channel_name = _parser.get_args().at(0);
        string invite_nickname = _parser.get_args().at(1);
        Channel* channel = _server.findChannelByName(channel_name);
        if(channel == NULL)
            throw runtime_error(err_403(_user, channel_name));
        if(channel->is_operator(_user.get_fd()) == false)
            throw runtime_error(err_482(_user, channel_name));
        if(channel->channel_is_full() == true)
            throw runtime_error(err_471(_user, channel_name));
        User* user = _server.findUserByNick(invite_nickname);
        if (user == NULL)
            throw runtime_error(err_401(_user, invite_nickname));
        if (channel->is_client(user->get_fd()) == true)
            throw runtime_error(err_443(_user, channel_name));
        else if (channel->is_invited(user->get_fd()) == true)
            throw runtime_error(err_443(_user, channel_name)); // what is already invited error code ???
        else {
            channel->add_invited(user->get_fd());
            string res = response341(_user, channel_name, invite_nickname);
            send(user->get_fd(), res.c_str(), res.size(), 0);
        }
    } catch(const exception &e) {
        send(_user.get_fd(), e.what(), strlen(e.what()), 0);
    }
}
