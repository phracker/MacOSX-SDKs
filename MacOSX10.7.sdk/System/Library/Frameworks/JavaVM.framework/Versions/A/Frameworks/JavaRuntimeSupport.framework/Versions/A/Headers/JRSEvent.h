//
//  JRSEvent.h
//  Copyright 2011 Apple Inc. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface NSEvent (JavaRuntimeSupport)
- (unichar) deadKeyCharacter;
- (BOOL) willBeHandledByComplexInputMethod;
@end
