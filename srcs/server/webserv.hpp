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
        Server(const string &config_file);
        ~Server();
        void run();
    private:
        const string _config_file;
};

#endif