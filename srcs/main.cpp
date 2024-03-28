#include "Server.hpp"
#include <iostream>
#include <cerrno>

using namespace std;

long checkport(const char *port)
{
    if (!port || *port == '\0')
        throw std::invalid_argument("Invalid port number");
    char *endptr;
    long port_num = strtol(port, &endptr, 10);
    if (port_num < 0 || port_num > 0xffff || errno == ERANGE || *endptr != '\0')
        throw std::invalid_argument("Invalid port number");
    return port_num;
}

int main(int argc, char **argv)
{

    if (argc != 3) {
        cerr << "usage: " << argv[0] << " <port> <password>" << endl;
        return 1;
    }
    try {
        Server IrcServer(checkport(argv[1]), argv[2]);
    } catch (const std::exception &e) {
        cerr << e.what() << endl;
        return 1;
    }
    return 0;
}