//
//  SNDefines.h
//  SoundAnalysis
//
//  Copyright © 2019 Apple. All rights reserved.
//

#ifndef SNDEFINES_H
#define SNDEFINES_H

#ifdef __cplusplus
# define SN_EXPORT extern "C" __attribute__((visibility("default")))
#else
# define SN_EXPORT extern __attribute__((visibility("default")))
#endif

#endif /* SNDEFINES_H */
