#if !__has_include(<AVFCore/AVCaption.h>)
/*
	File:  AVCaption.h

	Framework:  AVFoundation
 
	Copyright 2015-2023 Apple Inc. All rights reserved.

*/

#import <AVFoundation/AVBase.h>
#if ( TARGET_OS_OSX || ( TARGET_OS_IOS && ! TARGET_OS_VISION ) )

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <CoreMedia/CMTimeRange.h>

NS_ASSUME_NONNULL_BEGIN

@class AVCaptionRuby;

/*!
 @enum AVCaptionUnitsType
 @abstract
	Geometry unit.
 @discussion
	Some geometric objects are positioned or sized with different kinds of dimensions differeing in unit. In some cases, an object might allow multiple kinds of dimensions varrying by units. AVCaptionUnitsType is an enumeration of kinds of units that are used across caption formats.
 @constant AVCaptionUnitsTypeUnspecified
	The units has not been specified. The dimension can be seen as invalid.
 @constant AVCaptionUnitsTypeCells
	The integer value is a number of cells.
 @constant AVCaptionUnitsTypePercent
	The floating-point value number value is [0 .. 100] correspondng to 0% to 100%, typically relative to the enclosing rectangle.
 */
typedef NS_ENUM(NSInteger, AVCaptionUnitsType) {
	AVCaptionUnitsTypeUnspecified = 0,
	AVCaptionUnitsTypeCells,
	AVCaptionUnitsTypePercent,
};

/*!
 @typedef AVCaptionDimension
 @abstract The length with a unit or coordinate on a 2D geometric axis
 @field value The value of the coordinate or length.
 @field units The units of the coordinate (e.g., cells, points)
 */
typedef struct AVCaptionDimension {
	CGFloat value;
	AVCaptionUnitsType units;
} AVCaptionDimension;

/*!
 @typedef AVCaptionPoint
 @abstract A two dimensional point made of x and y AVCaptionDimension coordinates
 @field x An AVCaptionDimension holding the x coordinate of the point
 @field y An AVCaptionDimension holding the y coordinate of the point
 */
typedef struct AVCaptionPoint {
	AVCaptionDimension x;
	AVCaptionDimension y;
} AVCaptionPoint;

/*!
 @typedef AVCaptionSize
 @abstract A two dimensional size made of width and height AVCaptionDimensions
 @field width An AVCaptionDimension holding the width
 @field height An AVCaptionDimension holding the height
 */
typedef struct AVCaptionSize {
	AVCaptionDimension width;
	AVCaptionDimension height;
} AVCaptionSize;

/*!
	@function	AVCaptionDimensionMake
	@abstract	Makes an AVCaptionDimension from a value and units.
*/
AVF_EXPORT AVCaptionDimension AVCaptionDimensionMake( CGFloat value, AVCaptionUnitsType units )
API_AVAILABLE(macos(12.0), ios(18.0), macCatalyst(15.0)) API_UNAVAILABLE(tvos, watchos, visionos);

/*!
	@function	AVCaptionPointMake
	@abstract	Makes an AVCaptionPoint from x and y coordinate AVCaptionDimensions.
*/
AVF_EXPORT AVCaptionPoint AVCaptionPointMake( AVCaptionDimension x, AVCaptionDimension y )
API_AVAILABLE(macos(12.0), ios(18.0), macCatalyst(15.0)) API_UNAVAILABLE(tvos, watchos, visionos);

/*!
	@function	AVCaptionSizeMake
	@abstract	Makes an AVCaptionSize from width and height AVCaptionDimensions.
*/
AVF_EXPORT AVCaptionSize AVCaptionSizeMake( AVCaptionDimension width, AVCaptionDimension height )
API_AVAILABLE(macos(12.0), ios(18.0), macCatalyst(15.0)) API_UNAVAILABLE(tvos, watchos, visionos);

/*!
 @enum AVCaptionRegionDisplayAlignment
 @abstract
    Choices for region display alignment

 @discussion
    Whenever a caption line is inserted into a region, it's placed relative to the existing lines and the direction to which the line is placed is called the block progression direction of the region. For example, English caption's block progression direction is top-to-bottom, while Japanese vertical caption uses right-to-left.

    The value describes how the caption lines should positioned in a region in terms of the block progression direction.

 @constant AVCaptionRegionDisplayAlignmentBefore
    Align lines in earlier position in the block progression direction, or align to the top for English captions, for example.

 @constant AVCaptionRegionDisplayAlignmentCenter
    Align lines in center position in the block progression direction. iTT doesn't support this.

 @constant AVCaptionRegionDisplayAlignmentAfter
    Align lines in later position in the block progression direction, or align to the left for Japanese vertical captions, for example.
 */
