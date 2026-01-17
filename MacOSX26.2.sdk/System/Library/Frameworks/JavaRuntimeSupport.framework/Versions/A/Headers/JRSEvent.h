//
//  JRSEvent.h
//  Copyright 2011 Apple Inc. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <JavaRuntimeSupport/JRSDefines.h>

JRS_BEGIN_DECLS

@interface NSEvent (JavaRuntimeSupport)
- (unichar) deadKeyCharacter;
- (BOOL) willBeHandledByComplexInputMethod;
@end

JRS_END_DECLS
