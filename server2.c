#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUF_SIZE 512

int main(int argc, char *argv[])
{
int server_socket, client_socket;
socklen_t client_addr_size;
struct sockaddr_in server_addr, client_addr;
FILE *fp;
char buf[BUF_SIZE];
ssize_t read_size;

if (argc != 3) {
fprintf(stderr, "Usage: %s <ip> <port>\n", argv[0]);
exit(EXIT_FAILURE);
}

server_socket = socket(AF_INET, SOCK_STREAM, 0);
if (server_socket < 0) {
perror("socket");
exit(EXIT_FAILURE);
}

server_addr.sin_family = AF_INET;
server_addr.sin_port = htons(atoi(argv[2]));
if (inet_pton(AF_INET, argv[1], &server_addr.sin_addr) <= 0) {
perror("inet_pton");
exit(EXIT_FAILURE);
}

if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
perror("bind");
exit(EXIT_FAILURE);
}

if (listen(server_socket, 5) < 0) {
perror("listen");
exit(EXIT_FAILURE);
}

printf("Waiting for client...\n");

client_addr_size = sizeof(client_addr);
client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_size);
if (client_socket < 0) {
perror("accept");
exit(EXIT_FAILURE);
}

printf("Connected with %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

fp = fopen("file.txt", "rb");
if (fp == NULL) {
perror("fopen");
exit(EXIT_FAILURE);
}

while ((read_size = fread(buf, 1, BUF_SIZE, fp)) > 0) {
if (send(client_socket, buf, read_size, 0) < 0) {
perror("send");
exit(EXIT_FAILURE);
}
}

fclose(fp);
close(client_socket);
close(server_socket);

return 0;
}
