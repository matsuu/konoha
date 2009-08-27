/* ------------------------------------------------------------------------
 * konohadev - char device for konoha
 * Masahiro Ide
 *
 * ------------------------------------------------------------------------ */

#ifdef KONOHA_ON_LKM

#include <konoha.h>
#include <konoha/gen/konoha_knhapi_.h>


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
#ifdef KNH_ENABLE_SEMAPHORE
    struct semaphore sem;
#endif
};

static const char *msg = "konohadev";
struct konohadev_t *konohadev_p;

static int knh_dev_open (struct inode *inode , struct file *filp);
static ssize_t knh_dev_read(struct file *filp, char __user *user_buf,
        size_t count, loff_t *offset);
// static int knh_dev_ioctl (struct inode *inode, struct file *filp,
//   unsigned int cmd, unsigned long arg);
static ssize_t knh_dev_write(struct file *file,const char __user *buf,
        size_t count,loff_t *offp) ;

static struct file_operations knh_fops = {
    .owner = THIS_MODULE,
    .open  = knh_dev_open,
    .read  = knh_dev_read,
    .write = knh_dev_write,
    //.ioctl = knh_dev_ioctl,
};

/*
konoha_t *konoha_getCurrntKnh(const void *p)
{
    return &konohadev_p->konoha;
}
*/

static inline void *konoha_malloc(const size_t size)
{
    // kzalloc : see linux/slab.h
    void *p = kzalloc(size, GFP_KERNEL);
    return p;
}

static inline void konoha_free(const void *p)
{
    if (p)
        kfree(p);
}

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

#ifdef KNH_ENABLE_SEMAPHORE
    if(down_interruptible(&dev->sem)){
        return -ERESTARTSYS;
    }
#endif

    len = snprintf(buf,sizeof(buf),"%s\n",dev->buffer);

    if(copy_to_user(user_buf,buf,len)){
#ifdef KNH_ENABLE_SEMAPHORE
        up(&dev->sem);
#endif
        printk(KERN_ALERT "%s: copy_to_user failed\n",msg);
        return -EFAULT;
    }

#ifdef KNH_ENABLE_SEMAPHORE
    up(&dev->sem);
#endif
    *offset += len;

    return len;
}

static ssize_t knh_dev_write(struct file *filp,const char __user *user_buf,
        size_t count,loff_t *offset) {
    char buf[MAXCOPYBUF];
    char*  ret = NULL;
    struct konohadev_t *dev = filp->private_data;
    konoha_t konoha = dev->konoha;
    long len;

#ifdef KNH_ENABLE_SEMAPHORE
    if(down_interruptible(&dev->sem)){
        return -ERESTARTSYS;
    }
#endif

    len = copy_from_user(buf,user_buf,count);
    buf[count] = '\0';
    memset(dev->buffer,0,sizeof(dev->buffer));

    printk("[%s][user_buf=%s]\n", __FUNCTION__,buf);
    konoha_evalScript(konoha,buf);
    ret = konoha_getStdOutBufferText(konoha);
    snprintf(dev->buffer,sizeof(dev->buffer),"%s",ret);
    printk(KERN_DEBUG "[%s][dev->buffer=%s]\n",__FUNCTION__ ,dev->buffer);
    printk(KERN_DEBUG "[%s][STDOUT=%s]\n",__FUNCTION__ ,ret);
    printk(KERN_DEBUG "[%s][STDERR=%s]\n",__FUNCTION__ ,konoha_getStdErrBufferText(konoha));

#ifdef KNH_ENABLE_SEMAPHORE
    up(&dev->sem);
#endif
    *offset += count - len;
    return count -len;
}

static void knh_dev_setup(struct konohadev_t *dev){
    int err = alloc_chrdev_region(&dev->id, 0, 1, msg);
    size_t size = MAXCOPYBUF;
    if(err){
        printk(KERN_ALERT "%s: alloc_chrdev_region() failed (%d)\n",
                msg,err);
        return;
    }
    cdev_init(&dev->cdev,&knh_fops);
    dev->cdev.owner = THIS_MODULE;
    dev->konoha = konoha_open(size);
    konoha_setOutputStreamBuffer(dev->konoha, size,size);
    dev->buffer = konoha_malloc(size);

#ifdef KNH_ENABLE_SEMAPHORE
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
    printk(KERN_ALERT "Hello konoha!\n");
    konohadev_p = konoha_malloc(sizeof(struct konohadev_t));
    if(!konohadev_p){
        printk(KERN_ALERT "%s:kmalloc() failed\n",msg);
        return -ENOMEM;
    }
    
    knh_dev_setup(konohadev_p);

    return 0;
}

// End/Cleanup function
static void __exit konoha_exit(void) {
    printk(KERN_ALERT "Goodbye konoha!\n");
    konoha_close(konohadev_p->konoha);
    konoha_free(konohadev_p->buffer);

    cdev_del(&konohadev_p->cdev);
    unregister_chrdev_region(konohadev_p->id,1);
    konoha_free(konohadev_p);
}

module_init(konoha_init);
module_exit(konoha_exit);

#endif /*KONOHA_ON_LKM*/

