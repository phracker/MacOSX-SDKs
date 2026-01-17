//
// Types.h
// HVFLib
//
// Copyright (c) 2024 Apple Inc. All rights reserved.
//

#ifndef HVF_Types_H
#define HVF_Types_H

#include <stddef.h>
#include <stdint.h>

// Index of a part within an hvgl table or other source
typedef size_t HVFPartIndex;

// An x or y coordinate within the UPM space of a part
typedef double  HVFXYCoord;

// A rotation angle in radians, counterclockwise
typedef double  HVFRotation;

// A value that can be set on an axis, in the range [-1.0, 1.0]
typedef double  HVFAxisValue;

// A translation that can be applied to a subpart
struct HVFTranslation {
    HVFXYCoord  dx;
    HVFXYCoord  dy;
};
typedef struct HVFTranslation HVFTranslation;

// The version of the hvgl table the scaler supports
struct HVFTableVersion {
    uint16_t major;
    uint16_t minor;
};
typedef struct HVFTableVersion HVFTableVersion;

// The version of the HVF library
struct HVFLibraryVersion {
    uint16_t major;
    uint16_t minor;
    uint16_t patch;
};
typedef struct HVFLibraryVersion HVFLibraryVersion;

#endif // HVF_Types_H
