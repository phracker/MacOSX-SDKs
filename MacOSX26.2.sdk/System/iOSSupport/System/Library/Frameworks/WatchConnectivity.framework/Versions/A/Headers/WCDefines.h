//
//  WCDefines.h
//  WatchConnectivity
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#ifndef WC_EXTERN
#ifdef __cplusplus
#define WC_EXTERN   extern "C" __attribute__((visibility ("default")))
#else
#define WC_EXTERN   extern __attribute__((visibility ("default")))
#endif
#endif
