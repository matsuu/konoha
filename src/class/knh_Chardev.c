
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
#ifdef KONOHA_ON_LKM
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
    printk("%s at %d\n",__FUNCTION__,__LINE__);
    return 0;
}

static ssize_t knh_device_read (struct file* filp, char __user *user_buf,
        size_t count, loff_t *offset)
{
    knh_device_t *dev = filp->private_data;
    DictMap *dict = (DictMap *)dev->fmap;

    Ctx *lctx = knh_beginContext(dev->ctx);
    knh_sfp_t *lsfp = KNH_LOCAL(lctx);
    Closure *cc = (Closure *) knh_DictMap_get__b(lctx, dict, B("read"));

    printk("%s at %d [dev=0x%p]\n",__FUNCTION__,__LINE__,cc);
    if (cc) {
    printk("%s at %d\n",__FUNCTION__,__LINE__);
        knh_Closure_invokesfp(lctx, cc, lsfp, 0);
    printk("%s at %d\n",__FUNCTION__,__LINE__);
    // XXX where is return value?
    // I think sfp[-1], but it isn't hear.
        char* ret = knh_String_tochar((String*)lsfp[-1].o);
        printk("%s at %d [ret=%s]\n",__FUNCTION__,__LINE__,ret);
    }

    return 0;
}
#endif

knh_bool_t knh_Chardev_regist(Ctx *ctx, Chardev *o)
{
    fprintf(stderr, "%s\n",__FUNCTION__);
#ifdef KONOHA_ON_LKM
    knh_device_t *dev = (knh_device_t *) o->device;
    char* name = o->name;
    int err = alloc_chrdev_region(&dev->id, 0, 1, name);
    if(err){
        printk(KERN_ALERT "%s: alloc_chrdev_region() failed (%d)\n",name,err);
        return 0; // false
    }
    cdev_init(&dev->cdev,&knh_fops);
    dev->cdev.owner = THIS_MODULE;
    err = cdev_add(&dev->cdev, dev->id, 1);
    if(err){
        printk(KERN_ALERT "%s: cdev_add() failed (%d)\n",name,err);
        return 0; // false
    }
    o->isEnable = 1;
#endif

    return 1;
}

/* ------------------------------------------------------------------------ */
/* @method Boolean! Chardev.regist() */

METHOD knh__Chardev_regist(Ctx *ctx, knh_sfp_t *sfp)
{
    Chardev *cdev = (Chardev *) sfp[0].o;
    cdev->device->ctx = (Context *)ctx;
    KNH_RETURN_Boolean(ctx, sfp, knh_Chardev_regist(ctx, cdev))
}

/* ------------------------------------------------------------------------ */
/* @method Boolean! Chardev.unregist() */

METHOD knh__Chardev_unregist(Ctx *ctx, knh_sfp_t *sfp)
{
    Chardev *cdev = (Chardev *) sfp[0].o;
    knh_device_t *device = cdev->device;
    if(cdev->isEnable) {
#ifdef KONOHA_ON_LKM
        cdev_del(&device->cdev);
        unregister_chrdev_region(device->id,1);
        cdev->isEnable = 0;
#endif
    }
    KNH_RETURN_Boolean(ctx, sfp, 1);
}

/* ------------------------------------------------------------------------ */
/* @method Boolean! Chardev.addFunc(String op, Closure c) */

METHOD knh__Chardev_addFunc(Ctx *ctx, knh_sfp_t *sfp)
{
    Chardev *cdev = (Chardev *) sfp[0].o;
    String* opname = (String*)sfp[1].o;
    Closure *cc   = sfp[2].cc;

    DictMap *fmap = cdev->device->fmap;
    knh_DictMap_set(ctx, fmap, opname, (Object *)cc);
    KNH_RETURN_Boolean(ctx, sfp, 1);
}


/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
