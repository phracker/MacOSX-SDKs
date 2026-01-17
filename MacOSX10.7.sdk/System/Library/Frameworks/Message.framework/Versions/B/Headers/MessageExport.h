//
//  MessageExport.h
//  Message
//  
//  Copyright © 1999–2011 Apple Inc. All rights reserved.
//

#include <TargetConditionals.h>

#if defined(__cplusplus)
#define MESSAGE_EXTERN extern "C"
#else
#define MESSAGE_EXTERN extern
#endif

#if TARGET_OS_WIN32
    #undef MESSAGE_EXTERN
#else
    #ifdef __MWERKS__
        #define MESSAGE_EXPORT __declspec(export) MESSAGE_EXTERN
    #else
        #define MESSAGE_EXPORT MESSAGE_EXTERN
    #endif
    
    #define MESSAGE_IMPORT MESSAGE_EXTERN
#endif
