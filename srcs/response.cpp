#include "response.hpp"
#include "User.hpp"

// RPL_NOTOPIC (331): チャンネルにトピックが設定されていない場合に返されます。
string err_331(User user, string channel_name)
{
    string res;
    res = USER_IDENTIFIER(user.get_nickname(), user.get_username());
    res += " 331 ";
    res += user.get_nickname();
    res += " ";
    res += channel_name;
    res += " :No topic is set";
    res += "\r\n";
    return res;
}

// ERR_NOSUCHNICK (401): 指定されたニックネームが存在しない場合に返されます。
string err_401(User user, string nickname)
{
    string res;
    res = USER_IDENTIFIER(user.get_nickname(), user.get_username());
    res += " 401 ";
    res += user.get_nickname();
    res += " ";
    res += nickname;
    res += " :No such nick/channel";
    res += "\r\n";
    return res;
}

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

string err_411(User user)
{
    string res;
    res = USER_IDENTIFIER(user.get_nickname(), user.get_username());
    res += " 411 ";
    res += user.get_nickname();
    res += " :No recipient given (PRIVMSG)";
    res += "\r\n";
    return res;
}

// ERR_NONICKNAMEGIVEN (431): ニックネームが指定されていない場合に返されます。
string err_431(User user)
{
    string res;
    res = USER_IDENTIFIER(user.get_nickname(), user.get_username());
    res += " 431 ";
    res += user.get_nickname();
    res += " :No nickname given";
    res += "\r\n";
    return res;
}

// ERR_ERRONEUSNICKNAME (432): ニックネームが無効な形式である場合に返されます。
string err_432(User user, string nickname)
{
    string res;
    res = USER_IDENTIFIER(user.get_nickname(), user.get_username());
    res += " 432 ";
    res += user.get_nickname();
    res += " ";
    res += nickname;
    res += " :Erroneous nickname";
    res += "\r\n";
    return res;
}

