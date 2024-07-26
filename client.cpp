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
#define SERVER_CLOSE_CONNECTION_SYMBOL "#"

bool is_client_connection_close(const char* msg);

int main(int argc, char const* argv[]){
    int client;

    struct sockaddr_in server_address;

    client = socket(AF_INET, SOCK_STREAM, 0);

    if (client<0){
        cout<< ERROR_S << ": establishing socket error";
        exit(0);
    }

    server_address.sin_port = htons(DEFAULT_PORT);
    server_address.sin_family = AF_INET;
    inet_pton(AF_INET, SERVER_IP, &server_address.sin_addr);

    cout<<"=> Client socked was created";
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
