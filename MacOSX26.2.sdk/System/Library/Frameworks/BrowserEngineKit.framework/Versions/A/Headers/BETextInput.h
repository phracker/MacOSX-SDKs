//
//  BETextInput.h
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <BrowserEngineKit/BETextInputDelegate.h>
#import <BrowserEngineKit/BEKeyEntry.h>
#import <BrowserEngineKit/BETextSelectionTypes.h>
#import <BrowserEngineKit/BETextAlternatives.h>
#import <BrowserEngineKit/BEMacros.h>

#if BROWSERENGINEKIT_HAS_UIVIEW
#import <UIKit/UIKit.h>
#import <UIKit/UITextInput.h>
#import <UIKit/UIColor.h>
#import <UIKit/UIView.h>
#import <UIKit/UIEditMenuInteraction.h>
#import <UIKit/UIGestureRecognizer.h>

@class BETextDocumentContext;
@class BETextDocumentRequest;
@class BETextSuggestion;
@class BEKeyEntry;
@class BEKeyEntryContext;

NS_ASSUME_NONNULL_BEGIN

typedef struct {
    NSInteger offset;
    NSInteger length;
} BEDirectionalTextRange BROWSERENGINE_TEXTINPUT_AVAILABILITY;

typedef NS_OPTIONS(NSUInteger, BETextReplacementOptions) {
    BETextReplacementOptionsNone = 0,
    BETextReplacementOptionsAddUnderline = 1 << 0,
} BROWSERENGINE_TEXTINPUT_AVAILABILITY;

typedef NS_ENUM(NSInteger, BEKeyModifierFlags) {
    BEKeyModifierFlagNone,
    BEKeyModifierFlagShift,
    BEKeyModifierFlagCapsLock
} BROWSERENGINE_TEXTINPUT_AVAILABILITY;

#pragma mark - Extended Edit Actions

BROWSERENGINE_EXPORT BROWSERENGINE_TEXTINPUT_AVAILABILITY
@protocol BEResponderEditActions <UIResponderStandardEditActions>

@optional

/**
 *  Shares the selected content.
 *  See corresponding share methods in BETextInteraction.
 */
- (void)share:(nullable id)sender;

/**
 *  Adds a text replacement shortcut to the keyboard dictionary.
 *  See corresponding shortcut methods in BETextInteraction.
 */
- (void)addShortcut:(nullable id)sender;

/**
 *  Presents a dictionary definition for the selected content.
 *  See corresponding dictionary methods in BETextInteraction.
 */
- (void)lookup:(nullable id)sender;

/**
 *  Performs a find for the selected content
 *  See find related methods in UIResponderStandardEditActions
 */
- (void)findSelected:(nullable id)sender;

/**
 *  Shows the replacements for the selected content.
 *  See corresponding replacement methods in BETextInteraction.
 */
- (void)promptForReplace:(nullable id)sender;

/**
 *  Inserts the selected replacement for the selected content.
 *  See corresponding replacement methods in BETextInputDelegate
 */
- (void)replace:(nullable id)sender;

/**
 *  Presents a translation view for the selected content.
 *  See corresponding translation methods in BETextInteraction.
 */
- (void)translate:(nullable id)sender;

/**
 *  Converts the selected content between traditional and simplified Chinese
 *  See corresponding transliteration methods in BETextInteraction.
 */
- (void)transliterateChinese:(nullable id)sender;

@end

#pragma mark - Text navigation

BROWSERENGINE_EXPORT BROWSERENGINE_TEXTINPUT_AVAILABILITY
@protocol BETextSelectionDirectionNavigation
/**
 *  Moves the cursor in the specified directions, such as in response to an arrow key press.
 */
- (void)moveInLayoutDirection:(UITextLayoutDirection)direction;

/**
 *  Extends text selection in the specified directions, such as in response to an arrow key press while shift is held.
 */
- (void)extendInLayoutDirection:(UITextLayoutDirection)direction;

/**
 *  Moves the cursor in the specified directions by granularity, in response to different key combinations:
 *
 *  Option + left/right = word
 *  Option + up/down = paragraph
 *  Command + left/right = line
 *  Command + up/down = document
 */
