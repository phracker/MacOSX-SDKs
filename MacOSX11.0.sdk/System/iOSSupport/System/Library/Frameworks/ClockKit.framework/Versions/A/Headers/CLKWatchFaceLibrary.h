//
//  CLKWatchFaceLibrary.h
//  ClockKit
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ClockKit/CLKDefines.h>

NS_ASSUME_NONNULL_BEGIN

extern NSString * const CLKWatchFaceLibraryErrorDomain API_AVAILABLE(watchos(7.0), ios(14.0)) NS_SWIFT_NAME(CLKWatchFaceLibrary.ErrorDomain);
typedef NS_ENUM(NSInteger, CLKWatchFaceLibraryErrorCode)  {
    CLKWatchFaceLibraryErrorCodeNotFileURL = 1,
    CLKWatchFaceLibraryErrorCodeInvalidFile = 2,
    CLKWatchFaceLibraryErrorCodePermissionDenied = 3,
    CLKWatchFaceLibraryErrorCodeFaceNotAvailable = 4,
} API_AVAILABLE(watchos(7.0), ios(14.0)) NS_SWIFT_NAME(CLKWatchFaceLibrary.ErrorCode);

API_AVAILABLE(watchos(7.0), ios(14.0))
@interface CLKWatchFaceLibrary : NSObject

// Use this method to import a watch face with the given file URL.
// The completionHandler will always be called on the main thread.
- (void)addWatchFaceAtURL:(NSURL *)fileURL completionHandler:(void (^)(NSError * _Nullable))handler;

@end

NS_ASSUME_NONNULL_END

