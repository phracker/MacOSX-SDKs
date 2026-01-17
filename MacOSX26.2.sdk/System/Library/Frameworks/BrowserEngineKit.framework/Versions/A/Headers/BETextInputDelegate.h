//
//  BETextInputDelegate.h
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <BrowserEngineKit/BETextInput.h>

@class BEKeyEntryContext;
@class BETextSuggestion;
@protocol BETextInput;

NS_ASSUME_NONNULL_BEGIN

BROWSERENGINE_EXPORT BROWSERENGINE_TEXTINPUT_AVAILABILITY
@protocol BETextInputDelegate

/**
 *  Defers the key event to the system and returns whether the key event was handled.
 *
 *  For example, the system will handle key events for character insertions, deletions, key commands, and more.
 */
- (BOOL)shouldDeferEventHandlingToSystemForTextInput:(id<BETextInput>)textInput context:(BEKeyEntryContext *)keyEventContext;

/**
 *  Provides text suggestions to the system.
 *
 *  For example, suggestions could include data list elements or AutoFill candidates.
 */
- (void)textInput:(id<BETextInput>)textInput setCandidateSuggestions:(NSArray<BETextSuggestion *> * _Nullable)suggestions;

/**
 *  Tells the system when the selection is about to change in the document.
 */
- (void)selectionWillChangeForTextInput:(id <BETextInput>)textInput;

/**
 *  Tells the system when the selection has changed in the document.
 *
 *  This method results in an document state refresh with an invocation to:
 *  -[BETextInput requestTextContextForAutocorrectionWithCompletionHandler:]
 */
- (void)selectionDidChangeForTextInput:(id <BETextInput>)textInput;

/**
 *  Defers a replace text action to the ssytem.
 *
 *  When handling the replace: action, use this method to defer the replacement to the system.
 *
 *  For example, a replacement could be deferred after it is selected from the autocorrect replacements list.
 */
- (void)textInput:(id<BETextInput>)textInput deferReplaceTextActionToSystem:(id)sender;

/**
 *  Tells the system the text entry context has changed and that text entry UI's need to be refreshed.
 *
 *  This is a costly operation and should only used with intention.  For example, when switching focus
 *  between different elements.
 */
- (void)invalidateTextEntryContextForTextInput:(id<BETextInput>)textInput;

@end

NS_ASSUME_NONNULL_END
