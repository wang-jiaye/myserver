// server.cpp
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <string>

int main()
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    std::string resp = "respond from server";

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {

        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8888);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 5) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                                 (socklen_t *)&addrlen)) < 0)
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        while (1)
        {
            std::memset(buffer, 0, sizeof(buffer));
            valread = read(new_socket, buffer, 1024);
            if (valread <= 0)
            {
                std::cout << "client disconnected" << std::endl;
                break;
            }
            std::cout << buffer << std::endl;

            send(new_socket, resp.c_str(), resp.length(), 0);
            std::cout << "respond message sent\n";
        }

        close(new_socket);
    }
    return 0;
}
