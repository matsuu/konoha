/* 
 * cmpiOSBase_HelloProvider.c
 * (c) masahiro@ynu 2009
 */

#include <cmpi/cmpidt.h>
#include <cmpi/cmpift.h>
#include <cimc/cimcdt.h>
#include <cmpi/cmpimacs.h>
#include <konoha.h>
#include <pthread.h>

static const CMPIBroker * _broker;
static char* _Name = "Linux_Hello";

CMPIStatus OSBase_HelloProviderCleanup(
        CMPIInstanceMI * mi, 
        const CMPIContext * ctx, 
        CMPIBoolean terminating
        )
{ 
    CMReturn(CMPI_RC_OK);
}

CMPIStatus OSBase_HelloProviderEnumInstanceNames(
        CMPIInstanceMI* mi,       const CMPIContext* ctx,
        const CMPIResult* rslt,   const CMPIObjectPath* op
        )
{
    CMPIStatus rc = {CMPI_RC_OK, NULL};

    char buf[256];
    snprintf(buf,256,"%s at %s","CIM_ERR_NOT_SUPPORTED ",__FUNCTION__);
    CMSetStatusWithChars( _broker, &rc, 
            CMPI_RC_ERR_NOT_SUPPORTED, buf);

    return rc;
}

CMPIStatus OSBase_HelloProviderEnumInstances(
        CMPIInstanceMI * mi,         const CMPIContext * ctx, 
        const CMPIResult * rslt,     const CMPIObjectPath * ref, 
        const char ** properties)
{
    CMPIStatus rc = {CMPI_RC_OK, NULL}; 

    char *nameSpace = CMGetCharPtr(CMGetNameSpace(ref, &rc));
    CMPIObjectPath *op = CMNewObjectPath( _broker, nameSpace, _Name, &rc);

    if (CMIsNullObject(op)) {
        char buf[256];
        snprintf(buf,256,"%s at %s","ERROR. Create CMPIObjectPath failed ",__FUNCTION__);
        CMSetStatusWithChars( _broker, &rc, CMPI_RC_ERR_FAILED, buf);
        return rc;
    }

    CMAddKey(op, "Message", "hi", CMPI_chars);
    CMReturnObjectPath(rslt, op);
    return rc;
}

CMPIStatus OSBase_HelloProviderGetInstance(
        CMPIInstanceMI * mi,         const CMPIContext * ctx, 
        const CMPIResult * rslt,     const CMPIObjectPath * cop, 
        const char ** properties)
{
    CMPIInstance *ci = NULL;
    CMPIStatus    rc     = {CMPI_RC_OK, NULL};

    char *nameSpace = CMGetCharPtr(CMGetNameSpace(cop, &rc));
    CMPIObjectPath *op = CMNewObjectPath( _broker, nameSpace, _Name, &rc);

    if (CMIsNullObject(op)) {
        char buf[256];
        snprintf(buf,256,"%s at %s","ERROR. Create CMPIObjectPath failed ",__FUNCTION__);
        CMSetStatusWithChars( _broker, &rc, CMPI_RC_ERR_FAILED, buf);
        return rc;
    }

    ci = CMNewInstance( _broker, op, &rc);
    CMSetProperty(ci, "Message", "hello world", CMPI_chars);
    CMReturnInstance(rslt, ci);
    CMReturnDone(rslt);
    return rc;
}

CMPIStatus OSBase_HelloProviderCreateInstance(
        CMPIInstanceMI * mi,     const CMPIContext * ctx, 
        const CMPIResult * rslt, const CMPIObjectPath * cop, 
        const CMPIInstance * ci)
{
    CMPIStatus rc = {CMPI_RC_OK, NULL};

    char buf[256];
    snprintf(buf,256,"%s at %s","CIM_ERR_NOT_SUPPORTED ",__FUNCTION__);

    CMSetStatusWithChars( _broker, &rc, 
            CMPI_RC_ERR_NOT_SUPPORTED, buf);

    return rc;
}

