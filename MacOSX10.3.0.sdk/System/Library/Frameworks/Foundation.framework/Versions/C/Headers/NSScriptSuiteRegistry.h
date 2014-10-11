/*	NSScriptSuiteRegistry.h
	Copyright (c) 1997-2003, Apple, Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSArray;
@class NSBundle;
@class NSData;
@class NSDictionary;
@class NSMutableArray;
@class NSMutableData;
@class NSMutableDictionary;
@class NSMutableSet;
@class NSScriptCommandDescription;
@class NSScriptClassDescription;

@interface NSScriptSuiteRegistry : NSObject {
    @private
    NSMutableArray *_suiteNames;
    NSMutableDictionary *_appleEventCodes;
    NSMutableDictionary *_bundles;
    NSMutableDictionary *_classes;
    NSMutableDictionary *_synonyms;
    NSMutableDictionary *_synonymTables;
    NSMutableDictionary *_commands;
    NSMutableDictionary *_enumerations;
    NSMutableDictionary *_valueTypes;
    NSMutableDictionary *_terminologies;
    NSMutableDictionary *_usedFeatures;
    NSMutableSet *_seenBundles;

    void *_codeToSuiteNameTable;
    void *_codeToCommandLookupTable;
    void *_codeToClassDescTable;
    void *_codeToKeyTable;
}

+ (NSScriptSuiteRegistry *)sharedScriptSuiteRegistry;
+ (void)setSharedScriptSuiteRegistry:(NSScriptSuiteRegistry *)registry;

- (NSArray *)suiteNames;
- (NSDictionary *)commandDescriptionsInSuite:(NSString *)suiteName;
- (NSDictionary *)classDescriptionsInSuite:(NSString *)suiteName;

- (unsigned long)appleEventCodeForSuite:(NSString *)suiteName;
- (NSString *)suiteForAppleEventCode:(unsigned long)code;

- (NSBundle *)bundleForSuite:(NSString *)suiteName;

- (NSScriptCommandDescription *)commandDescriptionWithAppleEventClass:(unsigned long)eventClass andAppleEventCode:(unsigned long)commandCode;
- (NSScriptClassDescription *)classDescriptionWithAppleEventCode:(unsigned long)classCode;

- (void)registerCommandDescription:(NSScriptCommandDescription *)commandDef;
- (void)registerClassDescription:(NSScriptClassDescription *)classDesc;

- (void)loadSuitesFromBundle:(NSBundle *)bundle;
- (void)loadSuiteWithDictionary:(NSDictionary *)dict fromBundle:(NSBundle *)bundle;

- (NSData *)aeteResource:(NSString *)languageName;

@end