- (void)moveInStorageDirection:(UITextStorageDirection)direction byGranularity:(UITextGranularity)granularity;

/**
 *  Moves the selection in the specified directions by granularity, in response to different key combinations:
 *
 *  word = shift + option + left/right
 *  paragraph = shift + option + up/down
 *  line = shift + command + left/right
 *  document = shift + command + up/down
 */
- (void)extendInStorageDirection:(UITextStorageDirection)direction byGranularity:(UITextGranularity)granularity;
@end

@class UITextSelectionRect;

BROWSERENGINE_EXPORT BROWSERENGINE_TEXTINPUT_AVAILABILITY
@protocol BEExtendedTextInputTraits <UITextInputTraits>

@optional

/**
 *  Represents whether the active web input field is a single line document
 */
@property (nonatomic, readonly, getter=isSingleLineDocument) BOOL singleLineDocument;
/**
 *  Disables the learning of new words and corrections and prevents their addition into the keyboard lexicon
 */
@property (nonatomic, readonly, getter=isTypingAdaptationEnabled) BOOL typingAdaptationEnabled;
#pragma mark - Theming Traits

/**
 *  Customizes the color of the text cursor at the insertion point
 */
@property (nullable, nonatomic, readonly) UIColor *insertionPointColor;

/**
 *  Customizes the color of the selection handles
 */
@property (nullable, nonatomic, readonly) UIColor *selectionHandleColor;

/**
 *  Customizes the color of the selection highlight rect
 */
@property (nullable, nonatomic, readonly) UIColor *selectionHighlightColor;

@end

BROWSERENGINE_EXPORT BROWSERENGINE_TEXTINPUT_AVAILABILITY
@protocol BETextInput <UIKeyInput, BETextSelectionDirectionNavigation, BEResponderEditActions>

/**
 *  A system-provided input delegate is assigned when the system is interested in input changes.
 */
@property (nullable, nonatomic, weak) id <BETextInputDelegate> asyncInputDelegate;

/**
 *  Returns whether text related actions, such those included in UIResponderStandardEditActions, can be handled
 */
- (BOOL)canPerformAction:(SEL)action withSender:(nullable id)sender;

#pragma mark - Text Input Methods

/**
 *  Reflects the ability to modify text
 */
@property (nonatomic, readonly, getter=isEditable) BOOL editable;

/**
 *  Delegates the handling for each stage of a key event (key down, press, up) and allows the BETextInput object to indicate whether it should prevent default system behaviors.
 */
- (void)handleKeyEntry:(BEKeyEntry *)entry withCompletionHandler:(void (^)(BEKeyEntry *theEvent, BOOL wasHandled))completionHandler NS_SWIFT_NAME(handleKeyEntry(_:completionHandler:));

/**
 *  Indicates a transition in shift state
 */
- (void)shiftKeyStateChangedFromState:(BEKeyModifierFlags)oldState toState:(BEKeyModifierFlags)newState;

/**
 *  Returns the text in the specified range.
 */
- (nullable NSString *)textInRange:(UITextRange *)range;

/**
 *  Returns the number of UTF-16 characters between one text position and another text position.
 */
- (NSInteger)offsetFromPosition:(UITextPosition *)from toPosition:(UITextPosition *)toPosition;

/**
 *  Sets the base writing direction for a specified range of text in a document.
 */
- (void)setBaseWritingDirection:(NSWritingDirection)writingDirection forRange:(UITextRange *)range;

/**
 *  Deletes text by the specified direction and granularity.  Current supported combinations include:
 *
 *  character backward  = delete
 *  character forward = delete-forward
 *  word backward = option + delete
 *  word forward = option + delete-forward
 *  line end = cmd + delete
 *  line start = cmd + delete-forward
 *  paragraph  end = ctrl + K
 *  paragraph start = ctrl + fn + K
 *
 *  (On Apple keyboards, the delete-forward key is a combination of fn + delete)
 */
- (void)deleteInDirection:(UITextStorageDirection)direction toGranularity:(UITextGranularity)granularity;

#pragma mark - Text Editing and Autocorrection

