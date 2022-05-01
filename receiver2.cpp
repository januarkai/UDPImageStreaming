#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>

void listenForPackets()
{
    int listeningSocket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (listeningSocket <= 0)
    {
        // NSLog(@"Error: listenForPackets - socket() failed.");
        return;
    }

    // set timeout to 2 seconds.
    struct timeval timeV;
    timeV.tv_sec = 2;
    timeV.tv_usec = 0;

    if (setsockopt(listeningSocket, SOL_SOCKET, SO_RCVTIMEO, &timeV, sizeof(timeV)) == -1)
    {
        // NSLog(@"Error: listenForPackets - setsockopt failed");
        close(listeningSocket);
        return;
    }

    // bind the port
    struct sockaddr_in sockaddr;
    memset(&sockaddr, 0, sizeof(sockaddr));

    // sockaddr.sin_len = sizeof(sockaddr);
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(8585);
    sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    int status = bind(listeningSocket, (struct sockaddr *)&sockaddr, sizeof(sockaddr));
    if (status == -1)
    {
        close(listeningSocket);
        // NSLog(@"Error: listenForPackets - bind() failed.");
        return;
    }

    // receive
    struct sockaddr_in receiveSockaddr;
    socklen_t receiveSockaddrLen = sizeof(receiveSockaddr);

    while (1)
    {
        size_t bufSize = 1024;
        void *buf = malloc(bufSize);
        // unsigned char* data;
        ssize_t result = recvfrom(listeningSocket, buf, bufSize, 0, (struct sockaddr *)&receiveSockaddr, &receiveSockaddrLen);
        if (result > 0)
        {
            printf("Success\n");
        }
        else{
            printf("No packet\n");
        }
    }

    close(listeningSocket);
}

int main()
{
    listenForPackets();
}
