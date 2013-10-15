// ================================================================================
//	**** PUBLIC HEADER ****
//
//	InterfaceBuilder.framework - IBInspectorManager.h
//	Copyright (c) 1991-2000 Apple Computer, Inc.
//	All rights reserved.
//
// ================================================================================

#import <Foundation/Foundation.h>
#import <InterfaceBuilder/IBSystem.h>
#import <InterfaceBuilder/IBDocuments.h>

@class IBInspector;
@class IBInspectorPanel;
@class IBInspectorMode;

@interface IBInspectorManager : NSObject
{
@private
    IBInspectorPanel 	*inspectorPanel;
    id 			selectedObject;
    id <IBDocuments> 	inspectedDocument;
    IBInspector 	*inspector;
    NSMutableArray 	*modes;
    IBInspectorMode	*currentMode;
}
+ (IBInspectorManager *)sharedInspectorManager;
- (void)addInspectorModeWithIdentifier:(NSString *)identifier
	forObject:(id)object localizedLabel:(NSString *)label
	inspectorClassName:(NSString *)inspectorClassName
	ordering:(float)ordering;
- (unsigned int)indexOfModeWithIdentifier:(NSString *)identifier;
@end

/* Notifications. */

/* IB will inspect an object with a new mode.  The notification object is
 * the mode's identifier. */
IB_EXTERN NSString * const IBWillInspectWithModeNotification;

/* IB will inspect a new object.  The notification object is the object
 * to be inspected. */
IB_EXTERN NSString * const IBWillInspectObjectNotification;

// Predefined inspector modes (for all frameworks)
IB_EXTERN NSString * const IBInspectAttributesMode;
IB_EXTERN NSString * const IBInspectConnectionsMode;
