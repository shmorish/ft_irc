#include "Server.hpp"
#include "utils.hpp"

extern bool server_running;

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
    _server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (_server_sockfd == -1) {
		throw runtime_error("ERROR: socket: " + string(strerror(errno)));
	}
    DEBUG_MSG("Server socket created fd -> ", _server_sockfd);
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(_port);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(_server_sockfd, (const struct sockaddr *)&server_addr, (socklen_t)sizeof(server_addr)) == -1) {
        close(_server_sockfd);
        throw runtime_error("ERROR: bind: " + string(strerror(errno)));
    }
    DEBUG_MSG("Server socket binded to port -> ", _port);
    if (listen(_server_sockfd, SOMAXCONN) == -1) {
        close(_server_sockfd);
        throw runtime_error("ERROR: listen: " + string(strerror(errno)));
    }
    DEBUG_MSG("Server socket listening on port -> ", _port);

    // poll initialization
}

void Server::run(void)
{
    while (server_running) {
        // poll
        ;
        try {
            ;
            // handle poll events
            // recieve commands from clients
        } catch (const exception &e) {
            cerr << e.what() << endl;
            continue;
        }
    }
    close(_server_sockfd);
}