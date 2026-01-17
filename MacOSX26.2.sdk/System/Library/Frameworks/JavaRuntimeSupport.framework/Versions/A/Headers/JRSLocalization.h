//
//  JRSLocalization.h
//  Copyright 2008-2011 Apple Inc. All rights reserved.
//

#import <JavaRuntimeSupport/JRSDefines.h>

#ifdef __x86_64__

JRS_BEGIN_DECLS

JRS_EXPORT char *JRSCopyPrimaryLanguage(void) JRS_DEPRECATED_2020_7;
JRS_EXPORT char *JRSCopyCanonicalLanguageForPrimaryLanguage(const char *primaryLanguage) JRS_DEPRECATED_2020_7;
JRS_EXPORT void JRSSetDefaultLocalization(const char *primaryLanguage) JRS_DEPRECATED_2020_7;

JRS_END_DECLS

#endif /* __x86_64__ */
