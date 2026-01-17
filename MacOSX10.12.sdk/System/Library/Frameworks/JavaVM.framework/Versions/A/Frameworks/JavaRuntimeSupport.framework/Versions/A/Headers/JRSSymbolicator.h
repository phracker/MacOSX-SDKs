//
//  JRSSymbolicator.h
//  Copyright 2011 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface JRSSymbolicator : NSObject
+ (JRSSymbolicator *)symbolicatorForPid:(pid_t)pid;
- (uint64_t)addressForSymbol:(NSString *)symbolName;
@end
