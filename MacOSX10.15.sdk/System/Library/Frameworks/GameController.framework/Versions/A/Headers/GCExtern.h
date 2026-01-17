//
//  GCExtern.h
//  GameController
//
//  Copyright (c) 2017 Apple Inc. All rights reserved.
//

#ifdef __cplusplus
#define GAMECONTROLLER_EXTERN		extern "C" __attribute__((visibility ("default")))
#else
#define GAMECONTROLLER_EXTERN	        extern __attribute__((visibility ("default")))
#endif

#define GAMECONTROLLER_EXPORT API_AVAILABLE(macos(10.9), ios(7.0), tvos(7.0))
