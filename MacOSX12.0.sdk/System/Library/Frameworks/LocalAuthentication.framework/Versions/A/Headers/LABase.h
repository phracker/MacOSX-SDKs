//
//  LABase.h
//  LocalAuthentication
//
//  Copyright © 2018 Apple. All rights reserved.
//

#ifndef LA_EXPORT
    #define LA_EXPORT __attribute__((visibility("default")))
#endif

#ifndef LA_EXTERN
    #ifdef __cplusplus
        #define LA_EXTERN extern "C" __attribute__((visibility("default")))
    #else
        #define LA_EXTERN extern __attribute__((visibility("default")))
    #endif
#endif
