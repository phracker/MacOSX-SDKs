//
//  PlaygroundRuntimeDefines.h
//  LiveExecutionResultsRuntime
//
//  Copyright © 2017-2020 Apple Inc. All rights reserved.
//

#ifndef LER_EXTERN
    #if defined(__cplusplus)
        #define LER_EXTERN extern "C"
    #else
        #define LER_EXTERN extern
    #endif
#endif

#ifndef LER_EXPORT
    #define LER_EXPORT LER_EXTERN
#endif
