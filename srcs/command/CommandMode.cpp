#include "Command.hpp"

//mode #channel +o nickname      ＝＞    nickname　にチャンネルオペレータ権限を与えます
//mode #channel -o nickname       ＝＞    nickname　からチャンネルオペレータ権限を奪います
//mode #channel +l 100               ＝＞    #channel　の参加数を100に制限します
//mode #channel -l                       ＝＞    #channel　の参加数制限を解除します

static void is_correct_input(const vector<string> &args){
    if (args.size() < 2)
        throw runtime_error("Too few arguments");
    if (args.size() > 3)
        throw runtime_error("Too many arguments");
    if (args.at(0).at(0) != '#')
        throw runtime_error("Channel name must start with #");
}

void    Command::mode(){
    // MODE #channel_name <mode>
    try{
        if(_parser.get_args().size() < 2)
            throw runtime_error("Too few arguments");
        if(_parser.get_args().size() > 2)
            throw runtime_error("Too many arguments");
        if(_parser.get_args().at(0).at(0) == '#' && (_parser.get_args().at(1).at(0) == '+' || _parser.get_args().at(1).at(0) == '-')){
            if(_server.findChannelByName(_parser.get_args().at(0)) == NULL)
                throw runtime_error("Channel not found");
        Channel *channel = _server.findChannelByName(_parser.get_args().at(0));
        if(channel->is_client(_user.get_fd()) == false)
            throw runtime_error("User not found in this channel");
        if(channel->is_operator(_user.get_fd()) == false)
            throw runtime_error("You are not operator");
        // <mode>が有効なものかどうかを確認
            if (_parser.get_args().at(1).at(0) == '+' && _parser.get_args().at(1).at(1) == 'l'){
                _server.findChannelByName(_parser.get_args().at(0))->set_users_limit(atoi(_parser.get_args().at(1).substr(2).c_str()));
                }
        }
    }catch(const exception &e){
        send(_user.get_fd(), e.what(), strlen(e.what()), 0);
    }
}

