#include <iostream>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>

using namespace std;

#define SERVER_IP "127.0.0.1"
#define DEFAULT_PORT 1601
#define ERROR_S "SERVER ERROR "
#define CLIENT_CLOSE_CONNECTION_SYMBOL "#"
#define BUFFER_SIZE 1024

bool is_client_connection_close(const char* msg);

int main(int argc, char const* argv[]){
    int client;

    struct sockaddr_in server_address;

    client = socket(AF_INET, SOCK_STREAM, 0);

    if (client<0){
        cout<< ERROR_S << ": establishing socket error\n";
        exit(0);
    }

    server_address.sin_port = htons(DEFAULT_PORT);
    server_address.sin_family = AF_INET;
    inet_pton(AF_INET, SERVER_IP, &server_address.sin_addr);

    cout<< "=> CLIENT: socked was created\n";

    int ret = connect(client, reinterpret_cast<const struct sockaddr*>(&server_address),sizeof(server_address));
    if (ret==0){
        cout<<"=> CLIENT: Connection to server "
            << inet_ntoa(server_address.sin_addr)
            << " on port " << DEFAULT_PORT << "\n";      
    }

    char buffer[BUFFER_SIZE];
    recv(client, buffer,BUFFER_SIZE, 0);
    cout<< "=> CLIENT: Connected establishing\n";
    cout<< "=> CLIENT: Enter " << CLIENT_CLOSE_CONNECTION_SYMBOL << " to end the connection\n";
    
    while (true){
        cout<< "CLIENT-> ";
        cin.getline(buffer, BUFFER_SIZE);
        send(client, buffer, BUFFER_SIZE, 0);
        if (is_client_connection_close(buffer)){
                break;
        }
        cout<< "SERVER<- ";
        recv(client, buffer, BUFFER_SIZE, 0);
            cout<< buffer<<endl;
            if (is_client_connection_close(buffer)){
                break;
            }
    }
    close(client);
    cout<<"Bye\n";
    
    return 0;
}

bool is_client_connection_close(const char* msg){
    for (int i=0; i<strlen(msg); ++i){
        if (msg[i]=='#'){
            return true;
        }
    }
    return false;
}
