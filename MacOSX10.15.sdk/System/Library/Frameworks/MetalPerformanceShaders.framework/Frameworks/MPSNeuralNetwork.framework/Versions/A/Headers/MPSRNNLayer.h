//
//  MPSRNNLayer.h
//  MPS
//
//  Created by Teemu Rantalaiho on 12/13/16.
//  Copyright © 2016 Apple. All rights reserved.
//

#ifndef MPSRNNLayer_h
#define MPSRNNLayer_h


#include <MPSNeuralNetwork/MPSCNNConvolution.h>
#include <MPSMatrix/MPSMatrix.h>

#ifdef __cplusplus
extern "C" {
#endif


/*! @enum       MPSRNNSequenceDirection
 *  @abstract   Defines the direction in which a sequence of inputs is processed by a RNN Layer.
 *              @see MPSRNNImageInferenceLayer and @see MPSRNNMatrixInferenceLayer.
 */
#if defined(DOXYGEN)
typedef enum MPSRNNSequenceDirection
#else
typedef NS_ENUM(NSUInteger, MPSRNNSequenceDirection)
#endif
{
    /*! The input sequence is processed from index zero to array length minus one */
    MPSRNNSequenceDirectionForward    MPS_ENUM_AVAILABLE_STARTING( macos(10.13), ios(11.0), macCatalyst(13.0), tvos(11.0)) MPS_SWIFT_NAME(forward)  = 0,
    /*! The input sequence is processed from index array length minus one to zero */
    MPSRNNSequenceDirectionBackward  MPS_ENUM_AVAILABLE_STARTING( macos(10.13), ios(11.0), macCatalyst(13.0), tvos(11.0)),
}
#if defined(DOXYGEN)
MPSRNNSequenceDirection
#endif
;

/*! @enum       MPSRNNBidirectionalCombineMode
 *  @abstract   Defines the way in which two images or matrices are combined together, or if the results are to be kept separate.
 *              @see MPSRNNImageInferenceLayer and @see MPSRNNMatrixInferenceLayer.
 */
#if defined(DOXYGEN)
typedef enum MPSRNNBidirectionalCombineMode
#else
typedef NS_ENUM(NSUInteger, MPSRNNBidirectionalCombineMode)
#endif
{
    /*! The two sequences are kept separate */
    MPSRNNBidirectionalCombineModeNone    MPS_ENUM_AVAILABLE_STARTING( macos(10.13), ios(11.0), macCatalyst(13.0), tvos(11.0)) MPS_SWIFT_NAME(none)  = 0,
    /*! The two sequences are summed together to form a single output */
    MPSRNNBidirectionalCombineModeAdd  MPS_ENUM_AVAILABLE_STARTING( macos(10.13), ios(11.0), macCatalyst(13.0), tvos(11.0)),
    /*! The two sequences are concatenated together along the feature channels to form a single output */
    MPSRNNBidirectionalCombineModeConcatenate  MPS_ENUM_AVAILABLE_STARTING( macos(10.13), ios(11.0), macCatalyst(13.0), tvos(11.0)),
}
#if defined(DOXYGEN)
MPSRNNBidirectionalCombineMode
#endif
;




#pragma mark -
#pragma mark MPSRNNDescriptor

/*!
 *  @class      MPSRNNDescriptor
 *  @dependency This depends on Metal.framework
 *  @discussion The MPSRNNDescriptor specifies a Recursive neural network block/layer descriptor.
 *
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), macCatalyst(13.0), tvos(11.0))
@interface MPSRNNDescriptor : NSObject


/*! @property   inputFeatureChannels
 *  @abstract   The number of feature channels per pixel in the input image or number of rows in the input matrix.
 */
@property(readwrite, nonatomic) NSUInteger      inputFeatureChannels;

/*! @property   outputFeatureChannels
 *  @abstract   The number of feature channels per pixel in the destination image or number of rows in the destination matrix.
 */
@property(readwrite, nonatomic) NSUInteger      outputFeatureChannels;

/*! @property   useLayerInputUnitTransformMode
 *  @abstract   if YES then use identity transformation for all weights (W, Wr, Wi, Wf, Wo, Wc) affecting input x_j in this layer,
 *              even if said weights are specified as nil.
 *              For example 'W_ij * x_j' is replaced by 'x_j' in formulae defined in @ref MPSRNNSingleGateDescriptor. Defaults to NO.
 */
@property(readwrite, nonatomic) BOOL            useLayerInputUnitTransformMode;

/*! @property   useFloat32Weights
 *  @abstract   If YES, then @ref MPSRNNMatrixInferenceLayer uses 32-bit floating point numbers internally for weights when
 *              computing matrix transformations. If NO, then 16-bit, half precision floating point numbers are used.
 *              Currently @ref MPSRNNImageInferenceLayer ignores this property and the convolution operations always
 *              convert FP32 weights into FP16 for better performance.
 *              Defaults to NO.
 */
@property(readwrite, nonatomic) BOOL            useFloat32Weights;



/*! @property   layerSequenceDirection
 *  @abstract   When the layer specified with this descriptor is used to process a sequence of inputs
 *              by calling @see encodeBidirectionalSequenceToCommandBuffer then this parameter defines
 *              in which direction the sequence is processed. The operation of the layer is:
 *                  (yt, ht, ct) = f(xt,ht-1,ct-1) for MPSRNNSequenceDirectionForward
 *              and
 *                  (yt, ht, ct) = f(xt,ht+1,ct+1) for MPSRNNSequenceDirectionBackward, where
 *              xt is the output of the previous layer that encodes in the same direction as this layer,
 *              (or the input image or matrix if this is the first layer in stack with this direction).
 *              @see MPSRNNImageInferenceLayer and @see MPSRNNMatrixInferenceLayer.
 */
@property(readwrite, nonatomic) MPSRNNSequenceDirection      layerSequenceDirection;

@end    /* MPSRNNDescriptor */



#pragma mark -
#pragma mark MPSRNNSingleGateDescriptor

/*!
 *  @class      MPSRNNSingleGateDescriptor
 *  @dependency This depends on Metal.framework
 *  @discussion The MPSRNNSingleGateDescriptor specifies a simple recurrent block/layer descriptor.
 *              The RNN layer initialized with a MPSRNNSingleGateDescriptor transforms the input data (image or matrix),
 *              and previous output with a set of filters, each producing one feature map in the new output data.
 *              The user may provide the RNN unit a single input or a sequence of inputs.
 *
 *                  Description of operation:
 *
 *              Let x_j be the input data (at time index t of sequence,
 *                          j index containing quadruplet: batch index, x,y and feature index (x=y=0 for matrices)).
 *              Let h0_j be the recurrent input (previous output) data from previous time step (at time index t-1 of sequence).
 *              Let h1_i be the output data produced at this time step.
 *
 *              Let W_ij, U_ij be the weights for input and recurrent input data respectively
 *              Let b_i be a bias term
 *
 *              Let gi(x) be a neuron activation function
 *
 *              Then the new output image h1_i data is computed as follows:
 *
 *                  h1_i = gi( W_ij * x_j + U_ij * h0_j  + b_i )
 *
 *              The '*' stands for convolution (see @ref MPSRNNImageInferenceLayer) or matrix-vector/matrix multiplication
 *              (see @ref MPSRNNMatrixInferenceLayer).
 *              Summation is over index j (except for the batch index), but there is no summation over
 *              repeated index i - the output index.
 *              Note that for validity all intermediate images have to be of same size and the U matrix has to be square
 *              (ie. outputFeatureChannels == inputFeatureChannels in those). Also the bias terms are scalars wrt. spatial dimensions.
 *
 *
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), macCatalyst(13.0), tvos(11.0))
@interface MPSRNNSingleGateDescriptor : MPSRNNDescriptor


// Input parameters

/*! @property   inputWeights
 *  @abstract   Contains weights 'W_ij', bias 'b_i' and neuron 'gi' from the simple RNN layer formula.
 *              If nil then assumed zero weights, bias and no neuron (identity mapping). Defaults to nil.
 */
@property (readwrite, retain, nonatomic, nullable)  id <MPSCNNConvolutionDataSource> inputWeights;

/*! @property   recurrentWeights
 *  @abstract   Contains weights 'U_ij' from the simple RNN layer formula.
 *              If nil then assumed zero weights. Defaults to nil.
 */
@property (readwrite, retain, nonatomic, nullable)  id <MPSCNNConvolutionDataSource> recurrentWeights;
/*!
 *  @abstract   Creates a MPSRNNSingleGateDescriptor
 *  @param      inputFeatureChannels    The number of feature channels in the input image/matrix. Must be >= 1.
 *  @param      outputFeatureChannels   The number of feature channels in the output image/matrix. Must be >= 1.
 *  @return     A valid MPSRNNSingleGateDescriptor object or nil, if failure.
 */
+(nonnull instancetype) createRNNSingleGateDescriptorWithInputFeatureChannels: (NSUInteger) inputFeatureChannels
                                                        outputFeatureChannels: (NSUInteger) outputFeatureChannels
MPS_AVAILABLE_STARTING(macos(10.13), ios(11.0), macCatalyst(13.0), tvos(11.0) );

@end    /* MPSRNNSingleGateDescriptor */



#pragma mark -
#pragma mark MPSGRUDescriptor

/*!
 *  @class      MPSGRUDescriptor
 *  @dependency This depends on Metal.framework
 *  @discussion The MPSGRUDescriptor specifies a GRU (Gated Recurrent Unit) block/layer descriptor.
 *              The RNN layer initialized with a MPSGRUDescriptor transforms the input data (image or matrix),
 *              and previous output with a set of filters, each producing one feature map in
 *              the output data according to the Gated unit formulae detailed below.
 *              The user may provide the GRU unit a single input or a sequence of inputs. The layer also supports
 *              p-norm gating (Detailed in: https://arxiv.org/abs/1608.03639 ).
 *
 *                  Description of operation:
 *
 *              Let x_j be the input data (at time index t of sequence,
 *                          j index containing quadruplet: batch index, x,y and feature index (x=y=0 for matrices)).
 *              Let h0_j be the recurrent input (previous output) data from previous time step (at time index t-1 of sequence).
 *              Let h_i be the proposed new output.
 *              Let h1_i be the output data produced at this time step.
 *
 *              Let Wz_ij, Uz_ij, be the input gate weights for input and recurrent input data respectively
 *              Let bi_i be the bias for the input gate
 *
 *              Let Wr_ij, Ur_ij be the recurrent gate weights for input and recurrent input data respectively
 *              Let br_i be the bias for the recurrent gate
 *
 *              Let Wh_ij, Uh_ij, Vh_ij, be the output gate weights for input, recurrent gate and input gate respectively
 *              Let bh_i be the bias for the output gate
 *
 *              Let gz(x), gr(x), gh(x) be the neuron activation function for the input, recurrent and output gates
 *              Let p > 0 be a scalar variable (typicall p >= 1.0) that defines the p-norm gating norm value.
 *
 *              Then the output of the Gated Recurrent Unit layer is computed as follows:
 *
 *                      z_i = gz(  Wz_ij * x_j  +  Uz_ij * h0_j  +  bz_i  )
 *                      r_i = gr(  Wr_ij * x_j  +  Ur_ij * h0_j  +  br_i  )
 *                      c_i =      Uh_ij * (r_j h0_j)  +  Vh_ij * (z_j h0_j)
 *                      h_i = gh(  Wh_ij * x_j  + c_i + bh_i  )
 *
 *                  h1_i = ( 1 - z_i ^ p)^(1/p) h_i + z_i h0_i
 *
 *
 *              The '*' stands for convolution (see @ref MPSRNNImageInferenceLayer) or matrix-vector/matrix multiplication
 *              (see @ref MPSRNNMatrixInferenceLayer).
 *              Summation is over index j (except for the batch index), but there is no summation over
 *              repeated index i - the output index.
 *              Note that for validity all intermediate images have to be of same size and all U and V matrices have to be square
 *              (ie. outputFeatureChannels == inputFeatureChannels in those). Also the bias terms are scalars wrt. spatial dimensions.
 *              The conventional GRU block is achieved by setting Vh = 0 (nil) and the so-called Minimal Gated Unit is achieved with Uh = 0.
 *              (The Minimal Gated Unit is detailed in: https://arxiv.org/abs/1603.09420 and there they call z_i the value of the forget gate).
 *
 *
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), macCatalyst(13.0), tvos(11.0))
@interface MPSGRUDescriptor : MPSRNNDescriptor


// Input gate parameters

/*! @property   inputGateInputWeights
 *  @abstract   Contains weights 'Wz_ij', bias 'bz_i' and neuron 'gz' from the GRU formula.
 *              If nil then assumed zero weights, bias and no neuron (identity mapping). Defaults to nil.
 */
@property (readwrite, retain, nonatomic, nullable)  id <MPSCNNConvolutionDataSource> inputGateInputWeights;
/*! @property   inputGateRecurrentWeights
 *  @abstract   Contains weights 'Uz_ij' from the GRU formula.
 *              If nil then assumed zero weights. Defaults to nil.
 */
@property (readwrite, retain, nonatomic, nullable)  id <MPSCNNConvolutionDataSource> inputGateRecurrentWeights;




// Recurrent gate parameters

/*! @property   recurrentGateInputWeights
 *  @abstract   Contains weights 'Wr_ij', bias 'br_i' and neuron 'gr' from the GRU formula.
 *              If nil then assumed zero weights, bias and no neuron (identity mapping).Defaults to nil.
 */
@property (readwrite, retain, nonatomic, nullable)  id <MPSCNNConvolutionDataSource> recurrentGateInputWeights;
/*! @property   recurrentGateRecurrentWeights
 *  @abstract   Contains weights 'Ur_ij' from the GRU formula.
 *              If nil then assumed zero weights.Defaults to nil.
 */
@property (readwrite, retain, nonatomic, nullable)  id <MPSCNNConvolutionDataSource> recurrentGateRecurrentWeights;




// Proposed output gate parameters

/*! @property   outputGateInputWeights
 *  @abstract   Contains weights 'Wh_ij', bias 'bh_i' and neuron 'gh' from the GRU formula.
 *              If nil then assumed zero weights, bias and no neuron (identity mapping).Defaults to nil.
 */
@property (readwrite, retain, nonatomic, nullable)  id <MPSCNNConvolutionDataSource> outputGateInputWeights;
/*! @property   outputGateRecurrentWeights
 *  @abstract   Contains weights 'Uh_ij' from the GRU formula.
 *              If nil then assumed zero weights. Defaults to nil.
 */
@property (readwrite, retain, nonatomic, nullable)  id <MPSCNNConvolutionDataSource> outputGateRecurrentWeights;
/*! @property   outputGateInputGateWeights
 *  @abstract   Contains weights 'Vh_ij' - can be used to implement the "Minimally Gated Unit".
 *              If nil then assumed zero weights. Defaults to nil.
 */
@property (readwrite, retain, nonatomic, nullable)  id <MPSCNNConvolutionDataSource> outputGateInputGateWeights;


/*! @property   gatePnormValue
 *  @abstract   The p-norm gating norm value as specified by the GRU formulae. Defaults to 1.0f.
 */
@property(readwrite, nonatomic) float       gatePnormValue;

/*! @property   flipOutputGates
 *  @abstract   If YES then the GRU-block output formula is changed to:
 *                  h1_i = ( 1 - z_i ^ p)^(1/p) h0_i + z_i h_i.
 *              Defaults to NO.
 */
@property(readwrite, nonatomic) BOOL        flipOutputGates;

/*!
 *  @abstract   Creates a GRU descriptor.
 *  @param      inputFeatureChannels    The number of feature channels in the input image/matrix. Must be >= 1.
 *  @param      outputFeatureChannels   The number of feature channels in the output image/matrix. Must be >= 1.
 *  @return     A valid MPSGRUDescriptor object or nil, if failure.
 */
+(nonnull instancetype) createGRUDescriptorWithInputFeatureChannels: (NSUInteger) inputFeatureChannels
                                              outputFeatureChannels: (NSUInteger) outputFeatureChannels
MPS_AVAILABLE_STARTING(macos(10.13), ios(11.0), macCatalyst(13.0), tvos(11.0) );

@end    /* MPSGRUDescriptor */





#pragma mark -
#pragma mark MPSLSTMDescriptor

/*!
 *  @class      MPSLSTMDescriptor
 *  @dependency This depends on Metal.framework
 *  @discussion The MPSLSTMDescriptor specifies a LSTM block/layer descriptor.
 *              The RNN layer initialized with a MPSLSTMDescriptor transforms the input data (image or matrix),
 *              the memory cell data and previous output with a set of filters, each producing one feature map in
 *              the output data and memory cell, according to the LSTM formulae detailed below.
 *              The user may provide the LSTM unit a single input or a sequence of inputs.
 *
 *                  Description of operation:
 *
 *              Let x_j be the input data (at time index t of sequence,
 *                          j index containing quadruplet: batch index, x,y and feature index (x=y=0 for matrices)).
 *              Let h0_j be the recurrent input (previous output) data from previous time step (at time index t-1 of sequence).
 *              Let h1_i be the output data produced at this time step.
 *              Let c0_j be the previous memory cell data (at time index t-1 of sequence).
 *              Let c1_i be the new memory cell data (at time index t-1 of sequence).
 *
 *              Let Wi_ij, Ui_ij, Vi_ij, be the input gate weights for input, recurrent input and memory cell (peephole) data respectively
 *              Let bi_i be the bias for the input gate
 *
 *              Let Wf_ij, Uf_ij, Vf_ij, be the forget gate weights for input, recurrent input and memory cell data respectively
 *              Let bf_i be the bias for the forget gate
 *
 *              Let Wo_ij, Uo_ij, Vo_ij, be the output gate weights for input, recurrent input and memory cell data respectively
 *              Let bo_i be the bias for the output gate
 *
 *              Let Wc_ij, Uc_ij, Vc_ij, be the memory cell gate weights for input, recurrent input and memory cell data respectively
 *              Let bc_i be the bias for the memory cell gate
 *
 *              Let gi(x), gf(x), go(x), gc(x) be neuron activation function for the input, forget, output gate and memory cell gate
 *              Let gh(x) be the activation function applied to result memory cell data
 *
 *              Then the new memory cell data c1_j and output image h1_i are computed as follows:
 *
 *                      I_i = gi(  Wi_ij * x_j  +  Ui_ij * h0_j  +  Vi_ij * c0_j  + bi_i  )
 *                      F_i = gf(  Wf_ij * x_j  +  Uf_ij * h0_j  +  Vf_ij * c0_j  + bf_i  )
 *                      C_i = gc(  Wc_ij * x_j  +  Uc_ij * h0_j  +  Vc_ij * c0_j  + bc_i  )
 *
 *                  c1_i = F_i c0_i  +  I_i C_i
 *
 *                      O_i = go(  Wo_ij * x_j  +  Uo_ij * h0_j  +  Vo_ij * c1_j  + bo_i  )
 *
 *                  h1_i = O_i gh( c1_i )
 *
 *              The '*' stands for convolution (see @ref MPSRNNImageInferenceLayer) or matrix-vector/matrix multiplication
 *              (see @ref MPSRNNMatrixInferenceLayer).
 *              Summation is over index j (except for the batch index), but there is no summation over
 *              repeated index i - the output index.
 *              Note that for validity all intermediate images have to be of same size and all U and V matrices have to be square
 *              (ie. outputFeatureChannels == inputFeatureChannels in those). Also the bias terms are scalars wrt. spatial dimensions.
 *
 *
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), macCatalyst(13.0), tvos(11.0))
@interface MPSLSTMDescriptor : MPSRNNDescriptor


/*! @property   memoryWeightsAreDiagonal
 *  @abstract   If YES, then the 'peephole' weight matrices will be diagonal matrices represented as
 *              vectors of length the number of features in memory cells, that will be multiplied pointwise
 *              with the peephole matrix or image in order to achieve the diagonal (nonmixing) update.
 *              Defaults to NO.
 */
@property(readwrite, nonatomic)     BOOL      memoryWeightsAreDiagonal;



// Input gate parameters

/*! @property   inputGateInputWeights
 *  @abstract   Contains weights 'Wi_ij', bias 'bi_i' and neuron 'gi' from the LSTM formula.
 *              If nil then assumed zero weights, bias and no neuron (identity mapping). Defaults to nil.
 */
@property (readwrite, retain, nonatomic, nullable)  id <MPSCNNConvolutionDataSource> inputGateInputWeights;
/*! @property   inputGateRecurrentWeights
 *  @abstract   Contains weights 'Ui_ij' from the LSTM formula.
 *              If nil then assumed zero weights. Defaults to nil.
 */
@property (readwrite, retain, nonatomic, nullable)  id <MPSCNNConvolutionDataSource> inputGateRecurrentWeights;
/*! @property   inputGateMemoryWeights
 *  @abstract   Contains weights 'Vi_ij' - the 'peephole' weights - from the LSTM formula.
 *              if YES == memoryWeightsAreDiagonal, then the number of weights used is the number of features
 *                  in the memory cell image/matrix.
 *              If nil then assumed zero weights. Defaults to nil.
 */
@property (readwrite, retain, nonatomic, nullable)  id <MPSCNNConvolutionDataSource> inputGateMemoryWeights;




// Forget gate parameters

/*! @property   forgetGateInputWeights
 *  @abstract   Contains weights 'Wf_ij', bias 'bf_i' and neuron 'gf' from the LSTM formula.
 *              If nil then assumed zero weights, bias and no neuron (identity mapping).Defaults to nil.
 */
@property (readwrite, retain, nonatomic, nullable)  id <MPSCNNConvolutionDataSource> forgetGateInputWeights;
/*! @property   forgetGateRecurrentWeights
 *  @abstract   Contains weights 'Uf_ij' from the LSTM formula.
 *              If nil then assumed zero weights. Defaults to nil.
 */
@property (readwrite, retain, nonatomic, nullable)  id <MPSCNNConvolutionDataSource> forgetGateRecurrentWeights;
/*! @property   forgetGateMemoryWeights
 *  @abstract   Contains weights 'Vf_ij' - the 'peephole' weights - from the LSTM formula.
 *              if YES == memoryWeightsAreDiagonal, then the number of weights used is the number of features
 *                  in the memory cell image/matrix.
 *              If nil then assumed zero weights. Defaults to nil.
 */
@property (readwrite, retain, nonatomic, nullable)  id <MPSCNNConvolutionDataSource> forgetGateMemoryWeights;




// Output gate parameters

/*! @property   outputGateInputWeights
 *  @abstract   Contains weights 'Wo_ij', bias 'bo_i' and neuron 'go' from the LSTM formula.
 *              If nil then assumed zero weights, bias and no neuron (identity mapping). Defaults to nil.
 */
@property (readwrite, retain, nonatomic, nullable)  id <MPSCNNConvolutionDataSource> outputGateInputWeights;
/*! @property   outputGateRecurrentWeights
 *  @abstract   Contains weights 'Uo_ij' from the LSTM formula.
 *              If nil then assumed zero weights. Defaults to nil.
 */
@property (readwrite, retain, nonatomic, nullable)  id <MPSCNNConvolutionDataSource> outputGateRecurrentWeights;
/*! @property   outputGateMemoryWeights
 *  @abstract   Contains weights 'Vo_ij' - the 'peephole' weights - from the LSTM.
 *              if YES == memoryWeightsAreDiagonal, then the number of weights used is the number of features
 *                  in the memory cell image/matrix.
 *              If nil then assumed zero weights. Defaults to nil.
 */
@property (readwrite, retain, nonatomic, nullable)  id <MPSCNNConvolutionDataSource> outputGateMemoryWeights;




// Memory cell gate parameters

/*! @property   cellGateInputWeights
 *  @abstract   Contains weights 'Wc_ij', bias 'bc_i' and neuron 'gc' from the LSTM formula.
 *              If nil then assumed zero weights, bias and no neuron (identity mapping). Defaults to nil.
 */
@property (readwrite, retain, nonatomic, nullable)  id <MPSCNNConvolutionDataSource> cellGateInputWeights;
/*! @property   cellGateRecurrentWeights
 *  @abstract   Contains weights 'Uc_ij' from the LSTM formula.
 *              If nil then assumed zero weights. Defaults to nil.
 */
@property (readwrite, retain, nonatomic, nullable)  id <MPSCNNConvolutionDataSource> cellGateRecurrentWeights;
/*! @property   cellGateMemoryWeights
 *  @abstract   Contains weights 'Vc_ij' - the 'peephole' weights - from the LSTM formula.
 *              if YES == memoryWeightsAreDiagonal, then the number of weights used is the number of features
 *                  in the memory cell image/matrix.
 *              If nil then assumed zero weights. Defaults to nil.
 */
@property (readwrite, retain, nonatomic, nullable)  id <MPSCNNConvolutionDataSource> cellGateMemoryWeights;



/*! @property   cellToOutputNeuronType
 *  @abstract   Neuron type definition for 'gh', see @ref MPSCNNNeuronType. Defaults to MPSCNNNeuronTypeTanH.
 */
@property(readwrite, nonatomic) MPSCNNNeuronType        cellToOutputNeuronType;

/*! @property   cellToOutputNeuronParamA
 *  @abstract   Neuron parameter A for 'gh'. Defaults to 1.0f.
 */
@property(readwrite, nonatomic) float                   cellToOutputNeuronParamA;

/*! @property   cellToOutputNeuronParamB
 *  @abstract   Neuron parameter B for 'gh'. Defaults to 1.0f.
 */
@property(readwrite, nonatomic) float                   cellToOutputNeuronParamB;

/*! @property   cellToOutputNeuronParamC
 *  @abstract   Neuron parameter C for 'gh'. Defaults to 1.0f.
 */
@property(readwrite, nonatomic) float                   cellToOutputNeuronParamC;



/*!
 *  @abstract   Creates a LSTM descriptor.
 *  @param      inputFeatureChannels    The number of feature channels in the input image/matrix. Must be >= 1.
 *  @param      outputFeatureChannels   The number of feature channels in the output image/matrix. Must be >= 1.
 *  @return     A valid MPSNNLSTMDescriptor object or nil, if failure.
 */
+(nonnull instancetype) createLSTMDescriptorWithInputFeatureChannels: (NSUInteger) inputFeatureChannels
                                               outputFeatureChannels: (NSUInteger) outputFeatureChannels
MPS_AVAILABLE_STARTING(macos(10.13), ios(11.0), macCatalyst(13.0), tvos(11.0) );

@end    /* MPSNNLSTMDescriptor */





/*!
 *  @class      MPSRNNRecurrentImageState
 *  @dependency This depends on Metal.framework
 *  @discussion This class holds all the data that is passed from one sequence iteration of the image-based RNN layer (stack) to the next.
 */

MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), macCatalyst(13.0), tvos(11.0))
@interface  MPSRNNRecurrentImageState : MPSState

