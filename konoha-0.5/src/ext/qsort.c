#ifdef KONOHA_OS__LKM
#include <linux/slab.h>
#include <linux/string.h>
#endif

#define SWAP(s, i, j, n)\
  {						\
    memcpy(n,i,s);				\
    memcpy(i,j,s);				\
    memcpy(j,n,s);				\
  }

void qsort(void *a, size_t elt, size_t s, int (*compare)(const void *,const void *))
{
    if(s > 0 && elt > 1){
        void *i, *j, *v, *n;
        n = kmalloc(s,GFP_KERNEL);
        v = a + elt * s - 1 * s;
        i = a;
        j = a + elt * s - 2 * s;
        while(1){
            while(compare(i,v) < 0){
                i += s;
            };
            while(compare(j,v) >= 0){
                j -= s;
            };
            if(i >= j){
                break;
            }
            SWAP(s,i,j,n);
        }
        SWAP(s,i,v,n);
        kfree(n);
        qsort(a,(i-a)/s,s,compare);
        qsort(i+s,elt-(i-a+s)/s,s,compare);
    }
}

