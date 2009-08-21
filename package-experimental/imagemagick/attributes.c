
#include "knh_imagemagick.h"

/* Float ImageMagick.getGamma(self) */

METHOD ImageMagick_getGamma(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	double ret = MagickGetImageGamma(self );
	if (!ret)  KNH_RETURN_Int(ctx, sfp, 0);
	KNH_RETURN_Float(ctx, sfp, ret);
}

/* Boolean ImageMagick.getMatte(self) */

METHOD ImageMagick_getMatte(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int ret = MagickGetImageMatte(self );
	if (!ret)  KNH_RETURN_Int(ctx, sfp, 0);
	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Int ImageMagick.getImageColors(self) */

METHOD ImageMagick_getColors(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int ret = MagickGetImageColors(self );
	if (!ret)  KNH_RETURN_Int(ctx, sfp, 0);
	KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int ImageMagick.getHeight(self) */

METHOD ImageMagick_getHeight(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int ret = MagickGetImageHeight(self );
	if (!ret)  KNH_RETURN_Int(ctx, sfp, 0);
	KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int ImageMagick.getDepth(self) */

METHOD ImageMagick_getDepth(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int ret = MagickGetImageDepth(self );
	if (!ret)  KNH_RETURN_Int(ctx, sfp, 0);
	KNH_RETURN_Int(ctx, sfp, ret);
}
/* Int ImageMagick.getIterations(self) */

METHOD ImageMagick_getIterations(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int ret = MagickGetImageIterations(self );
	if (!ret)  KNH_RETURN_Int(ctx, sfp, 0);
	KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int ImageMagick.getScene(self) */

METHOD ImageMagick_getScene(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int ret = MagickGetImageScene(self );
	if (!ret)  KNH_RETURN_Int(ctx, sfp, 0);
	KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int ImageMagick.getWidth(self) */

METHOD ImageMagick_getWidth(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int ret = MagickGetImageWidth(self );
	if (!ret)  KNH_RETURN_Int(ctx, sfp, 0);
	KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int ImageMagick.getCompressionQuality(self) */

METHOD ImageMagick_getCompressionQuality(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int ret = MagickGetImageCompressionQuality(self );
	if (!ret)  KNH_RETURN_Int(ctx, sfp, 0);
	KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int ImageMagick.getDelay(self) */

METHOD ImageMagick_getDelay(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int ret = MagickGetImageDelay(self );
	if (!ret) KNH_RETURN_Int(ctx, sfp, 0);
	KNH_RETURN_Int(ctx, sfp, ret);
}
