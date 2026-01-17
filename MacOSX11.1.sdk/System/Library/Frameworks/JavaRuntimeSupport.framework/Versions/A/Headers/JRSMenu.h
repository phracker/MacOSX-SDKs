//
//  JRSMenu.h
//  Copyright 2011 Apple Inc. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <JavaRuntimeSupport/JRSDefines.h>

JRS_BEGIN_DECLS

JRS_EXPORT extern NSString * const JRSMenuDidReuseItemNotification JRS_DEPRECATED_2020;

JRS_EXPORT
@protocol JRSMenuDelegate <NSObject>
@optional
- (void) handleJavaMouseEvent:(NSEvent *)event;
- (void) handleJavaMenuItemTargetedAtIndex:(NSUInteger)menuIndex rect:(NSRect)rect;
@end

@interface NSMenu(JavaRuntimeSupport)
+ (NSMenu *) javaMenuWithTitle:(NSString *)title;
- (void) setJavaMenuDelegate:(id <JRSMenuDelegate>)delegate;
- (BOOL) isJavaMenu;
@end

JRS_END_DECLS
