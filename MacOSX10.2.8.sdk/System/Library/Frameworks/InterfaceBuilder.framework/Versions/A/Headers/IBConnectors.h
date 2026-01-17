// ================================================================================
//	**** PUBLIC HEADER ****
//
//	InterfaceBuilder.framework - IBConnectors.h
//	Copyright (c) 1995-2000 Apple Computer, Inc.
//	All rights reserved.
//
// ================================================================================

#import <InterfaceBuilder/IBSystem.h>
#import <AppKit/NSApplication.h>
#import <AppKit/NSNibConnector.h>
#import <AppKit/NSNibControlConnector.h>
#import <AppKit/NSNibOutletConnector.h>

@protocol IBConnectors <NSObject, NSCoding>
- (id)source;
- (id)destination;
- (NSString *)label;
- (void)replaceObject:(id)oldObject withObject:(id)newObject;
- (id)nibInstantiate;
- (void)establishConnection;
@end

@interface NSNibConnector (IBConnectorsProtocol) <IBConnectors>
@end

/* Managing connectors.  The following might be useful when
 * implementing your own connection inspector.
 */

@interface NSApplication (IBConnections)
- (id)connectSource;
- (id)connectDestination;
- (BOOL)isConnecting;
- (void)stopConnecting;
- (void)displayConnectionBetween:(id)source and:(id)destination;
@end

@interface NSObject (IBNibInstantiation)
- (id)nibInstantiate;
@end

/* Notifications. */

/* The notification object is the connector in question. */
IB_EXTERN NSString * const IBWillAddConnectorNotification;
IB_EXTERN NSString * const IBDidAddConnectorNotification;
IB_EXTERN NSString * const IBWillRemoveConnectorNotification;
IB_EXTERN NSString * const IBDidRemoveConnectorNotification;
