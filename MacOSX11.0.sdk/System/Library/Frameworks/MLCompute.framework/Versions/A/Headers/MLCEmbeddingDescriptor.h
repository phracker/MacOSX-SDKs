//
//  MLCEmbeddingDescriptor.h
//  MLCompute
//
//  Copyright © 2020 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <MLCompute/MLCDefines.h>
#import <MLCompute/MLCTypes.h>

NS_ASSUME_NONNULL_BEGIN

/*! @class      MLCEmbeddingDescriptor
    @discussion The MLCEmbeddingDescriptor specifies an embedding layer descriptor
 */
MLCOMPUTE_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MLCEmbeddingDescriptor : NSObject <NSCopying>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/*! @property   embeddingCount
 *  @abstract   The size of the dictionary
 */
@property (readonly, nonatomic) NSNumber *embeddingCount NS_REFINED_FOR_SWIFT;

/*! @property   embeddingDimension
 *  @abstract   The dimension of embedding vectors
 */
@property (readonly, nonatomic) NSNumber *embeddingDimension NS_REFINED_FOR_SWIFT;

/*! @property   paddingIndex
 *  @abstract   If set, the embedding vector at paddingIndex is initialized with zero and will not be updated in gradient pass, Default=nil
 */
@property (readonly, nonatomic) NSNumber * _Nullable paddingIndex NS_REFINED_FOR_SWIFT;

/*! @property   maximumNorm
 *  @abstract   A float, if set, in the forward pass only, the selected embedding vectors will be re-normalized to have an Lp norm of less than maximumNorm in the dictionary, Default=nil
 */
@property (readonly, nonatomic) NSNumber * _Nullable maximumNorm NS_REFINED_FOR_SWIFT;

/*! @property   pNorm
 *  @abstract   A float, the p of the Lp norm, can be set to infinity norm by [NSNumber numberWithFloat:INFINITY]. Default=2.0
 */
@property (readonly, nonatomic) NSNumber * _Nullable pNorm NS_REFINED_FOR_SWIFT;

/*! @property   scalesGradientByFrequency
 *  @abstract   If set, the gradients are scaled by the inverse of the frequency of the words in batch before the weight update. Default=NO
 */
@property (readonly, nonatomic) BOOL scalesGradientByFrequency;

+ (instancetype _Nullable)descriptorWithEmbeddingCount:(NSNumber *)embeddingCount
                                    embeddingDimension:(NSNumber *)embeddingDimension
    NS_REFINED_FOR_SWIFT;

+ (instancetype _Nullable)descriptorWithEmbeddingCount:(NSNumber *)embeddingCount
                                    embeddingDimension:(NSNumber *)embeddingDimension
                                          paddingIndex:(NSNumber * _Nullable)paddingIndex
                                           maximumNorm:(NSNumber * _Nullable)maximumNorm
                                                 pNorm:(NSNumber * _Nullable)pNorm
                             scalesGradientByFrequency:(BOOL)scalesGradientByFrequency
    NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END

