#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIEventAttribution.h>)
//
//  UIEventAttribution.h
//  UIKit
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <UIKit/UIKitDefines.h>

#import <Foundation/Foundation.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

UIKIT_EXTERN API_AVAILABLE(ios(14.5)) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_UI_ACTOR
@interface UIEventAttribution : NSObject <NSCopying>

/// An identifier that is associated with the source of the attribution. For example, you may choose to use this as a campaign identifier to measure the effectiveness of different advertisement campaigns.
///
/// This field corresponds to `source_id` in the subsequent attribution report.
@property (nonatomic, assign, readonly) uint8_t sourceIdentifier;

/// The destination URL of an attribution. For example, the link opened when an advertisement is tapped.
///
/// This field corresponds to `attributed_on_site` in the subsequent attribution report.
@property (nonatomic, copy, readonly) NSURL *destinationURL;

/// The URL to which the attribution report will be sent. You do not provide this field at creation time. Instead, you must define the URL
/// as a string in your app's Info.plist under the `NSAdvertisingAttributionReportEndpoint` key.
///
/// This field corresponds to `source_site` in the subsequent attribution report.
@property (nonatomic, nullable, copy, readonly) NSURL *reportEndpoint;

/// A high-level description of the source of the attribution. For example, this could be a description of the content of an advertisement a user taps on.
///
/// The system may truncate this field if it is too long.
@property (nonatomic, copy, readonly) NSString *sourceDescription;

/// The name of the party that purchased the content to be attributed. For example, this could be the name of the party that purchased the placement of an advertisement.
///
/// The system may truncate this field if it is too long.
@property (nonatomic, copy, readonly) NSString *purchaser;

/// Create a `UIEventAttribution` object.
///
/// @param sourceIdentifier An identifier associated with the attribution.
/// @param destinationURL The destination URL of the attribution.
/// @param sourceDescription A high-level description of the content to be attributed. Pass in an empty string if no description is available.
/// @param purchaser The name of the party that purchased the content to be attributed. Pass in an empty string if no name is available.
///
/// @return An instance of `UIEventAttribution` with the specified values for each field.
///
/// The `sourceDescription` and `purchaser` fields may be truncated by the system if they are too long.
- (instancetype)initWithSourceIdentifier:(uint8_t)sourceIdentifier
                          destinationURL:(NSURL *)destinationURL
                       sourceDescription:(NSString *)sourceDescription
                               purchaser:(NSString *)purchaser;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIEventAttribution.h>
#endif
