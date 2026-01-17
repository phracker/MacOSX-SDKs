//
//  CLEssentialsAvailability.h
//  LocationEssentials
//
//  Created by Ilya Veygman on 2/6/25.
//

#pragma once

#ifdef __cplusplus
#define CLES_EXPORT extern "C" __attribute__((visibility ("default")))
#else
#define CLES_EXPORT extern __attribute__((visibility ("default")))
#endif
