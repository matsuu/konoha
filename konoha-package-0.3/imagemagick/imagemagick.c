#include <konoha.h>
#include <wand/MagickWand.h>


/* Int MagickWand.getImageIndex(self) */

METHOD MagickWand_getImageIndex(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int ret = MagickGetImageIndex(self );

	KNH_RETURN_Int(ctx, sfp, ret);
}

/* String MagickWand.getFilename(self) */

METHOD MagickWand_getFilename(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	char *ret = MagickGetFilename(self );

	KNH_RETURN(ctx, sfp, new_String(ctx, B(ret), NULL));
}

/* String MagickWand.getFormat(self) */

METHOD MagickWand_getFormat(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	char *ret = MagickGetFormat(self );

	KNH_RETURN(ctx, sfp, new_String(ctx, B(ret), NULL));
}

/* String MagickWand.getFont(self) */

METHOD MagickWand_getFont(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	char *ret = MagickGetFont(self );

	KNH_RETURN(ctx, sfp, new_String(ctx, B(ret), NULL));
}

/* String MagickWand.getHomeURL() */

METHOD MagickWand_getHomeURL(Ctx *ctx, knh_sfp_t* sfp)
{
	char *ret = MagickGetHomeURL();

	KNH_RETURN(ctx, sfp, new_String(ctx, B(ret), NULL));
}

/* String MagickWand.getOption(self, String s1) */

METHOD MagickWand_getOption(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	char *s1 = p_char(sfp[1]);
	char *ret = MagickGetOption(self ,s1 );

	KNH_RETURN(ctx, sfp, new_String(ctx, B(ret), NULL));
}

/* String MagickWand.queryConfigureOption(String s1) */

METHOD MagickWand_queryConfigureOption(Ctx *ctx, knh_sfp_t* sfp)
{
	char *s1 = p_char(sfp[0]);
	char *ret = MagickQueryConfigureOption(s1 );

	KNH_RETURN(ctx, sfp, new_String(ctx, B(ret), NULL));
}

/* MagickWand MagickWand.averageImages(self) */

METHOD MagickWand_averageImages(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	MagickWand *ret = MagickAverageImages(self );

	KNH_RETURN(ctx, sfp, ret);
}

/* MagickWand MagickWand.coalesceImages(self) */

METHOD MagickWand_coalesceImages(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	MagickWand *ret = MagickCoalesceImages(self );

	KNH_RETURN(ctx, sfp, ret);
}

/* MagickWand MagickWand.deconstructImages(self) */

METHOD MagickWand_deconstructImages(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	MagickWand *ret = MagickDeconstructImages(self );

	KNH_RETURN(ctx, sfp, ret);
}

/* MagickWand MagickWand.fxImage(self, String s1) */

METHOD MagickWand_fxImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	char *s1 = p_char(sfp[1]);
	MagickWand *ret = MagickFxImage(self ,s1 );

	KNH_RETURN(ctx, sfp, ret);
}

/* MagickWand MagickWand.getImage(self) */

METHOD MagickWand_getImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	MagickWand *ret = MagickGetImage(self );

	KNH_RETURN(ctx, sfp, ret);
}

/* MagickWand MagickWand.getImageClipMask(self) */

METHOD MagickWand_getImageClipMask(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	MagickWand *ret = MagickGetImageClipMask(self );

	KNH_RETURN(ctx, sfp, ret);
}

/* MagickWand MagickWand.optimizeImageLayers(self) */

METHOD MagickWand_optimizeImageLayers(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	MagickWand *ret = MagickOptimizeImageLayers(self );

	KNH_RETURN(ctx, sfp, ret);
}

/* Boolean MagickWand.animateImages(self, String s1) */

