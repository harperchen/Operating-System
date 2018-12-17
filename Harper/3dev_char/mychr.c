#include <linux/fs.h>
#include <linux/init.h>
#include <asm/uaccess.h>
#include <linux/module.h>
#include <linux/syscalls.h>
#include <linux/semaphore.h>
MODULE_LICENSE("GPL");

#define MAJOR_NUM 244

static int count = 0;
static struct file *tmp_file;
static struct semaphore sem;
static DEFINE_SPINLOCK(spin);

static int chr_open(struct inode *inode, struct file *filp){
	spin_lock(&spin);
	printk("open filp is %s", filp->f_path.dentry->d_iname);
	if(count){
		spin_unlock(&spin);
		return -EBUSY;
	}
	tmp_file->f_pos = 0;
	count++;
	printk("Success to open file!\n");
	spin_unlock(&spin);
	return 0;
}

static int chr_release(struct inode *inode, struct file *filp){
	printk("release filp is %s", filp->f_path.dentry->d_iname);
	tmp_file->f_pos = 0;
	count--;
	printk("Success to close file!\n");
	return 0;
}

static ssize_t chr_read(struct file *filp, char *buf, size_t count, loff_t *f_pos){
	char *str;
	ssize_t size;
	mm_segment_t fs;
	fs = get_fs();
	set_fs(KERNEL_DS);
	if(down_interruptible(&sem)){
		return -ERESTARTSYS;
	}
	printk("read filp is %s f_pos is %lld", filp->f_path.dentry->d_iname, *f_pos);
	printk("tmp file pos is %lld", tmp_file->f_pos);
	str = (char *)kmalloc(count + 1, GFP_KERNEL);
	memset(str, 0, count + 1);
	size = vfs_read(tmp_file, str, count, &tmp_file->f_pos);
	*f_pos += size;
	copy_to_user(buf, str, count);
	printk("Content of buf is %s\n", str);
	printk("Success to read content of file!\n");
	printk("Kernel read size is %ld\n", size);
	printk("tmp file pos is %lld", tmp_file->f_pos);
	kfree(str);
	up(&sem);
	set_fs(fs);
	return size;
}

static ssize_t chr_write(struct file *filp, const char *buf, size_t count, loff_t *f_pos){
	char *str;
	ssize_t size;
	mm_segment_t fs;
	fs = get_fs();
	set_fs(KERNEL_DS);
	if(down_interruptible(&sem)){
		return -ERESTARTSYS;
	}
	printk("write filp is %s f_pos is %lld", filp->f_path.dentry->d_iname, *f_pos);
	printk("tmp file pos is %lld", tmp_file->f_pos);
	str = (char *)kmalloc(count + 1, GFP_KERNEL);
	memset(str, 0, count + 1);
	copy_from_user(str, buf, count);
	printk("Content of buf is %s", str);
	size = vfs_write(tmp_file, str, count, &tmp_file->f_pos);
	*f_pos += size;
	printk("Success to write buf!\n");
	printk("Kernel write size is %ld\n", size);
	printk("tmp file pos is %lld", tmp_file->f_pos);
	kfree(str);
	up(&sem);
	set_fs(fs);
	return size;
}

static loff_t chr_llseek(struct file *filp, loff_t off, int whence){
	vfs_llseek(tmp_file, off, whence);
	filp->f_pos = tmp_file->f_pos;
	return tmp_file->f_pos;
}


struct file_operations chr_fops = {
	.open  = chr_open,
	.release = chr_release,
	.read  = chr_read,
	.write = chr_write,
	.llseek = chr_llseek,
};


static int chr_init(void){
	int ret;
	printk("I will init my char device module!\n");
	ret = register_chrdev(MAJOR_NUM, "mychr", &chr_fops);
	if(ret){
		printk("Fail to register char device!\n");
		return ret;
	}
	else{
		printk("Success to register char device!\n");
		sema_init(&sem, 1);
	}
	tmp_file = filp_open("/tmp/mychr", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if(IS_ERR(tmp_file)){
		printk("Fail to create file!\n");
		return -1;
	}
	else{
		printk("Success to create file!\n");
	}
	return ret;
}

static void chr_exit(void){
	printk("I will clean up my char device module!\n");
	filp_close(tmp_file, NULL);
	unregister_chrdev(MAJOR_NUM, "mychr");
}

module_init(chr_init);
module_exit(chr_exit);
