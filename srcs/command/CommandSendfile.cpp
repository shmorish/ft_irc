#include "Command.hpp"

// SENDFILE <accepter_nickname> <ファイルの絶対or相対path>

static void is_correct_input(const vector<string> &args, User _user)
{
    if (args.size() != 2)
        throw runtime_error(err_461(_user, "SENDFILE"));
    if (_user.get_ready_to_connect() == false)
        throw runtime_error(err_451(_user));
}

void Command::sendfile()
{
    try {
        // check input
        is_correct_input(_parser.get_args(), _user);
        string accepter_name = _parser.get_args().at(0);
        if (_server.findUserByNick(accepter_name) == NULL)
            throw runtime_error(err_401(_user, accepter_name));
        
        // check input file
        std::fstream ifs(_parser.get_args().at(1), std::ios::in);
        if (ifs.fail())
            throw runtime_error(err_461(_user, "SENDFILE"));
        
        // create file
        size_t pos = _parser.get_args().at(1).find_last_of("/");
        string filename = _parser.get_args().at(1).substr(pos + 1);
        _server.get_files().insert(new File(_parser.get_args().at(1), filename));
        File *file = _server.findFileByFilename(filename);
        if (file == NULL)
            throw runtime_error(err_461(_user, "SENDFILE"));
        file->set_sender_fd(_user.get_fd());
        file->set_accepter_fd(_server.findUserByNick(accepter_name)->get_fd());

        // 同一の名前のファイルが存在する場合、削除
        for (set<File*>::iterator it = _server.get_files().begin(); it != _server.get_files().end(); it++){
            string tmp_filename = (*it)->get_filename();
            if (tmp_filename.compare(filename) == 0){
                _server.get_files().erase(it);
                delete *it;
                throw runtime_error("Invalid Filename.\r\n");
            }
        }
        send(_server.findUserByNick(accepter_name)->get_fd(), "SENDFILE", 7, 0);
    }
    catch (const exception &e) {
        send(_user.get_fd(), e.what(), strlen(e.what()), 0);
    }
}