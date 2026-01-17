#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UITextInput.h>)
//
//  UITextInput.h
//  UIKit
//
//  Copyright (c) 2009-2018 Apple Inc. All rights reserved.
//

#import <CoreGraphics/CoreGraphics.h>

#import <UIKit/UITextInputTraits.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIResponder.h>
#import <UIKit/NSText.h>


//===================================================================================================
// Responders that implement the UIKeyInput protocol will be driven by the system-provided keyboard,
// which will be made available whenever a conforming responder becomes first responder.

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@protocol UIKeyInput <UITextInputTraits>

@property(nonatomic, readonly) BOOL hasText API_UNAVAILABLE(watchos);
- (void)insertText:(NSString *)text;
- (void)deleteBackward;

@end

//===================================================================================================
// Responders that implement the UITextInput protocol allow the system-provided keyboard to
// offer more sophisticated behaviors based on a current selection and context.

@class NSTextAlternatives;
@class UITextPosition;
@class UITextRange;
@class UITextSelectionRect;
@class UIBarButtonItemGroup;
@class UIBarButtonItem;
@class NSAdaptiveImageGlyph;
@class NSAttributedString;
@class UIConversationContext;
@class UIInputSuggestion;

@protocol UITextInputTokenizer;
@protocol UITextInputDelegate;
@protocol UIEditMenuInteractionAnimating;

typedef NS_ENUM(NSInteger, UITextStorageDirection) {
    UITextStorageDirectionForward = 0,
    UITextStorageDirectionBackward
} API_UNAVAILABLE(watchos);

typedef NS_ENUM(NSInteger, UITextLayoutDirection) {
    UITextLayoutDirectionRight = 2,
    UITextLayoutDirectionLeft,
    UITextLayoutDirectionUp,
    UITextLayoutDirectionDown
} API_UNAVAILABLE(watchos);

typedef NSInteger UITextDirection NS_TYPED_ENUM API_UNAVAILABLE(watchos);

typedef NS_ENUM(NSInteger, UITextGranularity) {
    UITextGranularityCharacter,
    UITextGranularityWord,
    UITextGranularitySentence,
    UITextGranularityParagraph,
    UITextGranularityLine,
    UITextGranularityDocument
} API_UNAVAILABLE(watchos);

