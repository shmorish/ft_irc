#include "File.hpp"

File::File(string send_path, string filename, string sender, string accepter) : _filename(filename), _send_path(send_path),
                                                                                _accept_path(""), _sender_fd(-1), _accepter_fd(-1) {
    set_send_nickname(sender);
    set_accept_nickname(accepter);
}

File::~File() {}

void File::set_accept_path(string path) { _accept_path = path; }

void File::set_sender_fd(int send_fd) { _sender_fd = send_fd; }

void File::set_accepter_fd(int accept_fd) { _accepter_fd = accept_fd; }

void File::set_send_nickname(string nickname) { _send_nickname = nickname; }

void File::set_accept_nickname(string nickname) { _accept_nickname = nickname; }

string File::get_filename() { return _filename; }

string File::get_accept_path() { return _accept_path; }

string File::get_send_path() { return _send_path; }

string File::get_send_nickname() { return _send_nickname; }

string File::get_accept_nickname() { return _accept_nickname; }

int File::get_sender_fd() { return _sender_fd; }

int File::get_accepter_fd() { return _accepter_fd; }
