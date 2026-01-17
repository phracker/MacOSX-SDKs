//
//  BABase.h
//  BackgroundAssets
//
//  Copyright (c) 2022, Apple Inc.
//  All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

#ifndef BA_EXPORT
    #ifdef __cplusplus
        #define BA_EXPORT   extern "C" __attribute__((visibility ("default")))
    #else
        #define BA_EXPORT   extern __attribute__((visibility ("default")))
    #endif
#endif
#ifndef BA_HIDDEN
    #ifdef __cplusplus
        #define BA_HIDDEN   "C" __attribute__((visibility("hidden")))
    #else
        #define BA_HIDDEN   __attribute__((visibility("hidden")))
    #endif
#endif
#ifndef BA_HIDDEN_EXTERN
    #ifdef __cplusplus
        #define BA_HIDDEN_EXTERN  extern "C" __attribute__((visibility("hidden")))
    #else
        #define BA_HIDDEN_EXTERN  extern __attribute__((visibility("hidden")))
    #endif
#endif

NS_ASSUME_NONNULL_END
