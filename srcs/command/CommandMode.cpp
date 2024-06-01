#include "Command.hpp"

/* ◦[+|-]o => オペレータ権限の授与[+]・剥奪[-] */
/* /mode #channel +o nickname  ＝＞  nickname にチャンネルオペレータ権限を与えます */
/* /mode #channel -o nickname  ＝＞  nickname からチャンネルオペレータ権限を奪います */

/* ◦[+|-]l => チャンネル参加クライアント数の制限 */
/* /mode #channel +l 100       ＝＞  #channel の参加数を100に制限します */
/* /mode #channel -l           ＝＞  #channel の参加数制限を解除します */

/* ◦[+|-]t => トピック変更権：オペレータのみ[+]・誰でも[-] */
/* /mode #channel +t           ＝＞  オペレータのみ #channel のトピックを変更できるようにします */
/* /mode #channel -t           ＝＞  誰でも #channel のトピックの変更ができるようにします */

/* ◦[+|-]m => モデレートチャンネル属性の設定[+]・解除[-] */
/* /mode #channel +m           ＝＞  オペレータのみ #channel で発言できるようにします */
/* /mode #channel -m           ＝＞  誰でも #channel で発言できるようにします */

/* ◦[+|-]v => モデレートチャンネル属性のチャンネルでの発言権の授与[+]・剥奪[-] */
/* /mode #channel +v nickname  ＝＞  +m フラグの立っている #channel で nickname が発言できるようにしますを与えます */
/* /mode #channel -v nickname  ＝＞  +m フラグの立っている #channel で 発言権のある nickname から発言権を奪います */

/* ◦[+|-]k => チャンネルキー(パスワード)の設定[+]・解除[-] */
/* /mode #channel +k password */
/* /mode #channel -k password */

static void is_correct_input(const vector<string> &args, Server &_server, User &_user, Parser &_parser) {
    if (args.size() < 2)
        throw runtime_error("Too few arguments\n");
    if (args.at(0).at(0) != '#')
        throw runtime_error("Channel name must start with #\n");
    Channel *channel = _server.findChannelByName(_parser.get_args().at(0));
    if (channel == NULL)
        throw runtime_error("Channel not found");
    if(channel->is_client(_user.get_fd()) == false)
        throw runtime_error("User not found in this channel");
    if(channel->is_operator(_user.get_fd()) == false)
        throw runtime_error("You are not operator");
    string flag = _parser.get_args().at(1);
    if (flag.size() != 2 || (flag.at(0) != '+' && flag.at(0) != '-'))
        throw runtime_error("Invalid mode");
}

void    Command::mode_command_o(Channel *channel) {
    if (_parser.get_args().size() != 3)
        throw runtime_error("Too few arguments\n");
    string flag = _parser.get_args().at(1);
    string nickname = _parser.get_args().at(2);
    User *user = _server.findUserByNick(nickname);
    if (flag.at(0) == '+')
        channel->add_operator(user->get_fd());
    else
        channel->remove_operator(user->get_fd());
}

void    Command::mode_command_l(Channel *channel) {
    string flag = _parser.get_args().at(1);
    if (flag.at(0) == '+') {
        if (_parser.get_args().size() != 3)
            throw runtime_error("Too few arguments\n");
        char *end;
        long limit = strtol(_parser.get_args().at(2).c_str(), &end, 10);
        if (*end != '\0')
            throw runtime_error("Invalid limit\n");
        if (limit < 0)
            throw runtime_error("Invalid limit\n");
        if (limit > OPEN_MAX)
            throw runtime_error("Limit is too high\n");
        if ((size_t)limit < channel->get_clients().size())
            throw runtime_error("Limit is too low\n");
        channel->set_users_limit(limit);
    } else {
        if (_parser.get_args().size() != 2)
            throw runtime_error("Too few arguments\n");
        channel->set_users_limit(OPEN_MAX);
    }
}

void    Command::mode_command_t(Channel *channel) {
    string flag = _parser.get_args().at(1);
    Channel::ChannelMode mode = channel->get_mode();
    if (flag.at(0) == '+') {
        mode = Channel::ChannelMode(mode | Channel::TopicOpOnly);
        channel->set_mode(mode);
    } else {
        mode = Channel::ChannelMode(mode & Channel::TopicOpOnly);
        channel->set_mode(mode);
    }
}

void    Command::mode_command_m(Channel *channel) {
    string flag = _parser.get_args().at(1);
    Channel::ChannelMode mode = channel->get_mode();
    if (flag.at(0) == '+') {
        mode = Channel::ChannelMode(mode | Channel::Moderated);
        channel->set_mode(mode);
    } else {
        mode = Channel::ChannelMode(mode & Channel::Moderated);
        channel->set_mode(mode);
    }
}

void    Command::mode_command_v(Channel *channel) {
    string flag = _parser.get_args().at(1);
    string nickname = _parser.get_args().at(2);
    if (_parser.get_args().size() != 3)
        throw runtime_error("Too few arguments\n");
    User *user = _server.findUserByNick(nickname);
    if (flag.at(0) == '+')
        channel->add_can_talk_in_mod_channel(user->get_fd());
    else
        channel->remove_can_talk_in_mod_channel(user->get_fd());
}

void    Command::mode_command_k(Channel *channel) {
    string flag = _parser.get_args().at(1);
    if (_parser.get_args().size() != 3)
        throw runtime_error("Too few arguments\n");
    Channel::ChannelMode mode = channel->get_mode();
    if (flag.at(0) == '+') {
        mode = Channel::ChannelMode(mode | Channel::NeedPassword);
        channel->set_mode(mode);
        channel->set_password(_parser.get_args().at(2));
    } else {
        mode = Channel::ChannelMode(mode & Channel::NeedPassword);
        channel->set_mode(mode);
        channel->set_password("");
    }
}

void    Command::mode(){
    // MODE #channel_name <mode>
    try
    {
        is_correct_input(_parser.get_args(), _server, _user, _parser);
        char mode = _parser.get_args().at(1).at(1);
        if (mode != 'o' && mode != 'l' && mode != 't' && mode != 'm' && mode != 'v' && mode != 'k')
            throw runtime_error("Invalid mode");
        Channel *channel = _server.findChannelByName(_parser.get_args().at(0));
        if (mode == 'o') mode_command_o(channel);
        else if (mode == 'l') mode_command_l(channel);
        else if (mode == 't') mode_command_t(channel);
        else if (mode == 'm') mode_command_m(channel);
        else if (mode == 'v') mode_command_v(channel);
        else if (mode == 'k') mode_command_k(channel);

    } catch(const exception &e) {
        send(_user.get_fd(), e.what(), strlen(e.what()), 0);
    }
}

