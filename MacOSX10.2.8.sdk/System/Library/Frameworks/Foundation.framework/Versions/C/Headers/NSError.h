/*	NSError.h
	Copyright 2003, Apple, Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

// Note: To use the APIs described in these headers, you must perform
// a runtime check for Foundation-462.1 or later.
#import <AvailabilityMacros.h>
#if defined(MAC_OS_X_VERSION_10_2) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_2)

@class NSString;
@class NSDictionary;

// In simple cases, for subsystems wishing to provide their error description up-front.
FOUNDATION_EXPORT NSString * const NSLocalizedDescriptionKey;

// Predefined domains; value of "code" will correspond to preexisting values in these domains.
FOUNDATION_EXPORT NSString * const NSPOSIXErrorDomain;
FOUNDATION_EXPORT NSString * const NSOSStatusErrorDomain;
FOUNDATION_EXPORT NSString * const NSMachErrorDomain;

@interface NSError : NSObject <NSCopying, NSCoding> {
    @private
    void *_reserved;
    int _code;
    NSString *_domain;
    NSDictionary *_userInfo;
}

/* Designated initializer. Domain cannot be nil; dict may be nil if no userInfo desired.
*/
- (id)initWithDomain:(NSString *)domain code:(int)code userInfo:(NSDictionary *)dict;
+ (id)errorWithDomain:(NSString *)domain code:(int)code userInfo:(NSDictionary *)dict;

/* These define the error. Domains are described by names that are arbitrary strings used to differentiate groups of codes; for custom domain using reverse-DNS naming will help avoid conflicts. Codes are domain-specific.
*/
- (NSString *)domain;
- (int)code;

/* Additional info which may be used to describe the error further. Examples of keys that might be included in here are "Line Number", "Failed URL", etc. Embedding other NSErrors in here can also be used as a way to communicate underlying reasons for failures; for instance "File System Error" embedded in the userInfo of an NSError returned from a higher level document object.
*/
- (NSDictionary *)userInfo;

/* This method can be overridden by subclassers wishing to present better error strings.  By default this looks for NSLocalizedDescriptionKey in the user info. If not present, it manufactures a string from the domain and code. Also, for some of the built-in domains it knows about, it might try to fetch an error string by calling a domain-specific function. In the absence of a custom error string, the manufactured one might not be suitable for presentation to the user, but can be used in logs or debugging. 
*/
- (NSString *)localizedDescription;

@end

#endif
