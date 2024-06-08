#include "Server.hpp"
#include "Parser.hpp"

extern bool server_running;

Server::Server(long port, const string &password) : _port(port), _password(password), _server_sockfd()
{
    DEBUG_MSG("Port Number =", _port);
    DEBUG_MSG("Password    =", _password);
    (void)_port;
}

Server::~Server()
{
}

void Server::setup(void)
{
    _server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (_server_sockfd == -1) {
		throw runtime_error("ERROR: socket: ");
	}
    DEBUG_MSG("Server socket created fd -> ", _server_sockfd);

    _server_addr.sin_family = AF_INET;
    _server_addr.sin_port = htons(_port);
    _server_addr.sin_addr.s_addr = INADDR_ANY;

    int enable_SO_REU = 1;
    if (setsockopt(_server_sockfd, SOL_SOCKET, SO_REUSEADDR, &enable_SO_REU, sizeof(int)) == -1)
    {
        close(_server_sockfd);
        throw runtime_error("ERROR: setsockopt: ");
    }
    if (bind(_server_sockfd, (const struct sockaddr *)&_server_addr, (socklen_t)sizeof(_server_addr)) == -1) {
        close(_server_sockfd);
        throw runtime_error("ERROR: bind: ");
    }
    DEBUG_MSG("Server socket binded to port -> ", _port);
    if (listen(_server_sockfd, SOMAXCONN) == -1) {
        close(_server_sockfd);
        throw runtime_error("ERROR: listen: ");
    }
    DEBUG_MSG("Server socket listening on port -> ", _port);

    struct pollfd server_pollfd;
    server_pollfd.fd = _server_sockfd;
    server_pollfd.events = POLLIN;
    server_pollfd.revents = 0;
    _pollfd_vector.push_back(server_pollfd);
}

static void send_welcome_message_001(int fd, string nickname, string username)
{
    string msg = USER_IDENTIFIER(nickname, username);
    msg += RPL_WELCOME(fd, nickname);
    // cout << "Sending welcome message to client [" << fd << "]" << endl;
    // cout << msg << endl;
    send(fd, msg.c_str(), msg.size(), 0);
}

static void send_host_info_002(int client_sockfd, const string &servername, string nickname, string username)
{
    string msg = USER_IDENTIFIER(nickname, username);
    msg += RPL_YOURHOST(servername, nickname);
    send(client_sockfd, msg.c_str(), msg.size(), 0);
}

static void send_server_created_003(int client_sockfd, string nickname, string username)
{
    string date = SERVER_DATE;
    string msg = USER_IDENTIFIER(nickname, username);
    msg += RPL_CREATED(date, nickname);
    send(client_sockfd, msg.c_str(), msg.size(), 0);
}

static void send_modes_004(int client_sockfd, const string &nick, string nickname, string username)
{
    string msg = USER_IDENTIFIER(nickname, username);
    msg += RPL_MYINFO(nick);
    send(client_sockfd, msg.c_str(), msg.size(), 0);
}

static void send_bot_message(int client_sockfd)
{
    string userID = USER_IDENTIFIER("bot", "bot");
    string msg = userID + "bot PRIVMSG bot Hello, welcome to the server!\r\n";
    send(client_sockfd, msg.c_str(), msg.size(), 0);
}

void Server::handle_new_client_connections(void)
{
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    int client_sockfd = accept(_server_sockfd, (struct sockaddr *)&client_addr, &client_addr_len);
    if (client_sockfd == -1) {
        close(_server_sockfd);
        throw runtime_error("ERROR: accept");
    }
    cout << "New client connected with fd [" << client_sockfd << "]" << endl;
    struct pollfd client_pollfd;
    client_pollfd.fd = client_sockfd;
    client_pollfd.events = POLLIN;
    client_pollfd.revents = 0;
    _pollfd_vector.push_back(client_pollfd);
    // client fd and client user make pair

    // add User with new client client_sockfd
    User *new_user = new User(client_sockfd);
    _users.insert(new_user);
}

static vector<string> split(const string &str, char delim)
{
    vector<string> result;
    stringstream ss(str);
    string item;
    while (getline(ss, item, delim))
    {
        result.push_back(item);
    }
    return result;
}

