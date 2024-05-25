#include "User.hpp"

User::User(int fd) : _is_password(false), _is_nickname(false), _is_username(false) , _fd(fd)
{
    _nickname = "";
    _username = "";
    _realname = "";
    _hostname = "";
}

User::~User(){}

void User::set_nickname(const string &nickname){
    _nickname = nickname;
}

void User::set_username(const string &username){
    _username = username;
}

void User::set_realname(const string &realname){
    _realname = realname;
}

void User::set_hostname(const string &hostname){
    _hostname = hostname;
}

void User::set_servername(const string &servername){
    _servername = servername;
}

void User::set_is_password(bool is_password){
    _is_password = is_password;
}

void User::set_is_nickname(bool is_nickname){
    _is_nickname = is_nickname;
}

void User::set_is_username(bool is_username){
    _is_username = is_username;
}

string User::get_nickname() const{
    return _nickname;
}

string User::get_username() const{
    return _username;
}

string User::get_realname() const{
    return _realname;
}

string User::get_hostname() const{
    return _hostname;
}

string User::get_servername() const{
    return _servername;
}

bool User::get_is_password() const{
    return _is_password;
}

bool User::get_is_nickname() const{
    return _is_nickname;
}

bool User::get_is_username() const{
    return _is_username;
}

int User::get_fd() const{
    return _fd;
}