#ifndef WEBSERV_HPP
# define WEBSERV_HPP

# include <iostream>
# include <string>
# include <vector>
# include <map>
# include <exception>
# include <poll.h>
# include <arpa/inet.h>
# include <cerrno>
# include <iomanip>
# include <iostream>
# include <map>
# include <poll.h>
# include <set>
# include <sstream>
# include <string>
# include <sys/socket.h>
# include <unistd.h>
# include <vector>

using namespace std;

class Server
{
    public:
        Server(long port, const string &password);
        ~Server();
        void setup();
        void run();
        void handle_new_client_connection();
    private:
        const long              _port;
        const string            _password;
        int                     _server_sockfd;
        struct sockaddr_in      _server_addr;
        vector<struct pollfd>   _pollfd_vector;
};

#endif