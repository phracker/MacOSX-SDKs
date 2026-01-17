//
//  MediaPlayerDefines.h
//  MediaPlayer
//
//  Copyright 2008 Apple, Inc. All rights reserved.
//

#ifdef __cplusplus
#define MP_EXTERN extern "C" __attribute__((visibility ("default")))
#else
#define MP_EXTERN     extern __attribute__((visibility ("default")))
#endif

#define MP_EXTERN_CLASS                       __attribute__((visibility("default")))
#define MP_EXTERN_CLASS_AVAILABLE(version)    __attribute__((visibility("default"))) NS_CLASS_AVAILABLE(NA, version)
#define MP_EXTERN_CLASS_AVAILABLE_X(ios, mac) __attribute__((visibility("default"))) NS_CLASS_AVAILABLE(mac, ios)

#define MP_API __attribute__((visibility("default"))) __API_AVAILABLE
#define MP_DEPRECATED __attribute__((visibility("default"))) __API_DEPRECATED
#define MP_DEPRECATED_WITH_REPLACEMENT __attribute__((visibility("default"))) __API_DEPRECATED_WITH_REPLACEMENT
#define MP_UNAVAILABLE __attribute__((visibility("default"))) __API_UNAVAILABLE

#if __has_include(<AvailabilityProhibitedInternal.h>)
#define MP_API_IOS_AVAILABLE_TVOS_PROHIBITED(iosver, macosver, tvosver) MP_API(ios(iosver), tvos(tvosver), macos(macosver)) __TVOS_PROHIBITED
#define MP_API_IOS_AVAILABLE_MACOS_TVOS_PROHIBITED(iosver, macosver, tvosver) MP_API(ios(iosver), tvos(tvosver), macos(macosver)) __TVOS_PROHIBITED
#define MP_API_IOS_DEPRECATED_TVOS_PROHIBITED(iosintro, iosdep, macosintro, macosdep, tvosintro, tvosdep) \
    MP_DEPRECATED("No longer supported", ios(iosintro, iosdep), tvos(tvosintro, tvosdep), macos(macosintro, macosdep)) __TVOS_PROHIBITED
#define MP_API_IOS_DEPRECATED_MACOS_TVOS_PROHIBITED(iosintro, iosdep, macosintro, macosdep, tvosintro, tvosdep) \
    MP_DEPRECATED("No longer supported", ios(iosintro, iosdep), tvos(tvosintro, tvosdep), macos(macosintro, macosdep)) __TVOS_PROHIBITED
#define MP_API_IOS_DEPRECATED_WITH_REPLACEMENT_MACOS_TVOS_PROHIBITED(replacement, iosintro, iosdep, macosintro, macosdep, tvosintro, tvosdep) \
    MP_DEPRECATED_WITH_REPLACEMENT(replacement, ios(iosintro, iosdep), tvos(tvosintro, tvosdep), macos(macosintro, macosdep)) __TVOS_PROHIBITED
#else
#define MP_API_IOS_AVAILABLE_TVOS_PROHIBITED(iosver, macosver, tvosver) MP_API(ios(iosver), macos(macosver)) __TVOS_PROHIBITED
#define MP_API_IOS_AVAILABLE_MACOS_TVOS_PROHIBITED(iosver, macosver, tvosver) MP_API(ios(iosver)) __TVOS_PROHIBITED __OS_AVAILABILITY(macosx,unavailable)
#define MP_API_IOS_DEPRECATED_TVOS_PROHIBITED(iosintro, iosdep, macosintro, macosdep, tvosintro, tvosdep) \
    MP_DEPRECATED("No longer supported", ios(iosintro, iosdep), macos(macosintro, macosdep)) __TVOS_PROHIBITED
#define MP_API_IOS_DEPRECATED_MACOS_TVOS_PROHIBITED(iosintro, iosdep, macosintro, macosdep, tvosintro, tvosdep) \
    MP_DEPRECATED("No longer supported", ios(iosintro, iosdep)) __TVOS_PROHIBITED __OS_AVAILABILITY(macosx,unavailable)
#define MP_API_IOS_DEPRECATED_WITH_REPLACEMENT_MACOS_TVOS_PROHIBITED(replacement, iosintro, iosdep, macosintro, macosdep, tvosintro, tvosdep) \
    MP_DEPRECATED_WITH_REPLACEMENT(replacement, ios(iosintro, iosdep)) __TVOS_PROHIBITED __OS_AVAILABILITY(macosx,unavailable)
#endif
