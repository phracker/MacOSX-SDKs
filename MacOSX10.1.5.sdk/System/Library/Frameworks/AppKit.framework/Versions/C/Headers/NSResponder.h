/*
        NSResponder.h
        Application Kit
        Copyright (c) 1994-2001, Apple Computer, Inc.
        All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSArray, NSEvent, NSMenu, NSUndoManager;

@interface NSResponder : NSObject <NSCoding>
{
    /*All instance variables are private*/
    id _nextResponder;
}

- (NSResponder *)nextResponder;
- (void)setNextResponder:(NSResponder *)aResponder;
- (BOOL)tryToPerform:(SEL)anAction with:(id)anObject;
- (BOOL)performKeyEquivalent:(NSEvent *)theEvent;
- (id)validRequestorForSendType:(NSString *)sendType returnType:(NSString *)returnType;
- (void)mouseDown:(NSEvent *)theEvent;
- (void)rightMouseDown:(NSEvent *)theEvent;
- (void)otherMouseDown:(NSEvent *)theEvent;
- (void)mouseUp:(NSEvent *)theEvent;
- (void)rightMouseUp:(NSEvent *)theEvent;
- (void)otherMouseUp:(NSEvent *)theEvent;
- (void)mouseMoved:(NSEvent *)theEvent;
- (void)mouseDragged:(NSEvent *)theEvent;
- (void)scrollWheel:(NSEvent *)theEvent;
- (void)rightMouseDragged:(NSEvent *)theEvent;
- (void)otherMouseDragged:(NSEvent *)theEvent;
- (void)mouseEntered:(NSEvent *)theEvent;
- (void)mouseExited:(NSEvent *)theEvent;
- (void)keyDown:(NSEvent *)theEvent;
- (void)keyUp:(NSEvent *)theEvent;
- (void)flagsChanged:(NSEvent *)theEvent;
- (void)noResponderFor:(SEL)eventSelector;
- (BOOL)acceptsFirstResponder;
- (BOOL)becomeFirstResponder;
- (BOOL)resignFirstResponder;

- (void)interpretKeyEvents:(NSArray *)eventArray;
- (void)flushBufferedKeyEvents;

- (void)setMenu:(NSMenu *)menu;
- (NSMenu *)menu;

- (void)showContextHelp:(id)sender;

- (void)helpRequested:(NSEvent *)eventPtr;

@end

@interface NSResponder(NSKeyboardUI)
- (BOOL)performMnemonic:(NSString *)theString;
@end

@interface NSResponder (NSStandardKeyBindingMethods)

// This category contains a large number of methods intended for use as key binding commands.  NSResponder does not implement any of them.  NSTextView implements a certain subset of them (see the NSTextView.h header).  Your responder subclasses can implement any that make sense.  You can make up your own as well, but you should use these if the concepts map.  If your view is key and uses key binding and the user types a key sequence which is bound to a command which is not implemented in your class, it is OK, nothing will happen by default.

/************************* Key binding entry-points *************************/

- (void)insertText:(id)insertString;
    // When key events have been passed off to the key binding mechanism through interpretKeyEvents:, they end up back in the view through either this method or the below doCommand... methods.  insertText: is used to pass through text that was not a command.

- (void)doCommandBySelector:(SEL)aSelector;
    // Performs the given selector if possible.

/************************* Standard bindable commands *************************/

    /* Selection movement and scrolling */

- (void)moveForward:(id)sender;
- (void)moveRight:(id)sender;
- (void)moveBackward:(id)sender;
- (void)moveLeft:(id)sender;
- (void)moveUp:(id)sender;
- (void)moveDown:(id)sender;
- (void)moveWordForward:(id)sender;
- (void)moveWordBackward:(id)sender;
- (void)moveToBeginningOfLine:(id)sender;
- (void)moveToEndOfLine:(id)sender;
- (void)moveToBeginningOfParagraph:(id)sender;
- (void)moveToEndOfParagraph:(id)sender;
- (void)moveToEndOfDocument:(id)sender;
- (void)moveToBeginningOfDocument:(id)sender;
- (void)pageDown:(id)sender;
- (void)pageUp:(id)sender;
- (void)centerSelectionInVisibleArea:(id)sender;

- (void)moveBackwardAndModifySelection:(id)sender;
- (void)moveForwardAndModifySelection:(id)sender;
- (void)moveWordForwardAndModifySelection:(id)sender;
- (void)moveWordBackwardAndModifySelection:(id)sender;
- (void)moveUpAndModifySelection:(id)sender;
- (void)moveDownAndModifySelection:(id)sender;

- (void)scrollPageUp:(id)sender;
- (void)scrollPageDown:(id)sender;
- (void)scrollLineUp:(id)sender;
- (void)scrollLineDown:(id)sender;

    /* Graphical Element transposition */

- (void)transpose:(id)sender;
- (void)transposeWords:(id)sender;

    /* Selections */

- (void)selectAll:(id)sender;
- (void)selectParagraph:(id)sender;
- (void)selectLine:(id)sender;
- (void)selectWord:(id)sender;

    /* Insertions and Indentations */

- (void)indent:(id)sender;
- (void)insertTab:(id)sender;
- (void)insertBacktab:(id)sender;
- (void)insertNewline:(id)sender;
- (void)insertParagraphSeparator:(id)sender;
- (void)insertNewlineIgnoringFieldEditor:(id)sender;
- (void)insertTabIgnoringFieldEditor:(id)sender;

    /* Case changes */

- (void)changeCaseOfLetter:(id)sender;
- (void)uppercaseWord:(id)sender;
- (void)lowercaseWord:(id)sender;
- (void)capitalizeWord:(id)sender;

    /* Deletions */

- (void)deleteForward:(id)sender;
- (void)deleteBackward:(id)sender;
- (void)deleteWordForward:(id)sender;
- (void)deleteWordBackward:(id)sender;
- (void)deleteToBeginningOfLine:(id)sender;
- (void)deleteToEndOfLine:(id)sender;
- (void)deleteToBeginningOfParagraph:(id)sender;
- (void)deleteToEndOfParagraph:(id)sender;

- (void)yank:(id)sender;

    /* Completion */

- (void)complete:(id)sender;

    /* Mark/Point manipulation */

- (void)setMark:(id)sender;
- (void)deleteToMark:(id)sender;
- (void)selectToMark:(id)sender;
- (void)swapWithMark:(id)sender;

@end

@interface NSResponder(NSUndoSupport)
- (NSUndoManager *)undoManager;
@end
