//
//  MLCLSTMDescriptor.h
//  MLCompute
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <MLCompute/MLCDefines.h>
#import <MLCompute/MLCTypes.h>

NS_ASSUME_NONNULL_BEGIN

/*! @class      MLCLSTMDescriptor
    @discussion The MLCLSTMDescriptor specifies a LSTM descriptor
 */
MLCOMPUTE_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MLCLSTMDescriptor : NSObject <NSCopying>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/*! @property   inputSize
    @abstract   The number of expected feature channels in the input
 */
@property (readonly, nonatomic) NSUInteger inputSize;

/*! @property   hiddenSize
    @abstract   The number of feature channels in the hidden state
 */
@property (readonly, nonatomic) NSUInteger hiddenSize;

/*! @property   layerCount
    @abstract   The number of recurrent layers.  Default is 1.
 */
@property (readonly, nonatomic) NSUInteger layerCount;

/*! @property   usesBiases
    @abstract   If NO, the layer does not use bias terms.  Default is YES.
 */
@property (readonly, nonatomic) BOOL usesBiases;

/*! @property   batchFirst
    @abstract   if YES, the input and output will be in shape [batch, feature, 1, time steps], else it will be in shape [time steps, batch, feature].
                Note that [time steps, batch, feature] will be the more efficient implementation. Default is YES.
 */
@property (readonly, nonatomic) BOOL batchFirst;

/*! @property   isBidirectional
    @abstract   If YES, becomes a bidirectional LSTM.  Default is NO.
 */
@property (readonly, nonatomic) BOOL isBidirectional;

/*! @property   returnsSequences
    @abstract   if YES return output for all sequences else return output only for the last sequences. Default: YES
 */
@property (readonly, nonatomic) BOOL returnsSequences;

/*! @property   dropout
    @abstract   If non-zero, intrdouces a dropout layer on the outputs of each LSTM layer
                except the last layer, with dropout probablity equal to dropout.  Default is 0.0.
 */
@property (readonly, nonatomic) float dropout;

/*! @property   resultMode
    @abstract   MLCLSTMResultModeOutput returns output data. MLCLSTMResultModeOutputAndStates returns
                output data, last hidden state h_n, and last cell state c_n. Default MLCLSTMResultModeOutput.
 */
@property (readonly, nonatomic) MLCLSTMResultMode resultMode;



/*! @abstract   Creates a LSTM descriptor with batchFirst = YES
    @param      inputSize The number of expected features in the input
    @param      hiddenSize The number of features in the hidden state
    @param      layerCount Number of recurrent layers
    @return     A valid MLCLSTMDescriptor object or nil, if failure.
 */
+ (instancetype)descriptorWithInputSize:(NSUInteger)inputSize
                             hiddenSize:(NSUInteger)hiddenSize
                             layerCount:(NSUInteger)layerCount;

/*! @abstract   Creates a LSTM descriptor descriptor with batchFirst = YES
 @param      inputSize The number of expected features in the input
 @param      hiddenSize The number of features in the hidden state
 @param      layerCount Number of recurrent layers
 @param      usesBiases  If NO, the layer does not use bias weights.  Default: YES
 @param      isBidirectional  If YES, becomes a bi-directional LSTM.  Default: NO
 @param      dropout  If non-zero, introduces a dropout layer on the outputs of each LSTM layer except the last layer
 with dropout probability equal to dropout.
 @return     A valid MLCLSTMDescriptor object or nil, if failure.
 */
+ (instancetype)descriptorWithInputSize:(NSUInteger)inputSize
                             hiddenSize:(NSUInteger)hiddenSize
                             layerCount:(NSUInteger)layerCount
                             usesBiases:(BOOL)usesBiases
                        isBidirectional:(BOOL)isBidirectional
                                dropout:(float)dropout;

+ (instancetype)descriptorWithInputSize:(NSUInteger)inputSize
                             hiddenSize:(NSUInteger)hiddenSize
                             layerCount:(NSUInteger)layerCount
                             usesBiases:(BOOL)usesBiases
                             batchFirst:(BOOL)batchFirst
                        isBidirectional:(BOOL)isBidirectional
                                dropout:(float)dropout;

+ (instancetype)descriptorWithInputSize:(NSUInteger)inputSize
                             hiddenSize:(NSUInteger)hiddenSize
                             layerCount:(NSUInteger)layerCount
                             usesBiases:(BOOL)usesBiases
                             batchFirst:(BOOL)batchFirst
                        isBidirectional:(BOOL)isBidirectional
                       returnsSequences:(BOOL)returnsSequences
                                dropout:(float)dropout;

/*! @abstract   Creates a LSTM descriptor.
 @param      inputSize The number of expected features in the input
 @param      hiddenSize The number of features in the hidden state
 @param      layerCount Number of recurrent layers
 @param      usesBiases  If NO, the layer does not use bias weights.  Default: YES
 @param      batchFirst if YES, the input and output will be in shape [batch, feature, 1, time steps], else it will be in shape [time steps, batch, feature].
 Note that [time steps, batch, feature] will be the more efficient implementation. Default is YES.
 @param      isBidirectional  If YES, becomes a bi-directional LSTM.  Default: NO
 @param      returnsSequences if YES return output for all sequences else return output only for the last sequences. Default: YES
 @param      dropout  If non-zero, introduces a dropout layer on the outputs of each LSTM layer except the last layer
 with dropout probability equal to dropout.
 @param      resultMode expected result tensors. MLCLSTMResultModeOutput returns output data. MLCLSTMResultModeOutputAndStates returns
             output data, last hidden state h_n, and last cell state c_n. Default: MLCLSTMResultModeOutput.
 @return     A valid MLCLSTMDescriptor object or nil, if failure.
 */
+ (instancetype)descriptorWithInputSize:(NSUInteger)inputSize
                             hiddenSize:(NSUInteger)hiddenSize
                             layerCount:(NSUInteger)layerCount
                             usesBiases:(BOOL)usesBiases
                             batchFirst:(BOOL)batchFirst
                        isBidirectional:(BOOL)isBidirectional
                       returnsSequences:(BOOL)returnsSequences
                                dropout:(float)dropout
                             resultMode:(MLCLSTMResultMode)resultMode;

@end

NS_ASSUME_NONNULL_END
