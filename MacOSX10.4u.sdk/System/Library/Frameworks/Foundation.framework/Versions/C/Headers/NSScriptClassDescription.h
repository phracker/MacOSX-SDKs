/*
	NSScriptClassDescription.h
	Copyright (c) 1997-2005, Apple Computer, Inc.
	All rights reserved.
*/

#import <Foundation/NSClassDescription.h>

@class NSScriptCommandDescription;

@interface NSScriptClassDescription : NSClassDescription {
    @private
    NSString *_suiteName;
    NSString *_objcClassName;
    unsigned long _appleEventCode;
    NSObject *_superclassNameOrDescription;
    NSArray *_attributeDescriptions;
    NSArray *_toOneRelationshipDescriptions;
    NSArray *_toManyRelationshipDescriptions;
    NSDictionary *_commandMethodSelectorsByName;
    id _moreVars;
}

/* Initialize, given a scripting suite name, class name, and class declaration dictionary of the sort that is valid in .scriptSuite property list files.
*/
- (id)initWithSuiteName:(NSString *)suiteName className:(NSString *)className dictionary:(NSDictionary *)classDeclaration;

/* Return the suite name or class name provided at initialization time.
*/
- (NSString *)suiteName;
- (NSString *)className;

/* Return the scripting class description of the superclass of the class described by the receiver.
*/
- (NSScriptClassDescription *)superclassDescription;

/* Return the primary four character code used to identify the described class in Apple events.
*/
- (unsigned long)appleEventCode;

/* Return YES if the four character code identifies the described class in Apple events. Return NO otherwise.
*/
- (BOOL)matchesAppleEventCode:(unsigned long)appleEventCode;

/* Return YES if the described class or one of its superclasses is explicitly declared to support the described command, NO otherwise.
*/
- (BOOL)supportsCommand:(NSScriptCommandDescription *)commandDescription;

/* If the described class or one of its superclasses is explicitly declared to support the described command and the declaration includes a method name, return the selector for the class' handler method for the command. Return NULL otherwise.
*/
- (SEL)selectorForCommand:(NSScriptCommandDescription *)commandDescription;

/* Return the name of the declared type of the keyed attribute, to-one relationship, or to-many relationship.
*/
- (NSString *)typeForKey:(NSString *)key;

/* Return the class description for the keyed attribute, to-one relationship, or to-many relationship.
*/
- (NSScriptClassDescription *)classDescriptionForKey:(NSString *)key;

/* Return the four character code that identifies the keyed attribute, to-one relationship, or to-many relationship in Apple events.
*/
- (unsigned long)appleEventCodeForKey:(NSString *)key;

/* Return YES if the keyed attribute, to-one relationship, or to-many relationship is read-only, NO otherwise.
*/
- (BOOL)isReadOnlyKey:(NSString *)key;

/* Given a four character code used to identify a property or element class in Apple events, return the key identifying the corresponding attribute, to-one relationship or to-many relationship.
*/
- (NSString *)keyWithAppleEventCode:(unsigned long)appleEventCode;

#if MAC_OS_X_VERSION_10_2 <= MAC_OS_X_VERSION_MAX_ALLOWED

/* Return the value of the DefaultSubcontainerAttribute entry of the class declaration dictionary provided when the receiver was instantiated, or nil if there was no such entry.
*/
- (NSString *)defaultSubcontainerAttributeKey;

/* Return YES if creation of objects for the relationship specified by the key, in containers of the class described by the receiver, requires an explicitly specified insertion location. Return NO otherwise. For example, NSMakeCommand uses this method to determine whether or not a specific Make command must have an at parameter.
*/
- (BOOL)isLocationRequiredToCreateForKey:(NSString *)toManyRelationshipKey;

#endif

@end

@interface NSObject(NSScriptClassDescription)

/* Return the four character code identifying the receiver's class in Apple events.
*/
- (unsigned long)classCode;

/* Return the Objective-C name of the receiver's class.
*/
- (NSString *)className;

@end
