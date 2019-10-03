/*
 * SyncServices -- ISyncCommon.h
 * Copyright (c) 2004, Apple Computer, Inc.  All rights reserved.
 */

#ifndef H_ISYNCCOMMON
#define H_ISYNCCOMMON

#import <Foundation/Foundation.h>

#if defined(__cplusplus)
   #define SYNCSERVICES_EXTERN extern "C"
#else
   #define SYNCSERVICES_EXTERN extern
#endif

#if TARGET_OS_MAC

   #define SYNCSERVICES_IMPORT SYNCSERVICES_EXTERN
   #define SYNCSERVICES_EXPORT SYNCSERVICES_EXTERN
   #define SYNCSERVICES_EXPORT_DEFINITION

   #define SYNCSERVICESUI_IMPORT SYNCSERVICES_EXTERN
   #define SYNCSERVICESUI_EXPORT SYNCSERVICES_EXTERN
   #define SYNCSERVICESUI_EXPORT_DEFINITION
#endif


#endif // H_ISYNCCOMMON
