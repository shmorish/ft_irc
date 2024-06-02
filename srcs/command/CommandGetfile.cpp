#include "Command.hpp"
#include <fcntl.h>

void Command::getfile() {
    // try {
    //     if (_user.get_ready_to_connect() == false)
    //         throw runtime_error(err_451(_user));
    //     string filename = _parser.get_args().at(0);
    //     if (filename.empty())
    //         throw runtime_error(err_461(_user, "GETFILE"));
    //     string get_path = _parser.get_args().at(1);
    //     if (get_path.empty())
    //         throw runtime_error(err_461(_user, "GETFILE"));
    //     int fd = open(get_path.c_str(), O_DIRECTORY);
    //     if (fd == -1)
    //         throw runtime_error("GETFILE: " + get_path + ": Not a directory");
    //     close(fd);
    //     if (get_path.back() == '/')
    //         get_path.pop_back();
    //     string path = get_path + "/" + filename;
    // } catch (exception &e) {
    //     send(_user.get_fd(), e.what(), strlen(e.what()), 0);
    // }
}