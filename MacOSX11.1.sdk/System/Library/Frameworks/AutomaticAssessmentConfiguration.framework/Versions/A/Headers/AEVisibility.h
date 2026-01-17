//
//  AEVisibility.h
//  AutomaticAssessmentConfiguration
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#ifndef AE_HIDDEN
    #ifdef __cplusplus
        #define AE_HIDDEN   extern "C" __attribute__((visibility ("hidden")))
    #else
        #define AE_HIDDEN   extern __attribute__((visibility ("hidden")))
    #endif
#endif

#ifndef AE_VISIBLE
    #ifdef __cplusplus
        #define AE_VISIBLE   extern "C" __attribute__((visibility ("default")))
    #else
        #define AE_VISIBLE   extern __attribute__((visibility ("default")))
    #endif
#endif
