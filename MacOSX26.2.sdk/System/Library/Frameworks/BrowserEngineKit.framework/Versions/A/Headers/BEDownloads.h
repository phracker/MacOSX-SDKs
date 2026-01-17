//
//  BEDownloads.h
//  BrowserEngineKit
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <Foundation/NSObject.h>

@class NSURL;
@class UTType;

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(BEDownloadMonitor.Location)
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(18.2))
API_UNAVAILABLE(macos)
API_UNAVAILABLE(watchos, tvos, visionos)
BROWSERENGINE_EXPORT
@interface BEDownloadMonitorLocation : NSObject
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
@property (readonly) NSURL* url;
@property (readonly) NSData* bookmarkData;
@end

NS_REFINED_FOR_SWIFT
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(18.2))
API_UNAVAILABLE(macos)
API_UNAVAILABLE(watchos, tvos, visionos)
BROWSERENGINE_EXPORT
@interface BEDownloadMonitor : NSObject
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

- (instancetype)initWithSourceURL:(NSURL *)sourceURL destinationURL:(NSURL *)destinationURL observedProgress:(NSProgress *)observedProgress liveActivityAccessToken:(NSData *)liveActivityAccessToken;

- (void)useDownloadsFolderWithPlaceholderType:(nullable UTType *)type finalFileCreatedHandler:(void (^)(BEDownloadMonitorLocation* _Nullable finalLocation))finalFileCreatedHandler;

- (void)beginMonitoring:(void (^)(BEDownloadMonitorLocation* _Nullable placeholderLocation, NSError* _Nullable error))completion;
- (void)resumeMonitoring:(NSURL *)url completionHandler:(void (^)(NSError* _Nullable error))completionHandler;

@property (readonly) NSUUID* identifier NS_SWIFT_NAME(id);
@property (readonly) NSURL* sourceURL;
@property (readonly) NSURL* destinationURL;

+ (nullable NSData *)createAccessToken;
@end

NS_ASSUME_NONNULL_END
