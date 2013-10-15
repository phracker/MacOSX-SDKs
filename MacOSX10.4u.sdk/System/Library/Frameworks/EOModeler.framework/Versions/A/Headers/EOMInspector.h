// EOMInspector.h
// Copyright (c) 1995, 1998 Apple Computer, Inc.
// All rights reserved.


#import <EOInterface/EOInterface.h>

@interface EOMInspector:NSObject {
    IBOutlet NSView *view;
    IBOutlet NSWindow *window;
    NSImage *image;            // required, by convention same as class name
    NSImage *hilightedImage;   // computed
}

+ (NSArray *)allRegisteredInspectors;

+ (NSArray *)allInspectorsThatCanInspectObject:(id)selObj;
    // calls canInspectObject: on all registered inspectors
    // and returns result

+ (EOMInspector *)sharedInspector;

+ (BOOL)usesControlActionForValidation;

   // EOMInspector will currently fire NSTextField actions for subclasses
   // which fail to leverage delegate methods for validation.  Overloading
   // this method to return NO turns this mechanism off for instances of
   // the receiver.

- init;
    // designated initializer

- (NSString *)displayName;
    // defaults to the the window name

- (NSImage *)image;

- (NSImage *)hilightedImage;

- (float)displayOrder;
    // subclasses override to specify where they should appear in
    // inspector list

- (BOOL)canInspectObject:(id)selObj;
    // subclasses override to determine whether they can inspect the current
    // object.  E.g.: return [selObj isKindOfClass:[EOAttribute class]]

- (void)load;
    // should load.  default implementation loads nib file with
    // name matching class name.  Subclasses should do other initialization
    // here.

- (void) unload;
    // sent to inspector before it is unloaded and replaced by another

- (void)prepareForDisplay;
    // is view==nil, calls load  

- (NSView *)view;
    // defined for all Inspector subclasses
    // used by InspectorController

- (void)refresh;
    // must be redefined by subclass
    // default is to do nothing

- (NSArray *)selectedObjects;
    // Convenience to facilitate implementation of an inspector

- (id)selectedObject;
    // Convenience to facilitate implementation of an inspector

- (BOOL)isAdvanced;
    // advanced inspectors are displayed only if the user checks
    // "Display Advanced Options"  Default is NO.

+ (NSArray *)selectionBeingValidated;

@end










