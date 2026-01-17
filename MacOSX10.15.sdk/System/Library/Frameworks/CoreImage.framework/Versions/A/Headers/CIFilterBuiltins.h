
#if TARGET_OS_OSX || TARGET_OS_IOS || TARGET_OS_TV

#import <CoreImage/CIFilter.h>
@class CIVector;
@class CIColor;
@class CIBarcodeDescriptor;
@class MLModel;

NS_ASSUME_NONNULL_BEGIN

// CICategoryGradient
@protocol CIGaussianGradient <CIFilter>
  @property (nonatomic) CGPoint center;
  @property (nonatomic, retain) CIColor *color0;
  @property (nonatomic, retain) CIColor *color1;
  @property (nonatomic) float radius;
@end
@protocol CIHueSaturationValueGradient <CIFilter>
  @property (nonatomic) float value;
  @property (nonatomic) float radius;
  @property (nonatomic) float softness;
  @property (nonatomic) float dither;
  @property (nonatomic, nullable) CGColorSpaceRef colorSpace;
@end
@protocol CILinearGradient <CIFilter>
  @property (nonatomic) CGPoint point0;
  @property (nonatomic) CGPoint point1;
  @property (nonatomic, retain) CIColor *color0;
  @property (nonatomic, retain) CIColor *color1;
@end
@protocol CIRadialGradient <CIFilter>
  @property (nonatomic) CGPoint center;
  @property (nonatomic) float radius0;
  @property (nonatomic) float radius1;
  @property (nonatomic, retain) CIColor *color0;
  @property (nonatomic, retain) CIColor *color1;
@end
@protocol CISmoothLinearGradient <CIFilter>
  @property (nonatomic) CGPoint point0;
  @property (nonatomic) CGPoint point1;
  @property (nonatomic, retain) CIColor *color0;
  @property (nonatomic, retain) CIColor *color1;
@end

// CICategorySharpen
@protocol CISharpenLuminance <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic) float sharpness;
  @property (nonatomic) float radius;
@end
@protocol CIUnsharpMask <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic) float radius;
  @property (nonatomic) float intensity;
@end

// CICategoryHalftoneEffect
@protocol CICircularScreen <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic) CGPoint center;
  @property (nonatomic) float width;
  @property (nonatomic) float sharpness;
@end
@protocol CICMYKHalftone <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic) CGPoint center;
  @property (nonatomic) float width;
  @property (nonatomic) float angle;
  @property (nonatomic) float sharpness;
  @property (nonatomic) float grayComponentReplacement;
  @property (nonatomic) float underColorRemoval;
@end
@protocol CIDotScreen <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic) CGPoint center;
  @property (nonatomic) float angle;
  @property (nonatomic) float width;
  @property (nonatomic) float sharpness;
@end
@protocol CIHatchedScreen <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic) CGPoint center;
  @property (nonatomic) float angle;
  @property (nonatomic) float width;
  @property (nonatomic) float sharpness;
@end
@protocol CILineScreen <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic) CGPoint center;
  @property (nonatomic) float angle;
  @property (nonatomic) float width;
  @property (nonatomic) float sharpness;
@end

// CICategoryGeometryAdjustment
@protocol CIFourCoordinateGeometryFilter <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic) CGPoint topLeft;
  @property (nonatomic) CGPoint topRight;
  @property (nonatomic) CGPoint bottomRight;
  @property (nonatomic) CGPoint bottomLeft;
@end
@protocol CIBicubicScaleTransform <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic) float scale;
  @property (nonatomic) float aspectRatio;
  @property (nonatomic) float parameterB;
  @property (nonatomic) float parameterC;
@end
@protocol CIEdgePreserveUpsample <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic, retain, nullable) CIImage *smallImage;
  @property (nonatomic) float spatialSigma;
  @property (nonatomic) float lumaSigma;
@end
@protocol CIKeystoneCorrectionCombined <CIFourCoordinateGeometryFilter>
  @property (nonatomic) float focalLength;
@end
@protocol CIKeystoneCorrectionHorizontal <CIFourCoordinateGeometryFilter>
  @property (nonatomic) float focalLength;
@end
@protocol CIKeystoneCorrectionVertical <CIFourCoordinateGeometryFilter>
  @property (nonatomic) float focalLength;
@end
@protocol CILanczosScaleTransform <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic) float scale;
  @property (nonatomic) float aspectRatio;
@end
@protocol CIPerspectiveCorrection <CIFourCoordinateGeometryFilter>
  @property (nonatomic) bool crop;
@end
@protocol CIPerspectiveRotate <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic) float focalLength;
  @property (nonatomic) float pitch;
  @property (nonatomic) float yaw;
  @property (nonatomic) float roll;
@end
@protocol CIPerspectiveTransform <CIFourCoordinateGeometryFilter>
@end
@protocol CIPerspectiveTransformWithExtent <CIFourCoordinateGeometryFilter>
  @property (nonatomic) CGRect extent;
@end
@protocol CIStraighten <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic) float angle;
@end

