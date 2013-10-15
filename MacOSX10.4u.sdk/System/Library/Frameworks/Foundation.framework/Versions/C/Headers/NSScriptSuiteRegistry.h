/*
	NSScriptSuiteRegistry.h
	Copyright (c) 1997-2005, Apple Computer, Inc.
	All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSArray, NSBundle, NSData, NSDictionary, NSMutableArray, NSMutableDictionary, NSMutableSet, NSScriptClassDescription, NSScriptCommandDescription;

@interface NSScriptSuiteRegistry : NSObject {
    @private
    BOOL _isLoadingSDEFFiles;
    char _reserved1[3];
    NSMutableSet *_seenBundles;
    NSMutableArray *_suiteDescriptionsBeingCollected;
    NSScriptClassDescription *_classDescriptionNeedingRegistration;
    NSMutableArray *_suiteDescriptions;
    NSScriptCommandDescription *_commandDescriptionNeedingRegistration;
    NSMutableDictionary *_cachedClassDescriptionsByAppleEventCode;
    NSMutableDictionary *_cachedCommandDescriptionsByAppleEventCodes;
    NSDictionary *_cachedSuiteDescriptionsByName;
    NSMutableDictionary *_complexTypeDescriptionsByName;
    NSMutableDictionary *_listTypeDescriptionsByName;
    unsigned int _nextComplexTypeAppleEventCode;
    void *_reserved2[4];
}

/* Get or set the program's single NSScriptSuiteRegistry.
*/
+ (NSScriptSuiteRegistry *)sharedScriptSuiteRegistry;
+ (void)setSharedScriptSuiteRegistry:(NSScriptSuiteRegistry *)registry;

/* Given a bundle, register class and command descriptions from any .scriptSuite/.scriptTerminology resource files in the bundle. Redundant invocations of this method are ignored.
*/
- (void)loadSuitesFromBundle:(NSBundle *)bundle;

/* Given a scripting suite declaration dictionary of the sort that is valid in .scriptSuite property list files, and a pointer to the bundle that contains the code that implements the suite, register class and command descriptions for the suite.
*/
- (void)loadSuiteWithDictionary:(NSDictionary *)suiteDeclaration fromBundle:(NSBundle *)bundle;

/* Register a scripting class or command description.
*/
- (void)registerClassDescription:(NSScriptClassDescription *)classDescription;
- (void)registerCommandDescription:(NSScriptCommandDescription *)commandDescription;

/* Return a list of all registered suite names.
*/
- (NSArray *)suiteNames;

/* Return the four character code used to identify the named suite.
*/
- (unsigned long)appleEventCodeForSuite:(NSString *)suiteName;

/* Return the bundle that contains the code that implements the named suite.
*/
- (NSBundle *)bundleForSuite:(NSString *)suiteName;

/* Return a dictionary containing the descriptions of all of the classes or commands in the named suite, keyed by class or comand name.
*/
- (NSDictionary *)classDescriptionsInSuite:(NSString *)suiteName;
- (NSDictionary *)commandDescriptionsInSuite:(NSString *)suiteName;

/* Given a four character code used to identify a scripting suite, return the name of the suite.
*/
- (NSString *)suiteForAppleEventCode:(unsigned long)appleEventCode;

/* Given a four character code used to identify a scriptable class in Apple events, return the class description.
*/
- (NSScriptClassDescription *)classDescriptionWithAppleEventCode:(unsigned long)appleEventCode;

/* Given the pair of four character codes used to identify a scripting command in Apple events, return the command description.
*/
- (NSScriptCommandDescription *)commandDescriptionWithAppleEventClass:(unsigned long)appleEventClassCode andAppleEventCode:(unsigned long)appleEventIDCode;

/* Return suitable reply data for the standard Get AETE Apple event, given the set of scripting suites currently registered.
*/
- (NSData *)aeteResource:(NSString *)languageName;

@end
