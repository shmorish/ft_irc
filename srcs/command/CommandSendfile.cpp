#include "Command.hpp"
#include <fstream>

void Command::sendfile()
{
    // check if the user in the channel
    try {
        if (_parser.get_args().size() < 2)
            throw runtime_error(err_461(_user, "SENDFILE"));
        std::fstream ifs(_parser.get_args().at(1), std::ios::in);
        if (!ifs.fail())
            throw runtime_error(err_461(_user, "SENDFILE"));
    }
    catch (const exception &e) {
        send(_user.get_fd(), e.what(), strlen(e.what()), 0);
    }
}
