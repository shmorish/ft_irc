#include "Command.hpp"
#include <fcntl.h>

// GETFILE 受け取るfilename ファイルを置きたい場所の絶対path

void Command::getfile() {
    try {
        if (_parser.get_args().size() != 2)
            throw runtime_error(err_461(_user, "GETFILE"));
        // ユーザーが接続しているか確認
        if (_user.get_ready_to_connect() == false)
            throw runtime_error(err_451(_user));
        // ファイル名が存在するものか、受取手が正しいか確認
        string filename = _parser.get_args().at(0);
        if (filename.empty())
            throw runtime_error(err_461(_user, "GETFILE")); /*change err num*/
        if (_server.findFileByFilename(filename) == NULL)
            throw runtime_error(err_461(_user, "GETFILE")); /*change err num*/
        if (_user.get_fd() != _server.findFileByFilename(filename)->get_accepter_fd())
            throw runtime_error(err_461(_user, "GETFILE")); /*change err num*/
        File *file = _server.findFileByFilename(filename);
        // 置きたい場所のpathが正しいかどうか、ディレクトリか確認
        string get_path = _parser.get_args().at(1);
        if (get_path.empty())
            throw runtime_error(err_461(_user, "GETFILE")); /*change err num*/
        int fd = open(get_path.c_str(), O_DIRECTORY, 0777);
        if (fd == -1)
            throw runtime_error("GETFILE: " + get_path + ": Failed to open directory");
        close(fd);
        // ファイルを受け取る
        file->set_accept_path(get_path);
        fstream ofs(get_path + "/" + filename, ios::out);
        if (ofs.fail())
            throw runtime_error("GETFILE: " + get_path + "/" + filename + ": Permission denied\r\n"); /*change err num*/
        fstream ifs(file->get_filename(), ios::in);
        if (ifs.fail())
            throw runtime_error("GETFILE: " + file->get_filename() + ": Permission denied\r\n"); /*change err num*/
        send(_user.get_fd(), "GETFILE\r\n", 9, 0);
        if (ofs.is_open() && ifs.is_open()) {
            ofs << ifs.rdbuf();
            ifs.close();
            ofs.close();
        }
        // ~~がファイルを受け取りましたみたいなメッセージを送りたい
        _server.get_files().erase(file);
        delete file;
    } catch (exception &e) {
        send(_user.get_fd(), e.what(), strlen(e.what()), 0);
    }
}