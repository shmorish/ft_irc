#include "Command.hpp"

// ユーザーがすでに登録されているかどうかをチェック
static void check_user_registration_status(User user) {
    if (user.get_is_nickname() == true)
        throw runtime_error(err_462(user));
}

// argsの引数を処理
static void process_title_arguments(vector<string> args, User user) {
    if (args.empty() == true)
        throw runtime_error(err_461(user, "NICK"));
    if (args.size() > 1)
        throw runtime_error(err_461(user, "NICK"));
}

// ニックネームが長すぎるかどうかをチェック
static void check_nickname_length(const string nickname, User user) {
    if (nickname.size() > 256)
        throw runtime_error(err_696(user));
}

// // 使用できる特殊文字かどうかを判定
static bool is_special_Character(const char c) {
    const string special = "[]\\`_^{|}";
    return special.find(c) != string::npos;
}

// nicknameに使える文字を選別
static void check_nickname_characters(const string nickname, User user) {
    for (size_t i = 0; i < nickname.size(); i++)
        if (!(isalnum(nickname[i]) || is_special_Character(nickname[i]))) {
            // string error_message = "Invalid character in nickname: ";
            // error_message += nickname[i];
            // error_message += "\n";
            // throw runtime_error(error_message);
            throw runtime_error(err_432(user, nickname));
        }
}

static void replaceSpecialCharacters(string &nickname) {
    const string fromChars = "{}|^";
    const string toChars = "[]\\~";

    for (size_t i = 0; i < nickname.size(); i++) {
        char c = nickname[i];
        size_t index = fromChars.find(c);
        if (index != string::npos)
            nickname[i] = toChars[index];
    }
}

// 同じニックネームの人物を探す
static void check_nickname_uniqueness(Server server, string nickname) {
    for (set<User *>::iterator it = server.get_users().begin(); it != server.get_users().end(); it++) {
        string user_nickname = (*it)->get_nickname();
        if (user_nickname.compare(nickname) == 0)
            throw runtime_error(err_433(*(*it), nickname));
    }
}

// ニックネームと同じ名前のチャンネルを探す
static void check_nickname_against_channel_names(Server server, const string nickname, User user) {
    for (set<Channel *>::iterator it = server.get_channels().begin(); it != server.get_channels().end(); ++it) {
        string channel_name = (*it)->get_channel_name();
        if (channel_name.compare(nickname) == 0)
            throw runtime_error(err_433(user, nickname));
    }
}

// ニックネームを設定
static void set_user_nickname(User &_user, const string nickname) {
    // ユーザーにニックネームを設定
    _user.set_nickname(nickname);
    // フラグを更新
    _user.set_is_nickname(true);
}

void Command::nick() {
    try {
        // ユーザーがすでに登録されているかどうかをチェック
        check_user_registration_status(_user);
        // 引数を処理
        process_title_arguments(_parser.get_args(), _user);
        // ニックネームが長すぎるかどうかをチェック
        string nickname = _parser.get_args().at(0);
        if (nickname == "bot")
            throw runtime_error(err_433(_user, nickname));
        check_nickname_length(nickname, _user);
        // nicknameに使える文字を選別 (A-Z, a-z, 0-9, []\^_{|}` )
        check_nickname_characters(nickname, _user);
        // { -> [  | -> \  } -> ]  ~ -> _
        replaceSpecialCharacters(nickname);
        // 他のユーザーと重複していないか確認
        check_nickname_uniqueness(_server, nickname);
        // ニックネームと同じ名前のチャンネルを探す
        check_nickname_against_channel_names(_server, nickname, _user);
        // ニックネームを設定
        set_user_nickname(_user, nickname);
        string mess = ": You are now nicked as ";
        mess += nickname;
        mess += "\r\n";
        send(_user.get_fd(), mess.c_str(), mess.size(), 0);
    } catch (const exception &e) {
        send(_user.get_fd(), e.what(), strlen(e.what()), 0);
    }
}
