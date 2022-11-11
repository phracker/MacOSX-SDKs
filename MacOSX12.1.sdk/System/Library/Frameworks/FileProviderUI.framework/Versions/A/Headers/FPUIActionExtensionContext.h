//
//  FPUIActionExtensionContext.h
//  FileProviderUI
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <FileProvider/FileProvider.h>
#import <FileProviderUI/FPUIBase.h>
#import <FileProviderUI/FPUIActionExtensionContext.h>


NS_ASSUME_NONNULL_BEGIN

extern NSString *const FPUIErrorDomain API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macCatalyst, tvos);

typedef NSString * FPUIActionIdentifier NS_EXTENSIBLE_STRING_ENUM;

typedef NS_ENUM(NSUInteger, FPUIExtensionErrorCode) {
    FPUIExtensionErrorCodeUserCancelled,
    FPUIExtensionErrorCodeFailed,
} API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macCatalyst, tvos);


FPUI_AVAILABLE(ios(11.0), macos(10.15))
API_UNAVAILABLE(macCatalyst)
@interface FPUIActionExtensionContext : NSExtensionContext

@property (readonly, copy, nullable) NSFileProviderDomainIdentifier domainIdentifier;

/// The extension should call this method when the action did terminate successfully.
- (void)completeRequest;
- (void)completeRequestReturningItems:(nullable NSArray *)items completionHandler:(void(^ __nullable)(BOOL expired))completionHandler NS_UNAVAILABLE;


/// The extension should call this method when the action failed.
/// The error's Domain should be FPUIErrorDomain and the code should be a value of type FPUIErrorCode.
- (void)cancelRequestWithError:(NSError *)error;
    
@end

NS_ASSUME_NONNULL_END
