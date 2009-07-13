#include <konoha.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifdef __cplusplus
extern "C" {
#endif

// String System.tmpfile();
METHOD System_tmpfile(Ctx *ctx, knh_sfp_t *sfp)
{
    char template[] = "/tmp/konohaXXXXXX";
    int fd = mkstemp(template);
    if(fd < 0){
        KNH_THROWs(ctx, "cant create tempolary file");
    }
    KNH_RETURN(ctx, sfp, new_String(ctx, B(template), NULL));
}

// String OutputStream.getURN();
METHOD OutputStream_getUrn(Ctx *ctx, knh_sfp_t *sfp)
{
    OutputStream* o = (OutputStream*) sfp[0].o;
    String* urn = DP(o)->urn;
    KNH_RETURN(ctx, sfp, urn);
}

// String InputStream.getURN();
METHOD InputStream_getUrn(Ctx *ctx, knh_sfp_t *sfp)
{
    InputStream* o = (InputStream*) sfp[0].o;
    String* urn = DP(o)->urn;
    KNH_RETURN(ctx, sfp, urn);
}

// String[] System.popen();

#define BUFSIZE 256
METHOD System_popen(Ctx *ctx, knh_sfp_t *sfp)
{
    char* cmd = p_char(sfp[1]);
    char buffer[BUFSIZE];
    FILE *pipe;
    Array *a = new_Array(ctx, CLASS_String, 0);
    memset(buffer,0,sizeof(buffer));
    pipe = popen(cmd,"r");
    if ((pipe = popen(cmd, "r")) == NULL) {
        KNH_THROWs(ctx, "IO!! : cant execute this");
        fprintf(stderr, "err\n");
    }
    while(fgets(buffer, BUFSIZE, pipe) != NULL) {
        knh_Array_add(ctx, a, UP(new_String(ctx, B(buffer), NULL)));
    }
    pclose(pipe);
    usleep(100);
    KNH_RETURN(ctx, sfp, a);
}

KNH_EXPORTS(int) init(Ctx *ctx)
{
    KNH_NOTICE(ctx, "loading ext..");
    return 1;
}

#ifdef __cplusplus
}
#endif

