#include "Server.hpp"
#include "parser.hpp"

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

    setsockopt(_server_sockfd, SOL_SOCKET, SO_REUSEADDR, NULL, 0);
    if (bind(_server_sockfd, (const struct sockaddr *)&_server_addr, (socklen_t)sizeof(_server_addr)) == -1) {
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

void Server::handle_new_client_connections(void)
{
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    int client_sockfd = accept(_server_sockfd, (struct sockaddr *)&client_addr, &client_addr_len);
    if (client_sockfd == -1) {
        close(_server_sockfd);
        throw runtime_error("ERROR: accept: " + string(strerror(errno)));
    }
    cout << "New client connected with fd [" << client_sockfd << "]" << endl;
    struct pollfd client_pollfd;
    client_pollfd.fd = client_sockfd;
    client_pollfd.events = POLLIN;
    client_pollfd.revents = 0;
    _pollfd_vector.push_back(client_pollfd);
    // client fd and client user make pair
}

string Server::recieve_command(int client_sockfd, size_t i)
{
    char buffer[BUFSIZ + 1] = {0};
    ssize_t bytes_read = recv(client_sockfd, buffer, sizeof(buffer), 0);
    if (bytes_read == EOF) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) {return ("");}
        close(client_sockfd);
        close(_server_sockfd);
        throw runtime_error("ERROR: recv: " + string(strerror(errno)));
    }
    if (bytes_read == 0) {
        close(client_sockfd);
        _pollfd_vector.erase(_pollfd_vector.begin() + i);
        string msg = "client -> fd [" + to_string(client_sockfd) + "] client disconnected";
        throw runtime_error(msg);
    }
    if (bytes_read > BUFSIZ)
        throw runtime_error("ERROR: message too long");
    return string(buffer);
}

int Server::make_polls()
{
    const int timeout = -1; // wait infinitely
    int numReadyForIo = poll((pollfd *)_pollfd_vector.data(), (nfds_t)_pollfd_vector.size(), timeout);
    if (numReadyForIo == -1) {
        close(_server_sockfd);
        throw runtime_error("ERROR: poll: " + string(strerror(errno)));
    }
    return numReadyForIo;
}

void    Server::recieve_and_execute_commands(size_t i)
{
    try
    {
        string msg = recieve_command(_pollfd_vector[i].fd, i);
        if (msg.size() == 0)
            return ;
        // cout << "Client " << _pollfd_vector[i].fd << " says: " << msg << endl;
        // Parser(msg, _pollfd_vector[i].fd, _password);
        // recieve commands from clients
        // handle poll events

        // recieve command from client
        // ↓
        long recived_fd = _pollfd_vector[i].fd;
        for (unsigned long i = 0; i < _pollfd_vector.size(); i++) {
            if (_pollfd_vector[i].fd != recived_fd) {
                string client_msg = "Client [" + to_string(recived_fd) + "] says: " + msg;
                send(_pollfd_vector[i].fd, client_msg.c_str(), client_msg.size(), 0);
            }
        }
        // ↑
    }
    catch (const exception &e)
    {
        cerr << e.what() << endl;
        return ;
    }
}

void    Server::check_all_polls()
{
    for (size_t i = 0; i < _pollfd_vector.size(); i++) {
        if (_pollfd_vector[i].revents & POLLIN) {
            if (_pollfd_vector[i].fd == _server_sockfd)
                handle_new_client_connections();
            else
                recieve_and_execute_commands(i);
        }
        // else if (_pollfd_vector[i].revents & POLLHUP) {
        //     close(_pollfd_vector[i].fd);
        //     _pollfd_vector.erase(_pollfd_vector.begin() + i);
        // }
    }
}

void Server::run()
{
    while (server_running)
    {
        make_polls();
        check_all_polls();
    }
    close(_server_sockfd);
    cout << "Server stopped" << endl;
}