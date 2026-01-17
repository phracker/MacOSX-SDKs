/*	NSUndoManager.h
	Copyright (c) 1995-2019, Apple Inc. All rights reserved.
*/

//
// NSUndoManager is a general-purpose undo stack where clients can register
// callbacks to be invoked should an undo be requested.
//

#import <Foundation/NSObject.h>
#include <stdint.h>
#import <Foundation/NSNotification.h>
#import <Foundation/NSRunLoop.h>

@class NSArray<ObjectType>;
@class NSString;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

// used with NSRunLoop's performSelector:target:argument:order:modes:
static const NSUInteger NSUndoCloseGroupingRunLoopOrdering = 350000;

/// A key used to set and get user info for undo and redo actions
typedef NSString * NSUndoManagerUserInfoKey NS_TYPED_EXTENSIBLE_ENUM NS_SWIFT_NAME(UndoManager.UserInfoKey) API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0));

API_AVAILABLE(macos(10.0), ios(3.0), watchos(2.0), tvos(9.0))
NS_SWIFT_UI_ACTOR
@interface NSUndoManager : NSObject

/// Marks the beginning of an undo group.
///
/// All individual undo operations before a subsequent ``endUndoGrouping`` message are grouped together and reversed by a later ``undo`` message. By default undo groups are begun automatically at the start of the event loop, but you can begin your own undo groups with this method, and nest them within other groups.
/// 
/// This method posts an ``NSUndoManagerCheckpointNotification`` unless a top-level undo is in progress. It posts an ``NSUndoManagerDidOpenUndoGroupNotification`` if a new group was successfully created.
- (void)beginUndoGrouping;

/// Marks the end of an undo group.
/// 
/// All individual undo operations back to the matching ``beginUndoGrouping`` message are grouped together and reversed by a later ``undo`` or ``undoNestedGroup`` message. Undo groups can be nested, thus providing functionality similar to nested transactions. Raises an ``NSInternalInconsistencyException`` if there’s no ``beginUndoGrouping`` message in effect.
/// 
/// This method posts an ``NSUndoManagerCheckpointNotification`` and an ``NSUndoManagerDidCloseUndoGroupNotification`` just before the group is closed.
- (void)endUndoGrouping;

/// The number of nested undo groups (or redo groups, if Redo was invoked last) in the current event loop.
///
/// An integer indicating the number of nested groups. If `0` is returned, there is no open undo or redo group.
@property (readonly) NSInteger groupingLevel;

/// Disables the recording of undo operations, whether by ``registerUndoWithTarget:selector:object:`` or by invocation-based undo.
///
/// This method can be invoked multiple times by multiple clients. The ``enableUndoRegistration`` method must be invoked an equal number of times to re-enable undo registration.
- (void)disableUndoRegistration;

/// Enables the recording of undo operations.
///
/// Because undo registration is enabled by default, this is used to balance a prior ``disableUndoRegistration``. Undo registration isn’t actually re-enabled until an enable message balances the last disable message in effect.
/// Raises an NSInternalInconsistencyException if invoked while no disableUndoRegistration() message is in effect.
- (void)enableUndoRegistration;

/// Whether the recording of undo operations is enabled.
@property (readonly, getter=isUndoRegistrationEnabled) BOOL undoRegistrationEnabled;

/// A Boolean value that indicates whether the receiver automatically creates undo groups around each pass of the run loop.
///
/// If `true`, the receiver automatically creates undo groups around each pass of the run loop.
/// The default is `true`. If you turn automatic grouping off, you must close groups explicitly before invoking either ``undo`` or ``undoNestedGroup``.
@property BOOL groupsByEvent;


/// The maximum number of top-level undo groups the receiver holds.
///
/// An integer specifying the number of undo groups. A limit of 0 indicates no limit, so old undo groups are never dropped.
/// When ending an undo group results in the number of groups exceeding this limit, the oldest groups are dropped from the stack. The default is 0.
/// If you change the limit to a level below the prior limit, old undo groups are immediately dropped.
@property NSUInteger levelsOfUndo;