CMPIStatus OSBase_HelloProviderSetInstance(
        CMPIInstanceMI * mi,     const CMPIContext * ctx, 
        const CMPIResult * rslt, const CMPIObjectPath * cop,
        const CMPIInstance * ci, char **properties)
{
    CMPIStatus rc = {CMPI_RC_OK, NULL};

    char buf[256];
    snprintf(buf,256,"%s at %s","CIM_ERR_NOT_SUPPORTED ",__FUNCTION__);

    CMSetStatusWithChars( _broker, &rc, CMPI_RC_ERR_NOT_SUPPORTED, buf);
    return rc;
}

CMPIStatus OSBase_HelloProviderModifyInstance(
        CMPIInstanceMI * mi,     const CMPIContext * ctx, 
        const CMPIResult * rslt, const CMPIObjectPath * ref,
        const CMPIInstance * ci, const char **properties)
{
    CMPIStatus rc = {CMPI_RC_OK, NULL};

    char buf[256];
    snprintf(buf,256,"%s at %s","CIM_ERR_NOT_SUPPORTED ",__FUNCTION__);

    CMSetStatusWithChars( _broker, &rc, CMPI_RC_ERR_NOT_SUPPORTED, buf);

    return rc;
}

CMPIStatus OSBase_HelloProviderDeleteInstance(
        CMPIInstanceMI * mi,     const CMPIContext * ctx, 
        const CMPIResult * rslt, const CMPIObjectPath * cop)
{
    CMPIStatus rc = {CMPI_RC_OK, NULL}; 

    char buf[256];
    snprintf(buf,256,"%s at %s","CIM_ERR_NOT_SUPPORTED ",__FUNCTION__);

    CMSetStatusWithChars( _broker, &rc, CMPI_RC_ERR_NOT_SUPPORTED, buf);

    return rc;
}

CMPIStatus OSBase_HelloProviderExecQuery(
        CMPIInstanceMI * mi,     const CMPIContext * ctx, 
        const CMPIResult * rslt, const CMPIObjectPath * ref, 
        const char * lang,       const char * query)
{
    CMPIStatus rc = {CMPI_RC_OK, NULL};

    char buf[256];
    snprintf(buf,256,"%s at %s","CIM_ERR_NOT_SUPPORTED ",__FUNCTION__);

    CMSetStatusWithChars( _broker, &rc, CMPI_RC_ERR_NOT_SUPPORTED, buf);

    return rc;
}

CMPIStatus OSBase_HelloProviderMethodCleanup(
        CMPIMethodMI * mi, const CMPIContext * ctx,
        CMPIBoolean terminate)
{
    CMReturn(CMPI_RC_OK);
}