// CICategoryTransition
@protocol CITransitionFilter <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic, retain, nullable) CIImage *targetImage;
  @property (nonatomic) float time;
@end
@protocol CIAccordionFoldTransition <CITransitionFilter>
  @property (nonatomic) float bottomHeight;
  @property (nonatomic) float numberOfFolds;
  @property (nonatomic) float foldShadowAmount;
@end
@protocol CIBarsSwipeTransition <CITransitionFilter>
  @property (nonatomic) float angle;
  @property (nonatomic) float width;
  @property (nonatomic) float barOffset;
@end
@protocol CICopyMachineTransition <CITransitionFilter>
  @property (nonatomic) CGRect extent;
  @property (nonatomic, retain) CIColor *color;
  @property (nonatomic) float angle;
  @property (nonatomic) float width;
  @property (nonatomic) float opacity;
@end
@protocol CIDisintegrateWithMaskTransition <CITransitionFilter>
  @property (nonatomic, retain, nullable) CIImage *maskImage;
  @property (nonatomic) float shadowRadius;
  @property (nonatomic) float shadowDensity;
  @property (nonatomic) CGPoint shadowOffset;
@end
@protocol CIDissolveTransition <CITransitionFilter>
@end
@protocol CIFlashTransition <CITransitionFilter>
  @property (nonatomic) CGPoint center;
  @property (nonatomic) CGRect extent;
  @property (nonatomic, retain) CIColor *color;
  @property (nonatomic) float maxStriationRadius;
  @property (nonatomic) float striationStrength;
  @property (nonatomic) float striationContrast;
  @property (nonatomic) float fadeThreshold;
@end
@protocol CIModTransition <CITransitionFilter>
  @property (nonatomic) CGPoint center;
  @property (nonatomic) float angle;
  @property (nonatomic) float radius;
  @property (nonatomic) float compression;
@end
@protocol CIPageCurlTransition <CITransitionFilter>
  @property (nonatomic, retain, nullable) CIImage *backsideImage;
  @property (nonatomic, retain, nullable) CIImage *shadingImage;
  @property (nonatomic) CGRect extent;
  @property (nonatomic) float angle;
  @property (nonatomic) float radius;
@end
@protocol CIPageCurlWithShadowTransition <CITransitionFilter>
  @property (nonatomic, retain, nullable) CIImage *backsideImage;
  @property (nonatomic) CGRect extent;
  @property (nonatomic) float angle;
  @property (nonatomic) float radius;
  @property (nonatomic) float shadowSize;
  @property (nonatomic) float shadowAmount;
  @property (nonatomic) CGRect shadowExtent;
@end
@protocol CIRippleTransition <CITransitionFilter>
  @property (nonatomic, retain, nullable) CIImage *shadingImage;
  @property (nonatomic) CGPoint center;
  @property (nonatomic) CGRect extent;
  @property (nonatomic) float width;
  @property (nonatomic) float scale;
@end
@protocol CISwipeTransition <CITransitionFilter>
  @property (nonatomic) CGRect extent;
  @property (nonatomic, retain) CIColor *color;
  @property (nonatomic) float angle;
  @property (nonatomic) float width;
  @property (nonatomic) float opacity;
@end

// CICategoryCompositeOperation
@protocol CICompositeOperation <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic, retain, nullable) CIImage *backgroundImage;
@end

// CICategoryColorAdjustment
@protocol CIColorClamp <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic, retain) CIVector *minComponents;
  @property (nonatomic, retain) CIVector *maxComponents;
@end
@protocol CIColorControls <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic) float saturation;
  @property (nonatomic) float brightness;
  @property (nonatomic) float contrast;
@end
@protocol CIColorMatrix <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic, retain) CIVector *RVector;
  @property (nonatomic, retain) CIVector *GVector;
  @property (nonatomic, retain) CIVector *BVector;
  @property (nonatomic, retain) CIVector *AVector;
  @property (nonatomic, retain) CIVector *biasVector;
@end
@protocol CIColorPolynomial <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic, retain) CIVector *redCoefficients;
  @property (nonatomic, retain) CIVector *greenCoefficients;
  @property (nonatomic, retain) CIVector *blueCoefficients;
  @property (nonatomic, retain) CIVector *alphaCoefficients;
@end
@protocol CIDepthToDisparity <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
@end
@protocol CIDisparityToDepth <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
@end
@protocol CIExposureAdjust <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic) float EV;
@end
@protocol CIGammaAdjust <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic) float power;
@end
@protocol CIHueAdjust <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic) float angle;
@end
@protocol CILinearToSRGBToneCurve <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
@end
@protocol CISRGBToneCurveToLinear <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
@end
@protocol CITemperatureAndTint <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic, retain) CIVector *neutral;
  @property (nonatomic, retain) CIVector *targetNeutral;
@end
@protocol CIToneCurve <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic) CGPoint point0;
  @property (nonatomic) CGPoint point1;
  @property (nonatomic) CGPoint point2;
  @property (nonatomic) CGPoint point3;
  @property (nonatomic) CGPoint point4;
@end
@protocol CIVibrance <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic) float amount;
@end
@protocol CIWhitePointAdjust <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic, retain) CIColor *color;
@end

