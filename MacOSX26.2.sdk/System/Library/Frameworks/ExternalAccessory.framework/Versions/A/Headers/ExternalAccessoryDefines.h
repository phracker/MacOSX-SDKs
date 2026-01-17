//
//  ExternalAccessoryDefines.h
//  ExternalAccessory
//
//  Copyright (c) 2008-2015 Apple Inc. All rights reserved.
//

#ifdef __cplusplus
#define EA_EXTERN	 extern "C" __attribute__((visibility ("default")))
#else // #ifdef __cplusplus
#define EA_EXTERN	 extern __attribute__((visibility ("default")))
#endif // #ifdef __cplusplus

#define EA_EXTERN_CLASS __attribute__((visibility("default")))
#define EA_EXTERN_CLASS_AVAILABLE(version) __attribute__((visibility("default"))) NS_CLASS_AVAILABLE(NA, version)