CMPIStatus OSBase_HelloProviderInvokeMethod(
        CMPIMethodMI * mi,       const CMPIContext * ctx,
        const CMPIResult * rslt, const CMPIObjectPath * ref,
        const char * methodName, const CMPIArgs * args,
        CMPIArgs * out)
{
    CMPIString *class = NULL; 
    CMPIStatus  rc    = {CMPI_RC_OK, NULL};
    char *className = NULL;

    // ref = { "CLASS":"Test" };
    class = CMGetKey(ref, "CLASS", &rc).value.string;
    className = CMGetCharPtr(class);

    if (className == NULL) {
        CMSetStatusWithChars( _broker, &rc, CMPI_RC_ERR_FAILED, 
                "ERROR. you must set ObjectPath");
        return rc;
    }

    /*
    // args = { "a0":"hoge" ,"a1": 3, "a2":"orz"};
    int argc = args->ft->getArgCount(args,&rc);
    CMPIData args;
    val = args->ft->getArg(args,"src",&rc);
    //val = args->ft->getArgAt(args,0,NULL,&rc);
    CMPIString* str = val.value.string;
    */
    int argc = args->ft->getArgCount(args,&rc);
    int i;
    char c[64] = {0};
    char **argv;
    char mName[128] = {0};
    //char name[128] = {0};
    CMPIData val;
    CMPIString *str;
    argv = (char **)alloca(argc * sizeof(char*));
    for(i=0;i<argc;i++){
      snprintf(c,64,"a%d",i);
      val = args->ft->getArg(args,c,&rc);
      str = val.value.string;
      argv[i] = str->ft->getCharPtr(str,NULL);
    }
    if(argc!=0){
      snprintf(mName,128,"%s(%%s",methodName);
    }
    else{
      snprintf(mName,128,"%s(",methodName);
    }    
    for(i=1;i<argc;i++){
      //snprintf(name,128,"%s",mName);
      //snprintf(mName,128,"%s,%%s",name);
      strncat(mName,",%s",3);
    }
    //snprintf(name,128,"%s",mName);
    //snprintf(mName,128,"%s)",name);
    strncat(mName,")",1);
    /* //hope this format
      if(argc!=0){
      snprintf(mName,128,"%s(%s",methodName,argv[0]);
      }
      else{
      snprintf(mName,128,"%s(",methodName);
      }    
      for(i=1;i<argc;i++){
      strncat(mName,",",1);
      strncat(mName,argv[i],strlen(argv[i]));
      }
      strncat(mName,")",1);
     */

    char path[128];
    snprintf(path, sizeof(path), "/usr/local/share/konoha/script/%s.k",className);
    
    konoha_t konoha = konoha_open(4096);
    knh_setOutputStreamBuffer(konoha, 256,256);
    konoha_loadScript(konoha,path);
    //snprintf(methodName,128,"%s",mName);
    printf("%s %d\n",mName,__LINE__);
    char* retval;
    
    switch(argc){
    case 0:
      retval = konoha_invokeStringFunc(konoha, mName);
      break;
    case 1:
      retval = konoha_invokeStringFunc(konoha, mName,argv[0]);
      break;
    case 2:
      retval = konoha_invokeStringFunc(konoha, mName, argv[0], argv[1]);
      break;
    case 3:
      retval = konoha_invokeStringFunc(konoha, mName, argv[0], argv[1], argv[2]);
      break; 
    case 4:
      retval = konoha_invokeStringFunc(konoha, mName, argv[0], argv[1], argv[2], argv[3]);
      break;
    case 5:
      retval = konoha_invokeStringFunc(konoha, mName, argv[0], argv[1], argv[2], argv[3], argv[4]);
      break;
    default:
      retval = "Too many args!!";
      konoha_invokeStringFunc(konoha, methodName); // segmentasionfault
      break;
    }
    
  
    
    printf("%s %d\n",mName,__LINE__);
    printf("%s %d\n",retval,__LINE__);
    if (konoha_hasRuntimeError(konoha)) {
        /* runtime error */
      char err[128] = {0};
      fprintf(stderr, "O::%s\n",knh_getSTDOUTBuffer(konoha));
      fprintf(stderr, "E::123 %s456\n",knh_getSTDERRBuffer(konoha));
      snprintf(err,128,"%s%s",retval,knh_getSTDERRBuffer(konoha));
      retval = err;
      printf("%s %d\n",retval,__LINE__);
    } else {
      fprintf(stderr, "O::%s\n",knh_getSTDOUTBuffer(konoha));
    }

    //char* retval = knh_getSTDOUTBuffer(konoha);
    CMPIValue value;
    value.string = CMNewString(_broker, retval, &rc);

    /*
    // how to return object path.
    // but, objectPath is unable to send.
    // because sfcb( or cim) cant send it.
    char *nameSpace = CMGetCharPtr(CMGetNameSpace(ref, &rc));
    CMPIObjectPath *op = CMNewObjectPath( _broker, nameSpace, _Name, &rc);
    op->ft->addKey(op, "ret", (CMPIValue*)ptr, CMPI_chars);
    value.ref = op;
    CMReturnData(rslt, &value,CMPI_ref);
    */

    CMReturnData(rslt, &value,CMPI_string);
    CMReturnDone(rslt);
    konoha_close(konoha);

    return rc;
}


CMInstanceMIStub( OSBase_HelloProvider, OSBase_HelloProvider, _broker,CMNoHook);
CMMethodMIStub  ( OSBase_HelloProvider, OSBase_HelloProvider, _broker,CMNoHook);

