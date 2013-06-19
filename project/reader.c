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
#define MAX_BUFF		80
#define MAX_PENDING		10
#define MAX_THREAD		5
#define PORT_NUMBER 	8888

/* Arduino */
int serial;		// file descriptor of serial port

/* Thread */
pthread_t socketthread_recv;
pthread_t socketthread_send;
pthread_t command_thread;
pthread_mutex_t lock;

int is_sock_running = 0;
int is_prog_running = 0;

/* parameter */
char str[MAX_LINE];

/* Function */
void *thread_recv(void *arg);
void *thread_send(void *arg);
void *thread_command(void *arg);

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

	while (1 && is_prog_running )
	{

		// 4. accept: wait until we get a connection on that port
		int fd = accept(sock, (struct sockaddr *)&client_addr,(socklen_t *)&sin_size);
		printf("STATE: Server got a connection from (%s, %d)\n", inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));

		is_sock_running = 1;
		
		// 5. 6. receive and send information via this socket
		pthread_create(&socketthread_recv, NULL, thread_recv, (void *)&fd);
		pthread_create(&socketthread_send, NULL, thread_send, (void *)&fd);
	}

	close(sock);
}

void *thread_recv(void *arg)
{
	int sock = *((int *) arg);
	printf("STATE: Start receiving from socket: %d\n", sock);

	char buf[MAX_BUFF];

	while (recv(sock, buf, sizeof(buf), 0) > 0 && is_sock_running)
	{
		printf("%s\n", buf);
		if (buf[0] == '%')
		{
			if (buf[1] == 'C' && buf[2] == 'L' && buf[3] == 'S')
			{
				printf("COMMAND: Close the socket connection.\n");
				is_sock_running = 0;				
			}
		}
		if (buf[0] == '$')
		{
			write(serial, buf, strlen(buf));
		}
		memset(buf, 0, MAX_BUFF * sizeof(char));
	}

	// 7. close: close the socket connection
    printf("STATE: Server closed connection\n");
    close(sock);
}

void *thread_send(void *arg)
{
	int sock = *((int *) arg);
	memset(str, 0, MAX_LINE * sizeof(char));
	printf("STATE: Start sending to socket: %d\n", sock);

	while (is_sock_running)
	{
		while (str[strlen(str)-1] == '\n')
		{
			// printf("send:%s", str);
			send(sock, str, strlen(str), 0);
			memset(str, 0, MAX_LINE * sizeof(char));
		}
	}
	


}

void *thread_command(void *arg)
{
	printf("STATE: Start command thread.\n");
	char command[MAX_LINE];
	while (fgets(command, sizeof(command), stdin) > 0)
	{
		if (command[0] == '$')
		{
			write(serial, command, strlen(command));
		}
		else if ((!strcmp(command, "QUIT\n") || (!strcmp(command, "quit\n"))))
		{
			printf("STATE: QUIT.\n");
			is_prog_running = 0;
			sleep(1);
			exit(0);
		}
		memset(command, 0, MAX_LINE * sizeof(char));
	}

}

main(int argc, char *argv[])
{
	is_prog_running = 1;

	/* connect the device IO */
	serial = open("/dev/cu.usbmodem1421", O_RDWR);

	struct termios options;
	tcgetattr(serial, &options);
	cfsetispeed(&options, 9600);
	cfsetospeed(&options, 9600);
	tcsetattr(serial, TCSANOW, &options);

	int port_number;
	if(argc == 2)
	{
		port_number = atoi(argv[1]);
	}
	else
	{
		port_number = 0;
	}

	/* create thread & mutex */
	pthread_mutex_init(&lock, NULL) != 0;
	pthread_create(&socketthread_recv, NULL, start_server, (void*)&port_number);
	pthread_create(&command_thread, NULL, thread_command, NULL);

	// while(1);
	printf("STATE: Start reading from arduino.\n");
	while(1)
	{
		char buf[30];
		memset(buf, 0, 30 * sizeof(char));
		int bytes_read = read(serial, buf, 40);

		if(bytes_read > 0)
		{
			strcat (str, buf);

			if (strlen(str) > MAX_LINE/5) 
			{	
				// printf("%s", str);
				memset(str, 0, MAX_LINE * sizeof(char));
			}
		}
	}
}

