#include "Command.hpp"

void Command::join()
{
    try {
        if (_user.get_is_nickname() == false) {
            throw runtime_error("You are not registered\n");
        }
        if (_parser.get_args().empty() == true) {
            throw runtime_error("channel is empty\n");
        }
        if (_parser.get_args().size() > 1) {
            throw runtime_error("Too many arguments\n");
        }
        if (_parser.get_args().at(0).size() > 200) {
            throw runtime_error("channel is too long\n");
        }
        if (_parser.get_args().at(0).at(0) != '#') {
            throw runtime_error("channel must start with #\n");
        }
    } catch (const exception &e) {
        send(_user.get_fd(), e.what(), strlen(e.what()), 0);
        // cerr << e.what() << endl;
    }
    // チャンネル名が存在するかどうか
    // →存在しない場合は作成し、存在する場合は権限を確認する

    cout << "Joining channel: " << _parser.get_args().at(0) << endl;
    ;
}