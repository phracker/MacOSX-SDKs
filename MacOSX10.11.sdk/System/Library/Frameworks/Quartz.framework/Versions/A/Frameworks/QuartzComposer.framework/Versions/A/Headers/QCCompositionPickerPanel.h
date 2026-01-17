/*
	Copyright:	(c) 2003-2008 by Apple, Inc., all rights reserved.
*/

#import <AppKit/AppKit.h>

#if defined(MAC_OS_X_VERSION_10_5) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5)

#import <QuartzComposer/QCCompositionPickerView.h>

/* HIGH-LEVEL NOTES:
- The Quartz Composer composition picker panel is a floating window version of the QCCompositionPickerView.
- The composition picker panel displays a picker for a set of Quartz compositions from the Quartz Composer composition repository.
- The user can browse the compositions and select a single one, or none if allowed.
- Use standard NSWindow methods like -makeKeyAndOrderFront: / -orderOut to show or hide the panel.
- QCCompositionPickerPanel cannot be subclassed.
*/

/* Notification names */
extern NSString* const QCCompositionPickerPanelDidSelectCompositionNotification; //QCComposition

/* Quartz Composer composition picker panel */
@interface QCCompositionPickerPanel : NSPanel
{
@private
	__strong void*				_private;
}

/*
Returns the shared instance of the QCCompositionPickerPanel.
*/
+ (QCCompositionPickerPanel*) sharedCompositionPickerPanel;

/*
Returns the QCCompositionPickerView used by the panel so that it can be configured.
*/
- (QCCompositionPickerView*) compositionPickerView;

@end

#endif
