/*
	Copyright:	(c) 2003-2008 by Apple, Inc., all rights reserved.
*/
#import <QuartzComposer/QuartzComposerDefines.h>
#import <AppKit/AppKit.h>

#if defined(MAC_OS_X_VERSION_10_5) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5)

/* HIGH-LEVEL NOTES:
- The QCCompositionPickerView is a view that displays a picker for a set of Quartz compositions from the Quartz Composer composition repository.
- The user can browse the compositions and select a single one, or none if allowed.
- To set the input parameters of the compositions being displayed by the composition picker view, use -setDefaultValue:forInputKey:
- Note that the composition picker view will not automatically refresh its content when the composition repository is updated: it's up to the client to do so if needed.
*/

/* Notification names */
extern NSString* const QCCompositionPickerViewDidSelectCompositionNotification QC_DEPRECATED_MAC(10_15); //QCComposition

/* Opaque QCComposition object from QCCompositionRepository */
@class QCComposition;

/* Quartz Composer composition picker view */
QC_CLASS_DEPRECATED_MAC(10_15)
@interface QCCompositionPickerView : NSView
{
@private
	void*				_QCCompositionPickerViewPrivate;
}

/*
Sets the list of compositions in the composition picker view from the compositions in the Quartz Composer composition repository matching a given protocol and set of attributes.
Pass one or more attributes and their values to require only compositions that have these attributes set to those values, or pass nil to not do any filtering on attributes.
*/
- (void) setCompositionsFromRepositoryWithProtocol:(NSString*)protocol andAttributes:(NSDictionary*)attributes;

/*
Returns the list of compositions currently in the composition picker view as QCComposition objects.
*/
- (NSArray*) compositions;

/*
Sets / Retrieves the composition picker view delegate.
*/
- (void) setDelegate:(id)delegate;
- (id) delegate;

/*
Enables / Disables the display of the composition names in the composition picker view (default is NO).
*/
- (void) setShowsCompositionNames:(BOOL)flag;
- (BOOL) showsCompositionNames;

/*
Allows / Disallows empty composition selection in the composition picker view (default is NO).
*/
- (void) setAllowsEmptySelection:(BOOL)flag;
- (BOOL) allowsEmptySelection;

/*
Sets / Retrieves the aspect ratio at which to display compositions in the composition picker view.
*/
- (void) setCompositionAspectRatio:(NSSize)ratio;
- (NSSize) compositionAspectRatio;

/*
Sets the default value to use for composition input parameters with a given key.
This default value overrides any initial value existing for composition input parameters with this key.
The supported value types are the same as for -setValue:forInputKey: in the <QCCompositionRenderer> protocol.
Pass "nil" as the value to clear the default value.
*/
- (void) setDefaultValue:(id)value forInputKey:(NSString*)key;

/*
Clears all default values previously set with -setDefaultValue:forInputKey:.
*/
- (void) resetDefaultInputValues;

/*
Sets the currently selected composition in the composition picker view (pass nil to select no composition).
Behavior is undefined if passing a composition not in the list of compositions currently in the composition picker view.
*/
- (void) setSelectedComposition:(QCComposition*)composition;

/*
Returns the currently selected composition in the composition picker view or nil if none.
*/
- (QCComposition*) selectedComposition;

/*
Starts animating the compositions in the composition picker view.
*/
- (void) startAnimation:(id)sender;

/*
Stops animating the compositions in the composition picker view.
*/
- (void) stopAnimation:(id)sender;

/*
Returns true if the composition picker view is currently animating its compositions.
*/
- (BOOL) isAnimating;

/*
Sets / Retrieves the maximum composition animation framerate (pass 0.0 to specify no limit).
*/
- (void) setMaxAnimationFrameRate:(float)maxFPS;
- (float) maxAnimationFrameRate;

/*
Sets / Retrieves the composition picker view background color
*/
- (void) setBackgroundColor:(NSColor*)color;
- (NSColor*) backgroundColor;

/*
Sets / Returns whether the composition picker view draws its background.
*/
- (void) setDrawsBackground:(BOOL)flag;
- (BOOL) drawsBackground;

/*
Sets / Retrieves number of columns
*/
- (NSUInteger) numberOfColumns;
- (void) setNumberOfColumns:(NSUInteger)columns;

/*
Sets / Retrieves number of rows
*/
- (NSUInteger) numberOfRows;
- (void) setNumberOfRows:(NSUInteger)rows;

@end

/* Informal protocol for the QCCompositionPickerView delegate */
QC_CLASS_DEPRECATED_MAC(10_15)
@interface NSObject (QCCompositionPickerViewDelegate)

/*
Called whenever the selected composition in the composition picker view changes.
The "composition" parameter will be nil if the previously selected composition is deselected.
*/
- (void) compositionPickerView:(QCCompositionPickerView*)pickerView didSelectComposition:(QCComposition*)composition;

/*
Called when the composition picker view starts animating its compositions.
*/
- (void) compositionPickerViewDidStartAnimating:(QCCompositionPickerView*)pickerView;

/*
Called when the composition picker view stops animating its compositions.
*/
- (void) compositionPickerViewWillStopAnimating:(QCCompositionPickerView*)pickerView;

@end

#endif
