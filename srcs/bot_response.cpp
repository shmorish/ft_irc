#include "response.hpp"
#include "User.hpp"

string bot_err_response(string err_message)
{
    User bot = User(-1);
    bot.set_nickname("bot");
    bot.set_username("bot");

    string res = USER_IDENTIFIER(bot.get_nickname(), bot.get_username());
    res += bot.get_nickname();
    res += " PRIVMSG ";
    res += bot.get_nickname();
    res += " ";
    res += err_message;
    res += " ";
    res += "\r\n";
    return res;
}

string bot_success_sendfile()
{
    return bot_err_response("send file!\r\n");
}

string bot_success_getfile()
{
    return bot_err_response("recieved file!\r\n");
}

string bot_err_response401(string nickname)
{
    return bot_err_response(nickname + " :No such nick/channel");
}

string bot_err_response451()
{
    return bot_err_response("You have not registered");
}

string bot_err_response461(string command)
{
    return bot_err_response(command + ":Not enough parameters");
}

// NO_SUCH_FILE_OR_DIRECTORY : ファイルが存在しないか、またはディレクトリが存在しない場合に返されます。
string bot_err_response825(string file_name)
{
    return bot_err_response(file_name + " :No such file or directory");
}

// ERR_FILE_ALREADY_EXISTS : ファイルが既に存在する場合に返されます。
string bot_err_response826(string file_name)
{
    return bot_err_response(file_name + " :File already exists");
}

// ERR_FILE_PERMISSION_DENIED : ファイルにアクセスする権限がない場合に返されます。
string bot_err_response827(string file_name)
{
    return bot_err_response(file_name + " :Permission denied");
}

// ERR_NOT_ACCEPTER : ファイルを受け取る権限がない場合に返されます。
string bot_err_response828(string file_name)
{
    return bot_err_response(file_name + " :You are not accepter of this file");
}

// ERR_NOT_A_DIRECTORY : ディレクトリが存在しない場合に返されます。
string bot_err_response829(string file_name)
{
    return bot_err_response(file_name + " :Not a directory");
}

// ERR_IS_A_DIRECTORY : ファイルがディレクトリの場合に返されます。
string bot_err_response830(string file_name)
{
    return bot_err_response(file_name + " :Is a directory");
}
