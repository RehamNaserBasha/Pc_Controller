#include <iostream>
#include <cstring>
#include <algorithm>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstdlib>
#include <string.h>
#include "server.hpp"


#define port 8080 

ServerSocket::ServerSocket(){

}
ServerSocket::~ServerSocket(){
    
};
void ServerSocket::trim(std::string &str){
    str.erase(std::find_if(str.rbegin() , str.rend() ,[](unsigned char ch){
       return !std::isspace(ch); 
    }).base() , str.end());
}
std::string ServerSocket::read() {
    std::string input;
    std::getline(std::cin, input);  // Reading input from standard input
    return input;
}

// Implement the send function
void ServerSocket::send(const std::string& message) {
    std::cout << message << std::endl;  // Output message to standard output
}
void openlink(const std::string& link)
{
   std::string command = "xdg-open \"" + link + "\"";
   system(command.c_str());
}
 
void handleclient(int client_socket)
{
    std::string full_command;

   char buffer[1024]={0};
   read(client_socket,buffer,1024);
   std::string command(buffer);
   
   if(command == "linkdin")
   {
    openlink("https://www.linkedin.com/in/reham-naser-715551260/");
   }
   else if(command =="github")
   {
     openlink("https://github.com/RehamNaserBasha");
   }
   else if(command =="Youtube")
   {
    openlink("https://www.youtube.com/");
   }
   else if(command =="chatGPT")
   {
    openlink("https://chatgpt.com/");
   }
   else if(command =="embedded linux")
   {
    openlink("https://www.youtube.com/results?search_query=embeded+linux");
   }
   else
   {
    std::string response ="Unknown Command";
    send(client_socket,response.c_str(),response.size(),0);
   }
   
   std::string sucessMessage ="Command excuted :" +command;
   send(client_socket,sucessMessage.c_str(),sucessMessage.size(),0);
   close(client_socket);
}

int main()
{
    int server_fd,new_socket;
    sockaddr_in address,cli_addr;
    socklen_t clilen;
    int addrlen = sizeof(address);
    server_fd=socket(AF_INET,SOCK_STREAM,0);
    if (server_fd < 0)
    {
        perror("Socket failed");
        return 1;
    }
    address.sin_family=AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port=htons(port);
    if(bind(server_fd,(sockaddr *)&address,sizeof(address)) < 0)
    {
        perror("Bind failed");
        return 1;
    }

    listen (server_fd,5);
    
    std::cout<<"Server is listening on port" << " " << port <<std::endl;
    while (true) {
        new_socket = accept(server_fd, (sockaddr *)&address, (socklen_t *)&addrlen);
        
        if (new_socket < 0) 
        {
            perror("Accept failed");
            continue;
        }
        ServerSocket server;
        std::string s;
        s=server.read();
        server.trim(s);
        std::cout << "Data recieved:" << std::endl;
        if(s== "exit")
        {
            server.send("Exiting...........\n");
        }

     handleclient(new_socket);
    }
    close(server_fd);
    return 0;
}
