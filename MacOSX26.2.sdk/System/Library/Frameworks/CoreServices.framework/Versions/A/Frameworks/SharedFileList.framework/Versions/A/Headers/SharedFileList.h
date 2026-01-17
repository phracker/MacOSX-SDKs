//
//  SharedFileList.h
//  SharedFileList
//
//  Copyright (c) 2013 Apple Inc. All rights reserved.
//



#ifndef __SHAREDFILELIST__
#define __SHAREDFILELIST__
#include <TargetConditionals.h>
#if TARGET_OS_OSX || TARGET_OS_MACCATALYST
#include <SharedFileList/LSSharedFileList.h>
#endif // TARGET_OS_OSX || TARGET_OS_MACCATALYST
#endif // __SHAREDFILELIST__
