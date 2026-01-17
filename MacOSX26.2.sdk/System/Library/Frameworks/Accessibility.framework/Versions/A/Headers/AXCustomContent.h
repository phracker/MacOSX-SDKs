//
//  AXCustomContent.h
//  Accessibility
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Accessibility/AXFoundation.h>

NS_ASSUME_NONNULL_BEGIN

/* If an object combines a significant amount of content into one label that is not always pertinent,
 using the accessibilityCustomContent method below provides an alternative way to deliver content to the user.
 
 For example, in a photos app, you may want the user to know the date, time, orientation, and shutter speed of a photo.
 However, that information may not always be necessary to the user. Using the AXCustomContentProvider protocol
 allows the user to experience the content in a more appropriate manner for that assistive technology.
 */

typedef NS_ENUM(NSUInteger, AXCustomContentImportance) {
    AXCustomContentImportanceDefault,   // Default. Content will be output on-demand by the user.
    AXCustomContentImportanceHigh,      // Content will be output immediately to the user.
} NS_SWIFT_NAME(AXCustomContent.Importance) API_AVAILABLE(ios(14.0), tvos(14.0), watchos(7.0), macos(11.0));

AX_EXTERN API_AVAILABLE(ios(14.0), tvos(14.0), watchos(7.0), macos(11.0))
@interface AXCustomContent : NSObject <NSCopying, NSSecureCoding>

+ (instancetype)customContentWithLabel:(NSString *)label value:(NSString *)value;
+ (instancetype)customContentWithAttributedLabel:(NSAttributedString *)label attributedValue:(NSAttributedString *)value;

// A localized string that describes how to name this content.
// For example, 'Orientation' would be an appropriate name used for photo information.
@property (nonatomic, copy, readonly) NSString *label;
@property (nonatomic, copy, readonly) NSAttributedString *attributedLabel;

// A localized string that describes the content.
// For example, 'Portrait' or 'Landscape' would be an appropriate content value for 'Orientation.'
@property (nonatomic, copy, readonly) NSString *value;
@property (nonatomic, copy, readonly) NSAttributedString *attributedValue;

// Changing this property allows the user to choose when they experience this content, based on preference.
// For example, this content may be spoken all the time, or only in a "verbose" mode.
// Default: AXCustomContentImportanceDefault
@property (nonatomic, assign) AXCustomContentImportance importance;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

API_AVAILABLE(ios(14.0), tvos(14.0), watchos(7.0), macos(11.0))
@protocol AXCustomContentProvider <NSObject>
@property (nonatomic, copy, null_resettable) NSArray<AXCustomContent *> *accessibilityCustomContent;

// The block based setter takes precedence over the single line setter and property override.
// The return type for the block must be a pointer to an AXCustomContent instance.
typedef NSArray<AXCustomContent *> *_Nullable(^AXCustomContentReturnBlock)(void);
@optional
@property (nonatomic, copy, nullable) AXCustomContentReturnBlock accessibilityCustomContentBlock API_AVAILABLE(ios(17.0), tvos(17.0), watchos(10.0), macos(14.0));
@end

NS_ASSUME_NONNULL_END
