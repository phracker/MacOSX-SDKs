//
//  CAInterDeviceAudioViewController.h
//
//  Created by Michael Hopkins on 12/8/14.
//  Copyright (c) 2014 Apple. All rights reserved.
//

#if __OBJC2__

#import <Cocoa/Cocoa.h>

/*!
 @class CAInterDeviceAudioViewController
 @abstract  A view controller object that manages a view displaying iOS devices that are connected to the Mac and support inter-device audio. The user can select one of those peripherals and connect it to their mac. This class is only available in 64-bit runtimes.
 
 @discussion To use this class, create an instance of the CAInterDeviceAudioController, get the view and add it as a subview of a NSWindow.
 */
@interface CAInterDeviceAudioViewController : NSViewController
@end
#endif