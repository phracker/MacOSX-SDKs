/*
	NSKeyValueCoding.h
	Copyright (c) 1994-2005, Apple Computer, Inc.
	All rights reserved.
*/

#import <Foundation/NSArray.h>
#import <Foundation/NSDictionary.h>
#import <Foundation/NSSet.h>

@class NSError, NSString;

// The exception that is thrown when a key value coding operation fails. The exception's user info dictionary will contain at least two entries:
// @"NSTargetObjectUserInfoKey": the receiver of the failed KVC message.
// @"NSUnknownUserInfoKey": the key that was used in the failed KVC message.
FOUNDATION_EXPORT NSString *const NSUndefinedKeyException AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

// Strings for the names of array operators supported by key-value coding. Only these string declarations are new in Mac OS 10.4. The actual support for array operators appeared in Mac OS 10.3. The values of these do not include "@" prefixes.
FOUNDATION_EXPORT NSString *const NSAverageKeyValueOperator AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
FOUNDATION_EXPORT NSString *const NSCountKeyValueOperator AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
FOUNDATION_EXPORT NSString *const NSDistinctUnionOfArraysKeyValueOperator AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
FOUNDATION_EXPORT NSString *const NSDistinctUnionOfObjectsKeyValueOperator AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
FOUNDATION_EXPORT NSString *const NSDistinctUnionOfSetsKeyValueOperator AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
FOUNDATION_EXPORT NSString *const NSMaximumKeyValueOperator AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
FOUNDATION_EXPORT NSString *const NSMinimumKeyValueOperator AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
FOUNDATION_EXPORT NSString *const NSSumKeyValueOperator AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
FOUNDATION_EXPORT NSString *const NSUnionOfArraysKeyValueOperator AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
FOUNDATION_EXPORT NSString *const NSUnionOfObjectsKeyValueOperator AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
FOUNDATION_EXPORT NSString *const NSUnionOfSetsKeyValueOperator AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

@interface NSObject(NSKeyValueCoding)

// Return YES if -valueForKey:, -setValue:forKey:, -mutableArrayValueForKey:, -storedValueForKey:, -takeStoredValue:forKey:, and -takeValue:forKey: may directly manipulate instance variables when sent to instances of the receiving class, NO otherwise. The default implementation of this method returns YES.
+ (BOOL)accessInstanceVariablesDirectly;

