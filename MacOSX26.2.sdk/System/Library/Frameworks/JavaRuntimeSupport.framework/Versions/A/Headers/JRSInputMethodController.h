//
//  JRSInputMethodController.h
//  Copyright 2011 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <JavaRuntimeSupport/JRSDefines.h>

JRS_BEGIN_DECLS

JRS_EXPORT
@interface JRSInputMethodController : NSObject
+ (JRSInputMethodController *) controller;
- (NSArray *) availableInputMethodLocales;
- (NSString *) currentInputMethodName;
- (NSString *) currentInputMethodLocale;
- (void) setCurrentInputMethodForLocale:(NSString *)theLocale;
@end

JRS_END_DECLS
