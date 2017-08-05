/*	NSError.h
	Copyright (c) 2003-2016, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSDictionary, NSArray<ObjectType>, NSString;

#if FOUNDATION_SWIFT_SDK_EPOCH_AT_LEAST(7)
typedef NSString *NSErrorDomain;
#else
typedef NSString *NSErrorDomain NS_EXTENSIBLE_STRING_ENUM;
#endif

NS_ASSUME_NONNULL_BEGIN

// Predefined domain for errors from most AppKit and Foundation APIs.
FOUNDATION_EXPORT NSErrorDomain const NSCocoaErrorDomain;

// Other predefined domains; value of "code" will correspond to preexisting values in these domains.
FOUNDATION_EXPORT NSErrorDomain const NSPOSIXErrorDomain;
FOUNDATION_EXPORT NSErrorDomain const NSOSStatusErrorDomain;
FOUNDATION_EXPORT NSErrorDomain const NSMachErrorDomain;

#if FOUNDATION_SWIFT_SDK_EPOCH_AT_LEAST(7)
// Key in userInfo. A recommended standard way to embed NSErrors from underlying calls. The value of this key should be an NSError.
FOUNDATION_EXPORT NSString *const NSUnderlyingErrorKey;
#else
typedef NSString *NSErrorUserInfoKey NS_EXTENSIBLE_STRING_ENUM;
FOUNDATION_EXPORT NSErrorUserInfoKey const NSUnderlyingErrorKey;
#endif

// Keys in userInfo, for subsystems wishing to provide their error messages up-front. Note that NSError will also consult the userInfoValueProvider for the domain when these values are not present in the userInfo dictionary.
#if FOUNDATION_SWIFT_SDK_EPOCH_AT_LEAST(7)
FOUNDATION_EXPORT NSString *const NSLocalizedDescriptionKey;             // NSString
FOUNDATION_EXPORT NSString *const NSLocalizedFailureReasonErrorKey;      // NSString
FOUNDATION_EXPORT NSString *const NSLocalizedRecoverySuggestionErrorKey; // NSString
FOUNDATION_EXPORT NSString *const NSLocalizedRecoveryOptionsErrorKey;    // NSArray of NSStrings
FOUNDATION_EXPORT NSString *const NSRecoveryAttempterErrorKey;           // Instance of a subclass of NSObject that conforms to the NSErrorRecoveryAttempting informal protocol
FOUNDATION_EXPORT NSString *const NSHelpAnchorErrorKey;                  // NSString containing a help anchor

// Other standard keys in userInfo, for various error codes
FOUNDATION_EXPORT NSString *const NSStringEncodingErrorKey ;  // NSNumber containing NSStringEncoding
FOUNDATION_EXPORT NSString *const NSURLErrorKey;              // NSURL
FOUNDATION_EXPORT NSString *const NSFilePathErrorKey;         // NSString
#else
FOUNDATION_EXPORT NSErrorUserInfoKey const NSLocalizedDescriptionKey;             // NSString
FOUNDATION_EXPORT NSErrorUserInfoKey const NSLocalizedFailureReasonErrorKey;      // NSString
FOUNDATION_EXPORT NSErrorUserInfoKey const NSLocalizedRecoverySuggestionErrorKey; // NSString
FOUNDATION_EXPORT NSErrorUserInfoKey const NSLocalizedRecoveryOptionsErrorKey;    // NSArray of NSStrings
FOUNDATION_EXPORT NSErrorUserInfoKey const NSRecoveryAttempterErrorKey;           // Instance of a subclass of NSObject that conforms to the NSErrorRecoveryAttempting informal protocol
FOUNDATION_EXPORT NSErrorUserInfoKey const NSHelpAnchorErrorKey;                  // NSString containing a help anchor

// Other standard keys in userInfo, for various error codes
FOUNDATION_EXPORT NSErrorUserInfoKey const NSStringEncodingErrorKey ;  // NSNumber containing NSStringEncoding
FOUNDATION_EXPORT NSErrorUserInfoKey const NSURLErrorKey;              // NSURL
FOUNDATION_EXPORT NSErrorUserInfoKey const NSFilePathErrorKey;         // NSString
#endif


@interface NSError : NSObject <NSCopying, NSSecureCoding> {
    @private
    void *_reserved;
    NSInteger _code;
    NSString *_domain;
    NSDictionary *_userInfo;
}

/* Domain cannot be nil; dict may be nil if no userInfo desired.
*/
- (instancetype)initWithDomain:(NSErrorDomain)domain code:(NSInteger)code userInfo:(nullable NSDictionary *)dict NS_DESIGNATED_INITIALIZER;
+ (instancetype)errorWithDomain:(NSErrorDomain)domain code:(NSInteger)code userInfo:(nullable NSDictionary *)dict;

/* These define the error. Domains are described by names that are arbitrary strings used to differentiate groups of codes; for custom domain using reverse-DNS naming will help avoid conflicts. Codes are domain-specific.
*/
@property (readonly, copy) NSErrorDomain domain;
@property (readonly) NSInteger code;

/* Additional info which may be used to describe the error further. Examples of keys that might be included in here are "Line Number", "Failed URL", etc. Embedding other errors in here can also be used as a way to communicate underlying reasons for failures; for instance "File System Error" embedded in the userInfo of an NSError returned from a higher level document object. If the embedded error information is itself NSError, the standard key NSUnderlyingErrorKey can be used.
*/
@property (readonly, copy) NSDictionary *userInfo;

/* The primary user-presentable message for the error, for instance for NSFileReadNoPermissionError: "The file "File Name" couldn't be opened because you don't have permission to view it.". By default this looks for NSLocalizedDescriptionKey in the user info. If not present, it consults the userInfoValueProvider for the domain, and if that returns nil, it manufactures a last-resort string from the domain and code. This manufactured result is likely not suitable for presentation to the user, but can be used in logs or debugging.
*/
@property (readonly, copy) NSString *localizedDescription;

