#include "utils.hpp"

class File {
private:
    string _key;
    string _path;
    int _send_fd;
    int _accept_fd;

public:
    File();
    ~File();
    void set_filename(string filename);
    void set_path(string path);
    void set_send_fd(int send_fd);
    void set_accept_fd(int accept_fd);
    string get_filename();
    string get_path();
    int get_send_fd();
    int get_accept_fd();
};
