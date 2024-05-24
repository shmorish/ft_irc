#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "Server.hpp"
#include "Parser.hpp"
#include "User.hpp"
#include "utils.hpp"

class Server;
class Parser;
class User;

class Command {
public:
	Command(Server &server, Parser &parser, User &user);
	~Command();
private:
	void	pass(User &user , Parser &parser);
	void	nick(Server &server, Parser &parser){cout << "nick" << endl; (void)server; (void)parser;};
	void	user(Server &server, Parser &parser){cout << "user" << endl; (void)server; (void)parser;};
	void	join(){};
	void	part(){};
	void	privmsg(){};
	void	quit(){};
	void	ping(){};
	void	pong(){};

	Server	&_server;
	Parser	&_parser;
	User	&_user;
};

#endif
