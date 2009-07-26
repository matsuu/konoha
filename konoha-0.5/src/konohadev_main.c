/* ------------------------------------------------------------------------
 * konohadev - char device for konoha
 * Masahiro Ide
 *
 * ------------------------------------------------------------------------ */

#ifdef KONOHA_ON_LKM

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/init.h>
#include <asm/uaccess.h>
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,25))
#include <linux/semaphore.h>
#endif

#include <konoha.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("masahiro ide");

enum {
    MAXCOPYBUF = 128
};

struct konohadev_t {
    dev_t id;
    struct cdev cdev;
    konoha_t  konoha;
    char* buffer;
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,25))
    struct semaphore sem;
#endif
};

static const char *msg = "konohadev";
static struct konohadev_t *konohadev_p;

static int knh_dev_open (struct inode *inode , struct file *filp);
static ssize_t knh_dev_read(struct file *filp, char __user *user_buf,
        size_t count, loff_t *offset);
/*
   static int knh_dev_ioctl (struct inode *inode, struct file *filp,
   unsigned int cmd, unsigned long arg);
 */

static ssize_t knh_dev_write(struct file *file,const char __user *buf,
        size_t count,loff_t *offp) ;

static struct file_operations knh_fops = {
    .owner = THIS_MODULE,
    .open  = knh_dev_open,
    .read  = knh_dev_read,
    .write = knh_dev_write,
    //.ioctl = knh_dev_ioctl,
};

static int knh_dev_open (struct inode* inode, struct file *filp)
{
    filp->private_data = container_of(inode->i_cdev,
            struct konohadev_t,cdev);
    return 0;
}

static ssize_t knh_dev_read (struct file* filp, char __user *user_buf,
        size_t count, loff_t *offset)
{
    struct konohadev_t *dev = filp->private_data;
    char buf[MAXCOPYBUF];
    int len;

    if(*offset > 0) return 0;

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,25))
    if(down_interruptible(&dev->sem)){
        return -ERESTARTSYS;
    }
#endif

    len = snprintf(buf,MAXCOPYBUF,"%s\n",dev->buffer);

    if(copy_to_user(user_buf,buf,len)){
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,25))
        up(&dev->sem);
#endif
        printk(KERN_ALERT "%s: copy_to_user failed\n",msg);
        return -EFAULT;
    }

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,25))
    up(&dev->sem);
#endif
    *offset += len;

    return len;
}

static ssize_t knh_dev_write(struct file *filp,const char __user *user_buf,
        size_t count,loff_t *offset) {
    char buf[MAXCOPYBUF];
    char* konoha_ret = NULL;
    struct konohadev_t *dev = filp->private_data;
    long len;

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,25))
    if(down_interruptible(&dev->sem)){
        return -ERESTARTSYS;
    }
#endif

    len = copy_from_user(buf,user_buf,count);
    memset(dev->buffer,0,sizeof(char)*MAXCOPYBUF);
    buf[count] = '\0';
    printk("[%s][user_buf=%s]\n", __FUNCTION__,buf);
    //printk(KERN_DEBUG "[%s]\n",konoha_eval(dev->konoha, "int fib(int n) { if (n==3) { return 1;}}"));
    //printk(KERN_DEBUG "[%s]\n",konoha_eval(dev->konoha, "fib(10);"));
    konoha_evalScript(dev->konoha,buf);
    konoha_ret = konoha_getSTDOUTBuffer(dev->konoha);

    snprintf(dev->buffer,MAXCOPYBUF,"%s",konoha_ret);
    printk(KERN_DEBUG "[%s][dev->buffer=%s]\n",__FUNCTION__ ,dev->buffer);

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,25))
    up(&dev->sem);
#endif
    *offset += count - len;
    return count -len;
    //*offset = 0;
    //return 1;
}

static void knh_dev_setup(struct konohadev_t *dev){
    int err = alloc_chrdev_region(&dev->id, 0, 1, msg);
    if(err){
        printk(KERN_ALERT "%s: alloc_chrdev_region() failed (%d)\n",
                msg,err);
        return;
    }
    cdev_init(&dev->cdev,&knh_fops);
    dev->cdev.owner = THIS_MODULE;
    dev->konoha = konoha_open(128);
    knh_setOutputStreamBuffer(dev->konoha, 128,128);
    dev->buffer = kmalloc(sizeof(char)*MAXCOPYBUF,GFP_KERNEL);
    memset(dev->buffer,0,sizeof(char)*MAXCOPYBUF);
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,25))
    init_MUTEX(&dev->sem);
#endif

    err = cdev_add(&dev->cdev, dev->id, 1);
    if(err){
        printk(KERN_ALERT "%s:cdev_add() failed(%d)\n",msg,err);
        return;
    }
}

// Start/Init function
static int __init konoha_init(void) {
    konohadev_p = kmalloc(sizeof(struct konohadev_t),GFP_KERNEL);
    if(!konohadev_p){
        printk(KERN_ALERT "%s:kmalloc() failed\n",msg);
        return -ENOMEM;
    }
    memset(konohadev_p,0,sizeof(struct konohadev_t));
    knh_dev_setup(konohadev_p);

    return 0;
}

// End/Cleanup function
static void __exit konoha_exit(void) {
    printk(KERN_ALERT "Goodbye!\n");
    konoha_close(konohadev_p->konoha);
    kfree(konohadev_p->buffer);
    cdev_del(&konohadev_p->cdev);
    unregister_chrdev_region(konohadev_p->id,1);
    kfree(konohadev_p);
}

module_init(konoha_init);
module_exit(konoha_exit);

#endif /*KONOHA_ON_LKM*/

