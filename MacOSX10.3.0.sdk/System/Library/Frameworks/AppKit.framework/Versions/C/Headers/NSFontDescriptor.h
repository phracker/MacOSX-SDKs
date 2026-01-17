/*
	NSFontDescriptor.h
	Application Kit
	Copyright (c) 2003-2003, Apple Computer, Inc.
	All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <AppKit/AppKitDefines.h>

#if MAC_OS_X_VERSION_10_3 <= MAC_OS_X_VERSION_MAX_ALLOWED

@class NSMutableDictionary, NSDictionary;

@interface NSFontDescriptor: NSObject <NSCopying, NSCoding> {
/*All instance variables are private*/
    NSMutableDictionary *_attributes;
    id _reserved1;
    id _reserved2;
    id _reserved3;
    id _reserved4;
    id _reserved5;
}

- (id)initWithFontAttributes:(NSDictionary *)attributes;
+ (id)fontDescriptorWithFontAttributes:(NSDictionary *)attributes;
+ (id)fontDescriptorWithName:(NSString *)fontName size:(float)size;
- (NSDictionary *)fontAttributes;
@end
#endif

/* Predefined font attributes not defined in NSAttributedString.h */

APPKIT_EXTERN NSString *NSFontFamilyAttribute			AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
APPKIT_EXTERN NSString *NSFontNameAttribute			AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
APPKIT_EXTERN NSString *NSFontFaceAttribute			AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
APPKIT_EXTERN NSString *NSFontSizeAttribute			AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER; 
APPKIT_EXTERN NSString *NSFontVisibleNameAttribute 		AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER; 
APPKIT_EXTERN NSString *NSFontColorAttribute 			AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER; 

