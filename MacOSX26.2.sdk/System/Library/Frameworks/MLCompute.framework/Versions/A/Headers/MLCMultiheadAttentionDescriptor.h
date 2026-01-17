//
//  MLCMultiheadAttentionDescriptor.h
//  MLCompute
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <MLCompute/MLCDefines.h>
#import <MLCompute/MLCTypes.h>

NS_ASSUME_NONNULL_BEGIN

/*! @class      MLCMultiheadAttentionDescriptor
    @discussion The MLCMultiheadAttentionDescriptor specifies a Multi-Head Attention descriptor
 */
MLCOMPUTE_AVAILABLE_STARTING_BUT_DEPRECATED_MACOS14(11.0, 14.0, 14.0)
@interface MLCMultiheadAttentionDescriptor : NSObject <NSCopying>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/*! @brief model or embedding dimension */
@property (readonly, nonatomic) NSUInteger modelDimension;

/*! @brief total dimension of key space, Default = modelDimension */
@property (readonly, nonatomic) NSUInteger keyDimension;

/*! @brief total dimension of value space, Default = modelDimension */
@property (readonly, nonatomic) NSUInteger valueDimension;

/*! @brief number of parallel attention heads */
@property (readonly, nonatomic) NSUInteger headCount;

/*! @brief a droupout layer applied to the output projection weights. Default = 0.0 */
@property (readonly, nonatomic) float dropout;

/*! @brief if true, bias is used for query/key/value/output projections. Default = true */
@property (readonly, nonatomic) BOOL hasBiases;

/*! @brief if true, an array of biases is added to key and value respectively. Default = false */
@property (readonly, nonatomic) BOOL hasAttentionBiases;

/*! @brief if true, a row of zeroes is added to projected key and value. Default = false */
@property (readonly, nonatomic) BOOL addsZeroAttention;

/*! @abstract   A multi-head attention layer descriptor
    @param      modelDimension  total dimension of model space
    @param      keyDimension  total dimension of key space. Default = modelDimension
    @param      valueDimension  total dimension of value space. Default = modelDimension
    @param      headCount  number of parallel attention heads
    @param      dropout optional, a dropout layer applied to the output projection weights. Default = 0.0f
    @param      hasBiases  if true, bias will be added to query/key/value/output projections. Default = YES
    @param      hasAttentionBiases  if true, an array of biases is added to key and value respectively. Default = NO
    @param      addsZeroAttention  if true, a row of zeroes is added to projected key and value. Default = NO
    @return     A new MultiheadAttention layer descriptor
 */
+ (instancetype _Nullable)descriptorWithModelDimension:(NSUInteger)modelDimension
                                          keyDimension:(NSUInteger)keyDimension
                                        valueDimension:(NSUInteger)valueDimension
                                             headCount:(NSUInteger)headCount
                                               dropout:(float)dropout
                                             hasBiases:(BOOL)hasBiases
                                    hasAttentionBiases:(BOOL)hasAttentionBiases
                                     addsZeroAttention:(BOOL)addsZeroAttention;

/*! @abstract   A multi-head attention layer descriptor
    @param      modelDimension  total dimension of model space
    @param      headCount  number of parallel attention heads
    @return     A valid MultiheadAttention layer descriptor
*/
+ (instancetype)descriptorWithModelDimension:(NSUInteger)modelDimension
                                   headCount:(NSUInteger)headCount;

@end

NS_ASSUME_NONNULL_END
