import socket
import sys

HOST = "127.0.0.1"
PORT = 9000

def start_client():
    try:
        client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        
        print(f"Connection to {HOST}:{PORT}...")
        client_socket.connect((HOST, PORT))
        print("Connected!")
        print("Enter 'exit' to exit the programm")

        while True:
            message = input("You: ")

            #if message.lower() == 'shutdown':
            #    break

            if not message:
                continue

            full_message = message + "\n"
            
            client_socket.sendall(full_message.encode('utf-8'))

            data = client_socket.recv(1024)
            if not data:
                print("Server closed the connection.")
                break
                
            print("Server replied: ")
            print(f"{data.decode('utf-8')}")

    except ConnectionRefusedError:
        print("Erro: No connection. Check if server works!")
    except Exception as e:
        #print(f"Error happend: {e}")
        print("")
    finally:
        client_socket.close()
        print("\nConnection closed.")
        input("Press Enter to exit...")

if __name__ == "__main__":
    start_client()