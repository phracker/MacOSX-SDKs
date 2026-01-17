// Copyright © Apple Inc. All rights reserved.

#import <TargetConditionals.h>

#if TARGET_OS_OSX
#ifndef GKDialogController_h
#define GKDialogController_h

#import <Cocoa/Cocoa.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(10.8)) API_UNAVAILABLE(ios, tvos, visionos, watchos)
@protocol GKViewController
@end

API_AVAILABLE(macos(10.8)) API_UNAVAILABLE(ios, tvos, visionos, watchos)
@interface GKDialogController : NSResponder

@property (weak, nullable) IBOutlet NSWindow *parentWindow;

- (BOOL)presentViewController:(NSViewController<GKViewController>  *)viewController;
- (IBAction)dismiss:(id)sender;

@end

API_AVAILABLE(macos(10.8)) API_UNAVAILABLE(ios, tvos, visionos, watchos)
@interface GKDialogController (SharedDialogController)
+ (GKDialogController *)sharedDialogController;
@end

NS_ASSUME_NONNULL_END

#endif
#endif
