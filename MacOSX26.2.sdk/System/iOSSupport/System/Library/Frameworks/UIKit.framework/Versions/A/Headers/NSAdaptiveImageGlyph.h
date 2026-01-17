#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIFoundation/NSAdaptiveImageGlyph.h>)
//
//  NSAdaptiveImageGlyph.h
//  Text Kit
//
//  Copyright (c) 2024-2025,Apple Inc. All rights reserved.
//

#import <Foundation/NSAttributedString.h>
#import <CoreText/CTRunDelegate.h>
#import <UIKit/UIKitDefines.h>

@protocol CTAdaptiveImageProviding;
@class UTType;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

// NSAdaptiveImageGlyph is a data model object representing an image containing multiple resolutions and representations conforming to the image format described by NSAdaptiveImageGlyph.contentType. It can be applied to a range of text with NSAttributedString.Key.adaptiveImageGlyph (NSAdaptiveImageGlyphAttributeName).

API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0), visionos(2.0)) NS_SWIFT_SENDABLE
@interface NSAdaptiveImageGlyph : NSObject <NSCopying, NSSecureCoding, CTAdaptiveImageProviding>

- (instancetype)initWithImageContent:(NSData *)imageContent NS_DESIGNATED_INITIALIZER; // Initialization: imageContent must conform to the image data format identified by contentType
- (instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_UNAVAILABLE;

@property (readonly) NSData *imageContent;

// Unique identifier, derived from the underlying image data which can be used as a persistent / durable way to reference the content represented by this adaptive image glyph instance.
@property (readonly) NSString *contentIdentifier;

// Brief textual alternate representation of the represented contents, useful for non-graphical depiction of the image data or searching.  Note that the value of this property is derived from the underlying image data.
@property (readonly, copy) NSString *contentDescription;

@property (class, readonly) UTType *contentType; // A UTType identifying the image data format
@end

@interface NSAttributedString (NSAttributedStringAdaptiveImageGlyphConveniences)
// A convenience method for creating an attributed string containing an NSAdaptiveImageGlyph with attributes using NSAttachmentCharacter as the base character.
+ (instancetype)attributedStringWithAdaptiveImageGlyph:(NSAdaptiveImageGlyph *)adaptiveImageGlyph attributes:(NSDictionary<NSAttributedStringKey, id> *)attributes API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0), visionos(2.0));
@end
NS_HEADER_AUDIT_END(nullability, sendability)
#else
#import <UIFoundation/NSAdaptiveImageGlyph.h>
#endif
