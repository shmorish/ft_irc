#ifndef UTILS_HPP
#define UTILS_HPP

#include <algorithm>
#include <arpa/inet.h>
#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <exception>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <poll.h>
#include <set>
#include <signal.h>
#include <sstream>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

using namespace std;

#include "response.hpp"

#define BLUE "\033[0;34m"
#define RESET "\033[0m"
#ifdef DEBUG
#define DEBUG_MSG(x, ...) cout << BLUE << "[DEBUG]: " << x << " " << __VA_ARGS__ << RESET << endl
#else
#define DEBUG_MSG(x, ...)
#endif

#ifndef OPEN_MAX
#define OPEN_MAX 10240
#endif

template<typename T>
std::string to_string(const T &value) {
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

#endif
