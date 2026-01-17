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

#if TARGET_OS_WIN32
   #if BUILDING_SYNC_SERVICES
      #define SYNCSERVICES_EXPORT SYNCSERVICES_EXTERN __declspec(dllexport)
   #else
      #define SYNCSERVICES_EXPORT SYNCSERVICES_EXTERN __declspec(dllimport)
   #endif

   #if BUILDING_SYNC_SERVICESUI
      #define SYNCSERVICESUI_EXPORT SYNCSERVICES_EXTERN __declspec(dllexport)
   #else
      #define SYNCSERVICESUI_EXPORT SYNCSERVICES_EXTERN __declspec(dllimport)
   #endif

   #define SYNCSERVICES_IMPORT SYNCSERVICES_EXTERN __declspec(dllimport)
   #define SYNCSERVICES_EXPORT_DEFINITION __declspec(dllexport)

   #define SYNCSERVICESUI_IMPORT SYNCSERVICES_EXTERN __declspec(dllimport)
   #define SYNCSERVICESUI_EXPORT_DEFINITION __declspec(dllexport)

#elif TARGET_OS_MAC

   #define SYNCSERVICES_IMPORT SYNCSERVICES_EXTERN
   #define SYNCSERVICES_EXPORT SYNCSERVICES_EXTERN
   #define SYNCSERVICES_EXPORT_DEFINITION

   #define SYNCSERVICESUI_IMPORT SYNCSERVICES_EXTERN
   #define SYNCSERVICESUI_EXPORT SYNCSERVICES_EXTERN
   #define SYNCSERVICESUI_EXPORT_DEFINITION
#endif


#endif // H_ISYNCCOMMON
