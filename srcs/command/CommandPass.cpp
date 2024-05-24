#include "Command.hpp"

void	Command::pass(Server &server, Parser &parser)
{
	(void)server;
	string input;
	//input=get_message()をパーサー
	if(input != parser.get_password())
		throw runtime_error("Invalid password");
	else
		cout << "Password is correct" << endl;
}