METHOD MagickWand_animateImages(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	char *s1 = p_char(sfp[1]);
	int ret = MagickAnimateImages(self ,s1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.blurImage(self, Float f1, Float f2) */

METHOD MagickWand_blurImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	float f2 = p_float(sfp[2]);
	int ret = MagickBlurImage(self ,f1 ,f2 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.charcoalImage(self, Float f1, Float f2) */

METHOD MagickWand_charcoalImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	float f2 = p_float(sfp[2]);
	int ret = MagickCharcoalImage(self ,f1 ,f2 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.clipImage(self) */

METHOD MagickWand_clipImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int ret = MagickClipImage(self );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.commentImage(self, String s1) */

METHOD MagickWand_commentImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	char *s1 = p_char(sfp[1]);
	int ret = MagickCommentImage(self ,s1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.contrastImage(self, Boolean b1) */

METHOD MagickWand_contrastImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int b1 = p_int(sfp[1]);
	int ret = MagickContrastImage(self ,b1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.contrastStretchImage(self, Float f1, Float f2) */

METHOD MagickWand_contrastStretchImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	float f2 = p_float(sfp[2]);
	int ret = MagickContrastStretchImage(self ,f1 ,f2 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.despeckleImage(self) */

METHOD MagickWand_despeckleImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int ret = MagickDespeckleImage(self );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.displayImage(self, String s1) */

METHOD MagickWand_displayImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	char *s1 = p_char(sfp[1]);
	int ret = MagickDisplayImage(self ,s1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.displayImages(self, String s1) */

METHOD MagickWand_displayImages(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	char *s1 = p_char(sfp[1]);
	int ret = MagickDisplayImages(self ,s1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.edgeImage(self, Float f1) */

METHOD MagickWand_edgeImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	int ret = MagickEdgeImage(self ,f1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.embossImage(self, Float f1, Float f2) */

METHOD MagickWand_embossImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	float f2 = p_float(sfp[2]);
	int ret = MagickEmbossImage(self ,f1 ,f2 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.enhanceImage(self) */

METHOD MagickWand_enhanceImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int ret = MagickEnhanceImage(self );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.equalizeImage(self) */

METHOD MagickWand_equalizeImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int ret = MagickEqualizeImage(self );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.flipImage(self) */

METHOD MagickWand_flipImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int ret = MagickFlipImage(self );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.gammaImage(self, Float f1) */

METHOD MagickWand_gammaImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	int ret = MagickGammaImage(self ,f1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.gaussianBlurImage(self, Float f1, Float f2) */

METHOD MagickWand_gaussianBlurImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	float f2 = p_float(sfp[2]);
	int ret = MagickGaussianBlurImage(self ,f1 ,f2 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.getImageMatte(self) */

METHOD MagickWand_getImageMatte(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int ret = MagickGetImageMatte(self );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.hasNextImage(self) */

METHOD MagickWand_hasNextImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int ret = MagickHasNextImage(self );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.hasPreviousImage(self) */

METHOD MagickWand_hasPreviousImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int ret = MagickHasPreviousImage(self );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.linearStretchImage(self, Float f1, Float f2) */

METHOD MagickWand_linearStretchImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	float f2 = p_float(sfp[2]);
	int ret = MagickLinearStretchImage(self ,f1 ,f2 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.magnifyImage(self) */

METHOD MagickWand_magnifyImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int ret = MagickMagnifyImage(self );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.medianFilterImage(self, Float f1) */

METHOD MagickWand_medianFilterImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	int ret = MagickMedianFilterImage(self ,f1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.minifyImage(self) */

METHOD MagickWand_minifyImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int ret = MagickMinifyImage(self );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.modulateImage(self, Float f1, Float f2, Float f3) */

METHOD MagickWand_modulateImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	float f2 = p_float(sfp[2]);
	float f3 = p_float(sfp[3]);
	int ret = MagickModulateImage(self ,f1 ,f2 ,f3 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.motionBlurImage(self, Float f1, Float f2, Float f3) */

METHOD MagickWand_motionBlurImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	float f2 = p_float(sfp[2]);
	float f3 = p_float(sfp[3]);
	int ret = MagickMotionBlurImage(self ,f1 ,f2 ,f3 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.nextImage(self) */

METHOD MagickWand_nextImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int ret = MagickNextImage(self );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.normalizeImage(self) */

METHOD MagickWand_normalizeImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int ret = MagickNormalizeImage(self );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.oilPaintImage(self, Float f1) */

METHOD MagickWand_oilPaintImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	int ret = MagickOilPaintImage(self ,f1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.orderedPosterizeImage(self, String s1) */

METHOD MagickWand_orderedPosterizeImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	char *s1 = p_char(sfp[1]);
	int ret = MagickOrderedPosterizeImage(self ,s1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.pingImage(self, String s1) */

METHOD MagickWand_pingImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	char *s1 = p_char(sfp[1]);
	int ret = MagickPingImage(self ,s1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.previousImage(self) */

METHOD MagickWand_previousImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int ret = MagickPreviousImage(self );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.radialBlurImage(self, Float f1) */

METHOD MagickWand_radialBlurImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	int ret = MagickRadialBlurImage(self ,f1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.randomThresholdImage(self, Float f1, Float f2) */

METHOD MagickWand_randomThresholdImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	float f2 = p_float(sfp[2]);
	int ret = MagickRandomThresholdImage(self ,f1 ,f2 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.readImage(self, String s1) */

METHOD MagickWand_readImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	char *s1 = p_char(sfp[1]);
	int ret = MagickReadImage(self ,s1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.reduceNoiseImage(self, Float f1) */

METHOD MagickWand_reduceNoiseImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	int ret = MagickReduceNoiseImage(self ,f1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.removeImage(self) */

METHOD MagickWand_removeImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int ret = MagickRemoveImage(self );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.rollImage(self, int i1, int i2) */

METHOD MagickWand_rollImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int i1 = p_int(sfp[1]);
	int i2 = p_int(sfp[2]);
	int ret = MagickRollImage(self ,i1 ,i2 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.sampleImage(self, int i1, int i2) */

METHOD MagickWand_sampleImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int i1 = p_int(sfp[1]);
	int i2 = p_int(sfp[2]);
	int ret = MagickSampleImage(self ,i1 ,i2 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.sepiaToneImage(self, Float f1) */

METHOD MagickWand_sepiaToneImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	int ret = MagickSepiaToneImage(self ,f1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.setImageBias(self, Float f1) */

METHOD MagickWand_setImageBias(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	int ret = MagickSetImageBias(self ,f1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.setImageBluePrimary(self, Float f1, Float f2) */

METHOD MagickWand_setImageBluePrimary(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	float f2 = p_float(sfp[2]);
	int ret = MagickSetImageBluePrimary(self ,f1 ,f2 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.setImageDelay(self, int i1) */

METHOD MagickWand_setImageDelay(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int i1 = p_int(sfp[1]);
	int ret = MagickSetImageDelay(self ,i1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.setImageDepth(self, int i1) */

METHOD MagickWand_setImageDepth(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int i1 = p_int(sfp[1]);
	int ret = MagickSetImageDepth(self ,i1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.setImageCompressionQuality(self, int i1) */

METHOD MagickWand_setImageCompressionQuality(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int i1 = p_int(sfp[1]);
	int ret = MagickSetImageCompressionQuality(self ,i1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.setImageGreenPrimary(self, Float f1, Float f2) */

METHOD MagickWand_setImageGreenPrimary(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	float f2 = p_float(sfp[2]);
	int ret = MagickSetImageGreenPrimary(self ,f1 ,f2 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.setImageGamma(self, Float f1) */

METHOD MagickWand_setImageGamma(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	int ret = MagickSetImageGamma(self ,f1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.setImageExtent(self, int i1, int i2) */

METHOD MagickWand_setImageExtent(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int i1 = p_int(sfp[1]);
	int i2 = p_int(sfp[2]);
	int ret = MagickSetImageExtent(self ,i1 ,i2 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.setImageFilename(self, String s1) */

METHOD MagickWand_setImageFilename(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	char *s1 = p_char(sfp[1]);
	int ret = MagickSetImageFilename(self ,s1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.setImageFormat(self, String s1) */

METHOD MagickWand_setImageFormat(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	char *s1 = p_char(sfp[1]);
	int ret = MagickSetImageFormat(self ,s1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.setImageIterations(self, int i1) */

METHOD MagickWand_setImageIterations(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int i1 = p_int(sfp[1]);
	int ret = MagickSetImageIterations(self ,i1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.setImageMatte(self, Boolean b1) */

METHOD MagickWand_setImageMatte(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int b1 = p_int(sfp[1]);
	int ret = MagickSetImageMatte(self ,b1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.setImageOpacity(self, Float f1) */

METHOD MagickWand_setImageOpacity(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	int ret = MagickSetImageOpacity(self ,f1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.resetImagePage(self, String s1) */

METHOD MagickWand_resetImagePage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	char *s1 = p_char(sfp[1]);
	int ret = MagickResetImagePage(self ,s1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.setImageRedPrimary(self, Float f1, Float f2) */

METHOD MagickWand_setImageRedPrimary(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	float f2 = p_float(sfp[2]);
	int ret = MagickSetImageRedPrimary(self ,f1 ,f2 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.setImageResolution(self, Float f1, Float f2) */

METHOD MagickWand_setImageResolution(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	float f2 = p_float(sfp[2]);
	int ret = MagickSetImageResolution(self ,f1 ,f2 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.setImageScene(self, int i1) */

METHOD MagickWand_setImageScene(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int i1 = p_int(sfp[1]);
	int ret = MagickSetImageScene(self ,i1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.setImageTicksPerSecond(self, int i1) */

METHOD MagickWand_setImageTicksPerSecond(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int i1 = p_int(sfp[1]);
	int ret = MagickSetImageTicksPerSecond(self ,i1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.setImageWhitePoint(self, Float f1, Float f2) */

METHOD MagickWand_setImageWhitePoint(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	float f2 = p_float(sfp[2]);
	int ret = MagickSetImageWhitePoint(self ,f1 ,f2 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.sharpenImage(self, Float f1, Float f2) */

METHOD MagickWand_sharpenImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	float f2 = p_float(sfp[2]);
	int ret = MagickSharpenImage(self ,f1 ,f2 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.shaveImage(self, int i1, int i2) */

METHOD MagickWand_shaveImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int i1 = p_int(sfp[1]);
	int i2 = p_int(sfp[2]);
	int ret = MagickShaveImage(self ,i1 ,i2 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.sketchImage(self, Float f1, Float f2, Float f3) */

METHOD MagickWand_sketchImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	float f2 = p_float(sfp[2]);
	float f3 = p_float(sfp[3]);
	int ret = MagickSketchImage(self ,f1 ,f2 ,f3 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.solarizeImage(self, Float f1) */

METHOD MagickWand_solarizeImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	int ret = MagickSolarizeImage(self ,f1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.spreadImage(self, Float f1) */

METHOD MagickWand_spreadImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	int ret = MagickSpreadImage(self ,f1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.stripImage(self) */

METHOD MagickWand_stripImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int ret = MagickStripImage(self );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.swirlImage(self, Float f1) */

METHOD MagickWand_swirlImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	int ret = MagickSwirlImage(self ,f1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.transposeImage(self) */

METHOD MagickWand_transposeImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int ret = MagickTransposeImage(self );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.transverseImage(self) */

METHOD MagickWand_transverseImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int ret = MagickTransverseImage(self );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.thresholdImage(self, Float f1) */

METHOD MagickWand_thresholdImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	int ret = MagickThresholdImage(self ,f1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.trimImage(self, Float f1) */

METHOD MagickWand_trimImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	int ret = MagickTrimImage(self ,f1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.uniqueImageColors(self) */

METHOD MagickWand_uniqueImageColors(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int ret = MagickUniqueImageColors(self );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.waveImage(self, Float f1, Float f2) */

METHOD MagickWand_waveImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	float f2 = p_float(sfp[2]);
	int ret = MagickWaveImage(self ,f1 ,f2 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.writeImage(self, String s1) */

METHOD MagickWand_writeImage(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	char *s1 = p_char(sfp[1]);
	int ret = MagickWriteImage(self ,s1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.writeImages(self, String s1, Boolean b1) */

METHOD MagickWand_writeImages(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	char *s1 = p_char(sfp[1]);
	int b1 = p_int(sfp[2]);
	int ret = MagickWriteImages(self ,s1 ,b1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* String MagickWand.getCopyright() */

METHOD MagickWand_getCopyright(Ctx *ctx, knh_sfp_t* sfp)
{
	char *ret = MagickGetCopyright();

	KNH_RETURN(ctx, sfp, new_String(ctx, B(ret), NULL));
}

/* String MagickWand.getPackageName() */

METHOD MagickWand_getPackageName(Ctx *ctx, knh_sfp_t* sfp)
{
	char *ret = MagickGetPackageName();

	KNH_RETURN(ctx, sfp, new_String(ctx, B(ret), NULL));
}

/* String MagickWand.getReleaseDate() */

METHOD MagickWand_getReleaseDate(Ctx *ctx, knh_sfp_t* sfp)
{
	char *ret = MagickGetReleaseDate();

	KNH_RETURN(ctx, sfp, new_String(ctx, B(ret), NULL));
}

/* String MagickWand.getVersion(int f1) */

METHOD MagickWand_getVersion(Ctx *ctx, knh_sfp_t* sfp)
{
	int f1 = p_int(sfp[0]);
	char *ret = MagickGetVersion(f1 );

	KNH_RETURN(ctx, sfp, new_String(ctx, B(ret), NULL));
}

/* Boolean MagickWand.setFont(self, String s1) */

METHOD MagickWand_setFont(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	char *s1 = p_char(sfp[1]);
	int ret = MagickSetFont(self ,s1 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.setResolution(self, Float f1, Float f2) */

METHOD MagickWand_setResolution(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	float f1 = p_float(sfp[1]);
	float f2 = p_float(sfp[2]);
	int ret = MagickSetResolution(self ,f1 ,f2 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* Boolean MagickWand.setSize(self, int f1, int f2) */

METHOD MagickWand_setSize(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int f1 = p_int(sfp[1]);
	int f2 = p_int(sfp[2]);
	int ret = MagickSetSize(self ,f1 ,f2 );

	KNH_RETURN_Boolean(ctx, sfp, ret);
}

/* String MagickWand.getImageBlob(self, int i1) */

METHOD MagickWand_getImageBlob(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int i1 = p_int(sfp[1]);
	char *ret = MagickGetImageBlob(self ,i1 );

	KNH_RETURN(ctx, sfp, new_String(ctx, B(ret), NULL));
}

/* String MagickWand.getImagesBlob(self, int i1) */

METHOD MagickWand_getImagesBlob(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	int i1 = p_int(sfp[1]);
	char *ret = MagickGetImagesBlob(self ,i1 );

	KNH_RETURN(ctx, sfp, new_String(ctx, B(ret), NULL));
}

/* Float MagickWand.getPointsize(self) */

METHOD MagickWand_getPointsize(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	double ret = MagickGetPointsize(self );

	KNH_RETURN_Float(ctx, sfp, ret);
}

/* Float MagickWand.getCompressionQuality(self) */

METHOD MagickWand_getCompressionQuality(Ctx *ctx, knh_sfp_t* sfp)
{
	MagickWand *self =(MagickWand*)((sfp[0].glue)->ptr);
	double ret = MagickGetCompressionQuality(self );

	KNH_RETURN_Float(ctx, sfp, ret);
}


METHOD MagickWand_new(Ctx *ctx, knh_sfp_t* sfp)
{
  knh_Glue_t *glue = sfp[0].glue;
  MagickWandGenesis();
  glue->ptr = (void *)NewMagickWand();
  KNH_RETURN(ctx, sfp, sfp[0].o);
}