/*!
 *  @abstract   Access the stored recurrent image data.
 *  @param      layerIndex      Index of the layer whose to get - belongs to { 0, 1,...,@see numberOfLayers - 1 }
 *  @return     For valid layerIndex the recurrent output image data, otherwise nil.
 */
-(nullable MPSImage*)   getRecurrentOutputImageForLayerIndex: (NSUInteger) layerIndex;

/*!
 *  @abstract   Access the stored memory cell image data (if present).
 *  @param      layerIndex      Index of the layer whose to get - belongs to { 0, 1,...,@see numberOfLayers - 1 }
 *  @return     For valid layerIndex the memory cell image data, otherwise nil.
 */
-(nullable MPSImage*)   getMemoryCellImageForLayerIndex: (NSUInteger) layerIndex;



@end    /* MPSRNNRecurrentImageState */



#pragma mark -
#pragma mark MPSRNNImageInferenceLayer

/*!
 *  @class      MPSRNNImageInferenceLayer
 *  @dependency This depends on Metal.framework
 *  @discussion The MPSRNNImageInferenceLayer specifies a recurrent neural network layer for inference on MPSImages.
 *              Currently two types of recurrent layers are supported: ones that operate with convolutions on
 *              images: @ref MPSRNNImageInferenceLayer and one that operates on matrices: @ref MPSRNNMatrixInferenceLayer.
 *              The former can be often used to implement the latter by using 1x1-images, but due to
 *              image size restrictions and performance, it is advisable to use @ref MPSRNNMatrixInferenceLayer for
 *              linear recurrent layers.
 *              A MPSRNNImageInferenceLayer is initialized using a @ref MPSRNNLayerDescriptor, which further specifies the
 *              recurrent network layer, or an array of @ref MPSRNNLayerDescriptors, which specifies a stack
 *              of recurrent layers, that can operate in parallel a subset of the inputs in a sequence of inputs and
 *              recurrent outputs. Note that currently stacks with bidirectionally traversing encode functions do not support starting
 *              from a previous set of recurrent states, but this can be achieved quite easily by defining two separate
 *              unidirectional stacks of layers, and running the same input sequence on them separately (one forwards and one backwards)
 *              and ultimately combining the two result sequences as desired with auxiliary functions.
 *
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), macCatalyst(13.0), tvos(11.0))
@interface  MPSRNNImageInferenceLayer : MPSCNNKernel


/*! @property   inputFeatureChannels
 *  @abstract   The number of feature channels per pixel in the input image.
 */
