//
//  NSFileProviderDefines.h
//  FileProvider
//
//  Copyright © 2017-2020 Apple Inc. All rights reserved.
//

// original API
#define FILEPROVIDER_API_AVAILABILITY_V1 API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, macCatalyst) API_UNAVAILABLE(watchos, tvos)
// original API that made it to macOS
#define FILEPROVIDER_API_AVAILABILITY_V1_V2_V3 API_AVAILABLE(ios(8.0), macos(11.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos)
// iOS API with file enumeration
#define FILEPROVIDER_API_AVAILABILITY_V2 API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, macCatalyst) API_UNAVAILABLE(watchos, tvos)
// iOS API with file enumeration and macOS API with FPFS
#define FILEPROVIDER_API_AVAILABILITY_V2_V3 API_AVAILABLE(ios(11.0), macos(11.0)) API_UNAVAILABLE(macCatalyst) API_UNAVAILABLE(watchos, tvos)
// macOS API with FPFS
#define FILEPROVIDER_API_AVAILABILITY_V3 API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(watchos, tvos) API_UNAVAILABLE(ios, macCatalyst)
// macOS API with first revision of FPFS
#define FILEPROVIDER_API_AVAILABILITY_V3_1 API_AVAILABLE(macos(11.3)) API_UNAVAILABLE(watchos, tvos) API_UNAVAILABLE(ios, macCatalyst)
// macOS API with second revision of FPFS
#define FILEPROVIDER_API_AVAILABILITY_V4_0 API_AVAILABLE(macos(12.0)) API_UNAVAILABLE(watchos, tvos) API_UNAVAILABLE(ios, macCatalyst)
// macOS API with third revision of FPFS
#define FILEPROVIDER_API_AVAILABILITY_V4_1 API_AVAILABLE(macos(12.3)) API_UNAVAILABLE(watchos, tvos) API_UNAVAILABLE(ios, macCatalyst)
