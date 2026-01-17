//
//  MessagesDefines.h
//  Messages
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#ifdef __cplusplus
#define MESSAGES_EXTERN extern "C" __attribute__((visibility("default")))
#else
#define MESSAGES_EXTERN extern __attribute__((visibility("default")))
#endif