// Given a key that identifies an attribute or to-one relationship, return the attribute value or the related object. Given a key that identifies a to-many relationship, return an immutable array or an immutable set that contains all of the related objects. The default implementation of this method does the following:
// 1. Searches the class of the receiver for an accessor method whose name matches the pattern -get<Key>, -<key>, or -is<Key>, in that order. If such a method is found it is invoked. If the type of the result is one of the scalar types supported by NSNumber, conversion is done and an NSNumber is returned. If the type of the result is one of the structure types explicitly supported by NSValue, conversion is done and an NSValue is returned. Otherwise the the result itself is returned.
// 2. Otherwise (no simple accessor method is found), searches the class of the receiver for methods whose names match the patterns -countOf<Key> and -objectIn<Key>AtIndex: (corresponding to the primitive methods defined by the NSArray class) and (introduced in Mac OS 10.4) also -<key>AtIndexes: (corresponding to -[NSArray objectsAtIndexes:]). If a count method and at least one of the other two possible methods are found a collection proxy object that responds to all NSArray methods is returned. Each NSArray message sent to the collection proxy object will result in some combination of -countOf<Key>, -objectIn<Key>AtIndex:, and -<key>AtIndexes: messages being sent to the original receiver of -valueForKey:. If the class of the receiver also implements an optional method whose name matches the pattern -get<Key>:range: that method will be used when appropriate for best performance.
// 3 (introduced in Mac OS 10.4). Otherwise (no simple accessor method or set of array access methods is found), searches the class of the receiver for a threesome of methods whose names match the patterns -countOf<Key>, -enumeratorOf<Key>, and -memberOf<Key>: (corresponding to the primitive methods defined by the NSSet class). If all three such methods are found a collection proxy object that responds to all NSSet methods is returned. Each NSSet message sent to the collection proxy object will result in some combination of -countOf<Key>, -enumeratorOf<Key>, and -memberOf<Key>: messages being sent to the original receiver of -valueForKey:.
// 4. Otherwise (no simple accessor method or set of collection access methods is found), if the receiver's class' +accessInstanceVariablesDirectly method returns YES, searches the class of the receiver for an instance variable whose name matches the pattern _<key>, _is<Key>, <key>, or is<Key>, in that order. If such an instance variable is found, the value of the instance variable in the receiver is returned.
// 5. Otherwise (no simple accessor method, set of collection access methods, or instance variable is found), invokes -valueForUndefinedKey: and returns the result. The default implementation of -valueForUndefinedKey: raises an NSUndefinedKeyException.
// Compatibility notes:
// - For backward binary compatibility, an accessor method whose name matches the pattern -_get<Key>, or -_<key> is searched for between steps 1 and 2. If such a method is found it is invoked, with the same NSNumber/NSValue conversion as in step 1. KVC accessor methods whose names start with underscores were deprecated as of Mac OS 10.3 though.
// - The behavior described in step 4 is a change from Mac OS 10.2, in which the instance variable search order was <key>, _<key>.
// - For backward binary compatibility, -handleQueryWithUnboundKey: will be invoked instead of -valueForUndefinedKey: in step 5, if the implementation of -handleQueryWithUnboundKey: in the receiver's class is not NSObject's.
// FoundationJava notes:
// - When the receiver is an instance of a Java class, member functions whose names match the patterns get<Key>(), <key>(), and is<Key>() will be recognized in step 1.
// - The member function name patterns used in step 2 are countOf<Key>(), objectIn<Key>AtIndex(), and (in Mac OS 10.4) <key>AtIndexes(). To support common Java coding style, member functions whose names match the patterns getCountOf<Key>(), getObjectFrom<Key>(), and (in Mac OS 10.4) getObjectsFrom<Key>() are also recognized.
// - The member function name patterns used in step 3 are countOf<Key>(), enumeratorOf<Key>(), and memberOf<Key>(). To support common Java coding style, member functions whose names match the patterns getCountOf<Key>(), getEnumeratorOf<Key>(), and getMemberOf<Key>() are also recognized.
- (id)valueForKey:(NSString *)key;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3

// Given a value and a key that identifies an attribute, set the value of the attribute. Given an object and a key that identifies a to-one relationship, relate the object to the receiver, unrelating the previously related object if there was one. Given a collection object and a key that identifies a to-many relationship, relate the objects contained in the collection to the receiver, unrelating previously related objects if there were any. The default implementation of this method does the following:
// 1. Searches the class of the receiver for an accessor method whose name matches the pattern -set<Key>:. If such a method is found the type of its parameter is checked. If the parameter type is one of the scalar types supported by NSNumber or one of the structure types explicitly supported by NSNumber but the value is nil -setNilValueForKey: is invoked. The default implementation of -setNilValueForKey: raises an NSInvalidArgumentException. If the value is not nil the appropriate -<type>Value: message is sent to the value and the result is used as the argument of an invocation of the accessor method. If the type of the accessor method's parameter is not an NSNumber scalar type or an NSNValue structure type the accessor method is invoked with the value as the argument.
// 2. Otherwise (no accessor method is found), if the receiver's class' +accessInstanceVariablesDirectly method returns YES, searches the class of the receiver for an instance variable whose name matches the pattern _<key>, _is<Key>, <key>, or is<Key>, in that order. If such an instance variable is found and its type is an NSNumber scalar type or NSValue structure type the value of the instance variable in the receiver is set using the same NSNumber/NSValue conversion as in step 1. If such an instance variable is found but its type is not an NSNumber scalar type or NSValue structure type the value is retained and the result is set in the instance variable, after first autoreleasing the instance variable's old value.
// 3. Otherwise (no accessor method or instance variable is found), invokes -setValue:forUndefinedKey:. The default implementation of -setValue:forUndefinedKey: raises an NSUndefinedKeyException.
// Compatibility notes:
// - For backward binary compatibility with -takeValue:forKey:'s behavior, a method whose name matches the pattern -_set<Key>: is also recognized in step 1. KVC accessor methods whose names start with underscores were deprecated as of Mac OS 10.3 though.
// - For backward binary compatibility, -unableToSetNilForKey: will be invoked instead of -setNilValueForKey: in step 1, if the implementation of -unableToSetNilForKey: in the receiver's class is not NSObject's.
// - The behavior described in step 2 is different from -takeValue:forKey:'s, in which the instance variable search order is <key>, _<key>.
// - For backward binary compatibility with -takeValue:forKey:'s behavior, -handleTakeValue:forUnboundKey: will be invoked instead of -setValue:forUndefinedKey: in step 3, if the implementation of -handleTakeValue:forUnboundKey: in the receiver's class is not NSObject's.
// FoundationJava note: when the receiver is an instance of a Java class, member functions whose names match the pattern set<Key>() will be recognized in step 1.
- (void)setValue:(id)value forKey:(NSString *)key;

