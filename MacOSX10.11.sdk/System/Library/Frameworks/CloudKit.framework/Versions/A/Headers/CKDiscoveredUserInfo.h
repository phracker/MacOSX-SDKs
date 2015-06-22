//
//  CKDiscoveredUserInfo.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Contacts/CNContact.h>

@class CKRecordID;

NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface CKDiscoveredUserInfo : NSObject

- (instancetype)init NS_UNAVAILABLE;

@property (nonatomic, readonly, copy, nullable) CKRecordID *userRecordID;

@property (nonatomic, readonly, copy, nullable) NSString *firstName NS_DEPRECATED(10_10, 10_11, 8_0, 9_0, "Use -[[CKDiscoveredUserInfo displayContact] givenName]");
@property (nonatomic, readonly, copy, nullable) NSString *lastName NS_DEPRECATED(10_10, 10_11, 8_0, 9_0, "Use -[[CKDiscoveredUserInfo displayContact] familyName]");

/* displayContact is not associated with the local Address Book.  It is a wrapper around
 information known to the CloudKit server, including first and last names */
@property (nonatomic, readonly, copy, nullable) CNContact *displayContact NS_AVAILABLE(10_11, 9_0);

@end
NS_ASSUME_NONNULL_END
