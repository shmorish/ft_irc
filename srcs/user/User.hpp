#ifndef USER_HPP
# define USER_HPP

# include "utils.hpp"

class User
{
private:
    string _nickname;
    string _username;
    string _realname;
    string _hostname;
    string _servername;
    bool _is_password;
    bool _is_nickname;
    bool _is_username;
    int _fd;

public:
    User(int fd);
    ~User();
    
    void set_nickname(const string &nickname);
    void set_username(const string &username);
    void set_realname(const string &realname);
    void set_hostname(const string &hostname);
    void set_servername(const string &servername);
    void set_is_password(bool is_password);
    void set_is_nickname(bool is_nickname);
    void set_is_username(bool is_username);
    
    string get_nickname() const;
    string get_username() const;
    string get_realname() const;
    string get_hostname() const;
    string get_servername() const;
    bool get_is_password() const;
    bool get_is_nickname() const;
    bool get_is_username() const;
    int get_fd() const;
};

#endif