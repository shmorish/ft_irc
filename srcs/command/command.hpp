#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "utils.hpp"
#include "Server.hpp"
#include "Parser.hpp"

class Server;
class Parser;

class Command {
public:
	Command(Server &server, Parser &parser);
	~Command();
private:
	void	pass(Server &server, Parser &parser);
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
};

#endif
