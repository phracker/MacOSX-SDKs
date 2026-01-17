/*
 * NCWidgetController.h
 * NotificationCenter.framework
 * Copyright (c) 2014-2015 Apple Inc. All rights reserved.
 */

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN
API_UNAVAILABLE_BEGIN(ios)

/* The NCWidgetController provides an interface available to both the widget
   and the providing app can coordinate whether there is widget content
   available for display.

   If the client no longer has content to display, it can obtain the widget
   controller and update this state.

   Later, should the providing app determine that the widget should have content
   it can update the widget, even if the widget is no longer running. */

API_DEPRECATED("Use WidgetKit instead. Today View extensions have been deprecated.", macos(10.10, 11.0))
@interface NCWidgetController : NSObject

+ (instancetype)widgetController;

+ (NCWidgetController *)defaultWidgetController __deprecated_msg("Use widgetController instead.");

/* Indicate that the widget has content to display, and that the view should be
   visible in the Notification Center. (Widgets are considered to have content
   by default.) This method can be called on the widgetController in
   either the widget or the providing app. */
- (void)setHasContent:(BOOL)flag forWidgetWithBundleIdentifier:(NSString *)bundleID;

@end

API_UNAVAILABLE_END
NS_ASSUME_NONNULL_END