// Given a pointer to a value pointer, a key that identifies an attribute or to-one relationship, and a pointer to an NSError pointer, return a value that is suitable for use in subsequent -setValue:forKey: messages sent to the same receiver. If no validation is necessary, return YES without altering *ioValue or *outError. If validation is necessary and possible, return YES after setting *ioValue to an object that is the validated version of the original value, but without altering *outError. If validation is necessary but not possible, return NO after setting *outError to an NSError that encapsulates the reason that validation was not possible, but without altering *ioValue. The sender of the message is never given responsibility for releasing ioValue or outError. The default implementation of this method searches the class of the receiver for a validator method whose name matches the pattern -validate<Key>:error:. If such a method is found it is invoked and the result is returned. If no such method is found, YES is returned.
- (BOOL)validateValue:(id *)ioValue forKey:(NSString *)inKey error:(NSError **)outError;

// Given a key that identifies an _ordered_ to-many relationship, return a mutable array that provides read-write access to the related objects. Objects added to the mutable array will become related to the receiver, and objects removed from the mutable array will become unrelated. The default implementation of this method recognizes the same simple accessor methods and array accessor methods as -valueForKey:'s, and follows the same direct instance variable access policies, but always returns a mutable collection proxy object instead of the immutable collection that -valueForKey: would return. It also:
// 1. Searches the class of the receiver for methods whose names match the patterns -insertObject:in<Key>AtIndex: and -removeObjectFrom<Key>AtIndex: (corresponding to the two most primitive methods defined by the NSMutableArray class), and (introduced in Mac OS 10.4) also -insert<Key>:atIndexes: and -remove<Key>AtIndexes: (corresponding to -[NSMutableArray insertObjects:atIndexes:] and -[NSMutableArray removeObjectsAtIndexes:). If at least one insertion method and at least one removal method are found each NSMutableArray message sent to the collection proxy object will result in some combination of -insertObject:in<Key>AtIndex:, -removeObjectFrom<Key>AtIndex:, -insert<Key>:atIndexes:, and -remove<Key>AtIndexes: messages being sent to the original receiver of -mutableArrayValueForKey:. If the class of the receiver also implements an optional method whose name matches the pattern -replaceObjectIn<Key>AtIndex:withObject: or (introduced in Mac OS 10.4) -replace<Key>AtIndexes:with<Key>: that method will be used when appropriate for best performance.
// 2. Otherwise (no set of array mutation methods is found), searches the class of the receiver for an accessor method whose name matches the pattern -set<Key>:. If such a method is found each NSMutableArray message sent to the collecton proxy object will result in a -set<Key>: message being sent to the original receiver of -mutableArrayValueForKey:.
// 3. Otherwise (no set of array mutation methods or simple accessor method is found), if the receiver's class' +accessInstanceVariablesDirectly method returns YES, searches the class of the receiver for an instance variable whose name matches the pattern _<key> or <key>, in that order. If such an instance variable is found, each NSMutableArray message sent to the collection proxy object will be forwarded to the instance variable's value, which therefore must typically be an instance of NSMutableArray or a subclass of NSMutableArray.
// 4. Otherwise (no set of array mutation methods, simple accessor method, or instance variable is found), raises an NSUndefinedKeyException.
// Performance note: the repetitive -set<Key>: messages implied by step 2's description are a potential performance problem. For better performance implement insertion and removal methods that fulfill the requirements for step 1 in your KVC-compliant class. For best performance implement a replacement method too.
// FoundationJava notes:
// - When the receiver is an instance of a Java class, member functions whose names match the patterns insertObjectIn<Key>AtIndex(), removeObjectFrom<Key>AtIndex(), replaceObjectIn<Key>AtIndexWithObject(), and (in Mac OS 10.4) insert<Key>AtIndexes(), remove<Key>AtIndexes(), and replace<Key>AtIndexesWith<Key>() will be recognized in step 1.
// - The member function name pattern used in step 2 is set<Key>().
- (NSMutableArray *)mutableArrayValueForKey:(NSString *)key;

