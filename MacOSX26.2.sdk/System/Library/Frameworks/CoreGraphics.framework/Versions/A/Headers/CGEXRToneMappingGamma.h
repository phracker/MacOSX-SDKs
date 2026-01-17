/* CoreGraphics - CGEXRToneMappingGamma.h
   Copyright (c) 21 Apple Inc.
   All rights reserved. */

#ifndef CGEXRTONEMAPPINGGAMMA_H
#define CGEXRTONEMAPPINGGAMMA_H

#include <CoreFoundation/CoreFoundation.h>
#include <CoreGraphics/CGBase.h>

CF_IMPLICIT_BRIDGING_ENABLED

CF_ASSUME_NONNULL_BEGIN

/* kCGEXRToneMappingGammaDefog allows for specifying custom defog value to override system defaults when applying kCGToneMappingEXRGamma tone mapping method */
CG_EXTERN const CFStringRef kCGEXRToneMappingGammaDefog    API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0)); /* default value: 0.0f range [0.0f, 0.01f]   */

/* kCGEXRToneMappingGammaExposure allows for specifying custom exposure value to override system defaults when applying kCGToneMappingEXRGamma tone mapping method */
CG_EXTERN const CFStringRef kCGEXRToneMappingGammaExposure API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0)); /* default value: 0.0f range [-10.0f, 10.0f] */

/* kCGEXRToneMappingGammaKneeLow allows for specifying custom "knee low" value to override system defaults when applying kCGToneMappingEXRGamma tone mapping method */
CG_EXTERN const CFStringRef kCGEXRToneMappingGammaKneeLow  API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0)); /* default value: 0.0f range [-2.85f, 3.0f]  */

/* kCGEXRToneMappingGammaKneeHigh allows for specifying custom "knee high" value to override system defaults when applying kCGToneMappingEXRGamma tone mapping method */
CG_EXTERN const CFStringRef kCGEXRToneMappingGammaKneeHigh API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0)); /* default value: 5.0f range [3.5f, 7.5f]    */

/* Return a dictionary with default options for tone mapping using EXR Gamma method */
CG_EXTERN CFDictionaryRef CGEXRToneMappingGammaGetDefaultOptions(void)
    CF_REFINED_FOR_SWIFT
    API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));

CF_ASSUME_NONNULL_END

CF_IMPLICIT_BRIDGING_DISABLED

#endif /* CGEXRTONEMAPPINGGAMMA_H */