/**
 *  Transposes the characters on either side of the caret in response to the key command, ctrl + T
 */
- (void)transposeCharactersAroundSelection;

/**
 *  Replace the specified text preceding the current selection.
 *
 *  Completion handler should be invoked with the rects representing the replacementText.  If the replaceText
 *  could not be completed succesfully, such as when the originalText no longer matches the current text, then
 *  the completion handler should be invoked with an empty array.
 */
- (void)replaceText:(NSString *)originalText withText:(NSString *)replacementText options:(BETextReplacementOptions)options completionHandler:(void (^)(NSArray<UITextSelectionRect *> *rects))completionHandler;

/**
 *  Invoked by the system to gather context around the current selection.  Clients should generally include the setence
 *  that contains the current selection and include the previous sentence if the current selection is at a boundary.
 */
- (void)requestTextContextForAutocorrectionWithCompletionHandler:(void (^)(BETextDocumentContext *context))completionHandler;

/**
 *  Invoked by the system to gather context for the presentation of various text related UI's.
 *  Completion handler should be invoked with the `UITextSelectionRect`s for the substring nearest to the caret
 *  that matches the given `input`
 */
- (void)requestTextRectsForString:(NSString *)input withCompletionHandler:(void (^)(NSArray<UITextSelectionRect *> *rects))completionHandler;

/**
 *  Controls whether the edit menu is allowed to be presented or should be suppressed.
 */
@property (readonly, nonatomic) BOOL automaticallyPresentEditMenu;

/**
 *  Invoked by the system to gather context, including the client's preference for how the edit menu should be positioned
 *  relative to the selected text.
 */
- (void)requestPreferredArrowDirectionForEditMenuWithCompletionHandler:(void (^)(UIEditMenuArrowDirection))completionHandler API_UNAVAILABLE(watchos, tvos);

/**
 *  Invoked by the system when it is about to present an edit menu with an animator.
 */
- (void)systemWillPresentEditMenuWithAnimator:(id<UIEditMenuInteractionAnimating>)animator API_UNAVAILABLE(watchos, tvos);

/**
 *  Invoked by the system when it is about to dismiss an edit menu with an animator.
 */
- (void)systemWillDismissEditMenuWithAnimator:(id<UIEditMenuInteractionAnimating>)animator API_UNAVAILABLE(watchos, tvos);

#pragma mark - Input Traits

/**
 *  Object from which the BEExtendedTextInputTraits will be gathered.
 */
@property (nullable, nonatomic, readonly) id<BEExtendedTextInputTraits> extendedTextInputTraits;

/**
 *  Returns a dictionary containing NSAttributedString keys represeting appearance customizations.
 *
 *  For example, text styling information influence the appearance of a correction rect.
 */
- (nullable NSDictionary<NSAttributedStringKey, id> *)textStylingAtPosition:(UITextPosition *)position inDirection:(UITextStorageDirection)direction;

#pragma mark Text Replacement

/**
 *  Returns whether replacement should be allowed for an editable element.
 *
 *  For example, replacement shouldn't be allowed in password fields or when the selected text
 *  is only consists of whitespace.
 */
@property (nonatomic, readonly, getter=isReplaceAllowed) BOOL replaceAllowed;

/**
 *  Replaces the specified `text` with `replacementText`
 *
 *  1. If there is a nonzero length current selection, then replace text with replacementText.
 *  2. If there is zero length current selection, then replace the matching word before the selection
 *  3. If the zero length selection is at the start of the element, then replace the matching word after the selection
 */
- (void)replaceSelectedText:(NSString *)text withText:(NSString *)replacementText;

#pragma mark Gesture

/**
 *  Indicates the `point` the text interaction gesture is tracking has changed
 *
 *  Indicate to the system the change was handled by invoking:
 *  -[BETextInteraction selectionChangedWithGestureAtPoint:gesture:state:flags:]
 */
- (void)updateCurrentSelectionTo:(CGPoint)point fromGesture:(BEGestureType)gestureType inState:(UIGestureRecognizerState)state;