typedef NS_ENUM(NSInteger, AVCaptionRegionDisplayAlignment) {
	AVCaptionRegionDisplayAlignmentBefore        = 0,
	AVCaptionRegionDisplayAlignmentCenter        = 1,
	AVCaptionRegionDisplayAlignmentAfter         = 2,
} API_AVAILABLE(macos(12.0), ios(18.0), macCatalyst(15.0)) API_UNAVAILABLE(tvos, watchos, visionos);

/*!
 @enum AVCaptionRegionWritingMode
 @abstract
    Choices for region writing mode

 @constant AVCaptionRegionWritingModeLeftToRightAndTopToBottom
 @constant AVCaptionRegionWritingModeTopToBottomAndRightToLeft
 */
typedef NS_ENUM(NSInteger, AVCaptionRegionWritingMode) {
	AVCaptionRegionWritingModeLeftToRightAndTopToBottom  = 0,
	AVCaptionRegionWritingModeTopToBottomAndRightToLeft  = 2,
} API_AVAILABLE(macos(12.0), ios(18.0), macCatalyst(15.0)) API_UNAVAILABLE(tvos, watchos, visionos);

/*!
 @enum AVCaptionRegionScroll
 @abstract
	Scrolling effect for a region
 @constant AVCaptionRegionScrollNone

 @constant AVCaptionRegionScrollRollUp
 */
typedef NS_ENUM(NSInteger, AVCaptionRegionScroll) {
	AVCaptionRegionScrollNone   = 0,
	AVCaptionRegionScrollRollUp = 1,
} API_AVAILABLE(macos(12.0), ios(18.0), macCatalyst(15.0)) API_UNAVAILABLE(tvos, watchos, visionos);

/*!
 @class AVCaptionRegion
 @abstract
	An instance of AVCaptionRegion represents a region where a caption is placed.
 @discussion
	Currently, there is just four predefined region instances. The interface doesn't support configuration of region settings.
 */
API_AVAILABLE(macos(12.0), ios(18.0), macCatalyst(15.0)) API_UNAVAILABLE(tvos, watchos, visionos)
@interface AVCaptionRegion : NSObject <NSCopying, NSMutableCopying, NSSecureCoding>

/*!
  @property appleITTTopRegion
  @abstract
	The top region for iTT format
  @discussion
	This region can be used in iTT format and it occupies the top 15% of the display area. The region uses LRTB, a line progresses left to right and the block extends from top to bottom. Each line is stacked with top justified.
 */
@property (class, readonly) AVCaptionRegion  * appleITTTopRegion;

/*!
  @property appleITTBottomRegion
  @abstract
	The bottom region for iTT format
  @discussion
	This region can be used in iTT format and it occupies the bottom 15% of the display area. The region uses LRTB, a line progresses left to right and the block extends from top to bottom. Each line is stacked with bottom justified.
 */
@property (class, readonly) AVCaptionRegion  * appleITTBottomRegion;

/*!
  @property appleITTLeftRegion
  @abstract
	The  left region for iTT format
  @discussion
	This region can be used in iTT format and it occupies the left 15% of the display area. The region uses TBRL, a line progresses top to bottom and the block extends from right to left. Each line is stacked with right justified.
 */
@property (class, readonly) AVCaptionRegion  * appleITTLeftRegion;

/*!
  @property appleITTRightRegion
  @abstract
	The right region for iTT format
  @discussion
	This region can be used in iTT format and it occupies the right 15% of the display area. The region uses TBRL, a line progresses top to bottom and the block extends from right to left. Each line is stacked with right justified.
 */
@property (class, readonly) AVCaptionRegion  * appleITTRightRegion;

/*!
  @property subRipTextBottomRegion
  @abstract
	The bottom region for SubRip Text (SRT) format
  @discussion
	This region can be used in SRT format and it occupies the entire video display area. The region uses LRTB, a line progresses left to right and the block extends from top to bottom. Each line is stacked with bottom justified.
 */
@property (class, readonly) AVCaptionRegion  * subRipTextBottomRegion;

/*!
  @property identifier
  @abstract
    Identifier for the region
  @discussion
    When regionIdentifier is nil, two regions with the same position and endPosition are considered to be same, that is
    captions referring these regions belong to the same region when serialized to a format like TTML.  In addition, the
	AVCaptionRegion cannot be mutably copied.

    When regionIdentifier is not nil, two regions are same if and only if the region identifier is equal. It is a
    client's responsibility to ensure these AVCaptionRegion objects have the same properties.
 */
