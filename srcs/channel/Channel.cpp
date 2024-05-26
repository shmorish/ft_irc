#include "Channel.hpp"

Channel::Channel()
{
    _channel_name = "";
    _clients = set<USER_ID>();
    _operators = set<USER_ID>();
    _invited = set<USER_ID>();
    _banned = set<USER_ID>();
    _users_limit = OPEN_MAX;
    _mode = None;
    _topic = "";
    // _user_lists = set<User>();
}

Channel::Channel(const string &channel_name)
{
    _channel_name = channel_name;
    _clients = set<USER_ID>();
    _operators = set<USER_ID>();
    _invited = set<USER_ID>();
    _banned = set<USER_ID>();
    _users_limit = OPEN_MAX;
    _mode = None;
    _topic = "";
    // _user_lists = set<User>();
}

Channel::~Channel()
{
}

void Channel::set_channel_name(const string &channel_name)
{
    _channel_name = channel_name;
}

void Channel::set_users_limit(const unsigned int limit){
    _users_limit = limit;
}

void Channel::add_client(USER_ID client)
{
    _clients.insert(client);
}

void Channel::remove_client(USER_ID client)
{
    _clients.erase(client);
}

void Channel::add_operator(USER_ID client)
{
    _operators.insert(client);
}

void Channel::remove_operator(USER_ID client)
{
    _operators.erase(client);
}

void Channel::add_invited(USER_ID client)
{
    _invited.insert(client);
}

void Channel::remove_invited(USER_ID client)
{
    _invited.erase(client);
}

void Channel::add_banned(USER_ID client)
{
    _banned.insert(client);
}

void Channel::remove_banned(USER_ID client)
{
    _banned.erase(client);
}

string Channel::get_channel_name() const
{
    return _channel_name;
}

set<USER_ID> Channel::get_clients() const
{
    return _clients;
}

set<USER_ID> Channel::get_operators() const
{
    return _operators;
}

set<USER_ID> Channel::get_invited() const
{
    return _invited;
}

set<USER_ID> Channel::get_banned() const
{
    return _banned;
}

unsigned int Channel::get_users_limit() const
{
    return _users_limit;
}

bool Channel::channel_is_full() const
{
    return _clients.size() >= _users_limit;
}

bool Channel::is_client(USER_ID client) const
{
    return _clients.find(client) != _clients.end();
}

bool Channel::is_operator(USER_ID client) const
{
    return _operators.find(client) != _operators.end();
}

bool Channel::is_invited(USER_ID client) const
{
    return _invited.find(client) != _invited.end();
}

bool Channel::is_banned(USER_ID client) const
{
    return _banned.find(client) != _banned.end();
}

void Channel::set_topic(const string &topic)
{
    _topic = topic;
}
