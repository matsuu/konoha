
/* ************************************************************************ */

#include <konoha.h>
#include <zlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define FHCRC    0x02
#define FEXTRA   0x04
#define FNAME    0x08
#define FCOMMENT 0x10
#define FENCODE  0x12

#define ZLIB_HDRBUF   256
#define ZLIB_BUFSIZE 1024

enum result {
    S_OK,E_FAIL,E_INIT,E_HEAD,E_READ,E_COMP,E_DECOMP,E_OUT,E_WRITE,E_FREE,E_REMOV
};

char* message[] = {
    "ok","fail","init","head","read","comp","decomp","out","write","free","remov"
};

/* ************************************************************************ */
static int knh_get_gzheader(char*);
static int knh_decompress_gzfile(FILE*,FILE*,int);
/* ************************************************************************ */

METHOD Zlib_new(Ctx *ctx, knh_sfp_t *sfp)
{
    knh_Glue_t *glue = sfp[0].glue;
    z_stream *z = (z_stream*)malloc(sizeof(z_stream));
    z->zalloc = Z_NULL;
    z->zfree = Z_NULL;
    z->opaque = Z_NULL;

    glue->ptr = (void *)z;
    KNH_RETURN(ctx, sfp, sfp[0].o);
}


METHOD Zlib_compress(Ctx *ctx, knh_sfp_t *sfp)
{
    String *str = sfp[1].s;
    unsigned char out[ZLIB_BUFSIZE];
    z_stream *z = (z_stream*)sfp[0].glue->ptr;
    int flush, status;

    /* initiation for deflate */
    if  ((deflateInit(z, Z_DEFAULT_COMPRESSION)) !=Z_OK) {
        KNH_THROW(ctx, "cannot create zobject");
    }

    z->avail_in = 0;
    z->next_out = out;
    z->avail_out = ZLIB_BUFSIZE;

    flush = Z_NO_FLUSH;

    z->next_in = str->str;
    z->avail_in = str->size;
    flush = Z_FINISH;
    status = deflate(z, flush);
    if (status == Z_STREAM_END) {
        fprintf(stderr, "compress OK\n");
    } else if (status != Z_OK) {
        fprintf(stderr, "delfate:%s\n", (z->msg) ? z->msg : "???");
        KNH_THROW(ctx, "cannot compress");
    }

    /* output */
    String *ret= new_String(ctx, B((char*) out), NULL);
    if (deflateEnd(z) != Z_OK) {
        KNH_THROW(ctx, "cannot end deflate.");
    }
    KNH_RETURN(ctx, sfp, ret);
}

METHOD Zlib_decompress(Ctx *ctx, knh_sfp_t *sfp)
{
    z_stream *z = (z_stream*)sfp[0].glue->ptr;
    String *str = sfp[1].s;
    unsigned char out[ZLIB_BUFSIZE];
    int status;

    z->next_in = Z_NULL;
    z->avail_in = 0;
    /* initiation for inflate */

    if (inflateInit(z) != Z_OK) {
        KNH_THROW(ctx, "cannot init inflate");
    }

    z->next_out = out;
    z->avail_out = ZLIB_BUFSIZE;
    status = Z_OK;
    String *ret;


    z->next_in = str->str;
    z->avail_in = str->size;

    status = inflate(z, Z_NO_FLUSH);
    if (status == Z_STREAM_END) {
        fprintf(stderr, "decompress OK!\n");

    }else if (status != Z_OK) {
        KNH_THROW(ctx, "decompress failed");
    }

    ret = new_String(ctx, B((char*) out), NULL);
    if (inflateEnd(z) != Z_OK) {
        KNH_THROW(ctx, "cannot end decompress");
    }

    KNH_RETURN(ctx, sfp, ret);
}