@property (nonatomic, readonly, nullable) NSString *identifier;

/*!
  @property origin
  @abstract
	The position of the top-left of the region, potentially with unspecified fields.
  @discussion
	It returns an AVCaptionPoint potentially with unspecified x and/or y fields. Unspecified dimensions indicate the region doesn't have positioning information for that dimension.
 */
@property (nonatomic, readonly) AVCaptionPoint origin;

/*!
  @property size
  @abstract
	The width and height of the region, potentally with unspecified fields.
  @discussion
	It returns an AVCaptionSize potentially with unspecified width and/or height.
	CEA608 closed captions support limits the size.height property’s value to 1 cell except when the AVCaptionRegionScroll is AVCaptionRegionScrollRollUp.
 If the AVCaptionRegionScroll is AVCaptionRegionScrollRollUp, the size.height property’s value must be 2, 3 or 4 cells.
	It returns an AVCaptionSize with unspecifed width and height when the region doesn't have width or height information.
 */
@property (nonatomic, readonly) AVCaptionSize size;

/*!
  @property scroll
  @abstract
    Scroll mode for the region
  @discussion
    See AVCaptionRegionScrollXXX enum for possible values.
 */
@property (nonatomic, readonly) AVCaptionRegionScroll scroll;

/*!
  @property displayAlignment
  @abstract
    Alignment of lines for the region
 */
@property (nonatomic, readonly) AVCaptionRegionDisplayAlignment displayAlignment;

/*!
  @property writingMode
  @abstract
    The block and inline progression direction of the region.
 */
@property (nonatomic, readonly) AVCaptionRegionWritingMode writingMode;

/*!
  @method encodeWithCoder:
  @abstract
	NSCoding protocol method override
  @discussion
	This method throws an exception if the caption region's size has different units for width and height, or if the units are unrecognizeable.
 */
- (void)encodeWithCoder:(NSCoder *)encoder;

/*!
  @method isEqual:
  @abstract
	NSObject protocol method override
  @discussion
	This method throws an exception if the caption region's size has different units for width and height, or if the units are unrecognizeable.
 */

- (BOOL)isEqual:(id)object;

/*!
  @method mutableCopyWithZone:
  @abstract
	NSMutableCopying protocol method override
  @discussion
	This method throws an exception if the caption region contains an identifier.
 */
- (id)mutableCopyWithZone:(nullable NSZone *)zone;

@end

/*!
 @class AVMutableCaptionRegion
 @abstract
	Mutable subclass of AVCaptionRegion.
 */
NS_SWIFT_NONSENDABLE
API_AVAILABLE(macos(12.0), ios(18.0), macCatalyst(15.0)) API_UNAVAILABLE(tvos, watchos, visionos)
@interface AVMutableCaptionRegion : AVCaptionRegion

/*!
  @method init
  @abstract
    Create a region object without any properties.
 */
- (instancetype)init;

/*!
  @method initWithIdentifier:
  @abstract
    Create a region object with the identifier.
 */
- (instancetype)initWithIdentifier:(NSString *)identifier;

/*!
  @property origin
  @abstract
	The position of the top-left of the region.
 */
@property (nonatomic, assign) AVCaptionPoint 	origin;

/*!
  @property size
  @abstract
	The width and height of the region, potentally with unspecified fields.
 */
@property (nonatomic, assign) AVCaptionSize size;

/*!
  @property scroll
  @abstract
    Region scroll mode.
 */
@property (nonatomic, assign) AVCaptionRegionScroll scroll;

/*!
  @property displayAlignment
  @abstract
    Alignment of lines in the region.
 */
@property (nonatomic, assign) AVCaptionRegionDisplayAlignment displayAlignment API_AVAILABLE(macos(12.0), ios(18.0), macCatalyst(15.0)) API_UNAVAILABLE(tvos, watchos, visionos);

/*!
  @property writingMode
  @abstract
    The block and inline progression direction of the region.
 */
@property (nonatomic, assign) AVCaptionRegionWritingMode writingMode API_AVAILABLE(macos(12.0), ios(18.0), macCatalyst(15.0)) API_UNAVAILABLE(tvos, watchos, visionos);
@end

/*!
 @enum AVCaptionAnimation
 @abstract
	Animation effect for a caption
 @constant AVCaptionAnimationNone

 @constant AVCaptionAnimationCharacterReveal
 */