/// The modes governing the types of input handled during a cycle of the run loop.
/// 
/// An array of string constants specifying the current run-loop modes.
/// By default, the sole run-loop mode is ``NSDefaultRunLoopMode`` (which excludes data from ``NSConnection`` objects). Some examples of other uses are to limit the input to data received during a mouse-tracking session by setting the mode to ``NSEventTrackingRunLoopMode``, or limit it to data received from a modal panel with ``NSModalPanelRunLoopMode``.
@property (copy) NSArray<NSRunLoopMode> *runLoopModes;

/// Closes the top-level undo group if necessary and invokes ``undoNestedGroup``.
///
/// This method also invokes ``endUndoGrouping`` if the nesting level is 1. Raises an ``NSInternalInconsistencyException`` if more than one undo group is open (that is, if the last group isn’t at the top level).
/// This method posts an ``NSUndoManagerCheckpointNotification``.
- (void)undo;

/// Performs the operations in the last group on the redo stack, if there are any, recording them on the undo stack as a single group.
///
/// Raises an ``NSInternalInconsistencyException`` if the method is invoked during an undo operation.
/// This method posts an ``NSUndoManagerCheckpointNotification`` and ``NSUndoManagerWillRedoChangeNotification`` before it performs the redo operation, and it posts the ``NSUndoManagerDidRedoChangeNotification`` after it performs the redo operation.
- (void)redo;

/// Performs the undo operations in the last undo group (whether top-level or nested), recording the operations on the redo stack as a single group.
/// 
/// Raises an ``NSInternalInconsistencyException`` if any undo operations have been registered since the last ``enableUndoRegistration`` message.
/// This method posts an ``NSUndoManagerCheckpointNotification`` and ``NSUndoManagerWillUndoChangeNotification`` before it performs the undo operation, and it posts an ``NSUndoManagerDidUndoChangeNotification`` after it performs the undo operation.
- (void)undoNestedGroup;

/// Whether the receiver has any actions to undo.
///
/// The return value does not mean you can safely invoke ``undo`` or ``undoNestedGroup`` — you may have to close open undo groups first.
@property (readonly) BOOL canUndo;

/// Whether the receiver has any actions to redo.
/// 
/// Because any undo operation registered clears the redo stack, this method posts an NSUndoManagerCheckpointNotification to allow clients to apply their pending operations before testing the redo stack.
@property (readonly) BOOL canRedo;

/// How many times `undo` can be invoked before there are no more actions left to
/// be undone
@property (readonly) NSUInteger undoCount API_AVAILABLE(macos(14.4), ios(17.4), tvos(17.4), watchos(10.4));
/// How many times `redo` can be invoked before there are no more actions left to
/// be redone
@property (readonly) NSUInteger redoCount API_AVAILABLE(macos(14.4), ios(17.4), tvos(17.4), watchos(10.4));

/// Whether the receiver is in the process of performing its ``undo`` or ``undoNestedGroup`` method.
@property (readonly, getter=isUndoing) BOOL undoing;

/// Whether the receiver is in the process of performing its ``redo`` method.
@property (readonly, getter=isRedoing) BOOL redoing;

/// Clears the undo and redo stacks and re-enables the receiver.
- (void)removeAllActions;

/// Clears the undo and redo stacks of all operations involving the specified target as the recipient of the undo message.
///
/// Doesn't re-enable the receiver if it's disabled.
///
/// - Parameter target: The recepient of the undo mesages to be removed.
- (void)removeAllActionsWithTarget:(id)target;

/// Registers the selector of the specified target to implement a single undo operation that the target receives.
///
/// - Parameter target: The target of the undo operation. The undo manager maintains an unowned reference to `target` to prevent retain cycles.
/// - Parameter selector: The selector for the undo operation.
/// - Parameter object: The argument sent with the selector. The undo manager maintains a strong reference to `object`
- (void)registerUndoWithTarget:(id)target selector:(SEL)selector object:(nullable id)object;

