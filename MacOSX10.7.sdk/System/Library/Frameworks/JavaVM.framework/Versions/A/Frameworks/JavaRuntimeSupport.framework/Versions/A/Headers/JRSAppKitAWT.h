//
//  JRSAppKitAWT.h
//  Copyright 2010 Apple Inc. All rights reserved.
//

#import <Cocoa/Cocoa.h>


@interface JRSAppKitAWT : NSObject { }

#if MAC_OS_X_VERSION_MAX_ALLOWED < (MAC_OS_X_VERSION_10_5 + 10) // 10.6
+ (id)awtAppDelegate;
#else
+ (id <NSApplicationDelegate>)awtAppDelegate;
#endif

@end