#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4

// Given a key that identifies an _unordered_ to-many relationship, return a mutable set that provides read-write access to the related objects. Objects added to the mutable set will become related to the receiver, and objects removed from the mutable set will become unrelated. The default implementation of this method recognizes the same simple accessor methods and set accessor methods as -valueForKey:'s, and follows the same direct instance variable access policies, but always returns a mutable collection proxy object instead of the immutable collection that -valueForKey: would return. It also:
// 1. Searches the class of the receiver for methods whose names match the patterns -add<Key>Object: and -remove<Key>Object: (corresponding to the two primitive methods defined by the NSMutableSet class) and also -add<Key>: and -remove<Key>: (corresponding to -[NSMutableSet unionSet:] and -[NSMutableSet minusSet:]). If at least one addition method and at least one removal method are found each NSMutableSet message sent to the collection proxy object will result in some combination of -add<Key>Object:, -remove<Key>Object:, -add<Key>:, and -remove<Key>: messages being sent to the original receiver of -mutableSetValueForKey:. If the class of the receiver also implements an optional method whose name matches the pattern -intersect<Key>: or -set<Key>: that method will be used when appropriate for best performance.
// 2. Otherwise (no set of set mutation methods is found), searches the class of the receiver for an accessor method whose name matches the pattern -set<Key>:. If such a method is found each NSMutableSet message sent to the collecton proxy object will result in a -set<Key>: message being sent to the original receiver of -mutableSetValueForKey:.
// 3. Otherwise (no set of set mutation methods or simple accessor method is found), if the receiver's class' +accessInstanceVariablesDirectly method returns YES, searches the class of the receiver for an instance variable whose name matches the pattern _<key> or <key>, in that order. If such an instance variable is found, each NSMutableSet message sent to the collection proxy object will be forwarded to the instance variable's value, which therefore must typically be an instance of NSMutableSet or a subclass of NSMutableSet.
// 4. Otherwise (no set of set mutation methods, simple accessor method, or instance variable is found), raises an NSUndefinedKeyException.
// Performance note: the repetitive -set<Key>: messages implied by step 2's description are a potential performance problem. For better performance implement methods that fulfill the requirements for step 1 in your KVC-compliant class.
// FoundationJava notes:
// - When the receiver is an instance of a Java class, member functions whose names match the patterns add<Key>Object(), remove<Key>Object(), add<Key>(), remove<Key>(), intersect<Key>(), and set<Key>() will be recognized in step 1.
// - The member function name pattern used in step 2 is set<Key>().
- (NSMutableSet *)mutableSetValueForKey:(NSString *)key;

#endif

// Key-path-taking variants of like-named methods. The default implementation of each parses the key path enough to determine whether or not it has more than one component (key path components are separated by periods). If so, -valueForKey: is invoked with the first key path component as the argument, and the method being invoked is invoked recursively on the result, with the remainder of the key path passed as an argument. If not, the like-named non-key-path-taking method is invoked.
- (id)valueForKeyPath:(NSString *)keyPath;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
- (void)setValue:(id)value forKeyPath:(NSString *)keyPath;
- (BOOL)validateValue:(id *)ioValue forKeyPath:(NSString *)inKeyPath error:(NSError **)outError;
- (NSMutableArray *)mutableArrayValueForKeyPath:(NSString *)keyPath;
#endif
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
- (NSMutableSet *)mutableSetValueForKeyPath:(NSString *)keyPath;
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3

