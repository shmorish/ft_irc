#include "Command.hpp"

void	Command::pass(User &user, Parser &parser) {
	try{
		if (user.get_is_password() == true) {
			throw runtime_error("You are already registered");
		}
		if (parser.get_args().empty() == true) {
			throw runtime_error("Password is empty");
		}
		if (parser.get_args().size() > 1) {
			throw runtime_error("Too many arguments");
		}
		if (parser.get_args().at(0).size() > 4096) {
			throw runtime_error("Password is too long");
		}
		if (parser.get_args().at(0).compare(this->_server.get_password()) == 0) {
			user.set_is_password(true);
		} else {
			throw runtime_error("Password is incorrect");
		}
	} catch (const exception &e) {
		send(user.get_fd(), e.what(), strlen(e.what()), 0);
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