// CICategoryColorEffect
@protocol CIColorCrossPolynomial <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic, retain) CIVector *redCoefficients;
  @property (nonatomic, retain) CIVector *greenCoefficients;
  @property (nonatomic, retain) CIVector *blueCoefficients;
@end
@protocol CIColorCube <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic) float cubeDimension;
  @property (nonatomic, retain) NSData *cubeData;
@end
@protocol CIColorCubesMixedWithMask <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic, retain, nullable) CIImage *maskImage;
  @property (nonatomic) float cubeDimension;
  @property (nonatomic, retain) NSData *cube0Data;
  @property (nonatomic, retain) NSData *cube1Data;
  @property (nonatomic, nullable) CGColorSpaceRef colorSpace;
@end
@protocol CIColorCubeWithColorSpace <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic) float cubeDimension;
  @property (nonatomic, retain) NSData *cubeData;
  @property (nonatomic, nullable) CGColorSpaceRef colorSpace;
@end
@protocol CIColorCurves <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic, retain) NSData *curvesData;
  @property (nonatomic, retain) CIVector *curvesDomain;
  @property (nonatomic, nullable) CGColorSpaceRef colorSpace;
@end
@protocol CIColorInvert <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
@end
@protocol CIColorMap <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic, retain, nullable) CIImage *gradientImage;
@end
@protocol CIColorMonochrome <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic, retain) CIColor *color;
  @property (nonatomic) float intensity;
@end
@protocol CIColorPosterize <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic) float levels;
@end
@protocol CIDither <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic) float intensity;
@end
@protocol CIDocumentEnhancer <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic) float amount;
@end
@protocol CIFalseColor <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic, retain) CIColor *color0;
  @property (nonatomic, retain) CIColor *color1;
@end
@protocol CILabDeltaE <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic, retain, nullable) CIImage *image2;
@end
@protocol CIMaskToAlpha <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
@end
@protocol CIMaximumComponent <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
@end
@protocol CIMinimumComponent <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
@end
@protocol CIPaletteCentroid <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic, retain, nullable) CIImage *paletteImage;
  @property (nonatomic) bool perceptual;
@end
@protocol CIPalettize <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic, retain, nullable) CIImage *paletteImage;
  @property (nonatomic) bool perceptual;
@end
@protocol CIPhotoEffect <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
@end
@protocol CISepiaTone <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic) float intensity;
@end
@protocol CIThermal <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
@end
@protocol CIVignette <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic) float intensity;
  @property (nonatomic) float radius;
@end
@protocol CIVignetteEffect <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic) CGPoint center;
  @property (nonatomic) float radius;
  @property (nonatomic) float intensity;
  @property (nonatomic) float falloff;
@end
@protocol CIXRay <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
@end

// CICategoryTileEffect
@protocol CIAffineClamp <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic) CGAffineTransform transform;
@end
@protocol CIAffineTile <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic) CGAffineTransform transform;
@end
@protocol CIEightfoldReflectedTile <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic) CGPoint center;
  @property (nonatomic) float angle;
  @property (nonatomic) float width;
@end
@protocol CIFourfoldReflectedTile <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic) CGPoint center;
  @property (nonatomic) float angle;
  @property (nonatomic) float width;
  @property (nonatomic) float acuteAngle;
@end
@protocol CIFourfoldRotatedTile <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic) CGPoint center;
  @property (nonatomic) float angle;
  @property (nonatomic) float width;
@end
@protocol CIFourfoldTranslatedTile <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic) CGPoint center;
  @property (nonatomic) float angle;
  @property (nonatomic) float width;
  @property (nonatomic) float acuteAngle;
@end
@protocol CIGlideReflectedTile <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic) CGPoint center;
  @property (nonatomic) float angle;
  @property (nonatomic) float width;
@end
@protocol CIKaleidoscope <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic) NSInteger count;
  @property (nonatomic) CGPoint center;
  @property (nonatomic) float angle;
@end
@protocol CIOpTile <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic) CGPoint center;
  @property (nonatomic) float scale;
  @property (nonatomic) float angle;
  @property (nonatomic) float width;
@end
@protocol CIParallelogramTile <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic) CGPoint center;
  @property (nonatomic) float angle;
  @property (nonatomic) float acuteAngle;
  @property (nonatomic) float width;
@end
@protocol CIPerspectiveTile <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic) CGPoint topLeft;
  @property (nonatomic) CGPoint topRight;
  @property (nonatomic) CGPoint bottomRight;
  @property (nonatomic) CGPoint bottomLeft;
@end
@protocol CISixfoldReflectedTile <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic) CGPoint center;
  @property (nonatomic) float angle;
  @property (nonatomic) float width;
@end
@protocol CISixfoldRotatedTile <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic) CGPoint center;
  @property (nonatomic) float angle;
  @property (nonatomic) float width;
@end
@protocol CITriangleKaleidoscope <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic) CGPoint point;
  @property (nonatomic) float size;
  @property (nonatomic) float rotation;
  @property (nonatomic) float decay;
