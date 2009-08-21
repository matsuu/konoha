#include <konoha.h>
#include <wand/MagickWand.h>

/* void ImageMagick.coreGenesis(String s0, Boolean b1) */

METHOD ImageMagick_coreGenesis(Ctx *ctx, knh_sfp_t* sfp)
{
	char *s0 = p_char(sfp[1]);
	int b1 = p_int(sfp[2]);
	MagickCoreGenesis(s0 ,b1 );

	KNH_RETURN_void(ctx, sfp);
}


/* void ImageMagick.coreTerminus() */

METHOD ImageMagick_coreTerminus(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickCoreTerminus();

	KNH_RETURN_void(ctx, sfp);
}

/* String ImageMagick.toMime(String s0) */

METHOD ImageMagick_toMime(Ctx *ctx, knh_sfp_t* sfp)
{
	char *s0 = p_char(sfp[1]);
	char *ret = MagickToMime(s0 );

	KNH_RETURN(ctx, sfp, new_String(ctx, B(ret), NULL));
}

/* String ImageMagick.describeImage(self) */

METHOD ImageMagick_describeImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	char *ret = MagickDescribeImage(self );

	KNH_RETURN(ctx, sfp, new_String(ctx, B(ret), NULL));
}

/* String ImageMagick.getImageAttribute(self, String s1) */

METHOD ImageMagick_getImageAttribute(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	char *s1 = p_char(sfp[1]);
	char *ret = MagickGetImageAttribute(self ,s1 );

	KNH_RETURN(ctx, sfp, new_String(ctx, B(ret), NULL));
}

/* Int ImageMagick.getImageIndex(self) */

METHOD ImageMagick_getImageIndex(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int ret = MagickGetImageIndex(self );

	KNH_RETURN_Int(ctx, sfp, ret);
}

/* Boolean ImageMagick.clipPathImage(self, String s1, Boolean b2) */

