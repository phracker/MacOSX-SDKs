//
//  EXMacros.h
//  ExtensionFoundation
//

#ifndef EXMacros_h
#define EXMacros_h

#if defined(__cplusplus)
#define EXTENSIONKIT_EXTERN __attribute__((visibility("default"))) extern "C"
#else
#define EXTENSIONKIT_EXTERN __attribute__((visibility("default"))) extern
#endif

#define EXTENSIONKIT_EXPORT EXTENSIONKIT_EXTERN
#define EXTENSIONKIT_IMPORT EXTENSIONKIT_EXTERN


#import <os/availability.h>


#endif /* EXMacros_h */
