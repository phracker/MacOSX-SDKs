//
//  NSFileProviderDefines.h
//  FileProvider
//
//  Copyright © 2017-2020 Apple Inc. All rights reserved.
//

#ifndef PREPROCESS_AVAILABILITY_MACROS

// original API
#define FILEPROVIDER_CLASS_AVAILABILITY API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, macCatalyst) API_UNAVAILABLE(watchos, tvos)
// iOS API with file enumeration
#define FILEPROVIDER_API_AVAILABILITY_V2 API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, macCatalyst) API_UNAVAILABLE(watchos, tvos)
// iOS API with file enumeration and macOS API with FPFS
#define FILEPROVIDER_API_AVAILABILITY_V2_V3 API_AVAILABLE(ios(11.0), macos(11.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos)
// macOS API with FPFS
#define FILEPROVIDER_API_AVAILABILITY_V3 API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(watchos, tvos) API_UNAVAILABLE(ios, macCatalyst)
// macOS API with first revision of FPFS
#define FILEPROVIDER_API_AVAILABILITY_V3_1 API_AVAILABLE(macos(11.3)) API_UNAVAILABLE(watchos, tvos) API_UNAVAILABLE(ios, macCatalyst)

#else
// This file intentionally left blank.
#endif
