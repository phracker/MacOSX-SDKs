/* Vision - VNDefines.h
 
 Copyright (c) 2015 Apple, Inc.
 All rights reserved. */

#ifndef VNDEFINES_H
#define VNDEFINES_H

#ifdef __cplusplus
#define VN_EXTERN_C_BEGIN  extern "C" {
#define VN_EXTERN_C_END  }
#else
#define VN_EXTERN_C_BEGIN
#define VN_EXTERN_C_END
#endif

#ifdef __cplusplus
# define VN_EXPORT extern "C" __attribute__((visibility("default")))
#else
# define VN_EXPORT extern __attribute__((visibility("default")))
#endif


#endif /* VNDEFINES_H */
