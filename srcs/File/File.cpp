#include "File.hpp"

File::File(string send_path, string filename) : \
    _filename(filename), _send_path(send_path), \
    _accept_path(""), _sender_fd(-1), _accepter_fd(-1) {}

File::~File() {}

void File::set_accept_path(string path) { _accept_path = path; }

void File::set_sender_fd(int send_fd) { _sender_fd = send_fd; }

void File::set_accepter_fd(int accept_fd) { _accepter_fd = accept_fd; }

string File::get_filename() { return _filename; }

string File::get_accept_path() { return _accept_path; }

int File::get_sender_fd() { return _sender_fd; }

int File::get_accepter_fd() { return _accepter_fd; }

