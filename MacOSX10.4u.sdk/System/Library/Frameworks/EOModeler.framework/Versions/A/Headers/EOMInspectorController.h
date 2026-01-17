// InspectorController.h
// Copyright (c) 1995, 1998 Apple Computer, Inc.
// All rights reserved.


#import <EOInterface/EOInterface.h>
@class EOMInspector;

// Inspector observes EOMSelectionChangedNotification notifications to refresh its display

@interface EOMInspectorController:NSObject {
    NSWindow		*window;
    NSScrollView	*scrollView;
    NSMapTable		*inspSpecsConfigToBest;
    EOMInspector	*lastInspector;
}

+ (void)showInspector;
+ (EOMInspectorController *)sharedInstance;
    // returns shared instance of inspector object for receieving class

@end
