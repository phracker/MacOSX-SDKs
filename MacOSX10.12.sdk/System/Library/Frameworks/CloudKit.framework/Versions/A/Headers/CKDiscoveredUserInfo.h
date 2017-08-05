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
NS_CLASS_DEPRECATED(10_10, 10_12, 8_0, 10_0, "Replaced by CKUserIdentity")
@interface CKDiscoveredUserInfo : NSObject

- (instancetype)init NS_UNAVAILABLE;

@property (nonatomic, readonly, copy, nullable) CKRecordID *userRecordID;

#if (TARGET_OS_MAC && !defined(__i386__) && !TARGET_OS_IPHONE && !TARGET_OS_SIMULATOR && !TARGET_OS_EMBEDDED) || TARGET_OS_IOS

@property (nonatomic, readonly, copy, nullable) NSString *firstName NS_DEPRECATED(10_10, 10_11, 8_0, 9_0, "Use -[[CKDiscoveredUserInfo displayContact] givenName]");
@property (nonatomic, readonly, copy, nullable) NSString *lastName NS_DEPRECATED(10_10, 10_11, 8_0, 9_0, "Use -[[CKDiscoveredUserInfo displayContact] familyName]");

/* displayContact is not associated with the local Address Book.  It is a wrapper around
 information known to the CloudKit server, including first and last names */
@property (nonatomic, readonly, copy, nullable) CNContact *displayContact NS_AVAILABLE(10_11, 9_0);

#else // (TARGET_OS_MAC && !TARGET_OS_IPHONE && !TARGET_OS_SIMULATOR && !TARGET_OS_EMBEDDED) || TARGET_OS_IOS


@property (nonatomic, readonly, copy, nullable) NSString *firstName;
@property (nonatomic, readonly, copy, nullable) NSString *lastName;

#endif // (TARGET_OS_MAC && !TARGET_OS_IPHONE && !TARGET_OS_SIMULATOR && !TARGET_OS_EMBEDDED) || TARGET_OS_IOS


@end
NS_ASSUME_NONNULL_END
