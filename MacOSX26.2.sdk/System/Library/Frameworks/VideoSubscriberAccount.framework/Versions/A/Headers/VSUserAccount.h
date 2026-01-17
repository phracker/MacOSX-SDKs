//
//  VSUserAccount.h
//  VideoSubscriberAccountFramework
//
//  Created by Nik Harris on 1/30/22.
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <VideoSubscriberAccount/VSAppleSubscription.h>
#import <VideoSubscriberAccount/VideoSubscriberAccountDefines.h>

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, VSUserAccountType) {
    VSUserAccountTypeFree,    // Default. The user has access to free content only.
    VSUserAccountTypePaid     // The user has access to content offered to paid subscriptions.
} NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(16.4), tvos(16.4), macos(13.3)) API_UNAVAILABLE(watchos, macCatalyst);

typedef NS_ENUM(NSInteger, VSOriginatingDeviceCategory) {
    VSOriginatingDeviceCategoryMobile,
    VSOriginatingDeviceCategoryOther
} NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(16.4), tvos(16.4), macos(13.3)) API_UNAVAILABLE(watchos, macCatalyst);

VS_EXPORT API_AVAILABLE(ios(16.4), tvos(16.4), macos(13.3)) API_UNAVAILABLE(watchos, macCatalyst)
    NS_REFINED_FOR_SWIFT
    NS_SWIFT_SENDABLE
    @interface VSUserAccount : NSObject

// The URL pointing to the application JS that can respond to account update requests, or nil if JS updates are not supported.
@property (nonatomic, copy, nullable) NSURL *updateURL;

// Indicates whether or not the update URL must have a certificate trusted by the system,
// and not a certificate trusted by the user of the device.
@property (nonatomic, assign) BOOL requiresSystemTrust;

// The identifier of the provider known to Apple that provides the account. For use only with TV Provider Authentication integrated apps.
@property (nonatomic, strong, nullable) NSString *accountProviderIdentifier;

// A value opaque to Apple that can be used to uniquely identify the account.
// When an account update request is made to the application JS, this identifier will be provided in order to help identify the account to be refreshed.
@property (nonatomic, copy, nullable) NSString *identifier;

@property (nonatomic, assign) VSUserAccountType accountType;

// Indicates if the user has signed out of their account.
@property (nonatomic, assign, getter=isSignedOut) BOOL signedOut;

// The date in which the billing cycle ends for paid accounts.
// used as a heuristic to determine when a refresh should occur.
// If there is no existing billing cycle, this value should be nil.
@property (nonatomic, copy, nullable) NSDate *subscriptionBillingCycleEndDate;


// Identifies a subset of content from your catalog that subscriber can play.
// Matches tier identifiers that are present in the availability feed.
@property (nonatomic, copy, nullable) NSArray<NSString *> *tierIdentifiers;

// Identifies the billing group associated with the subscription.
@property (nonatomic, copy, nullable) NSString *billingIdentifier;

// The authentication token or data used to maintain the authentication state for the account
// in your application. This will be provided to the application JS during account refresh requests
// so that billing cycle dates, account validity, or any other data can be fetched for the account.
// Additionally, when fetching accounts using VSUserAccountManager, if an account is pulled from a
// different device, and the user is not signed in to the current device, it can be used to
// authenticate the user seamlessly without requiring username/password.
// This data is not accessible by Apple.
@property (nonatomic, copy, nullable) NSString *authenticationData;

// Indicates whether or not the account was registered on the current device.
// Accounts pulled using VSUserAccountManager may be from other devices signed
// in to the same iCloud account.
@property (nonatomic, readonly, getter=isFromCurrentDevice) BOOL fromCurrentDevice;

// The type of device the VSUserAccount was registered on.
@property (nonatomic, readonly) VSOriginatingDeviceCategory deviceCategory;

// The Apple service subscription associated with the user account.
@property (nonatomic, strong, nullable) VSAppleSubscription *appleSubscription
    API_AVAILABLE(ios(17.4), tvos(17.4), macos(14.4), visionos(1.1)) API_UNAVAILABLE(watchos, macCatalyst);

// Use -initWithAccountType:updateURL: or -initWithAccountProviderIdentifier: instead.
VS_INIT_UNAVAILABLE

// Initializes a new VSUserAccount with a URL that points to an application JS
// that can respond to account update requests.
- (instancetype)initWithAccountType:(VSUserAccountType)accountType updateURL:(nullable NSURL *)url;

@end

NS_ASSUME_NONNULL_END
