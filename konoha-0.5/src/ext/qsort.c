#include <stdio.h>

#define SWAP(a,b,size) { \
    size_t _size = (size);  \
    char* _a = (a);         \
    char* _b = (b);         \
    do {                    \
        char _tmp = *_a;    \
        *_a++ = *_b;        \
        *_b++ = _tmp;       \
    } while(--_size > 0);   \
} \

void qsort(void* base,size_t total,size_t size, int (*comp)(const void*,const void*)){
    void *left  = base;
    void *right = left + size * (total - 1);
    void *i = left;
    void *j = right;
    void *pivot = left + size * ((right - left) / size / 2);
    if(total <= 1) return;
    do{
        while(i<j && comp(i,pivot) < 0) i += size;
        while(i<j && comp(pivot,j) < 0) j -= size;
        if(i < j){
            SWAP(i,j,size);
            if(i == pivot)       pivot = j;
            else if( j == pivot) pivot = i;
            i += size;
            j -= size;
        } else if(i== j){
            i += size;
            j -= size;
            break;
        }
    } while(i <= j);

    size_t l = (pivot - left ) / size;
    size_t r = (right - pivot) / size + 1;

    if(left <  j) qsort(left ,l,size,comp);
    if(i < right) qsort(i,    r,size,comp);
}
/*
// test code
int comp_int(const void* ap, const void* bp){
    int a = *((int *)ap);
    int b = *((int *)bp);
    if(a < b) return -1;
    if(a > b) return  1;
    return 0;
}

void p(int* a,size_t s){
    int i=0;
    if(s > 20) asm("int3");
    for(;i<s;i++){
        fprintf(stderr,"%d ",a[i]);
    }
    fprintf(stderr,"\n");
}
int main(){
    int a[] = {1,4,9,3,11,7,9,10,5,2,0,-1,8,6,7};
    //int a[] = {1,4,9,3,11,5,0,7};
    size_t n = sizeof(a) / sizeof(int);
    qsort(a,n,sizeof(int),comp_int);
    p(a,sizeof(a) / sizeof(int));
    return 0;
}

*/
