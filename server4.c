// Xác thực việc gửi và nhận tin nhắn đã thành công chưa
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

int main(){
int server_sock, client_sock, c, read_size;
struct sockaddr_in server, client;
char client_message[2000];
char *acknowledgement = "Message received.";

server_sock = socket(AF_INET, SOCK_STREAM, 0);
server.sin_family = AF_INET;
server.sin_addr.s_addr = INADDR_ANY;
server.sin_port = htons(8888);

bind(server_sock, (struct sockaddr *)&server, sizeof(server));

listen(server_sock, 3);

c = sizeof(struct sockaddr_in);
client_sock = accept(server_sock, (struct sockaddr *)&client, (socklen_t*)&c);

while( (read_size = recv(client_sock, client_message, 2000, 0)) > 0 ){
printf("Received message from client: %s\n", client_message);
write(client_sock, acknowledgement, strlen(acknowledgement));
}

if(read_size == 0){
printf("Client disconnected.\n");
}else if(read_size == -1){
printf("Error in receiving message from client.\n");
return -1;
}

return 0;
}
