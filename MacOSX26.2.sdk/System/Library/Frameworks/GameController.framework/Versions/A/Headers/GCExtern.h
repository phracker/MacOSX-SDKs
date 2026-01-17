//
//  GCExtern.h
//  GameController
//
//  Copyright (c) 2017 Apple Inc. All rights reserved.
//

#if !defined(GAMECONTROLLER_EXTERN)
#   if defined(__cplusplus)
#       define GAMECONTROLLER_EXTERN extern "C"
#   else
#       define GAMECONTROLLER_EXTERN extern
#   endif
#endif

#if !defined(GAMECONTROLLER_EXPORT)
#   define GAMECONTROLLER_EXPORT __attribute__((visibility("default"))) GAMECONTROLLER_EXTERN
#endif



