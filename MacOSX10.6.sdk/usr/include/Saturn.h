/*
 *  Saturn.h
 *  Saturn
 *
 *  Copyright (c) 2002-2003 Apple Computer, Inc., all rights reserved.
 *
 */

#ifndef __cplusplus
#include <stdbool.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

void startSaturn (void);
void stopSaturn (void);
void initSaturn (const char *path);


#ifdef __cplusplus
}
#endif

