#include "command.hpp"

void	Command::pass(Server &server, Parser &parser)
{
	cout << "PASS" << endl;
	if(/*入力された文字列が設定パスワードと違ったら*/)
		throw runtime_error("Invalid password");
	else
		cout << "Password is correct" << endl;
}
