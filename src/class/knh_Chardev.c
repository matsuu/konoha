
/* ************************************************************************ */

#include"commons.h"

/* ************************************************************************ */

#ifdef __cplusplus
extern "C" {
#endif

/* ======================================================================== */
/* [constructors] */

KNHAPI(Chardev*) new_Chardev(Ctx *ctx)
{
    Chardev *cdev = (Chardev*)new_Object_bcid(ctx, CLASS_Chardev, 0);
    cdev->device = KNH_MALLOC(ctx, sizeof(knh_device_t));
    fprintf(stderr, "%s\n",__FUNCTION__);
    return cdev;
}

/* ------------------------------------------------------------------------ */

void knh_Chardev_setName(Ctx *ctx, Chardev *o, char* devname)
{
    o->name = (char *)KNH_MALLOC(ctx, strlen(devname));
    strncpy(o->name, devname, sizeof(devname));
    //fprintf(stderr, "%s,%s,%s\n",__FUNCTION__,devname,o->name);
}

/* ------------------------------------------------------------------------ */
/* [new] */
/* @method[VIRTUAL] This! Chardev.new(String! devname) */

METHOD knh__Chardev_new(Ctx *ctx, knh_sfp_t *sfp)
{
    Chardev *o = (Chardev *) sfp[0].o;
    char* devname = knh_String_tochar((String*)sfp[1].o);
    //fprintf(stderr, "%s\n",__FUNCTION__);
    knh_Chardev_setName(ctx, o, devname);
    KNH_RETURN(ctx, sfp, o);
}

/* ------------------------------------------------------------------------ */
static int knh_device_open (struct inode *inode , struct file *filp);
static ssize_t knh_device_read(struct file *filp, char __user *user_buf,
        size_t count, loff_t *offset);
//static ssize_t knh_dev_write(struct file *file,const char __user *buf,
//        size_t count,loff_t *offp) ;

static struct file_operations knh_fops = {
    .owner = THIS_MODULE,
    .open  = knh_device_open,
    .read  = knh_device_read,
    //.ioctl = knh_dev_ioctl,
};

static int knh_device_open (struct inode* inode, struct file *filp)
{
    filp->private_data = container_of(inode->i_cdev, knh_device_t,cdev);
    printk("%s at %d",__FUNCTION__,__LINE__);
    return 0;
}

static ssize_t knh_device_read (struct file* filp, char __user *user_buf,
        size_t count, loff_t *offset)
{
    struct knh_device_t *dev = filp->private_data;
    printk("%s at %d [dev=0x%p]",__FUNCTION__,__LINE__,dev);
    return 0;

}

knh_bool_t knh_Chardev_regist(Ctx *ctx, Chardev *o, char* devname)
{
    //fprintf(stderr, "%s\n",__FUNCTION__);
#ifdef KONOHA_ON_LKM
    knh_device_t *dev = (knh_device_t *) o->device;
    int err = alloc_chrdev_region(&dev->id, 0, 1, devname);
    if(err){
        printk(KERN_ALERT "%s: alloc_chrdev_region() failed (%d)\n",devname,err);
        return 0; // false
    }
    cdev_init(&dev->cdev,&knh_fops);
    dev->cdev.owner = THIS_MODULE;
    err = cdev_add(&dev->cdev, dev->id, 1);

    return 1; // true
#else
    return 1;
#endif
}

/* ------------------------------------------------------------------------ */
/* @method Boolean! Chardev.regist(String! devname) */

METHOD knh__Chardev_regist(Ctx *ctx, knh_sfp_t *sfp)
{
    Chardev *cdev = (Chardev *) sfp[0].o;
    char* devname = knh_String_tochar((String*)sfp[1].o);
    KNH_RETURN_Boolean(ctx, sfp, knh_Chardev_regist(ctx, cdev,devname))
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
