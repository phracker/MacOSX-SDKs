//
//  MPSCNNNeuronType.h
//  MPS
//
//  Created by iano on 12/1/16.
//  Copyright © 2016 Apple. All rights reserved.
//

#ifndef MPSCNNNeuronType_h
#define MPSCNNNeuronType_h

#if defined(DOXYGEN) || defined(__METAL_VERSION__)
#    define MPS_SWIFT_NAME(_a)
#    define MPS_ENUM_AVAILABLE_STARTING(...)
typedef enum MPSCNNNeuronType 
#else
#    import <MPSNeuralNetwork/MPSNeuralNetworkTypes.h>
typedef NS_ENUM(int32_t, MPSCNNNeuronType)
#endif
{
    MPSCNNNeuronTypeNone            MPS_ENUM_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0)) MPS_SWIFT_NAME(none) = 0, ///< f(x) = x
    MPSCNNNeuronTypeReLU            MPS_ENUM_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0)), ///< f(x) = x >= 0 ? x : a * x;  rectified linear unit
    MPSCNNNeuronTypeLinear          MPS_ENUM_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0)), ///< f(x) = a * x + b
    MPSCNNNeuronTypeSigmoid         MPS_ENUM_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0)), ///< f(x) = 1 / (1 + e^-x)
    MPSCNNNeuronTypeHardSigmoid     MPS_ENUM_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0)), ///< f(x) = clamp((x * a) + b, 0, 1)
    MPSCNNNeuronTypeTanH            MPS_ENUM_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0)), ///< f(x) = a * tanh(b * x)
    MPSCNNNeuronTypeAbsolute        MPS_ENUM_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0)), ///< f(x) = fabs(x)
    MPSCNNNeuronTypeSoftPlus        MPS_ENUM_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0)), ///< f(x) = a * log(1 + e^(b * x))
    MPSCNNNeuronTypeSoftSign        MPS_ENUM_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0)), ///< f(x) = x / (1 + abs(x))
    MPSCNNNeuronTypeELU             MPS_ENUM_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0)), ///< f(x) = x >= 0 ? x : a * (exp(x) - 1); exponential linear unit
    MPSCNNNeuronTypePReLU           MPS_ENUM_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0)), ///< Same as ReLU except parameter a is per channel; parameterized rectified linear unit
    MPSCNNNeuronTypeReLUN           MPS_ENUM_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0)), ///< f(x) = min((x >= 0 ? x : a * x), b); clamped rectified liniear unit
    MPSCNNNeuronTypePower           MPS_ENUM_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), tvos(11.3)), ///< f(x) = (a * x + b) ^ c
    MPSCNNNeuronTypeExponential     MPS_ENUM_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), tvos(11.3)), ///< f(x) = c ^ (a * x + b)
    MPSCNNNeuronTypeLogarithm       MPS_ENUM_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), tvos(11.3)), ///< f(x) = log_c(a * x + b)
    
    // must be last
    MPSCNNNeuronTypeCount           MPS_ENUM_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0)), ///< holds the number of MPSCNNNeuronTypes
}
#if defined(DOXYGEN) || defined(__METAL_VERSION__)
    MPSCNNNeuronType
#endif
;

#endif /* MPSCNNNeuronType_h */
