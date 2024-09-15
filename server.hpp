#ifndef SERVER_SOCKET_HPP
#define SERVER_SOCKET_HPP
#include <array>
#include<iostream>
#include <string.h>
#include <cstring>
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class ServerSocket{
private:
int server_IB;
int client_IB;
sockaddr_in sockaddr_accept;
std::array<char, 5000>buffer; 
public:
ServerSocket();
~ServerSocket();
void trim(std::string &str);
void send_data_to_client(const std::string &message);
void send(const std::string &message);
std::string read();
std::string receive_data_from_client();
};
#endif
