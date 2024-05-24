#include "Channel.hpp"

Channel::Channel()
{
    _channel_name = "";
    _clients = set<USER_ID>();
    _operators = set<USER_ID>();
    _invited = set<USER_ID>();
    _banned = set<USER_ID>();
    // _user_lists = set<User>();
}

Channel::~Channel()
{
}
