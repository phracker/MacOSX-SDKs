//
//  JRSLocalization.h
//  Copyright 2008 Apple Inc. All rights reserved.
//

#import <Cocoa/Cocoa.h>

char *JRSCopyPrimaryLanguage();
char *JRSCopyCanonicalLanguageForPrimaryLanguage(const char *primaryLanguage);
void JRSSetDefaultLocalization(const char *primaryLanguage);
