//
//  SHDefines.h
//  ShazamKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#include <TargetConditionals.h>

#ifndef SHDEFINES_H
#define SHDEFINES_H

#ifdef __cplusplus

#define SH_EXPORT extern "C" __attribute__((visibility ("default")))

#ifndef SH_EXPORT_WITH_FULL_SDK

#define SH_EXPORT_WITH_FULL_SDK extern "C" __attribute__((visibility ("default")))

#endif

#else

#define SH_EXPORT extern __attribute__((visibility ("default")))

#ifndef SH_EXPORT_WITH_FULL_SDK

#define SH_EXPORT_WITH_FULL_SDK extern __attribute__((visibility ("default")))

#endif

#endif

#endif /* SHDEFINES_H */
