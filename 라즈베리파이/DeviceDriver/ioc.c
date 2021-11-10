#include <linux/module.h>
#include <linux/fs.h>
#include <asm/io.h> // ioremap

#define NOD_MAJOR 100 // 주 번호
#define NOD_NAME "ioc"  // 디바이스노드 이름

MODULE_LICENSE("GPL");  // 라이센스

static volatile uint32_t *BASE;
// LED
static volatile uint32_t *GPFSEL1;
static volatile uint32_t *GPSET0;
static volatile uint32_t *GPCLR0;
// BTN
static volatile uint32_t *GPFSEL2;
static volatile uint32_t *GPLEV0;

/////////////////////////////////////////////////////////////////////////

void init(void){ // LED와 버튼 초기화
	BASE = (uint32_t*)ioremap(0xFE200000, 256);
	// led init(GPIO 18)
	GPFSEL1 = BASE + (0x04/4);
	GPSET0 	= BASE + (0x1C/4);
	GPCLR0	= BASE + (0x28/4);
	*GPFSEL1 &= ~(0x7 << 24); // 001 : GPIO18 as OUTPUT MODE
	*GPFSEL1 |= (1 << 24);
	
	// btn init(
	GPFSEL2 = BASE + (0x08/4);
	*GPFSEL2 &= ~(0x7 << 3); // 000 : GPIO21 as INPUT MODE (xxxxx_xxxx _xxxx_xxxx _xxxx_xxxx _xx00_0xxx로 설정됨.)
	
	GPLEV0 	 = BASE + (0x34/4); 
	/* GPLEV0은 GPIO0 ~ GPIO31의 실제 값이 저장되어있다. 
	 버튼을 풀업으로 구성했으므로, 누르지 않았을 때는 1, 눌렀을 때 0이 리턴된다.

	*/
}

// GPIO 18 SET
void led_set(void){
	printk( KERN_INFO "LED ON...\n");
	*GPSET0	= (1 << 18); 
}

// GPIO 18 CLR
void led_clr(void){
	printk( KERN_INFO "LED OFF...\n");
	*GPCLR0 = (1 << 18);
}

// Read GPIO 21 
static int my_btn_state(void){
	// printk( KERN_INFO "value = %d\n", (int)(*GPLEV0)); // GPIO0~31 까지 모든 값 출력됨. 
	
	int ret = (((*GPLEV0) >> 21) & 0x1); // 이중에서 원하는 21번째 핀의 값만 추출 후 리턴한다
	return ret;
}


//////////////////////////////////////////////////////////////////////////

static int ioc_open(struct inode* inode, struct file* filp){
	printk( KERN_INFO "ioc :: open()\n");
	init();	 // 현재는 init에서 초기화하나 open에서 초기화하나 한번만 호출한다. 별 차이 없으므로 아무데나 넣어도 됨  
	return 0;
}

static int ioc_release(struct inode* inode, struct file* filp){
	printk( KERN_INFO "ioc :: release()\n");
	return 0;	
}

static long ioc_ioctl(struct file* filp, unsigned int cmd, unsigned int long arg){
	int btn_ret = 0;
	printk( KERN_ALERT "ioc :: ioctl() :: CMD %d\n", cmd);
	switch(cmd){
		case _IO(0, 3):
			led_set();
			break;
		
		case _IO(0, 4):
			led_clr();
			break;

		case _IO(0, 5):
			btn_ret = my_btn_state();
			printk( KERN_INFO "BUTTON STATE : %d\n", btn_ret);
			break;
	}
	return 0;
}

static struct file_operations fops ={
	.open 		= ioc_open,
	.release 	= ioc_release,
	.unlocked_ioctl	= ioc_ioctl,
};

// insmod
static int ioc_init(void){
	if(register_chrdev(NOD_MAJOR, NOD_NAME, &fops) < 0){
		printk("ioc :: init() :: INIT FAILED\n");
		return 1;
	}
	printk( KERN_INFO "ioc :: init() :: Hi\n");
	return 0;
}

// rmmod
static void ioc_exit(void){
	unregister_chrdev(NOD_MAJOR, NOD_NAME);
	printk( KERN_INFO "ioc :: exit() :: Bye\n");
}

module_init(ioc_init);
module_exit(ioc_exit);