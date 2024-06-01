#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "utils.hpp"
# include "User.hpp"

# define USER_ID int

class User;

class Channel
{
public:
  enum ChannelMode {
    None = 0,
    InviteOnly = 1 << 0,      // i
    Moderated = 1 << 1,       // m
    TopicOpOnly = 1 << 2,    // t
	NeedPassword = 1 << 3,    // k
  };
  // i t k o l

private:
	string						_channel_name;
	set<pair<USER_ID, string> >	_clients_nicks;
	set<USER_ID>				_clients;
	set<USER_ID>				_operators;
	set<USER_ID>				_can_talk_in_mod_channel;
	set<USER_ID>				_invited;
	set<USER_ID>				_banned;
	// set<User>				_user_lists;

	enum ChannelMode	_mode;
	unsigned int		_users_limit;
	string				_topic;
	string				_password;

public:

    Channel();
	Channel(const string &channel_name);
    ~Channel();

	bool operator<(const Channel& other) const {
    return this->_channel_name < other._channel_name;
  }

	void set_channel_name(const string &channel_name);
	void set_users_limit(const unsigned int limit);
	void set_topic(const string &topic);
	void set_mode(enum ChannelMode mode);
	void set_password(const string &password);

	void add_client_nickname(USER_ID client, string nickname);
	void add_client(USER_ID client);
	void remove_client(USER_ID client);
	void add_operator(USER_ID client);
	void remove_operator(USER_ID client);
	void add_can_talk_in_mod_channel(USER_ID client);
	void remove_can_talk_in_mod_channel(USER_ID client);
	void add_invited(USER_ID client);
	void remove_invited(USER_ID client);
	void add_banned(USER_ID client);
	void remove_banned(USER_ID client);

	string get_channel_name() const;
	set<pair<USER_ID, string> > get_clients_nicks() const;
	set<USER_ID> get_clients() const;
	set<USER_ID> get_operators() const;
	set<USER_ID> get_can_talk_in_mod_channel() const;
	set<USER_ID> get_invited() const;
	set<USER_ID> get_banned() const;
	unsigned int get_users_limit() const;
	string get_topic() const;
	enum ChannelMode get_mode() const;
	string get_password() const;

	bool channel_is_full() const;

	bool is_client(USER_ID client) const;
	bool is_operator(USER_ID client) const;
	bool is_invited(USER_ID client) const;
	bool is_banned(USER_ID client) const;

	string get_nickname_list() const;
};

#endif
