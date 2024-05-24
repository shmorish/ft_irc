#include "Command.hpp"

void  Command::nick()
{
	if (_user.get_is_nickname() == true) {
		throw runtime_error("You are already registered");
	}
	if (_parser.get_args().empty() == true) {
		throw runtime_error("nickname is empty");
	}
	if (_parser.get_args().size() > 1) {
		throw runtime_error("Too many arguments");
	}
	if (_parser.get_args().at(0).size() > 256) {
		throw runtime_error("nickname is too long");
	}
}