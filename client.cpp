// client.cpp
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    std::string message;
    char buffer[1024] = {0};
    // 创建套接字
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        std::cerr << "Socket creation error" << std::endl;
        return -1;
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8888); // 将 IP 地址转换为网络字节序
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
    {
        std::cerr << "Invalid address/ Address not supported" << std::endl;
        return -1;
    } // 连接到服务器
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        std::cerr << "Connection Failed" << std::endl;
        return -1;
    }
    while (1)
    { // 发送数据
        std::getline(std::cin, message);
        if (send(sock, message.c_str(), message.length(), 0) < 0)
        {
            std::cout << "Send failed\n";
            return -1;
        }
        std::cout << "Send succ\n"; // 接收数据
        valread = read(sock, buffer, 1024);
        if (valread < 0)
        {
            perror("Read failed");
            std::cout << "Read failed";
            return -1;
        }
        else if (valread > 0)
        {
            std::cout << "Server response: " << buffer << std::endl;
        }
    }
    return 0;
}