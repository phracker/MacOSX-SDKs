// ================================================================================
//	**** PUBLIC HEADER ****
//
//	InterfaceBuilder.framework - IBInspector.h
//	Copyright (c) 2000 Apple Computer, Inc.
//	All rights reserved.
//
// ================================================================================

#import <InterfaceBuilder/IBSystem.h>
#import <InterfaceBuilder/IBDocuments.h>
#import <Foundation/Foundation.h>

@class NSButton;
@class NSWindow;
@class NSView;

// --------------------------------------------------------------------------------
//	@interface IBInspector : NSObject
// --------------------------------------------------------------------------------

@interface IBInspector : NSObject
{
@private
    id 	       		_object;
    NSView  		*_inspectorView;
    NSView 		*_initialFirstResponder;
    NSButton  		*_okButton;
    NSButton  		*_revertButton;
}
- (BOOL)wantsButtons; /* Default implementation returns NO */
- (void)revert:(id)sender;
- (void)ok:(id)sender;
- (id)object;
- (id <IBDocuments>)inspectedDocument;
- (NSWindow *)window;
- (NSButton *)okButton;
- (NSButton *)revertButton;
- (NSView *)initialFirstResponder;
- (BOOL)isResizable; /* Default implementation returns NO, if isResizable == NO then inspectors are centered */

// Undo Support for inspectors.
- (void)beginUndoGrouping;
- (void)noteAttributesWillChangeForObject:(id)object; // Note: old API noteAttributeDidChangedForObject: simply calls this one

@end
