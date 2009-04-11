// struct MagickWand
class MagickWand;


Int MagickWand.getImageIndex();


String MagickWand.getFilename();
String MagickWand.getFormat();
String MagickWand.getFont();
String MagickWand.getHomeURL();
String MagickWand.getOption( String s1);
String MagickWand.queryConfigureOption(String s1);


MagickWand MagickWand.averageImages();
MagickWand MagickWand.coalesceImages();
MagickWand MagickWand.deconstructImages();
MagickWand MagickWand.fxImage( String s1);
MagickWand MagickWand.getImage();
MagickWand MagickWand.getImageClipMask();
MagickWand MagickWand.optimizeImageLayers();

Boolean MagickWand.animateImages( String s1);
Boolean MagickWand.blurImage( Float f1, Float f2);
Boolean MagickWand.charcoalImage( Float f1, Float f2);
Boolean MagickWand.clipImage();
Boolean MagickWand.commentImage( String s1);
Boolean MagickWand.contrastImage( Boolean b1);
Boolean MagickWand.contrastStretchImage( Float f1, Float f2);
Boolean MagickWand.despeckleImage();
Boolean MagickWand.displayImage( String s1);
Boolean MagickWand.displayImages( String s1);
Boolean MagickWand.edgeImage( Float f1);
Boolean MagickWand.embossImage( Float f1, Float f2);
Boolean MagickWand.enhanceImage();
Boolean MagickWand.equalizeImage();
Boolean MagickWand.flipImage();
Boolean MagickWand.gammaImage( Float f1);
Boolean MagickWand.gaussianBlurImage( Float f1, Float f2);
//Boolean MagickWand.getImageGreenPrimary( Float f1, Float f2);
Boolean MagickWand.getImageMatte();
//Boolean MagickWand.getImageRange( Float f1, Float f2);
//Boolean MagickWand.getImageRedPrimary( Float f1, Float f2);
//Boolean MagickWand.getImageResolution( Float f1, Float f2);
//Boolean MagickWand.getImageWhitePoint( Float f1, Float f2);
Boolean MagickWand.hasNextImage();
Boolean MagickWand.hasPreviousImage();
//Boolean MagickWand.labelmage( String s1);
Boolean MagickWand.linearStretchImage( Float f1, Float f2);
Boolean MagickWand.magnifyImage();
Boolean MagickWand.medianFilterImage( Float f1);
Boolean MagickWand.minifyImage();
Boolean MagickWand.modulateImage( Float f1, Float f2, Float f3);
Boolean MagickWand.motionBlurImage( Float f1, Float f2, Float f3);
Boolean MagickWand.nextImage();
Boolean MagickWand.normalizeImage();
Boolean MagickWand.oilPaintImage( Float f1);
Boolean MagickWand.orderedPosterizeImage( String s1);
Boolean MagickWand.pingImage( String s1);
Boolean MagickWand.previousImage();
Boolean MagickWand.radialBlurImage( Float f1);
Boolean MagickWand.randomThresholdImage( Float f1, Float f2);
Boolean MagickWand.readImage( String s1);
Boolean MagickWand.reduceNoiseImage( Float f1);
Boolean MagickWand.removeImage();
Boolean MagickWand.rollImage( int i1, int i2);
Boolean MagickWand.sampleImage( int i1, int i2);
Boolean MagickWand.sepiaToneImage( Float f1);
Boolean MagickWand.setImageBias( Float f1);
Boolean MagickWand.setImageBluePrimary( Float f1, Float f2);
Boolean MagickWand.setImageDelay( int i1);
Boolean MagickWand.setImageDepth( int i1);
Boolean MagickWand.setImageCompressionQuality( int i1);
Boolean MagickWand.setImageGreenPrimary( Float f1, Float f2);
Boolean MagickWand.setImageGamma( Float f1);
Boolean MagickWand.setImageExtent( int i1, int i2);
Boolean MagickWand.setImageFilename( String s1);
Boolean MagickWand.setImageFormat( String s1);
Boolean MagickWand.setImageIterations( int i1);
Boolean MagickWand.setImageMatte( Boolean b1);
Boolean MagickWand.setImageOpacity( Float f1);
Boolean MagickWand.resetImagePage( String s1);
Boolean MagickWand.setImageRedPrimary( Float f1, Float f2);
Boolean MagickWand.setImageResolution( Float f1, Float f2);
Boolean MagickWand.setImageScene( int i1);
Boolean MagickWand.setImageTicksPerSecond( int i1);
Boolean MagickWand.setImageWhitePoint( Float f1, Float f2);
Boolean MagickWand.sharpenImage( Float f1, Float f2);
Boolean MagickWand.shaveImage( int i1, int i2);
Boolean MagickWand.sketchImage( Float f1, Float f2, Float f3);
Boolean MagickWand.solarizeImage( Float f1);
Boolean MagickWand.spreadImage( Float f1);
Boolean MagickWand.stripImage();
Boolean MagickWand.swirlImage( Float f1);
Boolean MagickWand.transposeImage();
Boolean MagickWand.transverseImage();
Boolean MagickWand.thresholdImage( Float f1);
Boolean MagickWand.trimImage( Float f1);
Boolean MagickWand.uniqueImageColors();
Boolean MagickWand.waveImage( Float f1, Float f2);
Boolean MagickWand.writeImage( String s1);
Boolean MagickWand.writeImages( String s1, Boolean b1);


String MagickWand.getCopyright();
String MagickWand.getPackageName();
String MagickWand.getReleaseDate();
String MagickWand.getVersion(int f1);

Boolean MagickWand.setFont( String s1);
Boolean MagickWand.setResolution( Float f1, Float f2);
Boolean MagickWand.setSize( int f1, int f2);

String MagickWand.getImageBlob( int i1);
String MagickWand.getImagesBlob( int i1);


Float MagickWand.getPointsize();

Float MagickWand.getCompressionQuality();


MagickWand MagickWand.new();
//MagickWand MagickWand.clone();
//MagickWand MagickWand.destroy();

//void MagickWand.clear();
//void MagickWand.genesis();
//void MagickWand.terminus();
//void MagickWand.resetIterator();
//void MagickWand.setFirstIterator();
//void MagickWand.setLastIterator();



