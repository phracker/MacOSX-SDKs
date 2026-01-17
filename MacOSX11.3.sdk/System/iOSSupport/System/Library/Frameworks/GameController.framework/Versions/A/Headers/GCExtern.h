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