@property(readonly, nonatomic) NSUInteger       inputFeatureChannels;

/*! @property   outputFeatureChannels
 *  @abstract   The number of feature channels per pixel in the output image.
 */
@property(readonly, nonatomic) NSUInteger       outputFeatureChannels;



/*! @property   numberOfLayers
 *  @abstract   Number of layers in the filter-stack. This will be one when using initWithDevice:rnnDescriptor to initialize
 *                  this filter and the number of entries in the array 'rnnDescriptors' when initializing this filter with
 *                  initWithDevice:rnnDescriptors.
 */
@property(readonly, nonatomic) NSUInteger   numberOfLayers;


/*! @property   recurrentOutputIsTemporary
 *  @abstract   How output states from @ref encodeSequenceToCommandBuffer are constructed.
 *              Defaults to NO. For reference @see MPSState.
 */
@property(readwrite, nonatomic) BOOL   recurrentOutputIsTemporary;

/*! @property   storeAllIntermediateStates
 *  @abstract   If YES then calls to @ref encodeSequenceToCommandBuffer return every recurrent state
 *              in the array: recurrentOutputStates.
 *              Defaults to NO.
 */
@property(readwrite, nonatomic) BOOL   storeAllIntermediateStates;



/*! @property   bidirectionalCombineMode
 *  @abstract   Defines how to combine the output-results, when encoding bidirectional layers using
 *              @ref encodeBidirectionalSequenceToCommandBuffer.
 *              Defaults to @ref MPSRNNBidirectionalCombineModeNone.
 */
@property(readwrite, nonatomic) MPSRNNBidirectionalCombineMode   bidirectionalCombineMode;