typedef NS_ENUM(NSInteger, AVCaptionAnimation) {
	AVCaptionAnimationNone = 0,
	AVCaptionAnimationCharacterReveal = 1,
} API_AVAILABLE(macos(12.0), ios(18.0), macCatalyst(15.0)) API_UNAVAILABLE(tvos, watchos, visionos);

/*!
 @class AVCaption
 @abstract
	An instance of AVCaption represents a unit of text that is active at a particular time range. 
 @discussion
	A caption contains one meaningful sentence, paragraph, or otherwise known as a caption cue. Within the active time range, it may perform animation (e.g. Karaoke), rolling-up, changes the visibility, or any other dynamic styling.
 */
API_AVAILABLE(macos(12.0), ios(18.0), macCatalyst(15.0)) API_UNAVAILABLE(tvos, watchos, visionos)
@interface AVCaption : NSObject <NSCopying, NSMutableCopying, NSSecureCoding>
AV_INIT_UNAVAILABLE

/*!
 @method initWithText:timeRange:
 @abstract
	Initializes an instance of AVCaption with the given text and time range.
 @param text
	The text for the new caption object. See text property for the available character sets and other restrictions.
 @param timeRange
	The time range for the new caption object.
 @result
	An instance of AVCaption that carries the given text and time range.
 */
- (instancetype)initWithText:(NSString *)text timeRange:(CMTimeRange)timeRange NS_DESIGNATED_INITIALIZER;

/*!
 @property text
 @abstract
	The text content of the caption.
 @discussion
 	The text may contain any of the line breaking character sequences (LF, CR, or CF+LF) and separating the lines in the presentation.

	The Apple iTT format supports all Unicode code points allowed in a XML document. Any XML special characters such as '&' are converted to a corresponding character reference syntax when written to the destination file.

	CEA608 closed captions support the following Unicode characters.
		Range: U+0020 - U+005F
		Range: U+0061 - U+007E
		Range: U+00A1 - U+00A5
		Characters: U+00A9, U+00AB, U+00AE, U+00B0, U+00BB, U+00BD, U+00BF
		Range: U+00C0-U+00C5
		Range: U+00C7-U+00CF
		Range: U+00D1-U+00D6
		Range: U+00D8-U+00DC
		Range: U+00DF-U+00E5
		Range: U+00E7-U+00EF
		Range: U+00F1-U+00FC
		Range: U+2018-U+2019
		Range: U+2018-U+201D
		Character: U+2022
		Range: U+2120-U+2122
		Characters: U+2501, U+2503, U+250F, U+2513, U+2517, U+251B, U+2588, U+266A

	CEA608 closed captions don't support the line breaking character sequences (LF, CR, or CF+LF).
 */
@property (nonatomic, readonly) NSString *text;

/*!
 @property timeRange
 @abstract
	The time range during which the caption should be presented.

	Apple iTT format doesn't allow two captions to have overlapped time range except when the two captions are associated with different regions.

	CEA608 closed caption time ranges can't start with zero, because the decoder needs some transmission time.
	CEA608 closed caption time ranges should be aligned with the video frame rate because this is how often the commands are delivered.
 */
@property (nonatomic, readonly) CMTimeRange timeRange;

@end

/*!
 @class AVMutableCaption
 @abstract
	Mutable subclass of AVCaption.
 */
NS_SWIFT_NONSENDABLE
API_AVAILABLE(macos(12.0), ios(18.0), macCatalyst(15.0)) API_UNAVAILABLE(tvos, watchos, visionos)
@interface AVMutableCaption : AVCaption

/*!
 @property text
 @abstract
	The text content of the caption.
 @discussion
	All styling information is cleared on setting this property.
 */
@property (nonatomic, copy) NSString *text;

/*!
 @property timeRange
 @abstract
	The time range during which the caption should be presented.
 */
@property (nonatomic, assign) CMTimeRange timeRange;

@end

/*!
 @enum AVCaptionFontWeight
 @abstract
	Choices for font weight.
 @constant AVCaptionFontWeightUnknown Font weight is unknown.
 @constant AVCaptionFontWeightNormal Font weight is normal (i.e., not bold).
 @constant AVCaptionFontWeightBold Font weight is bold.

 */
typedef NS_ENUM(NSInteger, AVCaptionFontWeight) {
	AVCaptionFontWeightUnknown = 0,
	AVCaptionFontWeightNormal = 1,
	AVCaptionFontWeightBold = 2
} API_AVAILABLE(macos(12.0), ios(18.0), macCatalyst(15.0)) API_UNAVAILABLE(tvos, watchos, visionos);

