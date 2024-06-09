#include "Command.hpp"

// すでに入力してあるかどうかをチェック
static void check_user_registration_status(User user) {
    if (user.get_is_username() == true)
        throw runtime_error(err_462(user));
}

// 引数の数をチェック
static void process_title_arguments(User user, vector<string> args) {
    if (args.size() != 4)
        throw runtime_error(err_461(user, "User"));
}

// 引数の長さをチェック
static void check_parser_args_length(User user, Parser &_parser) {
    for (size_t i = 0; i < _parser.get_args().size(); i++)
        if (_parser.get_args().at(i).size() > 256)
            throw runtime_error(err_696(user));
}

// ユーザーの詳細を設定
static void set_user_details(User &_user, vector<string> args) {
    _user.set_is_username(true);
    _user.set_username(args.at(0));
    _user.set_realname(args.at(1));
    _user.set_hostname(args.at(2));
    _user.set_servername(args.at(3));
    send(_user.get_fd(), "Username set\n", 13, 0);
}

void Command::user() {
    try {
        // すでに入力してあるかどうかをチェック
        check_user_registration_status(_user);
        // 引数の数をチェック
        process_title_arguments(_user, _parser.get_args());
        // 引数の長さをチェック
        check_parser_args_length(_user, _parser);
        // ユーザーの詳細を設定
        set_user_details(_user, _parser.get_args());
        //channel参加の権限を初期値に設定
    } catch (const exception &e) {
        send(_user.get_fd(), e.what(), strlen(e.what()), 0);
    }
}
