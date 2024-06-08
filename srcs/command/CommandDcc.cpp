#include "Command.hpp"

void Command::dcc() {}

// void Command::dcc()
// {
//     try {
//         if (_parser.get_args().size() != 2)
//             throw runtime_error(err_461(_user, "DCC"));
//         string sub_command = _parser.get_args().at(0);
//         // if (sub_command == "SEND")
//         //     send_file();
//         // else if (sub_command == "ACCEPT")
//         //     accept_file();
//         // else if (sub_command == "LIST")
//         //     list_file();
//         // else if (sub_command == "CHAT")
//         //     chat();
//         // else
//         //     throw runtime_error(err_421(_user, sub_command));
//     }
//     catch (const exception &e) {
//         send(_user.get_fd(), e.what(), strlen(e.what()), 0);
//     }
// }