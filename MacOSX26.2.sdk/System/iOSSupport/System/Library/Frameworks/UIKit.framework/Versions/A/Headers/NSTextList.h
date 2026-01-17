#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIFoundation/NSTextList.h>)
//
//  NSTextList.h
//  Text Kit
//
//  Copyright (c) 2004-2025, Apple Inc. All rights reserved.

#import <Foundation/NSObject.h>
#import <UIKit/UIKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)
// NSTextList represents a stylistic format of a group of text list items belonging to the same nested level. It supports both ordered and unordered lists. The type of marker is defined by markerFormat.

typedef NS_OPTIONS(NSUInteger, NSTextListOptions) {
    NSTextListPrependEnclosingMarker API_AVAILABLE(macos(10.0), ios(7.0), tvos(9.0), watchos(2.0), visionos(1.0)) = (1 << 0), // All marker strings up to the top-level parent are concatenated to the marker string used by the text list item.
} API_AVAILABLE(macos(10.0), ios(7.0), tvos(9.0), watchos(2.0), visionos(1.0));

typedef NSString * NSTextListMarkerFormat NS_TYPED_EXTENSIBLE_ENUM API_AVAILABLE(macos(10.0), ios(7.0), tvos(9.0), watchos(2.0), visionos(1.0));
UIKIT_EXTERN NSTextListMarkerFormat const NSTextListMarkerBox API_AVAILABLE(macos(10.0), ios(7.0), tvos(9.0), watchos(2.0), visionos(1.0));
UIKIT_EXTERN NSTextListMarkerFormat const NSTextListMarkerCheck API_AVAILABLE(macos(10.0), ios(7.0), tvos(9.0), watchos(2.0), visionos(1.0));
UIKIT_EXTERN NSTextListMarkerFormat const NSTextListMarkerCircle API_AVAILABLE(macos(10.0), ios(7.0), tvos(9.0), watchos(2.0), visionos(1.0));
UIKIT_EXTERN NSTextListMarkerFormat const NSTextListMarkerDiamond API_AVAILABLE(macos(10.0), ios(7.0), tvos(9.0), watchos(2.0), visionos(1.0));
UIKIT_EXTERN NSTextListMarkerFormat const NSTextListMarkerDisc API_AVAILABLE(macos(10.0), ios(7.0), tvos(9.0), watchos(2.0), visionos(1.0));
UIKIT_EXTERN NSTextListMarkerFormat const NSTextListMarkerHyphen API_AVAILABLE(macos(10.0), ios(7.0), tvos(9.0), watchos(2.0), visionos(1.0));
UIKIT_EXTERN NSTextListMarkerFormat const NSTextListMarkerSquare API_AVAILABLE(macos(10.0), ios(7.0), tvos(9.0), watchos(2.0), visionos(1.0));
UIKIT_EXTERN NSTextListMarkerFormat const NSTextListMarkerLowercaseHexadecimal API_AVAILABLE(macos(10.0), ios(7.0), tvos(9.0), watchos(2.0), visionos(1.0));
UIKIT_EXTERN NSTextListMarkerFormat const NSTextListMarkerUppercaseHexadecimal API_AVAILABLE(macos(10.0), ios(7.0), tvos(9.0), watchos(2.0), visionos(1.0));
UIKIT_EXTERN NSTextListMarkerFormat const NSTextListMarkerOctal API_AVAILABLE(macos(10.0), ios(7.0), tvos(9.0), watchos(2.0), visionos(1.0));
UIKIT_EXTERN NSTextListMarkerFormat const NSTextListMarkerLowercaseAlpha API_AVAILABLE(macos(10.0), ios(7.0), tvos(9.0), watchos(2.0), visionos(1.0));
UIKIT_EXTERN NSTextListMarkerFormat const NSTextListMarkerUppercaseAlpha API_AVAILABLE(macos(10.0), ios(7.0), tvos(9.0), watchos(2.0), visionos(1.0));
UIKIT_EXTERN NSTextListMarkerFormat const NSTextListMarkerLowercaseLatin API_AVAILABLE(macos(10.0), ios(7.0), tvos(9.0), watchos(2.0), visionos(1.0));
UIKIT_EXTERN NSTextListMarkerFormat const NSTextListMarkerUppercaseLatin API_AVAILABLE(macos(10.0), ios(7.0), tvos(9.0), watchos(2.0), visionos(1.0));
UIKIT_EXTERN NSTextListMarkerFormat const NSTextListMarkerLowercaseRoman API_AVAILABLE(macos(10.0), ios(7.0), tvos(9.0), watchos(2.0), visionos(1.0));
UIKIT_EXTERN NSTextListMarkerFormat const NSTextListMarkerUppercaseRoman API_AVAILABLE(macos(10.0), ios(7.0), tvos(9.0), watchos(2.0), visionos(1.0));
UIKIT_EXTERN NSTextListMarkerFormat const NSTextListMarkerDecimal API_AVAILABLE(macos(10.0), ios(7.0), tvos(9.0), watchos(2.0), visionos(1.0));

API_AVAILABLE(macos(10.0), ios(7.0), tvos(9.0), watchos(2.0), visionos(1.0))
@interface NSTextList : NSObject <NSSecureCoding, NSCopying>

#pragma mark Initialization
- (instancetype)initWithMarkerFormat:(NSTextListMarkerFormat)markerFormat options:(NSTextListOptions)options startingItemNumber:(NSInteger)startingItemNumber NS_DESIGNATED_INITIALIZER API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), watchos(9.0), visionos(1.0));
- (instancetype)initWithMarkerFormat:(NSTextListMarkerFormat)markerFormat options:(NSUInteger)options;

- (nullable instancetype) initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

#pragma mark Properties
@property (readonly, strong) NSTextListMarkerFormat markerFormat;
@property (readonly) NSTextListOptions listOptions;

#pragma mark Ordered List
// When > 0, it is used to define the starting value for a group of ordered text list.
@property NSInteger startingItemNumber;

// Yes if markerFormat is an ordered text list type
@property (readonly, getter=isOrdered) BOOL ordered API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), watchos(9.0), visionos(1.0));

#pragma mark Resolved Marker String
// Returns the marker corresponding to itemNumber. itemNumber is ignored if < 1 or isOrdered==NO.
- (NSString *)markerForItemNumber:(NSInteger)itemNumber;

#pragma mark Marker handling
// When YES, TextKit includes text list marker in the contents.
// It is NO by default.
@property (readonly, class) BOOL includesTextListMarkers API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));
@end

NS_HEADER_AUDIT_END(nullability, sendability)
#else
#import <UIFoundation/NSTextList.h>
#endif
