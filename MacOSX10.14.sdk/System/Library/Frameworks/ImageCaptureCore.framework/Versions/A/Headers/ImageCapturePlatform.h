//
//  ImageCapturePlatform.h
//  ImageCapture
//

#import <TargetConditionals.h>

#if TARGET_OS_IPHONE
    #define IMAGECAPTURE_PLATFORM_IOS
#elif TARGET_OS_SIMULATOR
    #define IMAGECAPTURE_PLATFORM_SIM
#else
    #define IMAGECAPTURE_PLATFORM_OSX
#endif

#if (TARGET_OS_IPHONE && !TARGET_OS_SIMULATOR)
    #define IMAGECAPTURE_IOS
#endif

#if (!TARGET_OS_IPHONE && TARGET_OS_SIMULATOR)
    #define IMAGECAPTURE_SIM
#endif

#if ( (TARGET_OS_IPHONE || TARGET_OS_OSX ) && !TARGET_OS_SIMULATOR )
    #define IMAGECAPTURE_IOS_OSX
#endif

#if (TARGET_OS_IPHONE || TARGET_OS_SIMULATOR)
    #define IMAGECAPTURE_IOS_SIM
#endif

#ifndef IMAGECAPTURE_EXTERN
    #ifdef __cplusplus
        #define IMAGECAPTURE_EXTERN extern "C" __attribute__((visibility ("default")))
    #else
        #define IMAGECAPTURE_EXTERN extern __attribute__((visibility ("default")))
    #endif
#endif

// Deprecation &  macros
#if defined(IMAGECAPTURE_INTERNAL_BUILD)

// Suppressed macros for internal builds still implementing and testing deprecated methods
#define IMAGECAPTURE_AVAILABLE(_macIntro, _iosIntro) \
NS_AVAILABLE(_macIntro, _iosIntro)

#define IMAGECAPTURE_DEPRECATED(_macIntro, _macDep, _iosIntro, _iosDep) \
NS_AVAILABLE(_macIntro, _iosIntro)

#define IMAGECAPTURE_CLASS_AVAILABLE(_macIntro, _iosIntro) \
NS_CLASS_AVAILABLE(_macIntro, _iosIntro)

#define IMAGECAPTURE_CLASS_DEPRECATED(_macIntro, _macDep, _iosIntro, _iosDep) \
NS_CLASS_AVAILABLE(_macIntro, _iosIntro)

#define IMAGECAPTURE_ENUM_AVAILABLE(_macIntro, _iosIntro) \
NS_ENUM_AVAILABLE(_macIntro, _iosIntro)

#define IMAGECAPTURE_ENUM_DEPRECATED(_macIntro, _macDep, _iosIntro, _iosDep) \
NS_ENUM_AVAILABLE(_macIntro, _iosIntro)

// External builds
#else

#define IMAGECAPTURE_AVAILABLE(_macIntro, _iosIntro) \
NS_AVAILABLE(_macIntro, _iosIntro)

#define IMAGECAPTURE_DEPRECATED(_macIntro, _macDep, _iosIntro, _iosDep) \
NS_DEPRECATED(_macIntro, _macDep, _iosIntro, _iosDep)

#define IMAGECAPTURE_CLASS_AVAILABLE(_macIntro, _iosIntro) \
NS_CLASS_AVAILABLE(_macIntro, _iosIntro)

#define IMAGECAPTURE_CLASS_DEPRECATED(_macIntro, _macDep, _iosIntro, _iosDep) \
NS_CLASS_DEPRECATED(_macIntro, _macDep, _iosIntro, _iosDep)

#define IMAGECAPTURE_ENUM_AVAILABLE(_macIntro, _iosIntro) \
NS_ENUM_AVAILABLE(_macIntro, _iosIntro)

#define IMAGECAPTURE_ENUM_DEPRECATED(_macIntro, _macDep, _iosIntro, _iosDep) \
NS_ENUM_DEPRECATED(_macIntro, _macDep, _iosIntro, _iosDep)

#endif

#if defined(IMAGECAPTURE_PLATFORM_OSX)

// OSX Headers
#import <Cocoa/Cocoa.h>

#elif defined(IMAGECAPTURE_PLATFORM_IOS) || defined(IMAGECAPTURE_PLATFORM_SIM)

// iOS Headers
#import <Foundation/Foundation.h>

#else

#error "Failure: ImageCapture -- unsupported platform"

#endif

