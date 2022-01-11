#include <stdio.h>
#include <wiringPi.h>
#include <termio.h>

#define LED1 14 // GPIO 14
#define LED2 15 // GPIO 15
#define LED3 23 // GPIO 23
#define LED4 24 // GPIO 24

int getch(void) // 키보드 입력을 char 단위로 받는 함수.
{

	int ch;
	struct termios buf;
	struct termios save;

	tcgetattr(0, &save);
	buf = save;
	buf.c_lflag &= ~(ICANON|ECHO);
	buf.c_cc[VMIN] = 1;
	buf.c_cc[VTIME] = 0;
	tcsetattr(0, TCSAFLUSH, &buf);
	ch = getchar();
	tcsetattr(0, TCSAFLUSH, &save);
	return ch;
}

int main(void){

	int ch;
	if(wiringPiSetupGpio() == -1) 
		return -1;

	pinMode(LED1, OUTPUT);
	pinMode(LED2, OUTPUT);
	pinMode(LED3, OUTPUT);
	pinMode(LED4, OUTPUT);

	while(1){

		ch = getch();
	
		if(ch == 'w' || ch == 'W'){
 			digitalWrite(LED1, 1);
 			digitalWrite(LED2, 0);
 			digitalWrite(LED3, 0);
 			digitalWrite(LED4, 0);
			printf("Foward\n");
		} else if(ch == 's' || ch == 'S'){
 			digitalWrite(LED1, 0);
 			digitalWrite(LED2, 1);
 			digitalWrite(LED3, 0);
 			digitalWrite(LED4, 0);
			printf("Backward\n");
		} else if(ch == 'a' || ch == 'A' ){
 			digitalWrite(LED1, 0);
 			digitalWrite(LED2, 0);
 			digitalWrite(LED3, 1);
 			digitalWrite(LED4, 0);
			printf("Left\n");
		} else if(ch == 'd' || ch == 'D' ){
 			digitalWrite(LED1, 0);
 			digitalWrite(LED2, 0);
 			digitalWrite(LED3, 0);
 			digitalWrite(LED4, 1);
			printf("Right\n");
		} else if(ch == 'o' || ch == 'O' ){
 			digitalWrite(LED1, 1);
 			digitalWrite(LED2, 1);
 			digitalWrite(LED3, 1);
 			digitalWrite(LED4, 1);
			printf("All on\n");
		} else if(ch == 'n' || ch == 'N' ){
 			digitalWrite(LED1, 0);
 			digitalWrite(LED2, 0);
 			digitalWrite(LED3, 0);
 			digitalWrite(LED4, 0);
			printf("All off\n");
		}
	}
	return 0;

}
