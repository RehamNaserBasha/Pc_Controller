import socket

def create_client():
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_address = ('192.168.1.11', 8080)  # Update to the server's address

    try:
        client_socket.connect(server_address)
        print(f"Connected to server at {server_address}")

        while True:
            # Get the command from the user
            command = input("Enter command (1-linkdin \n 2-github\n 3-Youtube\n 4-chatGPT/n 5-embedded linux\n 7-vscode\n 8-terminal\n 9-Exit\n): ")

            # Exit loop if user enters "Exit"
            if command.lower() == "exit":
                print("Closing connection.")
                client_socket.sendall(command.encode('utf-8'))  # Notify the server to exit
                break

            # Send the command to the server
            client_socket.sendall(command.encode('utf-8'))

            # Receive the server's response
            response = client_socket.recv(1024)
            if not response:
                print("No response from server.")
                break

            print(f"Received from server: {response.decode('utf-8')}")

    except Exception as e:
        print(f"Error: {e}")

    finally:
        client_socket.close()
        print("Connection closed.")

if __name__ == "__main__":
    create_client()
