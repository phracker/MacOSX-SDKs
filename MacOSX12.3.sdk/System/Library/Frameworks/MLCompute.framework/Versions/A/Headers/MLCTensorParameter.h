//
//  MLCTensorParameter.h
//  MLCompute
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <MLCompute/MLCDefines.h>
#import <MLCompute/MLCTypes.h>

@class MLCTensor;

NS_ASSUME_NONNULL_BEGIN

/*! @class      MLCTensorParameter
    @discussion A tensor parameter object.  This is used to describe input tensors that are updated by the optimizer during training.
 */
MLCOMPUTE_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MLCTensorParameter : NSObject

/*! @property   tensor
    @abstract   The underlying tensor
 */
@property (readonly, nonatomic, retain) MLCTensor *tensor;

/*! @property   isUpdatable
    @abstract   Specifies whether this tensor parameter is updatable
 */
@property (readwrite, nonatomic) BOOL isUpdatable;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/*! @abstract   Create a tensor parameter
    @param      tensor            The unedrlying tensor
    @return     A new tensor parameter object
 */
+ (instancetype)parameterWithTensor:(MLCTensor *)tensor;

/*! @abstract   Create a tensor parameter
    @param      tensor            The unedrlying tensor
    @param      optimizerData   The optimizer data needed for this input tensor
    @return     A new tensor parameter object
 */
+ (instancetype)parameterWithTensor:(MLCTensor *)tensor
                      optimizerData:(NSArray<MLCTensorData *> * _Nullable)optimizerData;
@end

NS_ASSUME_NONNULL_END


