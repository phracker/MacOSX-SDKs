/* CoreGraphics - CGColorConversionInfo.h
   Copyright (c) 2016 Apple Inc.
   All rights reserved. */

#ifndef CGCOLORCONVERSIONINFO_H_
#define CGCOLORCONVERSIONINFO_H_

#include <CoreGraphics/CGBase.h>
#include <CoreFoundation/CFAvailability.h>
#include <CoreGraphics/CGColorSpace.h>
#include <CoreGraphics/CGImage.h>
#include <CoreGraphics/CGToneMapping.h>

typedef const struct CF_BRIDGED_TYPE(id) CGColorConversionInfo* CGColorConversionInfoRef;

CF_IMPLICIT_BRIDGING_ENABLED

CF_ASSUME_NONNULL_BEGIN

CG_EXTERN CFTypeID CGColorConversionInfoGetTypeID(void);

typedef CF_ENUM (uint32_t, CGColorConversionInfoTransformType) {
  kCGColorConversionTransformFromSpace = 0,
  kCGColorConversionTransformToSpace,
  kCGColorConversionTransformApplySpace
};

/* Create CGColorConversionInfoRef for converting color from `src' color space to `dst' color space
 * using kCGRenderingIntentDefault rendering intent.
 * Requirements: CG color spaces must be calibrated (no Device{Gray,RGB,CMYK}, Indexed or DeviceN are allowed).
 */

CG_EXTERN CGColorConversionInfoRef __nullable CGColorConversionInfoCreate(cg_nullable CGColorSpaceRef src, cg_nullable CGColorSpaceRef dst)
    API_AVAILABLE(macos(10.12), ios(10.0));

/* CGColorConversionInfoCreateWithOptions allows to request a specifc behavior of color conversion
 * which is consistent with CGContextDrawImageApplyingToneMapping when applying kCGToneMappingITURecommended.
 * These options include: kCGUse100nitsHLGOOTF, kCGUseBT1886ForCoreVideoGamma, kCGSkipBoostToHDR
 * and kCGUseLegacyHDREcosystem.
 * See CGContext.h and CGToneMapping.h for more details.
 */
CG_EXTERN CGColorConversionInfoRef __nullable CGColorConversionInfoCreateWithOptions(__nonnull CGColorSpaceRef src, __nonnull CGColorSpaceRef dst, CFDictionaryRef __nullable options)
API_AVAILABLE(macos(10.14.6), ios(13));

/* Create CGColorConversionInfoRef from a list of CG color spaces, transform types and rendering intents.
 * ColorSpaces are iterated from first to last. The list of triples:
 * {CGColorSpaceRef, CGColorConversionInfoTransformType, CGColorRenderingIntent} must be terminated with NULL
 * Requirements: CG color spaces must be calibrated (no Device{Gray,RGB,CMYK}, Indexed or DeviceN are allowed).
 */

CG_EXTERN CGColorConversionInfoRef __nullable CGColorConversionInfoCreateFromList
  (CFDictionaryRef __nullable options, cg_nullable CGColorSpaceRef, CGColorConversionInfoTransformType, CGColorRenderingIntent, ...)
  API_AVAILABLE(macos(10.12), ios(10.0));

CG_EXTERN CGColorConversionInfoRef __nullable CGColorConversionInfoCreateFromListWithArguments
  (CFDictionaryRef __nullable options, cg_nullable CGColorSpaceRef, CGColorConversionInfoTransformType, CGColorRenderingIntent, va_list)
  API_AVAILABLE(macos(10.13), ios(11.0));

/* CGColorConversionInfoCreateForToneMapping allows to request the specifc behavior of a color conversion
 * which is consistent with CGContextDrawImageApplyingToneMapping.
 * See CGContext.h and CGToneMapping.h for more details about CGToneMapping type and options.
 * CGColorConversionInfoCreateWithOptions will return NULL when CGColorConversionInfoRef cannot be created or no cconversion is required.
 * Headroom values are ignored when kCGToneMappingITURecommended, kCGToneMappingEXRGamma or kCGToneMappingNone methods are used.
 * Otherwise headroom values must be equal or greater 1.0f to be considered valid.
 * CGColorConversionInfoCreateForToneMapping requires that target headroom is smaller or equal source headroom to succeed, except when converting
 * SDR to HDR.
 * If CGColorConversionInfoRef cannot be created because of incorrect parameters and 'error' is a non-NULL pointer, a CFErrorRef will be returned
 * with the description explaining the reason.
 */

CG_EXTERN CGColorConversionInfoRef __nullable CGColorConversionInfoCreateForToneMapping(__nonnull CGColorSpaceRef from, float source_headroom, __nonnull CGColorSpaceRef to, float target_headroom, CGToneMapping method, CFDictionaryRef __nullable options, CFErrorRef* __nullable error) API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0));

typedef struct {
    uint32_t        version;            // current version = 0
    CGBitmapInfo    bitmapInfo;         // see CGImage.h
    size_t          bitsPerComponent;   // only 8, 10, 16 fixed, 16 bit float and 32 bit float are supported
    size_t          bitsPerPixel;
    size_t          bytesPerRow;
} CGColorBufferFormat;

/*
 * CGColorConversionInfoConvertData will use CGColorConversionInfoRef 'info' to convert 'src_data' described by 'width' (in pixels),
 * 'height' (in pixels) and 'src_format' to 'dst_data' of the same pixel size ('width', 'height') and 'dst_format'.
 * CFDictionaryRef 'options' is reserved for future use.
 * CGColorConversionInfoConvertData will return 'true' on success and 'false' on failure.
 */

CG_EXTERN bool CGColorConversionInfoConvertData(__nonnull CGColorConversionInfoRef info, size_t width, size_t height, void* __nonnull dst_data, CGColorBufferFormat dst_format, const void* __nonnull src_data, CGColorBufferFormat src_format, CFDictionaryRef __nullable options) API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0));

/* CFBooleanRef's which can be used as options to create CGColorConversionInfoRef */
CG_EXTERN const CFStringRef kCGColorConversionBlackPointCompensation API_AVAILABLE(macos(10.12), ios(10.0));

CG_EXTERN const CFStringRef kCGColorConversionTRCSize API_AVAILABLE(macos(10.13), ios(11.0));

CF_ASSUME_NONNULL_END

CF_IMPLICIT_BRIDGING_DISABLED

#endif /* CGCOLORCONVERSIONINFO_H_ */
