/*
	NSObjectScripting.h
	Copyright (c) 2002, Apple Computer, Inc.
	All rights reserved.
*/

#if MAC_OS_X_VERSION_10_2 <= MAC_OS_X_VERSION_MAX_ALLOWED

#import <Foundation/NSObject.h>

@class NSDictionary;

@interface NSObject(NSScripting)

// Return an NSString-keyed dictionary of the object's scriptable properties, including all of those that are declared as Attributes and ToOneRelationships in the .scriptSuite property list entries for the class and its scripting superclasses, with the exception of ones keyed by "scriptingProperties."  Each key in the dictionary must be identical to the key for an Attribute or ToOneRelationship.  The values of the dictionary must be Objective-C objects that are convertible to NSAppleEventDescriptors.
- (NSDictionary *)scriptingProperties;

// Given an NSString-keyed dictionary, set one or more scriptable properties of the object.  The valid keys for the dictionary include the keys for non-ReadOnly Attributes and ToOneRelationships in the .scriptSuite property list entries for the object's class and its scripting superclasses, and no others.  In other words, invokers of this method must have already done any necessary validation to ensure that the properties dictionary includes nothing but entries for declared, settable, Attributes and ToOneRelationships.  Implementations of this method are not expected to check the validity of keys in the passed-in dictionary, but must be able accept dictionaries that do not contain entries for every scriptable property.  The values of the dictionary are Objective-C objects.  Implementations of this method must perform type checking on the dictionary values.
- (void)setScriptingProperties:(NSDictionary *)properties;

@end

#endif
