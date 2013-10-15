/*
	NSInputServer.h
	Application Kit
	Copyright (c) 1994-2005, Apple Computer, Inc.
	All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSGeometry.h>
#import <Foundation/NSRange.h>

/* These methods must be implemented by the delegate.
*/
@protocol NSInputServiceProvider

- (void) insertText:(id)aString client:(id)sender;
- (void) doCommandBySelector:(SEL)aSelector client:(id)sender;
- (void) markedTextAbandoned:(id)sender;
- (void) markedTextSelectionChanged:(NSRange)newSel client:(id)sender;
- (void) terminate:(id)sender;

/* Normally canBeDisabled returns YES and is implemented that way in the abstract NSInputServer class.
*/
- (BOOL) canBeDisabled;

/* Many existing input servers have built-in key bindings that affect what happens within the marked region.  If such an input server wants to handle ALL key events through insertText:client:conversation: and never receive doCommandBySelector:client:conversation:, then it should respond (consistently) YES to this method.  The default is NO.  The processing of incoming events looks at this flag as reflected in the corresponding NSInputManager, before deciding how to deal with events.  A module which responds YES to this method must be prepared to deal with arbitrary strings of Unicode characters under all circumstances whenever it is active.
*/
- (BOOL) wantsToInterpretAllKeystrokes;

/* Input servers that wants to receive mouse notifications should return YES & implement NSInputServerMouseTrackers protocol */
- (BOOL) wantsToHandleMouseEvents;

/* This should return YES when the input method (language) prefers to delay text change notification 'till the input is actually committed.
*/
- (BOOL) wantsToDelayTextChangeNotifications;

/* These methods are sent by current input manager when the application changes state so that the server can update its concept of who's current.  The actually "active" sender is the last one to have sent a senderDidBecomeActive: message.  They may not arrive in the expected order.
*/
- (void) inputClientBecomeActive:(id)sender;
- (void) inputClientResignActive:(id)sender;

/* These methods are sent by current input manger when it's enabled & the server returns YES to canBeDisabled.  When disabled, the server is expected to send only insertText: or doCommandBySelector:.
*/
- (void) inputClientEnabled:(id)sender;
- (void) inputClientDisabled:(id)sender;

/* These methods are sent by input manager when the conversation within a particular sender changes.
*/
- (void) activeConversationWillChange:(id)sender fromOldConversation:(long)oldConversation;
- (void) activeConversationChanged:(id)sender toNewConversation:(long)newConversation;

@end

/* These methods are sent to input servers that return YES to wantsToHandleMouseEvents.  thePoint is in screen coordinate.
*/
@protocol NSInputServerMouseTracker
- (BOOL) mouseDownOnCharacterIndex:(unsigned)theIndex atCoordinate:(NSPoint)thePoint withModifier:(unsigned int)theFlags client:(id)sender;
- (BOOL) mouseDraggedOnCharacterIndex:(unsigned)theIndex atCoordinate:(NSPoint)thePoint withModifier:(unsigned int)theFlags client:(id)sender;
- (void) mouseUpOnCharacterIndex:(unsigned)theIndex atCoordinate:(NSPoint)thePoint withModifier:(unsigned int)theFlags client:(id)sender;
@end

@interface NSInputServer : NSObject <NSInputServiceProvider, NSInputServerMouseTracker> {
    NSString *_name;
    id _delegate;
}

- initWithDelegate:(id)aDelegate name:(NSString *)name;
@end
