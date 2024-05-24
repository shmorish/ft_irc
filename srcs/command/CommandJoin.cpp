#include "Command.hpp"

void Command::join()
{
    try {
        if (_user.get_is_nickname() == false) {
            throw runtime_error("You are not registered");
        }
        if (_parser.get_args().empty() == true) {
            throw runtime_error("channel is empty");
        }
        if (_parser.get_args().size() > 1) {
            throw runtime_error("Too many arguments");
        }
        if (_parser.get_args().at(0).size() > 200) {
            throw runtime_error("channel is too long");
        }
        if (_parser.get_args().at(0).at(0) != '#') {
            throw runtime_error("channel must start with #");
        }
        // チャンネル名が存在するかどうか
        // →存在しない場合は作成し、存在する場合は権限を確認する
    } catch (const exception &e) {
        send(_user.get_fd(), e.what(), strlen(e.what()), 0);
        // cerr << e.what() << endl;
    }

    cout << "Joining channel: " << _parser.get_args().at(0) << endl;
    ;
}