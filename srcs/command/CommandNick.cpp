#include "Command.hpp"

// 同じニックネームの人物を探す
static bool has_duplicate_nickname(Server server, string nickname) {
	for (std::set<User*>::iterator it = server.get_users().begin(); it != server.get_users().end(); it++)
		if ((*it)->get_nickname().compare(nickname) == 0)
			return true;
	return false;
}

// ニックネームと同じ名前のチャンネルを探す
// static bool has_channel_with_name(Server server, const string& channel_name) {
// 	for (std::set<Channel>::iterator it = server.get_channels().begin(); it != server.get_channels().end(); ++it) {
// 			if (it->get_channel_name().compare(channel_name) == 0) {
// 					return true;
// 			}
// 	}
// 	return false;
// }

void  Command::nick()
{
	try {
		if (_user.get_is_nickname() == true) {
			throw runtime_error("You are already registered\n");
		}
		if (_parser.get_args().empty() == true) {
			throw runtime_error("nickname is empty\n");
		}
		if (_parser.get_args().size() > 1) {
			throw runtime_error("Too many arguments\n");
		}
		if (_parser.get_args().at(0).size() > 256) {
			throw runtime_error("nickname is too long\n");
		}
		// nicknameに使える文字を選別
		// 他のユーザーと重複していないか確認
		if (has_duplicate_nickname(_server, _parser.get_args().at(0)) == true) {
			throw runtime_error("nickname is already used\n");
		}
		// チャンネル名と重複していないか確認
		// if (has_channel_with_name(_server, _parser.get_args().at(0)) == true) {
		// 	throw runtime_error("nickname is already used");
		// }
		// ニックネームを登録

		// if (_parser.get_args().at(0).compare(_server.get_password()) == 0) {
		// 		_user.set_is_password(true);
		// } else {
		// 		throw runtime_error("Password is incorrect");
		// }
    _user.set_nickname(_parser.get_args().at(0));
	} catch (const exception &e) {
		send(_user.get_fd(), e.what(), strlen(e.what()), 0);
		// cerr << e.what() << endl;
	}
}
