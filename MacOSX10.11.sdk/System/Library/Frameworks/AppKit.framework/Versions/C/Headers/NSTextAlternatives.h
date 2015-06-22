/*
	NSTextAlternatives.h
	Application Kit
	Copyright (c) 2011-2015, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSArray.h>
#import <AppKit/AppKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class NSString;

NS_CLASS_AVAILABLE(10_8, NA)
@interface NSTextAlternatives : NSObject {
@private
    NSString *_primaryString;
    NSArray *_alternativeStrings;
    id _internal;
}

- (instancetype)initWithPrimaryString:(NSString *)primaryString alternativeStrings:(NSArray<NSString *> *)alternativeStrings;

@property (readonly, copy) NSString *primaryString;
@property (readonly, copy) NSArray<NSString *> *alternativeStrings;

- (void)noteSelectedAlternativeString:(NSString *)alternativeString;

@end

APPKIT_EXTERN NSString * NSTextAlternativesSelectedAlternativeStringNotification NS_AVAILABLE_MAC(10_8); // @"NSAlternativeString"

NS_ASSUME_NONNULL_END
