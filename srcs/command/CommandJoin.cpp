#include "Command.hpp"

// 想定されるエラー
// ERR_NOSUCHCHANNEL (403): 指定されたチャンネルが存在しない場合に返されます。このエラーは、チャンネル名が間違っているか、存在しないチャンネルにアクセスしようとした場合に発生します。
// ERR_TOOMANYCHANNELS (405): ユーザーが同時に参加できるチャンネルの最大数に達している場合に返されます。
// ERR_NOTREGISTERED (451): "You have not registered" というメッセージを伴い、クライアントがネットワークに対してユーザー名（NICK）や実際の名前（USERコマンドの一部）の登録が完了していない状態でコマンドを実行しようとしたときに発生します。
// ERR_NEEDMOREPARAMS (461): コマンドに必要なパラメータが不足している場合に返されます。例えば、JOINコマンドにチャンネル名が含まれていない場合などです。
// ERR_CHANNELISFULL (471): チャンネルが既に最大ユーザー数に達しており、これ以上のユーザーを受け入れられない場合に返されます。
// ERR_INVITEONLYCHAN (473): チャンネルが招待制で、ユーザーが招待されていない場合に返されます。
// ERR_BANNEDFROMCHAN (474): ユーザーがそのチャンネルから禁止されている（BANされている）場合に返されます。
// ERR_BADCHANNELKEY (475): チャンネルに入るためのキー（パスワード）が間違っている、または提供されていない場合に返されます。
// ERR_BADCHANMASK (476): 指定されたチャンネル名が無効な形式である場合に返されます。

// 未対応のエラー 473, 474, 475

static bool invalid_char(string str) {
    string invalid = "[]\\`_^{|} ,:;<>@$%&!*()+?\"'";
    for (size_t i = 0; i < str.size(); i++) {
        if (invalid.find(str[i]) != string::npos)
            return true;
    }
    return false;
}

static void check_valid_channel_name(const vector<string> &args, User _user, Server &_server) {
    if (_user.get_ready_to_connect() == false)
        throw runtime_error(err_451(_user));
    if (args.size() < 1 || 2 < args.size())
        throw runtime_error(err_461(_user, "JOIN"));
    string channel_name = args.at(0);
    if (channel_name.size() > MAX_CHANNEL_NAME_LEN || channel_name.at(0) != '#' || invalid_char(channel_name))
        throw runtime_error(err_476(_user));
    if (_user.get_joining_channel_count() >= CONNECTABLE_CHANNEL_MAX)
        throw runtime_error(err_405(_user));
    Channel *channel = _server.findChannelByName(channel_name);
    if (channel != NULL) {
        if (channel->is_client(_user.get_fd()) == true)
            throw runtime_error(err_443(_user, channel_name));
        if (channel->is_banned(_user.get_fd()) == true)
            throw runtime_error(err_474(_user, channel_name));
        if (channel->channel_is_full() == true)
            throw runtime_error(err_471(_user, channel_name));
    }
}

void send_success_response(User _user, string channel_name, string members, string mode) {
    string res = success_response(_user, "JOIN", channel_name);
    send(_user.get_fd(), res.c_str(), res.size(), 0);

    res = response353(_user, channel_name, members);
    send(_user.get_fd(), res.c_str(), res.size(), 0);

    res = response366(_user, channel_name);
    send(_user.get_fd(), res.c_str(), res.size(), 0);

    res = response324(_user, channel_name, mode);
    send(_user.get_fd(), res.c_str(), res.size(), 0);
}

void Command::join() {
    try {
        check_valid_channel_name(_parser.get_args(), _user, _server);
    } catch (const exception &e) {
        send(_user.get_fd(), e.what(), strlen(e.what()), 0);
        return;
    }
    string channel_name = _parser.get_args().at(0);
    string key = _parser.get_args().size() == 2 ? _parser.get_args().at(1) : "";
    Channel *channel = _server.findChannelByName(channel_name);
    string channel_mode = "n";
    if (channel == NULL) {
        try {
            _server.get_channels().insert(new Channel(channel_name));
            channel = _server.findChannelByName(channel_name);
            channel->add_client_nickname(_user.get_fd(), _user.get_nickname());
            channel->add_client(_user.get_fd());
            channel->add_operator(_user.get_fd());
            if (key != "") {
                channel_mode += "k";
                channel->set_password(key);
                channel->set_mode(Channel::NeedPassword);
            }
            send_success_response(_user, channel_name, channel->get_nickname_list(), channel_mode);
        } catch (const exception &e) {
            send(_user.get_fd(), e.what(), strlen(e.what()), 0);
        }
    } else {
        try {
            if (channel->get_mode() & Channel::NeedPassword) {
                if (channel->get_password() != key)
                    throw runtime_error(err_475(_user, channel_name));
                channel_mode += "k";
            }
            if (channel->get_mode() & Channel::InviteOnly) {
                if (channel->is_invited(_user.get_fd()) == false)
                    throw runtime_error(err_473(_user, channel_name));
                channel->remove_invited(_user.get_fd());
                channel_mode += "i";
            }
            channel->add_client_nickname(_user.get_fd(), _user.get_nickname());
            channel->add_client(_user.get_fd());
            send_success_response(_user, channel_name, channel->get_nickname_list(), channel_mode);
        } catch (const exception &e) {
            send(_user.get_fd(), e.what(), strlen(e.what()), 0);
        }
    }
}
