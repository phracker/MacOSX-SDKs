//
//  MLModelCollectionEntry.h
//  CoreML
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreML/MLExport.h>

#import <Availability.h>
#import <AvailabilityMacros.h>
#import <AvailabilityVersions.h>

#if TARGET_OS_OSX && defined(__MAC_OS_X_VERSION_MIN_REQUIRED)
    #if (__MAC_OS_X_VERSION_MIN_REQUIRED >= 150000 /* __MAC_15_0 */)
        #define MODELCOLLECTION_SUNSET(...) API_UNAVAILABLE(macos)
    #else
        #define MODELCOLLECTION_SUNSET(...) API_DEPRECATED(__VA_ARGS__)
    #endif
#elif TARGET_OS_IOS && defined(__IPHONE_OS_VERSION_MIN_REQUIRED)
    #if (__IPHONE_OS_VERSION_MIN_REQUIRED >= 180000)
        #define MODELCOLLECTION_SUNSET(...) API_UNAVAILABLE(ios)
    #else
        #define MODELCOLLECTION_SUNSET(...) API_DEPRECATED(__VA_ARGS__)
    #endif
#elif TARGET_OS_WATCH && defined(__WATCH_OS_VERSION_MIN_REQUIRED)
    #if (__WATCH_OS_VERSION_MIN_REQUIRED >= 110000 /* __WATCHOS_11_0 */)
        #define MODELCOLLECTION_SUNSET(...) API_UNAVAILABLE(watchos)
    #else
        #define MODELCOLLECTION_SUNSET(...) API_DEPRECATED(__VA_ARGS__)
    #endif
#elif TARGET_OS_TV && defined(__TV_OS_VERSION_MIN_REQUIRED)
    #if (__TV_OS_VERSION_MIN_REQUIRED >= 180000 /* __TVOS_18_0 */)
        #define MODELCOLLECTION_SUNSET(...) API_UNAVAILABLE(tvos)
    #else
        #define MODELCOLLECTION_SUNSET(...) API_DEPRECATED(__VA_ARGS__)
    #endif
#elif TARGET_OS_VISION
    #if (__VISION_OS_VERSION_MIN_REQUIRED >= 20000 /* __VISIONOS_2_0 */)
        #define MODELCOLLECTION_SUNSET(...) API_UNAVAILABLE(visionos)
    #else
        #define MODELCOLLECTION_SUNSET(...) API_DEPRECATED(__VA_ARGS__)
    #endif
#else
    #define MODELCOLLECTION_SUNSET(...) API_UNAVAILABLE(__VA_ARGS__)
#endif

NS_ASSUME_NONNULL_BEGIN

/*!
 * MLModelCollectionEntry
 * Information about a model in a model collection.
 */
MODELCOLLECTION_SUNSET("Use Background Assets or NSURLSession instead.", macos(11.0, 14.4), ios(14.0, 17.4))
API_UNAVAILABLE(tvos, watchos)
ML_EXPORT
@interface MLModelCollectionEntry : NSObject

@property (readonly, nonatomic) NSString *modelIdentifier MODELCOLLECTION_SUNSET("Use Background Assets or NSURLSession instead.", macos(11.0, 14.4), ios(14.0, 17.4));

@property (readonly, nonatomic) NSURL *modelURL MODELCOLLECTION_SUNSET("Use Background Assets or NSURLSession instead.", macos(11.0, 14.4), ios(14.0, 17.4));

- (BOOL)isEqualToModelCollectionEntry:(MLModelCollectionEntry *)entry MODELCOLLECTION_SUNSET("Use Background Assets or NSURLSession instead.", macos(11.0, 14.4), ios(14.0, 17.4));

- (instancetype)init NS_UNAVAILABLE;

+ (id)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