/*!
 @enum AVCaptionFontStyle
 @abstract
	Choices for character style.
 @constant AVCaptionFontStyleUnknown Font style is not specified.
 @constant AVCaptionFontStyleNormal Font is normal (i.e., not italic)
 @constant AVCaptionFontStyleItalic Font is italic.

 */
typedef NS_ENUM(NSInteger, AVCaptionFontStyle) {
	AVCaptionFontStyleUnknown = 0,
	AVCaptionFontStyleNormal = 1,
	AVCaptionFontStyleItalic = 2
} API_AVAILABLE(macos(12.0), ios(18.0), macCatalyst(15.0)) API_UNAVAILABLE(tvos, watchos, visionos);

/*!
 @enum AVCaptionDecoration
 @abstract
	Choices for character decoration .
 @constant AVCaptionDecorationNone Text is not decorated..
 @constant AVCaptionDecorationUnderline Text is underlined.
 @constant AVCaptionDecorationLineThrough Text has a strike through it.
 @constant AVCaptionDecorationOverline Text has a line above the it.

 */
typedef NS_OPTIONS(NSUInteger, AVCaptionDecoration) {
	AVCaptionDecorationNone        = 0,
	AVCaptionDecorationUnderline   = 1 << 0,
	AVCaptionDecorationLineThrough = 1 << 1,
	AVCaptionDecorationOverline    = 1 << 2,
} API_AVAILABLE(macos(12.0), ios(18.0), macCatalyst(15.0)) API_UNAVAILABLE(tvos, watchos, visionos);

/*!
 @enum AVCaptionTextCombine
 @abstract
	Choices for text combine.

 @discussion
	Text combine is a special rendering policy to combine multiple characters into one unit and present it in upright position in a vertical text flow in order to accomplish so-called "Tate-Chu-Yoko" layout, or horizontal-in-vertical layout.

	For example, it can be used to render "2017" horizontally in a vertical text.

 @constant AVCaptionTextCombineNone
	Don't combine text upright. It is the same as not specifying the style.

 @constant AVCaptionTextCombineAll
	Combine all the characters.

 @constant AVCaptionTextCombineOneDigit
	Make one digit upright.

 @constant AVCaptionTextCombineTwoDigits
	Combine two consecutive digits

 @constant AVCaptionTextCombineThreeDigits
	Combine three consecutive digits

 @constant AVCaptionTextCombineFourDigits
	Combine four consecutive digits
 */
typedef NS_ENUM(NSInteger, AVCaptionTextCombine) {
	AVCaptionTextCombineAll         = -1,
	AVCaptionTextCombineNone        = 0,
	AVCaptionTextCombineOneDigit    = 1,
	AVCaptionTextCombineTwoDigits   = 2,
	AVCaptionTextCombineThreeDigits = 3,
	AVCaptionTextCombineFourDigits  = 4,
} API_AVAILABLE(macos(12.0), ios(18.0), macCatalyst(15.0)) API_UNAVAILABLE(tvos, watchos, visionos);

/*!
 @enum AVCaptionTextAlignment
 @abstract
	Alignment of a caption within the containing region.
 @constant AVCaptionTextAlignmentStart
	Aligned to the start of inline progression direction; e.g. left in left-to-right writing mode and right in right-to-left writing mode.
 @constant AVCaptionTextAlignmentEnd
	Aligned to the end of inline progression direction; e.g. right in left-to-right writing mode and right in right-to-left writing mode.
 @constant AVCaptionTextAlignmentCenter
	Aligned at center in inline progression direction.
 @constant AVCaptionTextAlignmentLeft
	Aligned to left in horizontal writing mode or top in vertical writing mode.
 @constant AVCaptionTextAlignmentRight
	Aligned to right in horizontal writing mode or bottom in vertical writing mode.
 */
typedef NS_ENUM(NSInteger, AVCaptionTextAlignment) {
	AVCaptionTextAlignmentStart     = 0,
	AVCaptionTextAlignmentEnd       = 1,
	AVCaptionTextAlignmentCenter    = 2,
	AVCaptionTextAlignmentLeft      = 3,
	AVCaptionTextAlignmentRight     = 4,
} API_AVAILABLE(macos(12.0), ios(18.0), macCatalyst(15.0)) API_UNAVAILABLE(tvos, watchos, visionos);


@interface AVCaption (Styling)

