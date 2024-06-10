<h1 align="center">
	ft_irc
</h1>

<p align="center">
	<b><i>Internet Relay Chat</i></b><br>
</p>

---

## About the project

> _This project is about creating your own IRC server.
You will use an actual IRC client to connect to your server and test it.
Internet is ruled by solid standards protocols that allow connected computers to interact
with each other.
It’s always a good thing to know._


## Usage

### Requirements

The function is written in C language and thus needs the **`c++` compiler** and some standard **C, C++ libraries** to run.

First install a client, here we'll use irssi since it is the one we chose to do the project with :
```shell
# using apt to install
sudo apt install irssi

# using brew to install
brew install irssi
```

### Instructions

**1. Compiling the program**

To compile, go to the program path and run:

```shell
make
```

**2. Executing the program**

To launch the server, run:

```shell
./ircserv [port number] [password]
```

## Behaviors

Connect to the server with a Netcat
```shell
nc localhost [port]
```
Connect to the server with a IRSSI
```shell
irssi
/connect localhost [port] [password]
```

## Commands

### Auth Commands
<ul>
    <li>
        <strong>PASS</strong>: <em>&lt;password&gt;</em><br>
        The password is used to connect to the server
    </li>
    <li>
        <strong>NICK</strong>: <em>&lt;nickname&gt;</em><br>
        The nickname is used to identify you on the server
    </li>
    <li>
        <strong>USER</strong>: <em>&lt;username&gt; &lt;hostname&gt; &lt;servername&gt; &lt;realname&gt;</em><br>
        The username is used to identify you on the server
    </li>
</ul>

### Other Commands
<ul>
    <li>
        <strong>JOIN</strong>: <em>&lt;#channel&gt;</em><br>
        The channel is used to join a channel
    </li>
    <li>
        <strong>PART</strong>: <em>&lt;#channel&gt;</em><br>
        The channel is used to leave a channel
    </li>
    <li>
        <strong>PRIVMSG</strong>: <em>&lt;nickname&gt; &lt;message&gt;</em><br>
        The nickname is used to send a private message to a user
    </li>
    <li>
        <strong>PRIVMSG</strong>: <em>&lt;#channel&gt; &lt;message&gt;</em><br>
        The channel is used to send a message to a channel
    </li>
    <li>
        <strong>PRIVMSG</strong>: <em>bot announce &lt;message&gt;</em><br>
        The bot is used to send a message to all users in server
    </li>
    <li>
        <strong>PRIVMSG</strong>: <em>bot &lt;channel list | channel join | channel invite&gt;</em><br>
        The bot is used to see the list of channels, joining channel, or invited channel
    </li>
    <li>
        <strong>PRIVMSG</strong>: <em>bot sendfile &lt;nickname&gt; &lt;filename_path&gt;</em><br>
        The bot is used to send a file to a user
    </li>
    <li>
        <strong>PRIVMSG</strong>: <em>bot getfile &lt;nickname&gt; &lt;filename_path&gt;</em><br>
        The bot is used to get a file from a user
    </li>
    <li>
        <strong>QUIT</strong>: <em>&lt;message&gt;</em><br>
        The message is used to leave the server
    </li>
    <li>
        <strong>PING</strong>: <em>&lt;server&gt;</em><br>
        The server is used to check the connection with the server
    </li>
    <li>
        <strong>KICK</strong>: <em>&lt;#channel&gt; &lt;nickname&gt;</em><br>
        The channel is used to kick a user from a channel
    </li>
    <li>
        <strong>MODE</strong>: <em>&lt;#channel&gt; &lt;mode&gt;</em><br>
        The channel is used to change the mode of a channel
        <ul>
            <li><strong>Modes:</strong>
                <ul>
                    <li>o : Give operator status to a user</li>
                    <li>l : Only operators can change the channel limit</li>
                    <li>t : Only operators can change the topic</li>
                    <li>k : Set a password to join the channel</li>
                    <li>i : Set the channel to invite only</li>
                </ul>
            </li>
        </ul>
    </li>
    <li>
        <strong>TOPIC</strong>: <em>&lt;#channel&gt; &lt;topic&gt;</em><br>
        The channel is used to change the topic of a channel
    </li>
    <li>
        <strong>INVITE</strong>: <em>&lt;#channel&gt; &lt;nickname&gt;</em><br>
        The channel is used to invite a user to a channel
    </li>
    <li>
        <strong>TIME</strong>:<br>
        The time is used to check the time of the server
    </li>
    <li>
        <strong>VERSION</strong>:<br>
        The version is used to check the version of the server
    </li>
    <li>
        <strong>HELP</strong>: <em>&lt;command&gt;</em><br>
    </li>
</ul>

