#include "Command.hpp"

void Command::user()
{
    try {
        if (_parser.get_args().size() < 4) {
            throw runtime_error("Too few arguments\n");
        }
        if (_parser.get_args().size() > 4) {
            throw runtime_error("Too many arguments\n");
        }
        if (_user.get_is_username() == true) {
            throw runtime_error("You are already registered\n");
        }
        if (_parser.get_args().at(0).size() > 256) {
            throw runtime_error("Username is too long\n");
        }
        if (_parser.get_args().at(1).size() > 256) {
            throw runtime_error("Realname is too long\n");
        }
        if (_parser.get_args().at(2).size() > 256) {
            throw runtime_error("Hostname is too long\n");
        }
        if (_parser.get_args().at(3).size() > 256) {
            throw runtime_error("Servername is too long\n");
        }
        _user.set_is_username(true);
        _user.set_username(_parser.get_args().at(0));
        _user.set_realname(_parser.get_args().at(1));
        _user.set_hostname(_parser.get_args().at(2));
        _user.set_servername(_parser.get_args().at(3));
        send(_user.get_fd(), "Username set\n", 13, 0);
        //channel参加の権限を初期値に設定
    } catch (const exception &e) {
        send(_user.get_fd(), e.what(), strlen(e.what()), 0);
        // cerr << e.what() << endl;
    }
}