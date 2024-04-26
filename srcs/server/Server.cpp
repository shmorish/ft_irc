#include "Server.hpp"
#include "utils.hpp"

extern bool server_running;

Server::Server(long port, const string &password) : _port(port), _password(password), _server_sockfd()
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
    _server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (_server_sockfd == -1) {
		throw runtime_error("ERROR: socket: " + string(strerror(errno)));
	}
    DEBUG_MSG("Server socket created fd -> ", _server_sockfd);
    _server_addr.sin_family = AF_INET;
    _server_addr.sin_port = htons(_port);
    _server_addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(_server_sockfd,
        (const struct sockaddr *)&_server_addr,
        (socklen_t)sizeof(_server_addr)) == -1) {
        close(_server_sockfd);
        throw runtime_error("ERROR: bind: " + string(strerror(errno)));
    }
    DEBUG_MSG("Server socket binded to port -> ", _port);
    if (listen(_server_sockfd, SOMAXCONN) == -1) {
        close(_server_sockfd);
        throw runtime_error("ERROR: listen: " + string(strerror(errno)));
    }
    DEBUG_MSG("Server socket listening on port -> ", _port);

    struct pollfd server_pollfd;
    server_pollfd.fd = _server_sockfd;
    server_pollfd.events = POLLIN;
    server_pollfd.revents = 0;
    _pollfd_vector.push_back(server_pollfd);
}

void Server::handle_new_client_connection(void)
{
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    int client_sockfd = accept(_server_sockfd,
                               (struct sockaddr *)&client_addr,
                               &client_addr_len);
    if (client_sockfd == -1) {
        close(_server_sockfd);
        throw runtime_error("ERROR: accept: " + string(strerror(errno)));
    }
    DEBUG_MSG("New client connected fd -> ", client_sockfd);
    struct pollfd client_pollfd;
    client_pollfd.fd = client_sockfd;
    client_pollfd.events = POLLIN;
    client_pollfd.revents = 0;
    _pollfd_vector.push_back(client_pollfd);
    // client fd and client user make pair
}

void Server::run()
{
    int poll_ret;
    while (server_running) {
        poll_ret = poll((pollfd *)_pollfd_vector.data(),
                        (nfds_t)_pollfd_vector.size(), -1);
        if (poll_ret == -1) {
            close(_server_sockfd);
            throw runtime_error("ERROR: poll: " + string(strerror(errno)));
        }
        for (size_t i = 0; i < _pollfd_vector.size(); i++) {
            if (_pollfd_vector[i].revents & POLLIN) {
                if (_pollfd_vector[i].fd == _server_sockfd) {
                    // handle new client connections
                    handle_new_client_connection();
                } else {
                    // handle poll events
                    // recieve commands from clients
                }
            }
        }
    }
    close(_server_sockfd);
}