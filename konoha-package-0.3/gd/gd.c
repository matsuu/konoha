#include <konoha.h>
#include <gd.h>



/* GdImage GdImage.create(Int i0, Int i1) */

METHOD GdImage_create(Ctx *ctx, knh_sfp_t* sfp)
{
	int i0 = p_int(sfp[1]);
	int i1 = p_int(sfp[2]);
	gdImagePtr ret = gdImageCreate(i0 ,i1 );

	KNH_RETURN(ctx, sfp, ret);
}

/* GdImage GdImage.createTrueColor(Int i0, Int i1) */

METHOD GdImage_createTrueColor(Ctx *ctx, knh_sfp_t* sfp)
{
	int i0 = p_int(sfp[1]);
	int i1 = p_int(sfp[2]);
	gdImagePtr ret = gdImageCreateTrueColor(i0 ,i1 );

	KNH_RETURN(ctx, sfp, ret);
}

/* GdImage GdImage.createFromXpm(String s0) */

METHOD GdImage_createFromXpm(Ctx *ctx, knh_sfp_t* sfp)
{
	char *s0 = p_char(sfp[1]);
	gdImagePtr ret = gdImageCreateFromXpm(s0 );

	KNH_RETURN(ctx, sfp, ret);
}

/* void GdImage.destroy(self) */

METHOD GdImage_destroy(Ctx *ctx, knh_sfp_t* sfp)
{
	gdImagePtr self =(gdImagePtr)((sfp[0].glue)->ptr);
	gdImageDestroy(self );

	KNH_RETURN_void(ctx, sfp);
}

/* void GdImage.setPixel(self, Int i1, Int i2, Int i3) */

METHOD GdImage_setPixel(Ctx *ctx, knh_sfp_t* sfp)
{
	gdImagePtr self =(gdImagePtr)((sfp[0].glue)->ptr);
	int i1 = p_int(sfp[1]);
	int i2 = p_int(sfp[2]);
	int i3 = p_int(sfp[3]);
	gdImageSetPixel(self ,i1 ,i2 ,i3 );

	KNH_RETURN_void(ctx, sfp);
}

/* Int GdImage.getPixel(self, Int i1, Int i2) */

