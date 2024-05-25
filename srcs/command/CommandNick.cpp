#include "Command.hpp"

// ユーザーがすでに登録されているかどうかをチェック
static void check_user_registration_status(User user) {
  if (user.get_is_nickname() == true)
    throw runtime_error("You are already registered\n");
}

// argsの引数を処理
static void process_title_arguments(vector<string> args) {
  if (args.empty() == true)
    throw runtime_error("nickname is empty\n");
  if (args.size() > 1)
    throw runtime_error("Too many arguments\n");
}

// ニックネームが長すぎるかどうかをチェック
static void check_nickname_length(const string nickname) {
  if (nickname.size() > 256)
    throw runtime_error("nickname is too long\n");
}

// // 使用できる特殊文字かどうかを判定
static bool is_special_Character(const char c) {
  const string special = "[]\\`_^{|}";
  return special.find(c) != std::string::npos;
}

// nicknameに使える文字を選別
static void check_nickname_characters(const string nickname) {
  for (size_t i = 0; i < nickname.size(); i++)
    if (!(isalnum(nickname[i]) || is_special_Character(nickname[i]))) {
      string error_message = "Invalid character in nickname: ";
      error_message += nickname[i];
      error_message += "\n";
      throw runtime_error(error_message);
    }
}

static void replaceSpecialCharacters(string& nickname) {
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
  for (std::set<User*>::iterator it = server.get_users().begin(); it != server.get_users().end(); it++)
    if ((*it)->get_nickname().compare(nickname) == 0)
      throw runtime_error("nickname is already used\n");
}

// ニックネームと同じ名前のチャンネルを探す
static void check_nickname_against_channel_names(Server server, const string nickname) {
  for (std::set<Channel *>::iterator it = server.get_channels().begin(); it != server.get_channels().end(); ++it)
      if ((*it)->get_channel_name().compare(nickname) == 0)
        throw runtime_error("The nickname is already used as the name of the channel.\n");
}

void Command::nick() {
  try {
    // ユーザーがすでに登録されているかどうかをチェック
    check_user_registration_status(_user);
    // 引数を処理
    process_title_arguments(_parser.get_args());
    // ニックネームが長すぎるかどうかをチェック
    string nickname = _parser.get_args().at(0);
    check_nickname_length(nickname);
    // nicknameに使える文字を選別 (A-Z, a-z, 0-9, []\^_{|}` )
    check_nickname_characters(nickname);
    // { -> [  | -> \  } -> ]  ~ -> _
    replaceSpecialCharacters(nickname);
    // 他のユーザーと重複していないか確認
    check_nickname_uniqueness(_server, nickname);
    // ニックネームと同じ名前のチャンネルを探す
    check_nickname_against_channel_names(_server, nickname);
    // ニックネームを設定
    _user.set_nickname(nickname);
    // フラグを更新
    _user.set_is_nickname(true);
    // ニックネームを表示
    string response = "Nick set to: " + nickname + "\n";
    send(_user.get_fd(), response.c_str(), response.size(), 0);
  } catch (const exception &e) {
    send(_user.get_fd(), e.what(), strlen(e.what()), 0);
    // cerr << e.what() << endl;
  }
}