@end
@protocol CITriangleTile <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic) CGPoint center;
  @property (nonatomic) float angle;
  @property (nonatomic) float width;
@end
@protocol CITwelvefoldReflectedTile <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic) CGPoint center;
  @property (nonatomic) float angle;
  @property (nonatomic) float width;
@end

// CICategoryGenerator
@protocol CIAttributedTextImageGenerator <CIFilter>
  @property (nonatomic, retain) NSAttributedString *text;
  @property (nonatomic) float scaleFactor;
@end
@protocol CIAztecCodeGenerator <CIFilter>
  @property (nonatomic, retain) NSData *message;
  @property (nonatomic) float correctionLevel;
  @property (nonatomic) float layers;
  @property (nonatomic) float compactStyle;
@end
@protocol CIBarcodeGenerator <CIFilter>
  @property (nonatomic, retain) CIBarcodeDescriptor *barcodeDescriptor;
@end
@protocol CICheckerboardGenerator <CIFilter>
  @property (nonatomic) CGPoint center;
  @property (nonatomic, retain) CIColor *color0;
  @property (nonatomic, retain) CIColor *color1;
  @property (nonatomic) float width;
  @property (nonatomic) float sharpness;
@end
@protocol CICode128BarcodeGenerator <CIFilter>
  @property (nonatomic, retain) NSData *message;
  @property (nonatomic) float quietSpace;
  @property (nonatomic) float barcodeHeight;
@end
@protocol CILenticularHaloGenerator <CIFilter>
  @property (nonatomic) CGPoint center;
  @property (nonatomic, retain) CIColor *color;
  @property (nonatomic) float haloRadius;
  @property (nonatomic) float haloWidth;
  @property (nonatomic) float haloOverlap;
  @property (nonatomic) float striationStrength;
  @property (nonatomic) float striationContrast;
  @property (nonatomic) float time;
@end
@protocol CIMeshGenerator <CIFilter>
  @property (nonatomic) float width;
  @property (nonatomic, retain) CIColor *color;
  @property (nonatomic, retain) NSArray *mesh;
@end
@protocol CIPDF417BarcodeGenerator <CIFilter>
  @property (nonatomic, retain) NSData *message;
  @property (nonatomic) float minWidth;
  @property (nonatomic) float maxWidth;
  @property (nonatomic) float minHeight;
  @property (nonatomic) float maxHeight;
  @property (nonatomic) float dataColumns;
  @property (nonatomic) float rows;
  @property (nonatomic) float preferredAspectRatio;
  @property (nonatomic) float compactionMode;
  @property (nonatomic) float compactStyle;
  @property (nonatomic) float correctionLevel;
  @property (nonatomic) float alwaysSpecifyCompaction;
@end
@protocol CIQRCodeGenerator <CIFilter>
  @property (nonatomic, retain) NSData *message;
  @property (nonatomic, retain) NSString *correctionLevel;
@end
@protocol CIRandomGenerator <CIFilter>
@end
@protocol CIRoundedRectangleGenerator <CIFilter>
  @property (nonatomic) CGRect extent;
  @property (nonatomic) float radius;
  @property (nonatomic, retain) CIColor *color;
@end
@protocol CIStarShineGenerator <CIFilter>
  @property (nonatomic) CGPoint center;
  @property (nonatomic, retain) CIColor *color;
  @property (nonatomic) float radius;
  @property (nonatomic) float crossScale;
  @property (nonatomic) float crossAngle;
  @property (nonatomic) float crossOpacity;
  @property (nonatomic) float crossWidth;
  @property (nonatomic) float epsilon;
@end
@protocol CIStripesGenerator <CIFilter>
  @property (nonatomic) CGPoint center;
  @property (nonatomic, retain) CIColor *color0;
  @property (nonatomic, retain) CIColor *color1;
  @property (nonatomic) float width;
  @property (nonatomic) float sharpness;
@end
@protocol CISunbeamsGenerator <CIFilter>
  @property (nonatomic) CGPoint center;
  @property (nonatomic, retain) CIColor *color;
  @property (nonatomic) float sunRadius;
  @property (nonatomic) float maxStriationRadius;
  @property (nonatomic) float striationStrength;
  @property (nonatomic) float striationContrast;
  @property (nonatomic) float time;
@end
@protocol CITextImageGenerator <CIFilter>
  @property (nonatomic, retain) NSString *text;
  @property (nonatomic, retain) NSString *fontName;
  @property (nonatomic) float fontSize;
  @property (nonatomic) float scaleFactor;
@end

// CICategoryStylize
@protocol CIBlendWithMask <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic, retain, nullable) CIImage *backgroundImage;
  @property (nonatomic, retain, nullable) CIImage *maskImage;
@end
@protocol CIBloom <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic) float radius;
  @property (nonatomic) float intensity;
@end
@protocol CIComicEffect <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
@end
@protocol CIConvolution <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic, retain) CIVector *weights;
  @property (nonatomic) float bias;
@end
@protocol CICoreMLModel <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic, retain) MLModel *model;
  @property (nonatomic) float headIndex;
  @property (nonatomic) bool softmaxNormalization;
