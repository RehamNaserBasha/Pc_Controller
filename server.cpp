#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <string>
#include <array>
#include <algorithm>
#include "server.hpp"


#define PORT 8080 
ServerSocket::ServerSocket() {}

ServerSocket::~ServerSocket() {};

void ServerSocket::trim(std::string &str) {
    str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char ch) {
        return !std::isspace(ch); 
    }).base(), str.end());
}

std::string ServerSocket::read() {
    std::string input;
    std::getline(std::cin, input);  
    return input;
}

void ServerSocket::send_message(int client_socket, const std::string& message) {
    send(client_socket, message.c_str(), message.size(), 0);
}


void openlink(const std::string& link) {
    std::string command = "xdg-open \"" + link + "\"";
    system(command.c_str());
}
std::string open_vs_code(){
    FILE *fp;
    fp = popen("code", "r");
    if(!fp){
        std::cerr << "The process is unsuccess" << std::endl;
        return "Error\n";
    }
    char buffer[128];
    std::string result;
    while((fgets(buffer, sizeof(buffer), fp)) != nullptr){
        result+=buffer;
    }
    pclose(fp);
    return result;
}

void open_terminal() 
{
    std::cout << "Opening Terminal..." << std::endl;
    system("gnome-terminal");  
}
void handleclient(int client_socket)
 {
    char buffer[1024] = {0};
    ServerSocket server;

    while (true) {
        
        memset(buffer, 0, sizeof(buffer));

        
        ssize_t bytes_read = read(client_socket, buffer, sizeof(buffer) - 1);

        
        if (bytes_read <= 0) {
            std::cout << "Client disconnected or error in receiving data.\n";
            break;
        }

        // Null-terminate the buffer to make it a proper C-string
        buffer[bytes_read] = '\0';

        std::string command(buffer);
        command.erase(std::remove(command.begin(), command.end(), '\n'), command.end());

        server.trim(command);
        std::cout << "Command received: " << command << std::endl;

        // Check if the client wants to terminate the connection
        if (command == "exit") {
            std::cout << "Exit command received. Closing connection." << std::endl;
            std::string exitMessage = "Connection terminated by client.";
            server.send_message(client_socket, exitMessage);
            break; // Exit the loop, which will eventually close the socket
        }

        // Process different commands
        if (command == "linkdin") {
            std::cout << "Opening LinkedIn link..." << std::endl;
            openlink("https://www.linkedin.com/in/reham-naser-715551260/");
        } else if (command == "github") {
            std::cout << "Opening GitHub link..." << std::endl;
            openlink("https://github.com/RehamNaserBasha");
        } else if (command == "Youtube") {
            std::cout << "Opening YouTube link..." << std::endl;
            openlink("https://www.youtube.com/");
        } else if (command == "chatGPT") {
            std::cout << "Opening ChatGPT link..." << std::endl;
            openlink("https://chatgpt.com/");
        } else if (command == "embedded linux") {
            std::cout << "Opening Embedded Linux search..." << std::endl;
            openlink("https://www.youtube.com/results?search_query=embedded+linux");
        }
        else if (command == "vscode")
            {
               open_vs_code(); 
            }
        else if (command == "terminal")
             {
                open_terminal();
             }
        else {
            std::string response = "Unknown Command";
            std::cout << "Unknown command received: " << command << std::endl;
            server.send_message(client_socket, response);
        }

        // Send back a success message after each command is processed
        std::string successMessage = "Command executed: " + command;
        server.send_message(client_socket, successMessage);
    }

    // Close the socket after the client exits or disconnects
    close(client_socket);
    std::cout << "Connection closed.\n";
}

int main() {
    int server_fd, new_socket;
    sockaddr_in address;
    socklen_t addrlen = sizeof(address);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("Socket failed");
        return 1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        return 1;
    }

    listen(server_fd, 5);
    std::cout << "Server is listening on port " << PORT << std::endl;

    while (true) {
        new_socket = accept(server_fd, (sockaddr *)&address, &addrlen);
        if (new_socket < 0) {
            perror("Accept failed");
            continue;
        }
        handleclient(new_socket);
    }

    close(server_fd);
    return 0;
}
