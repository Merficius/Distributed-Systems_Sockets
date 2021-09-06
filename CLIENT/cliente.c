
#include "cliente.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

void send_integer(int sock);

int main(int argc, char *argv[])
{
    int sock = connection();
    
    // communicating with server
    send_integer(sock);
    
    close(sock);
    return 0;
}

void send_integer(int sock)
{
    int integer;
    
    printf("Enter an integer: ");
    scanf("%d", &integer);
    printf("The integer is: %d\n", integer);
    
    // send some data
    if(send(sock, &integer, sizeof(integer), 0) < 0) {
        puts("Send failed");
        exit(1);
    }
}
