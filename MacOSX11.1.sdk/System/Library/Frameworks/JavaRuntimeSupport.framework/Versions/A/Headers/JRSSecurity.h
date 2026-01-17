//
//  JRSSecurity.h
//  JavaRuntimeSupport
//
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <JavaRuntimeSupport/JRSDefines.h>

#ifdef __x86_64__

JRS_BEGIN_DECLS

enum {
    JRSSecurityExecutableCodeSignatureMissing                    = 0,   // Unsigned executable
    JRSSecurityExecutableCodeSignatureUnverifiable               = 1,   // Self signed or unverifiable executable
    JRSSecurityExecutableCodeSignatureValidatedThroughTrustedCA  = 2,   // CA signed executable
    JRSSecurityExecutableCodeSignatureExplicitlyTrusted          = 3,   // Signed with White-listed cert
    JRSSecurityExecutableCodeSignatureExplicitlyUntrusted        = 4,   // Signed with Black-listed cert
    JRSSecurityExecutableCodeSignatureExpired                    = 5,   // Signed with Expired cert

};

typedef uint32_t JRSSecurityExecutableCodeSignatureEvaluation;


enum {
    JRSSecurityExecutionPolicyNoPrompt       = 0,   // No need to prompt
    JRSSecurityExecutionPolicyOKPrompt       = 1,   // OK to run but prompt
    JRSSecurityExecutionPolicyWarnPrompt     = 2,   // Warn user of potential issue
    JRSSecurityExecutionPolicyBlockExecution = 3,   // Do not execute
};

typedef uint32_t JRSSecurityExecutionPolicy;

JRS_EXPORT
JRS_DEPRECATED_2020
@interface JRSSecurity : NSObject

+ (JRSSecurityExecutionPolicy)executionPolicyForExecutableCodeSignatureEvaluation:(JRSSecurityExecutableCodeSignatureEvaluation) evaluation;

@end

JRS_END_DECLS

#endif /* __x86_64__ */