/**
 *  Indicates the selection should change to contain the text between the
 *  `from` and `to` points.
 *
 *  For example, see the keyboard's trackpad selection gesture explained in
 *  "Turn the onscreen keyboard into a trackpad" guide on support.apple.com
 */
- (void)setSelectionFromPoint:(CGPoint)from toPoint:(CGPoint)to gesture:(BEGestureType)gesture state:(UIGestureRecognizerState)state NS_SWIFT_NAME(setSelection(from:to:gesture:state:));

/**
 *  Adjusts the selection's start or end boundary specified by `boundaryIsStart` to the `point`
 *
 *  For example, the selection's boundary would be adjusted when the user moves the selection handles
 *
 *  Indicate to the system that the change was handled by invoking:
 *  -[BETextInteraction selectionBoundaryAdjustedToPoint:touchPhase:flags:]
 */
- (void)adjustSelectionBoundaryToPoint:(CGPoint)point touchPhase:(BESelectionTouchPhase)touch baseIsStart:(BOOL)boundaryIsStart flags:(BESelectionFlags)flags;

/**
 *  Returns whether a gesture with the given `gestureType` should begin for the given `point`
 */
- (BOOL)textInteractionGesture:(BEGestureType)gestureType shouldBeginAtPoint:(CGPoint)point;

#pragma mark Text selection

@optional

/**
 *  If different than the text input view, one can return a container view here for selection views
 *  that draw _below_ text. Includes the selection highlight view. If this is unimplemented or nil
 *  is returned, views are to be installed onto the text input view.
 */
@property (nonatomic, nullable, readonly) UIView *selectionContainerViewBelowText API_AVAILABLE(ios(26.0));

/**
 *  If different than the text input view, one can return a container view here for selection views
 *  that draw _above_ text. Includes selection range adjustment handles. If this is unimplemented
 *  or nil is returned, views are to be installed onto the text input view.
 */
@property (nonatomic, nullable, readonly) UIView *selectionContainerViewAboveText API_AVAILABLE(ios(26.0));

@required

/**
 *  String representing the selected text.
 */
@property (nullable, readonly) NSString *selectedText;

/**
 *  Range representing the selected text.
 *
 *  Text may have a selection, either zero-length (a caret) or ranged.
 *  Editing operations are always performed on the text from this selection.  nil corresponds to no selection.
 */
@property (nullable, readwrite, copy) UITextRange *selectedTextRange;

/**
 *  Represents whether the current selection is at the beginning of the document
 */
@property (nonatomic, readonly, getter=isSelectionAtDocumentStart) BOOL selectionAtDocumentStart;

/**
 *  Returns a rectangle to draw the caret at a specified insertion point.
 */
- (CGRect)caretRectForPosition:(UITextPosition *)position;

/**
 *  Returns an array of selection rects corresponding to the range of text.
 */
- (NSArray<UITextSelectionRect *> *)selectionRectsForRange:(UITextRange *)range;

/**
 *  Selects a word with autocorrect replacement suggestions when it is tapped
 */
- (void)selectWordForReplacement;

/**
 *  Adjusts the selection from current text position to include text at the given `point`.
 *
 *  For example, while holding shift, click a point in a text document and the current selection should adjust to include
 *  all the text up to that point.
 */
- (void)updateSelectionWithExtentPoint:(CGPoint)point boundary:(UITextGranularity)granularity completionHandler:(void (^)(BOOL selectionEndIsMoving))completionHandler NS_SWIFT_NAME(updateSelection(extent:boundary:completionHandler:));

/**
 *  Updates the selection to text contained within the specified `granularity` at the given `point`
 */
- (void)selectTextInGranularity:(UITextGranularity)granularity atPoint:(CGPoint)point completionHandler:(void (^)(void))completionHandler NS_SWIFT_NAME(selectText(in:at:completionHandler:));

/**
 *  Sets the selection caret to the given point
 */
- (void)selectPositionAtPoint:(CGPoint)point completionHandler:(void (^)(void))completionHandler;

/**
 *  Sets the selection caret to the given point.  Also includes a convenience document context request.
 */
