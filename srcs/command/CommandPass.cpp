#include "Command.hpp"

// すでに入力してあるかどうかをチェック
static void check_user_registration_status(User user) {
    if (user.get_is_password() == true)
        throw runtime_error(err_462(user));
}

// 引数を処理
static void process_title_arguments(User user, vector<string> args) {
    if (args.size() != 1)
        throw runtime_error(err_461(user, "PASS"));
}

// ユーザーを認証
static void authenticate_user(const Server _server, User &_user, const string password) {
    if (_server.get_password().compare(password) == 0) {
        send(_user.get_fd(), "Password is correct\n", 20, 0);
        _user.set_is_password(true);
    } else
        throw runtime_error(err_464(_user));
}

void Command::pass() {
    // for (size_t i = 0; i < _parser.get_args().size(); i++)
    //   cout << i << " : " << _parser.get_args().at(i) << endl;

    try {
        // すでに入力してあるかどうかをチェック
        check_user_registration_status(_user);
        // 引数を処理
        process_title_arguments(_user, _parser.get_args());
        // ユーザーを認証
        authenticate_user(_server, _user, _parser.get_args().at(0));
    } catch (const exception &e) {
        send(_user.get_fd(), e.what(), strlen(e.what()), 0);
    }
}