/*!
 @method textColorAtIndex:range:
 @abstract
	The color of the character(s).
 @discussion
	A value of NULL means that the color is not specified. The caller must release the returned object via CGColorRelease. The range parameter receives UTF-16 code unit index range the style is effective. The range will indicate where the current style returned (including NULL) will be active and allows discovery of the next change in the style.

	CEA608 closed captions support the following 8 colors with 1.0 alpha value.
		White	(RGB:1.0, 1.0, 1.0)
		Red		(RGB:1.0, 0.0, 0.0)
		Blue	(RGB:0.0, 0.0, 1.0)
		Green	(RGB:0.0, 1.0, 0.0)
		Yellow	(RGB:1.0, 1.0, 0.0)
		Cyan	(RGB:0.0, 1.0, 1.0)
		Magenta	(RGB:1.0, 0.0, 1.0)
		Black	(RGB:0.0, 0.0, 0.0)
 */
- (nullable CGColorRef)textColorAtIndex:(NSInteger)index range:(nullable NSRange *)outRange CF_RETURNS_RETAINED;

/*!
 @method backgroundColorAtIndex:range:
 @abstract
	The background color of the character(s).
 @discussion
	A value of NULL means that the color is not specified. The caller must release the returned object via CGColorRelease. The range parameter receives UTF-16 code unit index range the style is effective. After returning from the call, the range will indicate where the current style returned (including NULL) will be active and allows discovery of the next change in the style.

	iTT format ignores this property.

	CEA608 closed captions support the following 8 colors with 1.0, 0.5 and 0.0 alpha values.
		White	(RGB:1.0, 1.0, 1.0)
		Red		(RGB:1.0, 0.0, 0.0)
		Blue	(RGB:0.0, 0.0, 1.0)
		Green	(RGB:0.0, 1.0, 0.0)
		Yellow	(RGB:1.0, 1.0, 0.0)
		Cyan	(RGB:0.0, 1.0, 1.0)
		Magenta	(RGB:1.0, 0.0, 1.0)
		Black	(RGB:0.0, 0.0, 0.0)
 */
- (nullable CGColorRef)backgroundColorAtIndex:(NSInteger)index range:(nullable NSRange *)outRange CF_RETURNS_RETAINED;

/*!
 @method fontWeightAtIndex:range:
 @abstract
	Indicates the font weight of the character(s).
 @discussion
	The range parameter receives UTF-16 code unit index range the style is effective. After returning from the call, the range will indicate where the current style returned will be active and allows discovery of the next change in the style.

	CEA608 closed captions ignore this property.
 
 	A visible distinction between AVCaptionFontWeightNormal and AVCaptionFontWeightBold may not exist if the font used has only one weight. This can be more common with CJK fonts where individual fonts can be quite large in terms of storage. Nevertheless, AVCaption still carries the font weight semantics so if the same AVCaption is applied to a different font having multiple weights, the distinction will become visible.
 */
- (AVCaptionFontWeight)fontWeightAtIndex:(NSInteger)index range:(nullable NSRange *)outRange;

/*!
 @method fontStyleAtIndex:range:
 @abstract
	Indicates the font style of the character(s).
 @discussion
	The range parameter receives UTF-16 code unit index range the style is effective. After returning from the call, the range will indicate where the current style returned will be active and allows discovery of the next change in the style.
 
 	Some writing systems may not have italic glyphs for characters and so fonts with italic forms are not available. For example, Japanese fonts do not typically have italic forms for most characters although there may be special cases for Latin characters. Nevertheless, AVCaption still carries the font style semantics even though there may be no visible rendering distinction between using AVCaptionFontStyleNormal and AVCaptionFontStyleItalic with that language.
 */
- (AVCaptionFontStyle)fontStyleAtIndex:(NSInteger)index range:(nullable NSRange *)outRange;

/*!
 @method	decorationAtIndex:range:
 @abstract	Character decoration
 @discussion
 	The value of OR-ed value of AVCaptionDecoration as NSInteger. The range parameter receives UTF-16 code unit index range the style is effective. After returning from the call, the range will indicate where the current style returned will be active and allows discovery of the next change in the style.

	CEA608 closed captions support only AVCaptionDecorationNone and AVCaptionDecorationUnderline.
*/
- (AVCaptionDecoration)decorationAtIndex:(NSInteger)index range:(nullable NSRange *)outRange;

/*!
  @method	textCombineAtIndex:range:
  @abstract	Text combine (Tate-Chu-Yoko)
  @discussion
	The style is effective only in a vertical text region.

	When specified, the renderer combines all the characters in the style range so that their glyph areas consume the nominal bounding box of a single em square of the surrounding vertical text.
 */
