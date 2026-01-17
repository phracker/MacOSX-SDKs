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

#ifndef CK_HIDDEN
#define CK_HIDDEN   __attribute__((visibility("hidden")))
#endif

#ifndef CK_EXTERN_HIDDEN
#ifdef __cplusplus
#define CK_EXTERN_HIDDEN   extern "C" __attribute__((visibility ("hidden")))
#else
#define CK_EXTERN_HIDDEN   extern __attribute__((visibility ("hidden")))
#endif
#endif
