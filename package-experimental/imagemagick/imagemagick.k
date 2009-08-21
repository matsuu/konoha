/*
 *----------------------------------------------------
 *  ImageMagick bindings for konoha
 *  version 0.1
 *  kindofbrown (c) 2009
 *  kindofbrown@users.sourceforge.net
 *----------------------------------------------------
 */

/* -----------------------------------------------------------------*/
/* Class Definition */

//class ImageMagick {
//	String filename;
//}

class ImageMagick;

/* -----------------------------------------------------------------*/
/* Getter Override */
String ImageMagick.getFilename();
String ImageMagick.getImageAttribute(String s1);
Int ImageMagick.getImageIndex();
String ImageMagick.getFormat();
String ImageMagick.getFont();
String ImageMagick.getHomeURL();
String ImageMagick.getImageProperty(String s1);


/* -----------------------------------------------------------------*/
/* Class Definition */

/* -----------------------------------------------------------------*/
/* new */

ImageMagick ImageMagick.new();


/* -----------------------------------------------------------------*/
/* ImageMagick */

/**
 * Read Image into imagemagick's buffer
 * @param filename path to input imagefile
 */
Boolean ImageMagick.readImage(String filename);

/**
 * Flip buffer image
 * @param filename path to imagefile
 */
Boolean ImageMagick.flipImage();

/**
 * Write buffer into specified filename
 * @param filename path to output imagefile
 */
Boolean ImageMagick.writeImage(String filename);

/**
 * Minify buffer image (half sized)
 */
Boolean ImageMagick.minifyImage();

/**
 * Magnify buffer image (double sized)
 */
Boolean ImageMagick.magnifyImage();

/**
 * Resize buffer image
 * @param width width of resized image
 * @param height height of resized image
 */
Boolean ImageMagick.sampleImage(Int width, Int height);
Boolean ImageMagick.scaleImage(Int width, Int height);

/*
 * Blur buffer image
 *
 */
 Boolean ImageMagick.sharpenImage(Float f1, Float f2);


/* -----------------------------------------------------------------*/
/* get attributes */



void ImageMagick.coreGenesis(String s0, Boolean b1);
void ImageMagick.coreTerminus();
String ImageMagick.toMime(String s0);
String ImageMagick.describeImage();


Boolean ImageMagick.clipPathImage(String s1, Boolean b2);
Boolean ImageMagick.setImageAttribute(String s1, String s2);
Boolean ImageMagick.setImageIndex(Int i1);
Boolean ImageMagick.setImageOption(String s1, String s2, String s3);
ImageMagick ImageMagick.flattenImages();
ImageMagick ImageMagick.mosaicImages();





String ImageMagick.getOption(String s1);
String ImageMagick.queryConfigureOption(String s0);
String ImageMagick.getCopyright();
String ImageMagick.getPackageName();
String ImageMagick.getReleaseDate();
Float ImageMagick.getPointsize();
Boolean ImageMagick.deleteOption(String s1);
Boolean ImageMagick.deleteImageProperty(String s1);
Boolean ImageMagick.getAntialias();
Boolean ImageMagick.setAntialias(Boolean b1);
Boolean ImageMagick.setCompressionQuality(Int i1);
Boolean ImageMagick.setDepth(Int i1);
Boolean ImageMagick.setFilename(String s1);
Boolean ImageMagick.setFormat(String s1);
Boolean ImageMagick.setFont(String s1);
Boolean ImageMagick.setImageProperty(String s1, String s2);
Boolean ImageMagick.setOption(String s1, String s2);
Boolean ImageMagick.setPassphrase(String s1);
Boolean ImageMagick.setPointsize(Float f1);
Boolean ImageMagick.setResolution(Float f1, Float f2);
Boolean ImageMagick.setSize(Int i1, Int i2);
Int ImageMagick.getCompressionQuality();
String ImageMagick.getImageFilename();
String ImageMagick.getImageFormat();
String ImageMagick.getImageSignature();
String ImageMagick.identifyImage();
Float ImageMagick.getImageGamma();
Float ImageMagick.getImageTotalInkDensity();
Boolean ImageMagick.adaptiveBlurImage(Float f1, Float f2);
Boolean ImageMagick.adaptiveSharpenImage(Float f1, Float f2);
Boolean ImageMagick.animateImages(String s1);
Boolean ImageMagick.blurImage(Float f1, Float f2);
Boolean ImageMagick.charcoalImage(Float f1, Float f2);
Boolean ImageMagick.clipImage();
Boolean ImageMagick.clipImagePath(String s1, Boolean b2);
Boolean ImageMagick.commentImage(String s1);
Boolean ImageMagick.contrastImage(Boolean b1);
Boolean ImageMagick.contrastStretchImage(Float f1, Float f2);
Boolean ImageMagick.cycleColormapImage(Int i1);
Boolean ImageMagick.despeckleImage();
Boolean ImageMagick.displayImage(String s1);
Boolean ImageMagick.displayImages(String s1);
Boolean ImageMagick.edgeImage(Float f1);
Boolean ImageMagick.embossImage(Float f1, Float f2);
Boolean ImageMagick.enhanceImage();
Boolean ImageMagick.equalizeImage();

