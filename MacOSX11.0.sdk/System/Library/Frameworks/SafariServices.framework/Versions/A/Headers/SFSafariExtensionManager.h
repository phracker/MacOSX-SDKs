//
//  SFSafariExtensionManager.h
//  Safari
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <SafariServices/SFFoundation.h>

#if __OBJC2__

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class SFSafariExtensionState;

SF_CLASS_AVAILABLE_MAC_SAFARI(10_0)
@interface SFSafariExtensionManager : NSObject

+ (void)getStateOfSafariExtensionWithIdentifier:(NSString *)identifier completionHandler:(void (^)(SFSafariExtensionState * _Nullable state, NSError * _Nullable error))completionHandler;

@end

NS_ASSUME_NONNULL_END

#endif // __OBJC2__
