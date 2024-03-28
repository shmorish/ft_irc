#ifndef UTILS_HPP
# define UTILS_HPP

# include <iostream>
# include <string>
# include <exception>
# include <cerrno>
# include <sys/socket.h>
# include <sys/types.h>
# include <arpa/inet.h>
# include <unistd.h>

using namespace std;

# define BLUE "\033[0;34m"
# define RESET "\033[0m"
#ifdef DEBUG
    #define DEBUG_MSG(x, ...) cout << BLUE << "[DEBUG]: " << x << " " << __VA_ARGS__ << RESET << endl
#else
    #define DEBUG_MSG(x, ...)
#endif

#endif