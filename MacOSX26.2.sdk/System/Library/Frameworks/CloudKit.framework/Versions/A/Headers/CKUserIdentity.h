//
//  CKUserIdentity.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <CloudKit/CKDefines.h>

@class CKRecordID, CKUserIdentityLookupInfo;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0))
CK_SUBCLASSING_DEPRECATED // should not be subclassed, or Sendable may no longer apply
// NS_SWIFT_SENDABLE on macos(13.3), macCatalyst(16.4), ios(16.4), tvos(16.4), watchos(9.4)
@interface CKUserIdentity : NSObject <NSSecureCoding, NSCopying>
/*! Use @c CKDiscoverUserIdentitiesOperation or @c CKFetchShareParticipantsOperation to create a @c CKUserIdentity */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@property (nullable, readonly, copy) CKRecordID *userRecordID;

/*! This is the @c lookupInfo you passed in to @c CKDiscoverUserIdentitiesOperation or @c CKFetchShareParticipantsOperation */
@property (nullable, readonly, copy) CKUserIdentityLookupInfo *lookupInfo;
@property (nullable, readonly, copy) NSPersonNameComponents *nameComponents;
@property (readonly, assign) BOOL hasiCloudAccount;

@property (readonly, copy) NSArray<NSString *> *contactIdentifiers API_DEPRECATED("No longer supported. Please see Sharing CloudKit Data with Other iCloud Users.", macos(10.13, 15.0), ios(11.0, 18.0), watchos(4.0, 11.0));

@end

NS_HEADER_AUDIT_END(nullability, sendability)
