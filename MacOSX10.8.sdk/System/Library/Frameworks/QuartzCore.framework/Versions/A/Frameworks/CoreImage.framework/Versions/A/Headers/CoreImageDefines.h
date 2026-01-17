/* CoreImage - CoreImageDefines.h
 
 Copyright (c) 2009 Apple Computer, Inc.
 All rights reserved. */

#ifndef COREIMAGEDEFINES_H_JUPUTD8M
#define COREIMAGEDEFINES_H_JUPUTD8M


#import "AvailabilityMacros.h"



#ifdef __cplusplus
# define CORE_IMAGE_EXPORT extern "C" __attribute__((visibility("default")))
#else
# define CORE_IMAGE_EXPORT extern __attribute__((visibility("default")))
#endif

#define CORE_IMAGE_CLASS_EXPORT __attribute__((visibility("default")))




#endif /* end of include guard: COREIMAGEDEFINES_H_JUPUTD8M */
