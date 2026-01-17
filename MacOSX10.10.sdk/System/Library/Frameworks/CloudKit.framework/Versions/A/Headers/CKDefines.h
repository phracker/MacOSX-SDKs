//
//  CKDefines.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#ifndef CK_EXTERN
#ifdef __cplusplus
#define CK_EXTERN   extern "C" __attribute__((visibility ("default")))
#else
#define CK_EXTERN   extern __attribute__((visibility ("default")))
#endif
#endif


#if DEBUG
    #define CK_UNIT_TESTS_AVAILABLE NS_CLASS_AVAILABLE(10_10, 8_0)
    #define CK_UNIT_TESTS_EXTERN CK_EXTERN
#else
    #define CK_UNIT_TESTS_AVAILABLE NS_CLASS_AVAILABLE(10_10, 8_0)
    #define CK_UNIT_TESTS_EXTERN CK_EXTERN
#endif
