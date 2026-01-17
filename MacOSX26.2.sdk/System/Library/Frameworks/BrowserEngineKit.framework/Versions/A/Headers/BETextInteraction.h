//
//  BETextInteraction.h
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <BrowserEngineKit/BEMacros.h>
#import <BrowserEngineKit/BETextSelectionTypes.h>
#import <BrowserEngineKit/BEMacros.h>

#if BROWSERENGINEKIT_HAS_UIVIEW
#import <UIKit/UIKit.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@protocol BETextInteractionDelegate;

BROWSERENGINE_EXPORT BROWSERENGINE_TEXTINPUT_AVAILABILITY
@interface BETextInteraction : NSObject<UIInteraction>

/**
 *  Assign a delegate to this object to receive callback information
 */
@property (weak, nonatomic) id<BETextInteractionDelegate> delegate;

/**
 *  Presents a sheet to add a text replacement shortcut to the keyboard dictionary
 *
 *  Generally used for IME languages, such as Chinese/Japanese
 */
- (void)addShortcutForText:(NSString *)text fromRect:(CGRect)presentationRect NS_SWIFT_NAME(addShortcut(forText:from:));

/**
 * Presents a share sheet for the `text` positioned relative to the `presentationRect`
 */
- (void)shareText:(NSString *)text fromRect:(CGRect)presentationRect NS_SWIFT_NAME(share(text:from:));

/**
 *  Presents a dictionary definition view for the `textWithContext` positioned relative to the `presentationRect`
 */
- (void)showDictionaryForTextInContext:(NSString *)textWithContext definingTextInRange:(NSRange)range fromRect:(CGRect)presentationRect NS_SWIFT_NAME(showDictionary(forTextInContext:definingTextInRange:from:));

/**
 *  Presents a translation view for the `text` positioned relative to the `presentationRect`
 */
- (void)translateText:(NSString *)text fromRect:(CGRect)presentationRect NS_SWIFT_NAME(translate(text:from:));

/**
 *  Displays the inline text replacement UI for the current selection.
 *  For example, inline text replacements are displayed in response to the "Replace..." option in the edit menu.
 *
 *  Could be invoked when handling `promptForReplace:` action
 */
- (void)showReplacementsForText:(NSString *)text NS_SWIFT_NAME(showReplacements(forText:));

/**
 *  Converts the text selection between traditional and simplified Chinese
 *
 *  Could be invoked when handling `transliterateChinese` action
 */
- (void)transliterateChineseForText:(NSString *)text NS_SWIFT_NAME(transliterateChinese(forText:));

/**
 *  Presents an edit menu for the current text selection
 */
- (void)presentEditMenuForSelection;

/**
 *  Dismisses an edit menu for the current text selection
 */
- (void)dismissEditMenuForSelection;

/**
 *  Tells the system that the document's editability status has changed.
 *
 *  In response, the system refreshes the text interaction gestures, depending on the value of `isEditable`
 */
- (void)editabilityChanged;

/**
 *  Tells the system to refresh the keyboard UI.
 *
 *  This lightweight method refreshes the selection UI.  For example, this could be invoked in response to
 *  programmatic text selection changes, independent of text interaction gestures
 */
- (void)refreshKeyboardUI;

/**
 *  Tells the system that the selection change has been handled for the given `point` and gesture.
 *
 *  Should be invoked in response to:
 *  -[BETextInput updateCurrentSelectionTo:fromGesture:inState:]
 */
- (void)selectionChangedWithGestureAtPoint:(CGPoint)point gesture:(BEGestureType)gestureType state:(UIGestureRecognizerState)gestureState flags:(BESelectionFlags)flags;

/**
 *  Tells the system the selection adjustment has been handled for the given `point` and touch
 *
 *  Should be invoked in response to:
 *  -[BETextInput adjustSelectionBoundaryToPoint:touchPhase:baseIsStart:flags:]
 */
- (void)selectionBoundaryAdjustedToPoint:(CGPoint)point touchPhase:(BESelectionTouchPhase)touch flags:(BESelectionFlags)flags;

/**
 *  Returns a UITextSelectionDisplayInteraction that manages selection UI
 */
@property (nonatomic, readonly) UITextSelectionDisplayInteraction *textSelectionDisplayInteraction;

#if !TARGET_OS_TV && !TARGET_OS_WATCH
/**
 * Set a delegate to receive callbacks for the context menu interaction
 */
@property (nonatomic, weak) id <UIContextMenuInteractionDelegate> contextMenuInteractionDelegate API_UNAVAILABLE(watchos, tvos);

/**
 *  Returns a UIContextMenuInteraction object whose delegate methods will be invoked
 *  on `contextMenuInteractionDelegate`
 */
@property (nonatomic, readonly) UIContextMenuInteraction *contextMenuInteraction API_UNAVAILABLE(watchos, tvos);

#endif

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#endif // BROWSERENGINEKIT_HAS_UIVIEW
