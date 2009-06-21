/* ------------------------------------------------------------------------
 * konohadev - char device for konoha
 * Masahiro Ide
 *
 * ------------------------------------------------------------------------ */


#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/init.h>
#include <asm/uaccess.h>
//#include <linux/semaphore.h>
#include "../include/konoha.h"


MODULE_LICENSE("GPL");
MODULE_AUTHOR("masahiro ide");
#if 1
// TODO_LKM
// cant find these functions
// I think it seam that "float" or "double" is still active.
// so, remove these type that can remove these functions.
//


/*
float  __floatsisf (int i) { return i; } //need
double __floatsidf (int i) { return i; } //need

signed   int __fixsfsi    (float  d) { return d; } //need
signed   int __fixdfsi (float  d) { return d; } //need

unsigned int __fixunsdfsi (float  d) { return d; } //need
double __adddf3(double a, double b) { return a+b; }//need
double __addsf3(float a, float b) { return a+b; } //ne
double __subdf3(double a, double b) { return a-b; } //need
double __mulsf3(double a, double b) { return a*b; } //need
double __muldf3(double a, double b) { return a*b; }//need
double __divdf3(double a, double b) { return a/b; } //need
double __gedf2(double a,double b) { return (a >= b) -1 ; } //need
float __nedf2(float a,float b) { return (a != b); }
float __nesf2(float a,float b) { return (a != b); }
float  __gtsf2(float  a,float  b) { return (a > b); }
double __gtdf2(double a,double b) { return (a > b); }
float __eqsf2(float a,float b) { return !(a == b); }
float __eqdf2(float a,float b) { return !(a == b); }
double __extendsfdf2(float a) {return a;}
*/

#endif

enum {
    MAXCOPYBUF = 128
};

struct konohadev_t {
    dev_t id;
  //    struct semaphore sem;
    struct cdev cdev;
    konoha_t  konoha;
    char* buffer;
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

static int knh_dev_write(struct file *file,const char __user *buf,
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

static int knh_dev_read (struct file* filp, char __user *user_buf,
        size_t count, loff_t *offset)
{
    struct konohadev_t *dev = filp->private_data;
    char buf[MAXCOPYBUF];
    int len;

    if(*offset > 0) return 0;

    //    if(down_interruptible(&dev->sem)){
    //        return -ERESTARTSYS;
    //    }

    len = snprintf(buf,MAXCOPYBUF,"%s\n",dev->buffer);

    if(copy_to_user(user_buf,buf,len)){
      //        up(&dev->sem);
        printk(KERN_ALERT "%s: copy_to_user failed\n",msg);
        return -EFAULT;
    }

    //    up(&dev->sem);
    *offset += len;

    return len;
}

static int knh_dev_write(struct file *filp,const char __user *user_buf,
        size_t count,loff_t *offset) {
    char buf[MAXCOPYBUF];
    struct konohadev_t *dev = filp->private_data;
    long len;

    //    if(down_interruptible(&dev->sem)){
    //        return -ERESTARTSYS;
    //    }

    len = copy_from_user(buf,user_buf,count);
    buf[count-1] = '\0';
    //printk("write:line=%d,%ld %ld [%s]\n", __LINE__,len, count,buf);
    //printk(KERN_DEBUG "[%s]\n",konoha_eval(dev->konoha, "int fib(int n) { if (n==3) { return 1;}}"));
    //printk(KERN_DEBUG "[%s]\n",konoha_eval(dev->konoha, "fib(10);"));
    snprintf(dev->buffer,MAXCOPYBUF,"%s",konoha_eval(dev->konoha,buf));
    printk(KERN_DEBUG "%s\n",dev->buffer);
    //    up(&dev->sem);
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
    dev->buffer = kmalloc(sizeof(char)*MAXCOPYBUF,GFP_KERNEL);
    memset(dev->buffer,0,sizeof(char)*MAXCOPYBUF);
    //    init_MUTEX(&dev->sem);

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
    cdev_del(&konohadev_p->cdev);
    unregister_chrdev_region(konohadev_p->id,1);
    kfree(konohadev_p);
}

module_init(konoha_init);
module_exit(konoha_exit);

