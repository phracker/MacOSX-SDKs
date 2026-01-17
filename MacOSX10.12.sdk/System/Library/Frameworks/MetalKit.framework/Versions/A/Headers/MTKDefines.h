//
//  MTKDefines.h
//  MetalKit
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Availability.h>
#import <TargetConditionals.h>

#define MTK_EXPORT __attribute__((visibility ("default")))

#define MTK_INLINE static __inline__

#ifdef __cplusplus
#define MTK_EXTERN extern "C" MTK_EXPORT
#else
#define MTK_EXTERN extern MTK_EXPORT
#endif
