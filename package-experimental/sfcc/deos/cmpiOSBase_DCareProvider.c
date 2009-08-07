/* 
 * cmpiOSBase_DCareProvider.c
 * (c) masahiro@ynu 2009
 */

#include <cmpi/cmpidt.h>
#include <cmpi/cmpift.h>
#include <cimc/cimcdt.h>
#include <cmpi/cmpimacs.h>
#include <konoha.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

static const CMPIBroker * _broker;
//static char* _Name = "DEOS_DCare";

CMPIStatus OSBase_DCareProviderCleanup(
        CMPIInstanceMI * mi, 
        const CMPIContext * ctx, 
        CMPIBoolean terminating
        )
{ 
    CMReturn(CMPI_RC_OK);
}


CMPIStatus OSBase_DCareProviderMethodCleanup(
        CMPIMethodMI * mi, const CMPIContext * ctx,
        CMPIBoolean terminate)
{
    CMReturn(CMPI_RC_OK);
}

CMPIStatus OSBase_DCareProviderInvokeMethod(
        CMPIMethodMI * mi,       const CMPIContext * ctx,
        const CMPIResult * rslt, const CMPIObjectPath * ref,
        const char * methodName, const CMPIArgs * args,
        CMPIArgs * out)
{
    CMPIString *class = NULL; 
    CMPIStatus  rc    = {CMPI_RC_OK, NULL};
    char *className = NULL;

    class = CMGetKey(ref, "CLASS", &rc).value.string;
    className = CMGetCharPtr(class);

    if (className == NULL) {
        CMSetStatusWithChars( _broker, &rc, CMPI_RC_ERR_FAILED, 
                "ERROR. you must set ObjectPath");
        return rc;
    }

    char *c = "a0";
    char *argv;
    char *mName = "receive(%s)";
    CMPIData val;
    CMPIString *str;
    argv = (char *)alloca(sizeof(char*));
    val = args->ft->getArg(args,c,&rc);
    str = val.value.string;
    argv = str->ft->getCharPtr(str,NULL);
   
    char path[128];
    snprintf(path, sizeof(path), "/usr/local/share/konoha/script/%s.k","DCare");
 
    konoha_t konoha = konoha_open(4096);
    konoha_setOutputStreamBuffer(konoha, 256,256);
    konoha_loadScript(konoha,path);
    
    printf("%s %d\n",mName,__LINE__);
    char* retval;
   
    retval = konoha_invokeStringFunc(konoha, mName,argv);
    retval = "";

    printf("%s %d\n",mName,__LINE__);
    printf("%s %d\n",retval,__LINE__);
    if (konoha_hasRuntimeError(konoha)) {
      /* runtime error */
      char err[128] = {0};
      fprintf(stderr, "O::%s\n",konoha_getStdOutBufferText(konoha));
      fprintf(stderr, "E::%s\n",konoha_getStdErrBufferText(konoha));
      snprintf(err,128,"%s",konoha_getStdErrBufferText(konoha));
      retval = err;
      printf("%s %d\n",retval,__LINE__);
    }
    else {
      fprintf(stderr, "O::%s\n",konoha_getStdOutBufferText(konoha));
    }

    CMPIValue value;
    value.string = CMNewString(_broker, retval, &rc);
    
    printf("retvalue:%s\n",retval);
    CMReturnData(rslt, &value,CMPI_string);
    CMReturnDone(rslt);
    konoha_close(konoha);

    return rc;
}

CMMethodMIStub  ( OSBase_DCareProvider, OSBase_DCareProvider, _broker,setuid(0));
