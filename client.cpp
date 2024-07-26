#include <iostream>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>


bool is_client_connection_close(const char* msg);

int main(int argc, char const* argv[]){
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
