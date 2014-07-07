// ================================================================================
//	**** PUBLIC HEADER ****
//
//	InterfaceBuilder.framework - IBViewAdditions.h 
//	Copyright (c) 1995-2000 Apple Computer, Inc.
//	All rights reserved.
//
// ================================================================================

#import <InterfaceBuilder/IBViewProtocol.h>

// --------------------------------------------------------------------------------
//	@interface NSView (NSView_IBViewProtocol) <IBViewProtocol>
// --------------------------------------------------------------------------------
// Default implementation of the IBViewProtocol for NSView

@interface NSView (NSView_IBViewProtocol) <IBViewProtocol>

- (NSRect)layoutRect;					// Calls layoutRectFromFrame: 
- (NSRect)layoutRectFromFrame:(NSRect)frame;		// Primitive
- (NSRect)frameFromLayoutRect:(NSRect)layoutRect;
@end
