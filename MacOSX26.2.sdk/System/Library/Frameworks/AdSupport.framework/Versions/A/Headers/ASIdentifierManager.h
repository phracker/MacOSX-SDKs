/*
 File: ASIdentifierManager.h
 
 Framework: AdSupport
 
 Copyright (c) 2012, Apple Inc. All rights reserved.
*/

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN


/// The object that contains the advertising identifier.
API_AVAILABLE(ios(6), macosx(10.14), tvos(6))
@interface ASIdentifierManager : NSObject

/// The shared instance of the identifier manager class.
///
/// - Returns: Returns the shared instance of the AdSupport identifier manager
/// class.
+ (ASIdentifierManager *)sharedManager;

/// The UUID that is specific to a device.
///
/// The ``ASIdentifierManager/advertisingIdentifier`` is an alphanumeric string
/// that’s unique to each device, and which you only use for advertising. Use
/// this string for frequency capping, attribution, conversion events,
/// estimating the number of unique users, advertising fraud detection, and
/// debugging. On devices running iOS 14.5 and later and iPadOS 14.5 and later,
/// your app must request tracking authorization before it can get the
/// advertising identifier. For more information on getting the advertising
/// identifier, see ``AdSupport``.
///
/// The advertising identifier returns either a unique UUID, or all zeros. It
/// returns a unique UUID in the following cases:
///
/// - If Settings &gt; Privacy &gt; Tracking &gt; Allow Apps to Request to Track
/// is On, you’ve requested tracking authorization from the user by calling the
/// <doc://com.apple.documentation/documentation/apptrackingtransparency> APIs,
/// and received authorization, indicated by
/// <doc://com.apple.documentation/documentation/apptrackingtransparency/attrackingmanager/authorizationstatus/authorized>.
/// - If the user changes Settings &gt; Privacy &gt; Tracking &gt; Allow Apps to
/// Request to Track to Off after authorizing your app, and leaves the
/// permissions On for your app.
///
/// The advertising identifier returns all zeros
/// (`00000000-0000-0000-0000-000000000000`) in the following cases:
///
/// - In Simulator, regardless of any settings.
/// - When you call this API on a device running macOS. 
/// - When you call this API in a compatible iPad or iPhone app running in visionOS.
/// - On devices running iOS 14.5 and later and iPadOS 14.5 and later, if you haven’t requested authorization using the <doc://com.apple.documentation/documentation/apptrackingtransparency> framework.
/// - If you’ve requested authorization using the <doc://com.apple.documentation/documentation/apptrackingtransparency> framework and the user declines, which results in an authorization status of <doc://com.apple.documentation/documentation/apptrackingtransparency/attrackingmanager/authorizationstatus/denied>.
/// - When a profile or configuration restricts access to the advertising identifier. For more information about restrictions, see <doc://com.apple.documentation/documentation/apptrackingtransparency/attrackingmanager/authorizationstatus/restricted>.
///
/// As a best practice, don’t store the advertising identifier value; access
/// ``ASIdentifierManager/advertisingIdentifier`` instead. Users can change
/// their authorization for tracking at any time in Settings &gt; Privacy &gt;
/// Tracking. Check your app’s authorization using the App Tracking Transparency
/// API
/// <doc://com.apple.documentation/documentation/apptrackingtransparency/attrackingmanager/3547038-trackingauthorizationstatus>
/// to determine the user’s intent.
///
/// For more information about asking users for permission to track, see [User
/// Privacy and Data
/// Use](https://developer.apple.com/app-store/user-privacy-and-data-use/).
@property (nonatomic, readonly) NSUUID *advertisingIdentifier;


/// A Boolean value that indicates whether the user has limited ad tracking
/// enabled.
///
/// - Warning: This property is deprecated. Functionality has been replaced by
/// the <doc://com.apple.documentation/documentation/apptrackingtransparency>
/// framework.
@property (nonatomic, readonly, getter=isAdvertisingTrackingEnabled) BOOL advertisingTrackingEnabled API_DEPRECATED("This has been replaced by functionality in AppTrackingTransparency's ATTrackingManager class.", ios(6, 14), macosx(10.14, 11.0), tvos(6, 14));

@end

NS_ASSUME_NONNULL_END