/*!
 *  @abstract   Initializes a convolutional RNN kernel
 *  @param      device                          The MTLDevice on which this MPSRNNImageLayer filter will be used
 *  @param      rnnDescriptor                   The descriptor that defines the RNN layer
 *  @return     A valid MPSRNNImageInferenceLayer object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                         rnnDescriptor: (nonnull const MPSRNNDescriptor*) rnnDescriptor
NS_DESIGNATED_INITIALIZER
MPS_AVAILABLE_STARTING(macos(10.13), ios(11.0), macCatalyst(13.0), tvos(11.0));

/*!
 *  @abstract   Initializes a kernel that implements a stack of convolutional RNN layers
 *  @param      device                          The MTLDevice on which this MPSRNNImageLayer filter will be used
 *  @param      rnnDescriptors                  An array of RNN descriptors that defines a stack of RNN layers, starting at index zero.
 *                                                  The number of layers in stack is the number of entries in the array.
 *                                                  All entries in the array must be valid MPSRNNDescriptors.
 *  @return     A valid MPSRNNImageInferenceLayer object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                        rnnDescriptors: (NSArray<const MPSRNNDescriptor*>  * __nonnull) rnnDescriptors
NS_DESIGNATED_INITIALIZER
MPS_AVAILABLE_STARTING(macos(10.13), ios(11.0), macCatalyst(13.0), tvos(11.0));


/*
 * Use initWithDevice:rnnDescriptor instead
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_UNAVAILABLE;


/*!
 *  @abstract   Encode an MPSRNNImageInferenceLayer kernel (stack) for a sequence of inputs into a command buffer.
 *                  Note that when encoding using this function the @see layerSequenceDirection is ignored and the layer stack operates as
 *                  if all layers were forward feeding layers. In order to run bidirectional sequences
 *                  use @ref encodeBidirectionalSequenceToCommandBuffer:sourceSequence: or alternatively run two layer stacks and combine
 *                  results at the end using utility functions.
 *  @param      commandBuffer                   A valid MTLCommandBuffer to receive the encoded filter
 *  @param      sourceImages                    An array of valid MPSImage objects containing the sequence of source images.
 *  @param      destinationImages               An array valid MPSImages to be overwritten by result image sequence. destinationImages may not alias sourceImages.
 *  @param      recurrentInputState             An optional state containing the output images and memory cells (for LSTMs)
 *                                                  of the layer obtained from the previous input images in a sequence of inputs.
 *                                                  Has to be the output of a previous call to this function or nil (assumed zero).
 *                                                  Note: can be one of the states returned in @ref recurrentOutputStates.
 *  @param      recurrentOutputStates            An optional array that will contain the recurrent output states. If nil then
 *                                                  the recurrent output state is discarded.
 *                                                  If @ref storeAllIntermediateStates is YES, then all intermediate states of the sequence
 *                                                  are returned in the array, the first one corresponding to the first input in the sequence,
 *                                                  otherwise only the last recurrent output state is returned.
 *                                                  If recurrentOutputIsTemporary is YES and then all returned recurrent states
 *                                                  will be temporary. @see MPSState:isTemporary.
 *                                                  Example: In order to get a new state one can do the following:
 *                                                  @code
 *                                                      MPSRNNRecurrentImageState* recurrent0 = nil;
 *                                                      [filter encodeToCommandBuffer: cmdBuf
 *                                                                        sourceImage: source0
 *                                                                   destinationImage: destination0
 *                                                                recurrentInputState: nil
 *                                                               recurrentOutputState: &recurrent0];
 *                                                  @endcode
 *                                                  Then use it for the next input in sequence:
 *                                                  @code
 *                                                      [filter encodeToCommandBuffer: cmdBuf
 *                                                                        sourceImage: source1
 *                                                                   destinationImage: destination1
 *                                                                recurrentInputState: recurrent0
 *                                                               recurrentOutputState: &recurrent0];
 *                                                  @endcode
 *                                                  And discard recurrent output of the third input:
 *                                                  @code
 *                                                      [filter encodeToCommandBuffer: cmdBuf
 *                                                                        sourceImage: source2
 *                                                                   destinationImage: destination2
 *                                                                recurrentInputState: recurrent0
 *                                                               recurrentOutputState: nil];
 *                                                  @endcode
 */

-(void)  encodeSequenceToCommandBuffer:(nonnull id<MTLCommandBuffer>)commandBuffer
                          sourceImages:(NSArray<MPSImage*> * __nonnull)sourceImages
                     destinationImages:(NSArray<MPSImage*> * __nonnull)destinationImages
                   recurrentInputState:(MPSRNNRecurrentImageState * __nullable)recurrentInputState
                 recurrentOutputStates:(NSMutableArray<MPSRNNRecurrentImageState*>  * __nullable)recurrentOutputStates

MPS_SWIFT_NAME( encodeSequence(commandBuffer:sourceImages:destinationImages:recurrentInputState:recurrentOutputStates:));


/*!
 *  @abstract   Encode an MPSRNNImageInferenceLayer kernel stack for an input image sequences into a command buffer bidirectionally.
 *                  The operation proceeds as follows: The first source image x0 is passed through all forward traversing layers in the stack,
 *                  ie. those that were initialized with MPSRNNSequenceDirectionForward, recurrent input is assumed zero.
 *                  This produces forward output yf0 and recurrent states hf00, hf01, hf02, ... hf0n, one for each forward layer.
 *                  Then x1 is passed to forward layers together with recurrent state hf00, hf01, ..., hf0n, which produces yf1, and hf10,...
 *                  This procedure is iterated until the last image in the input sequence x_(N-1), which produces forward output yf(N-1).
 *                  The backwards layers iterate the same sequence backwards, starting from input x_(N-1) (recurrent state zero),
 *                  that produces yb(N-1) and recurrent output hb(N-1)0, hf(N-1)1, ... hb(N-1)m, one for each backwards traversing layer.
 *                  Then the backwards layers handle input x_(N-2) using recurrent state hb(N-1)0, ..., et cetera, until the
 *                  first image of the sequence is computed, producing output yb0. The result of the operation is either pair of sequences
 *                  ({yf0, yf1, ... , yf(N-1)},  {yb0, yb1, ... , yb(N-1)}) or a combined sequence, {(yf0 + yb0), ... , (yf(N-1) + yb(N-1)) },
 *                  where '+' stands either for sum, or concatenation along feature channels, as specified by @ref bidirectionalCombineMode.
 *
 *  @param      commandBuffer                   A valid MTLCommandBuffer to receive the encoded filter
 *  @param      sourceSequence                  An array of valid MPSImage objects containing the source image sequence (x0, x1, ... x_n-1).
 *  @param      destinationForwardImages        An array of valid MPSImages to be overwritten by result from forward input images. If bidirectionalCombineMode
 *                                                  is either MPSRNNBidirectionalCombineModeAdd or MPSRNNBidirectionalCombineModeConcatenate, then will
 *                                                  contain the combined results. destinationForwardImage may not alias with any of the source images.
 *  @param      destinationBackwardImages       If bidirectionalCombineMode is MPSRNNBidirectionalCombineModeNone, then must be a valid MPSImage
 *                                                  that will be  overwritten by result from backward input image. Otherwise this parameter is ignored
 *                                                  and can be nil. destinationBackwardImages may not alias to any of the source images.
 */

-(void) encodeBidirectionalSequenceToCommandBuffer:(nonnull id<MTLCommandBuffer>)commandBuffer
                                    sourceSequence:(NSArray<MPSImage*> * __nonnull)sourceSequence
                          destinationForwardImages:(NSArray<MPSImage*> * __nonnull)destinationForwardImages
                         destinationBackwardImages:(NSArray<MPSImage*> * __nullable)destinationBackwardImages
MPS_SWIFT_NAME( encodeBidirectionalSequence(commandBuffer:sourceSequence:destinationForwardImages:destinationBackwardImages:));

/*! @abstract NSSecureCoding compatability
 *  @discussion See @ref MPSKernel#initWithCoder.
 *  @param      aDecoder    The NSCoder subclass with your serialized MPSRNNImageInferenceLayer
 *  @param      device      The MTLDevice on which to make the MPSRNNImageInferenceLayer
 *  @return     A new MPSRNNImageInferenceLayer object, or nil if failure.
 */
