//
//  MPSCNNTypes.h
//  MPS
//
//  Created by Anna Tikhonova on 10/20/17.
//  Copyright © 2017 Apple. All rights reserved.
//

#ifndef MPSCNNTypes_h
#define MPSCNNTypes_h

#pragma mark -
#pragma mark MPSCNNLossType

/*!
 * Supported loss filter types (see MPSCNNLoss.h for more information):
 */
#if defined(DOXYGEN) || defined(__METAL_VERSION__)
#    define MPS_SWIFT_NAME(_a)
#    define MPS_ENUM_AVAILABLE_STARTING(...)
typedef enum MPSCNNLossType
#else
typedef NS_ENUM(uint32_t, MPSCNNLossType)
#endif
{
    MPSCNNLossTypeMeanAbsoluteError             MPS_ENUM_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3))
                                                                                  MPS_SWIFT_NAME(meanAbsoluteError) = 0,  // Mean Absolute Error
    MPSCNNLossTypeMeanSquaredError              MPS_ENUM_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3)),      // Mean Squared Error
    MPSCNNLossTypeSoftMaxCrossEntropy           MPS_ENUM_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3)),      // SoftMax Cross Entropy
    MPSCNNLossTypeSigmoidCrossEntropy           MPS_ENUM_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3)),      // Sigmoid Cross Entropy
    MPSCNNLossTypeCategoricalCrossEntropy       MPS_ENUM_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3)),      // Categorical Cross Entropy
    MPSCNNLossTypeHinge                         MPS_ENUM_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3)),      // Hinge
    MPSCNNLossTypeHuber                         MPS_ENUM_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3)),      // Huber
    MPSCNNLossTypeCosineDistance                MPS_ENUM_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3)),      // Cosine Distance
    MPSCNNLossTypeLog                           MPS_ENUM_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3)),      // Log
    MPSCNNLossTypeKullbackLeiblerDivergence     MPS_ENUM_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3)),      // Kullback-Leibler Divergence
    
    // Must be last
    MPSCNNLossTypeCount // Holds the number of MPSCNNLossTypes
}
#if defined(DOXYGEN) || defined(__METAL_VERSION__)
MPSCNNLossType
#endif
;


#pragma mark -
#pragma mark MPSCNNReductionType

#if defined(DOXYGEN) || defined(__METAL_VERSION__)
#    define MPS_SWIFT_NAME(_a)
#    define MPS_ENUM_AVAILABLE_STARTING(...)
typedef enum MPSCNNReductionType
#else
typedef NS_ENUM(int32_t, MPSCNNReductionType)
#endif
{
    MPSCNNReductionTypeNone                     MPS_ENUM_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3))
                                                                                               MPS_SWIFT_NAME(none) = 0,  // No reduction
    MPSCNNReductionTypeSum                      MPS_ENUM_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3)),      // Sum
    MPSCNNReductionTypeMean                     MPS_ENUM_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3)),      // Mean
    MPSCNNReductionTypeSumByNonZeroWeights      MPS_ENUM_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3)),      // Sum divided by the number of non-zero weights
    
    // Must be last
    MPSCNNReductionTypeCount // Holds the number of MPSCNNReductionTypes
}
#if defined(DOXYGEN) || defined(__METAL_VERSION__)
MPSCNNReductionType
#endif
;

#endif /* MPSCNNTypes_h */
