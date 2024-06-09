#ifndef USER_HPP
#define USER_HPP

#include "utils.hpp"

#define CONNECTABLE_CHANNEL_MAX 20
#define MAX_CHANNEL_NAME_LEN 50

class User {
private:
    string _nickname;
    string _username;
    string _realname;
    string _hostname;
    string _servername;
    bool _is_password;
    bool _is_nickname;
    bool _is_username;
    bool _has_sent_welcome_message;
    int _fd;
    size_t _joining_channel_count;

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
    void set_has_sent_welcome_message(bool has_sent_welcome_message);
    void increment_joining_channel_count();
    void decrement_joining_channel_count();

    string get_nickname() const;
    string get_username() const;
    string get_realname() const;
    string get_hostname() const;
    string get_servername() const;
    bool get_is_password() const;
    bool get_is_nickname() const;
    bool get_is_username() const;
    bool get_has_sent_welcome_message() const;
    int get_fd() const;
    bool get_ready_to_connect() const;
    size_t get_joining_channel_count() const;
};

#endif
