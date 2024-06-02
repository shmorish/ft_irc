#include "Command.hpp"
#include <fstream>

void Command::sendfile()
{
    // check if the user in the channel
    // try {
    //     string reciver_name = _parser.get_args().at(0);
    //     if (_user.get_ready_to_connect() == false)
    //         throw runtime_error(err_451(_user));
    //     if (_parser.get_args().size() < 2)
    //         throw runtime_error(err_461(_user, "SENDFILE"));
    //     if (_server.findUserByNick(reciver_name) == NULL)
    //         throw runtime_error(err_401(_user, reciver_name));
    //     std::fstream ifs(_parser.get_args().at(1), std::ios::in);
    //     if (!ifs.fail())
    //         throw runtime_error(err_461(_user, "SENDFILE"));
    // }
    // catch (const exception &e) {
    //     send(_user.get_fd(), e.what(), strlen(e.what()), 0);
    // }
}