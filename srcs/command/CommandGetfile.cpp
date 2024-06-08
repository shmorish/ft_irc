#include "Command.hpp"
#include <fcntl.h>

// GETFILE 受け取るfilename ファイルを置きたい場所の絶対path

// privmsg bot :getfile filename path
void Command::getfile() {
    try {
        // ユーザーが接続しているか確認
        if (_user.get_ready_to_connect() == false)
            throw runtime_error(bot_err_response451());
        if (_parser.get_args().size() != 4)
            throw runtime_error(bot_err_response461("GETFILE"));
        // ファイル名が存在するものか、受取手が正しいか確認
        string filename = _parser.get_args().at(2);
        if (filename.empty())
            throw runtime_error(bot_err_response461("GETFILE"));
        File *file = _server.findFileByFilename(filename);
        if (file == NULL)
            throw runtime_error(bot_err_response825(filename));
        if (_user.get_fd() != file->get_accepter_fd())
            throw runtime_error(bot_err_response828(filename));
        // 置きたい場所のpathが正しいかどうか、ディレクトリか確認
        string get_path = _parser.get_args().at(3);
        if (get_path.empty())
            throw runtime_error(bot_err_response461("GETFILE"));
        int fd = open(get_path.c_str(), O_DIRECTORY);
        if (fd == -1)
            throw runtime_error(bot_err_response829(get_path));
        close(fd);
        // ファイルを受け取る
        file->set_accept_path(get_path);
        // そもそもそこにファイルがあるか確認
        string send_path = get_path + "/" + filename;
        if (access(send_path.c_str(), F_OK) == 0)
            throw runtime_error(bot_err_response826(send_path));
        // ファイルを作成権限があるか確認
        fstream ofs(send_path, ios::out);
        if (ofs.fail())
            throw runtime_error(bot_err_response827(send_path));
        fstream ifs(file->get_send_path(), ios::in);
        if (ifs.fail())
            throw runtime_error(bot_err_response827(file->get_send_path()));
        if (ofs.is_open() && ifs.is_open()) {
            ofs << ifs.rdbuf();
            ifs.close();
            ofs.close();
        }
        // ~~がファイルを受け取りましたみたいなメッセージを送りたい
        string userID = USER_IDENTIFIER("bot", "bot");
        string message = userID + "bot PRIVMSG " + _parser.get_args().at(0) + " recieved file!\r\n";
        send(_user.get_fd(), message.c_str(), message.size(), 0);
        _server.get_files().erase(file);
        delete file;
    } catch (exception &e) {
        send(_user.get_fd(), e.what(), strlen(e.what()), 0);
    }
}
