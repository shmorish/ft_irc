#include "Server.hpp"
#include "utils.hpp"

bool    server_running = true;

long checkPort(const char *port)
{
    if (!port || *port == '\0')
        throw invalid_argument("Invalid port number");
    char *endPtr;
    long port_num = strtol(port, &endPtr, 10);
    if (port_num < 0 || port_num > 0xffff || errno == ERANGE || *endPtr != '\0')
        throw invalid_argument("Invalid port number");
    return port_num;
}

std::string checkPassword(const char *password)
{
    if (!password || *password == '\0')
        throw invalid_argument("Invalid password");
    // if (strlen(password) < 8)
    //     throw invalid_argument("Password must be at least 8 characters long");
    if (strlen(password) > 64)
        throw invalid_argument("Password must be at most 64 characters long");
    for (size_t i = 0; password[i]; i++) {
        if (!isalnum(password[i]))
            throw invalid_argument("Invalid password character");
    }
    return password;
}

void    sigintHandler(int signum)
{
    (void)signum;
    endl(cout);
    cout << "Exiting..." << endl;
    server_running = false;
}

int main(int argc, char **argv)
{

    if (argc != 3) {
        cerr << "usage: " << argv[0] << " <port> <password>" << endl;
        return 1;
    }
    signal(SIGQUIT, SIG_IGN);
    signal(SIGTERM, SIG_IGN);
    signal(SIGINT, sigintHandler);
    try {
        Server IrcServer(checkPort(argv[1]), checkPassword(argv[2]));
        IrcServer.setup();
        IrcServer.run();
    } catch (const exception &e) {
        cerr << e.what() << endl;
        exit(1);
    }
    return 0;
}