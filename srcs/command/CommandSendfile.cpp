#include "Command.hpp"
#include <fcntl.h>

// SENDFILE <accepter_nickname> <ファイルの絶対or相対path>

static void is_correct_input(const vector<string> &args, User _user)
{
    if (args.size() != 4)
        throw runtime_error(bot_err_response461("SENDFILE"));
    if (_user.get_ready_to_connect() == false)
        throw runtime_error(bot_err_response451());
}

// privmsg bot :sendfile nick path
void Command::sendfile()
{
    try {
        // check input
        is_correct_input(_parser.get_args(), _user);
        string accepter_name = _parser.get_args().at(2);
        if (_server.findUserByNick(accepter_name) == NULL)
            throw runtime_error(bot_err_response401(accepter_name));

        // check input file
        string input_file_path = _parser.get_args().at(3);
        std::fstream ifs(input_file_path, std::ios::in);
        if (ifs.fail())
            throw runtime_error(bot_err_response825(input_file_path));
        int fd = open(input_file_path.c_str(), O_DIRECTORY);
        if (fd != -1) {
            close(fd);
            throw runtime_error(bot_err_response830(input_file_path));
        }

        // create file class
        size_t pos = input_file_path.find_last_of("/");
        string filename = input_file_path.substr(pos + 1);
        if (_server.findFileByFilename(filename) != NULL)
            throw runtime_error("SENDFILE: " + filename + "File already exists\r\n");
        _server.get_files().insert(new File(input_file_path, filename));
        File *file = _server.findFileByFilename(filename);
        if (file == NULL)
            throw runtime_error("SENDFILE: " + input_file_path + "Failed to create file\r\n");
        file->set_sender_fd(_user.get_fd());
        file->set_accepter_fd(_server.findUserByNick(accepter_name)->get_fd());

        /*~~が君にファイルを送信したよ！みたいなメッセージにしたい*/
        string message = bot_success_sendfile();
        send(_user.get_fd(), message.c_str(), message.size(), 0);
    }
    catch (const exception &e) {
        send(_user.get_fd(), e.what(), strlen(e.what()), 0);
    }
}
