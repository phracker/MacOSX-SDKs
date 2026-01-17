//
//  SRDefines.h
//  SensorKit
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#if !defined(__cplusplus)
#define SR_EXTERN extern __attribute__((visibility("default")))
#else
#define SR_EXTERN extern "C" __attribute__((visibility("default")))
#endif

#if !defined(__cplusplus)
#define SR_EXTERN_HIDDEN extern __attribute__((visibility("hidden")))
#else
#define SR_EXTERN_HIDDEN extern "C" __attribute__((visibility("hidden")))
#endif
