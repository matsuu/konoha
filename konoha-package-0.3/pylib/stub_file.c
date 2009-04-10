#include <konoha.h>


/* File! File.new(String filename, String mode) */

METHOD File_new(Ctx *ctx, knh_sfp_t* sfp)
{
	knh_String_t *mode = sfp[2].s;
	knh_String_t *filename = sfp[1].s;

}

/* void File.open(String filename, String mode) */

METHOD File_open(Ctx *ctx, knh_sfp_t* sfp)
{
	knh_String_t *mode = sfp[2].s;
	knh_String_t *filename = sfp[1].s;

	KNH_RETURN_void(ctx, sfp);
}

/* void File.putc(int c) */

METHOD File_putc(Ctx *ctx, knh_sfp_t* sfp)
{
	int c = p_int(sfp[1]);

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
