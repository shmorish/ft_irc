#include "Command.hpp"

void Command::join()
{
    try {
        if (_user.get_is_nickname() == false) {
            throw runtime_error("You don't have a nickname\n");
        }
        if (_user.get_is_password() == false) {
            throw runtime_error("You don't have a password\n");
        }
        if (_user.get_is_username() == false) {
            throw runtime_error("You don't have a username\n");
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
        if (_parser.get_args().at(0).find_first_of(" ") != string::npos) {
            throw runtime_error("channel must not contain spaces\n");
        }
        if (_parser.get_args().at(0).find_first_of(",") != string::npos) {
            throw runtime_error("channel must not contain commas\n");
        }
        if (_parser.get_args().at(0).find_first_of(":") != string::npos) {
            throw runtime_error("channel must not contain colons\n");
        }
        if (_parser.get_args().at(0).find_first_of("!") != string::npos) {
            throw runtime_error("channel must not contain exclamation marks\n");
        }
        if (_parser.get_args().at(0).find_first_of("@") != string::npos) {
            throw runtime_error("channel must not contain at signs\n");
        }
        if (_parser.get_args().at(0).find_first_of("/") != string::npos) {
            throw runtime_error("channel must not contain slashes\n");
        }
        if (_parser.get_args().at(0).find_first_of("\\") != string::npos) {
            throw runtime_error("channel must not contain backslashes\n");
        }
        if (_parser.get_args().at(0).find_first_of("^") != string::npos) {
            throw runtime_error("channel must not contain carets\n");
        }
        if (_parser.get_args().at(0).find_first_of("[") != string::npos) {
            throw runtime_error("channel must not contain opening square brackets\n");
        }
        if (_parser.get_args().at(0).find_first_of("]") != string::npos) {
            throw runtime_error("channel must not contain closing square brackets\n");
        }
        if (_parser.get_args().at(0).find_first_of("{") != string::npos) {
            throw runtime_error("channel must not contain opening curly brackets\n");
        }
        if (_parser.get_args().at(0).find_first_of("}") != string::npos) {
            throw runtime_error("channel must not contain closing curly brackets\n");
        }
        if (_parser.get_args().at(0).find_first_of("|") != string::npos) {
            throw runtime_error("channel must not contain pipes\n");
        }
        if (_parser.get_args().at(0).find_first_of("$") != string::npos) {
            throw runtime_error("channel must not contain dollar signs\n");
        }
        if (_parser.get_args().at(0).find_first_of("%") != string::npos) {
            throw runtime_error("channel must not contain percent signs\n");
        }
        if (_parser.get_args().at(0).find_first_of("&") != string::npos) {
            throw runtime_error("channel must not contain ampersands\n");
        }
        if (_parser.get_args().at(0).find_first_of("*") != string::npos) {
            throw runtime_error("channel must not contain asterisks\n");
        }
        if (_parser.get_args().at(0).find_first_of("(") != string::npos) {
            throw runtime_error("channel must not contain opening parentheses\n");
        }
        if (_parser.get_args().at(0).find_first_of(")") != string::npos) {
            throw runtime_error("channel must not contain closing parentheses\n");
        }
        if (_parser.get_args().at(0).find_first_of("+") != string::npos) {
            throw runtime_error("channel must not contain plus signs\n");
        }
        if (_parser.get_args().at(0).find_first_of("#", 1) != string::npos) {
            throw runtime_error("channel must contain only one #\n");
        }
    } catch (const exception &e) {
        send(_user.get_fd(), e.what(), strlen(e.what()), 0);
        // cerr << e.what() << endl;
        return ;
    }

    if (_server.findChannelByName(_parser.get_args().at(0)) == NULL) {
        _server.get_channels().insert(new Channel(_parser.get_args().at(0)));
        _server.findChannelByName(_parser.get_args().at(0))->add_client(_user.get_fd());
    }
    else {
        try {
            if (_server.findChannelByName(_parser.get_args().at(0))->get_clients().find(_user.get_fd()) != _server.findChannelByName(_parser.get_args().at(0))->get_clients().end()) {
                throw runtime_error("You are already in this channel\n");
            }
            _server.findChannelByName(_parser.get_args().at(0))->add_client(_user.get_fd());
            send(_user.get_fd(), "You have joined the channel\n", 28, 0);
        } catch (const exception &e) {
            send(_user.get_fd(), e.what(), strlen(e.what()), 0);
        }
    }
    // チャンネル名が存在するかどうか
    // →存在しない場合は作成し、存在する場合は権限を確認する
}