#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <string.h>

int main()
{
        int fd = open("/dev/frame", O_RDWR);
        if (fd < 0) {
                printf("ERROR OPEN\n");
                goto Exit;
        }

        printf("====HI===\n");
	
	char buf[10];
	while(1){
		printf("SSAFY >> ");
		gets(buf);
		if( !strcmp(buf, "U") ){
			ioctl(fd, _IO(0, 3), 0);
		}
		else if( !strcmp(buf, "D") ){
			ioctl(fd, _IO(0, 4), 0);
		}
		else if( !strcmp(buf, "MIN") ){
			ioctl(fd, _IO(0, 5), 0);
		}
		else if( !strcmp(buf, "MAX") ){
			ioctl(fd, _IO(0, 6), 0);
		}
		else if( !strcmp(buf, "exit") || !strcmp(buf, "EXIT") ){
			break;
		}
	}

        printf("===BYE===\n");

Exit:
        close(fd);
        return 0;
}
