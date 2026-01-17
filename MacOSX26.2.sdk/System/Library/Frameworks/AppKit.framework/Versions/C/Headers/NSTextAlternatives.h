#if !__has_include(<UIFoundation/NSTextAlternatives.h>)
/*
	NSTextAlternatives.h
	Application Kit
	Copyright (c) 2011-2024, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSArray.h>
#import <Foundation/NSNotification.h>
#import <AppKit/AppKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)
#if !TARGET_OS_IPHONE

@class NSString;

API_AVAILABLE(macos(10.8))
@interface NSTextAlternatives : NSObject <NSSecureCoding>

- (instancetype)initWithPrimaryString:(NSString *)primaryString alternativeStrings:(NSArray<NSString *> *)alternativeStrings;

@property (readonly, copy) NSString *primaryString;
@property (readonly, copy) NSArray<NSString *> *alternativeStrings;

- (void)noteSelectedAlternativeString:(NSString *)alternativeString;

@end

APPKIT_EXTERN NSNotificationName NSTextAlternativesSelectedAlternativeStringNotification API_AVAILABLE(macos(10.8)); // @"NSAlternativeString"



#endif // !TARGET_OS_IPHONE
NS_HEADER_AUDIT_END(nullability, sendability)
#else
#import <UIFoundation/NSTextAlternatives.h>
#endif