UIKIT_EXTERN API_AVAILABLE(ios(5.1)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UIDictationPhrase : NSObject {
    @private
        NSString *_text;
        NSArray * __nullable _alternativeInterpretations;
}

/* -text returns the most likely interpretation for a phrase. If there are other 
 * interpretations, -alternativeInterpretations will return an array of them, with 
 * the first being most likely and the last being least likely. */
@property (nonatomic, readonly) NSString *text;
@property (nullable, nonatomic, readonly) NSArray<NSString *> *alternativeInterpretations;

@end

UIKIT_EXTERN API_AVAILABLE(ios(9.0), visionos(2.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UITextInputAssistantItem : NSObject

/// Default is YES, controls if the user is allowed to hide the shortcuts bar. Does not influence the built in auto-hiding logic.
@property (nonatomic, readwrite, assign) BOOL allowsHidingShortcuts API_UNAVAILABLE(visionos);
/// Contains UIBarButtonItemGroups that should be displayed in the leading position on the keyboard's assistant bar.
@property (nonatomic, readwrite, copy) NSArray<UIBarButtonItemGroup *> *leadingBarButtonGroups API_UNAVAILABLE(visionos);
/// Contains UIBarButtonItemGroups that should be displayed in the trailing position on the keyboard's assistant bar.
@property (nonatomic, readwrite, copy) NSArray<UIBarButtonItemGroup *> *trailingBarButtonGroups API_UNAVAILABLE(visionos);
/// A button that appears next to the text preview in the keyboard on visionOS.
@property (nullable, nonatomic, strong) UIBarButtonItem *keyboardActionButtonItem NS_SWIFT_NAME(keyboardAction) API_AVAILABLE(visionos(2.0)) API_UNAVAILABLE(ios, watchos, tvos);

@end

UIKIT_EXTERN API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UITextPlaceholder : NSObject
// Return the rects of the placeholder
@property (nonatomic, readonly) NSArray<UITextSelectionRect *> *rects;
@end

typedef NS_ENUM(NSInteger, UITextAlternativeStyle) {
    UITextAlternativeStyleNone,
    UITextAlternativeStyleLowConfidence
} API_UNAVAILABLE(watchos);

API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@protocol UITextInput <UIKeyInput>
@required

/* Methods for manipulating text. */
- (nullable NSString *)textInRange:(UITextRange *)range;
- (void)replaceRange:(UITextRange *)range withText:(NSString *)text;

/* Text may have a selection, either zero-length (a caret) or ranged.  Editing operations are
 * always performed on the text from this selection.  nil corresponds to no selection. */

@property (nullable, readwrite, copy) UITextRange *selectedTextRange;

/* If text can be selected, it can be marked. Marked text represents provisionally
 * inserted text that has yet to be confirmed by the user.  It requires unique visual
 * treatment in its display.  If there is any marked text, the selection, whether a
 * caret or an extended range, always resides within.
 *
 * Setting marked text either replaces the existing marked text or, if none is present,
 * inserts it from the current selection. */ 

@property (nullable, nonatomic, readonly) UITextRange *markedTextRange; // Nil if no marked text.
@property (nullable, nonatomic, copy) NSDictionary<NSAttributedStringKey, id> *markedTextStyle; // Describes how the marked text should be drawn.
- (void)setMarkedText:(nullable NSString *)markedText selectedRange:(NSRange)selectedRange; // selectedRange is a range within the markedText
- (void)unmarkText;

/* The end and beginning of the the text document. */
@property (nonatomic, readonly) UITextPosition *beginningOfDocument;
@property (nonatomic, readonly) UITextPosition *endOfDocument;

/* Methods for creating ranges and positions. */
- (nullable UITextRange *)textRangeFromPosition:(UITextPosition *)fromPosition toPosition:(UITextPosition *)toPosition;
- (nullable UITextPosition *)positionFromPosition:(UITextPosition *)position offset:(NSInteger)offset;
- (nullable UITextPosition *)positionFromPosition:(UITextPosition *)position inDirection:(UITextLayoutDirection)direction offset:(NSInteger)offset;

/* Simple evaluation of positions */
- (NSComparisonResult)comparePosition:(UITextPosition *)position toPosition:(UITextPosition *)other;
- (NSInteger)offsetFromPosition:(UITextPosition *)from toPosition:(UITextPosition *)toPosition;

/* A system-provided input delegate is assigned when the system is interested in input changes. */
@property (nullable, nonatomic, weak) id <UITextInputDelegate> inputDelegate;

/* A tokenizer must be provided to inform the text input system about text units of varying granularity. */
@property (nonatomic, readonly) id <UITextInputTokenizer> tokenizer;

/* Layout questions. */
- (nullable UITextPosition *)positionWithinRange:(UITextRange *)range farthestInDirection:(UITextLayoutDirection)direction;
- (nullable UITextRange *)characterRangeByExtendingPosition:(UITextPosition *)position inDirection:(UITextLayoutDirection)direction;

/* Writing direction */
- (NSWritingDirection)baseWritingDirectionForPosition:(UITextPosition *)position inDirection:(UITextStorageDirection)direction;
- (void)setBaseWritingDirection:(NSWritingDirection)writingDirection forRange:(UITextRange *)range;

/* Geometry used to provide, for example, a correction rect. */
- (CGRect)firstRectForRange:(UITextRange *)range;
- (CGRect)caretRectForPosition:(UITextPosition *)position;
- (NSArray<UITextSelectionRect *> *)selectionRectsForRange:(UITextRange *)range API_AVAILABLE(ios(6.0));       // Returns an array of UITextSelectionRects

/* Hit testing. */
- (nullable UITextPosition *)closestPositionToPoint:(CGPoint)point;
- (nullable UITextPosition *)closestPositionToPoint:(CGPoint)point withinRange:(UITextRange *)range;
- (nullable UITextRange *)characterRangeAtPoint:(CGPoint)point;

@optional

- (BOOL)shouldChangeTextInRange:(UITextRange *)range replacementText:(NSString *)text API_AVAILABLE(ios(6.0));   // return NO to not change text

/* Text styling information can affect, for example, the appearance of a correction rect.
 * Returns a dictionary containing NSAttributedString keys. */
- (nullable NSDictionary<NSAttributedStringKey, id> *)textStylingAtPosition:(UITextPosition *)position inDirection:(UITextStorageDirection)direction;

/* To be implemented if there is not a one-to-one correspondence between text positions within range and character offsets into the associated string. */
- (nullable UITextPosition *)positionWithinRange:(UITextRange *)range atCharacterOffset:(NSInteger)offset;
- (NSInteger)characterOffsetOfPosition:(UITextPosition *)position withinRange:(UITextRange *)range;

/* An affiliated view that provides a coordinate system for all geometric values in this protocol.
 * If unimplemented, the first view in the responder chain will be selected. */
@property (nonatomic, readonly) __kindof UIView *textInputView;

/* Selection affinity determines whether, for example, the insertion point appears after the last
 * character on a line or before the first character on the following line in cases where text
 * wraps across line boundaries. */
@property (nonatomic) UITextStorageDirection selectionAffinity;

/* This is an optional method for clients that wish to support dictation phrase alternatives. If 
 * they do not implement this method, dictation will just insert the most likely interpretation 
 * of what was spoken via -insertText:.
 * dictationResult is an array of UIDictationPhrases. */
- (void)insertDictationResult:(NSArray<UIDictationPhrase *> *)dictationResult;

/* These are optional methods for clients that wish to know when there are pending dictation results. */
- (void)dictationRecordingDidEnd;
- (void)dictationRecognitionFailed;

/* The following three optional methods are for clients that wish to support a placeholder for 
 * pending dictation results. -insertDictationPlaceholder must return a reference to the 
 * placeholder. This reference will be used to identify the placeholder by the other methods
 * (there may be more than one placeholder). */
@property(nonatomic, readonly) id insertDictationResultPlaceholder API_UNAVAILABLE(watchos);
- (CGRect)frameForDictationResultPlaceholder:(id)placeholder;
/* willInsertResult will be NO if the recognition failed. */
- (void)removeDictationResultPlaceholder:(id)placeholder willInsertResult:(BOOL)willInsertResult;

// This is an optional method for clients that wish to support text phrase alternatives. If they do not implement this method,
// the text will be inserted by -insertText: without the phase alternatives.
- (void)insertText:(NSString *)text alternatives:(NSArray<NSString *> *)alternatives style:(UITextAlternativeStyle)style API_UNAVAILABLE(watchos);

// set attributedString as markedText, selectedRange is a range within the markedText
- (void)setAttributedMarkedText:(nullable NSAttributedString *)markedText selectedRange:(NSRange)selectedRange API_UNAVAILABLE(watchos);

// Insert a placeholder
// If `size.height` is <= 0, then the placeholder is inline and line height.
// If `size.height` is > 0, then the placeholder is treated as a paragraph of height `size.height`.
- (UITextPlaceholder *)insertTextPlaceholderWithSize:(CGSize)size API_UNAVAILABLE(watchos);

// Remove the placeholder.
- (void)removeTextPlaceholder:(UITextPlaceholder *)textPlaceholder API_UNAVAILABLE(watchos);

/* The following three optional methods are for clients that wish to display a floating cursor to
 * guide user manipulation of the selected text range via the system-provided keyboard. If a client
 * does not implement these methods, user feedback will be limited to the outcome after setting the
 * selected text range using positions resulting from hit testing. */
- (void)beginFloatingCursorAtPoint:(CGPoint)point API_AVAILABLE(ios(9.0));
- (void)updateFloatingCursorAtPoint:(CGPoint)point API_AVAILABLE(ios(9.0));
- (void)endFloatingCursor API_AVAILABLE(ios(9.0));

/// Similar to `-caretRectForPosition:`, optionally provide a transform for the caret at `position`. As with all geometry information in this protocol,
/// transforms are assumed to be relative to the `textInputView` coordinate space. If unimplemented, the identity transform is assumed.
- (CGAffineTransform)caretTransformForPosition:(UITextPosition *)position API_AVAILABLE(ios(17.4)) API_UNAVAILABLE(watchos);

/**
 * Called when the text input is preparing an edit menu presentation for the specified text range.
 *
 * @param textRange                  The text range for which the menu is presented for.
 * @param suggestedActions  The actions and commands that the system suggests.
 *
 * @return Return a UIMenu describing the desired menu hierarchy. Return @c nil to present the default system menu.
 */
- (nullable UIMenu *)editMenuForTextRange:(UITextRange *)textRange suggestedActions:(NSArray<UIMenuElement *> *)suggestedActions API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(watchos);

/* These are optional methods for clients that wish to know the visiblity of text editing menus */
- (void)willPresentEditMenuWithAnimator:(id<UIEditMenuInteractionAnimating>)animator API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);
- (void)willDismissEditMenuWithAnimator:(id<UIEditMenuInteractionAnimating>)animator API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);

@property (nonatomic) BOOL supportsAdaptiveImageGlyph API_AVAILABLE(ios(18.0),tvos(18.0),watchos(11.0),visionos(2.0));

- (void)insertAdaptiveImageGlyph:(NSAdaptiveImageGlyph *)adaptiveImageGlyph replacementRange:(UITextRange *)replacementRange API_AVAILABLE(ios(18.0),tvos(18.0),watchos(11.0),visionos(2.0));

@property (nonatomic, readonly, getter=isEditable) BOOL editable API_AVAILABLE(ios(18.0), macos(15.0), visionos(2.0)) API_UNAVAILABLE(tvos, watchos);

- (void)insertAttributedText:(NSAttributedString *)string API_AVAILABLE(ios(12.0), tvos(12.0), watchos(5.0), macos(10.14), visionos(1.0)) API_UNAVAILABLE(watchos);
- (NSAttributedString *)attributedTextInRange:(UITextRange *)range API_AVAILABLE(ios(12.0), tvos(12.0), macos(10.14), visionos(1.0)) API_UNAVAILABLE(watchos);
- (void)replaceRange:(UITextRange *)range withAttributedText:(NSAttributedString *)attributedText API_AVAILABLE(ios(13.0), tvos(13.0), macos(10.15), visionos(1.0)) API_UNAVAILABLE(watchos);

// These methods are called when the Writing Tools panel is presented and dismissed
- (void)willPresentWritingTools API_AVAILABLE(ios(18.0), visionos(2.4)) API_UNAVAILABLE(tvos, watchos);
- (void)didDismissWritingTools API_AVAILABLE(ios(18.0), visionos(2.4)) API_UNAVAILABLE(tvos, watchos);

/// Inserts the user or system’s input suggestion into the document.
- (void)insertInputSuggestion:(UIInputSuggestion *)inputSuggestion API_AVAILABLE(ios(18.4)) API_UNAVAILABLE(tvos, watchos, visionos, macCatalyst);

@end
//---------------------------------------------------------------------------------------------------

/* UITextInput keys to style dictionaries are deprecated. Use NSAttributedString keys instead, such as NSFontAttribute, etc. */
UIKIT_EXTERN NSString *const UITextInputTextBackgroundColorKey API_DEPRECATED_WITH_REPLACEMENT("NSBackgroundColorAttributeName", ios(3.2, 8.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(visionos, watchos); // Key to a UIColor
UIKIT_EXTERN NSString *const UITextInputTextColorKey           API_DEPRECATED_WITH_REPLACEMENT("NSForegroundColorAttributeName", ios(3.2, 8.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(visionos, watchos); // Key to a UIColor
UIKIT_EXTERN NSString *const UITextInputTextFontKey            API_DEPRECATED_WITH_REPLACEMENT("NSFontAttributeName", ios(3.2, 8.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(visionos, watchos); // Key to a UIFont

/* To accommodate text entry in documents that contain nested elements, or in which supplying and
 * evaluating characters at indices is an expensive proposition, a position within a text input
 * document is represented as an object, not an integer.  UITextRange and UITextPosition are abstract
 * classes provided to be subclassed when adopting UITextInput */
UIKIT_EXTERN API_AVAILABLE(ios(3.2)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UITextPosition : NSObject

@end

UIKIT_EXTERN API_AVAILABLE(ios(3.2)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UITextRange : NSObject

@property (nonatomic, readonly, getter=isEmpty) BOOL empty;     //  Whether the range is zero-length.
@property (nonatomic, readonly) UITextPosition *start;
@property (nonatomic, readonly) UITextPosition *end;

@end

/* UITextSelectionRect defines an annotated selection rect used by the system to
 * offer rich text interaction experience.  It also serves as an abstract class
 * provided to be subclassed when adopting UITextInput */
UIKIT_EXTERN API_AVAILABLE(ios(6.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UITextSelectionRect : NSObject

@property (nonatomic, readonly) CGRect rect;
@property (nonatomic, readonly) NSWritingDirection writingDirection;
@property (nonatomic, readonly) BOOL containsStart; // Returns YES if the rect contains the start of the selection.
@property (nonatomic, readonly) BOOL containsEnd; // Returns YES if the rect contains the end of the selection.
@property (nonatomic, readonly) BOOL isVertical; // Returns YES if the rect is for vertically oriented text.

/// Custom transform for highlight rects.
/// This transform is assumed to be in the `textInputView` coordinate space.
/// Default is CGAffineTransformIdentity (no transform applied).
@property (nonatomic, readonly) CGAffineTransform transform API_AVAILABLE(ios(17.4)) API_UNAVAILABLE(watchos);

@end

/* The input delegate must be notified of changes to the selection and text. */
API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@protocol UITextInputDelegate <NSObject>

- (void)selectionWillChange:(nullable id <UITextInput>)textInput;
- (void)selectionDidChange:(nullable id <UITextInput>)textInput;
- (void)textWillChange:(nullable id <UITextInput>)textInput;
- (void)textDidChange:(nullable id <UITextInput>)textInput;

/// Tells the input delegate when text has changed in the input object for a conversation.
- (void)conversationContext:(nullable UIConversationContext *)context didChange:(nullable id <UITextInput>)textInput API_AVAILABLE(ios(18.4)) API_UNAVAILABLE(tvos, watchos, visionos, macCatalyst);
@end


/* A tokenizer allows the text input system to evaluate text units of varying granularity. */
API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@protocol UITextInputTokenizer <NSObject>

@required

- (nullable UITextRange *)rangeEnclosingPosition:(UITextPosition *)position withGranularity:(UITextGranularity)granularity inDirection:(UITextDirection)direction;   // Returns range of the enclosing text unit of the given granularity, or nil if there is no such enclosing unit.  Whether a boundary position is enclosed depends on the given direction, using the same rule as isPosition:withinTextUnit:inDirection:
- (BOOL)isPosition:(UITextPosition *)position atBoundary:(UITextGranularity)granularity inDirection:(UITextDirection)direction;                             // Returns YES only if a position is at a boundary of a text unit of the specified granularity in the particular direction.
- (nullable UITextPosition *)positionFromPosition:(UITextPosition *)position toBoundary:(UITextGranularity)granularity inDirection:(UITextDirection)direction;   // Returns the next boundary position of a text unit of the given granularity in the given direction, or nil if there is no such position.
- (BOOL)isPosition:(UITextPosition *)position withinTextUnit:(UITextGranularity)granularity inDirection:(UITextDirection)direction;                         // Returns YES if position is within a text unit of the given granularity.  If the position is at a boundary, returns YES only if the boundary is part of the text unit in the given direction.

@end


/* A recommended base implementation of the tokenizer protocol. Subclasses are responsible
 * for handling directions and granularities affected by layout.*/
UIKIT_EXTERN API_AVAILABLE(ios(3.2)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UITextInputStringTokenizer : NSObject <UITextInputTokenizer> 

- (instancetype)initWithTextInput:(UIResponder <UITextInput> *)textInput;

@end

/* The UITextInputMode class should not be subclassed. It is to allow other in-app functionality to adapt 
 * based on the keyboard language. Different UITextInputMode objects may have the same primaryLanguage. */
UIKIT_EXTERN API_AVAILABLE(ios(4.2)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UITextInputMode : NSObject <NSSecureCoding>

@property (nullable, nonatomic, readonly, strong) NSString *primaryLanguage; // The primary language, if any, of the input mode.  A BCP 47 language identifier such as en-US

// To query the UITextInputMode, refer to the UIResponder method -textInputMode.
+ (nullable UITextInputMode *)currentInputMode API_DEPRECATED("", ios(4.2, 7.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(visionos, watchos); // The current input mode.  Nil if unset.
@property(class, nonatomic, readonly) NSArray<UITextInputMode *> *activeInputModes; // The active input modes.

@end

UIKIT_EXTERN NSNotificationName const UITextInputCurrentInputModeDidChangeNotification API_AVAILABLE(ios(4.2)) API_UNAVAILABLE(watchos) NS_SWIFT_NONISOLATED;

typedef NSWritingDirection UITextWritingDirection API_DEPRECATED_WITH_REPLACEMENT("NSWritingDirection", ios(3.2, 13.0), tvos(9.0, 13.0)) API_UNAVAILABLE(visionos, watchos);

static const UITextWritingDirection UITextWritingDirectionNatural API_DEPRECATED_WITH_REPLACEMENT("NSWritingDirectionNatural", ios(3.2, 13.0), tvos(9.0, 13.0)) API_UNAVAILABLE(visionos, watchos) = NSWritingDirectionNatural;
static const UITextWritingDirection UITextWritingDirectionLeftToRight API_DEPRECATED_WITH_REPLACEMENT("NSWritingDirectionLeftToRight", ios(3.2, 13.0), tvos(9.0, 13.0)) API_UNAVAILABLE(visionos, watchos) = NSWritingDirectionLeftToRight;
static const UITextWritingDirection UITextWritingDirectionRightToLeft API_DEPRECATED_WITH_REPLACEMENT("NSWritingDirectionRightToLeft", ios(3.2, 13.0), tvos(9.0, 13.0)) API_UNAVAILABLE(visionos, watchos) = NSWritingDirectionRightToLeft;

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UITextInput.h>
#endif