Boolean ImageMagick.flopImage();
Boolean ImageMagick.gammaImage(Float f1);
Boolean ImageMagick.gaussianBlurImage(Float f1, Float f2);
Boolean ImageMagick.getImageMatte();
Boolean ImageMagick.hasNextImage();
Boolean ImageMagick.hasPreviousImage();
Boolean ImageMagick.implodeImage(Float f1);
Boolean ImageMagick.labelImage(String s1);
Boolean ImageMagick.levelImage(Float f1, Float f2, Float f3);
Boolean ImageMagick.linearStretchImage(Float f1, Float f2);

Boolean ImageMagick.medianFilterImage(Float f1);

Boolean ImageMagick.modulateImage(Float f1, Float f2, Float f3);
Boolean ImageMagick.motionBlurImage(Float f1, Float f2, Float f3);
Boolean ImageMagick.negateImage(Boolean b1);
Boolean ImageMagick.nextImage();
Boolean ImageMagick.normalizeImage();
Boolean ImageMagick.oilPaintImage(Float f1);
Boolean ImageMagick.orderedPosterizeImage(String s1);
Boolean ImageMagick.pingImage(String s1);
Boolean ImageMagick.previousImage();
Boolean ImageMagick.radialBlurImage(Float f1);
Boolean ImageMagick.randomThresholdImage(Float f1, Float f2);

Boolean ImageMagick.reduceNoiseImage(Float f1);
Boolean ImageMagick.removeImage();
Boolean ImageMagick.rollImage(Int i1, Int i2);


Boolean ImageMagick.sepiaToneImage(Float f1);
Boolean ImageMagick.setImageBias(Float f1);
Boolean ImageMagick.setImageBluePrimary(Float f1, Float f2);
Boolean ImageMagick.setImageDelay(Int i1);
Boolean ImageMagick.setImageDepth(Int i1);
Boolean ImageMagick.setImageCompressionQuality(Int i1);
Boolean ImageMagick.setImageGreenPrimary(Float f1, Float f2);
Boolean ImageMagick.setImageGamma(Float f1);
Boolean ImageMagick.setImageExtent(Int i1, Int i2);
Boolean ImageMagick.setImageFilename(String s1);
Boolean ImageMagick.setImageFormat(String s1);
Boolean ImageMagick.setImageIterations(Int i1);
Boolean ImageMagick.setImageMatte(Boolean b1);
Boolean ImageMagick.setImageOpacity(Float f1);
Boolean ImageMagick.resetImagePage(String s1);
Boolean ImageMagick.setImageRedPrimary(Float f1, Float f2);
Boolean ImageMagick.setImageResolution(Float f1, Float f2);
Boolean ImageMagick.setImageScene(Int i1);
Boolean ImageMagick.setImageTicksPerSecond(Int i1);
Boolean ImageMagick.setImageWhitePoint(Float f1, Float f2);

Boolean ImageMagick.shaveImage(Int i1, Int i2);
Boolean ImageMagick.sketchImage(Float f1, Float f2, Float f3);
Boolean ImageMagick.solarizeImage(Float f1);
Boolean ImageMagick.spreadImage(Float f1);
Boolean ImageMagick.stripImage();
Boolean ImageMagick.swirlImage(Float f1);
Boolean ImageMagick.transposeImage();
Boolean ImageMagick.transverseImage();
Boolean ImageMagick.thresholdImage(Float f1);
Boolean ImageMagick.thumbnailImage(Int i1, Int i2);
Boolean ImageMagick.trimImage(Float f1);
Boolean ImageMagick.uniqueImageColors();
Boolean ImageMagick.waveImage(Float f1, Float f2);

Boolean ImageMagick.writeImages(String s1, Boolean b2);
ImageMagick ImageMagick.appendImages(Boolean b1);
ImageMagick ImageMagick.averageImages();
ImageMagick ImageMagick.coalesceImages();
ImageMagick ImageMagick.deconstructImages();
ImageMagick ImageMagick.fxImage(String s1);
ImageMagick ImageMagick.getImage();
ImageMagick ImageMagick.getImageClipMask();
ImageMagick ImageMagick.morphImages(Int i1);
ImageMagick ImageMagick.optimizeImageLayers();
ImageMagick ImageMagick.transformImage(String s1, String s2);
Int ImageMagick.getImageColors();
Int ImageMagick.getImageCompressionQuality();
Int ImageMagick.getImageDelay();
Int ImageMagick.getImageDepth();
Int ImageMagick.getImageHeight();
Int ImageMagick.getImageIterations();
Int ImageMagick.getImageScene();
Int ImageMagick.getImageTicksPerSecond();
Int ImageMagick.getImageWidth();
Int ImageMagick.getNumberImages();
Int ImageMagick.getIteratorIndex();
Boolean ImageMagick.clearException();
Boolean ImageMagick.setIteratorIndex(Int i1);
void ImageMagick.wandGenesis();
void ImageMagick.wandTerminus();
void ImageMagick.resetIterator();
void ImageMagick.setFirstIterator();
void ImageMagick.setLastIterator();
