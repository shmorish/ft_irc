#include "Command.hpp"


// ERR_NEEDMOREPARAMS (461): コマンドに必要なパラメータが不足している場合に送られます。例えば、PARTコマンドを使用する際にチャンネル名を指定しなかった場合などです。
// ERR_NOSUCHCHANNEL (403): 存在しない、または参加していないチャンネルから退出しようとした場合に返されます。
// ERR_NOTONCHANNEL (442): ユーザーが指定したチャンネルに実際には参加していない場合にこのエラーが返されます。

string err_461(User user, string command)
{
    string res;
    res = USER_IDENTIFIER(user.get_nickname(), user.get_username());
    res += " 461 ";
    res += user.get_nickname();
    res += " ";
    res + command;
    res += " ";
    res += ":Not enough parameters";
    res += "\r\n";
    return res;
}

string err_403(User user, string channel_name)
{
    string res;
    res = USER_IDENTIFIER(user.get_nickname(), user.get_username());
    res += " 403 ";
    res += user.get_nickname();
    res += " ";
    res += channel_name;
    res += ":No such channel";
    res += "\r\n";
    return res;
}

string err_442(User user, string channel_name)
{
    string res;
    res = USER_IDENTIFIER(user.get_nickname(), user.get_username());
    res += " 442 ";
    res += user.get_nickname();
    res += " ";
    res += channel_name;
    res += ":You're not on that channel";
    res += "\r\n";
    return res;
}

string part_success(User user, string channel_name)
{
    string res;
    res = USER_IDENTIFIER(user.get_nickname(), user.get_username());
    res += " PART ";
    res += channel_name;
    res += "\r\n";
    return res;
}

void Command::part()
{
    try {
        if (_parser.get_args().size() != 2) {
            throw runtime_error(err_461(_user, "PART"));
        }
        string channel_name = _parser.get_args().at(0);
        if (channel_name[0] != '#') {
            throw runtime_error(err_403(_user, _parser.get_args().at(0)));
        }
        Channel* channel = _server.findChannelByName(channel_name);
        if (channel == NULL) {
            throw runtime_error(err_403(_user, channel_name));
        }
        if (channel->is_client(_user.get_fd()) == false) {
            throw runtime_error(err_442(_user, channel_name));
        }
        string res = part_success(_user, channel_name);
        _server.sendMsgToChannel(channel_name, res);
        channel->remove_client(_user.get_fd());
        channel->remove_invited(_user.get_fd());
        channel->remove_can_talk_in_mod_channel(_user.get_fd());
        channel->remove_operator(_user.get_fd());
    }
    catch (const exception &e) {
        send(_user.get_fd(), e.what(), strlen(e.what()), 0);
    }
}