/// Prepares the undo manager for invocation-based undo with the given target as the subject of the next undo operation.
///
/// For example, when called as:
/// 
///     [[undoManager prepareWithInvocationTarget:target] setFont:oldFont color:oldColor]
/// 
/// When undo is called, the specified target will be called with
/// 
///     [target setFont:oldFont color:oldColor]
/// 
/// - Parameter target: The target of the undo operation. The undo manager maintains a weak reference to `target`.
/// - Returns:  A proxy object that forwards messages to the undo manager for recording as undo actions.
- (id)prepareWithInvocationTarget:(id)target;

/// Records a single undo operation for a given target so that when an undo is performed, it executes the specified block.
/// 
/// As with other undo operations, this does not strongly retain target. Care should be taken to avoid introducing retain cycles by other references captured by the block.
/// 
/// - Parameter target: The target of the undo operation.
/// - Parameter undoHandler: The block to be executed when an operation is undone. The block takes a single argument, the target of the undo operation.
- (void)registerUndoWithTarget:(id)target handler:(void (NS_SWIFT_UI_ACTOR ^)(id target))undoHandler API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0)) NS_REFINED_FOR_SWIFT;

/// Sets whether the next undo or redo action is discardable.
///
/// Specifies that the latest undo action may be safely discarded when a document can not be saved for any reason.
/// An example might be an undo action that changes the viewable area of a document.
/// To find out if an undo group contains only discardable actions, look for the ``NSUndoManagerGroupIsDiscardableKey`` in the `userInfo` dictionary of the ``NSUndoManagerWillCloseUndoGroupNotification``.
///
/// - Parameter discardable: Specifies if the action is discardable. YES if the next undo or redo action can be discarded; NO otherwise.
- (void)setActionIsDiscardable:(BOOL)discardable API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));

// This key is set on the user info dictionary of the NSUndoManagerDidCloseUndoGroupNotification, with a NSNumber boolean value of YES, if the undo group as a whole is discardable.
FOUNDATION_EXPORT NSString * const NSUndoManagerGroupIsDiscardableKey API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));

/// Whether the next undo action is discardable.
/// 
/// Specifies that the latest undo action may be safely discarded when a document can not be saved for any reason. These are typically actions that don’t affect persistent state.
/// An example might be an undo action that changes the viewable area of a document.
@property (readonly) BOOL undoActionIsDiscardable API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));

/// Whether the next redo action is discardable.
/// 
/// Specifies that the latest redo action may be safely discarded when a document can not be saved for any reason. These are typically actions that don’t affect persistent state.
/// An example might be an redo action that changes the viewable area of a document.
@property (readonly) BOOL redoActionIsDiscardable API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));

/// The name identifying the undo action.
///
/// The undo action name. Returns an empty string if no action name has been assigned or if there is nothing to undo.
/// For example, if the menu title is “Undo Delete,” the string returned is “Delete.”
@property (readonly, copy) NSString *undoActionName;

/// The name identifying the redo action.
/// 
/// The redo action name. Returns an empty string if no action name has been assigned or if there is nothing to redo.
/// For example, if the menu title is “Redo Delete,” the string returned is “Delete.”
@property (readonly, copy) NSString *redoActionName;

/// Sets the name of the action associated with the Undo or Redo command.
///
/// If `actionName` is an empty string, the undo manager removes the action name currently associated with the menu command.
///
/// - Parameter actionName: The name of the action.
- (void)setActionName:(NSString *)actionName  __attribute__((swift_attr("@_disfavoredOverload")));

/// Get a value from the undo action's user info
///
/// - Parameter key: Which value should be retrieved
-(id _Nullable)undoActionUserInfoValueForKey:(NSUndoManagerUserInfoKey)key API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0));

