#ifndef USER_HPP
# define USER_HPP

# include "utils.hpp"

class User
{
private:
    string _nickname;
    string _username;
    string _realname;
    string _hostname;
    string _mode;

public:
    User();
    ~User();
};

#endif