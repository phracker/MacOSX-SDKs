/* CoreGraphics - CGRenderingBufferProvider.h
 Copyright (c) 2018 Apple Inc.
 All rights reserved. */

#ifndef CGRENDERINGBUFFERPROVIDER_H_
#define CGRENDERINGBUFFERPROVIDER_H_

#include <CoreGraphics/CGBase.h>
#include <CoreFoundation/CoreFoundation.h>

typedef struct CF_BRIDGED_TYPE(id) CGRenderingBufferProvider* CGRenderingBufferProviderRef;

CF_IMPLICIT_BRIDGING_ENABLED

CF_ASSUME_NONNULL_BEGIN

CG_EXTERN CGRenderingBufferProviderRef __nullable CGRenderingBufferProviderCreate(void *__nullable info,
                                                                size_t size,
                                                                void* __nullable(^__nonnull  lockPointer)(void* __nullable info),
                                                                void            (^__nullable unlockPointer)(void* __nullable info, void*  __nonnull pointer),
                                                                void            (^__nullable releaseInfo)(void* __nullable info))
    CF_REFINED_FOR_SWIFT
    API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));

CG_EXTERN CGRenderingBufferProviderRef __nullable CGRenderingBufferProviderCreateWithCFData(CFMutableDataRef data)
    CF_REFINED_FOR_SWIFT
    API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));

CG_EXTERN size_t CGRenderingBufferProviderGetSize(CGRenderingBufferProviderRef provider)
    CF_REFINED_FOR_SWIFT
    API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));

CG_EXTERN void* __nullable CGRenderingBufferLockBytePtr(CGRenderingBufferProviderRef provider)
    CF_REFINED_FOR_SWIFT
    API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));

CG_EXTERN void CGRenderingBufferUnlockBytePtr(CGRenderingBufferProviderRef provider)
    CF_REFINED_FOR_SWIFT
    API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));

CG_EXTERN CFTypeID CGRenderingBufferProviderGetTypeID(void)
    CF_REFINED_FOR_SWIFT
    API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));

CF_ASSUME_NONNULL_END

CF_IMPLICIT_BRIDGING_DISABLED

#endif /* CGRENDERINGBUFFERPROVIDER_H_ */
