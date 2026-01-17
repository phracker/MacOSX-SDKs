/*
        NSInterfaceStyle.h
        Application Kit
        Copyright (c) 1995-2015, Apple Inc.
        All rights reserved.
*/

#import <AppKit/NSResponder.h>
#import <AppKit/AppKitDefines.h>

enum {
    NSNoInterfaceStyle = 0,    // Default value for a window's interfaceStyle
    NSNextStepInterfaceStyle = 1, 
    NSWindows95InterfaceStyle = 2,
    NSMacintoshInterfaceStyle = 3
} NS_ENUM_DEPRECATED_MAC(10_0, 10_8);
typedef NSUInteger NSInterfaceStyle NS_DEPRECATED_MAC(10_0, 10_8); // Deprecated in 10.8

APPKIT_EXTERN NSInterfaceStyle NSInterfaceStyleForKey(NSString *key, NSResponder *responder) NS_DEPRECATED_MAC(10_0, 10_8);
    // Responders can use this function to parameterize their drawing and behavior.  If the responder has specific defaults to control various aspects of its interface individually, the keys for those special settings can be passed in, otherwise pass nil to get the global setting.  The responder should always be passed, but in situations where a responder is not available, pass nil.

@interface NSResponder (NSInterfaceStyle)
- (NSInterfaceStyle)interfaceStyle NS_DEPRECATED_MAC(10_0, 10_8);
- (void)setInterfaceStyle:(NSInterfaceStyle)interfaceStyle NS_DEPRECATED_MAC(10_0, 10_8);
// A responder's style (if set) overrides all other settings.  Responders which need to redraw or do any other work when the interface style changes should override this to do it.  Always call super.
@end

// Default strings

APPKIT_EXTERN NSString *NSInterfaceStyleDefault NS_DEPRECATED_MAC(10_0, 10_8);