- (void)selectPositionAtPoint:(CGPoint)point withContextRequest:(BETextDocumentRequest *)request completionHandler:(void (^)(BETextDocumentContext *))completionHandler NS_SWIFT_NAME(selectPosition(at:for:completionHandler:));

/**
 *  Adjusts the selection by the moving the selected range by the given `range`, in character granularity units.
 *  
 *  The start of the current selection is moved by `range.offset` characters, and the length of the selection
 *  is modified by `range.length` characters. For instance, if the current selection is the word "world" in
 *  "Hello world" and the `range` is `{ -6, -2 }`, the selected text after adjustment will be "Hel".
 */
- (void)adjustSelectionByRange:(BEDirectionalTextRange)range completionHandler:(void (^)(void))completionHandler;

/**
 *  Adjusts the current selection by `offset` in character granularity units
 */
- (void)moveByOffset:(NSInteger)offset;

/**
 *  Moves the caret to relative to the current position in the `direction` to the given `granularity`.
 *  The `direction` is "forward" or "backward" in accordance with the directionality of the language.
 *
 *  This method is invoked only when -[BETextInput textInteractionGesture:shouldBeginAtPoint:] returns YES.
 */
- (void)moveSelectionAtBoundary:(UITextGranularity)granularity inStorageDirection:(UITextStorageDirection)direction completionHandler:(void (^)(void))completionHandler;

/** 
 *  Indicates the edit menu is being shown at the given location in the text input view's
 *  coordinate space.
 *
 *  The completion handler takes a BOOL indicating whether or not the menu
 *  should be shown, a string representing the text context around the updated selection range
 *  (generally encompassing the paragraph that contains the selection range) as well as the
 *  range of the updated selection, relative to the paragraph context.
 */
- (void)selectTextForEditMenuWithLocationInView:(CGPoint)locationInView completionHandler:(void(^)(BOOL shouldPresentMenu, NSString * _Nullable contextString, NSRange selectedRangeInContextString))completionHandler;

#pragma mark - Marked Text

/**
 *  String for the text that has been marked as part of an active input session
 */
@property (nullable, nonatomic, readonly) NSString *markedText;

/**
 *  Attributed string for the text that has been marked as part of an active input session
 */
@property (nullable, nonatomic, readonly) NSAttributedString *attributedMarkedText;

/**
 *  Range representing the position of the markedText.
 *
 *  If text can be selected, it can be marked. Marked text represents provisionally
 *  inserted text that has yet to be confirmed by the user.  It requires unique visual
 *  treatment in its display.  If there is any marked text, the selection, whether a
 *  caret or an extended range, always resides within.
 *
 *  Setting marked text either replaces the existing marked text or, if none is present,
 *  inserts it from the current selection.
 *
 *  Return nil if no marked text
 */
@property (nullable, nonatomic, readonly) UITextRange *markedTextRange;

/**
 *  Indicates whether there any text is currently marked as part of an active input session
 */
@property (nonatomic, readonly) BOOL hasMarkedText;

/**
 *  Inserts the provided text and marks it to indicate that it is part of an active input session.
 */
- (void)setMarkedText:(nullable NSString *)markedText selectedRange:(NSRange)selectedRange;

/**
 *  Inserts the provided styled text and marks it to indicate that it is part of an active input session.
 */
- (void)setAttributedMarkedText:(nullable NSAttributedString *)markedText selectedRange:(NSRange)selectedRange;

/**
 *  Unmarks the currently marked text
 */
- (void)unmarkText;

/**
 *  Returns whether a point should be considered "near" the marked text.
 *  Used to determine whether text interaction gestures near marked text should begin.
 *
 *  For example, text interaction gestures may considered "near" if they are within 66 points.
 */
- (BOOL)isPointNearMarkedText:(CGPoint)point;

#pragma mark - Document context

/**
 *  Gathers context about the current document for the system
 */
- (void)requestDocumentContext:(BETextDocumentRequest *)request completionHandler:(void (^)(BETextDocumentContext *))completionHandler;

#pragma mark Dictation

/**
 *  Indicates the system is about to insert the final dictation result.
 */
- (void)willInsertFinalDictationResult;

