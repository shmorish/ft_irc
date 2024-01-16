#include "webserv.hpp"

Server::Server(const string &config_file) : _config_file(config_file)
{
}

Server::~Server()
{
}

void Server::run()
{
    cout << "Server is running" << endl;
}
