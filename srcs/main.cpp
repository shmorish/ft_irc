#include "webserv.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        cout << "Usage: ./webserv [config_file]" << endl;
        return (1);
    }
    try
    {
        Server server(argv[1]);
        server.run();
    }
    catch (const std::exception &e)
    {
        cerr << e.what() << endl;
    }
    return (0);
}