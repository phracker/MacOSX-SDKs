/*
	NSKeyValueCoding.h
	Copyright (c) 1994-2003, Apple Computer, Inc.
	All rights reserved.
*/

#import <Foundation/NSArray.h>
#import <Foundation/NSDictionary.h>

@class NSError, NSString;

// The exception that is thrown when a key value coding operation fails.  The exception's user info dictionary will contain at least two entries:
// @"NSTargetObjectUserInfoKey": the receiver of the failed KVC message.
// @"NSUnknownUserInfoKey": the key that was used in the failed KVC message.
FOUNDATION_EXPORT NSString *NSUndefinedKeyException;

@interface NSObject(NSKeyValueCoding)

// Return yes if -valueForKey:, -setValue:forKey:, -mutableArrayValueForKey:, -storedValueForKey:, -takeStoredValue:forKey:, and -takeValue:forKey: may directly manipulate instance variables when sent to instances of the receiving class, no otherwise.  The default implementation of this method returns yes.
+ (BOOL)accessInstanceVariablesDirectly;

// Given a key that identifies an attribute or to-one relationship, return the attribute value or the related object.  Given a key that identifies a to-many relationship, return an immutable array that contains all of the related objects.  The default implementation of this method does the following:
// 1. Searches the class of the receiver for an accessor method whose name matches the pattern -get<Key>, -<key>, or -is<Key>, in that order.  If such a method is found it is invoked.  If the type of the result is one of the scalar types supported by NSNumber, conversion is done and an NSNumber is returned.  If the type of the result is one of the structure types explicitly supported by NSValue, conversion is done and an NSValue is returned.  Otherwise the the result itself is returned.
// 2. Otherwise (no simple accessor method is found), searches the class of the receiver for a pair of methods whose names match the patterns -countOf<Key> and -objectIn<Key>AtIndex: (and therefore correspond to the primitive methods defined by the NSArray class).  If both such methods are found a collection proxy object that responds to all NSArray methods is returned.  Each NSArray message sent to the collection proxy object will result in some combination of -countOf<Key> and -objectIn<Key>AtIndex: messages being sent to the original receiver of -valueForKey:, unless the class of the receiver also implements an optional method whose name matches the pattern -get<Key>:range:, in which case that method will be used when appropriate for best performance.
// 3. Otherwise (no simple accessor method or set of array primitive methods is found), if the receiver's class' +accessInstanceVariablesDirectly method returns yes, searches the class of the receiver for an instance variable whose name matches the pattern _<key>, _is<Key>, <key>, or is<Key>, in that order.  If such an instance variable is found, the value of the instance variable in the receiver is returned.
// 4. Otherwise (no simple accessor method, set of array primitive methods, or instance variable is found), invokes -valueForUndefinedKey: and returns the result.  The default implementation of -valueForUndefinedKey: raises an NSUndefinedKeyException.
// Compatibility notes:
// - For backward binary compatibility, an accessor method whose name matches the pattern -_get<Key>, or -_<key> is searched for between steps 2 and 3.  If such a method is found it is invoked, with the same NSNumber/NSValue conversion as in step 1.  KVC accessor methods whose names start with underscores are deprecated as of Mac OS 10.3 though.
// - The behavior described in step 3 is a change from Mac OS 10.2, in which the instance variable search order was <key>, _<key>.
// - For backward binary compatibility, -handleQueryWithUnboundKey: will be invoked instead of -valueForUndefinedKey: in step 4, if the implementation of -handleQueryWithUnboundKey: in the receiver's class is not NSObject's.
// FoundationJava notes:
// - When the receiver is an instance of a Java class, member functions whose names match the patterns get<Key>(), <key>(), and is<Key>() will be recognized in step 1.
// - The member function name patterns used in step 2 are countOf<Key>() and objectIn<Key>AtIndex().  To support common Java coding style, member functions whose names match the patterns getCountOf<Key>() and -getObjectFrom<Key>() are also recognized.
- (id)valueForKey:(NSString *)key;

#if MAC_OS_X_VERSION_10_3 <= MAC_OS_X_VERSION_MAX_ALLOWED

