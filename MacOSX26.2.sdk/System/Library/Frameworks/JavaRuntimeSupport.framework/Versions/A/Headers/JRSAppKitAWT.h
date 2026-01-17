//
//  JRSAppKitAWT.h
//  Copyright 2010-2011 Apple Inc. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <JavaRuntimeSupport/JRSDefines.h>

JRS_BEGIN_DECLS

#define JRSAppNameKey @"JRSAppNameKey"
#define JRSAppIsCommandLineKey @"JRSAppIsCommandLineKey"
#define JRSAppIsUIElementKey @"JRSAppIsUIElementKey"
#define JRSAppIsBackgroundOnlyKey @"JRSAppIsBackgroundOnlyKey"

JRS_EXPORT
@interface JRSAppKitAWT : NSObject { }
+ (id <NSApplicationDelegate>)awtAppDelegate;
+ (void) registerAWTAppWithOptions:(NSDictionary *)options;
+ (BOOL) markAppIsDaemon;
@end

JRS_END_DECLS