- (AVCaptionTextCombine)textCombineAtIndex:(NSInteger)index range:(nullable NSRange *)outRange;

/*!
  @method	rubyAtIndex:range:
  @abstract Get Ruby associated with the characters.
  @discussion
 	The range parameter receives UTF-16 code unit index range where the ruby text is applied. After returning from the call, the range will indicate where the current style returned (including NULL) will be active and allows discovery of the next change in the style.

	It returns nil when the text doesn't have a ruby at the position.

	CEA608 closed captions ignore this property.
 */
- (nullable AVCaptionRuby *)rubyAtIndex:(NSInteger)index range:(nullable NSRange *)outRange;

@end

@interface AVCaption (Region)
/*!
 @property region
 @abstract
	The region where the caption is placed.
 @discussion
	It can be nil when the underlying caption format doesn't support or use regions.
 */
@property (nonatomic, readonly, nullable) AVCaptionRegion *region;

/*!
  @property textAlignment
  @abstract
	The text alignment within the containing region.
  @discussion
	This property throws an exception if a value is set which is not a valid AVCaptionTextAlignment.
 */
@property (nonatomic, readonly) AVCaptionTextAlignment textAlignment;
@end

@interface AVCaption (Animation)
@property (nonatomic, readonly) AVCaptionAnimation animation;
@end

@interface AVMutableCaption (Styling)

/*!
  @method	setTextColor:inRange:
  @abstract Set text color for the range.
  @discussion
 	The range parameter uses UTF-16 code unit index range.
 */
- (void)setTextColor:(CGColorRef)color inRange:(NSRange)range;

/*!
  @method	setBackgroundColor:inRange:
  @abstract Set background color for the range.
  @discussion
 	The range parameter uses UTF-16 code unit index range.
 */
- (void)setBackgroundColor:(CGColorRef)color inRange:(NSRange)range;

/*!
  @method	setFontWeight:inRange:
  @abstract Set font weight for the range.
  @discussion
 	The range parameter uses UTF-16 code unit index range.
 */
- (void)setFontWeight:(AVCaptionFontWeight)fontWeight inRange:(NSRange)range;

/*!
  @method	setFontStyle:inRange:
  @abstract Set font style for the range.
  @discussion
 	The range parameter uses UTF-16 code unit index range.
 */
- (void)setFontStyle:(AVCaptionFontStyle)fontStyle inRange:(NSRange)range;

/*!
  @method	setDecoration:inRange:
  @abstract Set text decoration for the range.
  @discussion
 	The range parameter uses UTF-16 code unit index range.
 */
- (void)setDecoration:(AVCaptionDecoration)decoration inRange:(NSRange)range;

/*!
  @method	setTextCombine:inRange:
  @abstract Set text combine for the range.
  @discussion
 	The range parameter uses UTF-16 code unit index range.
 */
- (void)setTextCombine:(AVCaptionTextCombine)textCombine inRange:(NSRange)range;

/*!
  @method	setRuby:inRange:
  @abstract Set ruby text  for the range.
  @discussion
 	The range parameter uses UTF-16 code unit index range.
 */
- (void)setRuby:(AVCaptionRuby *)ruby inRange:(NSRange)range;

/*!
  @method	removeTextColorInRange:
  @abstract Remove text color for the range.
  @discussion
 	The range parameter uses UTF-16 code unit index range.
 */
- (void)removeTextColorInRange:(NSRange)range;

/*!
  @method	removeBackgroundColorInRange:
  @abstract Remove background color for the range.
  @discussion
 	The range parameter uses UTF-16 code unit index range.
 */
- (void)removeBackgroundColorInRange:(NSRange)range;

/*!
  @method	removeFontWeightInRange:
  @abstract Remove font weight for the range.
  @discussion
 	The range parameter uses UTF-16 code unit index range.
 */
- (void)removeFontWeightInRange:(NSRange)range;

/*!
  @method	removeFontStyleInRange:
  @abstract Remove font style for the range.
  @discussion
 	The range parameter uses UTF-16 code unit index range.
 */
- (void)removeFontStyleInRange:(NSRange)range;

/*!
  @method	removeDecorationInRange:
  @abstract Remove text decoration for the range.
  @discussion
 	The range parameter uses UTF-16 code unit index range.
 */
- (void)removeDecorationInRange:(NSRange)range;

/*!
  @method	removeTextCombineInRange:
  @abstract Remove text combine for the range.
  @discussion
 	The range parameter uses UTF-16 code unit index range.
 */
