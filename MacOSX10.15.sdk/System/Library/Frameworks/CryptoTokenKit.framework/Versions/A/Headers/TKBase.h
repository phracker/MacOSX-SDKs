//
//  TKBase.h
//  Copyright © 2018 Apple. All rights reserved.
//

#ifndef TK_EXTERN
    #ifdef __cplusplus
        #define TK_EXTERN   extern "C" __attribute__((visibility ("default")))
    #else
        #define TK_EXTERN   extern __attribute__((visibility ("default")))
    #endif
#endif
