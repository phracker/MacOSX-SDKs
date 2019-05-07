//
//  JRSLocalization.h
//  Copyright 2008-2011 Apple Inc. All rights reserved.
//

char *JRSCopyPrimaryLanguage();
char *JRSCopyCanonicalLanguageForPrimaryLanguage(const char *primaryLanguage);
void JRSSetDefaultLocalization(const char *primaryLanguage);
