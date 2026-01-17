// ================================================================================
//	**** PUBLIC HEADER ****
//
//	InterfaceBuilder.framework - IBObjectProtocol.h 
//	Copyright (c) 2000 Apple Computer, Inc.
//	All rights reserved.
//
// ================================================================================

#import <AppKit/AppKit.h>
#import <InterfaceBuilder/IBDocuments.h>

// --------------------------------------------------------------------------------
//	@protocol IBObjectProtocol
// --------------------------------------------------------------------------------
// This protocol describes all the public API an object may need to implement in order to
// correctly behaves inside IB. NSObject implements all those methods.

@protocol IBObjectProtocol

// --------------------------------------------------------------------------------
// Inspector

// Should return the class name for the given inspector.
- (NSString *)inspectorClassName;
- (NSString *)connectInspectorClassName;
- (NSString *)sizeInspectorClassName;
- (NSString *)helpInspectorClassName;
- (NSString *)classInspectorClassName;

// Should return the title for the inspector panel
- (NSString *)objectNameForInspectorTitle;

// --------------------------------------------------------------------------------
// Editor

// Should returns the class name for the in place editor used to edit this object.
- (NSString *)editorClassName;

// Should returns an image representing this object. Defaults is nil and is usually fine.
- (NSImage *)imageForViewer;

// --------------------------------------------------------------------------------
// Object label

// Should returns the label associated with this object (e.g. "NSButton(OK)" or "NSWindow(myWindow)" )
- (NSString *)nibLabel:(NSString*)objectName;

// --------------------------------------------------------------------------------
// Custom Object

// Returns YES if `self' is a valid replacement class for
// `originalObjectClass', NO otherwise. Default is YES for NSObject
+ (BOOL)canSubstituteForClass:(Class)originalObjectClass;

// Allows special behavior after the nib document has been loaded.
- (void)awakeFromDocument:(id <IBDocuments>)document;
@end

