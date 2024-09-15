import socket

def create_client():
    client_socket=socket.socket(socket.AF_INET,socket.SOCK_STREAM)

    server_address=('192.168.1.7',8080)
    #client_socket.listen(5)
    try:
        client_socket.connect(server_address)
        print(f"connected to server at {server_address}")
        
        command=input("Enter command ('1-linkdin \n' '2-github  \n' '3- Youtube \n' '4-chatGPT \n' '5-embedded linux \n'):")
                     
                      
                      
        client_socket.sendall(command.encode('utf-8'))
        response =client_socket.recv(1024)
        print(f"Recieved from server :{response.decode('utf-8')}")
    except Exception as e:
        print(f"Error:{e}")
    finally:
        client_socket.close()
        print("Connection closed.")
    
    
if __name__=="__main__":
    create_client()
