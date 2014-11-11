//
//  MCError.h
//  MultipeerConnectivity
//
//  Copyright (c) 2013 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#ifndef MC_EXTERN
#ifdef __cplusplus
#define MC_EXTERN   extern "C" __attribute__((visibility ("default")))
#else
#define MC_EXTERN   extern __attribute__((visibility ("default")))
#endif
#endif

#define MC_EXTERN_CLASS    __attribute__((visibility("default")))

#ifndef MC_EXTERN_WEAK
#define MC_EXTERN_WEAK  MC_EXTERN __attribute__((weak_import))
#endif

MC_EXTERN_WEAK NSString * const MCErrorDomain;

typedef NS_ENUM(NSInteger, MCErrorCode) {
    MCErrorUnknown                      = 0,
    MCErrorNotConnected                 = 1,
    MCErrorInvalidParameter             = 2,
    MCErrorUnsupported                  = 3,
    MCErrorTimedOut                     = 4,
    MCErrorCancelled                    = 5,
    MCErrorUnavailable                  = 6,
} NS_ENUM_AVAILABLE(10_10,7_0);
