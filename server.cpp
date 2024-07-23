#include <iostream>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>

#define DEFAULT_PORT 1601
#define ERROR_S "SERVER ERROR "
#define BUFFER_SIZE 1024
#define CLIENT_CLOSE_CONNECTION_SYMBOL "#"

bool is_client_connection_close(const char* msg);

using namespace std;

int main(int argc, char const* argv[]){
    int server;
    int client;

    struct sockaddr_in server_address;
    
    client = socket(AF_INET, SOCK_STREAM, 0);

    if (client<0){
        cout<< ERROR_S << ": establishing socket error";
        exit(0);
    }

    cout<< "SERVER: socket was created";

    server_address.sin_port = htons(DEFAULT_PORT);
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htons(INADDR_ANY);

    int ret = bind(client, reinterpret_cast<struct sockaddr*>(&server_address),sizeof(server_address));
    if (ret<0){
        cout<< ERROR_S << "binding connection";
        return -1;
    }

     socketlen_t size = sizeof(server_address);
     cout<< "SERVER: Listening client";
     listen(client,1);
     server = accept(client, reinterpret_cast<struct sockaddr*>(&server_address), &size);
     if (server<0){
        cout<< ERROR_S << "No accept client";
     }

    char buffer[BUFFER_SIZE];
    while (server>0){
        strcpy(buffer, "=> server connected");
        send(server, buffer, BUFFER_SIZE, 0);
        cout<< "Connected to client #1" << endl;
        cout<< "Enter" << CLIENT_CLOSE_CONNECTION_SYMBOL << "to end the connection";
        cout<< "Client ";
        recv(server, buffer, BUFFER_SIZE,0);
        cout<< buffer << endl;
        if (is_client_connection_close(buffer)){

        }

    }
     
}

bool is_client_connection_close(const char* msg){
    for (int i=0; i<strlen(msg); ++i){
        if (msg[i]==CLIENT_CLOSE_CONNECTION_SYMBOL){
            return true;
        }
    return false;
}

    
}

