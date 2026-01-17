/*
	NSDragging.h
	Application Kit
	Copyright (c) 1994-2011, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSObjCRuntime.h>
#import <Foundation/NSObject.h>
#import <Foundation/NSGeometry.h>
#import <limits.h>

@class NSDraggingItem, NSDraggingSession, NSImage, NSPasteboard, NSView, NSWindow;
@class NSURL, NSArray, NSDictionary;
@protocol NSPasteboardWriting;


typedef NSUInteger NSDragOperation;

enum {
    NSDragOperationNone		= 0,
    NSDragOperationCopy		= 1,
    NSDragOperationLink		= 2,
    NSDragOperationGeneric	= 4,
    NSDragOperationPrivate	= 8,
    NSDragOperationAll_Obsolete	= 15,
    NSDragOperationMove		= 16,
    NSDragOperationDelete	= 32,
    NSDragOperationEvery	= NSUIntegerMax
};

// NSDragOperationAll is deprecated - please use NSDragOperationEvery
#define NSDragOperationAll NSDragOperationAll_Obsolete

#if MAC_OS_X_VERSION_10_7 <= MAC_OS_X_VERSION_MAX_ALLOWED
enum {
    NSDraggingFormationDefault = 0, // System determined formation.
    NSDraggingFormationNone,  // Drag images maintain their set positions relative to each other
    NSDraggingFormationPile,  // Drag images are placed on top of each other with random rotations
    NSDraggingFormationList,  // Drag images are laid out vertically, non-overlapping with the left edges aligned
    NSDraggingFormationStack // Drag images are laid out overlapping diagonally
};
#endif
typedef NSInteger NSDraggingFormation;

#if MAC_OS_X_VERSION_10_7 <= MAC_OS_X_VERSION_MAX_ALLOWED
enum {
    NSDraggingContextOutsideApplication = 0,
    NSDraggingContextWithinApplication
};
#endif
typedef NSInteger NSDraggingContext;

#if MAC_OS_X_VERSION_10_7 <= MAC_OS_X_VERSION_MAX_ALLOWED
enum {
    NSDraggingItemEnumerationConcurrent			= NSEnumerationConcurrent,
    /* When the following option is set, AppKit will automatically set the imageComponentProvider to nil for all dragging items that do not meet the classes/searchOptions criteria. Effectively, this hides the drag image for non valid items for this destination. */
    NSDraggingItemEnumerationClearNonenumeratedImages 	= (1UL << 16),
};
#endif
typedef NSUInteger NSDraggingItemEnumerationOptions;

/* protocol for the sender argument of the messages sent to a drag destination.  The view or
   window that registered dragging types sends these messages as dragging is
   happening to find out details about that session of dragging.
 */
@protocol NSDraggingInfo <NSObject>
@required
- (NSWindow *)draggingDestinationWindow;
- (NSDragOperation)draggingSourceOperationMask;
- (NSPoint)draggingLocation;

/* Returns the current location of the current composited dragging image’s origin in NSDraggingFormationNone translated to the base coordinate system of the destination object’s window
*/
- (NSPoint)draggedImageLocation;
- (NSImage *)draggedImage;
- (NSPasteboard *)draggingPasteboard;
- (id)draggingSource;
- (NSInteger)draggingSequenceNumber;
- (void)slideDraggedImageTo:(NSPoint)screenPoint;
- (NSArray *)namesOfPromisedFilesDroppedAtDestination:(NSURL *)dropDestination;

/* Controls the dragging formation while the drag is over this destination. The default value is the current drag formation. */
@property NSDraggingFormation draggingFormation NS_AVAILABLE_MAC(10_7);

/* During the conclusion of an accepted drag, if this property is set to YES, the drag manager will animate each dragging image to their NSDraggingFormationNone locations. Otherwise, the drag images are removed without any animation. Note: This property is inspected between -prepareForDragOperation: and -performDragOperation:. If the final destination frames do not match the current NSDraggingFormationNone frames, then enumerate through the draggingItems during -performDragOperation: to set thier NSDraggingFormationNone frames to the correct destinations.
 */
@property BOOL animatesToDestination NS_AVAILABLE_MAC(10_7);

/* During draggingEntered: or draggingUpdated:, you are responsible for returning the drag operation. In some cases, you may accept some, but not all items on the dragging pasteboard. (For example, you only accept image files.) If you only accept some of the items, you should set this property so the drag manager can update the drag count badge. When -updateItems: is called, you should set the image of non valid dragging items to nil. If none of the drag items are valid then do not call this method. Simply return NSDragOperationNone from draggingEntered: and/or draggingUpdated: and do not modify any drag item properties.
 */
@property NSInteger numberOfValidItemsForDrop NS_AVAILABLE_MAC(10_7);

/* Use the following enumerate method to modify the properties of each dragging item. For example, change the drag image and size.
   Note: All changes made here are only in effect while the drag is over the destination. When the drag exits the destination all properties return to the values last set by the dragging session.
*/