// Given that an invocation of -valueForKey: would be unable to get a keyed value using its default access mechanism, return the keyed value using some other mechanism. The default implementation of this method raises an NSUndefinedKeyException.
- (id)valueForUndefinedKey:(NSString *)key;

// Given that an invocation of -setValue:forKey: would be unable to set the keyed value using its default mechanism, set the keyed value using some other mechanism. The default implementation of this method raises an NSUndefinedKeyException.
- (void)setValue:(id)value forUndefinedKey:(NSString *)key;

// Given that an invocation of -setValue:forKey: would be unable to set the keyed value because the type of the parameter of the corresponding accessor method is an NSNumber scalar type or NSValue structure type but the value is nil, set the keyed value using some other mechanism. The default implementation of this method raises an NSInvalidArgumentException. 
- (void)setNilValueForKey:(NSString *)key;

// Given an array of keys, return a dictionary containing the keyed attribute values, to-one-related objects, and/or collections of to-many-related objects. Entries for which -valueForKey: returns nil have NSNull as their value in the returned dictionary.
- (NSDictionary *)dictionaryWithValuesForKeys:(NSArray *)keys;

// Given a dictionary containing keyed attribute values, to-one-related objects, and/or collections of to-many-related objects, set the keyed values. Dictionary entries whose values are NSNull result in -setValue:nil forKey:key messages being sent to the receiver.
- (void)setValuesForKeysWithDictionary:(NSDictionary *)keyedValues;

#endif

@end

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3

@interface NSArray(NSKeyValueCoding)

// Return an array containing the results of invoking -valueForKey: on each of the receiver's elements. The returned array will contain NSNull elements for each instance of -valueForKey: returning nil.
- (id)valueForKey:(NSString *)key;

// Invoke -setValue:forKey: on each of the receiver's elements.
- (void)setValue:(id)value forKey:(NSString *)key;

@end

#endif

@interface NSDictionary(NSKeyValueCoding)

// Return the result of sending -objectForKey: to the receiver.
- (id)valueForKey:(NSString *)key;

@end

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3

@interface NSMutableDictionary(NSKeyValueCoding)

// Send -setObject:forKey: to the receiver, unless the value is nil, in which case send -removeObject:forKey:.
- (void)setValue:(id)value forKey:(NSString *)key;

@end

#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4

@interface NSSet(NSKeyValueCoding)

// Return a set containing the results of invoking -valueForKey: on each of the receiver's members. The returned set might not have the same number of members as the receiver. The returned set will not contain any elements corresponding to instances of -valueForKey: returning nil (in contrast with -[NSArray(NSKeyValueCoding) valueForKey:], which may put NSNulls in the arrays it returns).
- (id)valueForKey:(NSString *)key;

// Invoke -setValue:forKey: on each of the receiver's members.
- (void)setValue:(id)value forKey:(NSString *)key;

@end

#endif

@interface NSObject(NSDeprecatedKeyValueCoding)

// These methods were deprecated in Mac OS 10.3. Use the new, more consistently named, methods declared above instead.
- (void)takeValue:(id)value forKey:(NSString *)key;
- (void)takeValue:(id)value forKeyPath:(NSString *)keyPath;
- (id)handleQueryWithUnboundKey:(NSString *)key;
- (void)handleTakeValue:(id)value forUnboundKey:(NSString *)key;
- (void)unableToSetNilForKey:(NSString *)key;
- (NSDictionary *)valuesForKeys:(NSArray *)keys;
- (void)takeValuesFromDictionary:(NSDictionary *)properties;

// These methods were deprecated in Mac OS 10.4. If you are using the NSManagedObject class, use its -primitiveValueForKey: and -setPrimitiveValue:forKey: methods instead.
+ (BOOL)useStoredAccessor;
- (id)storedValueForKey:(NSString *)key;
- (void)takeStoredValue:(id)value forKey:(NSString *)key;

@end
