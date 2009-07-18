#include <openssl/sha.h>
#include <openssl/md5.h>
#include <konoha.h>

/*
int _main(int argc, char const* argv[])
{
    unsigned char md[SHA_DIGEST_LENGTH];
    memset(md,0,SHA_DIGEST_LENGTH);
    SHA1(argv[0],strlen(argv[0]),md);
    SHA_CTX sha;
    SHA1_Init(&sha);
    SHA1_Update(&sha,argv[0],strlen(argv[0]));
    SHA1_Final(md,&sha);
    printf("%s\n",pt(md));
    return 0;
}
*/

static inline void digest2string(unsigned char *md, size_t length, char* buf)
{
    size_t i;
    for (i = 0 ; i< length; i++) {
        sprintf(&(buf[i*2]), "%02x",md[i]);
    }
}


#define SHA_BUFFER_LENGTH SHA_DIGEST_LENGTH * 2
/* @method String Crypt.sha1(String data) */
METHOD Crypt_sha1(Ctx *ctx, knh_sfp_t *sfp)
{
    // message digest
    unsigned char md[SHA_DIGEST_LENGTH] = {0};
    char buf[SHA_BUFFER_LENGTH] = {0};
    String *data = (String *) sfp[1].s;

    SHA1(data->str, data->size, md);
    digest2string(md, SHA_DIGEST_LENGTH, buf);
    KNH_RETURN(ctx,sfp,new_String(ctx,B(buf),NULL));
}

#define MD5_BUFFER_LENGTH MD5_DIGEST_LENGTH * 2
/* @method String Crypt.md5(String data) */
METHOD Crypt_md5(Ctx *ctx, knh_sfp_t *sfp)
{
    // message digest
    unsigned char md[MD5_DIGEST_LENGTH] = {0};
    char buf[MD5_BUFFER_LENGTH] = {0};
    String *data = (String *) sfp[1].s;

    MD5(data->str, data->size, md);
    digest2string(md, MD5_DIGEST_LENGTH, buf);
    KNH_RETURN(ctx,sfp,new_String(ctx,B(buf),NULL));
}

