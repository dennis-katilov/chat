#include <iostream>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>

using namespace std;

int main(int argc, char const* argv[]){
    int server;
    int client;

    struct sockaddr_in server_address;
    
    client = socket(AF_INET, SOCK_STREAM, 0);

    if (client<0){
        cout<< "SERVER ERROR: establishing socket error.";
        exit(0);
    }

    cout<< "SERVER: socket was created";
}

