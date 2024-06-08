#ifndef WEBSERV_HPP
# define WEBSERV_HPP

# include "utils.hpp"
# include "Channel.hpp"
# include "User.hpp"
# include "Command.hpp"
# include "File.hpp"

using namespace std;

#ifndef BUFSIZ
# define BUFSIZ 1024
#endif

#ifndef EOF
# define EOF (-1)
#endif

class Channel;
class User;
class File;

class Server
{
    public:
        Server(long port, const string &password);
        ~Server();
        void setup();
        void run();
        void handle_new_client_connections();
        vector<string> recieve_command(int client_sockfd, size_t i);
        int  make_polls();
        void check_all_polls();
        void recieve_and_execute_commands(size_t i);
        string get_password() const;
        set<User *> &get_users();
        set<Channel *> &get_channels();
        set<File *> &get_files();
        void set_own_addr(void *addr);
        User* findUserByFd(int fd);
        User* findUserByNick(string nickname);
        Channel* findChannelByName(string name);
        File* findFileByFilename(string filename, string sender, string receiver);
        void removeUser(User *user);
        void close_server();
        void sendMsgToChannel(string channel_name, string msg);
        void print_log(int fd, string msg);
    private:
        void                    *own_addr;
        const long              _port;
        const string            _password;
        int                     _server_sockfd;
        struct sockaddr_in      _server_addr;
        vector<struct pollfd>   _pollfd_vector;

        // fd, nickname
        map<int, string>        _clients; // unuse
        set<Channel *>            _channels;
        set<User *>               _users;
        set<File *>               _files;
};

#endif
