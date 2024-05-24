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

	bool operator<(const Channel& other) const {
    return this->_channel_name < other._channel_name;
  }

	void set_channel_name(const string &channel_name);
	void add_client(USER_ID client);
	void remove_client(USER_ID client);
	void add_operator(USER_ID client);
	void remove_operator(USER_ID client);
	void add_invited(USER_ID client);
	void remove_invited(USER_ID client);
	void add_banned(USER_ID client);
	void remove_banned(USER_ID client);

	string get_channel_name() const;
	set<USER_ID> get_clients() const;
	set<USER_ID> get_operators() const;
	set<USER_ID> get_invited() const;
	set<USER_ID> get_banned() const;
};

#endif