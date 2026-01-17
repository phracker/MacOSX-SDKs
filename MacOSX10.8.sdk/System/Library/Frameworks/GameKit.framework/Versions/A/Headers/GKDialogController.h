//
//  GKDialogController.h
//  GameKit
//
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol GKViewController
@end

@interface GKDialogController : NSResponder {
	id _internal1, _internal2, _internal3, _internal4;
}
@property(assign, NS_NONATOMIC_IOSONLY) IBOutlet NSWindow* parentWindow;
-(BOOL)presentViewController:(NSViewController<GKViewController>*)viewController;
-(IBAction)dismiss:(id)sender;
@end

@interface GKDialogController (SharedDialogController)
+(GKDialogController*)sharedDialogController;
@end
