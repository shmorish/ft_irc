#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include "utils.hpp"
#define VERSION "1.0.0"
#define SERVER_NAME "irc.localhost"
#define SERVER_DATE __DATE__

#define USER_IDENTIFIER(nickname, username) (std::string(":") + nickname + "!" + username + "@" + SERVER_NAME)

#define RPL_WELCOME(fd, nickname)								" 001 " + nickname + " :Welcome to the Internet Relay Network fd[" + to_string(fd) + "] !" + SERVER_NAME + "\r\n"
#define RPL_YOURHOST(server_name, nickname)						" 002 " + nickname + " :Your host is " + servername + ", running version " + VERSION + "\r\n"
#define RPL_CREATED(date, nickname)								" 003 " + nickname + " :This server was created " + date + "\r\n"
#define RPL_MYINFO(nick)										" 004 " + nick + " :" + SERVER_NAME + " " + VERSION + " itkolmt it" + "\r\n"
#define RPL_ALREADYONCHANNEL(NickName,invNickName,Chanel)		"112 " + NickName + " " + invNickName + " " + Chanel + " :is already on channel"
#define ERR_CANNOTKICKOP(NickName,channel)						"113 " + NickName + " " + channel + " :You can't KICK the operator"

#define RPL_UMODEIS(nick, mode)									"221 " + nick + " " + mode

#define RPL_WHOISUSER(nick1,nick2,user,host,realname)			"311 " + nick1 + " " + nick2 + " " + user + " " + host + " * :" + realname
#define RPL_WHOISSERVER(nick1, nick2, ser, infos)				"312 " + nick1 + " " + nick2 + " " + ser + " :" + infos
#define RPL_WHOISIDLE(nick1, nick2, diff, int)					"317 " + nick1 + " " + nick2 + " " + diff + " " + int + " :seconds idle"
#define RPL_ENDOFWHOIS(nick1,nick2)								"318 " + nick1 + " " + nick2 + " :End of /WHOIS list"
#define RPL_CHANNELMODEIS(nick, channel, modestring, modeArg)	"318 " + nick + " " + channel + " " + modestring + " " + modeArg
#define RPL_WHOISCHANNELS(nick1,nick2, channels)				"319 " + nick1 + " " + nick2 + " :" + channels
#define RPL_LISTSTART(nick)										"321 " + nick + " Channel :Users Name"
#define RPL_LIST(nick, ch, nb, topic)							"322 " + nick + " " + ch + " " + nb + " :" + topic
#define RPL_LISTEND(nick)										"323 " + nick + " :End of /LIST"
#define ERR_SPECIFYPARAM(nick, channel)							"325 " + nick + " " + channel + "o :You must specify a parameter for the op mode. Syntax: <nick>"
#define RPL_NOTOPIC(nick, ch)									"331 " + nick + " " + ch + " :No topic is set"
#define RPL_TOPIC(nick, ch, topic)								"332 " + nick + " " + ch + " :" + topic
#define RPL_INVITING(rec, sen, ch)								"341 " + rec + " " + sen + " " + ch
#define RPL_NAMREPLY(nick, ch, members)							"353 " + nick + " = " + ch + " :" + members
#define RPL_ENDOFNAMES(nick, ch)								"366 " + nick + " " + ch + " :End of /NAMES list"
#define RPL_MOTD(nick, line)									"372 " + nick + " :" + line
#define RPL_MOTDSTART(Nickname)									"375 " + Nickname + " :- <Iba7lawn n irc> Message of the day - "
#define RPL_ENDOFMOTD(nick)										"376 " + nick + " :End of /MOTD command"
#define RPL_YOUREOPER(nick)										"381 " + nick + " :You are now an IRC operator"
#define ERR_NOUSERS(NickName,chanel)							"395 " + NickName + " " + chanel + " :User does not exist"

