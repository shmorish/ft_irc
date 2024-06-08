#include "Command.hpp"
#include <fcntl.h>

// SENDFILE <accepter_nickname> <ファイルの絶対or相対path>

static void is_correct_input(const vector<string> &args, User _user)
{
    if (args.size() != 4)
        throw runtime_error(err_461(_user, "SENDFILE"));
    if (_user.get_ready_to_connect() == false)
        throw runtime_error(err_451(_user));
}

// privmsg bot :sendfile nick path
void Command::sendfile()
{
    try {
        // check input
        is_correct_input(_parser.get_args(), _user);
        string accepter_name = _parser.get_args().at(2);
        if (_server.findUserByNick(accepter_name) == NULL)
            throw runtime_error(err_401(_user, accepter_name));

        // check input file
        std::fstream ifs(_parser.get_args().at(3), std::ios::in);
        if (ifs.fail())
            throw runtime_error("SENDFILE: " + _parser.get_args().at(3) + "Failed to open file\r\n");
        int fd = open(_parser.get_args().at(3).c_str(), O_DIRECTORY, 0777);
        if (fd != -1)
            throw runtime_error("SENDFILE: " + _parser.get_args().at(3) + ": Failed to open file\r\n");
        close(fd);

        // create file class
        size_t pos = _parser.get_args().at(3).find_last_of("/");
        string filename = _parser.get_args().at(3).substr(pos + 1);
        if (_server.findFileByFilename(filename) != NULL)
            throw runtime_error("SENDFILE: " + _parser.get_args().at(3) + "File already exists\r\n");
        _server.get_files().insert(new File(_parser.get_args().at(3), filename));
        File *file = _server.findFileByFilename(filename);
        if (file == NULL)
            throw runtime_error("SENDFILE: " + _parser.get_args().at(3) + "Failed to create file\r\n");
        file->set_sender_fd(_user.get_fd());
        file->set_accepter_fd(_server.findUserByNick(accepter_name)->get_fd());

        /*~~が君にファイルを送信したよ！みたいなメッセージにしたい*/
        // send(_server.findUserByNick(accepter_name)->get_fd(), "SENDFILE\r\n", 10, 0);
        string userID = USER_IDENTIFIER("bot", "bot");
        string message = userID + "bot PRIVMSG " + _parser.get_args().at(0) + " send file!\r\n";
        send(_user.get_fd(), message.c_str(), message.size(), 0);
    }
    catch (const exception &e) {
        send(_user.get_fd(), e.what(), strlen(e.what()), 0);
    }
}