/* Boolean! Zlib.decompGZ(String gzfile) */
METHOD Zlib_decompGZ(Ctx *ctx, knh_sfp_t *sfp)
{
    if(IS_String(sfp[1].o)) {
        char * fi = p_char(sfp[1]);
        int head = knh_get_gzheader(fi);
        if ( head > 0 ) {
            char * pt = strrchr(fi,'.');
            int olen = (int)(pt - fi);
            char fo[olen+1];
            strncpy(fo,fi,olen);
            fo[olen]='\0';
            FILE* fin  = fopen(fi,"rb");
            FILE* fout = fopen(fo,"wb");  
            int ret = knh_decompress_gzfile(fin,fout,head);
            fclose(fout);
            fclose(fin);
            if ( ret == S_OK ) {
                KNH_RETURN_Boolean(ctx, sfp, 1);
            } else {
                char * msg = "[zlib] decompress_gz";
                strcat(msg,message[ret]);
                KNH_THROW(ctx, msg);
                remove(fo);
            }
        } else if ( head == 0 ){
            KNH_THROWs(ctx, "this file isn't gzfile");
        } else {
            KNH_THROWs(ctx, "cannot open this file");
        }
    } else {
        KNH_THROWs(ctx, "Type!!: data must be String");
    }
    KNH_RETURN_Boolean(ctx, sfp, 0);
}

/* ************************************************************************ */
static int knh_decompress_gzfile(FILE* fin,FILE* fout,int head)
{
    z_stream z; 
    z.zalloc = Z_NULL;
    z.zfree = Z_NULL;
    z.opaque = Z_NULL;
    z.next_in = Z_NULL;
    z.avail_in = 0;
    if (inflateInit2(&z,-MAX_WBITS) != Z_OK) { return E_INIT; }
    char outbuf[ZLIB_BUFSIZE];
    char inbuf[ZLIB_BUFSIZE];
    fseek(fin, head, SEEK_SET);
    z.next_out = (Bytef*)outbuf;
    z.avail_out = ZLIB_BUFSIZE;
    int status = Z_OK;
    while (status != Z_STREAM_END) {
        if (z.avail_in == 0) {  
            z.next_in = (Bytef*)inbuf;
            z.avail_in = (int)fread(inbuf, 1, ZLIB_BUFSIZE, fin);
        }
        status = inflate(&z,Z_NO_FLUSH);
        if (status == Z_STREAM_END) { break; }
        if (status != Z_OK) { return E_DECOMP; }
        if (z.avail_out == 0) {
            if (fwrite(outbuf, 1,ZLIB_BUFSIZE, fout) != ZLIB_BUFSIZE) { return E_OUT; }
            z.next_out = (Bytef*)outbuf;
            z.avail_out = ZLIB_BUFSIZE;
        }
    }
    int count = ZLIB_BUFSIZE - z.avail_out;
    if (count != 0) {
        if (fwrite(outbuf, 1, count, fout) != count) { return E_WRITE; }
    }
    if (inflateEnd(&z) != Z_OK) { return E_FREE; }
    return S_OK;
}

static int knh_get_gzheader(char* fn)
{
    size_t headLen = 10;
    unsigned short xLen = 0;
    size_t nameLen = 0;
    size_t commentLen = 0;
    unsigned char chk[ZLIB_HDRBUF];
    unsigned char* check = chk;
    FILE* infile;
    if ( (infile = fopen(fn,"rb")) == NULL ) { return -1; }
    int ret = (int)fread(check,1,ZLIB_HDRBUF,infile);
    fclose(infile);
    if ( ret != ZLIB_HDRBUF ) { return -1; } 
    if ( check[0] != 0x1f || check[1] != 0x8b ) { return 0; }
    if ( check[3] & FHCRC ) {
        headLen += 2;
    } else if( check[3] & FEXTRA ) {
        memcpy(&xLen, &check[headLen], 2);
        headLen += 2 + xLen;
    } else if( check[3] & FNAME ) {
		nameLen = strlen( (char*)(check + headLen) );
        headLen += nameLen + 1;
    } else if( check[3] & FCOMMENT ) {
		commentLen = strlen( (char*)(check + headLen) );
        headLen += commentLen + 1;
    } else if( check[3] & FENCODE ) {
        headLen += 12;
    }
    return headLen;
}

/* ************************************************************************ */


#ifdef __cplusplus
}
#endif

