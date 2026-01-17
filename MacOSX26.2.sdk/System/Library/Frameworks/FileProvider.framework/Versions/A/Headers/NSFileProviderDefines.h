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
// iOS API with FPFS
#define FILEPROVIDER_API_AVAILABILITY_V3_IOS API_AVAILABLE(macos(11.0), ios(16.0)) API_UNAVAILABLE(watchos, tvos) API_UNAVAILABLE(macCatalyst)
// macOS API with first revision of FPFS
#define FILEPROVIDER_API_AVAILABILITY_V3_1 API_AVAILABLE(macos(11.3)) API_UNAVAILABLE(watchos, tvos) API_UNAVAILABLE(ios, macCatalyst)
// iOS API with first revision of FPFS
#define FILEPROVIDER_API_AVAILABILITY_V3_1_IOS API_AVAILABLE(macos(11.3), ios(16.0)) API_UNAVAILABLE(watchos, tvos) API_UNAVAILABLE(macCatalyst)
// macOS API with second revision of FPFS
#define FILEPROVIDER_API_AVAILABILITY_V4_0 API_AVAILABLE(macos(12.0)) API_UNAVAILABLE(watchos, tvos) API_UNAVAILABLE(ios, macCatalyst)
// iOS API with second revision of FPFS
#define FILEPROVIDER_API_AVAILABILITY_V4_0_IOS API_AVAILABLE(macos(12.0), ios(16.0)) API_UNAVAILABLE(watchos, tvos) API_UNAVAILABLE(macCatalyst)
// macOS API with third revision of FPFS
#define FILEPROVIDER_API_AVAILABILITY_V4_1 API_AVAILABLE(macos(12.3)) API_UNAVAILABLE(watchos, tvos) API_UNAVAILABLE(ios, macCatalyst)
// macOS API with the fourth revision of FPFS
#define FILEPROVIDER_API_AVAILABILITY_V5_0 API_AVAILABLE(macos(13.0)) API_UNAVAILABLE(watchos, tvos) API_UNAVAILABLE(ios, macCatalyst)
// iOS API with the fourth revision of FPFS
#define FILEPROVIDER_API_AVAILABILITY_V5_0_IOS API_AVAILABLE(macos(13.0), ios(16.0)) API_UNAVAILABLE(watchos, tvos) API_UNAVAILABLE(macCatalyst)
// macOS/iOS API
#define FILEPROVIDER_API_AVAILABILITY_V2_V5 API_AVAILABLE(macos(13.0), ios(16.0)) API_UNAVAILABLE(watchos, tvos) API_UNAVAILABLE(macCatalyst)
// macOS API with the fifth revision of FPFS
#define FILEPROVIDER_API_AVAILABILITY_V5_1 API_AVAILABLE(macos(13.4)) API_UNAVAILABLE(ios, watchos, tvos) API_UNAVAILABLE(macCatalyst)

#define FILEPROVIDER_API_AVAILABILITY_V6_0_IOS API_AVAILABLE(macos(14.1), ios(17.1)) API_UNAVAILABLE(watchos, tvos) API_UNAVAILABLE(macCatalyst)

#define FILEPROVIDER_API_AVAILABILITY_V7_0_IOS API_AVAILABLE(macos(14.4), ios(17.4)) API_UNAVAILABLE(watchos, tvos) API_UNAVAILABLE(macCatalyst)

#define FILEPROVIDER_API_AVAILABILITY_EXTERNAL_VOLUME API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(watchos, tvos) API_UNAVAILABLE(ios, macCatalyst)

// macOS API for support for known folders
#define FILEPROVIDER_API_AVAILABILITY_DESKTOP API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(watchos, tvos) API_UNAVAILABLE(ios, macCatalyst)

#define FILEPROVIDER_API_AVAILABILITY_V8_0_IOS API_AVAILABLE(macos(15.0), ios(18.0)) API_UNAVAILABLE(watchos, tvos) API_UNAVAILABLE(macCatalyst)

#define FILEPROVIDER_API_AVAILABILITY_FEEDBACK API_AVAILABLE(macos(15.4)) API_UNAVAILABLE(watchos, tvos) API_UNAVAILABLE(ios, macCatalyst)

#define FILEPROVIDER_API_AVAILABILITY_SEARCH API_AVAILABLE(macos(26.0)) API_UNAVAILABLE(watchos, tvos) API_UNAVAILABLE(ios, macCatalyst)

#define FILEPROVIDER_API_AVAILABILITY_SYNC_CONTROLS API_AVAILABLE(macos(26.0), ios(26.0)) API_UNAVAILABLE(watchos, tvos) API_UNAVAILABLE(macCatalyst)
