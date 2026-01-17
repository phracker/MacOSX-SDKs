/*
	NSTextInputClient.h
	Application Kit
	Copyright (c) 2006-2015, Apple Inc.
	All rights reserved.
 */

#import <Foundation/NSObject.h>
#import <Foundation/NSArray.h>
#import <Foundation/NSRange.h>
#import <Foundation/NSGeometry.h>

NS_ASSUME_NONNULL_BEGIN

@class NSAttributedString;

@protocol NSTextInputClient
@required
/* The receiver inserts aString replacing the content specified by replacementRange. aString can be either an NSString or NSAttributedString instance.
*/
- (void)insertText:(id)aString replacementRange:(NSRange)replacementRange;

/* The receiver invokes the action specified by aSelector.
*/
 - (void)doCommandBySelector:(SEL)aSelector;
 
/* The receiver inserts aString replacing the content specified by replacementRange. aString can be either an NSString or NSAttributedString instance. selectedRange specifies the selection inside the string being inserted; hence, the location is relative to the beginning of aString. When aString is an NSString, the receiver is expected to render the marked text with distinguishing appearance (i.e. NSTextView renders with -markedTextAttributes).
*/
- (void)setMarkedText:(id)aString selectedRange:(NSRange)selectedRange replacementRange:(NSRange)replacementRange;

/* The receiver unmarks the marked text. If no marked text, the invocation of this method has no effect.
*/
- (void)unmarkText;

/* Returns the selection range. The valid location is from 0 to the document length.
*/
- (NSRange)selectedRange;

/* Returns the marked range. Returns {NSNotFound, 0} if no marked range.
*/
- (NSRange)markedRange;

/* Returns whether or not the receiver has marked text.
*/
- (BOOL)hasMarkedText;

/* Returns attributed string specified by aRange. It may return nil. If non-nil return value and actualRange is non-NULL, it contains the actual range for the return value. The range can be adjusted from various reasons (i.e. adjust to grapheme cluster boundary, performance optimization, etc).
*/
- (nullable NSAttributedString *)attributedSubstringForProposedRange:(NSRange)aRange actualRange:(nullable NSRangePointer)actualRange;

/* Returns an array of attribute names recognized by the receiver.
*/
- (NSArray<NSString *> *)validAttributesForMarkedText;

/* Returns the first logical rectangular area for aRange. The return value is in the screen coordinate. The size value can be negative if the text flows to the left. If non-NULL, actuallRange contains the character range corresponding to the returned area.
*/
- (NSRect)firstRectForCharacterRange:(NSRange)aRange actualRange:(nullable NSRangePointer)actualRange;

/* Returns the index for character that is nearest to aPoint. aPoint is in the screen coordinate system.
*/
- (NSUInteger)characterIndexForPoint:(NSPoint)aPoint;

@optional
/* Returns an attributed string representing the receiver's document content. An NSTextInputClient can implement this interface if can be done efficiently. The caller of this interface can random access arbitrary portions of the receiver's content more efficiently.
*/
- (NSAttributedString *)attributedString;

/* Returns the fraction of distance for aPoint from the left side of the character. This allows caller to perform precise selection handling.
*/
- (CGFloat)fractionOfDistanceThroughGlyphForPoint:(NSPoint)aPoint;

/* Returns the baseline position relative to the origin of rectangle returned by -firstRectForCharacterRange:actualRange:. This information allows the caller to access finer-grained character position inside the NSTextInputClient document.
*/
- (CGFloat)baselineDeltaForCharacterAtIndex:(NSUInteger)anIndex;

/* Returns the window level of the receiver. An NSTextInputClient can implement this interface to specify its window level if it is higher than NSFloatingWindowLevel.
*/
- (NSInteger)windowLevel;

/* Returns if the marked text is in vertical layout.
 */
- (BOOL)drawsVerticallyForCharacterAtIndex:(NSUInteger)charIndex NS_AVAILABLE_MAC(10_6);
@end

NS_ASSUME_NONNULL_END
