/*
 *	CBDefines.h
 *	CoreBluetooth
 *
 *	Copyright 2011 Apple, Inc. All rights reserved.
 */

#ifndef CB_EXTERN
#ifdef __cplusplus
#define CB_EXTERN extern "C" __attribute__((visibility ("default")))
#else
#define CB_EXTERN extern __attribute__((visibility ("default")))
#endif
#endif

#define CB_EXTERN_CLASS __attribute__((visibility("default")))
