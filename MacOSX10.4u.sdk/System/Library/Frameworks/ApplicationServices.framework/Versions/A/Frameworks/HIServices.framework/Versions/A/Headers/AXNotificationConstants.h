/*
 *  AXNotificationConstants.h
 *  HIServices
 *
 *  Created by John Louch on Wed Feb 25 2004.
 *  Copyright (c) 2004 Apple Computer, Inc. All rights reserved.
 *
 */

#ifndef __AXNOTIFICATIONCONSTANTS__
#define __AXNOTIFICATIONCONSTANTS__

// focus notifications
#define kAXMainWindowChangedNotification		CFSTR("AXMainWindowChanged")
#define kAXFocusedWindowChangedNotification		CFSTR("AXFocusedWindowChanged")
#define kAXFocusedUIElementChangedNotification		CFSTR("AXFocusedUIElementChanged")

// application notifications
#define kAXApplicationActivatedNotification		CFSTR("AXApplicationActivated")
#define kAXApplicationDeactivatedNotification		CFSTR("AXApplicationDeactivated")
#define kAXApplicationHiddenNotification		CFSTR("AXApplicationHidden")
#define kAXApplicationShownNotification			CFSTR("AXApplicationShown")

// window notifications
#define kAXWindowCreatedNotification			CFSTR("AXWindowCreated")
#define kAXWindowMovedNotification			CFSTR("AXWindowMoved")
#define kAXWindowResizedNotification			CFSTR("AXWindowResized")
#define kAXWindowMiniaturizedNotification		CFSTR("AXWindowMiniaturized")
#define kAXWindowDeminiaturizedNotification		CFSTR("AXWindowDeminiaturized")

// new drawer, sheet, and help tag notifications
#define kAXDrawerCreatedNotification			CFSTR("AXDrawerCreated")
#define kAXSheetCreatedNotification			CFSTR("AXSheetCreated")
#define kAXHelpTagCreatedNotification			CFSTR("AXHelpTagCreated")

// element notifications
#define kAXValueChangedNotification			CFSTR("AXValueChanged")
#define kAXUIElementDestroyedNotification		CFSTR("AXUIElementDestroyed")

// menu notifications
#define kAXMenuOpenedNotification			CFSTR("AXMenuOpened")
#define kAXMenuClosedNotification			CFSTR("AXMenuClosed")
#define kAXMenuItemSelectedNotification			CFSTR("AXMenuItemSelected")

// table/outline notifications
#define kAXRowCountChangedNotification			CFSTR("AXRowCountChanged")

// other notifications
#define kAXSelectedChildrenChangedNotification		CFSTR("AXSelectedChildrenChanged")
#define kAXResizedNotification				CFSTR("AXResized")
#define kAXMovedNotification				CFSTR("AXMoved")
#define kAXCreatedNotification				CFSTR("AXCreated")
#define kAXSelectedRowsChangedNotification	CFSTR("AXSelectedRowsChanged")
#define kAXSelectedColumnsChangedNotification	CFSTR("AXSelectedColumnsChanged")
#define kAXSelectedTextChangedNotification	CFSTR("AXSelectedTextChanged")


#endif // __AXNOTIFICATIONCONSTANTS__