// Given a value and a key that identifies an attribute, set the value of the attribute.  Given an object and a key that identifies a to-one relationship, relate the object to the receiver, unrelating the previously related object if there was one.  Given a collection object and a key that identifies a to-many relationship, relate the objects contained in the collection to the receiver, unrelating previously related objects if there were any.  The default implementation of this method does the following:
// 1. Searches the class of the receiver for an accessor method whose name matches the pattern -set<Key>:.  If such a method is found the type of its parameter is checked.  If the parameter type is one of the scalar types supported by NSNumber or one of the structure types explicitly supported by NSNumber but the value is nil -setNilValueForKey: is invoked.  The default implementation of -setNilValueForKey: raises an NSInvalidArgumentException.  If the value is not nil the appropriate -<type>Value: message is sent to the value and the result is used as the argument of an invocation of the accessor method.   If the type of the accessor method's parameter is not an NSNumber scalar type or an NSNValue structure type the accessor method is invoked with the value as the argument.
// 2. Otherwise (no accessor method is found), if the receiver's class' +accessInstanceVariablesDirectly method returns yes, searches the class of the receiver for an instance variable whose name matches the pattern _<key>, _is<Key>, <key>, or is<Key>, in that order.  If such an instance variable is found and its type is an NSNumber scalar type or NSValue structure type the value of the instance variable in the receiver is set using the same NSNumber/NSValue conversion as in step 1.  If such an instance variable is found but its type is not an NSNumber scalar type or NSValue structure type the value is retained and the result is set in the instance variable, after first autoreleasing the instance variable's old value.
// 3. Otherwise (no accessor method or instance variable is found), invokes -setValue:forUndefinedKey:.  The default implementation of -setValue:forUndefinedKey: raises an NSUndefinedKeyException.
// Compatibility notes:
// - For backward binary compatibility with -takeValue:forKey:'s behavior, a method whose name matches the pattern  -_set<Key>: is also recognized in step 1.  KVC accessor methods whose names start with underscores are deprecated as of Mac OS 10.3 though.
// - For backward binary compatibility, -unableToSetNilForKey: will be invoked instead of -setNilValueForKey: in step 1, if the implementation of -unableToSetNilForKey: in the receiver's class is not NSObject's.
// - The behavior described in step 2 is different from -takeValue:forKey:'s, in which the instance variable search order is <key>, _<key>.
// - For backward binary compatibility with -takeValue:forKey:'s behavior, -handleTakeValue:forUnboundKey: will be invoked instead of -setValue:forUndefinedKey: in step 3, if the implementation of -handleTakeValue:forUnboundKey: in the receiver's class is not NSObject's.
// FoundationJava note: when the receiver is an instance of a Java class, member functions whose names match the pattern set<Key>() will be recognized in step 1.
- (void)setValue:(id)value forKey:(NSString *)key;

// Given a pointer to a value pointer, a key that identifies an attribute or to-one relationship, and a pointer to an NSError pointer, return a value that is suitable for use in subsequent -setValue:forKey: messages sent to the same receiver.  If no validation is necessary, return yes without altering *ioValue or *outError.  If validation is necessary and possible, return yes after setting *ioValue to an object that is the validated version of the original value, but without altering *outError.  If validation is necessary but not possible, return no after setting *outError to an NSError that encapsulates the reason that validation was not possible, but without altering *ioValue.  The sender of the message is never given responsibility for releasing ioValue or outError.  The default implementation of this method searches the class of the receiver for a validator method whose name matches the pattern -validate<Key>:error:.  If such a method is found it is invoked and the result is returned.  If no such method is found, yes is returned.
- (BOOL)validateValue:(id *)ioValue forKey:(NSString *)inKey error:(NSError **)outError;

// Given a key that identifies an ordered to-many relationship, return a mutable array that provides read-write access to the related objects.  Objects added to the mutable array will become related to the receiver, and objects removed from the mutable array will become unrelated.  The default implementation of this method recognizes the same simple accessor methods and array accessor methods as -valueForKey:'s, and follows the same direct instance variable access policies, but always returns a mutable collection proxy object instead of the immutable collection that -valueForKey: would return.  It also:
// 1. Searches the class of the receiver for a pair of methods whose names match the patterns -insertObject:in<Key>AtIndex: and -removeObjectFrom<Key>AtIndex: (and therefore correspond to the two most primitive methods defined by the NSMutableArray class).  If both such methods are found each NSMutableArray message sent to the collection proxy object will result in some combination of -insertObject:in<Key>AtIndex: and -removeObjectFrom<Key>AtIndex: messages being sent to the original receiver of -mutableArrayValueForKey:, unless the class of the receiver also implements an optional method whose name matches the pattern -replaceObjectIn<Key>AtIndex:withObject:, in which case that replacement method will be used when appropriate for best performance.
// 2. Otherwise (no set of mutable array primitive methods is found), searches the class of the receiver for an accessor method whose name matches the pattern -set<Key>:.  If such a method is found each NSMutableArray message sent to the collecton proxy object will result in a -set<Key>: message being sent to the original receiver of -mutableArrayValueForKey:.
// 3. Otherwise (no set of mutable array primitive methods or simple accessor method is found), if the receiver's class' +accessInstanceVariablesDirectly method returns yes, searches the class of the receiver for an instance variable whose name matches the pattern _<key> or <key>, in that order.  If such an instance variable is found, each NSMutableArray message sent to the collection proxy object will be forwarded to the instance variable's value, which therefore must typically be an instance of NSMutableArray or a subclass of NSMutableArray.
// 4. Otherwise (no set of mutable array primitives, simple accessor method, or instance variable is found), raises an NSUndefinedKeyException.
// Performance note: the repetitive -set<Key>: messages implied by step 2's description are a potential performance problem.  For better performance implement methods that fulfill the requirements for step 1 in your KVC-compliant class.  For best performance implement the optional methods described for step 1 too.
// FoundationJava notes:
// - When the receiver is an instance of a Java class, member functions whose names match the patterns insertObjectIn<Key>AtIndex(), removeObjectFrom<Key>AtIndex(), and replaceObjectIn<Key>AtIndexWithObject() will be recognized in step 1.
// - The member function name pattern used in step 2 is set<Key>().
- (NSMutableArray *)mutableArrayValueForKey:(NSString *)key;

