//
//  SFContentBlockerManager.h
//  SafariServices
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SafariServices/SFError.h>
#import <SafariServices/SFFoundation.h>

NS_ASSUME_NONNULL_BEGIN

@class SFContentBlockerState;

SF_EXTERN NSString * const SFContentBlockerErrorDomain API_DEPRECATED_WITH_REPLACEMENT("SFErrorDomain", ios(9.0, 10.0)) API_UNAVAILABLE(macCatalyst);

typedef NS_ENUM(NSInteger, SFContentBlockerErrorCode) {
    SFContentBlockerNoExtensionFound API_DEPRECATED_WITH_REPLACEMENT("SFErrorNoExtensionFound", ios(9.0, 10.0)) = SFErrorNoExtensionFound,
    SFContentBlockerNoAttachmentFound API_DEPRECATED_WITH_REPLACEMENT("SFErrorNoAttachmentFound", ios(9.0, 10.0)) = SFErrorNoAttachmentFound,
    SFContentBlockerLoadingInterrupted API_DEPRECATED_WITH_REPLACEMENT("SFErrorLoadingInterrupted", ios(9.0, 10.0)) = SFErrorLoadingInterrupted,
} API_DEPRECATED_WITH_REPLACEMENT("SFErrorCode", ios(9.0, 10.0)) API_UNAVAILABLE(macCatalyst);

SF_EXTERN API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macCatalyst)
@interface SFContentBlockerManager : NSObject

+ (void)reloadContentBlockerWithIdentifier:(NSString *)identifier completionHandler:(nullable void (^)(NSError *_Nullable error))completionHandler;
+ (void)getStateOfContentBlockerWithIdentifier:(NSString *)identifier completionHandler:(void (^)(SFContentBlockerState *_Nullable state, NSError *_Nullable error))completionHandler API_AVAILABLE(ios(10.0));

@end

NS_ASSUME_NONNULL_END
