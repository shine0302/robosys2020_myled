#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h> 
#include <linux/uaccess.h>
#include <linux/io.h>
#include <linux/delay.h>

MODULE_AUTHOR("Shinya Ishihara and Ryuichi Ueda");
MODULE_DESCRIPTION("driver for LED control");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.0.1");                       //MODULE

static dev_t dev;
static struct cdev cdv;
static struct class *cls = NULL;
static volatile u32 *gpio_base = NULL;  //グローバル変数
int i=0;

static ssize_t led_write(struct file* filp, const char* buf, size_t count, loff_t* pos)
{
	char c;   //読み込んだ字を入れる変数
 	if(copy_from_user(&c,buf,sizeof(char)))
  		return -EFAULT;

	if (c == '0') //全消灯
		while(1){
		gpio_base[10] = 1 << 24;
		gpio_base[10] = 1 << 25;
		gpio_base[10] = 1 << 26;
		gpio_base[10] = 1 << 27;	
		break;	
	       	}

	else if (c == '1') //上
		while(1){
		gpio_base[10] = 1<< 24;
		gpio_base[7] = 1 << 25;
		gpio_base[7] = 1 << 26;
		gpio_base[7] = 1 << 27;
		break;
		}

	else if(c == '2') //右
		while(1){
		gpio_base[10] =1<< 25;
		gpio_base[7] = 1<< 26;
		gpio_base[7] = 1<< 27;
		gpio_base[7] = 1<< 24;
		break;
		}

	else if(c == '3')//下
		while(1){
		gpio_base[10] = 1<< 26;
		gpio_base[7] = 1<< 27;
		gpio_base[7] = 1<< 24;
		gpio_base[7] = 1<< 25;
		break;
		}

	else if(c == '4')//左
		while(1){
		gpio_base[10] = 1<< 27;
		gpio_base[7] = 1<< 24;
		gpio_base[7] = 1<< 25;
		gpio_base[7] = 1<< 26;
		break;
		}

    	else if(c == '5')
		for(i=1; i<=20; i++){
		gpio_base[7]  =1<<24;
		gpio_base[10] =1<<25;
		gpio_base[10] =1<<26;
		gpio_base[10] =1<<27;
		mdelay(200);
		gpio_base[7] = 1<<25;
		gpio_base[10] =1<<26;
		gpio_base[10] =1<<27;
		gpio_base[10] =1<<24;
		mdelay(200);
		gpio_base[7] =1<<26;
		gpio_base[10] =1<<27;
		gpio_base[10] =1<<24;
		gpio_base[10] =1<<25;
		mdelay(200);
		gpio_base[7] =1<<27;
		gpio_base[10] =1<<24;
		gpio_base[10] =1<<25;
		gpio_base[10] =1<<26;
		mdelay(200);
		gpio_base[10] =1<<27;
		mdelay(0);
		}
 	return 1; 

}


static struct file_operations led_fops = {
	        .owner = THIS_MODULE,
		.write = led_write,
};


static int __init init_mod(void) //カーネルモジュールの初期化
{
 	int retval;
	    retval =  alloc_chrdev_region(&dev, 0, 1, "myled");
	    if(retval < 0){
	        printk(KERN_ERR "alloc_chrdev_region failed.\n");
			    return retval;
}

	printk(KERN_INFO "%s is loaded. major:%d\n",__FILE__,MAJOR(dev));	  
	cdev_init(&cdv, &led_fops);
	retval = cdev_add(&cdv, dev, 1);
	if(retval < 0){
			printk(KERN_ERR "cdev_add failed. major:%d, minor:%d",MAJOR(dev),MINOR(dev));
			return retval;

	}

	cls = class_create(THIS_MODULE,"myled");   
	if(IS_ERR(cls)){
		printk(KERN_ERR "class_create failed.");
		return PTR_ERR(cls);
									          
	}

	device_create(cls, NULL, dev, NULL, "myled%d",MINOR(dev));

	gpio_base = ioremap_nocache(0x3f200000, 0xA0); //Pi4の場合は0xfe200000

	const u32 led_a = 24;
	const u32 index_a = led_a/10;//GPFSE
	const u32 shift_a = (led_a%10)*3;//15bit
	const u32 mask_a = ~(0x7 << shift_a);//11111111111111000111111111111111
	gpio_base[index_a] = (gpio_base[index_a] & mask_a) | (0x1 << shift_a);//001: output flag
						    //111111111111110011111111111111
	const u32 led_b =25;
	const u32 index_b =led_b/10;
	const u32 shift_b = (led_b%10)*3;
	const u32 mask_b = ~(0x7 << shift_b);
	gpio_base[index_b] = (gpio_base[index_b] & mask_b) | (0x1 << shift_b);

	const u32 led_c =26;
	const u32 index_c =led_c/10;
	const u32 shift_c = (led_c%10)*3;
	const u32 mask_c = ~(0x7 << shift_c);
	gpio_base[index_c] = (gpio_base[index_c] & mask_c) | (0x1 << shift_c);                                  

	const u32 led_d =27;
	const u32 index_d =led_d/10;
	const u32 shift_d = (led_d%10)*3;
	const u32 mask_d = ~(0x7 << shift_d); 	
	gpio_base[index_d] = (gpio_base[index_d] & mask_d) | (0x1 << shift_d);
	return 0;
}

static void __exit cleanup_mod(void) //後始末
{
	cdev_del(&cdv);
	device_destroy(cls, dev);
	class_destroy(cls);  //追加
	unregister_chrdev_region(dev, 1);	
	printk(KERN_INFO "%s is unloaded. major:%d\n",__FILE__,MAJOR(dev));
}


module_init(init_mod);     // マクロで関数を登録
module_exit(cleanup_mod);  // 同上
