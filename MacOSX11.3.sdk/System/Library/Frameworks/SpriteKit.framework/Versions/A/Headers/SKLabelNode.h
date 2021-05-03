//
//  SKLabelNode.h
//  SpriteKit
//
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//

#import <SpriteKit/SKSpriteNode.h>
#import <SpriteKit/SpriteKitBase.h>

typedef NS_ENUM(NSInteger, SKLabelVerticalAlignmentMode) {
    SKLabelVerticalAlignmentModeBaseline    = 0,
    SKLabelVerticalAlignmentModeCenter      = 1,
    SKLabelVerticalAlignmentModeTop         = 2,
    SKLabelVerticalAlignmentModeBottom      = 3,
} NS_ENUM_AVAILABLE(10_9, 7_0);

typedef NS_ENUM(NSInteger, SKLabelHorizontalAlignmentMode) {
    SKLabelHorizontalAlignmentModeCenter    = 0,
    SKLabelHorizontalAlignmentModeLeft      = 1,
    SKLabelHorizontalAlignmentModeRight     = 2,
} NS_ENUM_AVAILABLE(10_9, 7_0);

NS_ASSUME_NONNULL_BEGIN

/**
 A node that displays a text label with a given font.
 */
SK_EXPORT @interface SKLabelNode : SKNode

+ (instancetype)labelNodeWithText:(nullable NSString *)text;
+ (instancetype)labelNodeWithAttributedText:(nullable NSAttributedString *)attributedText API_AVAILABLE(ios(11.0), tvos(11.0), watchos(4.0), macos(10.13));
+ (instancetype)labelNodeWithFontNamed:(nullable NSString *)fontName;

- (instancetype)initWithFontNamed:(nullable NSString *)fontName;

@property (nonatomic) SKLabelVerticalAlignmentMode verticalAlignmentMode;
@property (nonatomic) SKLabelHorizontalAlignmentMode horizontalAlignmentMode;

/**Determines the number of lines to draw. The default value is 1 (single line). A value of 0 means no limit.
   If the height of the text reaches the # of lines the text will be truncated using the line break mode.
 */
@property(nonatomic) NSInteger numberOfLines API_AVAILABLE(ios(11.0), tvos(11.0), macos(10.13), watchos(4.0));

/**Determines the line break mode for multiple lines.
   Default is NSLineBreakByTruncatingTail
 */
@property(nonatomic) NSLineBreakMode lineBreakMode API_AVAILABLE(ios(11.0), tvos(11.0), macos(10.13), watchos(4.0));

/**If nonzero, this is used when determining layout width for multiline labels.
   Default is zero.
 */
@property(nonatomic) CGFloat preferredMaxLayoutWidth API_AVAILABLE(ios(11.0), tvos(11.0), macos(10.13), watchos(4.0));

@property (nonatomic, copy, nullable) NSString *fontName;
@property (nonatomic, copy, nullable) NSString *text;
@property (nonatomic, copy, nullable) NSAttributedString *attributedText API_AVAILABLE(ios(11.0), tvos(11.0), macos(10.13), watchos(4.0));
@property (nonatomic) CGFloat fontSize;


/**
 Base color that the text is rendered with (if supported by the font)
 */
@property (nonatomic, retain, nullable) SKColor *fontColor;

/**
 Controls the blending between the rendered text and a color. The valid interval of values is from 0.0 up to and including 1.0. A value above or below that interval is clamped to the minimum (0.0) if below or the maximum (1.0) if above.
 */
@property (nonatomic) CGFloat colorBlendFactor;

/**
 Color to be blended with the text based on the colorBlendFactor
 */
@property (nonatomic, retain, nullable) SKColor *color;

/**
 Sets the blend mode to use when composing the sprite with the final framebuffer.
 @see SKNode.SKBlendMode
 */
@property (nonatomic) SKBlendMode blendMode;

@end

NS_ASSUME_NONNULL_END
