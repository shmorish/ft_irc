#include "Command.hpp"

void	Command::pass() {
	try{
		if (_user.get_is_password() == true) {
			throw runtime_error("You are already registered\n");
		}
		if (_parser.get_args().empty() == true) {
			throw runtime_error("Password is empty\n");
		}
		if (_parser.get_args().size() > 1) {
			throw runtime_error("Too many arguments\n");
		}
		if (_parser.get_args().at(0).size() > 256) {
			throw runtime_error("Password is too long\n");
		}
		if (_parser.get_args().at(0).compare(_server.get_password()) == 0) {
			_user.set_is_password(true);
		} else {
			throw runtime_error("Password is incorrect\n");
		}
	} catch (const exception &e) {
		send(_user.get_fd(), e.what(), strlen(e.what()), 0);
		// cerr << e.what() << endl;
	}
}


// void	Command::pass(Server &server, Parser &parser)
// {
// 	(void)server;
// 	string input;
// 	//input=get_message()をパーサー
// 	if(input != parser.get_password())
// 		throw runtime_error("Invalid password");
// 	else
// 		cout << "Password is correct" << endl;
// }
