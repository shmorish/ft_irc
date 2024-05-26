#include "Command.hpp"

void    Command::mode(){
    // MODE #channel_name <mode>
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
        // <mode>が有効なものかどうかを確認
        }
    }catch(const exception &e){
        send(_user.get_fd(), e.what(), strlen(e.what()), 0);
    }
}