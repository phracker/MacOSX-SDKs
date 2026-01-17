/*
	NSTextAlternatives.h
	Application Kit
	Copyright (c) 2011-2012, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <AppKit/AppKitDefines.h>

@class NSString, NSArray;

NS_CLASS_AVAILABLE(10_8, NA)
@interface NSTextAlternatives : NSObject {
@private
    NSString *_primaryString;
    NSArray *_alternativeStrings;
    id _internal;
}

- (id)initWithPrimaryString:(NSString *)primaryString alternativeStrings:(NSArray *)alternativeStrings;

@property (readonly) NSString *primaryString;
@property (readonly) NSArray *alternativeStrings;

- (void)noteSelectedAlternativeString:(NSString *)alternativeString;

@end

APPKIT_EXTERN NSString *NSTextAlternativesSelectedAlternativeStringNotification NS_AVAILABLE_MAC(10_8); // @"NSAlternativeString"
