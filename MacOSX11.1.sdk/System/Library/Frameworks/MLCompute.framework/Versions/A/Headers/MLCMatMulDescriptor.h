//
//  MLCMatMulDescriptor.h
//  MLCompute
//
//  Copyright © 2020 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <MLCompute/MLCTypes.h>

NS_ASSUME_NONNULL_BEGIN

/*! @class      MLCMatMulDescriptor
    @discussion The MLCMatMulDescriptor specifies a batched matrix multiplication descriptor
 */
MLCOMPUTE_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MLCMatMulDescriptor : NSObject <NSCopying>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/*! @brief a scalar to scale the result in C=alpha x X x Y. Default = 1.0 */
@property (readonly, nonatomic) float alpha;

/*! @brief if true, transposes the last two dimensions of X. Default = False */
@property (readonly, nonatomic) BOOL transposesX;

/*! @brief if true, transposes the last two dimensions of Y. Default = False */
@property (readonly, nonatomic) BOOL transposesY;


/*! @abstract   A matrix multiplication layer descriptor
 *  @param      alpha  a scalar to scale the left hand side, C = alpha x X x Y
 *  @param      transposesX  if true, transposes the last two dimensions of X
 *  @param      transposesY  if true, transposes the last two dimensions of Y
 *  @return     A new matrix multiplication layer descriptor
 */
+ (instancetype _Nullable)descriptorWithAlpha:(float)alpha
                                  transposesX:(BOOL)transposesX
                                  transposesY:(BOOL)transposesY;

/*! @property   descriptor
 *  @abstract   A matrix multiplication layer descriptor
 */
+ (instancetype)descriptor
    NS_SWIFT_NAME(init());

@end

NS_ASSUME_NONNULL_END
