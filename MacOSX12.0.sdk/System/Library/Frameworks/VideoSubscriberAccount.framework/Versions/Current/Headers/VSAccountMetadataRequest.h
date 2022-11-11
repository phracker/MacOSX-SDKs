//
//  VSAccountMetadataRequest.h
//  VideoSubscriberAccount
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <os/availability.h>
#import <VideoSubscriberAccount/VideoSubscriberAccountDefines.h>
#import <VideoSubscriberAccount/VSAccountProviderResponse.h>
#import <Foundation/NSObject.h>

NS_ASSUME_NONNULL_BEGIN

@class NSArray<ObjectType>;
@class NSString;
@class VSAccountApplicationProvider;

/// Specifies which information the app wants to obtain about the subscriber's account.
/// You should only request the information you need to fulfill your contractual obligations.
VS_EXPORT API_AVAILABLE(ios(10.0), tvos(10.0)) API_UNAVAILABLE(macCatalyst)
@interface VSAccountMetadataRequest : NSObject

/// Identifies who is making the request.
/// For use by applications using the SAML authentication scheme only.
@property (nonatomic, copy, nullable) NSString *channelIdentifier;

/// If non-empty, limits which account providers can respond to the request.
@property (nonatomic, copy) NSArray<NSString *> *supportedAccountProviderIdentifiers;

/// If non-empty, specifies providers which may be given more prominent placement
/// when choosing an account provider during authentication.
@property (nonatomic, copy) NSArray<NSString *> *featuredAccountProviderIdentifiers
API_AVAILABLE(ios(11.0), tvos(11.0));

/// A value that the account provider may use to verify the identity of the requesting app.
@property (nonatomic, copy, nullable) NSString *verificationToken;

/// Whether to request information that identifies the account provider.
@property (nonatomic, assign) BOOL includeAccountProviderIdentifier;

/// Whether to request the expiration date of the subscriber's current authentication.
@property (nonatomic, assign) BOOL includeAuthenticationExpirationDate;

/// A brief, user-presentable name for the video that the app will play if it receives a successful response.
/// For example, "What's New in Swift" or "Office Space"
/// Do not provide a value if the request will not be used to play a specific video.
@property (nonatomic, copy, nullable) NSString *localizedVideoTitle;

/// Whether the user might expect to be prompted to authenticate in order to complete this request.
@property (nonatomic, assign, getter=isInterruptionAllowed) BOOL interruptionAllowed;

/// Requests that the TV Provider reauthenticate the user if they are already authenticated.
@property (nonatomic, assign) BOOL forceAuthentication;

/// Attributes to add to a SAML attributeQuery request and sent to the account provider.
@property (nonatomic, copy) NSArray<NSString *> *attributeNames;

/// The collection of authentication schemes that the app supports for this request.
/// This list may be used to determine compatibility of the app with providers.
/// Defaults to SAML.
@property (nonatomic, copy) NSArray<VSAccountProviderAuthenticationScheme> *supportedAuthenticationSchemes
API_AVAILABLE(ios(10.2), tvos(10.1));

/// A value that an account provider application may set to pass an existing authentication session.
/// For use by TV Provider applications only.
@property (nonatomic, copy, nullable) NSString *accountProviderAuthenticationToken API_AVAILABLE(ios(13.0), tvos(13.0));

/// Application-specific providers to be added to the list of account providers.
@property (nonatomic, copy, nullable) NSArray<VSAccountApplicationProvider *> *applicationAccountProviders
API_AVAILABLE(ios(14.2), tvos(14.2));

@end

NS_ASSUME_NONNULL_END
