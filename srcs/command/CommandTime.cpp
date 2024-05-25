#include "Command.hpp"

void Command::show_time()
{
    time_t rawtime;
    struct tm *timeinfo;
    char buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, 80, "Current time: %H:%M:%S\n", timeinfo);
    send(_user.get_fd(), buffer, strlen(buffer), 0);
}