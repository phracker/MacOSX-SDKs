/* CoreImage - CoreImageDefines.h
 
 Copyright (c) 2009 Apple, Inc.
 All rights reserved. */

#ifndef COREIMAGEDEFINES_H
#define COREIMAGEDEFINES_H


#import "AvailabilityMacros.h"



#ifdef __cplusplus
# define CORE_IMAGE_EXPORT extern "C" __attribute__((visibility("default")))
#else
# define CORE_IMAGE_EXPORT extern __attribute__((visibility("default")))
#endif

#define CORE_IMAGE_CLASS_EXPORT __attribute__((visibility("default")))



#endif /* COREIMAGEDEFINES_H */
