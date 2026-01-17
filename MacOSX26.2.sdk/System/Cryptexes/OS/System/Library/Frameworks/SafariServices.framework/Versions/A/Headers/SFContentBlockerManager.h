//
//  SFContentBlockerManager.h
//  SafariServices
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <SafariServices/SFFoundation.h>

#if __OBJC2__

#import <Foundation/Foundation.h>
#import <SafariServices/SFError.h>

NS_ASSUME_NONNULL_BEGIN

@class SFContentBlockerState;

SF_CLASS_AVAILABLE_MAC_SAFARI(10_0)
@interface SFContentBlockerManager : NSObject

+ (void)reloadContentBlockerWithIdentifier:(NSString *)identifier completionHandler:(void (^ _Nullable)(NSError * _Nullable error))completionHandler;
+ (void)getStateOfContentBlockerWithIdentifier:(NSString *)identifier completionHandler:(void (^)(SFContentBlockerState * _Nullable state, NSError * _Nullable error))completionHandler;

@end

NS_ASSUME_NONNULL_END

#endif // __OBJC2__
