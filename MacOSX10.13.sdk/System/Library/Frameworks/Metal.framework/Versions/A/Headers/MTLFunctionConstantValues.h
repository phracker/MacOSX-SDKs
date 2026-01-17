//
//  MTLFunctionConstantValues.h
//  Metal
//
//  Copyright (c) 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Metal/MTLDefines.h>
#import <Metal/MTLArgument.h>


NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE(10_12, 10_0)
@interface MTLFunctionConstantValues : NSObject <NSCopying>

// using indices
- (void)setConstantValue:(const void *)value type:(MTLDataType)type atIndex:(NSUInteger)index;
- (void)setConstantValues:(const void *)values type:(MTLDataType)type withRange:(NSRange)range;

// using names
- (void)setConstantValue:(const void *)value type:(MTLDataType)type withName:(NSString *)name;

// delete all the constants
- (void)reset;

@end

NS_ASSUME_NONNULL_END
