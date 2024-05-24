#include "Command.hpp"

Command::Command(Server &server, Parser &parser , User &user) : _server(server), _parser(parser), _user(user) {
	switch(_parser.get_command()) {
		case PASS:
			this->pass(this->_user, this->_parser);
			break;
		case NICK:
			this->nick(this->_server, this->_parser);
			break;
		case USER:
			this->user(this->_server, this->_parser);
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


