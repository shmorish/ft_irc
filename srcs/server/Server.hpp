#ifndef WEBSERV_HPP
# define WEBSERV_HPP

# include <iostream>
# include <string>
# include <vector>
# include <map>
# include <exception>

using namespace std;

class Server
{
    public:
        Server(const long port, const string &password);
        ~Server();
        void setup();
        void run();
    private:
        const long  _port;
        const string _password;
        int _server_sockfd;
};

#endif