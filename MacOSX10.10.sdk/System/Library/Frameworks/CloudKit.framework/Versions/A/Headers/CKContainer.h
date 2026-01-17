//
//  CKContainer.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CloudKit/CKDefines.h>

@class CKDatabase, CKOperation, CKRecordID, CKDiscoveredUserInfo;

// This constant represents the current user's ID for zone ID
CK_EXTERN NSString * const CKOwnerDefaultName NS_AVAILABLE(10_10, 8_0);

NS_CLASS_AVAILABLE(10_10, 8_0)
@interface CKContainer : NSObject

- (instancetype)init NS_UNAVAILABLE;

/* These calls return a CKContainer initialized with a containerIdentifier of
  [NSString stringWithFormat:@"iCloud.%@", applicationIdentifier], where application identifier
   is the calling process' application-identifier (com.apple.application-identifier on OS X) entitlement.
   If the application is in production mode (aka,
   com.apple.developer.icloud-container-environment
   is set to Production in your entitlements plist, and you have no override in
   com.apple.developer.icloud-container-development-container-identifiers
   ), then the production environment is used. */
+ (CKContainer *)defaultContainer;
+ (CKContainer *)containerWithIdentifier:(NSString *)containerIdentifier;

@property (nonatomic, readonly) NSString *containerIdentifier;

- (void)addOperation:(CKOperation *)operation;

@end

@interface CKContainer (Database)

/* Public vs. Private databases:
 Records in a public database
 - By default are world readable, owner writable.
 - Can be locked down by Roles, a process done in the Developer Portal, a web interface.  Roles are not present in the client API.
 - Are visible to the application developer via the Developer Portal.
 - Do not contribute to the owner's iCloud account storage quota.
 Records in a private database
 - By default are only owner readable and owner writable.
 - Are not visible to the application developer via the Developer Portal.
 - Are counted towards the owner's iCloud account storage quota.
 */
@property (nonatomic, readonly) CKDatabase *privateCloudDatabase;
@property (nonatomic, readonly) CKDatabase *publicCloudDatabase;

@end

typedef NS_ENUM(NSInteger, CKAccountStatus) {
    /* An error occurred when getting the account status, consult the corresponding NSError */
    CKAccountStatusCouldNotDetermine                   = 0,
    /* The iCloud account credentials are available for this application */
    CKAccountStatusAvailable                           = 1,
    /* Parental Controls / Device Management has denied access to iCloud account credentials */
    CKAccountStatusRestricted                          = 2,
    /* No iCloud account is logged in on this device */
    CKAccountStatusNoAccount                           = 3,
} NS_ENUM_AVAILABLE(10_10, 8_0);

@interface CKContainer (AccountStatus)

- (void)accountStatusWithCompletionHandler:(void (^)(CKAccountStatus accountStatus, NSError *error))completionHandler;

@end

typedef NS_OPTIONS(NSUInteger, CKApplicationPermissions) {
    /* Allows the user's record in CloudKit to be discoverable via the user's email address */
    CKApplicationPermissionUserDiscoverability         = 1 << 0,
} NS_AVAILABLE(10_10, 8_0);

typedef NS_ENUM(NSInteger, CKApplicationPermissionStatus) {
    /* The user has not made a decision for this application permission. */
    CKApplicationPermissionStatusInitialState          = 0,
    /* An error occurred when getting or setting the application permission status, consult the corresponding NSError */
    CKApplicationPermissionStatusCouldNotComplete      = 1,
    /* The user has denied this application permission */
    CKApplicationPermissionStatusDenied                = 2,
    /* The user has granted this application permission */
    CKApplicationPermissionStatusGranted               = 3,
} NS_ENUM_AVAILABLE(10_10, 8_0);

typedef void(^CKApplicationPermissionBlock)(CKApplicationPermissionStatus applicationPermissionStatus, NSError *error);

@interface CKContainer (ApplicationPermission)

- (void)statusForApplicationPermission:(CKApplicationPermissions)applicationPermission completionHandler:(CKApplicationPermissionBlock)completionHandler;
- (void)requestApplicationPermission:(CKApplicationPermissions)applicationPermission completionHandler:(CKApplicationPermissionBlock)completionHandler;

@end

@interface CKContainer (UserRecords)

/* If there is no iCloud account configured, or if access is restricted, a CKErrorNotAuthenticated error will be returned. */
- (void)fetchUserRecordIDWithCompletionHandler:(void (^)(CKRecordID *recordID, NSError *error))completionHandler;

/* This fetches all user records that match an entry in the user's address book. */
- (void)discoverAllContactUserInfosWithCompletionHandler:(void (^)(NSArray /* CKDiscoveredUserInfo */ *userInfos, NSError *error))completionHandler;
- (void)discoverUserInfoWithEmailAddress:(NSString *)email completionHandler:(void (^)(CKDiscoveredUserInfo *userInfo, NSError *error))completionHandler;
- (void)discoverUserInfoWithUserRecordID:(CKRecordID *)userRecordID completionHandler:(void (^)(CKDiscoveredUserInfo *userInfo, NSError *error))completionHandler;

@end
