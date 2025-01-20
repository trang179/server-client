//Xác thực việc gửi và nhận tin nhắn đã thành công chưa
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

int main(){
int sock;
struct sockaddr_in server;
char *message = "Hello, server!";

sock = socket(AF_INET, SOCK_STREAM, 0);

server.sin_addr.s_addr = inet_addr("127.0.0.1");
server.sin_family = AF_INET;
server.sin_port = htons(8888);

connect(sock, (struct sockaddr *)&server, sizeof(server));

if(send(sock, message, strlen(message), 0) < 0){
printf("Error in sending message to server.\n");
return -1;
}

char server_acknowledgement[2000];
if(recv(sock, server_acknowledgement, 2000, 0) < 0){
printf("Error in receiving acknowledgement from server.\n");
return -1;
}

printf("Received acknowledgement from server: %s\n", server_acknowledgement);

return 0;
}