-(nullable instancetype) initWithCoder:(NSCoder * __nonnull)aDecoder
                                device:(nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER
MPS_AVAILABLE_STARTING(macos(10.13), ios(11.0), macCatalyst(13.0), tvos(11.0));


/*!
 *  @abstract   Make a copy of this kernel for a new device - @see MPSKernel
 *  @param      zone        The NSZone in which to allocate the object
 *  @param      device      The device for the new MPSKernel. If nil, then use
 *                          self.device.
 *  @result     a pointer to a copy of this MPSKernel. This will fail, returning
 *              nil if the device is not supported. Devices must be
 *              MTLFeatureSet_iOS_GPUFamily2_v1 or later.
 */

- (nonnull instancetype) copyWithZone:(nullable NSZone *)zone
                               device:(nullable id <MTLDevice>) device;

@end    /* MPSRNNImageInferenceLayer */



/* MPSRNNRecurrentMatrixState */


/*!
 *  @class      MPSRNNRecurrentMatrixState
 *  @dependency This depends on Metal.framework
 *  @discussion This class holds all the data that is passed from one sequence iteration of the matrix-based RNN layer to the next.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), macCatalyst(13.0), tvos(11.0))
@interface  MPSRNNRecurrentMatrixState : MPSState
/*!
 *  @abstract   Access the stored recurrent matrix data.
 *  @param      layerIndex      Index of the layer whose to get - belongs to { 0, 1,...,@see numberOfLayers - 1 }
 *  @return     For valid layerIndex the recurrent output matrix data, otherwise nil.
 */
-(nullable MPSMatrix*)   getRecurrentOutputMatrixForLayerIndex: (NSUInteger) layerIndex;

/*!
 *  @abstract   Access the stored memory cell matrix data (if present).
 *  @param      layerIndex      Index of the layer whose to get - belongs to { 0, 1,...,@see numberOfLayers - 1 }
 *  @return     For valid layerIndex the memory cell image matrix, otherwise nil.
 */
-(nullable MPSMatrix*)   getMemoryCellMatrixForLayerIndex: (NSUInteger) layerIndex;

@end



#pragma mark -
#pragma mark MPSRNNMatrixInferenceLayer

/*!
 *  @class      MPSRNNMatrixInferenceLayer
 *  @dependency This depends on Metal.framework
 *  @discussion The MPSRNNMatrixInferenceLayer specifies a recurrent neural network layer for inference on MPSMatrices.
 *              Currently two types of recurrent layers are supported: ones that operate with convolutions on
 *              images: @ref MPSRNNImageInferenceLayer and one that operates on matrices: @ref MPSRNNMatrixInferenceLayer.
 *              The former can be often used to implement the latter by using 1x1-matrices, but due to
 *              image size restrictions and performance, it is advisable to use @ref MPSRNNMatrixInferenceLayer for
 *              linear recurrent layers.
 *              A MPSRNNMatrixInferenceLayer is initialized using a @ref MPSRNNLayerDescriptor, which further specifies the
 *              recurrent network layer, or an array of @ref MPSRNNLayerDescriptors, which specifies a stack
 *              of recurrent layers, that can operate in parallel a subset of the inputs in a sequence of inputs and
 *              recurrent outputs. Note that currently stacks with bidirectionally traversing encode functions do not support starting
 *              from a previous set of recurrent states, but this can be achieved quite easily by defining two separate
 *              unidirectional stacks of layers, and running the same input sequence on them separately (one forwards and one backwards)
 *              and ultimately combining the two result sequences as desired with auxiliary functions.
 *              The input and output vectors in encode calls are stored as rows of the input and output matrices and
 *              MPSRNNMatrixInferenceLayer supports matrices with decreasing number of rows: The row-indices identify the different
 *              sequences that may be of different lengths - for example if we have three sequences:
 *                  ( x1, x2, x3 ), ( y1, y2, y3, y4 ) and ( z1, z2 )
 *              of vectors xi, yi and zi, then these can be inserted together as a batch to the sequence encoding kernel by
 *              using the matrices:
 *                  @code
 *                           ( y1 )        ( y2 )        ( y3 )        ( y4 )
 *                      m1 = ( x1 ),  m2 = ( x2 ),  m3 = ( x3 ),  m4 =
 *                           ( z1 )        ( z2 )
 *                  @endcode
 *              If a recurrent output state is requested then it will contain the state corresponding to last inputs to each
 *              sequence and if all the intermediate states are requested (see storeAllIntermediateStates),
 *              then the shorter sequences will be propagated by copying the state of the previous output if the
 *              input vector is not present in the sequence - in the example above the output states would be:
 *                  @code
 *                           ( s_y1 )        ( s_y2 )        ( s_y3 )        ( s_y4 )
 *                      s1 = ( s_x1 ),  s2 = ( s_x2 ),  s3 = ( s_x3 ),  s4 = ( s_x3 )
 *                           ( s_z1 )        ( s_z2 )        ( s_z2 )        ( s_z2 )
 *                  @endcode
 *              The mathematical operation described in the linear transformations of @ref MPSRNNSingleGateDescriptor
 *              @ref MPSLSTMDescriptor and @ref MPSGRUDescriptor are y^T = W x^T  <=> y = x W^T, where x is the matrix containing
 *              the input vectors as rows, y is the matrix containing the output vectors as rows and W is the weight matrix.
 *
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), macCatalyst(13.0), tvos(11.0))
@interface  MPSRNNMatrixInferenceLayer : MPSKernel


/*! @property   inputFeatureChannels
 *  @abstract   The number of feature channels input vector/matrix.
 */
@property(readonly, nonatomic) NSUInteger       inputFeatureChannels;

/*! @property   outputFeatureChannels
 *  @abstract   The number of feature channels in the output vector/matrix.
 */
@property(readonly, nonatomic) NSUInteger       outputFeatureChannels;



/*! @property   numberOfLayers
 *  @abstract   Number of layers in the filter-stack. This will be one when using initWithDevice:rnnDescriptor to initialize
 *                  this filter and the number of entries in the array 'rnnDescriptors' when initializing this filter with
 *                  initWithDevice:rnnDescriptors.
 */
@property(readonly, nonatomic) NSUInteger   numberOfLayers;

/*! @property   recurrentOutputIsTemporary
 *  @abstract   How output states from @ref encodeSequenceToCommandBuffer are constructed.
 *              Defaults to NO. For reference @see MPSState.
 */
@property(readwrite, nonatomic) BOOL   recurrentOutputIsTemporary;

/*! @property   storeAllIntermediateStates
 *  @abstract   If YES then calls to @ref encodeSequenceToCommandBuffer return every recurrent state
 *              in the array: recurrentOutputStates.
 *              Defaults to NO.
 */
@property(readwrite, nonatomic) BOOL   storeAllIntermediateStates;


/*! @property   bidirectionalCombineMode
 *  @abstract   Defines how to combine the output-results, when encoding bidirectional layers using
 *              @ref encodeBidirectionalSequenceToCommandBuffer.
 *              Defaults to @ref MPSRNNBidirectionalCombineModeNone.
 */
@property(readwrite, nonatomic) MPSRNNBidirectionalCombineMode   bidirectionalCombineMode;


/*!
 *  @abstract   Initializes a linear (fully connected) RNN kernel
 *  @param      device                          The MTLDevice on which this MPSRNNMatrixLayer filter will be used
 *  @param      rnnDescriptor                   The descriptor that defines the RNN layer
 *  @return     A valid MPSRNNMatrixInferenceLayer object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                         rnnDescriptor: (nonnull const MPSRNNDescriptor*) rnnDescriptor
NS_DESIGNATED_INITIALIZER
MPS_AVAILABLE_STARTING(macos(10.13), ios(11.0), macCatalyst(13.0), tvos(11.0));

/*!
 *  @abstract   Initializes a kernel that implements a stack of linear (fully connected) RNN layers
 *  @param      device                          The MTLDevice on which this MPSRNNMatrixLayer filter will be used
 *  @param      rnnDescriptors                  An array of RNN descriptors that defines a stack of RNN layers, starting at index zero.
 *                                                  The number of layers in stack is the number of entries in the array.
 *                                                  All entries in the array must be valid MPSRNNDescriptors.
 *  @return     A valid MPSRNNMatrixInferenceLayer object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                        rnnDescriptors: (NSArray<const MPSRNNDescriptor*>  * __nonnull) rnnDescriptors
NS_DESIGNATED_INITIALIZER
MPS_AVAILABLE_STARTING(macos(10.13), ios(11.0), macCatalyst(13.0), tvos(11.0));


/*
 * Use initWithDevice:rnnDescriptor instead
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_UNAVAILABLE;

/*!
 *  @abstract   Encode an MPSRNNMatrixInferenceLayer kernel (stack) for a sequence of inputs into a command buffer.
 *                  Note that when encoding using this function the @see layerSequenceDirection is ignored and the layer stack operates as
 *                  if all layers were forward feeding layers. In order to run bidirectional sequences
 *                  use @ref encodeBidirectionalSequenceToCommandBuffer:sourceSequence: or alternatively run two layer stacks and combine
 *                  results at the end using utility functions.
 *  @param      commandBuffer                   A valid MTLCommandBuffer to receive the encoded filter
 *  @param      sourceMatrices                  An array of valid MPSMatrix objects containing the sequence of source matrices.
 *  @param      sourceOffsets                   An array of byte-offsets into the sourceMatrices, if nil zeros are assumed and
 *                                                  if not nil must contain offset for every matrix in sourceMatrices.
 *  @param      destinationMatrices             An array valid MPSMatrices to be overwritten by result matrix sequence.
 *                                                  destinationMatrices may not alias sourceMatrices.
 *  @param      destinationOffsets              An array of byte-offsets into the destinationMatrices, if nil zeros are assumed and
 *                                                  if not nil must contain offset for every matrix in destinationMatrices.
 *  @param      recurrentInputState             An optional state containing the output matrices and memory cells (for LSTMs)
 *                                                  of the layer obtained from the previous input matrices in a sequence of inputs.
 *                                                  Has to be the output of a previous call to this function or nil (assumed zero).
 *                                                  Note: can be one of the states returned in @ref intermediateRecurrentStates.
 *  @param      recurrentOutputStates            An optional array that will contain the recurrent output states. If nil then
 *                                                  the recurrent output state is discarded.
 *                                                  If @ref storeAllIntermediateStates is YES, then all intermediate states of the sequence
 *                                                  are returned in the array, the first one corresponding to the first input in the sequence,
 *                                                  otherwise only the last recurrent output state is returned.
 *                                                  If recurrentOutputIsTemporary is YES and then all returned recurrent states
 *                                                  will be temporary. @see MPSState:isTemporary.
 *                                                  Example: In order to get a new state one can do the following:
 *                                                  @code
 *                                                      MPSRNNRecurrentMatrixState* recurrent0 = nil;
 *                                                      [filter encodeToCommandBuffer: cmdBuf
 *                                                                       sourceMatrix: source0
 *                                                                  destinationMatrix: destination0
 *                                                                recurrentInputState: nil
 *                                                               recurrentOutputState: &recurrent0];
 *                                                  @endcode
 *                                                  Then use it for the next input in sequence:
 *                                                  @code
 *                                                      [filter encodeToCommandBuffer: cmdBuf
 *                                                                       sourceMatrix: source1
 *                                                                  destinationMatrix: destination1
 *                                                                recurrentInputState: recurrent0
 *                                                               recurrentOutputState: &recurrent0];
 *                                                  @endcode
 *                                                  And discard recurrent output of the third input:
 *                                                  @code
 *                                                      [filter encodeToCommandBuffer: cmdBuf
 *                                                                       sourceMatrix: source2
 *                                                                  destinationMatrix: destination2
 *                                                                recurrentInputState: recurrent0
 *                                                               recurrentOutputState: nil];
 *                                                  @endcode
 */

-( void )  encodeSequenceToCommandBuffer:(nonnull id<MTLCommandBuffer>)commandBuffer
                          sourceMatrices:(NSArray<MPSMatrix*> * __nonnull)sourceMatrices
                           sourceOffsets:(NSUInteger * __nullable) sourceOffsets
                     destinationMatrices:(NSArray<MPSMatrix*> * __nonnull)destinationMatrices
                      destinationOffsets:(NSUInteger * __nullable) destinationOffsets
                     recurrentInputState:(MPSRNNRecurrentMatrixState * __nullable)recurrentInputState
                   recurrentOutputStates:(NSMutableArray<MPSRNNRecurrentMatrixState*>  * __nullable)recurrentOutputStates
MPS_SWIFT_NAME( encodeSequence(commandBuffer:sourceMatrices:sourceOffsets:destinationMatrices:destinationOffsets:recurrentInputState:recurrentOutputStates:))
MPS_AVAILABLE_STARTING(macos(10.14), ios(12.0), macCatalyst(13.0), tvos(12.0));


-( void )  encodeSequenceToCommandBuffer:(nonnull id<MTLCommandBuffer>)commandBuffer
                          sourceMatrices:(NSArray<MPSMatrix*> * __nonnull)sourceMatrices
                     destinationMatrices:(NSArray<MPSMatrix*> * __nonnull)destinationMatrices
                     recurrentInputState:(MPSRNNRecurrentMatrixState * __nullable)recurrentInputState
                   recurrentOutputStates:(NSMutableArray<MPSRNNRecurrentMatrixState*>  * __nullable)recurrentOutputStates

MPS_SWIFT_NAME( encodeSequence(commandBuffer:sourceMatrices:destinationMatrices:recurrentInputState:recurrentOutputStates:));


/*!
 *  @abstract   Encode an MPSRNNMatrixInferenceLayer kernel stack for an input matrix sequences into a command buffer bidirectionally.
 *                  The operation proceeds as follows: The first source matrix x0 is passed through all forward traversing layers in the stack,
 *                  ie. those that were initialized with MPSRNNSequenceDirectionForward, recurrent input is assumed zero.
 *                  This produces forward output yf0 and recurrent states hf00, hf01, hf02, ... hf0n, one for each forward layer in the stack.
 *                  Then x1 is passed to forward layers together with recurrent state hf00, hf01, ..., hf0n, which produces yf1, and hf10,...
 *                  This procedure is iterated until the last matrix in the input sequence x_(N-1), which produces forward output yf(N-1).
 *                  The backwards layers iterate the same sequence backwards, starting from input x_(N-1) (recurrent state zero),
 *                  that produces yb(N-1) and recurrent output hb(N-1)0, hf(N-1)1, ... hb(N-1)m, one for each backwards traversing layer.
 *                  Then the backwards layers handle input x_(N-2) using recurrent state hb(N-1)0, ..., et cetera, until the
 *                  first matrix of the sequence is computed, producing output yb0. The result of the operation is either pair of sequences
 *                  ({yf0, yf1, ... , yf(N-1)},  {yb0, yb1, ... , yb(N-1)}) or a combined sequence, {(yf0 + yb0), ... , (yf(N-1) + yb(N-1)) },
 *                  where '+' stands either for sum, or concatenation along feature channels, as specified by @ref bidirectionalCombineMode.
 *
 *  @param      commandBuffer                   A valid MTLCommandBuffer to receive the encoded filter
 *  @param      sourceSequence                  An array of valid MPSMatrix objects containing the source matrix sequence (x0, x1, ... x_n-1).
 *  @param      destinationForwardMatrices      An array of valid MPSMatrices to be overwritten by result from forward input matrices. If bidirectionalCombineMode
 *                                                  is either MPSRNNBidirectionalCombineModeAdd or MPSRNNBidirectionalCombineModeConcatenate, then will
 *                                                  contain the combined results. destinationForwardMatrix may not alias with any of the source matrices.
 *  @param      destinationBackwardMatrices     If bidirectionalCombineMode is MPSRNNBidirectionalCombineModeNone, then must be an array of valid MPSMatrices
 *                                                  that will be overwritten by result from backward input matrices. Otherwise this parameter is ignored
 *                                                  and can be nil. destinationBackwardMatrices may not alias to any of the source matrices.
 */

-(void) encodeBidirectionalSequenceToCommandBuffer:(nonnull id<MTLCommandBuffer>)commandBuffer
                                    sourceSequence:(NSArray<MPSMatrix*> * __nonnull)sourceSequence
                        destinationForwardMatrices:(NSArray<MPSMatrix*> * __nonnull)destinationForwardMatrices
                       destinationBackwardMatrices:(NSArray<MPSMatrix*> * __nullable)destinationBackwardMatrices
MPS_SWIFT_NAME( encodeBidirectionalSequence(commandBuffer:sourceSequence:destinationForwardMatrices:destinationBackwardMatrices:));



/*! @abstract NSSecureCoding compatability
 *  @discussion See @ref MPSKernel#initWithCoder.
 *  @param      aDecoder    The NSCoder subclass with your serialized MPSRNNMatrixInferenceLayer
 *  @param      device      The MTLDevice on which to make the MPSRNNMatrixInferenceLayer
 *  @return     A new MPSRNNMatrixInferenceLayer object, or nil if failure.
 */
-(nullable instancetype) initWithCoder:(NSCoder * __nonnull)aDecoder
                                device:(nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER
MPS_AVAILABLE_STARTING(macos(10.13), ios(11.0), macCatalyst(13.0), tvos(11.0));


/*!
 *  @abstract   Make a copy of this kernel for a new device - @see MPSKernel
 *  @param      zone        The NSZone in which to allocate the object
 *  @param      device      The device for the new MPSKernel. If nil, then use
 *                          self.device.
 *  @result     a pointer to a copy of this MPSKernel. This will fail, returning
 *              nil if the device is not supported. Devices must be
 *              MTLFeatureSet_iOS_GPUFamily2_v1 or later.
 */

- (nonnull instancetype) copyWithZone:(nullable NSZone *)zone
                               device:(nullable id <MTLDevice>) device;

@end    /* MPSRNNMatrixInferenceLayer */




/*!
 *  @class      MPSRNNMatrixTrainingState
 *  @dependency This depends on Metal.framework
 *  @discussion This class holds the data that is passed from the forward pass needed in the backward pass.
 *
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.14), ios(12.0), macCatalyst(13.0), tvos(12.0))
@interface  MPSRNNMatrixTrainingState : MPSState
@end

/*! @enum       MPSRNNMatrixId
 *  @abstract   Defines which matrix is to be copied in or out of the trainable RNN layer -
 *              @see MPSRNNMatrixTrainingLayer:encodeCopyWeightsToCommandBuffer. That is, this identifies a
 *              matrix within the set of trainable weight parameters in @ref initWithDevice, @ref createWeightGradientMatrices
 *              @ref encodeForwardSequenceToCommandBuffer, @ref encodeGradientSequenceToCommandBuffer etc.
 */
#if defined(DOXYGEN)
#    define MPS_SWIFT_NAME(_a)
#    define MPS_ENUM_AVAILABLE_STARTING(...)
typedef enum MPSRNNMatrixId
#else
typedef NS_ENUM(NSUInteger, MPSRNNMatrixId)
#endif
{
    MPSRNNMatrixIdSingleGateInputWeights            MPS_ENUM_AVAILABLE_STARTING( macos(10.14), ios(12.0), macCatalyst(13.0), tvos(12.0)) MPS_SWIFT_NAME(SingleGateInputWeights)  = 0,
    MPSRNNMatrixIdSingleGateRecurrentWeights        MPS_ENUM_AVAILABLE_STARTING( macos(10.14), ios(12.0), macCatalyst(13.0), tvos(12.0)),
    MPSRNNMatrixIdSingleGateBiasTerms               MPS_ENUM_AVAILABLE_STARTING( macos(10.14), ios(12.0), macCatalyst(13.0), tvos(12.0)),


    MPSRNNMatrixIdLSTMInputGateInputWeights         MPS_ENUM_AVAILABLE_STARTING( macos(10.14), ios(12.0), macCatalyst(13.0), tvos(12.0)),
    MPSRNNMatrixIdLSTMInputGateRecurrentWeights     MPS_ENUM_AVAILABLE_STARTING( macos(10.14), ios(12.0), macCatalyst(13.0), tvos(12.0)),
    MPSRNNMatrixIdLSTMInputGateMemoryWeights        MPS_ENUM_AVAILABLE_STARTING( macos(10.14), ios(12.0), macCatalyst(13.0), tvos(12.0)),
    MPSRNNMatrixIdLSTMInputGateBiasTerms            MPS_ENUM_AVAILABLE_STARTING( macos(10.14), ios(12.0), macCatalyst(13.0), tvos(12.0)),

    MPSRNNMatrixIdLSTMForgetGateInputWeights         MPS_ENUM_AVAILABLE_STARTING( macos(10.14), ios(12.0), macCatalyst(13.0), tvos(12.0)),
    MPSRNNMatrixIdLSTMForgetGateRecurrentWeights     MPS_ENUM_AVAILABLE_STARTING( macos(10.14), ios(12.0), macCatalyst(13.0), tvos(12.0)),
    MPSRNNMatrixIdLSTMForgetGateMemoryWeights        MPS_ENUM_AVAILABLE_STARTING( macos(10.14), ios(12.0), macCatalyst(13.0), tvos(12.0)),
    MPSRNNMatrixIdLSTMForgetGateBiasTerms            MPS_ENUM_AVAILABLE_STARTING( macos(10.14), ios(12.0), macCatalyst(13.0), tvos(12.0)),

    MPSRNNMatrixIdLSTMMemoryGateInputWeights         MPS_ENUM_AVAILABLE_STARTING( macos(10.14), ios(12.0), macCatalyst(13.0), tvos(12.0)),
    MPSRNNMatrixIdLSTMMemoryGateRecurrentWeights     MPS_ENUM_AVAILABLE_STARTING( macos(10.14), ios(12.0), macCatalyst(13.0), tvos(12.0)),
    MPSRNNMatrixIdLSTMMemoryGateMemoryWeights        MPS_ENUM_AVAILABLE_STARTING( macos(10.14), ios(12.0), macCatalyst(13.0), tvos(12.0)),
    MPSRNNMatrixIdLSTMMemoryGateBiasTerms            MPS_ENUM_AVAILABLE_STARTING( macos(10.14), ios(12.0), macCatalyst(13.0), tvos(12.0)),

    MPSRNNMatrixIdLSTMOutputGateInputWeights         MPS_ENUM_AVAILABLE_STARTING( macos(10.14), ios(12.0), macCatalyst(13.0), tvos(12.0)),
    MPSRNNMatrixIdLSTMOutputGateRecurrentWeights     MPS_ENUM_AVAILABLE_STARTING( macos(10.14), ios(12.0), macCatalyst(13.0), tvos(12.0)),
    MPSRNNMatrixIdLSTMOutputGateMemoryWeights        MPS_ENUM_AVAILABLE_STARTING( macos(10.14), ios(12.0), macCatalyst(13.0), tvos(12.0)),
    MPSRNNMatrixIdLSTMOutputGateBiasTerms            MPS_ENUM_AVAILABLE_STARTING( macos(10.14), ios(12.0), macCatalyst(13.0), tvos(12.0)),


    MPSRNNMatrixIdGRUInputGateInputWeights            MPS_ENUM_AVAILABLE_STARTING( macos(10.14), ios(12.0), macCatalyst(13.0), tvos(12.0)),
    MPSRNNMatrixIdGRUInputGateRecurrentWeights        MPS_ENUM_AVAILABLE_STARTING( macos(10.14), ios(12.0), macCatalyst(13.0), tvos(12.0)),
    MPSRNNMatrixIdGRUInputGateBiasTerms               MPS_ENUM_AVAILABLE_STARTING( macos(10.14), ios(12.0), macCatalyst(13.0), tvos(12.0)),

    MPSRNNMatrixIdGRURecurrentGateInputWeights        MPS_ENUM_AVAILABLE_STARTING( macos(10.14), ios(12.0), macCatalyst(13.0), tvos(12.0)),
    MPSRNNMatrixIdGRURecurrentGateRecurrentWeights    MPS_ENUM_AVAILABLE_STARTING( macos(10.14), ios(12.0), macCatalyst(13.0), tvos(12.0)),
    MPSRNNMatrixIdGRURecurrentGateBiasTerms           MPS_ENUM_AVAILABLE_STARTING( macos(10.14), ios(12.0), macCatalyst(13.0), tvos(12.0)),

    MPSRNNMatrixIdGRUOutputGateInputWeights            MPS_ENUM_AVAILABLE_STARTING( macos(10.14), ios(12.0), macCatalyst(13.0), tvos(12.0)),
    MPSRNNMatrixIdGRUOutputGateRecurrentWeights        MPS_ENUM_AVAILABLE_STARTING( macos(10.14), ios(12.0), macCatalyst(13.0), tvos(12.0)),
    MPSRNNMatrixIdGRUOutputGateInputGateWeights        MPS_ENUM_AVAILABLE_STARTING( macos(10.14), ios(12.0), macCatalyst(13.0), tvos(12.0)),
    MPSRNNMatrixIdGRUOutputGateBiasTerms               MPS_ENUM_AVAILABLE_STARTING( macos(10.14), ios(12.0), macCatalyst(13.0), tvos(12.0)),

    MPSRNNMatrixId_count // Do not use - auxiliary enum value that gives number of ids.

}
#if defined(DOXYGEN)
MPSRNNMatrixId
#endif
;




#pragma mark -
#pragma mark MPSRNNMatrixTrainingLayer

/*!
 *  @class      MPSRNNMatrixTrainingLayer
 *  @dependency This depends on Metal.framework
 *  @discussion The MPSRNNMatrixTrainingLayer specifies a recurrent neural network layer for training on MPSMatrices.
 *
 *              A MPSRNNMatrixTrainingLayer is initialized using a @ref MPSRNNLayerDescriptor, which further specifies the
 *              recurrent network layer.
 *              The input and output vectors in encode calls are stored as rows of the input and output matrices and
 *              MPSRNNMatrixTrainingLayer supports matrices with decreasing number of rows: The row-indices identify the different
 *              sequences that may be of different lengths - for example if we have three sequences:
 *                  ( x1, x2, x3 ), ( y1, y2, y3, y4 ) and ( z1, z2 )
 *              of vectors xi, yi and zi, then these can be inserted together as a batch to the sequence encoding kernel by
 *              using the matrices:
 *                  @code
 *                           ( y1 )        ( y2 )        ( y3 )        ( y4 )
 *                      m1 = ( x1 ),  m2 = ( x2 ),  m3 = ( x3 ),  m4 =
 *                           ( z1 )        ( z2 )
 *                  @endcode
 *              The gradient computation pass is then achieved by passing the corresponding gradient sequence from the
 *              previous layer ( dx1, dx2, dx3 ), ( dy1, dy2, dy3, dy4 ) and ( dz1, dz2 ) as matrices
 *                  @code
 *                            ( dy1 )         ( dy2 )         ( dy3 )         ( dy4 )
 *                      dm1 = ( dx1 ),  dm2 = ( dx2 ),  dm3 = ( dx3 ),  dm4 =
 *                            ( dz1 )         ( dz2 )
 *                  @endcode
 *
 *              The mathematical operation described in the linear transformations of @ref MPSRNNSingleGateDescriptor
 *              @ref MPSLSTMDescriptor and @ref MPSGRUDescriptor are y^T = W x^T  <=> y = x W^T, where x is the matrix containing
 *              the input vectors as rows, y is the matrix containing the output vectors as rows and W is the weight matrix.
 *
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.14), ios(12.0), macCatalyst(13.0), tvos(12.0))
@interface  MPSRNNMatrixTrainingLayer : MPSKernel


/*! @property   inputFeatureChannels
 *  @abstract   The number of feature channels input vector/matrix.
 */
@property(readonly, nonatomic) NSUInteger       inputFeatureChannels;

/*! @property   outputFeatureChannels
 *  @abstract   The number of feature channels in the output vector/matrix.
 */
@property(readonly, nonatomic) NSUInteger       outputFeatureChannels;

/*! @property   storeAllIntermediateStates
 *  @abstract   If YES then calls to functions @ref encodeForwardSequenceToCommandBuffer and
 *              @ref encodeGradientSequenceToCommandBuffer return every recurrent state
 *              in the array: recurrentOutputStates.
 *              Defaults to NO.
 */
@property(readwrite, nonatomic) BOOL            storeAllIntermediateStates;


/*! @property   recurrentOutputIsTemporary
 *  @abstract   How recurrent output states from @ref encodeForwardSequenceToCommandBuffer
 *              and encodeGradientSequenceToCommandBuffer are constructed.
 *              Defaults to NO. For reference @see MPSState.
 */
@property(readwrite, nonatomic) BOOL            recurrentOutputIsTemporary;


/*! @property   trainingStateIsTemporary
 *  @abstract   How training output states from @ref encodeForwardSequenceToCommandBuffer are constructed.
 *              Defaults to NO. For reference @see MPSState.
 */
@property(readwrite, nonatomic) BOOL            trainingStateIsTemporary;

/*! @property   accumulateWeightGradients
 *  @abstract   If yes then the computed weight gradients are accumulated on top of existing values in
 *              calls to the gradient computation functions: encodeGradientSequenceToCommandBuffer.
 *              Defaults to NO.
 */
@property(readwrite, nonatomic) BOOL            accumulateWeightGradients;


/*!
 *  @abstract   Initializes a linear (fully connected) RNN kernel for training
 *  @param      device                      The MTLDevice on which this MPSRNNMatrixLayer filter will be used
 *  @param      rnnDescriptor               The descriptor that defines the RNN layer
 *  @param      trainableWeights            An array where to store the weights of the layer as MPSMatrices.
 *                                          NOTE: The exact layout and number of matrices may vary between
 *                                          platforms and therefore you should not save out these weights directly,
 *                                          but instead use the function encodeCopyWeightsToCommandBuffer to identify
 *                                          the weights and biases for serialization.
 *                                          Typically you should pass here an initialized but empty NSMutableArray and
 *                                          when this function returns the array will have been populated with the
 *                                          weight matrices needed in the encode-calls, by using initial values from
 *                                          the datasources in rnnDescriptor.
 *  @return     A valid MPSRNNMatrixTrainingLayer object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                         rnnDescriptor: (nonnull const MPSRNNDescriptor*) rnnDescriptor
                      trainableWeights: (NSMutableArray<MPSMatrix*>  * __nonnull)trainableWeights
NS_DESIGNATED_INITIALIZER
MPS_AVAILABLE_STARTING(macos(10.14), ios(12.0), macCatalyst(13.0), tvos(12.0));


/*!
 *  @abstract   Initializes a set of matrices that can be used in training for weight and bias gradient outputs in
 *              @see encodeBackwardSequenceToCommandBuffer. Can be also used to easily create auxiliary matrices for example
 *              for ADAM and other advanced optimization schemes. The layout and number of matrices is the same as for the outputs of
 *              @see initWithDevice, but the data type may differ. NOTE: These matrices cannot be used as weight matrices in the
 *              forward and backward encode calls, but matrices from initWithDevice() or createWeightMatrices() should be used instead.
 *  @param      matricesOut                 An array where the newly created matrices will be stored, will be initialized to zero.
 *  @param      dataType                    Datatype for the entries - currently MPSDataTypeFloat32 and MPSDataTypeFloat16 are supported.
 */
-(void) createWeightGradientMatrices: (NSMutableArray<MPSMatrix*>  * __nonnull) matricesOut
                            dataType: (MPSDataType) dataType
MPS_AVAILABLE_STARTING(macos(10.14), ios(12.0), macCatalyst(13.0), tvos(12.0));

/*!
 *  @abstract   As @ref createWeightGradientMatrices, but the matrices will be temporary with readCount = 1, which means that they
 *              become invalid after the first encode call that reads them. Note also that as the matrices are temporary, their
 *              storage mode will be private which means that you can only access the data using a kernel on the GPU.
 *  @param      matricesOut                 An array where the newly created matrices will be stored, will be initialized to zero.
 *  @param      dataType                    Datatype for the entries - currently MPSDataTypeFloat32 and MPSDataTypeFloat16 are supported.
 *  @param      commandBuffer               The command buffer that the temporary matrices will live on.
 */
-(void) createTemporaryWeightGradientMatrices: (NSMutableArray<MPSMatrix*>  * __nonnull) matricesOut
                                     dataType: (MPSDataType) dataType
                                commandBuffer: (nonnull id<MTLCommandBuffer>) commandBuffer
MPS_AVAILABLE_STARTING(macos(10.14), ios(12.0), macCatalyst(13.0), tvos(12.0));


/*!
 *  @abstract   Initializes a set of matrices that can be used in training for weight and bias matrices in
 *              the forward and backward passes. The layout, datatype and number of matrices is the same as for the outputs of
 *              @see initWithDevice.
 *  @param      matricesOut                 An array where the newly created matrices will be stored, will be initialized to zero.
 */
-(void) createWeightMatrices: (NSMutableArray<MPSMatrix*>  * __nonnull) matricesOut
MPS_AVAILABLE_STARTING(macos(10.14), ios(12.0), macCatalyst(13.0), tvos(12.0));


/*
 * Use initWithDevice:rnnDescriptor instead
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_UNAVAILABLE;


/*!
 *  @abstract   Encode a copy kernel that copies one matrix from the trainable weight set to a matrix with standard layout,
 *              where the column index is the input feature channel index (in forward direction) and row index is the output
 *              feature channel index.
 *  @param      commandBuffer                   A valid MTLCommandBuffer to receive the encoded filter
 *  @param      weights                         An array weights from @see initWithDevice or @see createWeightMatrices.
 *  @param      matrixId                        Which matrix to copy - has to be a valid Id based on inputs defined in
 *                                              the rnnDescriptor of @see initWithDevice.
 *  @param      matrix                          The destination or source matrix that is used in the copy.
 *  @param      copyFromWeightsToMatrix         If YES then the copy direction is from the set of trainable 'weights' to 'matrix',
 *                                              otherwise the copy is done from 'matrix' to 'weights'.
 *  @param      matrixOffset                    A (valid) offset into matrix to be applied to the copy operation.
 */

-( void )  encodeCopyWeightsToCommandBuffer: (nonnull id<MTLCommandBuffer>)commandBuffer
                                    weights: (NSArray<MPSMatrix*>  * __nonnull)weights
                                   matrixId: (MPSRNNMatrixId) matrixId
                                     matrix: (MPSMatrix * __nonnull) matrix
                    copyFromWeightsToMatrix: (BOOL) copyFromWeightsToMatrix
                               matrixOffset: (MTLOrigin) matrixOffset

MPS_SWIFT_NAME( encodeCopyWeights(commandBuffer:weights:matrixId:matrix:copyFromWeightsToMatrix:matrixOffset:));


/*!
 *  @abstract   Encode an MPSRNNMatrixTrainingLayer forward pass kernel for a sequence of inputs into a command buffer.
 *  @param      commandBuffer                   A valid MTLCommandBuffer to receive the encoded filter
 *  @param      sourceMatrices                  An array of valid MPSMatrix objects containing the sequence of source matrices.
 *  @param      sourceOffsets                   An array of byte-offsets into the sourceMatrices, if nil zeros are assumed and
 *                                                  if not nil must contain offset for every matrix in sourceMatrices.
 *  @param      destinationMatrices             An array valid MPSMatrices to be overwritten by result matrix sequence.
 *                                                  destinationMatrices may not alias sourceMatrices.
 *  @param      destinationOffsets              An array of byte-offsets into the destinationMatrices, if nil zeros are assumed and
 *                                                  if not nil must contain offset for every matrix in destinationMatrices.
 *  @param      trainingStates                   An array containing the training states to be passed to the gradient computation
 *                                                  encode function.
 *  @param      recurrentInputState             An optional state containing the output matrices and memory cells (for LSTMs)
 *                                                  of the layer obtained from the previous input matrices in a sequence of inputs.
 *                                                  Has to be the output of a previous call to this function or nil (assumed zero).
 *  @param      recurrentOutputStates           An array that will be appended with the recurrent output states. May not be nil.
 *                                                  If recurrentOutputIsTemporary is YES and then all returned recurrent states
 *                                                  will be temporary. @see MPSState:isTemporary.
 *  @param      weights                         An array of valid MPSMatrix objects containing the weights, should be the array
 *                                                  that was produced either by @see initWithDevice or @see createWeightMatrices.
 */

-( void )  encodeForwardSequenceToCommandBuffer:(nonnull id<MTLCommandBuffer>)commandBuffer
                                 sourceMatrices:(NSArray<MPSMatrix*> * __nonnull)sourceMatrices
                                  sourceOffsets:(NSUInteger * __nullable)sourceOffsets
                            destinationMatrices:(NSArray<MPSMatrix*> * __nonnull)destinationMatrices
                             destinationOffsets:(NSUInteger * __nullable)destinationOffsets
                                 trainingStates:(NSMutableArray<MPSRNNMatrixTrainingState*> * __nonnull) trainingStates
                            recurrentInputState:(MPSRNNRecurrentMatrixState * __nullable)recurrentInputState
                          recurrentOutputStates:(NSMutableArray<MPSRNNRecurrentMatrixState*>  * __nullable)recurrentOutputStates
                                        weights:(NSArray<MPSMatrix*>  * __nonnull)weights

MPS_SWIFT_NAME( encodeForwardSequence(commandBuffer:sourceMatrices:sourceOffsets:destinationMatrices:destinationOffsets:trainingStates:recurrentInputState:recurrentOutputStates:weights:));

/*!
 *  @abstract   Encode an MPSRNNMatrixTrainingLayer forward pass kernel for a sequence of inputs into a command buffer.
 *  @param      commandBuffer                   A valid MTLCommandBuffer to receive the encoded filter
 *  @param      sourceMatrices                  An array of valid MPSMatrix objects containing the sequence of source matrices.
 *  @param      destinationMatrices             An array valid MPSMatrices to be overwritten by result matrix sequence.
 *                                                  destinationMatrices may not alias sourceMatrices.
 *  @param      trainingStates                   An array containing the training states to be passed to the gradient computation
 *                                                  encode function.
 *  @param      weights                         An array of valid MPSMatrix objects containing the weights, should be the array
 *                                                  that was produced either by @see initWithDevice or @see createWeightMatrices.
 */

-( void )  encodeForwardSequenceToCommandBuffer:(nonnull id<MTLCommandBuffer>)commandBuffer
                                 sourceMatrices:(NSArray<MPSMatrix*> * __nonnull)sourceMatrices
                            destinationMatrices:(NSArray<MPSMatrix*> * __nonnull)destinationMatrices
                                 trainingStates:(NSMutableArray<MPSRNNMatrixTrainingState*> * __nonnull) trainingStates
                                        weights:(NSArray<MPSMatrix*>  * __nonnull)weights

MPS_SWIFT_NAME( encodeForwardSequence(commandBuffer:sourceMatrices:destinationMatrices:trainingStates:weights:));



/*!
 *  @abstract   Encode an MPSRNNMatrixTrainingLayer gradient pass kernel for a sequence of input gradients into a command buffer.
 *              NOTE: The time sequence indexing follows the array indexing in the inputs: sourceGradients[0] has to contain the
 *              gradients corresponding to the first matrix in the forward pass corresponding to the current subsequence, which is
 *              typically sourceMatrices[0].
 *  @param      commandBuffer                   A valid MTLCommandBuffer to receive the encoded filter
 *  @param      forwardSources                  An array of MPSMatrix objects containing the sequence of source matrices of the forward pass.
 *  @param      forwardSourceOffsets            An array of byte-offsets into the forwardSources, if nil zeros are assumed and
 *                                                  if not nil must contain offset for every matrix in forwardSources.
 *  @param      sourceGradients                 An array of valid MPSMatrix objects containing the sequence of source gradient matrices.
 *  @param      sourceGradientOffsets           An array of byte-offsets into the sourceGradients, if nil zeros are assumed and
 *                                                  if not nil must contain offset for every matrix in sourceGradients.
 *  @param      destinationGradients            An array valid MPSMatrix objects that will receive the backpropagated gradients, may be
 *                                                  nil if not needed (for example first layer in graph).
 *  @param      destinationOffsets              An array of byte-offsets into the destinationGradients, if nil zeros are assumed and
 *                                                  if not nil must contain offset for every matrix in destinationGradients.
 *  @param      weightGradients                 An array of valid MPSMatrix objects that will receive the gradient wrt. weights and
 *                                                  biases of the layer - should be the array that was produced either
 *                                                  by @see initWithDevice or @see createWeightMatrices. May be nil in which case
 *                                                  the gradients for the weights are not computed.
 *  @param      trainingStates                  An array containing the training states from the forward pass - the array must contain
 *                                                  the states corresponding to the input gradients is sourceGradients.
 *  @param      recurrentInputState             An optional state containing the output matrices and memory cells (for LSTMs)
 *                                                  of the layer obtained from the previous input gradients in a sequence of inputs.
 *                                                  Has to be the output of a previous call to this function or nil (assumed zero).
 *  @param      recurrentOutputStates           An array that will be appended with the recurrent output states. Can be nil.
 *                                                  If recurrentOutputIsTemporary is YES and then all returned recurrent states
 *                                                  will be temporary. @see MPSState:isTemporary.
 *  @param      weights                         An array of valid MPSMatrix objects containing the weights, should be the array
 *                                                  that was produced either by @see initWithDevice or @see createWeightMatrices.
 */

-( void )  encodeGradientSequenceToCommandBuffer:(nonnull id<MTLCommandBuffer>) commandBuffer
                                  forwardSources:(NSArray<MPSMatrix*> * __nonnull) forwardSources
                            forwardSourceOffsets:(NSUInteger * __nullable)forwardSourceOffsets
                                 sourceGradients:(NSArray<MPSMatrix*> * __nonnull) sourceGradients
                           sourceGradientOffsets:(NSUInteger * __nullable)sourceGradientOffsets
                            destinationGradients:(NSArray<MPSMatrix*> * __nullable) destinationGradients
                              destinationOffsets:(NSUInteger * __nullable)destinationOffsets
                                 weightGradients:(NSArray<MPSMatrix*> * __nullable) weightGradients
                                  trainingStates:(NSArray<MPSRNNMatrixTrainingState*> * __nonnull) trainingStates
                             recurrentInputState:(MPSRNNRecurrentMatrixState * __nullable) recurrentInputState
                           recurrentOutputStates:(NSMutableArray<MPSRNNRecurrentMatrixState*>  * __nullable) recurrentOutputStates
                                         weights:(NSArray<MPSMatrix*>  * __nonnull)weights

MPS_SWIFT_NAME( encodeGradientSequence(commandBuffer:forwardSources:forwardSourceOffsets:sourceGradients:sourceOffsets:destinationGradients:destinationOffsets:weightGradients:trainingStates:recurrentInputState:recurrentOutputStates:weights:));


/*!
 *  @abstract   Encode an MPSRNNMatrixTrainingLayer gradient pass kernel for a sequence of input gradients into a command buffer.
 *              NOTE: The time sequence indexing follows the array indexing in the inputs: sourceGradients[0] has to contain the
 *              gradients corresponding to the first matrix in the forward pass corresponding to the current subsequence, which is
 *              typically sourceMatrices[0].
 *  @param      commandBuffer                   A valid MTLCommandBuffer to receive the encoded filter
 *  @param      forwardSources                  An array of MPSMatrix objects containing the sequence of source matrices of the forward pass.
 *  @param      sourceGradients                 An array of MPSMatrix objects containing the sequence of source gradient matrices.
 *  @param      destinationGradients            An array valid MPSMatrix objects that will receive the backpropagated gradients, may be
 *                                                  nil if not needed (for example first layer in graph).
 *  @param      weightGradients                 An array valid MPSMatrix objects that will receive the gradient wrt. weights and
 *                                                  biases of the layer - should be the array that was produced either
 *                                                  by @see initWithDevice or @see createWeightMatrices. May be nil in which case
 *                                                  the gradients for the weights are not computed.
 *                                                  NOTE: The weight gradients are accumulated on top of existing values so
 *
 *  @param      trainingStates                  An array containing the training states from the forward pass - the array must contain
 *                                                  the states corresponding to the input gradients is sourceGradients.
 *  @param      weights                         An array of valid MPSMatrix objects containing the weights, should be the array
 *                                                  that was produced either by @see initWithDevice or @see createWeightMatrices.
 */

-( void )  encodeGradientSequenceToCommandBuffer:(nonnull id<MTLCommandBuffer>) commandBuffer
                                  forwardSources:(NSArray<MPSMatrix*> * __nonnull) forwardSources
                                 sourceGradients:(NSArray<MPSMatrix*> * __nonnull) sourceGradients
                            destinationGradients:(NSArray<MPSMatrix*> * __nullable) destinationGradients
                                 weightGradients:(NSArray<MPSMatrix*> * __nullable) weightGradients
                                  trainingStates:(NSArray<MPSRNNMatrixTrainingState*> * __nonnull) trainingStates
                                         weights:(NSArray<MPSMatrix*>  * __nonnull)weights

MPS_SWIFT_NAME( encodeGradientSequence(commandBuffer:forwardSources:sourceGradients:destinationGradients:weightGradients:trainingStates:weights:));



/*! @abstract NSSecureCoding compatability
 *  @discussion See @ref MPSKernel#initWithCoder.
 *  @param      aDecoder    The NSCoder subclass with your serialized MPSRNNMatrixTrainingLayer
 *  @param      device      The MTLDevice on which to make the MPSRNNMatrixTrainingLayer
 *  @return     A new MPSRNNMatrixTrainingLayer object, or nil if failure.
 */
-(nullable instancetype) initWithCoder:(NSCoder * __nonnull)aDecoder
                                device:(nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER
MPS_AVAILABLE_STARTING(macos(10.13), ios(11.0), macCatalyst(13.0), tvos(11.0));


/*!
 *  @abstract   Make a copy of this kernel for a new device - @see MPSKernel
 *  @param      zone        The NSZone in which to allocate the object
 *  @param      device      The device for the new MPSKernel. If nil, then use
 *                          self.device.
 *  @result     a pointer to a copy of this MPSKernel. This will fail, returning
 *              nil if the device is not supported. Devices must be
 *              MTLFeatureSet_iOS_GPUFamily2_v1 or later.
 */

- (nonnull instancetype) copyWithZone:(nullable NSZone *)zone
                               device:(nullable id <MTLDevice>) device;

@end    /* MPSRNNMatrixTrainingLayer */



#ifdef __cplusplus
}
#endif



#endif /* MPSRNNLayer_h */
