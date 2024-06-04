#include "utils.hpp"

class File {
private:
    string _filename;
    string _send_path;
    string _accept_path;
    int _sender_fd;
    int _accepter_fd;
    File();

public:
    File(string send_path, string filename);
    ~File();
    void set_accept_path(string path);
    void set_sender_fd(int sender_fd);
    void set_accepter_fd(int accepter_fd);
    string get_filename();
    string get_accept_path();
    int get_sender_fd();
    int get_accepter_fd();
};
