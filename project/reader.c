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

/* Socket */
#define MAX_LINE		256
#define MAX_PENDING		10
#define MAX_THREAD		5
#define PORT_NUMBER 	8888

// int fd = 0;		// client socket descriptor

/* Thread */
pthread_t socketthread_recv;
pthread_t socketthread_send;
pthread_mutex_t lock;





int is_sock_running = 0;

/* parameter */
char str[80];

/* Function */
void *thread_recv(void *arg);
void *thread_send(void *arg);

void *start_server(void *arg)
{
	// structs to represent the server and client
	struct sockaddr_in server_addr, client_addr;

	int sock;	// socket descriptor
	int *port_number = (int*) arg;

	// if port_number = -1 then close the socket
	if (*port_number == -1)
		return;
	
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
	if (*port_number != 0) server_addr.sin_port = htons(*port_number);
	else server_addr.sin_port = htons(PORT_NUMBER);	// specify port number
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


	int sin_size = sizeof(struct sockaddr_in);

	while (1  /*  && is_running */)
	{
		int fd = accept(sock, (struct sockaddr *)&client_addr,(socklen_t *)&sin_size);
		printf("Server got a connection from (%s, %d)\n", inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));

		is_sock_running = 1;
		
		pthread_create(&socketthread_recv, NULL, thread_recv, (void *)&fd);
		pthread_create(&socketthread_send, NULL, thread_send, (void *)&fd);
	}
	

	// printf("Start receiving.\n");
	// char buf[MAX_LINE];


	// while (recv(fd, buf, sizeof(buf), 0) > 0 && is_sock_running)
	// {
	// 	printf("%s\n", buf);
	// 	if (buf[0] == '$')
	// 	{
	// 		printf("quit!!!\n");
	// 		is_sock_running = 0;
	// 	}
	// 	memset(buf, 0, MAX_LINE * sizeof(char));
	// }		
    // 4. accept: wait until we get a connection on that port
    
    //     	int sin_size = sizeof(struct sockaddr_in);
    // 	int fd = accept(sock, (struct sockaddr *)&client_addr,(socklen_t *)&sin_size);

    // while(1)
    // {

	   //  char data[80] = "data\n";
	   //  send(fd, data, strlen(data), 0);
	   //  printf("Server sent data.\n");
	   //  sleep(1);
    // }



  //   char buf[80];
  //   while(1)
  //   {
  // //   	if ((fgets(buf, sizeof(buf), stdin)) > 0) {
		// // 	// buf[79] = '\0';
		// // 	// // int len = strlen(buf) + 1;
		// // 	// send(fd, buf, strlen(buf), 0);
		// // 	// printf("send data.\n");
		// // 	if (buf == "q\n")
		// // 	{
		// // 		printf("break.\n");
		// // 		break;
		// // 	}
		// // 	else
		// // 	{
		// // 		printf("wrong.\n");
		// // 	}
		// // }
		// char send_data[80] = "hhhhh";
		// // sprintf(send_data, "%d", number);
		// send(fd, send_data, strlen(send_data), 0);
		// printf("send data.\n");
		// sleep(1);
  //   }
  //   while(1)
  //   {
  //   	pthread_mutex_lock(&lock);
  //   	char send_data[80];
		// sprintf(send_data, "%d", number);
	 //    send(fd, send_data, strlen(send_data), 0);
	 //    pthread_mutex_unlock(&lock);
  //   }
    // int i;
    // for (i = 0; i < 20; i ++)
    // {
	   //  char send_data[80] = "here's the message\n";
	   //  send(fd, send_data, strlen(send_data), 0);    	
	   //  printf("Send message.\n");
	   //  sleep(1);
    // }




//while(count++<10)
//{	

// pthread_mutex_lock(&lock);

// 	char send_data[80];
// 	sprintf(send_data, "%d", number);

// pthread_mutex_unlock(&lock);

//     // 6. send: send a message over the socket
//     send(fd, send_data, strlen(send_data), 0);
//}	    
    // printf("Server sent message: %s\n", send_data);
    
    // 7. close: close the socket connection



	

}

void *thread_recv(void *arg) {
	int sock = *((int *) arg);
	printf("Start receiving from socket: %d\n", sock);

	char buf[MAX_LINE];

	while (recv(sock, buf, sizeof(buf), 0) > 0 && is_sock_running)
	{
		printf("%s\n", buf);
		if (buf[0] == '$')
		{
			printf("quit!!!\n");
			is_sock_running = 0;
		}
		memset(buf, 0, MAX_LINE * sizeof(char));
	}		

    printf("Server closed connection\n");
    close(sock);

}

void *thread_send(void *arg) {
	int sock = *((int *) arg);
	printf("Start sending to socket: %d\n", sock);

	char buf[MAX_LINE];

	while (fgets(buf, sizeof(buf), stdin) > 0 && is_sock_running)
	{
		if (buf == "quit")
			is_sock_running = 0;
		send(sock, buf, strlen(buf), 0);
		memset(buf, 0, MAX_LINE * sizeof(char));
	}

}

main(int argc, char *argv[])
{
	/* connect the device IO */
	int fd = open("/dev/cu.usbmodem1421", O_RDWR);
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

	int port_number;
	if(argc == 2)
	{
		port_number = atoi(argv[1]);
	}
	else
	{
		port_number = 0;
	}

	/* create thread */
	if(pthread_mutex_init(&lock, NULL) != 0)
	{
		fprintf(stderr, "Error initializing lock.\n");
		exit(1);
	}

	if(pthread_create(&socketthread_recv, NULL, start_server, (void*)&port_number))
	{
		fprintf(stderr, "Error creating thread.\n");
		exit(1);
	}

	// while(1);
	printf("Start reading from arduino.\n");

	// char str[80];

	while(1)
	{

		char buf[80];
		memset(buf, 0, 80 * sizeof(char));
		int bytes_read = read(fd, buf, 80);

		if(bytes_read > 0)
		{
			strcat (str, buf);

			if (strlen(str) > 50) 
			{	
								printf("%s", str);
				memset(str, 0, 80 * sizeof(char));
			}
		}


	}


	
}

