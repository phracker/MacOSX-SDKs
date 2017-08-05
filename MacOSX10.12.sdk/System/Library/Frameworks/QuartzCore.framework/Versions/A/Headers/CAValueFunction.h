/* CoreAnimation - CAValueFunction.h

   Copyright (c) 2008-2016, Apple Inc.
   All rights reserved. */

#import <QuartzCore/CABase.h>
#import <Foundation/NSObject.h>

NS_ASSUME_NONNULL_BEGIN

CA_CLASS_AVAILABLE (10.6, 3.0, 9.0, 2.0)
@interface CAValueFunction : NSObject <NSCoding>
{
@protected
  NSString *_string;
  void *_impl;
}

+ (nullable instancetype)functionWithName:(NSString *)name;

@property(readonly) NSString *name;

@end

/** Value function names. **/

/* The `rotateX', `rotateY', `rotateZ' functions take a single input
 * value in radians, and construct a 4x4 matrix representing the
 * corresponding rotation matrix. */

CA_EXTERN NSString * const kCAValueFunctionRotateX
    CA_AVAILABLE_STARTING (10.6, 3.0, 9.0, 2.0);
CA_EXTERN NSString * const kCAValueFunctionRotateY
    CA_AVAILABLE_STARTING (10.6, 3.0, 9.0, 2.0);
CA_EXTERN NSString * const kCAValueFunctionRotateZ
    CA_AVAILABLE_STARTING (10.6, 3.0, 9.0, 2.0);

/* The `scale' function takes three input values and constructs a
 * 4x4 matrix representing the corresponding scale matrix. */

CA_EXTERN NSString * const kCAValueFunctionScale
    CA_AVAILABLE_STARTING (10.6, 3.0, 9.0, 2.0);

/* The `scaleX', `scaleY', `scaleZ' functions take a single input value
 * and construct a 4x4 matrix representing the corresponding scaling
 * matrix. */

CA_EXTERN NSString * const kCAValueFunctionScaleX
    CA_AVAILABLE_STARTING (10.6, 3.0, 9.0, 2.0);
CA_EXTERN NSString * const kCAValueFunctionScaleY
    CA_AVAILABLE_STARTING (10.6, 3.0, 9.0, 2.0);
CA_EXTERN NSString * const kCAValueFunctionScaleZ
    CA_AVAILABLE_STARTING (10.6, 3.0, 9.0, 2.0);

/* The `translate' function takes three input values and constructs a
 * 4x4 matrix representing the corresponding scale matrix. */

CA_EXTERN NSString * const kCAValueFunctionTranslate
    CA_AVAILABLE_STARTING (10.6, 3.0, 9.0, 2.0);

/* The `translateX', `translateY', `translateZ' functions take a single
 * input value and construct a 4x4 matrix representing the corresponding
 * translation matrix. */

CA_EXTERN NSString * const kCAValueFunctionTranslateX
    CA_AVAILABLE_STARTING (10.6, 3.0, 9.0, 2.0);
CA_EXTERN NSString * const kCAValueFunctionTranslateY
    CA_AVAILABLE_STARTING (10.6, 3.0, 9.0, 2.0);
CA_EXTERN NSString * const kCAValueFunctionTranslateZ
    CA_AVAILABLE_STARTING (10.6, 3.0, 9.0, 2.0);

NS_ASSUME_NONNULL_END
