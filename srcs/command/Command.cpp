#include "Command.hpp"

Command::Command(Server &server, Parser &parser , User &user_class) : _server(server), _parser(parser), _user(user_class) {
	cout << " -> " << _parser.get_command() << endl;
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
			join();
			break;
		case PART:
			part();
			break;
		case PRIVMSG:
			privmsg();
			break;
		case QUIT:
			quit();
			break;
		case PING:
			ping();
			break;
		case PONG:
			pong();
			break;
		default:
			throw runtime_error("Invalid command");
	}
}

Command::~Command(){};


