#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
//client va server gui tin nhan qua lai
int main(int argc, char *argv[]) {
int sock;
struct sockaddr_in server;
char message[1000], server_reply[2000];

// Tạo socket
sock = socket(AF_INET, SOCK_STREAM, 0);
if (sock == -1) {
printf("Không thể tạo socket!");
}

// Thiết lập thông tin server
server.sin_addr.s_addr = inet_addr("127.0.0.1");
server.sin_family = AF_INET;
server.sin_port = htons(8888);

// Kết nối đến server
if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
perror("connect failed");
return 1;
}

printf("Đã kết nối đến Server\n");

// Gửi và nhận tin liên tục
while (1) {
printf("Nhập tin nhắn của bạn: ");
scanf("%s", message);

// Gửi tin nhắn đến server
if (write(sock, message, strlen(message)) < 0) {
puts("Gửi thất bại");
return 1;
}

// Nhận phản hồi từ server
if (recv(sock, server_reply, 2000, 0) < 0) {
puts("Nhận thất bại");
break;
}

printf("Server: %s\n", server_reply);
memset(server_reply, 0, sizeof(server_reply));
}

close(sock);
return 0;
}
