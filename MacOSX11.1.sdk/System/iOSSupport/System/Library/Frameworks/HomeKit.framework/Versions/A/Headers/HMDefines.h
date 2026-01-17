//
//  HMDefines.h
//  HomeKit
//
//      Copyright (c) 2013-2015 Apple Inc. All rights reserved.
//

#ifndef HM_EXTERN
#ifdef __cplusplus
#define HM_EXTERN   extern "C" __attribute__((visibility ("default")))
#else
#define HM_EXTERN   extern __attribute__((visibility ("default")))
#endif
#endif

/*!
 * @brief A generic handler for callbacks containing a single error parameter.
 */
typedef void (^HMErrorBlock)(NSError * _Nullable error) API_AVAILABLE(ios(13.0), watchos(6.0), tvos(13.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);
