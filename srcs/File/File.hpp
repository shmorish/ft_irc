#ifndef FILE_HPP
#define FILE_HPP

#include "utils.hpp"

class File {
private:
    string _filename;
    string _send_path;
    string _accept_path;
    string _send_nickname;
    string _accept_nickname;
    int _sender_fd;
    int _accepter_fd;
    File();

public:
    File(string send_path, string filename, string sender, string accepter);
    ~File();
    void set_accept_path(string path);
    void set_sender_fd(int sender_fd);
    void set_accepter_fd(int accepter_fd);
    void set_send_nickname(string nickname);
    void set_accept_nickname(string nickname);
    string get_filename();
    string get_accept_path();
    string get_send_path();
    string get_send_nickname();
    string get_accept_nickname();
    int get_sender_fd();
    int get_accepter_fd();
};

#endif
