#include <konoha.h>
#include <wand/MagickWand.h>


/* File! File.new(String filename, String mode) */

METHOD File_new(Ctx *ctx, knh_sfp_t* sfp)
{
	char *filename = p_char(sfp[0]);
	char *mode = p_char(sfp[1]);
	File *ret = FileNew(filename ,mode );

}

/* void File.open(String filename, String mode) */

METHOD File_open(Ctx *ctx, knh_sfp_t* sfp)
{
	char *filename = p_char(sfp[0]);
	char *mode = p_char(sfp[1]);

	KNH_RETURN_void(ctx, sfp);
}

/* void File.putc(int c) */

METHOD File_putc(Ctx *ctx, knh_sfp_t* sfp)
{
	int c = p_int(sfp[0]);

	KNH_RETURN_void(ctx, sfp);
}

/* void File.close() */

METHOD File_close(Ctx *ctx, knh_sfp_t* sfp)
{

	KNH_RETURN_void(ctx, sfp);
}

/* void! File.close() */

METHOD File_close(Ctx *ctx, knh_sfp_t* sfp)
{

}


METHOD MagickWand_new(Ctx *ctx, knh_sfp_t* sfp)
{
  knh_Glue_t *glue = sfp[0].glue;
  glue->ptr = (void *)NewMagickWand();
  KNH_RETURN(ctx, sfp, sfp[0].o);
}