/// Get a value from the redo action's user info
/// 
/// - Parameter key: Which value should be retrieved
-(id _Nullable)redoActionUserInfoValueForKey:(NSUndoManagerUserInfoKey)key API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0));

/// Set user info for the Undo or Redo command.
/// - Parameter info: Value to be saved in the user info
/// - Parameter key: Key at which the object should be saved
-(void)setActionUserInfoValue:(id _Nullable)info forKey:(NSUndoManagerUserInfoKey)key API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0));

// Call undoMenuItemTitle or redoMenuItemTitle to get the string for the undo or redo menu item.
// In English they will return "Undo <action name>"/"Redo <action name>" or "Undo"/"Redo" if there is
// nothing to undo/redo or no action names were set.
// 

/// The complete title of the Undo menu command, for example, “Undo Paste.”
/// 
/// Returns “Undo” if no action name has been assigned or nil if there is nothing to undo.
@property (readonly, copy) NSString *undoMenuItemTitle;

/// The complete title of the Redo menu command, for example, “Redo Paste.”
/// 
/// Returns “Redo” if no action name has been assigned or nil if there is nothing to redo.
@property (readonly, copy) NSString *redoMenuItemTitle;


// MARK: Localization hooks

// The localization of the pattern is usually done by localizing the string patterns in
// undo.strings. But undo/redoMenuTitleForUndoActionName can also be overridden if
// localizing the pattern happens to not be sufficient.

/// Returns the complete, localized title of the Undo menu command for the action identified by the given name.
/// 
/// Override this method if you want to customize the localization behaviour. This method is invoked by ``undoMenuItemTitle``.
/// 
/// - Parameter actionName: The name of the undo action.
/// - Returns: The localized title of the undo menu item.
- (NSString *)undoMenuTitleForUndoActionName:(NSString *)actionName;

/// Returns the complete, localized title of the Redo menu command for the action identified by the given name.
/// 
/// Override this method if you want to customize the localization behaviour. This method is invoked by ``redoMenuItemTitle``.
/// 
/// - Parameter actionName: The name of the redo action.
/// - Returns: The localized title of the redo menu item.
- (NSString *)redoMenuTitleForUndoActionName:(NSString *)actionName;
@end

FOUNDATION_EXPORT NSNotificationName const NSUndoManagerCheckpointNotification API_AVAILABLE(macos(10.0), ios(3.0), watchos(2.0), tvos(9.0));
    // This is called before an undo group is begun or ended so any
    // clients that need to lazily register undos can do so in the
    // correct group.

FOUNDATION_EXPORT NSNotificationName const NSUndoManagerWillUndoChangeNotification API_AVAILABLE(macos(10.0), ios(3.0), watchos(2.0), tvos(9.0));
FOUNDATION_EXPORT NSNotificationName const NSUndoManagerWillRedoChangeNotification API_AVAILABLE(macos(10.0), ios(3.0), watchos(2.0), tvos(9.0));

FOUNDATION_EXPORT NSNotificationName const NSUndoManagerDidUndoChangeNotification API_AVAILABLE(macos(10.0), ios(3.0), watchos(2.0), tvos(9.0));
FOUNDATION_EXPORT NSNotificationName const NSUndoManagerDidRedoChangeNotification API_AVAILABLE(macos(10.0), ios(3.0), watchos(2.0), tvos(9.0));

FOUNDATION_EXPORT NSNotificationName const NSUndoManagerDidOpenUndoGroupNotification API_AVAILABLE(macos(10.0), ios(3.0), watchos(2.0), tvos(9.0));
FOUNDATION_EXPORT NSNotificationName const NSUndoManagerWillCloseUndoGroupNotification API_AVAILABLE(macos(10.0), ios(3.0), watchos(2.0), tvos(9.0));

// This notification is sent after an undo group closes. It should be safe to undo at this time.
FOUNDATION_EXPORT NSNotificationName const NSUndoManagerDidCloseUndoGroupNotification API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));

NS_HEADER_AUDIT_END(nullability, sendability)