/**
 *  Inserts/replaces text for a dictation.
 */
- (void)replaceDictatedText:(NSString *)oldText withText:(NSString *)newText;

/**
 *  Indicates system has inserted the final dictation result
 */
- (void)didInsertFinalDictationResult;

#pragma mark - Text Alternatives

/**
 *   Returns the text alternatives that are available to the text input object.
 */
- (nullable NSArray<BETextAlternatives *> *)alternativesForSelectedText;

/**
 *  Adds text alternatives to the text input object for the current selection
 */
- (void)addTextAlternatives:(BETextAlternatives *)alternatives;

/**
 * Inserts the given `text` or one of it's alternative texts available on `alternatives`
 */
- (void)insertTextAlternatives:(BETextAlternatives *)alternatives;

@optional
/**
 *  Removes text alternatives from the text input object for the current selection
 */
- (void)removeTextAlternatives API_AVAILABLE(ios(18.0));

@required

#pragma mark - Text Placeholders

/**
 *  Inserts a placeholder object to reserve visual space during text input.
 *  If `size.height` is less than or equal to zero, then the placeholder is inline and line height.
 *  If `size.height` is greather than zero, then the placeholder is treated as a paragraph of height `size.height`.
 */
- (void)insertTextPlaceholderWithSize:(CGSize)size completionHandler:(void (^)(UITextPlaceholder *))completionHandler NS_SWIFT_NAME(insertTextPlaceholder(size:completionHandler:));

/**
 *  Removes a placeholder object from the text input view.
 */
- (void)removeTextPlaceholder:(UITextPlaceholder *)placeholder willInsertText:(BOOL)willInsertText completionHandler:(void (^)(void))completionHandler;

#pragma mark - Suggestions

/**
 * Inserts a `textSuggestion` in response to a user suggestion selection
 */
- (void)insertTextSuggestion:(BETextSuggestion *)textSuggestion;

#pragma mark - Geometry
/**
 *  An affiliated view that provides a coordinate system for all geometric values in this protocol.
 */
@property (nonatomic, readonly) __kindof UIView *textInputView;

/**
 *  Returns a rect representing the bounds of the first line of marked text, if marked text is set.
 *
 *  Otherwise, this returns a rect representing the bounds of the last word at or before the insertion point.
 */
@property (nonatomic, readonly) CGRect textFirstRect;

/**
 *  Returns a rect representing the bounds of the last line of marked text, if marked text is set.
 *
 *  Otherwise, this returns a rect representing the bounds of the last word at or before the insertion point.
 *  This may have the same value of `textFirstRect`, but can differ in cases such as a word that spans two lines.
 */
@property (nonatomic, readonly) CGRect textLastRect;

/**
 *  Rect used to place UI (such as selection handles) in a location that isn't obscurred by app UI.
 *
 *  Must return a rect in `textInputView`'s coordinate space.
 */
@property (nonatomic, readonly) CGRect unobscuredContentRect;

/**
 *  View representing the web content that is agnostic of zoom state.
 *  Used to draw zoom agnostic system UI elements, such as the selection handles
 */
@property (nonatomic, readonly) UIView *unscaledView;

/**
 *  Rect representing the bounds of editable elements, used to ensure and UI don't overflow outside them
 */
@property (nonatomic, readonly) CGRect selectionClipRect;

/**
 *  Indicates autoscrolling has been triggered by a text interaction gesture.
 *
 *  Called repeatedly during range adjustment gestures, or when placing the text cursor.
 *
 *  The given point is in the coordinate space of the `textInputView`.
 */
- (void)autoscrollToPoint:(CGPoint)point;

/**
 *  Indicates autoscrolling is complete.
 *
 *  There will be no more calls into`autoscrollToPoint` until a text interaction gesture starts autoscrolling.
 */
- (void)cancelAutoscroll;

#pragma mark - Keyboards

@optional
/**
 *  Called when the user has requested the keyboard to dismiss itself.
 */
- (void)keyboardWillDismiss API_AVAILABLE(ios(18.0));

@end

NS_ASSUME_NONNULL_END

#endif // BROWSERENGINEKIT_HAS_UIVIEW
