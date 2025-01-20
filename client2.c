#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUF_SIZE 512

int main(int argc, char *argv[])
{
int client_socket;
struct sockaddr_in server_addr;
FILE *fp;
char buf[BUF_SIZE];
ssize_t read_size;

if (argc != 3) {
fprintf(stderr, "Usage: %s <ip> <port>\n", argv[0]);
exit(EXIT_FAILURE);
}

client_socket = socket(AF_INET, SOCK_STREAM, 0);
if (client_socket < 0) {
perror("socket");
exit(EXIT_FAILURE);
}

server_addr.sin_family = AF_INET;
server_addr.sin_port = htons(atoi(argv[2]));
if (inet_pton(AF_INET, argv[1], &server_addr.sin_addr) <= 0) {
perror("inet_pton");
exit(EXIT_FAILURE);
}

if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
perror("connect");
exit(EXIT_FAILURE);
}

printf("Connected with %s:%d\n", argv[1], atoi(argv[2]));

fp = fopen("file.txt", "wb");
if (fp == NULL) {
perror("fopen");
exit(EXIT_FAILURE);
}

while ((read_size = recv(client_socket, buf, BUF_SIZE, 0)) > 0) {
if (fwrite(buf, 1, read_size, fp) != read_size) {
perror("fwrite");
exit(EXIT_FAILURE);
}
}

fclose(fp);
close(client_socket);

return 0;
}
