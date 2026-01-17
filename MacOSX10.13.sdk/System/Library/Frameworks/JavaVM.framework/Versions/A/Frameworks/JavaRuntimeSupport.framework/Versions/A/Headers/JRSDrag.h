//
//  JRSDrag.h
//  Copyright 2011 Apple Inc. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface JRSDrag : NSObject
+ (NSDragOperation) currentAllowableActions;
+ (NSUInteger) currentModifiers;
@end