/* Return a complete sentence which describes why the operation failed. For instance, for NSFileReadNoPermissionError: "You don't have permission.". In many cases this will be just the "because" part of the error message (but as a complete sentence, which makes localization easier).  Default implementation of this picks up the value of NSLocalizedFailureReasonErrorKey from the userInfo dictionary. If not present, it consults the userInfoValueProvider for the domain, and if that returns nil, this also returns nil.
*/
@property (nullable, readonly, copy) NSString *localizedFailureReason;

/* Return the string that can be displayed as the "informative" (aka "secondary") message on an alert panel. For instance, for NSFileReadNoPermissionError: "To view or change permissions, select the item in the Finder and choose File > Get Info.". Default implementation of this picks up the value of NSLocalizedRecoverySuggestionErrorKey from the userInfo dictionary. If not present, it consults the userInfoValueProvider for the domain, and if that returns nil, this also returns nil.
*/
@property (nullable, readonly, copy) NSString *localizedRecoverySuggestion;

/* Return titles of buttons that are appropriate for displaying in an alert. These should match the string provided as a part of localizedRecoverySuggestion.  The first string would be the title of the right-most and default button, the second one next to it, and so on. If used in an alert the corresponding default return values are NSAlertFirstButtonReturn + n. Default implementation of this picks up the value of NSLocalizedRecoveryOptionsErrorKey from the userInfo dictionary. If not present, it consults the userInfoValueProvider for the domain, and if that returns nil, this also returns nil. nil return usually implies no special suggestion, which would imply a single "OK" button.
*/
@property (nullable, readonly, copy) NSArray<NSString *> *localizedRecoveryOptions;

/* Return an object that conforms to the NSErrorRecoveryAttempting informal protocol. The recovery attempter must be an object that can correctly interpret an index into the array returned by localizedRecoveryOptions. The default implementation of this picks up the value of NSRecoveryAttempterErrorKey from the userInfo dictionary. If not present, it consults the userInfoValueProvider for the domain. If that returns nil, this also returns nil.
*/
@property (nullable, readonly, strong) id recoveryAttempter;

/* Return the help anchor that can be used to create a help button to accompany the error when it's displayed to the user.  This is done automatically by +[NSAlert alertWithError:], which the presentError: variants in NSApplication go through. The default implementation of this picks up the value of the NSHelpAnchorErrorKey from the userInfo dictionary. If not present, it consults the userInfoValueProvider for the domain.  If that returns nil, this also returns nil.
*/
@property (nullable, readonly, copy) NSString *helpAnchor;


/* Specify a block which will be called from the implementations of localizedDescription, localizedFailureReason, localizedRecoverySuggestion, localizedRecoveryOptions, recoveryAttempter, and helpAnchor, when the underlying value for these is not present in the userInfo dictionary of NSError instances with the specified domain.  The provider will be called with the userInfo key corresponding to the queried property: For instance, NSLocalizedDescriptionKey for localizedDescription.  The provider should return nil for any keys it is not able to provide and, very importantly, any keys it does not recognize (since we may extend the list of keys in future releases).

The specified block will be called synchronously at the time when the above properties are queried. The results are not cached.

This provider is optional. It enables localization and formatting of error messages to be done lazily; rather than populating the userInfo at NSError creation time, these keys will be fetched on-demand when asked for.
 
It is expected that only the “owner” of an NSError domain specifies the provider for the domain, and this is done once. This facility is not meant for consumers of errors to customize the userInfo entries.  This facility should not be used to customize the behaviors of error domains provided by the system.
 
If an appropriate result for the requested key cannot be provided, return nil rather than choosing to manufacture a generic fallback response such as "Operation could not be completed, error 42." NSError will take care of the fallback cases.
*/
#if FOUNDATION_SWIFT_SDK_EPOCH_AT_LEAST(7)
+ (void)setUserInfoValueProviderForDomain:(NSErrorDomain)errorDomain provider:(id _Nullable (^ _Nullable)(NSError *err, NSString *userInfoKey))provider NS_AVAILABLE(10_11, 9_0);
+ (id _Nullable (^ _Nullable)(NSError *err, NSString *userInfoKey))userInfoValueProviderForDomain:(NSErrorDomain)errorDomain NS_AVAILABLE(10_11, 9_0);
#endif

@end


@interface NSObject(NSErrorRecoveryAttempting)

/* Given that an error alert has been presented document-modally to the user, and the user has chosen one of the error's recovery options, attempt recovery from the error, and send the selected message to the specified delegate. The option index is an index into the error's array of localized recovery options. The method selected by didRecoverSelector must have the same signature as:

    - (void)didPresentErrorWithRecovery:(BOOL)didRecover contextInfo:(void *)contextInfo;

The value passed for didRecover must be YES if error recovery was completely successful, NO otherwise.
*/
- (void)attemptRecoveryFromError:(NSError *)error optionIndex:(NSUInteger)recoveryOptionIndex delegate:(nullable id)delegate didRecoverSelector:(nullable SEL)didRecoverSelector contextInfo:(nullable void *)contextInfo;

/* Given that an error alert has been presented applicaton-modally to the user, and the user has chosen one of the error's recovery options, attempt recovery from the error, and return YES if error recovery was completely successful, NO otherwise. The recovery option index is an index into the error's array of localized recovery options.
*/
- (BOOL)attemptRecoveryFromError:(NSError *)error optionIndex:(NSUInteger)recoveryOptionIndex;

@end

NS_ASSUME_NONNULL_END

