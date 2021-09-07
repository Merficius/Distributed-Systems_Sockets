
#include "cliente.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

char c1 = 'A';
char c2 = 'B';
int i = 16; // Entero a 32 bits representado en LITTLE-ENDIAN
char c3 = 'C';
char c4 = 'D';

void send_integer(int sock);
void send_character(int sock, char* character);

int main(int argc, char *argv[])
{
    int sock = connection();
    
    // creando puntero para acceder a diferentes valores
    char *p = &c1;
    
    // Envío de primeros dos caracteres
    send_character(sock, &p[0]);
    send_character(sock, &p[1]);
    
    // Envío de entero dividido en 4 bytes usando caracteres, ordenado en big-endian
    
    send_character(sock, &p[7]);
    send_character(sock, &p[6]);
    send_character(sock, &p[5]);
    send_character(sock, &p[4]);
    
    // Envío de últimos dos caracteres
    send_character(sock, &p[8]);
    send_character(sock, &p[9]);
    
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

void send_character(int sock, char* character)
{
    printf("Sending byte value: %d with address %p\n", *character, character);
    if( send(sock, character, sizeof(*character), 0) < 0) {
        puts("Send failed");
        exit(1);
    }
}