#endif

// Key-path-taking variants of like-named methods.  The default implementation of each parses the key path enough to determine whether or not it has more than one component (key path components are separated by periods).  If so, -valueForKey: is invoked with the first key path component as the argument, and the method being invoked is invoked recursively on the result, with the remainder of the key path passed as an argument.  If not, the like-named non-key-path-taking method is invoked.
- (id)valueForKeyPath:(NSString *)keyPath;
- (void)setValue:(id)value forKeyPath:(NSString *)keyPath;
#if MAC_OS_X_VERSION_10_3 <= MAC_OS_X_VERSION_MAX_ALLOWED
- (BOOL)validateValue:(id *)ioValue forKeyPath:(NSString *)inKeyPath error:(NSError **)outError;
- (NSMutableArray *)mutableArrayValueForKeyPath:(NSString *)keyPath;
#endif

#if MAC_OS_X_VERSION_10_3 <= MAC_OS_X_VERSION_MAX_ALLOWED

// Given that an invocation of -valueForKey: would be unable to get a keyed value using its default access mechanism, return the keyed value using some other mechanism.  The default implementation of this method raises an NSUndefinedKeyException.
- (id)valueForUndefinedKey:(NSString *)key;

// Given that an invocation of -setValue:forKey: would be unable to set the keyed value using its default mechanism, set the keyed value using some other mechanism.  The default implementation of this method raises an NSUndefinedKeyException.
- (void)setValue:(id)value forUndefinedKey:(NSString *)key;

// Given that an invocation of -setValue:forKey: would be unable to set the keyed value because the type of the parameter of the corresponding accessor method is an NSNumber scalar type or NSValue structure type but the value is nil, set the keyed value using some other mechanism.  The default implementation of this method raises an NSInvalidArgumentException. 
- (void)setNilValueForKey:(NSString *)key;

// Given an array of keys, return a dictionary containing the keyed attribute values, to-one-related objects, and/or collections of to-many-related objects.  Entries for which -valueForKey: returns nil have NSNull as their value in the returned dictionary.
-(NSDictionary *)dictionaryWithValuesForKeys:(NSArray *)keys;

// Given a dictionary containing keyed attribute values, to-one-related objects, and/or collections of to-many-related objects, set the keyed values.  Dictionary entries whose values are NSNull result in -setValue:nil forKey:key messages being sent to the receiver.
- (void)setValuesForKeysWithDictionary:(NSDictionary *)keyedValues;

#endif

// These methods are not deprecated as of Mac OS 10.3, but may be deprecated in favor of new methods in a future release of Mac OS.
+ (BOOL)useStoredAccessor;
- (id)storedValueForKey:(NSString *)key;
- (void)takeStoredValue:(id)value forKey:(NSString *)key;

@end

#if MAC_OS_X_VERSION_10_3 <= MAC_OS_X_VERSION_MAX_ALLOWED

@interface NSArray(NSKeyValueCoding)

// Return an array containing the results of invoking -valueForKey: on each of the receiver's elements.  The returned array will contain NSNull elements for each instance of -valueForKey: returning nil.
- (id)valueForKey:(NSString *)key;

// Invoke -setValue:forKey: on each of the receiver's elements.
- (void)setValue:(id)value forKey:(NSString *)key;

@end

#endif

@interface NSDictionary(NSKeyValueCoding)

// Return the result of sending -objectForKey: to the receiver.
- (id)valueForKey:(NSString *)key;

@end

#if MAC_OS_X_VERSION_10_3 <= MAC_OS_X_VERSION_MAX_ALLOWED

@interface NSMutableDictionary(NSKeyValueCoding)

// Send -setObject:forKey: to the receiver, unless the value is nil, in which case send -removeObject:forKey:.
- (void)setValue:(id)value forKey:(NSString *)key;

@end

#endif

@interface NSObject(NSDeprecatedKeyValueCoding)

// These methods are deprecated as of Mac OS 10.3.  Use the new, more consistently named, methods declared above instead.
- (void)takeValue:(id)value forKey:(NSString *)key;
- (void)takeValue:(id)value forKeyPath:(NSString *)keyPath;
- (id)handleQueryWithUnboundKey:(NSString *)key;
- (void)handleTakeValue:(id)value forUnboundKey:(NSString *)key;
- (void)unableToSetNilForKey:(NSString *)key;
- (NSDictionary *)valuesForKeys:(NSArray *)keys;
- (void)takeValuesFromDictionary:(NSDictionary *)properties;

@end
