//
//  GKDialogController.h
//  GameKit
//
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//

#import <Cocoa/Cocoa.h>

NS_ASSUME_NONNULL_BEGIN

@protocol GKViewController
@end

@interface GKDialogController : NSResponder

@property (assign, nullable) IBOutlet NSWindow *parentWindow;

- (BOOL)presentViewController:(NSViewController<GKViewController>  *)viewController;
- (IBAction)dismiss:(id)sender;

@end

@interface GKDialogController (SharedDialogController)
+ (GKDialogController *)sharedDialogController;
@end

NS_ASSUME_NONNULL_END