//
//  JRSSymbolicator.h
//  Copyright 2011 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <JavaRuntimeSupport/JRSDefines.h>

JRS_BEGIN_DECLS

JRS_EXPORT
@interface JRSSymbolicator : NSObject
+ (JRSSymbolicator *)symbolicatorForPid:(pid_t)pid;
- (uint64_t)addressForSymbol:(NSString *)symbolName;
@end

JRS_END_DECLS
