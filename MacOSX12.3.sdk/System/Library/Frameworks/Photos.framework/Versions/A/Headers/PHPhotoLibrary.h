//
//  PHPhotoLibrary.h
//  Photos
//
//  Copyright (c) 2013 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Photos/PhotosTypes.h>

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE_BEGIN(macos(10.13), ios(8), tvos(10))

@class PHChange;
@class PHPhotoLibrary;

typedef NS_ENUM(NSInteger, PHAuthorizationStatus) {
    PHAuthorizationStatusNotDetermined = 0, // User has not yet made a choice with regards to this application
    PHAuthorizationStatusRestricted,        // This application is not authorized to access photo data.
                                            // The user cannot change this application’s status, possibly due to active restrictions
                                            //   such as parental controls being in place.
    PHAuthorizationStatusDenied,            // User has explicitly denied this application access to photos data.
    PHAuthorizationStatusAuthorized,        // User has authorized this application to access photos data.
    PHAuthorizationStatusLimited API_AVAILABLE(ios(14)), // User has authorized this application for limited photo library access. Add PHPhotoLibraryPreventAutomaticLimitedAccessAlert = YES to the application's Info.plist to prevent the automatic alert to update the users limited library selection. Use -[PHPhotoLibrary(PhotosUISupport) presentLimitedLibraryPickerFromViewController:] from PhotosUI/PHPhotoLibrary+PhotosUISupport.h to manually present the limited library picker.
};

typedef NS_ENUM(NSInteger, PHAccessLevel) {
    PHAccessLevelAddOnly = 1,
    PHAccessLevelReadWrite = 2,
} API_AVAILABLE(macos(11.0), ios(14), tvos(14));


#pragma mark -
@protocol PHPhotoLibraryChangeObserver <NSObject>
// This callback is invoked on an arbitrary serial queue. If you need this to be handled on a specific queue, you should redispatch appropriately
- (void)photoLibraryDidChange:(PHChange *)changeInstance;

@end

#pragma mark -
API_AVAILABLE(macos(10.15), ios(13), tvos(13))
@protocol PHPhotoLibraryAvailabilityObserver <NSObject>
// This notification is posted on a private queue.
- (void)photoLibraryDidBecomeUnavailable:(PHPhotoLibrary *)photoLibrary API_AVAILABLE(macos(10.15), ios(13), tvos(13));
@end

/*!
 @class        PHPhotoLibrary
 @abstract     A PHPhotoLibrary provides access to the metadata and image data for the photos, videos and related content in the user's photo library, including content from the Camera Roll, iCloud Shared, Photo Stream, imported, and synced from iTunes.
 @discussion   ...
 */
#pragma mark -
OS_EXPORT
@interface PHPhotoLibrary : NSObject

+ (PHPhotoLibrary *)sharedPhotoLibrary;

#pragma mark - Library access authorization status

/// Replaces \c +authorizationStatus to support add-only/read-write access level status
+ (PHAuthorizationStatus)authorizationStatusForAccessLevel:(PHAccessLevel)accessLevel API_AVAILABLE(macosx(11.0), ios(14), tvos(14));
+ (void)requestAuthorizationForAccessLevel:(PHAccessLevel)accessLevel handler:(void(^)(PHAuthorizationStatus status))handler API_AVAILABLE(macosx(11.0), ios(14), tvos(14)) NS_SWIFT_ASYNC(2);

/// Deprecated and replaced by authorizationStatusForAccessLevel:, will return \c PHAuthorizationStatusAuthorized if the user has chosen limited photo library access
+ (PHAuthorizationStatus)authorizationStatus API_DEPRECATED_WITH_REPLACEMENT("+authorizationStatusForAccessLevel:", ios(8, API_TO_BE_DEPRECATED), macos(10.13, API_TO_BE_DEPRECATED), tvos(10, API_TO_BE_DEPRECATED));
+ (void)requestAuthorization:(void(^)(PHAuthorizationStatus status))handler API_DEPRECATED_WITH_REPLACEMENT("+requestAuthorizationForAccessLevel:handler:", ios(8, API_TO_BE_DEPRECATED), macos(10.13, API_TO_BE_DEPRECATED), tvos(10, API_TO_BE_DEPRECATED));

#pragma mark - Library availability

@property (readonly, atomic, nullable, strong) NSError *unavailabilityReason API_AVAILABLE(macos(10.15), ios(13), tvos(13));

- (void)registerAvailabilityObserver:(id<PHPhotoLibraryAvailabilityObserver>)observer API_AVAILABLE(macos(10.15), ios(13), tvos(13));
- (void)unregisterAvailabilityObserver:(id<PHPhotoLibraryAvailabilityObserver>)observer API_AVAILABLE(macos(10.15), ios(13), tvos(13));

#pragma mark - Applying Changes

// handlers are invoked on an arbitrary serial queue
// Nesting change requests will throw an exception
- (void)performChanges:(dispatch_block_t)changeBlock completionHandler:(nullable void(^)(BOOL success, NSError *__nullable error))completionHandler NS_SWIFT_ASYNC_THROWS_ON_FALSE(1);
- (BOOL)performChangesAndWait:(dispatch_block_t)changeBlock error:(NSError *__autoreleasing *)error;

#pragma mark - Change Handling

- (void)registerChangeObserver:(id<PHPhotoLibraryChangeObserver>)observer;
- (void)unregisterChangeObserver:(id<PHPhotoLibraryChangeObserver>)observer;

@end

API_AVAILABLE_END
NS_ASSUME_NONNULL_END
