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
#else
#define SH_EXPORT extern __attribute__((visibility ("default")))
#endif

#endif /* SHDEFINES_H */
