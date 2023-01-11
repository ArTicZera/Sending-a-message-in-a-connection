//gcc -o bin.exe connect_server.c -lws2_32
#include <Winsock2.h>
#include <stdio.h>

#define PORT 80 //HTTP port

int main(int argc, char* argv[]) 
{
    WSADATA wsa;
    SOCKET skt;
	
    struct sockaddr_in sin;
    char buffer[] = "A quick brown fox jumps over the lazy dog!";
	char ip[] = "142.251.129.206";
    
    //Initializates winsock dll
    int init = WSAStartup(MAKEWORD(2, 2), &wsa);
    if (init != 0) {
        printf("\nWSAStartup failed: %d\n", init);
        return 1;
    } else {
		printf("\nWinsock started.\n");
	}

    //Create socket
    skt = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (skt == INVALID_SOCKET) {
        printf("\nSocket failed: %d\n", skt);
        return 1;
    } else {
		printf("Socket created.\n");
	}

    //Fill sockaddr_in struct
    sin.sin_addr.s_addr = inet_addr(ip); //Google IP
    sin.sin_family = AF_INET; //IPv4
    sin.sin_port = htons(PORT);

    //Connects to the server
    int connection = connect(skt, (struct sockaddr*)&sin, sizeof(sin));
    if (connection == SOCKET_ERROR) {
        printf("\nConnection failed: %d\n", connection);
        return 1;
    } else {
		printf("Connected to %s.\n", ip);
	}	

    //Sends the message
    int sendmsg = send(skt, buffer, sizeof(buffer), 0);
    if (sendmsg == SOCKET_ERROR) {
        printf("\nSending message failed: %d\n", sendmsg);
        return 1;
    } else {
		printf("Message sent.\n");
	}
	
	//Shutdown the socket
	int end = shutdown(skt, SD_SEND);
	if (end == SOCKET_ERROR) {
		printf("\nShutdown failed: %d\n", end);
		return 1;
	} else {
		printf("Socket Desligado.\n");
	}

    //Close the socket and terminates winsock dll
    closesocket(skt);
    WSACleanup();
	
    return 0;
}