vector<string> Server::recieve_command(int client_sockfd, size_t i)
{
    char buffer[BUFSIZ + 1] = {0};
    ssize_t bytes_read = recv(client_sockfd, buffer, sizeof(buffer), 0);
    if (bytes_read == EOF) {
        close(client_sockfd);
        close(_server_sockfd);
        throw runtime_error("ERROR: recv");
    }
    if (bytes_read == 0) {
        string msg = "QUIT\n";
        Parser parser = Parser(msg, _pollfd_vector[i].fd, _password);
        User* user = findUserByFd(_pollfd_vector[i].fd);
        Command command(*this, parser, *user);
        string server_msg = "client -> fd [" + to_string(client_sockfd) + "] client disconnected";
        throw runtime_error(server_msg);
    }
    if (bytes_read > BUFSIZ)
        throw runtime_error("ERROR: message too long");
    buffer[bytes_read] = '\0';
    vector<string> commands = split(buffer, '\n');
    return commands;
}

int Server::make_polls()
{
    // const int timeout = -1; // wait infinitely
    const int timeout = 0; // wait indefinitely for an event
    int numReadyForIo = poll(&_pollfd_vector[0], (nfds_t)_pollfd_vector.size(), timeout);
    if (numReadyForIo == -1) {
        close(_server_sockfd);
        throw runtime_error("Server Stopped");
    }
    return numReadyForIo;
}

void    Server::recieve_and_execute_commands(size_t i)
{
    try
    {
        // string msg = recieve_command(_pollfd_vector[i].fd, i);
        vector<string> commands = recieve_command(_pollfd_vector[i].fd, i);
        for (size_t j = 0; j < commands.size(); j++) {
            string msg = commands[j];
            if (msg.size() == 0) continue ;
            while (msg[0] == ' ') msg.erase(0, 1);
            if (msg.size() == 0 || msg == "\n") continue ;
            Parser parser = Parser(msg, _pollfd_vector[i].fd, _password);
            User* user = findUserByFd(_pollfd_vector[i].fd);
            Command command(*this, parser, *user);
            print_log(_pollfd_vector[i].fd, msg);
            if (findUserByFd(_pollfd_vector[i].fd) != NULL) {
                if (user->get_has_sent_welcome_message() == false) {
                    if (user->get_ready_to_connect() == true) {
                        send_welcome_message_001(_pollfd_vector[i].fd, user->get_nickname(), user->get_username());
                        send_host_info_002(_pollfd_vector[i].fd, "XServer", user->get_nickname(), user->get_username());
                        send_server_created_003(_pollfd_vector[i].fd, user->get_nickname(), user->get_username());
                        send_modes_004(_pollfd_vector[i].fd, user->get_nickname(), user->get_nickname(), user->get_username());
                        send_bot_message(_pollfd_vector[i].fd);
                        user->set_has_sent_welcome_message(true);
                    }
                }
            }
            // Command command(*this, parser, *new User(_pollfd_vector[i].fd));
            // recieve commands from clients
            // handle poll events

            // recieve command from client [PRIVMSG]
            // ↓
            // long recived_fd = _pollfd_vector[i].fd;
            // for (unsigned long i = 0; i < _pollfd_vector.size(); i++) {
            //     if (_pollfd_vector[i].fd != recived_fd) {
            //         string client_msg = "Client [" + to_string(recived_fd) + "] says: " + msg;
            //         send(_pollfd_vector[i].fd, client_msg.c_str(), client_msg.size(), 0);
            //     }
            // }
        }
        // ↑
    }
    catch (const exception &e)
    {
        cerr << e.what() << endl;
        return ;
    }
}

void    Server::check_all_polls()
{
    for (size_t i = 0; i < _pollfd_vector.size(); i++) {
        if (_pollfd_vector[i].revents & POLLIN) {
            if (_pollfd_vector[i].fd == _server_sockfd)
                handle_new_client_connections();
            else
                recieve_and_execute_commands(i);
        }
    }
}

void Server::close_server()
{
    for (set<User *>::iterator it = _users.begin(); it != _users.end(); ++it) {
        delete *it;
    }
    for (set<Channel *>::iterator it = _channels.begin(); it != _channels.end(); ++it) {
        delete *it;
    }
    _users.clear();
    _channels.clear();
    close(_server_sockfd);
}

