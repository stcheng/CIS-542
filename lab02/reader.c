#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

/* Thread */
pthread_t socketthread;
pthread_mutex_t lock;

/* Socket */
#define PORT_NUMBER 12322

/* parameter */
int value;

void *start_server()
{
	// structs to represent the server and client
	struct sockaddr_in server_addr, client_addr;

	int sock;	// socket descriptor

	// 1. socket: creates a socket descriptor that you later use to make other system calls
	if((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("Socket");
		exit(1);
	}
	int temp;
	if(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &temp, sizeof(int)) == -1)
	{
		perror("Setsockopt");
		exit(1);
	}

	// configure the server
	server_addr.sin_port = htons(PORT_NUMBER);	// specify port number
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	bzero(&(server_addr.sin_zero),8);
    
    // 2. bind: use the socket and associate it with the port number
    if (bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1) {
        perror("Unable to bind");
        exit(1);
    }
    
    // 3. listen: indicates that we want to listn to the port to which we bound; second arg is number of allowed connections
    if (listen(sock, 5) == -1) {
        perror("Listen");
        exit(1);
    }
    
    // printf("\nServer waiting for connection on port %d\n", PORT_NUMBER);
    // fflush(stdout);
    
    while(1)
	{

    // 4. accept: wait until we get a connection on that port
    int sin_size = sizeof(struct sockaddr_in);
    int fd = accept(sock, (struct sockaddr *)&client_addr,(socklen_t *)&sin_size);
    printf("Server got a connection from (%s, %d)\n", inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
    
    // buffer to read data into
    // char recv_data[1024];
    
    // 5. recv: read incoming message into buffer
    // int bytes_received = recv(fd,recv_data,1024,0);
    // null-terminate the string
    // recv_data[bytes_received] = '\0';
    
    // printf("Server received message: %s\n", recv_data);
    
    // echo back the message to the client
	pthread_mutex_lock(&lock);

	char *send_data = "Thank you!\n";
	pthread_mutex_unlock(&lock);

    // 6. send: send a message over the socket
    send(fd, send_data, strlen(send_data), 0);
    
    // printf("Server sent message: %s\n", send_data);
    
    // 7. close: close the socket connection
    close(fd);
    
    // printf("Server closed connection\n");

	}

}

main(int argc, char *argv)
{
	/* connect the device IO */
	int fd = open("/dev/ttyUSB10", O_RDWR);
	if(fd == -1)
	{
		fprintf(stderr, "Error opening the file.\n");
		exit(1);
	}

	struct termios options;
	tcgetattr(fd, &options);
	cfsetispeed(&options, 9600);
	cfsetospeed(&options, 9600);
	tcsetattr(fd, TCSANOW, &options);

	/* create thread */
	if(pthread_mutex_init(&lock, NULL) != 0)
	{
		fprintf(stderr, "Error initializing lock.\n");
		exit(1);
	}

	if(pthread_create(&socketthread, NULL, start_server, NULL))
	{
		fprintf(stderr, "Error creating thread.\n");
		exit(1);
	}
	

	while(1)
	{


		char buf[80];
		int bytes_read = read(fd, buf, 80);
	
		if(bytes_read > 0)
		{
			printf("%s", buf);	
			char *pch;
			pch = strtok (buf, " ");
			printf("%s", pch);

		}
		memset(buf, 0, 80 * sizeof (char));

	}
}

