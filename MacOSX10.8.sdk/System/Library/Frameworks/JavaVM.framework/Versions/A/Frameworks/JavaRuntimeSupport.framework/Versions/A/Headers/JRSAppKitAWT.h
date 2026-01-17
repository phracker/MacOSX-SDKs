//
//  JRSAppKitAWT.h
//  Copyright 2010-2011 Apple Inc. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <JavaRuntimeSupport/JRSDefines.h>

#define JRSAppNameKey @"JRSAppNameKey"
#define JRSAppIsCommandLineKey @"JRSAppIsCommandLineKey"
#define JRSAppIsUIElementKey @"JRSAppIsUIElementKey"
#define JRSAppIsBackgroundOnlyKey @"JRSAppIsBackgroundOnlyKey"

@interface JRSAppKitAWT : NSObject { }
+ (id <NSApplicationDelegate>)awtAppDelegate;
+ (void) registerAWTAppWithOptions:(NSDictionary *)options;
+ (BOOL) markAppIsDaemon;
@end
