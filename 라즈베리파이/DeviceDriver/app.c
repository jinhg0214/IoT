#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>

int main(){

	// open device node
	int fd = open("/dev/ioc", O_RDWR);
	if(fd < 0){
		printf("FILE OPEN ERROR\n");
		goto Exit;
	}
	
	printf("====Hi====\n");

	char buf[100];
	while(1){

		printf("SSAFY >> ");
		gets(buf);

		if( !strcmp(buf, "exit") || !strcmp(buf, "EXIT") ) break;
		// LED ON
		else if( !strcmp(buf, "ON")){
			ioctl(fd, _IO(0, 3), 0);
		}
		// LED OFF
		else if( !strcmp(buf, "OFF")){
			ioctl(fd, _IO(0, 4), 0);
		}
		// BLINK
		else if( !strcmp(buf, "BLINK")){
			for(int i=0; i<5 ; i++){
				ioctl(fd, _IO(0, 3), 0);
				usleep(500 * 1000);
				ioctl(fd, _IO(0, 4), 0);
				usleep(500 * 1000);
			}
		}
		//
		else if( !strcmp(buf, "BTN") ){
			ioctl(fd, _IO(0, 5), 0); 
		}
	}

	printf("====Bye===\n");

Exit:
	close(fd);
	return 0;
}
