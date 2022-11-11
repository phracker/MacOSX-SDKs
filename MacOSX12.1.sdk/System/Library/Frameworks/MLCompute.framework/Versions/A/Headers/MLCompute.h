//
//  MLCompute.h
//  MLCompute
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <MLCompute/MLCDefines.h>
#import <MLCompute/MLCTypes.h>

#import <MLCompute/MLCDevice.h>
#import <MLCompute/MLCTensor.h>
#import <MLCompute/MLCTensorData.h>
#import <MLCompute/MLCTensorParameter.h>
#import <MLCompute/MLCTensorOptimizerDeviceData.h>
#import <MLCompute/MLCGraph.h>
#import <MLCompute/MLCTrainingGraph.h>
#import <MLCompute/MLCInferenceGraph.h>
#import <MLCompute/MLCPlatform.h>

// Descriptors
#import <MLCompute/MLCActivationDescriptor.h>
#import <MLCompute/MLCPoolingDescriptor.h>
#import <MLCompute/MLCConvolutionDescriptor.h>
#import <MLCompute/MLCLossDescriptor.h>
#import <MLCompute/MLCYOLOLossDescriptor.h>
#import <MLCompute/MLCLSTMDescriptor.h>
#import <MLCompute/MLCTensorDescriptor.h>
#import <MLCompute/MLCOptimizerDescriptor.h>
#import <MLCompute/MLCMatMulDescriptor.h>
#import <MLCompute/MLCMultiheadAttentionDescriptor.h>
#import <MLCompute/MLCEmbeddingDescriptor.h>

// Layers
#import <MLCompute/MLCLayer.h>
#import <MLCompute/MLCArithmeticLayer.h>
#import <MLCompute/MLCComparisonLayer.h>
#import <MLCompute/MLCConvolutionLayer.h>
#import <MLCompute/MLCFullyConnectedLayer.h>
#import <MLCompute/MLCDropoutLayer.h>
#import <MLCompute/MLCGramMatrixLayer.h>
#import <MLCompute/MLCActivationLayer.h>
#import <MLCompute/MLCPoolingLayer.h>
#import <MLCompute/MLCBatchNormalizationLayer.h>
#import <MLCompute/MLCInstanceNormalizationLayer.h>
#import <MLCompute/MLCConcatenationLayer.h>
#import <MLCompute/MLCLayerNormalizationLayer.h>
#import <MLCompute/MLCGroupNormalizationLayer.h>
#import <MLCompute/MLCReshapeLayer.h>
#import <MLCompute/MLCSoftmaxLayer.h>
#import <MLCompute/MLCLossLayer.h>
#import <MLCompute/MLCYOLOLossLayer.h>
#import <MLCompute/MLCLSTMLayer.h>
#import <MLCompute/MLCUpsampleLayer.h>
#import <MLCompute/MLCPaddingLayer.h>
#import <MLCompute/MLCTransposeLayer.h>
#import <MLCompute/MLCReductionLayer.h>
#import <MLCompute/MLCMultiheadAttentionLayer.h>
#import <MLCompute/MLCSplitLayer.h>
#import <MLCompute/MLCMatMulLayer.h>
#import <MLCompute/MLCSliceLayer.h>
#import <MLCompute/MLCEmbeddingLayer.h>
#import <MLCompute/MLCSelectionLayer.h>
#import <MLCompute/MLCGatherLayer.h>
#import <MLCompute/MLCScatterLayer.h>

// Optimizers
#import <MLCompute/MLCOptimizer.h>
#import <MLCompute/MLCSGDOptimizer.h>
#import <MLCompute/MLCAdamOptimizer.h>
#import <MLCompute/MLCAdamWOptimizer.h>
#import <MLCompute/MLCRMSPropOptimizer.h>
