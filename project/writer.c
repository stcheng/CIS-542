#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

int main(){
    
    int fd = open("/dev/cu.usbmodem1421", O_RDWR);
    printf("?\n");
    if(fd == -1)
      exit(1);
    printf("?\n");

    struct termios options;
    tcgetattr(fd, &options);
    cfsetispeed(&options, 9600);
    cfsetospeed(&options, 9600);
    tcsetattr(fd, TCSANOW, &options);

    int size = 100;
    char buf[size];
    int bytes_read;
    
    printf("?\n");
    memset(buf, 0, size*sizeof(char));

    while(1){    
      scanf("%s", buf);
      
      if(buf > 0)
        write(fd, buf, size);
      
      memset(buf, 0, size*sizeof(char));

      }

 return 0;     
}