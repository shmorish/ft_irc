#include "Command.hpp"

Command::Command(Server &server, Parser &parser , User &user_class) : _server(server), _parser(parser), _user(user_class) {
	CommandType cmd = _parser.get_command();
	if (cmd == PASS) pass();
	else if (cmd == NICK) nick();
	else if (cmd == USER) user();
	else if (cmd == JOIN) join();
	else if (cmd == PART) part();
	else if (cmd == PRIVMSG) privmsg();
	else if (cmd == QUIT) quit();
	else if (cmd == PING) ping();
	else if (cmd == PONG) pong();
	else if (cmd == TIME) show_time();
	else if (cmd == KICK) kick();
	else if (cmd == MODE) mode();
	else if (cmd == TOPIC) topic();
	else if (cmd == INVITE) invite();
	else if (cmd == CAP) cap();
	else throw runtime_error("Invalid command");
}

Command::~Command(){};
