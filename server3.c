#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
// client va server gui tin nhan qua lai
int main(int argc, char *argv[]) {
int socket_desc, client_sock, c, read_size;
struct sockaddr_in server, client;
char client_message[2000];

// Tạo socket
socket_desc = socket(AF_INET, SOCK_STREAM, 0);
if (socket_desc == -1) {
printf("Không thể tạo socket!");
}

// Thiết lập thông tin server
server.sin_family = AF_INET;
server.sin_addr.s_addr = INADDR_ANY;
server.sin_port = htons(8888);

// Bind socket đến IP và port
if (bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0) {
perror("bind failed.");
return 1;
}

// Listen
listen(socket_desc, 3);

printf("Đang chờ kết nối...\n");
c = sizeof(struct sockaddr_in);

// Chấp nhận kết nối đến client
client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
if (client_sock < 0) {
perror("accept failed.");
return 1;
}

printf("Kết nối đã được thiết lập!\n");

// Gửi và nhận tin liên tục
while ((read_size = recv(client_sock, client_message, 2000, 0)) > 0) {
printf("Client: %s\n", client_message);
printf("Nhập tin nhắn của bạn: ");
scanf("%s", client_message);
write(client_sock, client_message, strlen(client_message));
memset(client_message, 0, 2000);
}

if (read_size == 0) {
puts("Client đã ngắt kết nối.");
fflush(stdout);
} else if (read_size == -1) {
perror("recv failed.");
}

return 0;
}