@end
@protocol CICrystallize <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic) float radius;
  @property (nonatomic) CGPoint center;
@end
@protocol CIDepthOfField <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic) CGPoint point0;
  @property (nonatomic) CGPoint point1;
  @property (nonatomic) float saturation;
  @property (nonatomic) float unsharpMaskRadius;
  @property (nonatomic) float unsharpMaskIntensity;
  @property (nonatomic) float radius;
@end
@protocol CIEdges <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic) float intensity;
@end
@protocol CIEdgeWork <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic) float radius;
@end
@protocol CIGaborGradients <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
@end
@protocol CIGloom <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic) float radius;
  @property (nonatomic) float intensity;
@end
@protocol CIHeightFieldFromMask <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic) float radius;
@end
@protocol CIHexagonalPixellate <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic) CGPoint center;
  @property (nonatomic) float scale;
@end
@protocol CIHighlightShadowAdjust <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic) float radius;
  @property (nonatomic) float shadowAmount;
  @property (nonatomic) float highlightAmount;
@end
@protocol CILineOverlay <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic) float NRNoiseLevel;
  @property (nonatomic) float NRSharpness;
  @property (nonatomic) float edgeIntensity;
  @property (nonatomic) float threshold;
  @property (nonatomic) float contrast;
@end
@protocol CIMix <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic, retain, nullable) CIImage *backgroundImage;
  @property (nonatomic) float amount;
@end
@protocol CIPixellate <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic) CGPoint center;
  @property (nonatomic) float scale;
@end
@protocol CIPointillize <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic) float radius;
  @property (nonatomic) CGPoint center;
@end
@protocol CISaliencyMap <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
@end
@protocol CIShadedMaterial <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic, retain, nullable) CIImage *shadingImage;
  @property (nonatomic) float scale;
@end
@protocol CISpotColor <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic, retain) CIColor *centerColor1;
  @property (nonatomic, retain) CIColor *replacementColor1;
  @property (nonatomic) float closeness1;
  @property (nonatomic) float contrast1;
  @property (nonatomic, retain) CIColor *centerColor2;
  @property (nonatomic, retain) CIColor *replacementColor2;
  @property (nonatomic) float closeness2;
  @property (nonatomic) float contrast2;
  @property (nonatomic, retain) CIColor *centerColor3;
  @property (nonatomic, retain) CIColor *replacementColor3;
  @property (nonatomic) float closeness3;
  @property (nonatomic) float contrast3;
@end
@protocol CISpotLight <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic, retain) CIVector *lightPosition;
  @property (nonatomic, retain) CIVector *lightPointsAt;
  @property (nonatomic) float brightness;
  @property (nonatomic) float concentration;
  @property (nonatomic, retain) CIColor *color;
@end

// CICategoryBlur
@protocol CIBokehBlur <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic) float radius;
  @property (nonatomic) float ringAmount;
  @property (nonatomic) float ringSize;
  @property (nonatomic) float softness;
@end
@protocol CIBoxBlur <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic) float radius;
@end
@protocol CIDiscBlur <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic) float radius;
@end
@protocol CIGaussianBlur <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic) float radius;
@end
@protocol CIMaskedVariableBlur <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic, retain, nullable) CIImage *mask;
  @property (nonatomic) float radius;
@end
@protocol CIMedian <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
@end
@protocol CIMorphologyGradient <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic) float radius;
@end
@protocol CIMorphologyMaximum <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic) float radius;
@end
@protocol CIMorphologyMinimum <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic) float radius;
@end
@protocol CIMorphologyRectangleMaximum <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic) float width;
  @property (nonatomic) float height;
@end
@protocol CIMorphologyRectangleMinimum <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic) float width;
  @property (nonatomic) float height;
@end
@protocol CIMotionBlur <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic) float radius;
  @property (nonatomic) float angle;
@end
@protocol CINoiseReduction <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic) float noiseLevel;
  @property (nonatomic) float sharpness;
@end
@protocol CIZoomBlur <CIFilter>
  @property (nonatomic, retain, nullable) CIImage *inputImage;
  @property (nonatomic) CGPoint center;
  @property (nonatomic) float amount;
@end


NS_CLASS_AVAILABLE(10_15, 13_0)
@interface CIFilter (Builtins)

// CICategoryGradient
+ (CIFilter<CIGaussianGradient>*) gaussianGradientFilter;
+ (CIFilter<CIHueSaturationValueGradient>*) hueSaturationValueGradientFilter;
+ (CIFilter<CILinearGradient>*) linearGradientFilter;
+ (CIFilter<CIRadialGradient>*) radialGradientFilter;
+ (CIFilter<CISmoothLinearGradient>*) smoothLinearGradientFilter;

// CICategorySharpen
+ (CIFilter<CISharpenLuminance>*) sharpenLuminanceFilter;
+ (CIFilter<CIUnsharpMask>*) unsharpMaskFilter;

