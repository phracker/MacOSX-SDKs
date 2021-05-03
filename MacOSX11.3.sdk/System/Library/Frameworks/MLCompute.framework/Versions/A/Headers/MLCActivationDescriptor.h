//
//  MLCActivationDescriptor.h
//  MLCompute
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <MLCompute/MLCDefines.h>
#import <MLCompute/MLCTypes.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class      MLCActivationDescriptor
 @discussion The MLCActivationDescriptor specifies a neuron descriptor.
 */
MLCOMPUTE_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MLCActivationDescriptor : NSObject <NSCopying>

/*! @property   activationType
    @abstract   The type of activation function
 */
@property (readonly, nonatomic) MLCActivationType activationType;

/*! @property   a
    @abstract   Parameter to the activation function
 */
@property (readonly, nonatomic) float a;

/*! @property   b
    @abstract   Parameter to the activation function
 */
@property (readonly, nonatomic) float b;

/*! @property   c
    @abstract   Parameter to the activation function
 */
@property (readonly, nonatomic) float c;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/*! @abstract  Create a MLCActivationDescriptor object
    @param     activationType  A type of activation function.
    @return    A new neuron descriptor or nil if failure
 */
+ (instancetype _Nullable)descriptorWithType:(MLCActivationType)activationType;

/*! @abstract  Create a MLCActivationDescriptor object
    @param     activationType  A type of activation function.
    @param     a                      Parameter "a".
    @return    A new neuron descriptor or nil if failure
 */
+ (instancetype _Nullable)descriptorWithType:(MLCActivationType)activationType
                                           a:(float)a;

/*! @abstract  Create a MLCActivationDescriptor object
    @param     activationType  A type of activation function.
    @param     a                      Parameter "a".
    @param     b                      Parameter "b".
    @return    A new neuron descriptor or nil if failure
 */
+ (instancetype _Nullable)descriptorWithType:(MLCActivationType)activationType
                                           a:(float)a
                                           b:(float)b;


/*! @abstract  Create a MLCActivationDescriptor object
    @param     activationType  A type of activation function.
    @param     a                      Parameter "a".
    @param     b                      Parameter "b".
    @param     c                      Parameter "c".
    @return    A new neuron descriptor or nil if failure
 */
+ (instancetype _Nullable)descriptorWithType:(MLCActivationType)activationType
                                           a:(float)a
                                           b:(float)b
                                           c:(float)c;

@end

NS_ASSUME_NONNULL_END
