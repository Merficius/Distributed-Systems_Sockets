
#include "server.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>

// Variables globales
char c1 = 'U';
char c2 = 'U';
// entero a 64 bits representado en LITTLE-ENDIAN
long i = -1;
char c3 = 'U';
char c4 = 'U';

int recv_integer(int client_sock);
char recv_character(int client_sock);

int main(int argc, char *argv[])
{
    int socket_desc = initialization();
    
    while(1) {
        
        int client_sock = connection(socket_desc);
        
        // Recuperación primeros dos caracteres
        char c1 = recv_character(client_sock);
        printf("%c\n", c1);
        char c2 = recv_character(client_sock);
        printf("%c\n", c2);

        // Lectura de caracteres enviados (representados en big-endian) para los primeros 4 bytes del long (representado en little-endian)
        char c3 = recv_character(client_sock);
        char c4 = recv_character(client_sock);
        char c5 = recv_character(client_sock);
        char c6 = recv_character(client_sock);
        
        // Creación de variable long y puntero para asignar valores
        long i;
        char *p = (char *)&i;
        
        // Asignación de valores para el long representado en little-endian
        p[3] = c3;
        p[2] = c4;
        p[1] = c5;
        p[0] = c6;
        p[4] = 0;
        p[5] = 0;
        p[6] = 0;
        p[7] = 0;
        printf("%ld\n", i);
        
        // Recuperación de últimos dos caracteres
        char c7 = recv_character(client_sock);
        printf("%c\n", c7);
        char c8 = recv_character(client_sock);
        printf("%c\n", c8);
    }
    
    close(socket_desc);
    return 0;
}

int recv_integer(int client_sock)
{
    int read_size, integer;
    
    // receive a message from client
    read_size = recv(client_sock, &integer, sizeof(integer), 0);
    
    if(read_size == 0) {
        puts("Client disconnected");
        fflush(stdout);
    }
    else if(read_size == -1) {
        perror("recv failed");
    }
    
    return integer;
}

char recv_character(int client_sock)
{
    int read_size;
    char character;
    
    // receive a message from client
    read_size = recv(client_sock, &character, sizeof(character), 0);
    
    if(read_size == 0) {
        puts("Client disconnected");
        fflush(stdout);
    }
    else if(read_size == -1) {
        perror("recv failed");
    }
    
    return character;
}
