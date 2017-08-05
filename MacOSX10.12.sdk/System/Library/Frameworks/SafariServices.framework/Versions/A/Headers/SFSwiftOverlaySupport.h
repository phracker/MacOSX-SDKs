//
//  SFSwiftOverlaySupport.h
//  SafariServices
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

// This header exists solely for use by the Swift overlay.
// Do not import this header or rely on it. It might not be present in a future version of the SDK.

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

extern void* _SFSafariServicesAvailable __attribute__((visibility("default"))) __attribute__((weak_import)) __attribute__((availability(swift, unavailable)));

#ifdef __cplusplus
}
#endif
