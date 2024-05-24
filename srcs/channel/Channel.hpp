#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "utils.hpp"
# include "User.hpp"

# define USER_ID size_t

class User;

class Channel
{
private:
	string				_channel_name;
	set<USER_ID>		_clients;
	set<USER_ID>		_operators;
	set<USER_ID>		_invited;
	set<USER_ID>		_banned;
	// set<User>			_user_lists;
public:
    Channel();
    ~Channel();
};


#endif