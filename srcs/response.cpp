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

// ERR_TOOMANYCHANNELS (405): ユーザーが同時に参加できるチャンネルの最大数に達している場合に返されます。
string err_405(User user)
{
    string res;
    res = USER_IDENTIFIER(user.get_nickname(), user.get_username());
    res += " 405 ";
    res += user.get_nickname();
    res += " :You have joined too many channels";
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

// ERR_NOTREGISTERED (451): "You have not registered" というメッセージを伴い、クライアントがネットワークに対してユーザー名（NICK）や実際の名前（USERコマンドの一部）の登録が完了していない状態でコマンドを実行しようとしたときに発生します。
string err_451(User user)
{
    string res;
    res = USER_IDENTIFIER(user.get_nickname(), user.get_username());
    res += " 451 ";
    res += user.get_nickname();
    res += " :You have not registered";
    res += "\r\n";
    return res;
}

// ERR_NEEDMOREPARAMS (461): コマンドに必要なパラメータが不足している場合に送られます。
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

string err_471(User user, string channel_name)
{
    string res;
    res = USER_IDENTIFIER(user.get_nickname(), user.get_username());
    res += " 471 ";
    res += user.get_nickname();
    res += " ";
    res += channel_name;
    res += " :Cannot join channel (+l)";
    res += "\r\n";
    return res;
}

// ERR_BADCHANMASK (476): 指定されたチャンネル名が無効な形式である場合に返されます。
string err_476(User user)
{
    string res;
    res = USER_IDENTIFIER(user.get_nickname(), user.get_username());
    res += " 476 ";
    res += user.get_nickname();
    res += " :Invalid channel name";
    res += "\r\n";
    return res;
}

string success_response(User user, string command, string arg)
{
    string res;
    res = USER_IDENTIFIER(user.get_nickname(), user.get_username());
    res += " ";
    res += command;
    res += " ";
    res += arg;
    res += "\r\n";
    return res;
}