// CICategoryHalftoneEffect
+ (CIFilter<CICircularScreen>*) circularScreenFilter;
+ (CIFilter<CICMYKHalftone>*) CMYKHalftone;
+ (CIFilter<CIDotScreen>*) dotScreenFilter;
+ (CIFilter<CIHatchedScreen>*) hatchedScreenFilter;
+ (CIFilter<CILineScreen>*) lineScreenFilter;

// CICategoryGeometryAdjustment
+ (CIFilter<CIBicubicScaleTransform>*) bicubicScaleTransformFilter;
+ (CIFilter<CIEdgePreserveUpsample>*) edgePreserveUpsampleFilter;
+ (CIFilter<CIKeystoneCorrectionCombined>*) keystoneCorrectionCombinedFilter;
+ (CIFilter<CIKeystoneCorrectionHorizontal>*) keystoneCorrectionHorizontalFilter;
+ (CIFilter<CIKeystoneCorrectionVertical>*) keystoneCorrectionVerticalFilter;
+ (CIFilter<CILanczosScaleTransform>*) lanczosScaleTransformFilter;
+ (CIFilter<CIPerspectiveCorrection>*) perspectiveCorrectionFilter;
+ (CIFilter<CIPerspectiveRotate>*) perspectiveRotateFilter;
+ (CIFilter<CIPerspectiveTransform>*) perspectiveTransformFilter;
+ (CIFilter<CIPerspectiveTransformWithExtent>*) perspectiveTransformWithExtentFilter;
+ (CIFilter<CIStraighten>*) straightenFilter;

// CICategoryTransition
+ (CIFilter<CIAccordionFoldTransition>*) accordionFoldTransitionFilter;
+ (CIFilter<CIBarsSwipeTransition>*) barsSwipeTransitionFilter;
+ (CIFilter<CICopyMachineTransition>*) copyMachineTransitionFilter NS_RETURNS_NOT_RETAINED;
+ (CIFilter<CIDisintegrateWithMaskTransition>*) disintegrateWithMaskTransitionFilter;
+ (CIFilter<CIDissolveTransition>*) dissolveTransitionFilter;
+ (CIFilter<CIFlashTransition>*) flashTransitionFilter;
+ (CIFilter<CIModTransition>*) modTransitionFilter;
+ (CIFilter<CIPageCurlTransition>*) pageCurlTransitionFilter;
+ (CIFilter<CIPageCurlWithShadowTransition>*) pageCurlWithShadowTransitionFilter;
+ (CIFilter<CIRippleTransition>*) rippleTransitionFilter;
+ (CIFilter<CISwipeTransition>*) swipeTransitionFilter;

// CICategoryCompositeOperation
+ (CIFilter<CICompositeOperation>*) additionCompositingFilter;
+ (CIFilter<CICompositeOperation>*) colorBlendModeFilter;
+ (CIFilter<CICompositeOperation>*) colorBurnBlendModeFilter;
+ (CIFilter<CICompositeOperation>*) colorDodgeBlendModeFilter;
+ (CIFilter<CICompositeOperation>*) darkenBlendModeFilter;
+ (CIFilter<CICompositeOperation>*) differenceBlendModeFilter;
+ (CIFilter<CICompositeOperation>*) divideBlendModeFilter;
+ (CIFilter<CICompositeOperation>*) exclusionBlendModeFilter;
+ (CIFilter<CICompositeOperation>*) hardLightBlendModeFilter;
+ (CIFilter<CICompositeOperation>*) hueBlendModeFilter;
+ (CIFilter<CICompositeOperation>*) lightenBlendModeFilter;
+ (CIFilter<CICompositeOperation>*) linearBurnBlendModeFilter;
+ (CIFilter<CICompositeOperation>*) linearDodgeBlendModeFilter;
+ (CIFilter<CICompositeOperation>*) luminosityBlendModeFilter;
+ (CIFilter<CICompositeOperation>*) maximumCompositingFilter;
+ (CIFilter<CICompositeOperation>*) minimumCompositingFilter;
+ (CIFilter<CICompositeOperation>*) multiplyBlendModeFilter;
+ (CIFilter<CICompositeOperation>*) multiplyCompositingFilter;
+ (CIFilter<CICompositeOperation>*) overlayBlendModeFilter;
+ (CIFilter<CICompositeOperation>*) pinLightBlendModeFilter;
+ (CIFilter<CICompositeOperation>*) saturationBlendModeFilter;
+ (CIFilter<CICompositeOperation>*) screenBlendModeFilter;
+ (CIFilter<CICompositeOperation>*) softLightBlendModeFilter;
+ (CIFilter<CICompositeOperation>*) sourceAtopCompositingFilter;
+ (CIFilter<CICompositeOperation>*) sourceInCompositingFilter;
+ (CIFilter<CICompositeOperation>*) sourceOutCompositingFilter;
+ (CIFilter<CICompositeOperation>*) sourceOverCompositingFilter;
+ (CIFilter<CICompositeOperation>*) subtractBlendModeFilter;

