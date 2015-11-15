/* CoreImage - CoreImageDefines.h
 
 Copyright (c) 2014 Apple, Inc.
 All rights reserved. */

#ifndef COREIMAGEDEFINES_H
#define COREIMAGEDEFINES_H


#include <TargetConditionals.h>

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#if TARGET_OS_IPHONE
#include <CoreGraphics/CoreGraphics.h>
#else
#include <ApplicationServices/ApplicationServices.h>
#endif

#ifdef __cplusplus
 #define CI_EXTERN_C_BEGIN  extern "C" {
 #define CI_EXTERN_C_END  }
#else
 #define CI_EXTERN_C_BEGIN
 #define CI_EXTERN_C_END
#endif

#ifdef __cplusplus
# define CORE_IMAGE_EXPORT extern "C" __attribute__((visibility("default")))
#else
# define CORE_IMAGE_EXPORT extern __attribute__((visibility("default")))
#endif

#define CORE_IMAGE_CLASS_EXPORT __attribute__((visibility("default")))


#endif /* COREIMAGEDEFINES_H */
