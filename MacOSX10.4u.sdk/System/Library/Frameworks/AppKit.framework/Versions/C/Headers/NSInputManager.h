/*
	NSInputManager.h
	Application Kit
	Copyright (c) 1994-2005, Apple Computer, Inc.
	All rights reserved.
 */

#import <Foundation/NSObject.h>
#import <Foundation/NSGeometry.h>
#import <Foundation/NSRange.h>

@class NSArray, NSAttributedString, NSEvent, NSInputServer, NSImage;

@protocol NSTextInput

- (void) insertText:(id)aString; // instead of keyDown: aString can be NSString or NSAttributedString
- (void) doCommandBySelector:(SEL)aSelector;
	// setMarkedText: cannot take a nil first argument. aString can be NSString or NSAttributedString
- (void) setMarkedText:(id)aString selectedRange:(NSRange)selRange;

- (void) unmarkText;
- (BOOL) hasMarkedText;
- (long) conversationIdentifier;

/* Returns attributed string at the range.  This allows input mangers to query any range in backing-store.  May return nil.
*/
- (NSAttributedString *) attributedSubstringFromRange:(NSRange)theRange;

/* This method returns the range for marked region.  If hasMarkedText == false, it'll return NSNotFound location & 0 length range.
*/
- (NSRange) markedRange;

/* This method returns the range for selected region.  Just like markedRange method, its location field contains char index from the text beginning.
*/
- (NSRange) selectedRange;

/* This method returns the first frame of rects for theRange in screen coordindate system.
*/
- (NSRect) firstRectForCharacterRange:(NSRange)theRange;

/* This method returns the index for character that is nearest to thePoint.  thPoint is in screen coordinate system.
*/
- (unsigned int)characterIndexForPoint:(NSPoint)thePoint;

/* This method is the key to attribute extension.  We could add new attributes through this method. NSInputServer examines the return value of this method & constructs appropriate attributed string.
*/
- (NSArray*) validAttributesForMarkedText;

@end

@interface NSInputManager : NSObject <NSTextInput> {
/*All instance variables are private*/
@private
    id _currentClient;
    id _server;			// an NSInputServer obj, usually
    id _bundleObj;		// principal obj instance of bundle, if any
    id _keybindings;		// optional extra bindings, if any
    NSString *_trueName;	// name passed to "init"
    NSString *_connectionName;	// the connection banner
    NSString *_hostName;	// host to run on or nil if own host
    NSString *_procToExec;	// process path, if any
    NSString *_visibleName;	// localized user-visible name
    NSString *_bundleName;	// path to bundle, if any
    NSString *_language;		// language name
    NSImage *_image;		// image for menu item
    unsigned int _flags;
    NSString *_keyBindingsName;	// path to the default bindings, if any
    int _reservedInputManager2;
}

/* The "current input manager" is the one that is receiving input events at the time this method is called.  It may change out from under you, so don't cache the return value.
*/
+ (NSInputManager *) currentInputManager;

/* Cycle through list of input managers. Called from NSKeyBindingManager via doCommandBySelector:.
*/
+ (void)cycleToNextInputLanguage:(id)sender;
+ (void)cycleToNextInputServerInLanguage:(id)sender;

- (NSInputManager *) initWithName:(NSString *)inputServerName host:(NSString *)hostName;

- (NSString *) localizedInputManagerName;

/* These messages are sent by Views that conform to the NSTextInput protocol TO the Current Input Manager when things happen via user or programmatic action.  E.g., when the mouse moves outside the marked range, send markedTextWillBeAbandoned:.  If the user selects some new text or moves the mouse within the marked region, send markedTextSelectionChanged:.  Not all input manager/server combinations will allow all changes, but abandoning of the marked region cannot be aborted.
*/ 

- (void) markedTextAbandoned:(id)cli; /* send after abandoning */
- (void) markedTextSelectionChanged:(NSRange)newSel client:(id)cli; /* send after changing */

/* This corresponds to a server method for input managers that demand to do their own interepretation of command keys as long as they're active.  This will typically be called by a key binder to find out whether it shouldn't just pass along strings.
*/
- (BOOL) wantsToInterpretAllKeystrokes;

- (NSString*) language;

- (NSImage *) image;

- (NSInputServer*) server;

/* If corresponding input server wants to handle mouse events within marked region, this should return YES.  In that case, handleMouseEvent is sent. Otherwiese, mouse events are handled by first responder.
*/
- (BOOL) wantsToHandleMouseEvents;

- (BOOL) handleMouseEvent:(NSEvent*)theMouseEvent;

/* This should return YES when the input method (language) prefers to delay text change notification 'till the input is actually committed.
*/
- (BOOL) wantsToDelayTextChangeNotifications;
@end
