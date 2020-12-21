//
//  PGDefines.h
//  ParavirtualizedGraphics
//
//  Copyright © 2018-2020 Apple Inc. All rights reserved.
//

#ifndef PGDefines_h
#define PGDefines_h

#define PG_EXPORT __attribute__((visibility ("default")))
#ifdef __cplusplus
#define PG_EXTERN extern "C" PG_EXPORT
#else
#define PG_EXTERN extern PG_EXPORT
#endif

#define PG_SUPPORT_EFI 1

#endif /* PGDefines_h */
