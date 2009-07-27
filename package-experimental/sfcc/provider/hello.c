/*
 * hello.c
 *
 */

#include <CimClientLib/cmci.h>
#include <CimClientLib/cmcidt.h>
#include <CimClientLib/cmcift.h>
#include <CimClientLib/native.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv)
{
#if 1
    if (argc != 2) {
        fprintf(stderr, "usage: %s filename\n",argv[0]);
        exit(EXIT_FAILURE);
    }
#endif

    CMCIClient* cc;
    CMPIObjectPath* objectpath;
    CMPIStatus status = {CMPI_RC_OK,NULL};
    CMPIArgs *inargs, *outargs; 
    CMPIData retval, outval;

    cc = cmciConnect("localhost", NULL, "5988","root", "password", NULL);
    objectpath = newCMPIObjectPath("root/cimv2", "Linux_Hello", NULL);

    printf("\n----------------------------------------------------------\n");
    printf("Testing invokeMethod() ...\n");
    printf("+++T1:passing IN chars argument\n");
    /*---------------------------------------------------------------------*/
    CMPIStatus rc = {CMPI_RC_OK, NULL};

    inargs  = newCMPIArgs(&rc);
    outargs = newCMPIArgs(&rc);

#if 1
    char* arg = argv[1];
#else
    char* arg = "/home/masa/src/konoha-utils/imasahiro/sfpro/script/hi.k";
#endif

    // 呼び出し時の引数登録
    // srcにargをCMPIValueとして登録
    inargs->ft->addArg(inargs, "src", (CMPIValue *)arg, CMPI_chars);
 
    /*
    CMPIData val;
    val = inargs->ft->getArg(inargs,"src",&rc);
    CMPIString* str;
    str = val.value.string;
    fprintf(stderr, "[%s]\n",CMGetCharPtr(str));
    */

    retval = cc->ft->invokeMethod(
            cc, objectpath, "call", inargs, outargs, &status);

    /* Print the results */
    printf( "invokeMethod() rc=%d, msg=%s\n", 
            status.rc, (status.msg)? (char *)status.msg->hdl : NULL);

    if (inargs)  CMRelease(inargs);
    if (outargs) CMRelease(outargs);
    if (status.msg) CMRelease(status.msg);
    if (!status.rc) {
        //char *cv = value2Chars(retval.type,&(retval.value));
        char *cv = CMGetCharPtr(retval.value.string);
        printf("return value:[%s]\n", cv);
        if (cv != NULL) free(cv);
    }
 
    if (objectpath) CMRelease(objectpath);
    if (cc) CMRelease(cc);

    return 0;
}