// CICategoryColorAdjustment
+ (CIFilter<CIColorClamp>*) colorClampFilter;
+ (CIFilter<CIColorControls>*) colorControlsFilter;
+ (CIFilter<CIColorMatrix>*) colorMatrixFilter;
+ (CIFilter<CIColorPolynomial>*) colorPolynomialFilter;
+ (CIFilter<CIDepthToDisparity>*) depthToDisparityFilter;
+ (CIFilter<CIDisparityToDepth>*) disparityToDepthFilter;
+ (CIFilter<CIExposureAdjust>*) exposureAdjustFilter;
+ (CIFilter<CIGammaAdjust>*) gammaAdjustFilter;
+ (CIFilter<CIHueAdjust>*) hueAdjustFilter;
+ (CIFilter<CILinearToSRGBToneCurve>*) linearToSRGBToneCurveFilter;
+ (CIFilter<CISRGBToneCurveToLinear>*) sRGBToneCurveToLinearFilter;
+ (CIFilter<CITemperatureAndTint>*) temperatureAndTintFilter;
+ (CIFilter<CIToneCurve>*) toneCurveFilter;
+ (CIFilter<CIVibrance>*) vibranceFilter;
+ (CIFilter<CIWhitePointAdjust>*) whitePointAdjustFilter;

// CICategoryColorEffect
+ (CIFilter<CIColorCrossPolynomial>*) colorCrossPolynomialFilter;
+ (CIFilter<CIColorCube>*) colorCubeFilter;
+ (CIFilter<CIColorCubesMixedWithMask>*) colorCubesMixedWithMaskFilter;
+ (CIFilter<CIColorCubeWithColorSpace>*) colorCubeWithColorSpaceFilter;
+ (CIFilter<CIColorCurves>*) colorCurvesFilter;
+ (CIFilter<CIColorInvert>*) colorInvertFilter;
+ (CIFilter<CIColorMap>*) colorMapFilter;
+ (CIFilter<CIColorMonochrome>*) colorMonochromeFilter;
+ (CIFilter<CIColorPosterize>*) colorPosterizeFilter;
+ (CIFilter<CIDither>*) ditherFilter;
+ (CIFilter<CIDocumentEnhancer>*) documentEnhancerFilter;
+ (CIFilter<CIFalseColor>*) falseColorFilter;
+ (CIFilter<CILabDeltaE>*) LabDeltaE;
+ (CIFilter<CIMaskToAlpha>*) maskToAlphaFilter;
+ (CIFilter<CIMaximumComponent>*) maximumComponentFilter;
+ (CIFilter<CIMinimumComponent>*) minimumComponentFilter;
+ (CIFilter<CIPaletteCentroid>*) paletteCentroidFilter;
+ (CIFilter<CIPalettize>*) palettizeFilter;
+ (CIFilter<CIPhotoEffect>*) photoEffectChromeFilter;
+ (CIFilter<CIPhotoEffect>*) photoEffectFadeFilter;
+ (CIFilter<CIPhotoEffect>*) photoEffectInstantFilter;
+ (CIFilter<CIPhotoEffect>*) photoEffectMonoFilter;
+ (CIFilter<CIPhotoEffect>*) photoEffectNoirFilter;
+ (CIFilter<CIPhotoEffect>*) photoEffectProcessFilter;
+ (CIFilter<CIPhotoEffect>*) photoEffectTonalFilter;
+ (CIFilter<CIPhotoEffect>*) photoEffectTransferFilter;
+ (CIFilter<CISepiaTone>*) sepiaToneFilter;
+ (CIFilter<CIThermal>*) thermalFilter;
+ (CIFilter<CIVignette>*) vignetteFilter;
+ (CIFilter<CIVignetteEffect>*) vignetteEffectFilter;
+ (CIFilter<CIXRay>*) xRayFilter;

// CICategoryTileEffect
+ (CIFilter<CIAffineClamp>*) affineClampFilter;
+ (CIFilter<CIAffineTile>*) affineTileFilter;
+ (CIFilter<CIEightfoldReflectedTile>*) eightfoldReflectedTileFilter;
+ (CIFilter<CIFourfoldReflectedTile>*) fourfoldReflectedTileFilter;
+ (CIFilter<CIFourfoldRotatedTile>*) fourfoldRotatedTileFilter;
+ (CIFilter<CIFourfoldTranslatedTile>*) fourfoldTranslatedTileFilter;
+ (CIFilter<CIGlideReflectedTile>*) glideReflectedTileFilter;
+ (CIFilter<CIKaleidoscope>*) kaleidoscopeFilter;
+ (CIFilter<CIOpTile>*) opTileFilter;
+ (CIFilter<CIParallelogramTile>*) parallelogramTileFilter;
+ (CIFilter<CIPerspectiveTile>*) perspectiveTileFilter;
+ (CIFilter<CISixfoldReflectedTile>*) sixfoldReflectedTileFilter;
+ (CIFilter<CISixfoldRotatedTile>*) sixfoldRotatedTileFilter;
+ (CIFilter<CITriangleKaleidoscope>*) triangleKaleidoscopeFilter;
+ (CIFilter<CITriangleTile>*) triangleTileFilter;
+ (CIFilter<CITwelvefoldReflectedTile>*) twelvefoldReflectedTileFilter;

