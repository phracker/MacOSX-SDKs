//
//  JRSWindow.h
//  Copyright 2012 Apple Inc. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <JavaRuntimeSupport/JRSDefines.h>

JRS_BEGIN_DECLS

@interface NSWindow (JavaRuntimeSupport)
- (void)javaAddToOrderingGroup:(NSWindow *)ownedWindow;
- (void)javaRemoveFromOrderingGroup:(NSWindow *)ownedWindow;
@end

JRS_END_DECLS
