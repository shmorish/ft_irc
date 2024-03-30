#include "Server.hpp"
#include "utils.hpp"

Server::Server(const long port, const string &password) : _port(port), _password(password)
{
    DEBUG_MSG("Port Number =", _port);
    DEBUG_MSG("Password    =", _password);
    (void)_port;
}

Server::~Server()
{
}

void Server::setup(void)
{
    int server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_sockfd == -1) {
		throw runtime_error("ERROR: socket: " + string(strerror(errno)));
	}
    DEBUG_MSG("Server socket created", server_sockfd);
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(_port);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(server_sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        throw runtime_error("ERROR: bind: " + string(strerror(errno)));
    }
    DEBUG_MSG("Server socket binded to port", _port);
}