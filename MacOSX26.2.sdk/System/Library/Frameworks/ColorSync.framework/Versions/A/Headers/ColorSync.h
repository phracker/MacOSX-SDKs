/*
 * ColorSync - ColorSync.h
 * Copyright (c)  2008 Apple Inc.
 * All rights reserved.
 */

#ifndef __COLORSYNC_MAIN_HEADER__
#define __COLORSYNC_MAIN_HEADER__

#include <ColorSync/ColorSyncBase.h>
#include <ColorSync/ColorSyncProfile.h>
#include <ColorSync/ColorSyncTransform.h>
    #include <ColorSync/ColorSyncCMM.h>
    #include <ColorSync/ColorSyncDevice.h>

#define COLORSYNC_API_VERSION 0x1A010000L
// 26.1.0.0 BCD; uint32_t BCD = (uint32_t)((majorOS << 24) | (minorOS << 16) | (dotOS << 8) | (API version & 0xFF));

CSEXTERN uint32_t ColorSyncAPIVersion(void);

#endif /* __COLORSYNC_MAIN_HEADER__ */

