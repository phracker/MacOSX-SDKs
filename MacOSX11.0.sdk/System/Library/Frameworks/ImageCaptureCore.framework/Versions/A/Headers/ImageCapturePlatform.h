//
//  ImageCapturePlatform.h
//  ImageCapture
//

#import <TargetConditionals.h>

#if TARGET_OS_IPHONE
    #define IMAGECAPTURE_PLATFORM_IOS
#elif ( TARGET_OS_SIMULATOR  )
    #define IMAGECAPTURE_PLATFORM_SIM
#elif ( TARGET_OS_TV  )
    #define IMAGECAPTURE_PLATFORM_TV
#else
    #define IMAGECAPTURE_PLATFORM_OSX
#endif

#if (TARGET_OS_IPHONE && !( TARGET_OS_SIMULATOR ) && !( TARGET_OS_TV ) )
    #define IMAGECAPTURE_IOS
#endif

#if (!TARGET_OS_IPHONE && ( TARGET_OS_SIMULATOR || TARGET_OS_TV ) )
    #define IMAGECAPTURE_SIM
#endif

#if ( (TARGET_OS_IPHONE || TARGET_OS_OSX ) && !TARGET_OS_SIMULATOR && !TARGET_OS_TV )
    #define IMAGECAPTURE_IOS_OSX
#endif

#if ( (TARGET_OS_IPHONE || TARGET_OS_OSX || TARGET_OS_SIMULATOR ) && !TARGET_OS_TV )
#define IMAGECAPTURE_IOS_OSX_SIM
#endif

#if (TARGET_OS_IPHONE || TARGET_OS_SIMULATOR  )
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
#define IC_AVAILABLE(args...) \
API_AVAILABLE(args)

#define IC_UNAVAILABLE(args...) \
API_UNAVAILABLE(args)

#define IC_DEPRECATED( args... )

#define IC_DEPRECATED_WITH_REPLACEMENT(msg, args... )

// External builds
#else

#define IC_AVAILABLE(args...) \
API_AVAILABLE(args)

#define IC_UNAVAILABLE(args...) \
API_UNAVAILABLE(args)

#define IC_DEPRECATED( args... ) \
API_DEPRECATED( args )

#define IC_DEPRECATED_WITH_REPLACEMENT( args... ) \
API_DEPRECATED_WITH_REPLACEMENT( args )

#endif

#if defined(IMAGECAPTURE_PLATFORM_OSX)

// macOS
#import <Cocoa/Cocoa.h>
#import <Foundation/NSGeometry.h>

#define ICPoint                                                NSPoint
#define ICRect                                                 NSRect
#define ICSize                                                 NSSize

#elif defined(IMAGECAPTURE_PLATFORM_IOS) || defined(IMAGECAPTURE_PLATFORM_SIM)

// iOS
#import <Foundation/Foundation.h>

#define ICPoint                                                CGPoint
#define ICRect                                                 CGRect
#define ICSize                                                 CGSize

#else

#error "Failure: ImageCapture -- unsupported platform"

#endif