#define ERR_NOSUCHNICK(nick,nick_channel)						"401 " + nick + " " + nick_channel + " :No such nick/channel"
#define ERR_NOSUCHSERVER(nick, ser)								"402 " + nick + " " + ser + " :No such server"
#define ERR_NOSUCHCHANNEL(nick, ch)								"403 " + nick + " " + ch + " :No such channel"
#define ERR_CANNOTSENDTOCHAN(nick)								"404 " + nick + " :Cannot send to channel"
#define ERR_NOORIGIN(nick)										"409 " + nick + " :No origin specified"
#define ERR_NOTEXTTOSEND(nick)									"412 " + nick + " :No text to send"
#define ERR_UNKNOWNCOMMAND(nick, cmd)							"421 " + nick + " " + cmd + " :Unknown command"
#define ERR_NONICKNAMEGIVEN(nick)								"431 " + nick + " :No nickname given"
#define ERR_ERRONEUSNICKNAME(nick)								"432 " + nick + " :Erroneus nickname"
#define ERR_NICKNAMEINUSE(nick)									"433 " + nick + " :Nickname is already in use"
#define ERR_USERNOTINCHANNEL(nick, nick2, ch)					"441 " + nick + " " + nick2 + " " + ch + " :They aren't on that channel"
#define ERR_NOTONCHANNEL(nick, ch)								"442 " + nick + " " + ch + " :You're not on that channel"
#define ERR_USERONCHANNEL(nick, ch)								"443 " + nick + " " + ch + " :is already on channel"
#define ERR_NOTREGISTERED(Client)								"451 " + Client + " :You have not registered"
#define ERR_NEEDMOREPARAMS(nick)								"461 " + nick + " :Not enough parameters"
#define ERR_PASSWDMISMATCH(nick)								"464 " + nick + " :Incorrect password"
#define ERR_ALREADYREGISTRED(nick)								"462 " + nick + " :You may not reregister"
#define ERR_CHANNELISFULL(nick, ch)								"471 " + nick + " " + ch + " :Cannot join channel (+l)"
#define ERR_UNKNOWNMODE(nick, char)								"472 " + nick + " " + char + " :is unknown mode char to me"
#define ERR_INVITEONLYCHAN(nick, ch)							"473 " + nick + " " + ch + " :Cannot join channel (+i)"
#define ERR_BADCHANNELKEY(nick, ch)								"475 " + nick + " " + ch + " :Cannot join channel (+k)"
#define ERR_BADCHANNAME(nick)									"479 " + nick + " :Invalid channel name"
#define ERR_NOPRIVILEGES(nick)									"481 " + nick + " :Permission Denied- You're not an IRC operator"
#define ERR_CHANOPRIVSNEEDED(nick, ch)							"482 " + nick + " " + ch + " :You're not channel operator"
#define ERR_NOOPERHOST(nick)									"491 " + nick + " :No O-lines for your host"

#define ERR_USERSDONTMATCH(nick)								"502 " + nick + " :Cant change mode for other users"

#define ERR_TOOMANYPARAM(Client)								"4001 " + Client + " :Too Many Paramater, Please try again!"
#define ERR_ALLREADYENTERPASS(Client)							"4002 " + Client + " :You have already entered the password!"
#define RPL_CORRECTPASS(Client)									"4003 " + Client + " :Your password is correct ✅"
#define ERR_MISSPASS(Client)									"4004 " + Client + " :Please enter the password to connect to the server first. 🚫"

class User;
string err_401(User user, string nickname);
string err_403(User user, string channel_name);
string err_405(User user);
string err_432(User user, string nickname);
string err_433(User user, string nickname);
string err_442(User user, string channel_name);
string err_443(User user, string channel_name);
string err_451(User user);
string err_461(User user, string command);
string err_462(User user);
string err_464(User user);
string err_471(User user, string channel_name);
string err_472(User user);
string err_473(User user, string channel_name);
string err_475(User user, string channel_name);
string err_476(User user);
string err_482(User user, string channel_name);
string err_696(User user);

//  332, 353, 366, 324

string response332(User user, string channel_name, string topic);
string response353(User user, string channel_name, string members);
string response366(User user, string channel_name);
string response324(User user, string channel_name, string mode);
string response341(User user, string channel_name, string nickname);

string success_response(User user, string command, string arg);

#endif
