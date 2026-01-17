// ================================================================================
//	**** PUBLIC HEADER ****
//
//	InterfaceBuilder.framework - IBCellProtocol.h 
//	Copyright (c) 1995-2000 Apple Computer, Inc.
//	All rights reserved.
//
// ================================================================================

#import <AppKit/AppKit.h>
#import <InterfaceBuilder/IBDefines.h>

@protocol IBCellProtocol

- (NSSize)minimumSizeForCellSize:(NSSize)cellSize knobPosition:(IBKnobPosition)knobPosition;
- (NSSize)maximumSizeForCellSize:(NSSize)cellSize knobPosition:(IBKnobPosition)knobPosition;

/* Allows the cell to set up necessary state before alt-dragging. */
- (void)cellWillAltDragWithSize:(NSSize)cellSize;

/* Used when dragging colors to cells. */
- (BOOL)acceptsColor:(NSColor *)color;
- (void)depositColor:(NSColor *)color;

// A string representing the type of widget. Predefined widget types are defined in IBUIMetrics.h
//    Default: kIBViewWidget (generic view)

- (NSString*)ibWidgetType;			

- (BOOL)ibHasAlternateMinimumWidth;		// NO
- (float)ibAlternateMinimumWidth;		// 0
- (BOOL)ibHasAlternateMinimumHeight;		// NO
- (float)ibAlternateMinimumHeight;		// 0

// Base Line support for guides
- (BOOL)ibHasBaseLine;  // Default is NO
- (float)ibBaseLineForCellSize:(NSSize)cellSize; 

// Call super and then matches this cell with the prototype. Call in NSMatrix inspector
- (void)ibMatchPrototype:(NSCell*)prototype;
@end