// ERR_NICKNAMEINUSE (433): ユーザーが指定したニックネームを既に他のユーザーが使用している場合に返されます。
string err_433(User user, string nickname)
{
    string res;
    res = USER_IDENTIFIER(user.get_nickname(), user.get_username());
    res += " 433 ";
    res += user.get_nickname();
    res += " ";
    res += nickname;
    res += " :Nickname is already in use";
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

// ERR_USERONCHANNEL (443): ユーザーが既に指定したチャンネルに参加している場合に返されます。
string err_443(User user, string channel_name)
{
    string res;
    res = USER_IDENTIFIER(user.get_nickname(), user.get_username());
    res += " 443 ";
    res += user.get_nickname();
    res += " ";
    res += channel_name;
    res += ":is already on channel";
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

// ERR_ALREADYREGISTERED (462): ユーザーが既に登録されている場合に返されます。
string err_462(User user)
{
    string res;
    res = USER_IDENTIFIER(user.get_nickname(), user.get_username());
    res += " 462 ";
    res += user.get_nickname();
    res += " :You may not reregister";
    res += "\r\n";
    return res;
}

string err_464(User user)
{
    string res;
    res = USER_IDENTIFIER(user.get_nickname(), user.get_username());
    res += " 464 ";
    res += user.get_nickname();
    res += " :Incorrect password";
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

string err_472(User user)
{
    string res;
    res = USER_IDENTIFIER(user.get_nickname(), user.get_username());
    res += " 472 ";
    res += user.get_nickname();
    res += " :is unknown mode char to me";
    res += "\r\n";
    return res;
}

// ERR_INVITEONLYCHAN (473): チャンネルが招待制で、ユーザーが招待されていない場合に返されます。
string err_473(User user, string channel_name)
{
    string res;
    res = USER_IDENTIFIER(user.get_nickname(), user.get_username());
    res += " 473 ";
    res += user.get_nickname();
    res += " ";
    res += channel_name;
    res += " :Cannot join channel (+i)";
    res += "\r\n";
    return res;
}

// ERR_BANNEDFROMCHAN (474): チャンネルに入ることが禁止されている場合に返されます。
string err_474(User user, string channel_name)
{
    string res;
    res = USER_IDENTIFIER(user.get_nickname(), user.get_username());
    res += " 474 ";
    res += user.get_nickname();
    res += " ";
    res += channel_name;
    res += " :Cannot join channel (+b)";
    res += "\r\n";
    return res;
}

// ERR_BADCHANNELKEY (475): チャンネルに入るためのキー（パスワード）が間違っている、または提供されていない場合に返されます。
string err_475(User user, string channel_name)
{
    string res;
    res = USER_IDENTIFIER(user.get_nickname(), user.get_username());
    res += " 475 ";
    res += user.get_nickname();
    res += " ";
    res += channel_name;
    res += " :Cannot join channel (+k)";
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

// ERR_CHANOPRIVSNEEDED (482): ユーザーがチャンネルのオペレータ権限を持っていない場合に返されます。
string err_482(User user, string channel_name)
{
    string res;
    res = USER_IDENTIFIER(user.get_nickname(), user.get_username());
    res += " 482 ";
    res += user.get_nickname();
    res += " ";
    res += channel_name;
    res += " :You're not channel operator";
    res += "\r\n";
    return res;
}

// 332, 353, 366, 324
// join
string response332(User user, string channel_name, string topic)
{
    string res;
    res = USER_IDENTIFIER(user.get_nickname(), user.get_username());
    res += " 332 ";
    res += user.get_nickname();
    res += " ";
    res += channel_name;
    res += " :";
    res += topic;
    res += "\r\n";
    return res;
}

string response353(User user, string channel_name, string members)
{
    string res;
    res = USER_IDENTIFIER(user.get_nickname(), user.get_username());
    res += " 353 ";
    res += user.get_nickname();
    res += " = ";
    res += channel_name;
    res += " :";
    res += members;
    res += "\r\n";
    return res;
}

string response366(User user, string channel_name)
{
    string res;
    res = USER_IDENTIFIER(user.get_nickname(), user.get_username());
    res += " 366 ";
    res += user.get_nickname();
    res += " ";
    res += channel_name;
    res += " :End of /NAMES list";
    res += "\r\n";
    return res;
}

string response324(User user, string channel_name, string mode)
{
    string res;
    res = USER_IDENTIFIER(user.get_nickname(), user.get_username());
    res += " 324 ";
    res += user.get_nickname();
    res += " ";
    res += channel_name;
    res += " +";
    res += mode;
    res += "\r\n";
    return res;
}

// ERR_INVALIDMODEPARAM (696) : チャンネルモードのパラメータが無効な場合に返されます。
string err_696(User user)
{
    string res;
    res = USER_IDENTIFIER(user.get_nickname(), user.get_username());
    res += " 696 ";
    res += user.get_nickname();
    res += " :Invalid mode parameter";
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

// RPL_INVITING (341) : ユーザーが指定したチャンネルに招待を送信した場合に返されます。
string response341(User user, string channel_name, string nickname)
{
    string res;
    res = USER_IDENTIFIER(user.get_nickname(), user.get_username());
    res += " 341 ";
    res += user.get_nickname();
    res += " :Inviting ";
    res += nickname;
    res += " to the channel ";
    res += channel_name;
    res += "\r\n";
    return res;
}


string err_800(User user, string channel_name)
{
    string res;
    res = USER_IDENTIFIER(user.get_nickname(), user.get_username());
    res += " 800 ";
    res += user.get_nickname();
    res += " ";
    res += channel_name;
    res += " ";
    res += "Already invited to the channel.";
    res += "\r\n";
    return res;
}

// NO_SUCH_FILE_OR_DIRECTORY : ファイルが存在しないか、またはディレクトリが存在しない場合に返されます。
string err_825(User user, string file_name)
{
    string res;
    res = USER_IDENTIFIER(user.get_nickname(), user.get_username());
    res += " 825 ";
    res += user.get_nickname();
    res += " ";
    res += file_name;
    res += " :No such file or directory";
    res += "\r\n";
    return res;
}

// ERR_FILE_ALREADY_EXISTS : ファイルが既に存在する場合に返されます。
string err_826(User user, string file_name)
{
    string res;
    res = USER_IDENTIFIER(user.get_nickname(), user.get_username());
    res += " 826 ";
    res += user.get_nickname();
    res += " ";
    res += file_name;
    res += " :File already exists";
    res += "\r\n";
    return res;
}

// ERR_FILE_PERMISSION_DENIED : ファイルにアクセスする権限がない場合に返されます。
string err_827(User user, string file_name)
{
    string res;
    res = USER_IDENTIFIER(user.get_nickname(), user.get_username());
    res += " 827 ";
    res += user.get_nickname();
    res += " ";
    res += file_name;
    res += " :Permission denied";
    res += "\r\n";
    return res;
}

// ERR_NOT_ACCEPTER : ファイルを受け取る権限がない場合に返されます。
string err_828(User user, string file_name)
{
    string res;
    res = USER_IDENTIFIER(user.get_nickname(), user.get_username());
    res += " 828 ";
    res += user.get_nickname();
    res += " ";
    res += file_name;
    res += " :You are not accepter of this file";
    res += "\r\n";
    return res;
}

// ERR_NOT_A_DIRECTORY : ディレクトリが存在しない場合に返されます。
string err_829(User user, string file_name)
{
    string res;
    res = USER_IDENTIFIER(user.get_nickname(), user.get_username());
    res += " 829 ";
    res += user.get_nickname();
    res += " ";
    res += file_name;
    res += " :Not a directory";
    res += "\r\n";
    return res;
}

// ERR_IS_A_DIRECTORY : ファイルがディレクトリの場合に返されます。
string err_830(User user, string file_name)
{
    string res;
    res = USER_IDENTIFIER(user.get_nickname(), user.get_username());
    res += " 830 ";
    res += user.get_nickname();
    res += " ";
    res += file_name;
    res += " :Is a directory";
    res += "\r\n";
    return res;
}
