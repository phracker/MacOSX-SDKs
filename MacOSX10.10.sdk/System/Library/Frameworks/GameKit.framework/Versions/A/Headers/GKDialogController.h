//
//  GKDialogController.h
//  GameKit
//
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@protocol GKViewController
@end

@interface GKDialogController : NSResponder

@property (assign) IBOutlet NSWindow *parentWindow;

- (BOOL)presentViewController:(NSViewController<GKViewController> *)viewController;
- (IBAction)dismiss:(id)sender;

@end

@interface GKDialogController (SharedDialogController)
+ (GKDialogController *)sharedDialogController;
@end