METHOD GdImage_getPixel(Ctx *ctx, knh_sfp_t* sfp)
{
	gdImagePtr self =(gdImagePtr)((sfp[0].glue)->ptr);
	int i1 = p_int(sfp[1]);
	int i2 = p_int(sfp[2]);
	int ret = gdImageGetPixel(self ,i1 ,i2 );

	KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int GdImage.getTrueColorPixel(self, Int i1, Int i2) */

METHOD GdImage_getTrueColorPixel(Ctx *ctx, knh_sfp_t* sfp)
{
	gdImagePtr self =(gdImagePtr)((sfp[0].glue)->ptr);
	int i1 = p_int(sfp[1]);
	int i2 = p_int(sfp[2]);
	int ret = gdImageGetTrueColorPixel(self ,i1 ,i2 );

	KNH_RETURN_Int(ctx, sfp, ret);
}

/* void GdImage.aABlend(self) */

METHOD GdImage_aABlend(Ctx *ctx, knh_sfp_t* sfp)
{
	gdImagePtr self =(gdImagePtr)((sfp[0].glue)->ptr);
	gdImageAABlend(self );

	KNH_RETURN_void(ctx, sfp);
}

/* Int GdImage.boundsSafe(self, Int i1, Int i2) */

METHOD GdImage_boundsSafe(Ctx *ctx, knh_sfp_t* sfp)
{
	gdImagePtr self =(gdImagePtr)((sfp[0].glue)->ptr);
	int i1 = p_int(sfp[1]);
	int i2 = p_int(sfp[2]);
	int ret = gdImageBoundsSafe(self ,i1 ,i2 );

	KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int GdImage.colorAllocate(self, Int i1, Int i2, Int i3) */

METHOD GdImage_colorAllocate(Ctx *ctx, knh_sfp_t* sfp)
{
	gdImagePtr self =(gdImagePtr)((sfp[0].glue)->ptr);
	int i1 = p_int(sfp[1]);
	int i2 = p_int(sfp[2]);
	int i3 = p_int(sfp[3]);
	int ret = gdImageColorAllocate(self ,i1 ,i2 ,i3 );

	KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int GdImage.colorAllocateAlpha(self, Int i1, Int i2, Int i3, Int i4) */

METHOD GdImage_colorAllocateAlpha(Ctx *ctx, knh_sfp_t* sfp)
{
	gdImagePtr self =(gdImagePtr)((sfp[0].glue)->ptr);
	int i1 = p_int(sfp[1]);
	int i2 = p_int(sfp[2]);
	int i3 = p_int(sfp[3]);
	int i4 = p_int(sfp[4]);
	int ret = gdImageColorAllocateAlpha(self ,i1 ,i2 ,i3 ,i4 );

	KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int GdImage.colorClosest(self, Int i1, Int i2, Int i3) */

METHOD GdImage_colorClosest(Ctx *ctx, knh_sfp_t* sfp)
{
	gdImagePtr self =(gdImagePtr)((sfp[0].glue)->ptr);
	int i1 = p_int(sfp[1]);
	int i2 = p_int(sfp[2]);
	int i3 = p_int(sfp[3]);
	int ret = gdImageColorClosest(self ,i1 ,i2 ,i3 );

	KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int GdImage.colorClosestAlpha(self, Int i1, Int i2, Int i3, Int i4) */

METHOD GdImage_colorClosestAlpha(Ctx *ctx, knh_sfp_t* sfp)
{
	gdImagePtr self =(gdImagePtr)((sfp[0].glue)->ptr);
	int i1 = p_int(sfp[1]);
	int i2 = p_int(sfp[2]);
	int i3 = p_int(sfp[3]);
	int i4 = p_int(sfp[4]);
	int ret = gdImageColorClosestAlpha(self ,i1 ,i2 ,i3 ,i4 );

	KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int GdImage.colorClosestHWB(self, Int i1, Int i2, Int i3) */

METHOD GdImage_colorClosestHWB(Ctx *ctx, knh_sfp_t* sfp)
{
	gdImagePtr self =(gdImagePtr)((sfp[0].glue)->ptr);
	int i1 = p_int(sfp[1]);
	int i2 = p_int(sfp[2]);
	int i3 = p_int(sfp[3]);
	int ret = gdImageColorClosestHWB(self ,i1 ,i2 ,i3 );

	KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int GdImage.colorExact(self, Int i1, Int i2, Int i3) */

METHOD GdImage_colorExact(Ctx *ctx, knh_sfp_t* sfp)
{
	gdImagePtr self =(gdImagePtr)((sfp[0].glue)->ptr);
	int i1 = p_int(sfp[1]);
	int i2 = p_int(sfp[2]);
	int i3 = p_int(sfp[3]);
	int ret = gdImageColorExact(self ,i1 ,i2 ,i3 );

	KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int GdImage.colorExactAlpha(self, Int i1, Int i2, Int i3, Int i4) */

METHOD GdImage_colorExactAlpha(Ctx *ctx, knh_sfp_t* sfp)
{
	gdImagePtr self =(gdImagePtr)((sfp[0].glue)->ptr);
	int i1 = p_int(sfp[1]);
	int i2 = p_int(sfp[2]);
	int i3 = p_int(sfp[3]);
	int i4 = p_int(sfp[4]);
	int ret = gdImageColorExactAlpha(self ,i1 ,i2 ,i3 ,i4 );

	KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int GdImage.colorResolve(self, Int i1, Int i2, Int i3) */

METHOD GdImage_colorResolve(Ctx *ctx, knh_sfp_t* sfp)
{
	gdImagePtr self =(gdImagePtr)((sfp[0].glue)->ptr);
	int i1 = p_int(sfp[1]);
	int i2 = p_int(sfp[2]);
	int i3 = p_int(sfp[3]);
	int ret = gdImageColorResolve(self ,i1 ,i2 ,i3 );

	KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int GdImage.colorResolveAlpha(self, Int i1, Int i2, Int i3, Int i4) */

METHOD GdImage_colorResolveAlpha(Ctx *ctx, knh_sfp_t* sfp)
{
	gdImagePtr self =(gdImagePtr)((sfp[0].glue)->ptr);
	int i1 = p_int(sfp[1]);
	int i2 = p_int(sfp[2]);
	int i3 = p_int(sfp[3]);
	int i4 = p_int(sfp[4]);
	int ret = gdImageColorResolveAlpha(self ,i1 ,i2 ,i3 ,i4 );

	KNH_RETURN_Int(ctx, sfp, ret);
}

/* void GdImage.colorDeallocate(self, Int i1) */

METHOD GdImage_colorDeallocate(Ctx *ctx, knh_sfp_t* sfp)
{
	gdImagePtr self =(gdImagePtr)((sfp[0].glue)->ptr);
	int i1 = p_int(sfp[1]);
	gdImageColorDeallocate(self ,i1 );

	KNH_RETURN_void(ctx, sfp);
}

/* void GdImage.colorTransparent(self, Int i1) */

METHOD GdImage_colorTransparent(Ctx *ctx, knh_sfp_t* sfp)
{
	gdImagePtr self =(gdImagePtr)((sfp[0].glue)->ptr);
	int i1 = p_int(sfp[1]);
	gdImageColorTransparent(self ,i1 );

	KNH_RETURN_void(ctx, sfp);
}

/* void GdImage.fill(self, Int i1, Int i2, Int i3) */

METHOD GdImage_fill(Ctx *ctx, knh_sfp_t* sfp)
{
	gdImagePtr self =(gdImagePtr)((sfp[0].glue)->ptr);
	int i1 = p_int(sfp[1]);
	int i2 = p_int(sfp[2]);
	int i3 = p_int(sfp[3]);
	gdImageFill(self ,i1 ,i2 ,i3 );

	KNH_RETURN_void(ctx, sfp);
}

/* void GdImage.setAntiAliased(self, Int i1) */

METHOD GdImage_setAntiAliased(Ctx *ctx, knh_sfp_t* sfp)
{
	gdImagePtr self =(gdImagePtr)((sfp[0].glue)->ptr);
	int i1 = p_int(sfp[1]);
	gdImageSetAntiAliased(self ,i1 );

	KNH_RETURN_void(ctx, sfp);
}

/* void GdImage.setAntiAliasedDontBlend(self, Int i1, Int i2) */

METHOD GdImage_setAntiAliasedDontBlend(Ctx *ctx, knh_sfp_t* sfp)
{
	gdImagePtr self =(gdImagePtr)((sfp[0].glue)->ptr);
	int i1 = p_int(sfp[1]);
	int i2 = p_int(sfp[2]);
	gdImageSetAntiAliasedDontBlend(self ,i1 ,i2 );

	KNH_RETURN_void(ctx, sfp);
}

/* void GdImage.setThickness(self, Int i1) */

METHOD GdImage_setThickness(Ctx *ctx, knh_sfp_t* sfp)
{
	gdImagePtr self =(gdImagePtr)((sfp[0].glue)->ptr);
	int i1 = p_int(sfp[1]);
	gdImageSetThickness(self ,i1 );

	KNH_RETURN_void(ctx, sfp);
}

/* void GdImage.interlace(self, Int i1) */

METHOD GdImage_interlace(Ctx *ctx, knh_sfp_t* sfp)
{
	gdImagePtr self =(gdImagePtr)((sfp[0].glue)->ptr);
	int i1 = p_int(sfp[1]);
	gdImageInterlace(self ,i1 );

	KNH_RETURN_void(ctx, sfp);
}

/* void GdImage.alphaBlending(self, Int i1) */

METHOD GdImage_alphaBlending(Ctx *ctx, knh_sfp_t* sfp)
{
	gdImagePtr self =(gdImagePtr)((sfp[0].glue)->ptr);
	int i1 = p_int(sfp[1]);
	gdImageAlphaBlending(self ,i1 );

	KNH_RETURN_void(ctx, sfp);
}

/* void GdImage.saveAlpha(self, Int i1) */

METHOD GdImage_saveAlpha(Ctx *ctx, knh_sfp_t* sfp)
{
	gdImagePtr self =(gdImagePtr)((sfp[0].glue)->ptr);
	int i1 = p_int(sfp[1]);
	gdImageSaveAlpha(self ,i1 );

	KNH_RETURN_void(ctx, sfp);
}

/* GdImage GdImage.squareToCircle(self, Int i1) */

METHOD GdImage_squareToCircle(Ctx *ctx, knh_sfp_t* sfp)
{
	gdImagePtr self =(gdImagePtr)((sfp[0].glue)->ptr);
	int i1 = p_int(sfp[1]);
	gdImagePtr ret = gdImageSquareToCircle(self ,i1 );

	KNH_RETURN(ctx, sfp, ret);
}

/* void GdImage.sharpen(self, Int i1) */

METHOD GdImage_sharpen(Ctx *ctx, knh_sfp_t* sfp)
{
	gdImagePtr self =(gdImagePtr)((sfp[0].glue)->ptr);
	int i1 = p_int(sfp[1]);
	gdImageSharpen(self ,i1 );

	KNH_RETURN_void(ctx, sfp);
}


/* GdImage_new(Int i1, Int i2) */
METHOD GdImage_new(Ctx *ctx, knh_sfp_t* sfp)
{
  gdImagePtr g;
  knh_Glue_t *glue = sfp[0].glue;
  g = gdImageCreate(p_int(sfp[1]), p_int(sfp[2]));

  glue->ptr = (void*)g;
  KNH_RETURN(ctx, sfp, sfp[0].o);
}
