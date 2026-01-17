//
//  JRSProperties.h
//  Copyright 2008-2011 Apple Inc. All rights reserved.
//

#import <JavaRuntimeSupport/JRSDefines.h>

#ifdef __x86_64__

JRS_BEGIN_DECLS

JRS_EXPORT char *JRSCopyOSName(void) JRS_DEPRECATED_2020_7;
JRS_EXPORT char *JRSCopyOSVersion(void) API_DEPRECATED_WITH_REPLACEMENT("[[NSProcessInfo processInfo] operatingSystemVersion]", macos(10.10, 11.0));
JRS_EXPORT char *JRSCopyOSJavaSupportVersion(void) JRS_DEPRECATED_2020;

JRS_END_DECLS

#endif /* __x86_64__ */
