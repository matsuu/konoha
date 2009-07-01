#ifdef KONOHA_ON_LKM
#include <linux/string.h>
#define _quicksort qsort
#else
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#endif

typedef char qstack_t;
#define STACK_SIZE      (128 * sizeof(size_t))
#define STACK_PUSH(stack,ptr) ((void) ((stack = (ptr)), ++stack))
#define STACK_POP( stack,ptr) ((void) (--stack, ptr= stack))
#define STACK_IS_EMPTY(stack,ptr) (stack >= ptr)

/* Byte-wise swap two items of size SIZE. */
#define SWAP(a, b, size) {                  \
	register size_t __size = (size);        \
	register char *__a = (a), *__b = (b);   \
	do {                                    \
		char __tmp = *__a;                  \
		*__a++ = *__b;                      \
		*__b++ = __tmp;                     \
	} while (--__size > 0);                 \
}                                           \

void _quicksort (void *const base, size_t total_elems, size_t size,
		int (*cmp)(const void*,const void*))
{
	char *base_ptr = (char *) base;
	if (total_elems == 0) return;
	char *left  = base_ptr;
	char *right = &left[size * (total_elems - 1)];
	qstack_t stack[STACK_SIZE];
	qstack_t *top = stack;

	STACK_PUSH (top, NULL);

	while (!STACK_IS_EMPTY(stack,top))
	{
		char *left_ptr  = left;
		char *right_ptr = right;
		char *mid = left + size * ((right - left) / size >> 1);

		while (left_ptr <= right_ptr) {
			while ((*cmp) ((void *) left_ptr, (void *) mid)  < 0) left_ptr  += size;
			while ((*cmp) ((void *) mid, (void *) right_ptr) < 0) right_ptr -= size;

			if (left_ptr < right_ptr) {
				SWAP (left_ptr, right_ptr, size);
				if (mid == left_ptr)        mid = right_ptr;
				else if (mid == right_ptr)  mid = left_ptr;
				left_ptr  += size;
				right_ptr -= size;
			}
			else if (left_ptr == right_ptr) {
				left_ptr  += size;
				right_ptr -= size;
				break;
			}
		}
		if((right_ptr - left) > (right - left_ptr)){
			STACK_PUSH(top,left);
			STACK_PUSH(top,right_ptr);
			left = left_ptr;
		} else {
			STACK_POP(top,left_ptr);
			STACK_POP(top,right);
			right = right_ptr;
		}
	}
}

