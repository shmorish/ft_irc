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

// static bool isSpecialTitleCharacter(const char c) {
//   const string special = "[]\\`_^{|}";
//   return special.find(c) != std::string::npos;
// }

// nicknameに使える文字を選別
// A-Z, a-z, 0-9, []\^_{|}`
// static void check_nickname_characters(const string nickname) {

//     for (char c : nickname) {
//         if (!(isalnum(c) || )) {
//             throw runtime_error("Invalid character in nickname: " + to_string(c));
//         }
//     }
// }
// 同じニックネームの人物を探す
static void check_nickname_uniqueness(Server server, string nickname) {
  for (std::set<User*>::iterator it = server.get_users().begin(); it != server.get_users().end(); it++)
    if ((*it)->get_nickname().compare(nickname) == 0)
      throw runtime_error("nickname is already used\n");
}

// ニックネームと同じ名前のチャンネルを探す
// static void check_nickname_against_channel_names(Server server, const string nickname) {
//   for (std::set<Channel>::iterator it = server.get_channels().begin(); it != server.get_channels().end(); ++it)
//       if (it->get_channel_name().compare(nickname) == 0)
//         throw runtime_error("The nickname is already used as the name of the channel.\n");
// }

void  Command::nick()
{
  try {
    // ユーザーがすでに登録されているかどうかをチェック
    check_user_registration_status(_user);
    // 引数を処理
    process_title_arguments(_parser.get_args());
    // ニックネームが長すぎるかどうかをチェック
    check_nickname_length(_parser.get_args().at(0));
    // nicknameに使える文字を選別
    // A-Z, a-z, 0-9, []\^_{|}`
    // { -> [  | -> \  } -> ]  ~ -> _
    // 他のユーザーと重複していないか確認
    // if (has_duplicate_nickname(_server, _parser.get_args().at(0)) == true) {
    // 	throw runtime_error("nickname is already used\n");
    // }
    // チャンネル名と重複していないか確認
    check_nickname_uniqueness(_server, _parser.get_args().at(0));
    // ニックネームと同じ名前のチャンネルを探す
    // check_nickname_against_channel_names(_server, _parser.get_args().at(0));
    _user.set_nickname(_parser.get_args().at(0));
    _user.set_is_nickname(true);
  } catch (const exception &e) {
    send(_user.get_fd(), e.what(), strlen(e.what()), 0);
    // cerr << e.what() << endl;
  }
}
