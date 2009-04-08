#include <konoha.h>
#include <zlib.h>

#define ZLIB_BUFSIZE 1024

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
  knh_Glue_t *glue = sfp[0].glue;
  String *str = sfp[1].s;
  char out[ZLIB_BUFSIZE];
  z_stream *z = (z_stream*)glue->ptr;
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
  String *ret= new_String(ctx, B(out), NULL);
  if (deflateEnd(z) != Z_OK) {
	KNH_THROW(ctx, "cannot end deflate.");
  }
  KNH_RETURN(ctx, sfp, ret);
}

METHOD Zlib_decompress(Ctx *ctx, knh_sfp_t *sfp)
{
  knh_Glue_t *glue = sfp[0].glue;
  z_stream *z = (z_stream*)glue->ptr;
  String *str = sfp[1].s;
  char out[ZLIB_BUFSIZE];
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
  
  ret = new_String(ctx, B(out), NULL);
  if (inflateEnd(z) != Z_OK) {
	KNH_THROW(ctx, "cannot end decompress");
  }
  
  KNH_RETURN(ctx, sfp, ret);
}

