//
//  SFSafariExtension.h
//  SafariServices
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <SafariServices/SFFoundation.h>

#if __OBJC2__

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

SF_CLASS_AVAILABLE_MAC_SAFARI(12_1)
@interface SFSafariExtension : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// Calls the completion handler with the base URI of the extension.
+ (void)getBaseURIWithCompletionHandler:(void (^)(NSURL * _Nullable baseURI))completionHandler;

@end

NS_ASSUME_NONNULL_END

#endif // __OBJC2__
