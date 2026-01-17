//
//  MLCUpsampleLayer.h
//  MLCompute
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <MLCompute/MLCDefines.h>
#import <MLCompute/MLCTypes.h>
#import <MLCompute/MLCLayer.h>

@class MLCDevice;
@class MLCTensor;

NS_ASSUME_NONNULL_BEGIN

/*! @class      MLCUpsampleLayer
    @abstract   An upsample layer
 */
MLCOMPUTE_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MLCUpsampleLayer : MLCLayer

/*! @property   shape
    @abstract   A NSArray<NSNumber *> representing just the width if number of entries in shape array is 1 or
                the height followed by width of result tensor if the number of entries in shape array is 2.
 */
@property (readonly, nonatomic, copy) NSArray<NSNumber *> *shape NS_REFINED_FOR_SWIFT;

/*! @property   sampleMode
    @abstract   The sampling mode to use when performing the upsample.
 */
@property (readonly, nonatomic) MLCSampleMode sampleMode;

/*! @property   alignsCorners
    @abstract   A boolean that specifies whether the corner pixels of the source and result tensors are aligned.
    @discussion If True, the corner pixels of the source and result tensors are aligned, and thus preserving the values at those pixels.
                This only has effect when mode is 'bilinear'. Default is NO.
 */
@property (readonly, nonatomic) BOOL alignsCorners;

/*! @abstract   Create an upsample layer
    @param      shape                   A NSArray<NSNumber *> representing the dimensions of the result tensor
    @return     A new upsample layer.
*/
+ (instancetype _Nullable)layerWithShape:(NSArray<NSNumber *> *)shape
    NS_REFINED_FOR_SWIFT;

/*! @abstract   Create an upsample layer
 *  @param      shape                   A NSArray<NSNumber *> representing the dimensions of the result tensor
 *  @param      sampleMode        The upsampling algorithm to use.  Default is nearest.
 *  @param      alignsCorners    Whether the corner pixels of the input and output tensors are aligned or not.
 *  @return     A new upsample layer.
 */
+ (instancetype _Nullable)layerWithShape:(NSArray<NSNumber *> *)shape
                              sampleMode:(MLCSampleMode)sampleMode
                           alignsCorners:(BOOL)alignsCorners
    NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END
