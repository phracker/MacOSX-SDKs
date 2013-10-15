/*
	Copyright:	(c) 2003-2008 by Apple, Inc., all rights reserved.
*/

#import <AppKit/AppKit.h>

#if defined(MAC_OS_X_VERSION_10_5) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5)

#import <QuartzComposer/QCRenderer.h>

/* HIGH-LEVEL NOTES:
- The Quartz Composer composition parameter view allows to live-edit the input parameters of a composition currently in use by a QCRenderer, QCView or QCCompositionLayer.
*/

/* Quartz Composer composition parameters view */
@interface QCCompositionParameterView : NSView
{
@private
	__strong void*				_QCCompositionParameterViewPrivate;
}

/*
Sets the current composition renderer whose composition input parameters to edit in the parameter view (pass nil to unset).
*/
- (void) setCompositionRenderer:(id<QCCompositionRenderer>)renderer;

/*
Returns the current composition renderer whose composition the parameter view is editing, or nil if none.
*/
- (id<QCCompositionRenderer>) compositionRenderer;

/*
Returns true if the composition currently loaded on the composition renderer has any input parameters.
*/
- (BOOL) hasParameters;

/*
Sets / Retrieves the composition parameter view background color
*/
- (void) setBackgroundColor:(NSColor*)color;
- (NSColor*) backgroundColor;

/*
Sets / Returns whether the composition parameter view draws its background.
*/
- (void) setDrawsBackground:(BOOL)flag;
- (BOOL) drawsBackground;

/*
Sets / Retrieves the composition parameter view delegate.
*/
- (void) setDelegate:(id)delegate;
- (id) delegate;

@end

/* Informal protocol for the QCCompositionParameterView delegate */
@interface NSObject (QCCompositionParameterViewDelegate)

/*
Called whenever the composition parameter view is layed out and allows the client to hide some specific input parameters.
*/
- (BOOL) compositionParameterView:(QCCompositionParameterView*)parameterView shouldDisplayParameterWithKey:(NSString*)portKey attributes:(NSDictionary*)portAttributes;

/*
Called whenever an input parameter in the composition parameter view has been edited.
*/
- (void) compositionParameterView:(QCCompositionParameterView*)parameterView didChangeParameterWithKey:(NSString*)portKey;

@end

#endif
