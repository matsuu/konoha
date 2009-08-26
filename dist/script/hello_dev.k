class Inode;
class File;
class Directory;
class Size;
/*
   struct module *owner;
   loff_t (*llseek) (struct file *, loff_t, int);
   ssize_t (*read) (struct file *, char *, size_t, loff_t *);
   ssize_t (*write) (struct file *, const char *, size_t, loff_t *);
   int (*readdir) (struct file *, void *, filldir_t);
   unsigned int (*poll) (struct file *, struct poll_table_struct *);
   int (*ioctl) (struct inode *, struct file *, unsigned int, unsigned long);
   int (*mmap) (struct file *, struct vm_area_struct *);
   int (*open) (struct inode *, struct file *);
   int (*flush) (struct file *);
   int (*release) (struct inode *, struct file *);
   int (*fsync) (struct file *, struct dentry *, int datasync);
   int (*fasync) (int, struct file *, int);
   int (*lock) (struct file *, int, struct file_lock *);
   ssize_t (*readv) (struct file *, const struct iovec *, unsigned long,
   loff_t *);
   ssize_t (*writev) (struct file *, const struct iovec *, unsigned long,
   loff_t *);
 */

class CharaDev {
    @virtual int llseek (File file, Offset off, int i);
    @virtual Size read (Inode inode, File file, Size size, Offset off);
    @virtual Size write (File file, String str, Size size, Offset off);
    @virtual int readdir(File file, Ptr ptr, FileDir dir);
    @virtual int poll ();
    @virtual int ioctl (Inode inode, File file, int, int);
    @virtual int mmap ();
    @virtual int open ();
    @virtual int flush(File file);
    @virtual int release ();
    @virtual int fsync ();
    @virtual int fasync (File file, int i);
    @virtual int lock() ;
    @virtual Size readv();
    @virtual Size writev();
}

class MyDev implements CharaDev {
    String buffer;
    CharaDev(String devname) {
        OUT << devname << EOL;
    }
    int read (Inode inode, File file, Size size, Offset off) {
        OUT << "hi" << EOL;
        return 0;
    }
}

mydev = new Charadev("devname");
mydev.register(); // actual registration