#if NS_BLOCKS_AVAILABLE
/* Enumerate through each dragging item. Any changes made to the properties of the draggingItem are reflected in the drag and are automatically removed when the drag exits. Classes in the provided array must implement the NSPasteboardReading protocol. Cocoa classes that implement this protocol include NSImage, NSString, NSURL, NSColor, NSAttributedString, and NSPasteboardItem. For every item on the pasteboard, each class in the provided array will be queried for the types it can read using -readableTypesForPasteboard:. An instance will be created of the first class found in the provided array whose readable types match a conforming type contained in that pasteboard item. If an Instance is created from the pasteboard item data, it is placed into an NSDraggingItem along with the dragging properties of that item such as the dragging image. The NSDraggingItem is then passed as a parameter to the provided block. Additional search options, such as restricting the search to file URLs with particular content types, can be specified with a search options dictionary.  See the comments for the Pasteboard Reading Options keys in NSPasteboard.h for a full description. Note: all coordinate properties in the NSDraggingItem are in the coordinate system of view. If view is nil, the screen coordinate space is used.
*/
- (void)enumerateDraggingItemsWithOptions:(NSDraggingItemEnumerationOptions)enumOpts forView:(NSView *)view classes:(NSArray *)classArray searchOptions:(NSDictionary *)searchOptions usingBlock:(void (^)(NSDraggingItem *draggingItem, NSInteger idx, BOOL *stop))block NS_AVAILABLE_MAC(10_7);
#endif
@end


/* Methods implemented by an object that receives dragged images.  The
   destination view or window is sent these messages during dragging if it
   responds to them.
 */
@protocol NSDraggingDestination <NSObject>
@optional
- (NSDragOperation)draggingEntered:(id <NSDraggingInfo>)sender;
- (NSDragOperation)draggingUpdated:(id <NSDraggingInfo>)sender; /* if the destination responded to draggingEntered: but not to draggingUpdated: the return value from draggingEntered: is used */
- (void)draggingExited:(id <NSDraggingInfo>)sender;
- (BOOL)prepareForDragOperation:(id <NSDraggingInfo>)sender;
- (BOOL)performDragOperation:(id <NSDraggingInfo>)sender;
- (void)concludeDragOperation:(id <NSDraggingInfo>)sender;
/* draggingEnded: is implemented as of Mac OS 10.5 */
- (void)draggingEnded:(id <NSDraggingInfo>)sender;
/* the receiver of -wantsPeriodicDraggingUpdates should return NO if it does not require periodic -draggingUpdated messages (eg. not autoscrolling or otherwise dependent on draggingUpdated: sent while mouse is stationary) */
- (BOOL)wantsPeriodicDraggingUpdates;

/* While a destination may change the dragging images at any time, it is recommended to wait until this method is called before updating the dragging image. This allows the system to delay changing the dragging images until it is likely that the user will drop on this destination. Otherwise, the dragging images will change too often during the drag which would be distracting to the user. The destination may update the dragging images by calling one of the -enumerateDraggingItems methods on the sender.
*/
- (void)updateDraggingItemsForDrag:(id <NSDraggingInfo>)sender NS_AVAILABLE_MAC(10_7);
@end


@protocol NSDraggingSource <NSObject>
/* Methods implemented by an object that initiates a drag session. The source application is sent these messages during dragging.  The first must be implemented, the others are sent if the source responds to them.
*/

@required 
/* Declares what types of operations the source allows to be performed. Apple may provide more specific "within" values in the future. To account for this, for unrecongized localities, return the operation mask for the most specific context that you are concerned with. For example:
    switch(context) {
        case NSDraggingContextOutsideApplication:
            return ...
            break;

        case NSDraggingContextWithinApplication:
        default:
            return ...
            break;
    }
*/
- (NSDragOperation)draggingSession:(NSDraggingSession *)session sourceOperationMaskForDraggingContext:(NSDraggingContext)context;

@optional
- (void)draggingSession:(NSDraggingSession *)session willBeginAtPoint:(NSPoint)screenPoint;
- (void)draggingSession:(NSDraggingSession *)session movedToPoint:(NSPoint)screenPoint;
- (void)draggingSession:(NSDraggingSession *)session endedAtPoint:(NSPoint)screenPoint operation:(NSDragOperation)operation;

- (BOOL)ignoreModifierKeysForDraggingSession:(NSDraggingSession *)session;

@end

@interface NSObject(NSDraggingSourceDeprecated)
/* The following methods are informally deprecated and are only called if the source does not implement the NSDraggingSource protocol methods. These methods will be formally deprecated in a future OS release
*/
- (NSDragOperation)draggingSourceOperationMaskForLocal:(BOOL)flag;
- (NSArray *)namesOfPromisedFilesDroppedAtDestination:(NSURL *)dropDestination;
- (void)draggedImage:(NSImage *)image beganAt:(NSPoint)screenPoint;
- (void)draggedImage:(NSImage *)image endedAt:(NSPoint)screenPoint operation:(NSDragOperation)operation;
- (void)draggedImage:(NSImage *)image movedTo:(NSPoint)screenPoint;
- (BOOL)ignoreModifierKeysWhileDragging;
// -draggedImage:endedAt:deposited: was deprecated in Mac OS 10.1.  Sources should instead implement the NSDraggingSource protocol instead
- (void)draggedImage:(NSImage *)image endedAt:(NSPoint)screenPoint deposited:(BOOL)flag NS_DEPRECATED_MAC(10_0, 10_1);

// Formally deprecated 
- (void)draggedImage:(NSImage *)image endedAt:(NSPoint)screenPoint deposited:(BOOL)flag DEPRECATED_IN_MAC_OS_X_VERSION_10_1_AND_LATER;
@end
