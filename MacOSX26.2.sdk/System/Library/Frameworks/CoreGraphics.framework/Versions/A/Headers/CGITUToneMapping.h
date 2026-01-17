/* CoreGraphics - CGITUToneMapping.h
   Copyright (c) 2024 Apple Inc.
   All rights reserved. */

#ifndef CGITUTONEMAPPING_H
#define CGITUTONEMAPPING_H

#include <CoreFoundation/CFAvailability.h>
#include <CoreGraphics/CGBase.h>

CF_IMPLICIT_BRIDGING_ENABLED

CF_ASSUME_NONNULL_BEGIN

/* kCGUse100nitsHLGOOTF allows for using HLG OOTF targeting 100 nits when converting HLG to SDR when applying kCGColorITURecommended tone mapping method */
CG_EXTERN const CFStringRef kCGUse100nitsHLGOOTF API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0));     /* The expected value is a CFBooleanRef (kCFBooleanTrue) */

/* kCGUseBT1886ForCoreVideoGamma allows for choosing BT1886 recommended gamma in lieu of CoreVideo Gamma. */
CG_EXTERN const CFStringRef kCGUseBT1886ForCoreVideoGamma API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0));     /* The expected value is a CFBooleanRef (kCFBooleanTrue) */

/* kCGSkipBoostToHDR allows for skipping linear boost when converting non-HDR content (either SDR or extended range) to HDR when applying kCGColorITURecommended tone mapping method */
CG_EXTERN const CFStringRef kCGSkipBoostToHDR API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0));     /* The expected value is a CFBooleanRef (kCFBooleanTrue) */

/* kCGUseLegacyHDREcosystem allows for choosing legacy HDR conversion functions implemented in previous versions of the OS when applying kCGColorITURecommended tone mapping method */
CG_EXTERN const CFStringRef kCGUseLegacyHDREcosystem API_AVAILABLE(macos(15.1), ios(18.1), tvos(18.1), watchos(11.1));     /* The expected value is a CFBooleanRef (kCFBooleanTrue) */

CF_ASSUME_NONNULL_END

CF_IMPLICIT_BRIDGING_DISABLED

#endif /* CGITUTONEMAPPING_H */
