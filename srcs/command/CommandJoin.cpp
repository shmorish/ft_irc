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
	if(_user.get_ready_to_connect() == false)
		throw runtime_error(err_451(_user));
	if (args.empty() == true || args.size() > 1)
		throw runtime_error(err_461(_user, "JOIN"));
	string channel_name = args.at(0);
	if (channel_name.size() > MAX_CHANNEL_NAME_LEN ||
		channel_name.at(0) != '#' ||
		invalid_char(channel_name))
		throw runtime_error(err_476(_user));
	if (_user.get_joining_channel_count() >= CONNECTABLE_CHANNEL_MAX)
		throw runtime_error(err_405(_user));
	Channel *channel = _server.findChannelByName(channel_name);
	if (channel != NULL && channel->channel_is_full() == true)
		throw runtime_error(err_471(_user, channel_name));
}

void Command::join()
{
	try {
		check_valid_channel_name(_parser.get_args(), _user, _server);
	} catch (const exception &e) {
		send(_user.get_fd(), e.what(), strlen(e.what()), 0);
		return ;
	}
	string channel_name = _parser.get_args().at(0);
	Channel *channel = _server.findChannelByName(channel_name);
	if (channel == NULL) {
		try {
			_server.get_channels().insert(new Channel(channel_name));
			channel->add_client(_user.get_fd());
			channel->add_operator(_user.get_fd());
			string message = "You have created and joined the channel\n";
			send(_user.get_fd(), "You have joined the channel\n", 28, 0);
		} catch (const exception &e) {
			send(_user.get_fd(), e.what(), strlen(e.what()), 0);
		}
	}
	else {
		try {
			set<int> client_fds = channel->get_clients();
			for (set<int>::iterator it = client_fds.begin(); it != client_fds.end(); it++)
				if (*it == _user.get_fd())
					throw runtime_error("You are already in this channel\n");
			channel->add_client(_user.get_fd());
			send(_user.get_fd(), "You have joined the channel\n", 28, 0);
		} catch (const exception &e) {
			send(_user.get_fd(), e.what(), strlen(e.what()), 0);
		}
	}
}
