#ifdef KONOHA_OS__LKM
#include<linux/errno.h>
#endif
#define EDOM        33 /* Numerical argument out of domain */
#define ERANGE      34 /* Result too large */

char *strerror(int errnum)
{
    char *result;
    switch (errnum)
    {
        case 0:
            result = "No error";
            break;
        case EDOM:
            result = "Domain error";
            break;
        case ERANGE:
            result = "Range error";
            break;
        case EILSEQ:
            result = "Illegal sequence";
            break;
        default:
            result = "Unknown error";
            break;
    }
    return result;
}

