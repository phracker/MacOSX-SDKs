/* CoreGraphics - CGToneMapping.h
   Copyright (c) 2018-2025 Apple Inc.
   All rights reserved. */

#ifndef CGTONEMAPPING_H_
#define CGTONEMAPPING_H_

#include <CoreFoundation/CoreFoundation.h>
#include <CoreFoundation/CFAvailability.h>
#include <stdint.h>


#include <CoreGraphics/CGEXRToneMappingGamma.h>
#include <CoreGraphics/CGITUToneMapping.h>

CF_IMPLICIT_BRIDGING_ENABLED

CF_ASSUME_NONNULL_BEGIN

#ifdef __cplusplus
    extern "C" {
#endif

typedef CF_ENUM (uint32_t, CGToneMapping) {
  kCGToneMappingDefault = 0,              /* A system default method will be used */
  kCGToneMappingImageSpecificLumaScaling, /* Implements tone mapping of HDR content associated with the CGImage gain map */
  kCGToneMappingReferenceWhiteBased,      /* Implements a tone curve that preserves SDR contrast and rolls off HDR highlights */
  kCGToneMappingITURecommended,           /* Implements tone mapping based on ITU-R specifications for HDR-to-SDR and SDR-to-HDR conversions assuming mastering peak of 1000 nits */
  kCGToneMappingEXRGamma,                 /* Implements Open EXR tone mapping gamma suitable for tone mapping images in extended linear sRGB color space to SDR */
  kCGToneMappingNone                      /* Does not apply any tone mapping. Color converted values in extended color spaces will be clipped to SDR ([0.0-1.0]) range */
} API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0));

typedef struct {
    CGToneMapping method;
    CFDictionaryRef __nullable options;
} CGContentToneMappingInfo
    CF_REFINED_FOR_SWIFT
    API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));

/* Option keys and values for Preferred Dynamic Range.
 * Applicable to kCGToneMappingDefault, kCGToneMappingImageSpecificLumaScaling and kCGToneMappingReferenceWhiteBased methods.
 */

CG_EXTERN const CFStringRef __nonnull kCGPreferredDynamicRange
    CF_REFINED_FOR_SWIFT
    API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));

/* Legal values for kCGPreferredDynamicRange are the following strings. */
    CG_EXTERN const CFStringRef __nonnull kCGDynamicRangeHigh
        CF_REFINED_FOR_SWIFT
        API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));
    CG_EXTERN const CFStringRef __nonnull kCGDynamicRangeConstrained
        CF_REFINED_FOR_SWIFT
        API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));
    CG_EXTERN const CFStringRef __nonnull kCGDynamicRangeStandard
        CF_REFINED_FOR_SWIFT
        API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));

CG_EXTERN const CFStringRef __nonnull kCGContentAverageLightLevel
    CF_REFINED_FOR_SWIFT
    API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));
CG_EXTERN const CFStringRef __nonnull kCGContentAverageLightLevelNits
    CF_REFINED_FOR_SWIFT
    API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));

#ifdef __cplusplus
}   /* extern "C" */
#endif

CF_ASSUME_NONNULL_END

CF_IMPLICIT_BRIDGING_DISABLED

#endif /* CGTONEMAPPING_H_ */
