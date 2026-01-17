// ================================================================================
//	**** PUBLIC HEADER ****
//
//	InterfaceBuilder.framework - IBPalette.h
//	Copyright (c) 1995-2000 Apple Computer, Inc.
//	All rights reserved.
//
// ================================================================================

#import <InterfaceBuilder/IBDocuments.h>

/* InterfaceBuilder pasteboard types. */

IB_EXTERN NSString * const IBCellPboardType;
IB_EXTERN NSString * const IBFormatterPboardType;
IB_EXTERN NSString * const IBMenuItemPboardType;
IB_EXTERN NSString * const IBMenuPboardType;
IB_EXTERN NSString * const IBObjectPboardType;
IB_EXTERN NSString * const IBTableColumnPboardType;
IB_EXTERN NSString * const IBTabViewItemPboardType;
IB_EXTERN NSString * const IBViewPboardType;
IB_EXTERN NSString * const IBWindowPboardType;
IB_EXTERN NSString * const IBScriptControllerPboardType;

@class NSImage;
@class NSView;
@class NSWindow;

@interface IBPalette : NSObject
{
    id <IBDocuments> _paletteDocument;
    NSWindow *_originalWindow;
    NSView *_paletteView;
    NSView *_draggedView;
    id _paletteInfo;
}
/* Associates a view from the palette with an object of a given pboard type. */
- (void)associateObject:(id)object ofType:(NSString *)type withView:(NSView *)view;

/* Called after the palette has been initialized to allow any final
 * initialization. */
- (void)finishInstantiate;

/* Returns the document associated with this palette. */
- (id <IBDocuments>)paletteDocument;

/* Returns the original window associated with this palette. */
- (NSWindow *)originalWindow;

/* Searches the palette bundle for an image of a given name. */
- (NSImage *)imageNamed:(NSString *)name;

/* Allows a palette to prevent the installation of another palette.
 * Default implementation returns YES. */
- (BOOL)shouldInstallPaletteWithPath:(NSString *)path;

// Returns the string to display in an help tag for a given object
- (NSString*)toolTipForObject:(id)object;
@end
