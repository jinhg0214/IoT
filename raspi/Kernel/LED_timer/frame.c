#include <linux/module.h>
#include <linux/fs.h>
#include <asm/io.h>
#include <linux/module.h> // for timer
#include <linux/timer.h> // for timer

#define NOD_MAJOR 100
#define NOD_NAME "frame"

MODULE_LICENSE("GPL");

static volatile uint32_t *BASE;

/////////////////// LED ///////////////////////

static volatile uint32_t *GPFSEL1;
static volatile uint32_t *GPSET0;
static volatile uint32_t *GPCLR0;

static void led_init(void){
	BASE = (uint32_t*)ioremap(0xFE200000, 256);
	GPFSEL1 = BASE + (0x04/4);
	GPSET0 	= BASE + (0x1C/4);
	GPCLR0	= BASE + (0x28/4);

	// GPIO 18 as output mode(xxxx_x001_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx)
	*GPFSEL1 &= ~(0x7 << 24);
	*GPFSEL1 |= (1 << 24);
}

static void led_set(void){
	//printk( KERN_INFO "LED ON...\n");
	*GPSET0 = (1 << 18);
}

static void led_clr(void){
	//printk( KERN_INFO "LED OFF...\n");
	*GPCLR0 = (1 << 18);
}
/////////////////// timer ///////////////////////
static struct timer_list timer;
static int interval = 1000; // default 1 sec
static int led_state = 0;

static void timer_func(struct timer_list *t){
	printk( KERN_INFO "LED INTERVAL: %d msec\n", interval);

	if(led_state == 0){
		led_set();
		led_state = 1;
	}	
	else{
		led_clr();
		led_state = 0;
	}

	// 현재(get_jiffies_674())로 부터 + (interval/10)msec 뒤에 만료되는 타이머를 다시 호출한다
	mod_timer(t, get_jiffies_64() + (interval/10)); 
	// kernel over 2.6 : HZ 1000, kernel under 2.4 : HZ 100 
	// Hz를 100으로 맞추기 위해 10으로 나눈다
}

static void timer_init(void){
	timer.expires = get_jiffies_64() + (1 * HZ); // 100Hz 뒤에 만료
	timer_setup(&timer, timer_func, 0); // 타이머 구조체에 timer_func 함수를 연결
	add_timer(&timer); // 타이머 시작
}

//////////////////////////////////////////////////
static void my_init(void){
	timer_init();
	led_init();
	return;
}
//////////////////////////////////////////////////
static int frame_open(struct inode *inode, struct file *filp)
{
    printk( KERN_INFO "[open()] welcome\n");
    return 0;
}

static int frame_release(struct inode *inode, struct file *flip)
{
    printk( KERN_INFO "[close()] release\n");
    return 0;
}

static long frame_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	// 200msec ~ 2000msec 사이
    switch (cmd) {
        case _IO(0, 3): // U
            if(interval < 2000){
		interval = interval + 20;
	    }
	    break;

	case _IO(0, 4): // D
	    if(interval > 3){
		interval = interval - 20;	   
	    }
	    break;

	case _IO(0, 5): // MIN
	    interval = 200; // MIN 0.20sec
	    break;

	case _IO(0, 6): // MAX
	    interval = 2000; // MAX 2sec
	    break;
    }

    return 0;
}

static struct file_operations fops = { //connection
    .open = frame_open,
    .release = frame_release,
    .unlocked_ioctl = frame_ioctl,
};

static int frame_init(void) //insmod
{
    if (register_chrdev(NOD_MAJOR, NOD_NAME, &fops) < 0) { //device file ----- module
        printk("INIT FAIL");
    }

    my_init();

    printk( KERN_INFO "[INIT] : HI\n");
    return 0;
}

static void frame_exit(void) //rmmod
{
    del_timer_sync(&timer); // timer delete
    unregister_chrdev(NOD_MAJOR, NOD_NAME);
    printk( KERN_INFO "[EXIT] : BYE\n");
}

module_init(frame_init);
module_exit(frame_exit);
