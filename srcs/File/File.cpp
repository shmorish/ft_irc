#include "File.hpp"

File::File() : _key(""), _path(""), _send_fd(-1), _accept_fd(-1) {}

File::~File() {}

void File::set_filename(string filename) { _key = filename; }

void File::set_path(string path) { _path = path; }

void File::set_send_fd(int send_fd) { _send_fd = send_fd; }

void File::set_accept_fd(int accept_fd) { _accept_fd = accept_fd; }

string File::get_filename() { return _key; }

string File::get_path() { return _path; }

int File::get_send_fd() { return _send_fd; }

int File::get_accept_fd() { return _accept_fd; }

