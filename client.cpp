#include <sys/socket.h>
#include <iostream>
#include <string>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

#define PORT 6667
#define SERVER_IP "127.0.0.1"
#define BUF_SIZE 1024

void	exit_error(const string& msg) {
	cerr << "ERROR: " << msg << endl;
	exit(1);
}

int main(void) {
	int client_socketfd;

	client_socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if (client_socketfd == -1) {
		exit_error("socket");
	}
	cout << "SUCCESS: socket: " << client_socketfd << endl;

	struct sockaddr_in client_addr;
	client_addr.sin_family = AF_INET;
	client_addr.sin_port = htons(PORT);
	client_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

	if (connect(client_socketfd, (struct sockaddr *)&client_addr, sizeof(client_addr)) == -1) {
		close(client_socketfd);
		exit_error("connect");
	}

	cout << "SUCCESS: connection" << endl;

	while (1) {
		cout << "input message: ";
		char send_msg[BUF_SIZE];
		cin.getline(send_msg, BUF_SIZE);

		if (send(client_socketfd, &send_msg, strlen(send_msg), 0) == -1) {
			cerr << "ERROR: send" << endl;
			break ;
		}
		
		char recv_msg[BUF_SIZE] = {0};
		ssize_t recv_size = recv(client_socketfd, &recv_msg, BUF_SIZE, 0);
		if (recv_size == -1) {
			cerr << "ERROR: recv" << endl;
			break ;
		} else if (recv_size == 0) {
			cout << "finish connection" << endl;
			break ;
		}
		cout << recv_msg;
	}

	close(client_socketfd);
	return 0;
}