// Copyright © 2025 Apple Inc. All rights reserved.


#import <Foundation/Foundation.h>
#import <SafariServices/SFFoundation.h>

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_SENDABLE
SF_EXTERN API_AVAILABLE(ios(26.0), visionos(26.0)) API_UNAVAILABLE(macCatalyst, tvos, watchos)
@interface SFSafariSettings : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

+ (void)openExportBrowsingDataSettingsWithCompletionHandler:(nullable NS_SWIFT_UI_ACTOR void (^)(NSError * _Nullable error))completionHandler;

+ (void)openExtensionsSettingsForIdentifiers:(NSArray<NSString *> *)extensionIdentifiers completionHandler:(nullable NS_SWIFT_UI_ACTOR void (^)(NSError * _Nullable error))completionHandler API_AVAILABLE(ios(26.2), visionos(26.2));
@end

NS_ASSUME_NONNULL_END

