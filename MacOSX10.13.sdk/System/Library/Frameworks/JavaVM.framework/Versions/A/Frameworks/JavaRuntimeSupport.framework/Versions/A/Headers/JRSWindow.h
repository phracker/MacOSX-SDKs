//
//  JRSWindow.h
//  Copyright 2012 Apple Inc. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface NSWindow (JavaRuntimeSupport)
- (void)javaAddToOrderingGroup:(NSWindow *)ownedWindow;
- (void)javaRemoveFromOrderingGroup:(NSWindow *)ownedWindow;
@end
