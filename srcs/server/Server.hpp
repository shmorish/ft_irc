#ifndef WEBSERV_HPP
# define WEBSERV_HPP

# include "utils.hpp"

using namespace std;

#ifndef BUFSIZ
# define BUFSIZ 1024
#endif

class Server
{
    public:
        Server(long port, const string &password);
        ~Server();
        void setup();
        void run();
        void handle_new_client_connection();
        // void handle_client_disconnection(int client_sockfd);
        string recieve_command(int client_sockfd);
    private:
        const long              _port;
        const string            _password;
        int                     _server_sockfd;
        struct sockaddr_in      _server_addr;
        vector<struct pollfd>   _pollfd_vector;
};

#endif