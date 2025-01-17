#include <iostream>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>

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
        cout<< ERROR_S << ": establishing socket error\n";
        exit(0);
    }

    cout<< "=> SERVER: socket was created\n";

    server_address.sin_port = htons(DEFAULT_PORT);
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htons(INADDR_ANY);

    int ret = bind(client, reinterpret_cast<struct sockaddr*>(&server_address),sizeof(server_address));
    if (ret<0){
        cout<< ERROR_S << "binding connection\n";
        return -1;
    }

     socklen_t size = sizeof(server_address);
     cout<< "=> SERVER: Listening client\n";
     listen(client,1);
     server = accept(client, reinterpret_cast<struct sockaddr*>(&server_address), &size);
     if (server<0){
        cout<< ERROR_S << "No accept client\n";
     }

    char buffer[BUFFER_SIZE];
    bool isExit=false;
    while (server>0){
        strcpy(buffer, "=> SERVER: server connected\n");
        send(server, buffer, BUFFER_SIZE, 0);
        cout<< "=> SERVER: Connected to client #1\n";
        cout<< "=> SERVER: Enter " << CLIENT_CLOSE_CONNECTION_SYMBOL << " to end the connection\n";
        cout<< "Client<- ";
        recv(server, buffer, BUFFER_SIZE,0);
        cout<< buffer << endl;
        if (is_client_connection_close(buffer)){
            isExit=true;
        }

        while (!isExit){
            cout<<"Server-> ";
            cin.getline(buffer, BUFFER_SIZE);
            send(server, buffer, BUFFER_SIZE, 0);
            if (is_client_connection_close(buffer)){
                break;
            }
            cout<< "Client<- ";
            recv(server, buffer, BUFFER_SIZE, 0);
            cout<< buffer<<endl;
            if (is_client_connection_close(buffer)){
                break;
            }
        }
        cout<<"Bye\n";
        isExit=false;
        exit(1);
    }
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

