#include "response.hpp"
#include "User.hpp"

// ERR_NOSUCHCHANNEL (403): 存在しない、または参加していないチャンネルから退出しようとした場合に返されます。
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

// ERR_NOTONCHANNEL (442): ユーザーが指定したチャンネルに実際には参加していない場合にこのエラーが返されます。
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

// ERR_NEEDMOREPARAMS (461): コマンドに必要なパラメータが不足している場合に送られます。例えば、PARTコマンドを使用する際にチャンネル名を指定しなかった場合などです。
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