- (void)removeTextCombineInRange:(NSRange)range;

/*!
  @method	removeRubyInRange:
  @abstract Remove ruby text  for the range.
  @discussion
	The range parameter uses UTF-16 code unit index range.
 */
- (void)removeRubyInRange:(NSRange)range;

@end

@interface AVMutableCaption (Region)
/*!
 @property region
 @abstract
	The region where the caption is placed.
 @discussion
	It can be nil when the underlying caption format doesn't support or use regions.
	This property throws an exception if region has unrecognizeable units.
 */
@property (nonatomic, copy) AVCaptionRegion *region;

/*!
  @property textAlignment
  @abstract
	The text alignemnt within the containing region.
 */
@property (nonatomic, assign) AVCaptionTextAlignment textAlignment;
@end

@interface AVMutableCaption (Animation)
@property (nonatomic, assign) AVCaptionAnimation animation;
@end

/*!
 @enum AVCaptionRubyPosition
 @abstract
    Choices for Ruby position
 @constant AVCaptionRubyPositionBefore
    Display Ruby text above horizontal text or right of vertical text in a right to left block progression.
 @constant AVCaptionRubyPositionAfter
    Display Ruby text below horizontal text or left of vertical text in a right to left block progression.
 */
typedef NS_ENUM(NSInteger, AVCaptionRubyPosition) {
	AVCaptionRubyPositionBefore = 0,
	AVCaptionRubyPositionAfter  = 1,
} API_AVAILABLE(macos(12.0), ios(18.0), macCatalyst(15.0)) API_UNAVAILABLE(tvos, watchos, visionos);

/*!
 @enum AVCaptionRubyAlignment
 @abstract
    Choices for Ruby alignment

 @discussion
	Given a ruby text rendering area denoted as [...], each spacing policy works as follows.

	Start          [Ruby Text         ]

	Center         [     Ruby Text    ]

	SpaceBetween   [R u b y  T e x t]    <- 'R' and 't' are aligned with start end end edges, spaces between each Ruby text character is equal.

	SpaceAround    [ R u b y  T e x t ]  <- Spaces around each Ruby text character is equal

 @constant AVCaptionRubyAlignmentStart
    Align Ruby base and text at left edge of horizontal text in a left to right inline progression, or at top of the vertical text in a top to bottom inline progression.
 @constant AVCaptionRubyAlignmentCenter
    Align Ruby text at the center of Ruby base.
 @constant AVCaptionRubyAlignmentDistributeSpaceBetween
    Align Ruby text so that the spaces between the Ruby text characters are equal. This is the default.
 @constant AVCaptionRubyAlignmentDistributeSpaceAround
    Align Ruby text so that the spaces around each Ruby text character are equal.
 */
typedef NS_ENUM(NSInteger, AVCaptionRubyAlignment) {
	AVCaptionRubyAlignmentStart                  = 0,
	AVCaptionRubyAlignmentCenter                 = 1,
	AVCaptionRubyAlignmentDistributeSpaceBetween = 2,
	AVCaptionRubyAlignmentDistributeSpaceAround  = 3,
} API_AVAILABLE(macos(12.0), ios(18.0), macCatalyst(15.0)) API_UNAVAILABLE(tvos, watchos, visionos);

/*!
 @class AVCaptionRuby
 @discussion
	Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
*/
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(12.0), ios(18.0), macCatalyst(15.0)) API_UNAVAILABLE(tvos, watchos, visionos)
@interface AVCaptionRuby : NSObject <NSCopying, NSSecureCoding>
AV_INIT_UNAVAILABLE

- (instancetype)initWithText:(NSString *)text NS_DESIGNATED_INITIALIZER;

- (instancetype)initWithText:(NSString *)text position:(AVCaptionRubyPosition)position alignment:(AVCaptionRubyAlignment)alignment;

/*!
 @property text
 @abstract
	The ruby text
 */
@property (nonatomic, readonly) NSString *text;

/*!
 @property position
 @abstract
	The position of ruby text with respect to the ruby base.
 */
@property (nonatomic, readonly) AVCaptionRubyPosition position;

/*!
 @property alignment
 @abstract
	The alignment of ruby text.
 */
@property (nonatomic, readonly) AVCaptionRubyAlignment alignment;

@end

NS_ASSUME_NONNULL_END

#endif // ( TARGET_OS_OSX || ( TARGET_OS_IOS && ! TARGET_OS_VISION ) )

#else
#import <AVFCore/AVCaption.h>
#endif
