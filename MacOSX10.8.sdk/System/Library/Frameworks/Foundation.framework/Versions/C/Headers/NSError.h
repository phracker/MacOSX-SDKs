/*	NSError.h
	Copyright (c) 2003-2012, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSDictionary, NSArray;


// Predefined domain for errors from most AppKit and Foundation APIs.
FOUNDATION_EXPORT NSString *const NSCocoaErrorDomain;

// Other predefined domains; value of "code" will correspond to preexisting values in these domains.
FOUNDATION_EXPORT NSString *const NSPOSIXErrorDomain;
FOUNDATION_EXPORT NSString *const NSOSStatusErrorDomain;
FOUNDATION_EXPORT NSString *const NSMachErrorDomain;

// Key in userInfo. A recommended standard way to embed NSErrors from underlying calls. The value of this key should be an NSError.
FOUNDATION_EXPORT NSString *const NSUnderlyingErrorKey;

// Keys in userInfo, for subsystems wishing to provide their error messages up-front.
FOUNDATION_EXPORT NSString *const NSLocalizedDescriptionKey;  // NSString
FOUNDATION_EXPORT NSString *const NSLocalizedFailureReasonErrorKey     ;  // NSString
FOUNDATION_EXPORT NSString *const NSLocalizedRecoverySuggestionErrorKey;  // NSString
FOUNDATION_EXPORT NSString *const NSLocalizedRecoveryOptionsErrorKey   ;  // NSArray of NSStrings
FOUNDATION_EXPORT NSString *const NSRecoveryAttempterErrorKey;  // Instance of a subclass of NSObject that conforms to the NSErrorRecoveryAttempting informal protocol
FOUNDATION_EXPORT NSString *const NSHelpAnchorErrorKey                ;  // NSString containing a help anchor

// Other standard keys in userInfo, for various error codes
FOUNDATION_EXPORT NSString *const NSStringEncodingErrorKey ;  // NSNumber containing NSStringEncoding
FOUNDATION_EXPORT NSString *const NSURLErrorKey		   ;  // NSURL
FOUNDATION_EXPORT NSString *const NSFilePathErrorKey	   ;  // NSString



@interface NSError : NSObject <NSCopying, NSSecureCoding> {
    @private
    void *_reserved;
    NSInteger _code;
    NSString *_domain;
    NSDictionary *_userInfo;
}

/* Designated initializer. Domain cannot be nil; dict may be nil if no userInfo desired.
*/
- (id)initWithDomain:(NSString *)domain code:(NSInteger)code userInfo:(NSDictionary *)dict;
+ (id)errorWithDomain:(NSString *)domain code:(NSInteger)code userInfo:(NSDictionary *)dict;

/* These define the error. Domains are described by names that are arbitrary strings used to differentiate groups of codes; for custom domain using reverse-DNS naming will help avoid conflicts. Codes are domain-specific.
*/
- (NSString *)domain;
- (NSInteger)code;

/* Additional info which may be used to describe the error further. Examples of keys that might be included in here are "Line Number", "Failed URL", etc. Embedding other errors in here can also be used as a way to communicate underlying reasons for failures; for instance "File System Error" embedded in the userInfo of an NSError returned from a higher level document object. If the embedded error information is itself NSError, the standard key NSUnderlyingErrorKey can be used.
*/
- (NSDictionary *)userInfo;

/* The primary user-presentable message for the error. This method can be overridden by subclassers wishing to present better error strings.  By default this looks for NSLocalizedDescriptionKey in the user info. If not present, it manufactures a string from the domain and code. Also, for some of the built-in domains it knows about, it might try to fetch an error string by calling a domain-specific function. In the absence of a custom error string, the manufactured one might not be suitable for presentation to the user, but can be used in logs or debugging. 
*/
- (NSString *)localizedDescription;

/* Return a complete sentence which describes why the operation failed. In many cases this will be just the "because" part of the error message (but as a complete sentence, which makes localization easier). This will return nil if string is not available. Default implementation of this will pick up the value of the NSLocalizedFailureReasonErrorKey from the userInfo dictionary.
*/
- (NSString *)localizedFailureReason;

/* Return the string that can be displayed as the "informative" (aka "secondary") message on an alert panel. Returns nil if no such string is available. Default implementation of this will pick up the value of the NSLocalizedRecoverySuggestionErrorKey from the userInfo dictionary.
*/
- (NSString *)localizedRecoverySuggestion;

/* Return titles of buttons that are appropriate for displaying in an alert. These should match the string provided as a part of localizedRecoverySuggestion.  The first string would be the title of the right-most and default button, the second one next to it, and so on. If used in an alert the corresponding default return values are NSAlertFirstButtonReturn + n. Default implementation of this will pick up the value of the NSLocalizedRecoveryOptionsErrorKey from the userInfo dictionary.  nil return usually implies no special suggestion, which would imply a single "OK" button.
*/
- (NSArray *)localizedRecoveryOptions;

/* Return an object that conforms to the NSErrorRecoveryAttempting informal protocol. The recovery attempter must be an object that can correctly interpret an index into the array returned by -localizedRecoveryOptions. The default implementation of this method merely returns [[self userInfo] objectForKey:NSRecoveryAttempterErrorKey].
*/
- (id)recoveryAttempter;

/* Return the help anchor that can be used to create a help button to accompany the error when it's displayed to the user.  This is done automatically by +[NSAlert alertWithError:], which the presentError: variants in NSApplication go through. The default implementation of this method merely returns [[self userInfo] objectForKey:NSHelpAnchorErrorKey].
*/
- (NSString *)helpAnchor;



@end

@interface NSObject(NSErrorRecoveryAttempting)

/* Given that an error alert has been presented document-modally to the user, and the user has chosen one of the error's recovery options, attempt recovery from the error, and send the selected message to the specified delegate. The option index is an index into the error's array of localized recovery options. The method selected by didRecoverSelector must have the same signature as:

    - (void)didPresentErrorWithRecovery:(BOOL)didRecover contextInfo:(void *)contextInfo;

The value passed for didRecover must be YES if error recovery was completely successful, NO otherwise.
*/
- (void)attemptRecoveryFromError:(NSError *)error optionIndex:(NSUInteger)recoveryOptionIndex delegate:(id)delegate didRecoverSelector:(SEL)didRecoverSelector contextInfo:(void *)contextInfo;

/* Given that an error alert has been presented applicaton-modally to the user, and the user has chosen one of the error's recovery options, attempt recovery from the error, and return YES if error recovery was completely successful, NO otherwise. The recovery option index is an index into the error's array of localized recovery options.
*/
- (BOOL)attemptRecoveryFromError:(NSError *)error optionIndex:(NSUInteger)recoveryOptionIndex;

@end


