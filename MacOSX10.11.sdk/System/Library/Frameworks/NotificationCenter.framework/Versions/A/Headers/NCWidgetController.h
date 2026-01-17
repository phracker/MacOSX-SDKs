/*
 * NCWidgetController.h
 * NotificationCenter.framework
 * Copyright (c) 2014 Apple Inc. All rights reserved.
 */

#import <Foundation/Foundation.h>

/* The NCWidgetController provides an interface available to both the widget
   and the providing app can coordinate whether there is widget content
   available for display.

   If the client no longer has content to display, it can obtain the widget
   controller and update this state.

   Later, should the providing app determine that the widget should have content
   it can update the widget, even if the widget is no longer running. */

NS_CLASS_AVAILABLE_MAC(10_10)
@interface NCWidgetController : NSObject

+ (instancetype)widgetController;

+ (NCWidgetController *)defaultWidgetController __deprecated_msg("Use widgetController instead.");

/* Indicate that the widget has content to display, and that the view should be
   visible in the Notification Center. (Widgets are considered to have content
   by default.) This method can be called on the widgetController in
   either the widget or the providing app. */
- (void)setHasContent:(BOOL)flag forWidgetWithBundleIdentifier:(NSString *)bundleID;

@end
