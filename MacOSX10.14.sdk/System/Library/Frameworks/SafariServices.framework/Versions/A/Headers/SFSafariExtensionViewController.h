//
//  SFSafariExtensionViewController.h
//  SafariServices
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <SafariServices/SFFoundation.h>

#if __OBJC2__

#import <AppKit/NSViewController.h>

SF_CLASS_AVAILABLE_MAC_SAFARI(10_0)
@interface SFSafariExtensionViewController : NSViewController
@end

#endif // __OBJC2__
