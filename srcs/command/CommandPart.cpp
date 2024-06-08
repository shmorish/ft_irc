#include "Command.hpp"

// 想定されるエラー
// ERR_NOSUCHCHANNEL (403): 存在しない、または参加していないチャンネルから退出しようとした場合に返されます。
// ERR_NOTONCHANNEL (442): ユーザーが指定したチャンネルに実際には参加していない場合にこのエラーが返されます。
// ERR_NEEDMOREPARAMS (461): コマンドに必要なパラメータが不足している場合に送られます。例えば、PARTコマンドを使用する際にチャンネル名を指定しなかった場合などです。

void Command::part() {
    try {
        if (_parser.get_args().size() != 1)
            throw runtime_error(err_461(_user, "PART"));
        string channel_name = _parser.get_args().at(0);
        if (channel_name.at(0) != '#')
            throw runtime_error(err_403(_user, channel_name));
        Channel *channel = _server.findChannelByName(channel_name);
        if (channel == NULL)
            throw runtime_error(err_403(_user, channel_name));
        if (channel->is_client(_user.get_fd()) == false)
            throw runtime_error(err_442(_user, channel_name));
        string res = success_response(_user, "PART", channel_name);
        _server.sendMsgToChannel(channel_name, res);
        channel->remove_client(_user.get_fd());
        channel->remove_invited(_user.get_fd());
        channel->remove_can_talk_in_mod_channel(_user.get_fd());
        channel->remove_operator(_user.get_fd());
        if (channel->get_clients().size() == 0) {
            delete channel;
            _server.get_channels().erase(channel);
        }
    } catch (const exception &e) {
        send(_user.get_fd(), e.what(), strlen(e.what()), 0);
    }
}
