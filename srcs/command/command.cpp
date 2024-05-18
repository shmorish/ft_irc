#include "command.hpp"

Command::Command(Server &server, Parser &parser):_server(server), _parser(parser){
	switch(_parser.get_command()) {
		case PASS:
			this->pass();
			break;
		case NICK:
			this->nick();
				break;
		case USER:
			this->user();
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


