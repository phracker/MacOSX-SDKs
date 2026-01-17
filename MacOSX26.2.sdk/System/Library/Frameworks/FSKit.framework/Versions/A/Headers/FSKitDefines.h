//
//  Copyright (c) 2023 Apple Inc.  All rights reserved.
//
//  Header.h
//  FSKit
//

#ifndef FSKitDefines_h
#define FSKitDefines_h

#ifdef __cplusplus
# define FS_EXTERN extern "C"
#else
# define FS_EXTERN extern
#endif

#ifndef FS_EXPORT
# ifndef FS_SUPPORTED_VISIBILITY
#  if FS_UNSUPPORTED_PLATFORM
#   define FS_SUPPORTED_VISIBILITY
#  else
#   define FS_SUPPORTED_VISIBILITY __attribute__((visibility("default")))
#  endif
# endif
#define FS_EXPORT FS_EXTERN FS_SUPPORTED_VISIBILITY
#endif

#ifndef FS_EXPORT_INTERNAL
#define FS_EXPORT_INTERNAL FS_EXTERN __attribute__((visibility("internal")))
#endif

#ifndef FS_ALWAYS_EXPORT
#define FS_ALWAYS_EXPORT FS_EXTERN __attribute__((visibility("default")))
#endif

// original API
#define FSKIT_API_AVAILABILITY_V1 API_AVAILABLE(macos(15.4)) \
    API_UNAVAILABLE(ios, visionos) API_UNAVAILABLE(watchos, tvos)
// Unavailable in original API
#define FSKIT_API_UNAVAILABLE_V1 API_UNAVAILABLE(macos, ios, visionos) API_UNAVAILABLE(watchos, tvos)

// macOS 16 API
#define FSKIT_API_AVAILABILITY_V2 API_AVAILABLE(macos(26.0)) \
    API_UNAVAILABLE(ios, visionos) API_UNAVAILABLE(watchos, tvos)

#endif /* FSKitDefines_h */
