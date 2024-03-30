#include "Server.hpp"
#include "utils.hpp"

bool    server_running = true;

long checkport(const char *port)
{
    if (!port || *port == '\0')
        throw invalid_argument("Invalid port number");
    char *endptr;
    long port_num = strtol(port, &endptr, 10);
    if (port_num < 0 || port_num > 0xffff || errno == ERANGE || *endptr != '\0')
        throw invalid_argument("Invalid port number");
    return port_num;
}

void    sigint_handler(int signum)
{
    (void)signum;
    cout << "Exiting..." << endl;
    server_running = false;
}

int main(int argc, char **argv)
{

    if (argc != 3) {
        cerr << "usage: " << argv[0] << " <port> <password>" << endl;
        return 1;
    }
    signal(SIGINT, sigint_handler);
    try {
        Server IrcServer(checkport(argv[1]), argv[2]);
        IrcServer.setup();
    } catch (const exception &e) {
        cerr << e.what() << endl;
        exit(1);
    }
    return 0;
}