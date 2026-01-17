//
//  GCEventViewController.h
//  GameController
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <TargetConditionals.h>

#import <Foundation/Foundation.h>

#if TARGET_OS_IPHONE
#import <UIKit/UIViewController.h>
#else
#import <AppKit/NSViewController.h>
#endif

/**
 A view controller subclass that allows fine grained control of the user interface system's handling
 of game controller events. Set an instance of this class as your root view controller if you intend
 to use GCController APIs for handling game controllers.
 */
#if TARGET_OS_IPHONE
API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0))
@interface GCEventViewController : UIViewController
#else
API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0))
@interface GCEventViewController : NSViewController
#endif

/**
 Controllers can be used to control the general UIKit user interface and for many views that is
 the default behavior. By using a controller event view controller you get fine grained control
 over whether the controller events go trough the UIEvent & UIResponder chain, or if they are
 decoupled from the UI and all incoming data is served via GCController.
 
 Defaults to NO - suppressing UIEvents from game controllers and presenting them via the GCController
 API whilst this controller's view or any of it's subviews are the first responders. If you are not
 using any UIView components or UIEvents in your application you should leave this as NO and process
 your game controller events via the normal GCController API.
 
 If set to YES the controller input will start flowing through UIEvent and the UIResponder
 chain will be used. This gives you fine grained control over the event handling of the
 controlled view and its subviews. You should stop using GCController instances and the corresponding
 profiles if you no longer need to read input from them.
 
 Note that unlike UIView.userInteractionEnabled this only controls the flow of game controller events.
 
 @see GCController
 @see UIView.userInteractionEnabled
 */
@property (nonatomic) BOOL controllerUserInteractionEnabled;

@end
