#include "Command.hpp"

Command::Command(Server &server, Parser &parser , User &user_) : _server(server), _parser(parser), _user(user_) {
	switch(_parser.get_command()) {
		case PASS:
			pass();
			break;
		case NICK:
			nick();
			break;
		case USER:
			user();
			break;
		case JOIN:
			this->join();
			break;
		case PART:
			this->part();
			break;
		case PRIVMSG:
			this->privmsg();
			break;
		case QUIT:
			this->quit();
			break;
		case PING:
			this->ping();
			break;
		case PONG:
			this->pong();
			break;
		default:
			throw runtime_error("Invalid command");
	}
}

Command::~Command(){};


