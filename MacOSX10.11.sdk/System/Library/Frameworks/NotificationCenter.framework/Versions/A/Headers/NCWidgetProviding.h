/*
 * NCWidgetProviding.h
 * NotificationCenter.framework
 * Copyright (c) 2014 Apple Inc. All rights reserved.
 */

#import <AppKit/AppKit.h>
#import <Foundation/NSExtensionRequestHandling.h>

/* Set the height value of the NSViewController's preferredContentSize property
   to indicate the preferred height of the widget's content instead of directly
   resizing the view.

   The Notification Center will take this preference under advisement and size
   the view appropriately. Clients should then layout within the bounds of the
   view in viewWillLayoutSubviews.

   Clients can animate their own content along with the resize animation by
   implementing viewWillTransitionToSize: and supply-
   ing the animations to the provided transition coordinator. */

typedef NS_ENUM(NSUInteger, NCUpdateResult) {
    NCUpdateResultNewData, // The update resulted in new data.
    NCUpdateResultNoData,  // The update did not result in any new data since the last update.
    NCUpdateResultFailed   // The update attempt failed.
} NS_ENUM_AVAILABLE_MAC(10_10);


/* NCWidgetProviding is an optional protocol for further customizing aspects
   of the widget's behavior. */
@protocol NCWidgetProviding <NSExtensionRequestHandling>

@optional

/* Called to allow the widget to update its state. This is done prior to taking
   a snapshot or possibly other operations. Clients should call the block
   provided when the work is complete, passing the appropriate NCUpdateResult
   value. */
- (void)widgetPerformUpdateWithCompletionHandler:(void (^)(NCUpdateResult result))completionHandler;

/* Implement this method to cutomize the margin insets of the widget content. */
- (NSEdgeInsets)widgetMarginInsetsForProposedMarginInsets:(NSEdgeInsets)defaultMarginInset;

/* Return YES to indicate that the widget supports editing mode.
   A button to begin and end editing will be created in the widget's header. */
@property (readonly) BOOL widgetAllowsEditing;

/* Called in response to the begin editing button when widgetAllowsEditing. */
- (void)widgetDidBeginEditing;

/* Called in response to the end editing button when widgetAllowsEditing.
   This will also be called when the widget is deactivated in response to
   another widget being edited. */
- (void)widgetDidEndEditing;

@end


@interface NSViewController (NCWidgetProvidingPresentationStyles)

/* Presents the viewController modally within the Notification Center widget.
   Use dismissViewController: to end the presentation of the view controller. */
- (void)presentViewControllerInWidget:(NSViewController *)viewController NS_AVAILABLE_MAC(10_10);

@end
