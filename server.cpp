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

     int size = sizeof(server_address);
     cout<< "SERVER: Listening client";
}