METHOD ImageMagick_clipPathImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	char *s1 = p_char(sfp[1]);
	int b2 = p_int(sfp[2]);
	int ret = MagickClipPathImage(self ,s1 ,b2 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.setImageAttribute(self, String s1, String s2) */

METHOD ImageMagick_setImageAttribute(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	char *s1 = p_char(sfp[1]);
	char *s2 = p_char(sfp[2]);
	int ret = MagickSetImageAttribute(self ,s1 ,s2 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.setImageIndex(self, Int i1) */

METHOD ImageMagick_setImageIndex(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int i1 = p_int(sfp[1]);
	int ret = MagickSetImageIndex(self ,i1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.setImageOption(self, String s1, String s2, String s3) */

METHOD ImageMagick_setImageOption(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	char *s1 = p_char(sfp[1]);
	char *s2 = p_char(sfp[2]);
	char *s3 = p_char(sfp[3]);
	int ret = MagickSetImageOption(self ,s1 ,s2 ,s3 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* ImageMagick ImageMagick.flattenImages(self) */

METHOD ImageMagick_flattenImages(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	MagickWand *ret = MagickFlattenImages(self );
	KNH_RETURN(ctx, sfp, sfp[0].o);
}

/* ImageMagick ImageMagick.mosaicImages(self) */

METHOD ImageMagick_mosaicImages(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	MagickWand *ret = MagickMosaicImages(self );
	KNH_RETURN(ctx, sfp, sfp[0].o);
}

/* String ImageMagick.getFilename(self) */

METHOD ImageMagick_getFilename(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	char *ret = MagickGetFilename(self );

	KNH_RETURN(ctx, sfp, new_String(ctx, B(ret), NULL));
}

/* String ImageMagick.getFormat(self) */

METHOD ImageMagick_getFormat(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	char *ret = MagickGetFormat(self );

	KNH_RETURN(ctx, sfp, new_String(ctx, B(ret), NULL));
}

/* String ImageMagick.getFont(self) */

METHOD ImageMagick_getFont(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	char *ret = MagickGetFont(self );

	KNH_RETURN(ctx, sfp, new_String(ctx, B(ret), NULL));
}

/* String ImageMagick.getHomeURL() */

METHOD ImageMagick_getHomeURL(Ctx *ctx, knh_sfp_t* sfp)
{
	char *ret = MagickGetHomeURL();

	KNH_RETURN(ctx, sfp, new_String(ctx, B(ret), NULL));
}

/* String ImageMagick.getImageProperty(self, String s1) */

METHOD ImageMagick_getImageProperty(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	char *s1 = p_char(sfp[1]);
	char *ret = MagickGetImageProperty(self ,s1 );

	KNH_RETURN(ctx, sfp, new_String(ctx, B(ret), NULL));
}

/* String ImageMagick.getOption(self, String s1) */

METHOD ImageMagick_getOption(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	char *s1 = p_char(sfp[1]);
	char *ret = MagickGetOption(self ,s1 );

	KNH_RETURN(ctx, sfp, new_String(ctx, B(ret), NULL));
}

/* String ImageMagick.queryConfigureOption(String s0) */

METHOD ImageMagick_queryConfigureOption(Ctx *ctx, knh_sfp_t* sfp)
{
	char *s0 = p_char(sfp[1]);
	char *ret = MagickQueryConfigureOption(s0 );

	KNH_RETURN(ctx, sfp, new_String(ctx, B(ret), NULL));
}

/* String ImageMagick.getCopyright() */

METHOD ImageMagick_getCopyright(Ctx *ctx, knh_sfp_t* sfp)
{
	char *ret = MagickGetCopyright();

	KNH_RETURN(ctx, sfp, new_String(ctx, B(ret), NULL));
}

/* String ImageMagick.getPackageName() */

METHOD ImageMagick_getPackageName(Ctx *ctx, knh_sfp_t* sfp)
{
	char *ret = MagickGetPackageName();

	KNH_RETURN(ctx, sfp, new_String(ctx, B(ret), NULL));
}

/* String ImageMagick.getReleaseDate() */

METHOD ImageMagick_getReleaseDate(Ctx *ctx, knh_sfp_t* sfp)
{
	char *ret = MagickGetReleaseDate();

	KNH_RETURN(ctx, sfp, new_String(ctx, B(ret), NULL));
}

/* Float ImageMagick.getPointsize(self) */

METHOD ImageMagick_getPointsize(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	double ret = MagickGetPointsize(self );

	KNH_RETURN_Float(ctx, sfp, ret);
}

/* Boolean ImageMagick.deleteOption(self, String s1) */

METHOD ImageMagick_deleteOption(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	char *s1 = p_char(sfp[1]);
	int ret = MagickDeleteOption(self ,s1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.deleteImageProperty(self, String s1) */

METHOD ImageMagick_deleteImageProperty(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	char *s1 = p_char(sfp[1]);
	int ret = MagickDeleteImageProperty(self ,s1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.getAntialias(self) */

METHOD ImageMagick_getAntialias(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int ret = MagickGetAntialias(self );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.setAntialias(self, Boolean b1) */

METHOD ImageMagick_setAntialias(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int b1 = p_int(sfp[1]);
	int ret = MagickSetAntialias(self ,b1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.setCompressionQuality(self, Int i1) */

METHOD ImageMagick_setCompressionQuality(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int i1 = p_int(sfp[1]);
	int ret = MagickSetCompressionQuality(self ,i1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.setDepth(self, Int i1) */

METHOD ImageMagick_setDepth(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int i1 = p_int(sfp[1]);
	int ret = MagickSetDepth(self ,i1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.setFilename(self, String s1) */

METHOD ImageMagick_setFilename(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	char *s1 = p_char(sfp[1]);
	int ret = MagickSetFilename(self ,s1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.setFormat(self, String s1) */

METHOD ImageMagick_setFormat(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	char *s1 = p_char(sfp[1]);
	int ret = MagickSetFormat(self ,s1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.setFont(self, String s1) */

METHOD ImageMagick_setFont(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	char *s1 = p_char(sfp[1]);
	int ret = MagickSetFont(self ,s1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.setImageProperty(self, String s1, String s2) */

METHOD ImageMagick_setImageProperty(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	char *s1 = p_char(sfp[1]);
	char *s2 = p_char(sfp[2]);
	int ret = MagickSetImageProperty(self ,s1 ,s2 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.setOption(self, String s1, String s2) */

METHOD ImageMagick_setOption(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	char *s1 = p_char(sfp[1]);
	char *s2 = p_char(sfp[2]);
	int ret = MagickSetOption(self ,s1 ,s2 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.setPassphrase(self, String s1) */

METHOD ImageMagick_setPassphrase(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	char *s1 = p_char(sfp[1]);
	int ret = MagickSetPassphrase(self ,s1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.setPointsize(self, Float f1) */

METHOD ImageMagick_setPointsize(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	int ret = MagickSetPointsize(self ,f1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.setResolution(self, Float f1, Float f2) */

METHOD ImageMagick_setResolution(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	float f2 = p_float(sfp[2]);
	int ret = MagickSetResolution(self ,f1 ,f2 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.setSize(self, Int i1, Int i2) */

METHOD ImageMagick_setSize(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int i1 = p_int(sfp[1]);
	int i2 = p_int(sfp[2]);
	int ret = MagickSetSize(self ,i1 ,i2 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Int ImageMagick.getCompressionQuality(self) */

METHOD ImageMagick_getCompressionQuality(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int ret = MagickGetCompressionQuality(self );

	KNH_RETURN_Int(ctx, sfp, ret);
}

/* String ImageMagick.getImageFilename(self) */

METHOD ImageMagick_getImageFilename(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	char *ret = MagickGetImageFilename(self );

	KNH_RETURN(ctx, sfp, new_String(ctx, B(ret), NULL));
}

/* String ImageMagick.getImageFormat(self) */

METHOD ImageMagick_getImageFormat(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	char *ret = MagickGetImageFormat(self );

	KNH_RETURN(ctx, sfp, new_String(ctx, B(ret), NULL));
}

/* String ImageMagick.getImageSignature(self) */

METHOD ImageMagick_getImageSignature(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	char *ret = MagickGetImageSignature(self );

	KNH_RETURN(ctx, sfp, new_String(ctx, B(ret), NULL));
}

/* String ImageMagick.identifyImage(self) */

METHOD ImageMagick_identifyImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	char *ret = MagickIdentifyImage(self );

	KNH_RETURN(ctx, sfp, new_String(ctx, B(ret), NULL));
}

/* Float ImageMagick.getImageGamma(self) */

METHOD ImageMagick_getImageGamma(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	double ret = MagickGetImageGamma(self );

	KNH_RETURN_Float(ctx, sfp, ret);
}

/* Float ImageMagick.getImageTotalInkDensity(self) */

METHOD ImageMagick_getImageTotalInkDensity(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	double ret = MagickGetImageTotalInkDensity(self );

	KNH_RETURN_Float(ctx, sfp, ret);
}

/* Boolean ImageMagick.adaptiveBlurImage(self, Float f1, Float f2) */

METHOD ImageMagick_adaptiveBlurImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	float f2 = p_float(sfp[2]);
	int ret = MagickAdaptiveBlurImage(self ,f1 ,f2 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.adaptiveSharpenImage(self, Float f1, Float f2) */

METHOD ImageMagick_adaptiveSharpenImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	float f2 = p_float(sfp[2]);
	int ret = MagickAdaptiveSharpenImage(self ,f1 ,f2 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.animateImages(self, String s1) */

METHOD ImageMagick_animateImages(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	char *s1 = p_char(sfp[1]);
	int ret = MagickAnimateImages(self ,s1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.blurImage(self, Float f1, Float f2) */

METHOD ImageMagick_blurImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	float f2 = p_float(sfp[2]);
	int ret = MagickBlurImage(self ,f1 ,f2 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.charcoalImage(self, Float f1, Float f2) */

METHOD ImageMagick_charcoalImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	float f2 = p_float(sfp[2]);
	int ret = MagickCharcoalImage(self ,f1 ,f2 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.clipImage(self) */

METHOD ImageMagick_clipImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int ret = MagickClipImage(self );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.clipImagePath(self, String s1, Boolean b2) */

METHOD ImageMagick_clipImagePath(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	char *s1 = p_char(sfp[1]);
	int b2 = p_int(sfp[2]);
	int ret = MagickClipImagePath(self ,s1 ,b2 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.commentImage(self, String s1) */

METHOD ImageMagick_commentImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	char *s1 = p_char(sfp[1]);
	int ret = MagickCommentImage(self ,s1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.contrastImage(self, Boolean b1) */

METHOD ImageMagick_contrastImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int b1 = p_int(sfp[1]);
	int ret = MagickContrastImage(self ,b1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.contrastStretchImage(self, Float f1, Float f2) */

METHOD ImageMagick_contrastStretchImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	float f2 = p_float(sfp[2]);
	int ret = MagickContrastStretchImage(self ,f1 ,f2 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.cycleColormapImage(self, Int i1) */

METHOD ImageMagick_cycleColormapImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int i1 = p_int(sfp[1]);
	int ret = MagickCycleColormapImage(self ,i1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.despeckleImage(self) */

METHOD ImageMagick_despeckleImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int ret = MagickDespeckleImage(self );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.displayImage(self, String s1) */

METHOD ImageMagick_displayImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	char *s1 = p_char(sfp[1]);
	int ret = MagickDisplayImage(self ,s1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.displayImages(self, String s1) */

METHOD ImageMagick_displayImages(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	char *s1 = p_char(sfp[1]);
	int ret = MagickDisplayImages(self ,s1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.edgeImage(self, Float f1) */

METHOD ImageMagick_edgeImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	int ret = MagickEdgeImage(self ,f1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.embossImage(self, Float f1, Float f2) */

METHOD ImageMagick_embossImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	float f2 = p_float(sfp[2]);
	int ret = MagickEmbossImage(self ,f1 ,f2 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.enhanceImage(self) */

METHOD ImageMagick_enhanceImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int ret = MagickEnhanceImage(self );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.equalizeImage(self) */

METHOD ImageMagick_equalizeImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int ret = MagickEqualizeImage(self );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.flipImage(self) */

METHOD ImageMagick_flipImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int ret = MagickFlipImage(self );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.flopImage(self) */

METHOD ImageMagick_flopImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int ret = MagickFlopImage(self );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.gammaImage(self, Float f1) */

METHOD ImageMagick_gammaImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	int ret = MagickGammaImage(self ,f1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.gaussianBlurImage(self, Float f1, Float f2) */

METHOD ImageMagick_gaussianBlurImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	float f2 = p_float(sfp[2]);
	int ret = MagickGaussianBlurImage(self ,f1 ,f2 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.getImageMatte(self) */

METHOD ImageMagick_getImageMatte(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int ret = MagickGetImageMatte(self );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.hasNextImage(self) */

METHOD ImageMagick_hasNextImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int ret = MagickHasNextImage(self );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.hasPreviousImage(self) */

METHOD ImageMagick_hasPreviousImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int ret = MagickHasPreviousImage(self );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.implodeImage(self, Float f1) */

METHOD ImageMagick_implodeImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	int ret = MagickImplodeImage(self ,f1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.labelImage(self, String s1) */

METHOD ImageMagick_labelImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	char *s1 = p_char(sfp[1]);
	int ret = MagickLabelImage(self ,s1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.levelImage(self, Float f1, Float f2, Float f3) */

METHOD ImageMagick_levelImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	float f2 = p_float(sfp[2]);
	float f3 = p_float(sfp[3]);
	int ret = MagickLevelImage(self ,f1 ,f2 ,f3 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.linearStretchImage(self, Float f1, Float f2) */

METHOD ImageMagick_linearStretchImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	float f2 = p_float(sfp[2]);
	int ret = MagickLinearStretchImage(self ,f1 ,f2 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.magnifyImage(self) */

METHOD ImageMagick_magnifyImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int ret = MagickMagnifyImage(self );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.medianFilterImage(self, Float f1) */

METHOD ImageMagick_medianFilterImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	int ret = MagickMedianFilterImage(self ,f1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.minifyImage(self) */

METHOD ImageMagick_minifyImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int ret = MagickMinifyImage(self );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.modulateImage(self, Float f1, Float f2, Float f3) */

METHOD ImageMagick_modulateImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	float f2 = p_float(sfp[2]);
	float f3 = p_float(sfp[3]);
	int ret = MagickModulateImage(self ,f1 ,f2 ,f3 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.motionBlurImage(self, Float f1, Float f2, Float f3) */

METHOD ImageMagick_motionBlurImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	float f2 = p_float(sfp[2]);
	float f3 = p_float(sfp[3]);
	int ret = MagickMotionBlurImage(self ,f1 ,f2 ,f3 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.negateImage(self, Boolean b1) */

METHOD ImageMagick_negateImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int b1 = p_int(sfp[1]);
	int ret = MagickNegateImage(self ,b1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.nextImage(self) */

METHOD ImageMagick_nextImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int ret = MagickNextImage(self );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.normalizeImage(self) */

METHOD ImageMagick_normalizeImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int ret = MagickNormalizeImage(self );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.oilPaintImage(self, Float f1) */

METHOD ImageMagick_oilPaintImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	int ret = MagickOilPaintImage(self ,f1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.orderedPosterizeImage(self, String s1) */

METHOD ImageMagick_orderedPosterizeImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	char *s1 = p_char(sfp[1]);
	int ret = MagickOrderedPosterizeImage(self ,s1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.pingImage(self, String s1) */

METHOD ImageMagick_pingImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	char *s1 = p_char(sfp[1]);
	int ret = MagickPingImage(self ,s1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.previousImage(self) */

METHOD ImageMagick_previousImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int ret = MagickPreviousImage(self );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.radialBlurImage(self, Float f1) */

METHOD ImageMagick_radialBlurImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	int ret = MagickRadialBlurImage(self ,f1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.randomThresholdImage(self, Float f1, Float f2) */

METHOD ImageMagick_randomThresholdImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	float f2 = p_float(sfp[2]);
	int ret = MagickRandomThresholdImage(self ,f1 ,f2 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.readImage(self, String s1) */

METHOD ImageMagick_readImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	char *s1 = p_char(sfp[1]);
	int ret = MagickReadImage(self ,s1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.reduceNoiseImage(self, Float f1) */

METHOD ImageMagick_reduceNoiseImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	int ret = MagickReduceNoiseImage(self ,f1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.removeImage(self) */

METHOD ImageMagick_removeImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int ret = MagickRemoveImage(self );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.rollImage(self, Int i1, Int i2) */

METHOD ImageMagick_rollImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int i1 = p_int(sfp[1]);
	int i2 = p_int(sfp[2]);
	int ret = MagickRollImage(self ,i1 ,i2 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.sampleImage(self, Int i1, Int i2) */

METHOD ImageMagick_sampleImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int i1 = p_int(sfp[1]);
	int i2 = p_int(sfp[2]);
	int ret = MagickSampleImage(self ,i1 ,i2 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.scaleImage(self, Int i1, Int i2) */

METHOD ImageMagick_scaleImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int i1 = p_int(sfp[1]);
	int i2 = p_int(sfp[2]);
	int ret = MagickScaleImage(self ,i1 ,i2 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.sepiaToneImage(self, Float f1) */

METHOD ImageMagick_sepiaToneImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	int ret = MagickSepiaToneImage(self ,f1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.setImageBias(self, Float f1) */

METHOD ImageMagick_setImageBias(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	int ret = MagickSetImageBias(self ,f1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.setImageBluePrimary(self, Float f1, Float f2) */

METHOD ImageMagick_setImageBluePrimary(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	float f2 = p_float(sfp[2]);
	int ret = MagickSetImageBluePrimary(self ,f1 ,f2 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.setImageDelay(self, Int i1) */

METHOD ImageMagick_setImageDelay(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int i1 = p_int(sfp[1]);
	int ret = MagickSetImageDelay(self ,i1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.setImageDepth(self, Int i1) */

METHOD ImageMagick_setImageDepth(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int i1 = p_int(sfp[1]);
	int ret = MagickSetImageDepth(self ,i1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.setImageCompressionQuality(self, Int i1) */

METHOD ImageMagick_setImageCompressionQuality(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int i1 = p_int(sfp[1]);
	int ret = MagickSetImageCompressionQuality(self ,i1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.setImageGreenPrimary(self, Float f1, Float f2) */

METHOD ImageMagick_setImageGreenPrimary(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	float f2 = p_float(sfp[2]);
	int ret = MagickSetImageGreenPrimary(self ,f1 ,f2 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.setImageGamma(self, Float f1) */

METHOD ImageMagick_setImageGamma(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	int ret = MagickSetImageGamma(self ,f1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.setImageExtent(self, Int i1, Int i2) */

METHOD ImageMagick_setImageExtent(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int i1 = p_int(sfp[1]);
	int i2 = p_int(sfp[2]);
	int ret = MagickSetImageExtent(self ,i1 ,i2 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.setImageFilename(self, String s1) */

METHOD ImageMagick_setImageFilename(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	char *s1 = p_char(sfp[1]);
	int ret = MagickSetImageFilename(self ,s1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.setImageFormat(self, String s1) */

METHOD ImageMagick_setImageFormat(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	char *s1 = p_char(sfp[1]);
	int ret = MagickSetImageFormat(self ,s1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.setImageIterations(self, Int i1) */

METHOD ImageMagick_setImageIterations(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int i1 = p_int(sfp[1]);
	int ret = MagickSetImageIterations(self ,i1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.setImageMatte(self, Boolean b1) */

METHOD ImageMagick_setImageMatte(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int b1 = p_int(sfp[1]);
	int ret = MagickSetImageMatte(self ,b1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.setImageOpacity(self, Float f1) */

METHOD ImageMagick_setImageOpacity(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	int ret = MagickSetImageOpacity(self ,f1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.resetImagePage(self, String s1) */

METHOD ImageMagick_resetImagePage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	char *s1 = p_char(sfp[1]);
	int ret = MagickResetImagePage(self ,s1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.setImageRedPrimary(self, Float f1, Float f2) */

METHOD ImageMagick_setImageRedPrimary(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	float f2 = p_float(sfp[2]);
	int ret = MagickSetImageRedPrimary(self ,f1 ,f2 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.setImageResolution(self, Float f1, Float f2) */

METHOD ImageMagick_setImageResolution(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	float f2 = p_float(sfp[2]);
	int ret = MagickSetImageResolution(self ,f1 ,f2 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.setImageScene(self, Int i1) */

METHOD ImageMagick_setImageScene(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int i1 = p_int(sfp[1]);
	int ret = MagickSetImageScene(self ,i1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.setImageTicksPerSecond(self, Int i1) */

METHOD ImageMagick_setImageTicksPerSecond(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int i1 = p_int(sfp[1]);
	int ret = MagickSetImageTicksPerSecond(self ,i1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.setImageWhitePoint(self, Float f1, Float f2) */

METHOD ImageMagick_setImageWhitePoint(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	float f2 = p_float(sfp[2]);
	int ret = MagickSetImageWhitePoint(self ,f1 ,f2 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.sharpenImage(self, Float f1, Float f2) */

METHOD ImageMagick_sharpenImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	float f2 = p_float(sfp[2]);
	int ret = MagickSharpenImage(self ,f1 ,f2 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.shaveImage(self, Int i1, Int i2) */

METHOD ImageMagick_shaveImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int i1 = p_int(sfp[1]);
	int i2 = p_int(sfp[2]);
	int ret = MagickShaveImage(self ,i1 ,i2 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.sketchImage(self, Float f1, Float f2, Float f3) */

METHOD ImageMagick_sketchImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	float f2 = p_float(sfp[2]);
	float f3 = p_float(sfp[3]);
	int ret = MagickSketchImage(self ,f1 ,f2 ,f3 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.solarizeImage(self, Float f1) */

METHOD ImageMagick_solarizeImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	int ret = MagickSolarizeImage(self ,f1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.spreadImage(self, Float f1) */

METHOD ImageMagick_spreadImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	int ret = MagickSpreadImage(self ,f1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.stripImage(self) */

METHOD ImageMagick_stripImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int ret = MagickStripImage(self );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.swirlImage(self, Float f1) */

METHOD ImageMagick_swirlImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	int ret = MagickSwirlImage(self ,f1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.transposeImage(self) */

METHOD ImageMagick_transposeImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int ret = MagickTransposeImage(self );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.transverseImage(self) */

METHOD ImageMagick_transverseImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int ret = MagickTransverseImage(self );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.thresholdImage(self, Float f1) */

METHOD ImageMagick_thresholdImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	int ret = MagickThresholdImage(self ,f1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.thumbnailImage(self, Int i1, Int i2) */

METHOD ImageMagick_thumbnailImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int i1 = p_int(sfp[1]);
	int i2 = p_int(sfp[2]);
	int ret = MagickThumbnailImage(self ,i1 ,i2 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.trimImage(self, Float f1) */

METHOD ImageMagick_trimImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	int ret = MagickTrimImage(self ,f1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.uniqueImageColors(self) */

METHOD ImageMagick_uniqueImageColors(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int ret = MagickUniqueImageColors(self );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.waveImage(self, Float f1, Float f2) */

METHOD ImageMagick_waveImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	float f2 = p_float(sfp[2]);
	int ret = MagickWaveImage(self ,f1 ,f2 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.writeImage(self, String s1) */

METHOD ImageMagick_writeImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	char *s1 = p_char(sfp[1]);
	int ret = MagickWriteImage(self ,s1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.writeImages(self, String s1, Boolean b2) */

METHOD ImageMagick_writeImages(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	char *s1 = p_char(sfp[1]);
	int b2 = p_int(sfp[2]);
	int ret = MagickWriteImages(self ,s1 ,b2 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* ImageMagick ImageMagick.appendImages(self, Boolean b1) */

METHOD ImageMagick_appendImages(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int b1 = p_int(sfp[1]);
	MagickWand *ret = MagickAppendImages(self ,b1 );

}

/* ImageMagick ImageMagick.averageImages(self) */

METHOD ImageMagick_averageImages(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	MagickWand *ret = MagickAverageImages(self );

}

/* ImageMagick ImageMagick.coalesceImages(self) */

METHOD ImageMagick_coalesceImages(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	MagickWand *ret = MagickCoalesceImages(self );

}

/* ImageMagick ImageMagick.deconstructImages(self) */

METHOD ImageMagick_deconstructImages(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	MagickWand *ret = MagickDeconstructImages(self );

}

/* ImageMagick ImageMagick.fxImage(self, String s1) */

METHOD ImageMagick_fxImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	char *s1 = p_char(sfp[1]);
	MagickWand *ret = MagickFxImage(self ,s1 );

}

/* ImageMagick ImageMagick.getImage(self) */

METHOD ImageMagick_getImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	MagickWand *ret = MagickGetImage(self );

}

/* ImageMagick ImageMagick.getImageClipMask(self) */

METHOD ImageMagick_getImageClipMask(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	MagickWand *ret = MagickGetImageClipMask(self );

}

/* ImageMagick ImageMagick.morphImages(self, Int i1) */

METHOD ImageMagick_morphImages(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int i1 = p_int(sfp[1]);
	MagickWand *ret = MagickMorphImages(self ,i1 );

}

/* ImageMagick ImageMagick.optimizeImageLayers(self) */

METHOD ImageMagick_optimizeImageLayers(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	MagickWand *ret = MagickOptimizeImageLayers(self );

}

/* ImageMagick ImageMagick.transformImage(self, String s1, String s2) */

METHOD ImageMagick_transformImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	char *s1 = p_char(sfp[1]);
	char *s2 = p_char(sfp[2]);
	MagickWand *ret = MagickTransformImage(self ,s1 ,s2 );

}

/* Int ImageMagick.getImageColors(self) */

METHOD ImageMagick_getImageColors(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int ret = MagickGetImageColors(self );

	KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int ImageMagick.getImageCompressionQuality(self) */

METHOD ImageMagick_getImageCompressionQuality(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int ret = MagickGetImageCompressionQuality(self );

	KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int ImageMagick.getImageDelay(self) */

METHOD ImageMagick_getImageDelay(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int ret = MagickGetImageDelay(self );

	KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int ImageMagick.getImageDepth(self) */

METHOD ImageMagick_getImageDepth(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int ret = MagickGetImageDepth(self );

	KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int ImageMagick.getImageHeight(self) */

METHOD ImageMagick_getImageHeight(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int ret = MagickGetImageHeight(self );

	KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int ImageMagick.getImageIterations(self) */

METHOD ImageMagick_getImageIterations(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int ret = MagickGetImageIterations(self );

	KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int ImageMagick.getImageScene(self) */

METHOD ImageMagick_getImageScene(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int ret = MagickGetImageScene(self );

	KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int ImageMagick.getImageTicksPerSecond(self) */

METHOD ImageMagick_getImageTicksPerSecond(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int ret = MagickGetImageTicksPerSecond(self );

	KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int ImageMagick.getImageWidth(self) */

METHOD ImageMagick_getImageWidth(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int ret = MagickGetImageWidth(self );

	KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int ImageMagick.getNumberImages(self) */

METHOD ImageMagick_getNumberImages(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int ret = MagickGetNumberImages(self );

	KNH_RETURN_Int(ctx, sfp, ret);
}

/* Int ImageMagick.getIteratorIndex(self) */

METHOD ImageMagick_getIteratorIndex(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int ret = MagickGetIteratorIndex(self );

	KNH_RETURN_Int(ctx, sfp, ret);
}

/* Boolean ImageMagick.clearException(self) */

METHOD ImageMagick_clearException(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int ret = MagickClearException(self );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean ImageMagick.setIteratorIndex(self, Int i1) */

METHOD ImageMagick_setIteratorIndex(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int i1 = p_int(sfp[1]);
	int ret = MagickSetIteratorIndex(self ,i1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* void ImageMagick.wandGenesis() */

METHOD ImageMagick_wandGenesis(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWandGenesis();

	KNH_RETURN_void(ctx, sfp);
}

/* void ImageMagick.wandTerminus() */

METHOD ImageMagick_wandTerminus(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWandTerminus();

	KNH_RETURN_void(ctx, sfp);
}

/* void ImageMagick.resetIterator(self) */

METHOD ImageMagick_resetIterator(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	MagickResetIterator(self );

	KNH_RETURN_void(ctx, sfp);
}

/* void ImageMagick.setFirstIterator(self) */

METHOD ImageMagick_setFirstIterator(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	MagickSetFirstIterator(self );

	KNH_RETURN_void(ctx, sfp);
}

/* void ImageMagick.setLastIterator(self) */

METHOD ImageMagick_setLastIterator(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	MagickSetLastIterator(self );

	KNH_RETURN_void(ctx, sfp);
}


METHOD ImageMagick_new(Ctx *ctx, knh_sfp_t* sfp)
{
  knh_Glue_t *glue = sfp[0].glue;
  MagickWandGenesis();
  glue->ptr = (void *)NewMagickWand();
  KNH_RETURN(ctx, sfp, sfp[0].o);
}
