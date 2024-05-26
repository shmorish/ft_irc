#include "Command.hpp"

static void is_valid_channel_name(const vector<string> &args){
    if (args.empty() == true) {
        throw runtime_error("channel is empty\n");
    }
    if (args.size() > 1) {
        throw runtime_error("Too many arguments\n");
    }
    if (args.at(0).size() > 200) {
        throw runtime_error("channel is too long\n");
    }
    if (args.at(0).at(0) != '#') {
        throw runtime_error("channel must start with #\n");
    }
    if (args.at(0).find_first_of(" ") != string::npos) {
        throw runtime_error("channel must not contain spaces\n");
    }
    if (args.at(0).find_first_of(",") != string::npos) {
        throw runtime_error("channel must not contain commas\n");
    }
    if (args.at(0).find_first_of(":") != string::npos) {
        throw runtime_error("channel must not contain colons\n");
    }
    if (args.at(0).find_first_of("!") != string::npos) {
        throw runtime_error("channel must not contain exclamation marks\n");
    }
    if (args.at(0).find_first_of("@") != string::npos) {
        throw runtime_error("channel must not contain at signs\n");
    }
    if (args.at(0).find_first_of("/") != string::npos) {
        throw runtime_error("channel must not contain slashes\n");
    }
    if (args.at(0).find_first_of("\\") != string::npos) {
        throw runtime_error("channel must not contain backslashes\n");
    }
    if (args.at(0).find_first_of("^") != string::npos) {
        throw runtime_error("channel must not contain carets\n");
    }
    if (args.at(0).find_first_of("[") != string::npos) {
        throw runtime_error("channel must not contain opening square brackets\n");
    }
    if (args.at(0).find_first_of("]") != string::npos) {
        throw runtime_error("channel must not contain closing square brackets\n");
    }
    if (args.at(0).find_first_of("{") != string::npos) {
        throw runtime_error("channel must not contain opening curly brackets\n");
    }
    if (args.at(0).find_first_of("}") != string::npos) {
        throw runtime_error("channel must not contain closing curly brackets\n");
    }
    if (args.at(0).find_first_of("|") != string::npos) {
        throw runtime_error("channel must not contain pipes\n");
    }
    if (args.at(0).find_first_of("$") != string::npos) {
        throw runtime_error("channel must not contain dollar signs\n");
    }
    if (args.at(0).find_first_of("%") != string::npos) {
        throw runtime_error("channel must not contain percent signs\n");
    }
    if (args.at(0).find_first_of("&") != string::npos) {
        throw runtime_error("channel must not contain ampersands\n");
    }
    if (args.at(0).find_first_of("*") != string::npos) {
           throw runtime_error("channel must not contain asterisks\n");
    }
    if (args.at(0).find_first_of("(") != string::npos) {
        throw runtime_error("channel must not contain opening parentheses\n");
    }
    if (args.at(0).find_first_of(")") != string::npos) {
        throw runtime_error("channel must not contain closing parentheses\n");
    }
    if (args.at(0).find_first_of("+") != string::npos) {
        throw runtime_error("channel must not contain plus signs\n");
    }
    if (args.at(0).find_first_of("#", 1) != string::npos) {
        throw runtime_error("channel must contain only one #\n");
    }
}

void Command::join()
{
    try {
        is_valid_channel_name(_parser.get_args());
        if(_user.get_ready_to_connect() == false) {
            throw runtime_error("You are not connected\n");
        }
    } catch (const exception &e) {
        send(_user.get_fd(), e.what(), strlen(e.what()), 0);
        // cerr << e.what() << endl;
        return ;
    }

    if (_server.findChannelByName(_parser.get_args().at(0)) == NULL) {
        _server.get_channels().insert(new Channel(_parser.get_args().at(0)));
        _server.findChannelByName(_parser.get_args().at(0))->add_client(_user.get_fd());
        send(_user.get_fd(), "You have joined the channel\n", 28, 0);
    }
    else {
        try {
            set<int> channels = _server.findChannelByName(_parser.get_args().at(0))->get_clients();
            for (set<int>::iterator it = channels.begin(); it != channels.end(); it++)
                if (*it == _user.get_fd())
                    throw runtime_error("You are already in this channel\n");
            _server.findChannelByName(_parser.get_args().at(0))->add_client(_user.get_fd());
            send(_user.get_fd(), "You have joined the channel\n", 28, 0);
        } catch (const exception &e) {
            send(_user.get_fd(), e.what(), strlen(e.what()), 0);
        }
    }
}
