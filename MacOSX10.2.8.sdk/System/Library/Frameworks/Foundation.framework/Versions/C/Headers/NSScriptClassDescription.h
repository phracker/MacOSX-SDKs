/*
	NSScriptClassDescription.h
	Copyright (c) 1997-2002, Apple Computer, Inc.
	All rights reserved.
*/

#import <Foundation/NSClassDescription.h>

@class NSScriptCommandDescription;
@class NSString;

@interface NSScriptClassDescription : NSClassDescription {
    @private
    NSString *_suiteName;
    NSString *_className;
    unsigned long _appleEventCode;
    NSString *_superclassName;
    NSDictionary *_attributes;
    NSDictionary *_toOneRelationships;
    NSDictionary *_toManyRelationships;
    NSDictionary *_supportedCommands;
    void *_privateVars;
}

- (id)initWithSuiteName:(NSString *)suiteName className:(NSString *)className dictionary:(NSDictionary *)dict;

- (NSString *)suiteName;
- (NSString *)className;

- (NSScriptClassDescription *)superclassDescription;

- (unsigned long)appleEventCode;

- (BOOL)matchesAppleEventCode:(unsigned long)code;
    // This returns YES if the code matches the primary code for this class or any of the synonym codes for this class.

- (BOOL)supportsCommand:(NSScriptCommandDescription *)commandDef;
    // Returns YES if the given command is supported/allowed by this class.

- (SEL)selectorForCommand:(NSScriptCommandDescription *)commandDef;
    // Returns the selector that the class uses to execute the comamnds of the given command defintion.  Returns NULL if the class is content with the default command implementation (if any).

- (NSString *)typeForKey:(NSString *)key;
- (NSScriptClassDescription *)classDescriptionForKey:(NSString *)key;
- (unsigned long)appleEventCodeForKey:(NSString *)key;
- (BOOL)isReadOnlyKey:(NSString *)key;
    // Given an attribute or relationship key, return more information.
- (NSString *)keyWithAppleEventCode:(unsigned long)code;
    // Find a key from its code

#if MAC_OS_X_VERSION_10_2 <= MAC_OS_X_VERSION_MAX_ALLOWED

- (NSString *)defaultSubcontainerAttributeKey;

- (BOOL)isLocationRequiredToCreateForKey:(NSString *)toManyRelationshipKey;

#endif

@end

@interface NSObject(NSScriptClassDescription)

- (NSString *)className;
- (unsigned long)classCode;

@end
