//
//  BETextDocumentContext.h
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <BrowserEngineKit/BEMacros.h>

#if BROWSERENGINEKIT_HAS_UIVIEW
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

BROWSERENGINE_EXPORT BROWSERENGINE_TEXTINPUT_AVAILABILITY
@interface BETextDocumentContext : NSObject

/**
 @abstract Initializes a new document context with plain text.
 @param selectedText The currently selected text, or nil in the case of a caret selection.
  This string may be empty but non-nil if non-textual content is selected, in which case a single call to -deleteBackward will not delete from contextBeforeSelection.
  May be empty if its outside of the context's area, even if it exists elsewhere in the document.
 @param contextBefore A suffix of the text preceding the selection, or nil if the selection is at the beginning of the document.
  This text must correspond to a range that does not include any non-text content.
  In particular, if a context comprises k backward-deletion clusters, then k calls to -deleteBackward must delete the corresponding text from the document.
  The beginning of this string must lie on a word boundary (or not be inside a word at all).
 @param contextAfter A prefix of the text following the selection, or nil if the selection is at the end of the document.
  This text must correspond to a range that does not include any non-text content.
  The end of this string must lie on a word boundary (or not be inside a word at all).
 @param markedText May be empty if it's outside of the context's area, even if it exists elsewhere in the document.
 @param selectedRangeInMarkedText The range of the current text selection, relative to the marked text range. Specify (NSNotFound, 0) if there is no marked text.
 */
- (instancetype)initWithSelectedText:(nullable NSString *)selectedText contextBefore:(nullable NSString *)contextBefore contextAfter:(nullable NSString *)contextAfter markedText:(nullable NSString *)markedText selectedRangeInMarkedText:(NSRange)selectedRangeInMarkedText;

/**
 *  Initializes a new document context with attributed strings. The `selectedText`, `contextBefore`, and `contextAfter`
 *  represent the same ranges as they do in the `-initWithSelectedText:contextBefore:contextAfter:` initializer.
 */
- (instancetype)initWithAttributedSelectedText:(nullable NSAttributedString *)selectedText contextBefore:(nullable NSAttributedString *)contextBefore contextAfter:(nullable NSAttributedString *)contextAfter markedText:(nullable NSAttributedString *)markedText selectedRangeInMarkedText:(NSRange)selectedRangeInMarkedText;

/**
 *  Adds a text `rect` for the given character `range`
 *  The CGRects representing each character range are specified in -textInputView coordinates.
 */
- (void)addTextRect:(CGRect)rect forCharacterRange:(NSRange)range;

/**
 *  Array of `NSRange` values, relative to the full context string made by combining the
 *  `contextBefore`, `markedText` (or `selectedText` if the marked text is empty), and the
 *  `contextAfter`.
 */
@property (nonatomic, copy) NSArray<NSValue *> *autocorrectedRanges;

- (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

#endif // BROWSERENGINEKIT_HAS_UIVIEW
