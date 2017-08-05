//
//  CKDiscoveredUserInfo.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#if (TARGET_OS_MAC && !defined(__i386__) && !TARGET_OS_IPHONE && !TARGET_OS_SIMULATOR && !TARGET_OS_EMBEDDED) || TARGET_OS_IOS
#import <Contacts/CNContact.h>
#endif

@class CKRecordID;

NS_ASSUME_NONNULL_BEGIN
API_DEPRECATED_WITH_REPLACEMENT("CKUserIdentity", macos(10.10, 10.12), ios(8.0, 10.0), tvos(9.0, 10.0), watchos(3.0, 3.0))
@interface CKDiscoveredUserInfo : NSObject

- (instancetype)init NS_UNAVAILABLE;

@property (nonatomic, readonly, copy, nullable) CKRecordID *userRecordID;

#if (TARGET_OS_MAC && !defined(__i386__) && !TARGET_OS_IPHONE && !TARGET_OS_SIMULATOR && !TARGET_OS_EMBEDDED) || TARGET_OS_IOS

@property (nonatomic, readonly, copy, nullable) NSString *firstName API_DEPRECATED("Use CKDiscoveredUserInfo.displayContact.givenName", macos(10.10, 10.11), ios(8.0, 9.0), tvos(9.0, 9.0));
@property (nonatomic, readonly, copy, nullable) NSString *lastName API_DEPRECATED("Use CKDiscoveredUserInfo.displayContact.familyName", macos(10.10, 10.11), ios(8.0, 9.0), tvos(9.0, 9.0));

/* displayContact is not associated with the local Address Book.  It is a wrapper around
 information known to the CloudKit server, including first and last names */
@property (nonatomic, readonly, copy, nullable) CNContact *displayContact API_AVAILABLE(macos(10.11), ios(9.0));

#else // (TARGET_OS_MAC && !TARGET_OS_IPHONE && !TARGET_OS_SIMULATOR && !TARGET_OS_EMBEDDED) || TARGET_OS_IOS


@property (nonatomic, readonly, copy, nullable) NSString *firstName;
@property (nonatomic, readonly, copy, nullable) NSString *lastName;

#endif // (TARGET_OS_MAC && !TARGET_OS_IPHONE && !TARGET_OS_SIMULATOR && !TARGET_OS_EMBEDDED) || TARGET_OS_IOS


@end
NS_ASSUME_NONNULL_END
