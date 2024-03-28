#include "Server.hpp"

#define BLUE "\033[0;34m"
#define RESET "\033[0m"
#define DEBUG_MSG(x, ...) cout << BLUE << "[DEBUG]: " << x << " " << __VA_ARGS__ << RESET << endl

Server::Server(const long port, const string &password) : _port(port), _password(password)
{
    #ifdef DEBUG
        DEBUG_MSG("Port Number =", _port);
        DEBUG_MSG("Password    =", _password);
    #endif
    (void)_port;
}

Server::~Server()
{
}
