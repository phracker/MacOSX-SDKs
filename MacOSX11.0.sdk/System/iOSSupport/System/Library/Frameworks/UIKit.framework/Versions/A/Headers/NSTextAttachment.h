#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/NSTextAttachment.h>)
//
//  NSTextAttachment.h
//  UIKit
//
//  Copyright (c) 2011-2018, Apple Inc. All rights reserved.
//

#import <Foundation/NSObject.h>
#import <UIKit/UIKitDefines.h>
#import <CoreGraphics/CGGeometry.h>

NS_ASSUME_NONNULL_BEGIN

enum {
    NSAttachmentCharacter API_AVAILABLE(macos(10.0), ios(7.0)) = 0xFFFC // Replacement character is used for attachments
};

@class NSTextContainer;
@class NSLayoutManager;
@class UIImage;


// This protocol defines the interface to attachment objects from NSLayoutManager
@protocol NSTextAttachmentContainer <NSObject>
#if __OBJC2__
// This protocol is available only for Objective-C 2 or later architecture

// Returns the image object rendered by NSLayoutManager at imageBounds inside textContainer.  It should return an image appropriate for the target rendering context derived by arguments to this method.  The NSTextAttachment implementation returns -image when non-nil.  If -image==nil, it returns an image based on -contents and -fileType properties.
- (nullable UIImage *)imageForBounds:(CGRect)imageBounds textContainer:(nullable NSTextContainer *)textContainer characterIndex:(NSUInteger)charIndex  API_AVAILABLE(macos(10.11), ios(7.0));


// Returns the layout bounds to the layout manager.  The bounds origin is interpreted to match position inside lineFrag.  The NSTextAttachment implementation returns -bounds if not CGRectZero; otherwise, it derives the bounds value from -[image size].  Conforming objects can implement more sophisticated logic for negotiating the frame size based on the available container space and proposed line fragment rect.
- (CGRect)attachmentBoundsForTextContainer:(nullable NSTextContainer *)textContainer proposedLineFragment:(CGRect)lineFrag glyphPosition:(CGPoint)position characterIndex:(NSUInteger)charIndex API_AVAILABLE(macos(10.11), ios(7.0));

#endif
@end

UIKIT_EXTERN API_AVAILABLE(macos(10.0), ios(7.0)) @interface NSTextAttachment : NSObject <NSTextAttachmentContainer, NSSecureCoding>

/**************************** Initialization ****************************/

// Designated initializer.  Both arguments can be nil.  When contentData==nil || uti==nil, the receiver is consider to be an attachment without document contents.  In this case, the NSAttributedString methods writing external file format tries to save the return value of -[NSTextAttachment image] instead.
- (instancetype)initWithData:(nullable NSData *)contentData ofType:(nullable NSString *)uti NS_DESIGNATED_INITIALIZER API_AVAILABLE(macos(10.11), ios(7.0));



#if __OBJC2__
/**************************** Content properties ****************************/

// These two properties define the contents for the text attachment.  Modifying these properties have a side effect of invalidating -image and -fileWrapper properties. -fileType is an UTI describing the format for -contents.
@property (nullable, copy, NS_NONATOMIC_IOSONLY) NSData *contents API_AVAILABLE(macos(10.11), ios(7.0));
@property (nullable, copy, NS_NONATOMIC_IOSONLY) NSString *fileType API_AVAILABLE(macos(10.11), ios(7.0));

/**************************** Rendering/layout properties ****************************/

// Image representing the text attachment contents. Modifying this property invalidates -contents, -fileType, and -FileWrapper properties.
@property (nullable, strong, NS_NONATOMIC_IOSONLY) UIImage *image API_AVAILABLE(macos(10.11), ios(7.0));

// Defines the layout bounds of the receiver's graphical representation in the text coordinate system.  The origin is at the glyph location on the text baseline.  The default value is CGRectZero.
@property (NS_NONATOMIC_IOSONLY) CGRect bounds API_AVAILABLE(macos(10.11), ios(7.0));
#endif

/**************************** Non-image contents properties ****************************/

// Optionally, NSTextAttachment can be associated with a file wrapper. Modifying this property has a side effect of invalidating -image, -contents, and fileType properties.
@property (nullable, strong, NS_NONATOMIC_IOSONLY) NSFileWrapper *fileWrapper;


@end

@interface NSAttributedString (NSAttributedStringAttachmentConveniences)
// A convenience method for creating an attributed string containing attachment using NSAttachmentCharacter as the base character.
+ (NSAttributedString *)attributedStringWithAttachment:(NSTextAttachment *)attachment API_AVAILABLE(macos(10.0), ios(7.0));
@end


NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/NSTextAttachment.h>
#endif
