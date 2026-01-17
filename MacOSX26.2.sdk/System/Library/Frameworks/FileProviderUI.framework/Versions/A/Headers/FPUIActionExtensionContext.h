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


/// The error domain for errors raised by the File Provider UI extension.
extern NSString *const FPUIErrorDomain API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macCatalyst, tvos);

typedef NSString * FPUIActionIdentifier NS_EXTENSIBLE_STRING_ENUM;


/// The error codes for errors raised by the File Provider UI extension.
typedef NS_ENUM(NSUInteger, FPUIExtensionErrorCode) {
    
    /// An error indicating that the action was canceled by the user.
    FPUIExtensionErrorCodeUserCancelled,
    
    /// An error indicating that the action has failed.
    FPUIExtensionErrorCodeFailed,
} API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macCatalyst, tvos);


FPUI_AVAILABLE(ios(11.0), macos(10.15))
API_UNAVAILABLE(macCatalyst)

/// An extension context provided to File Provider UI extensions.
@interface FPUIActionExtensionContext : NSExtensionContext


/// The identifier for the domain managed by the current file provider.
@property (readonly, copy, nullable) NSFileProviderDomainIdentifier domainIdentifier;


/// Marks the action as complete.
///
/// Call this method when the action completes successfully.
- (void)completeRequest;
- (void)completeRequestReturningItems:(nullable NSArray *)items completionHandler:(void(^ __nullable)(BOOL expired))completionHandler NS_UNAVAILABLE;



/// Cancels the action and returns the provided error.
///
/// Call this method if the action fails. Set the error's domain to
/// ``FPUIErrorDomain``. Set the error code to a ``FPUIExtensionErrorCode``
/// value.
- (void)cancelRequestWithError:(NSError *)error;
    
@end

NS_ASSUME_NONNULL_END
