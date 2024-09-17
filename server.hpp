#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>

class ServerSocket {
public:
    ServerSocket();
    ~ServerSocket();

    void trim(std::string &str);
    std::string read();
    void send_message(int client_socket, const std::string& message);
};


#endif
