#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "Server.hpp"
#include "Channel.hpp"
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
	void	pass();
	void	nick();
	void	user();
	void	join();
	void	part(){};
	void	privmsg();
	void	quit();
	void	ping(){};
	void	pong(){};
	void	show_time();
	void	kick(){};
	void	mode();
	void	topic(){};
	void	invite();

	Server	&_server;
	Parser	&_parser;
	User	&_user;
};

#endif
