//
//  JRSInputMethodController.h
//  Copyright 2011 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface JRSInputMethodController : NSObject
+ (JRSInputMethodController *) controller;
- (NSArray *) availableInputMethodLocales;
- (NSString *) currentInputMethodName;
- (NSString *) currentInputMethodLocale;
- (void) setCurrentInputMethodForLocale:(NSString *)theLocale;
@end