void Server::sendMsgToChannel(string channel_name, string msg)
{
    Channel* channel = findChannelByName(channel_name);
    if (channel == NULL) {
        return ;
    }
    set<int> clients = channel->get_clients();
    for (set<int>::iterator it = clients.begin(); it != clients.end(); ++it) {
        send(*it, msg.c_str(), msg.size(), 0);
    }
}

void Server::run()
{
    while (server_running)
    {
        make_polls();
        check_all_polls();
    }
    close_server();
    cout << "Server stopped" << endl;
}

string Server::get_password() const{
    return _password;
}

set<User *> &Server::get_users(){
    return _users;
}

set<Channel *> &Server::get_channels(){
    return _channels;
}

set<File *> &Server::get_files(){
    return _files;
}

void Server::set_own_addr(void *addr){
    own_addr = addr;
}

User* Server::findUserByFd(int fd) {
    for (set<User*>::iterator it = _users.begin(); it != _users.end(); ++it) {
        if ((*it)->get_fd() == fd) {
            return *it;
        }
    }
    return NULL;
}

User* Server::findUserByNick(string nick) {
    for (set<User*>::iterator it = _users.begin(); it != _users.end(); ++it) {
        if ((*it)->get_nickname() == nick) {
            return *it;
        }
    }
    return NULL;
}

Channel* Server::findChannelByName(string name) {
    for (set<Channel*>::iterator it = _channels.begin(); it != _channels.end(); ++it) {
        if ((*it)->get_channel_name() == name) {
            return *it;
        }
    }
    return NULL;
}

File* Server::findFileByFilename(string filename, string sender, string receiver) {
    for (set<File*>::iterator it = _files.begin(); it != _files.end(); ++it) {
        if ((*it)->get_filename() == filename && (*it)->get_send_nickname() == sender && (*it)->get_accept_nickname() == receiver)
            return *it;
    }
    return NULL;
}

void Server::removeUser(User *user) {
    _users.erase(user);
    delete user;
}

void Server::print_log(int fd, string msg) {
    cout << "----- Server Log -----" << endl;
    cout << "Current Command: " << endl;
    cout << "  [fd]: " << fd << " " << msg << endl;
    cout << "Users: " << endl;
    for (set<User*>::iterator it = _users.begin(); it != _users.end(); ++it) {
        cout << "  [fd]: " << (*it)->get_fd() << " " << (*it)->get_nickname() << endl;
    }
    cout << "Channels: " << endl;
    for (set<Channel*>::iterator it = _channels.begin(); it != _channels.end(); ++it) {
        Channel *channel = *it;
        cout << "  [name]: " << channel->get_channel_name() << endl;
        enum Channel::ChannelMode mode = channel->get_mode();
        cout << "    [Channel Mode]: ";
        if (mode == (0))
            cout << "NONE ";
        if (mode & (1 << 0))
            cout << "INVITE_ONLY ";
        if (mode & (1 << 1))
            cout << "MODERATED ";
        if (mode & (1 << 2))
            cout << "TOPIC_OP_ONLY ";
        if (mode & (1 << 3))
            cout << "NEED_PASSWORD ";
        cout << endl;
        set<int> clients = channel->get_clients();
        for (set<int>::iterator it2 = clients.begin(); it2 != clients.end(); ++it2) {
            string nickname = findUserByFd(*it2)->get_nickname();
            if (channel->is_operator(*it2))
                cout << "    [Operat] " << *it2 << ":" << nickname << endl;
            else
                cout << "    [Client] " << *it2 << ":" << nickname << endl;
        }
        set<int> invited = channel->get_invited();
        for (set<int>::iterator it2 = invited.begin(); it2 != invited.end(); ++it2) {
            string nickname = findUserByFd(*it2)->get_nickname();
            cout << "    [Invite] " << *it2 << ":" << nickname << endl;
        }
        set<int> banned = channel->get_banned();
        for (set<int>::iterator it2 = banned.begin(); it2 != banned.end(); ++it2) {
            string nickname = findUserByFd(*it2)->get_nickname();
            cout << "    [Banned] " << *it2 << ":" << nickname << endl;
        }
    }
    cout << "----------------------" << endl;
    cout << endl;
}
