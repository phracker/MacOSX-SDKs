//
//  JRSDrag.h
//  Copyright 2011 Apple Inc. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <JavaRuntimeSupport/JRSDefines.h>

JRS_BEGIN_DECLS

JRS_EXPORT
@interface JRSDrag : NSObject
+ (NSDragOperation) currentAllowableActions;
+ (NSUInteger) currentModifiers;
@end

JRS_END_DECLS