// CICategoryGenerator
+ (CIFilter<CIAttributedTextImageGenerator>*) attributedTextImageGeneratorFilter;
+ (CIFilter<CIAztecCodeGenerator>*) aztecCodeGeneratorFilter;
+ (CIFilter<CIBarcodeGenerator>*) barcodeGeneratorFilter;
+ (CIFilter<CICheckerboardGenerator>*) checkerboardGeneratorFilter;
+ (CIFilter<CICode128BarcodeGenerator>*) code128BarcodeGeneratorFilter;
+ (CIFilter<CILenticularHaloGenerator>*) lenticularHaloGeneratorFilter;
+ (CIFilter<CIMeshGenerator>*) meshGeneratorFilter;
+ (CIFilter<CIPDF417BarcodeGenerator>*) PDF417BarcodeGenerator;
+ (CIFilter<CIQRCodeGenerator>*) QRCodeGenerator;
+ (CIFilter<CIRandomGenerator>*) randomGeneratorFilter;
+ (CIFilter<CIRoundedRectangleGenerator>*) roundedRectangleGeneratorFilter;
+ (CIFilter<CIStarShineGenerator>*) starShineGeneratorFilter;
+ (CIFilter<CIStripesGenerator>*) stripesGeneratorFilter;
+ (CIFilter<CISunbeamsGenerator>*) sunbeamsGeneratorFilter;
+ (CIFilter<CITextImageGenerator>*) textImageGeneratorFilter;

// CICategoryStylize
+ (CIFilter<CIBlendWithMask>*) blendWithAlphaMaskFilter;
+ (CIFilter<CIBlendWithMask>*) blendWithBlueMaskFilter;
+ (CIFilter<CIBlendWithMask>*) blendWithMaskFilter;
+ (CIFilter<CIBlendWithMask>*) blendWithRedMaskFilter;
+ (CIFilter<CIBloom>*) bloomFilter;
+ (CIFilter<CIComicEffect>*) comicEffectFilter;
+ (CIFilter<CIConvolution>*) convolution3X3Filter;
+ (CIFilter<CIConvolution>*) convolution5X5Filter;
+ (CIFilter<CIConvolution>*) convolution7X7Filter;
+ (CIFilter<CIConvolution>*) convolution9HorizontalFilter;
+ (CIFilter<CIConvolution>*) convolution9VerticalFilter;
+ (CIFilter<CICoreMLModel>*) coreMLModelFilter;
+ (CIFilter<CICrystallize>*) crystallizeFilter;
+ (CIFilter<CIDepthOfField>*) depthOfFieldFilter;
+ (CIFilter<CIEdges>*) edgesFilter;
+ (CIFilter<CIEdgeWork>*) edgeWorkFilter;
+ (CIFilter<CIGaborGradients>*) gaborGradientsFilter;
+ (CIFilter<CIGloom>*) gloomFilter;
+ (CIFilter<CIHeightFieldFromMask>*) heightFieldFromMaskFilter;
+ (CIFilter<CIHexagonalPixellate>*) hexagonalPixellateFilter;
+ (CIFilter<CIHighlightShadowAdjust>*) highlightShadowAdjustFilter;
+ (CIFilter<CILineOverlay>*) lineOverlayFilter;
+ (CIFilter<CIMix>*) mixFilter;
+ (CIFilter<CIPixellate>*) pixellateFilter;
+ (CIFilter<CIPointillize>*) pointillizeFilter;
+ (CIFilter<CISaliencyMap>*) saliencyMapFilter;
+ (CIFilter<CIShadedMaterial>*) shadedMaterialFilter;
+ (CIFilter<CISpotColor>*) spotColorFilter;
+ (CIFilter<CISpotLight>*) spotLightFilter;

// CICategoryBlur
+ (CIFilter<CIBokehBlur>*) bokehBlurFilter;
+ (CIFilter<CIBoxBlur>*) boxBlurFilter;
+ (CIFilter<CIDiscBlur>*) discBlurFilter;
+ (CIFilter<CIGaussianBlur>*) gaussianBlurFilter;
+ (CIFilter<CIMaskedVariableBlur>*) maskedVariableBlurFilter;
+ (CIFilter<CIMedian>*) medianFilter;
+ (CIFilter<CIMorphologyGradient>*) morphologyGradientFilter;
+ (CIFilter<CIMorphologyMaximum>*) morphologyMaximumFilter;
+ (CIFilter<CIMorphologyMinimum>*) morphologyMinimumFilter;
+ (CIFilter<CIMorphologyRectangleMaximum>*) morphologyRectangleMaximumFilter;
+ (CIFilter<CIMorphologyRectangleMinimum>*) morphologyRectangleMinimumFilter;
+ (CIFilter<CIMotionBlur>*) motionBlurFilter;
+ (CIFilter<CINoiseReduction>*) noiseReductionFilter;
+ (CIFilter<CIZoomBlur>*) zoomBlurFilter;

@end

NS_ASSUME_NONNULL_END

#endif // TARGET_OS_OSX || TARGET_OS_IOS || TARGET_OS_TV
