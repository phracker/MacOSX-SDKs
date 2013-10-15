/*
	NSKeyValueObserving.h
	Copyright (c) 2003-2005, Apple Computer, Inc.
	All rights reserved.
*/

#import <Foundation/NSArray.h>
#import <Foundation/NSSet.h>

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3

@class NSIndexSet, NSString;

enum {
    NSKeyValueObservingOptionNew = 0x01,
    NSKeyValueObservingOptionOld = 0x02
};
typedef unsigned int NSKeyValueObservingOptions;

typedef enum {
    NSKeyValueChangeSetting = 1,
    NSKeyValueChangeInsertion = 2,
    NSKeyValueChangeRemoval = 3,
    NSKeyValueChangeReplacement = 4
} NSKeyValueChange;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4

// Possible values for the second argument of -willChangeValueForKey:withSetMutation:usingObjects: and -didChangeValueForKey:withSetMutation:usingObjects:.
typedef enum {
    
    // The set representing an unordered to-many relationship is being changed using NSMutableSet's -unionSet:, -minusSet:, -intersectSet:, or -setSet: method, or something that has the same semantics.
    NSKeyValueUnionSetMutation = 1,
    NSKeyValueMinusSetMutation = 2,
    NSKeyValueIntersectSetMutation = 3,
    NSKeyValueSetSetMutation = 4
    
} NSKeyValueSetMutationKind;

#endif

FOUNDATION_EXPORT NSString *const NSKeyValueChangeKindKey AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
FOUNDATION_EXPORT NSString *const NSKeyValueChangeNewKey AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
FOUNDATION_EXPORT NSString *const NSKeyValueChangeOldKey AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
FOUNDATION_EXPORT NSString *const NSKeyValueChangeIndexesKey AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

@interface NSObject(NSKeyValueObserving)

// Given that the receiver has been registered as an observer of the value at a key path relative to an object, be notified that the value has changed. The change dictionary always contains an NSKeyValueChangeKindKey entry whose value is an NSNumber wrapping an NSKeyValueChange (use -[NSNumber intValue]). The meaning of NSKeyValueChange depends on what sort of property is identified by the key path:
// - For any sort of property (attribute, to-one relationship, or ordered or unordered to-many relationship) NSKeyValueChangeSetting indicates that the observed object has received a -setValue:forKey: message, or that the key-value coding-compliant set method for the key has been invoked, or that a -willChangeValueForKey:/-didChangeValueForKey: pair has otherwise been invoked.
// - For an _ordered_ to-many relationship, NSKeyValueChangeInsertion, NSKeyValueChangeRemoval, and NSKeyValueChangeReplacement indicate that a mutating message has been sent to the array returned by a -mutableArrayValueForKey: message sent to the object, or that one of the key-value coding-compliant array mutation methods for the key has been invoked, or that a -willChange:valuesAtIndexes:forKey:/-didChange:valuesAtIndexes:forKey: pair has otherwise been invoked.
// - For an _unordered_ to-many relationship (introduced in Mac OS 10.4), NSKeyValueChangeInsertion, NSKeyValueChangeRemoval, and NSKeyValueChangeReplacement indicate that a mutating message has been sent to the set returned by a -mutableSetValueForKey: message sent to the object, or that one of the key-value coding-compliant set mutation methods for the key has been invoked, or that a -willChangeValueForKey:withSetMutation:usingObjects:/-didChangeValueForKey:withSetMutation:usingObjects: pair has otherwise been invoked.
// For any sort of property, the change dictionary always contains an NSKeyValueChangeNewKey entry if NSKeyValueObservingOptionNew was specified at observer-registration time, likewise for NSKeyValueChangeOldKey if NSKeyValueObservingOptionOld was specified. See the comments for the NSKeyValueObserverNotification informal protocol methods for what the values of those entries will be.
// For an _ordered_ to-many relationship, the change dictionary always contains an NSKeyValueChangeIndexesKey entry whose value is an NSIndexSet containing the indexes of the inserted, removed, or replaced objects, unless the change is an NSKeyValueChangeSetting.
//  context is always the same pointer that was passed in at observer-registration time.
- (void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object change:(NSDictionary *)change context:(void *)context;

@end

@interface NSObject(NSKeyValueObserverRegistration)

// Register or deregister as an observer of the value at a key path relative to the receiver.  The options determine what is included in observer notifications as described above, and the context is passed in observer notifications as described above.
- (void)addObserver:(NSObject *)observer forKeyPath:(NSString *)keyPath options:(NSKeyValueObservingOptions)options context:(void *)context;
- (void)removeObserver:(NSObject *)observer forKeyPath:(NSString *)keyPath;

@end

@interface NSArray(NSKeyValueObserverRegistration)

// Register or deregister as an observer of the values at a key path relative to each indexed element of the array.  The options determine what is included in observer notifications as described above, and the context is passed in observer notifications as described above.  This is not merely a convenience method; invoking this this is potentially much faster than repeatedly invoking -[NSObject(NSKeyValueObserverRegistration) addObserver:forKeyPath:options:context:].
- (void)addObserver:(NSObject *)observer toObjectsAtIndexes:(NSIndexSet *)indexes forKeyPath:(NSString *)keyPath options:(NSKeyValueObservingOptions)options context:(void *)context;
- (void)removeObserver:(NSObject *)observer fromObjectsAtIndexes:(NSIndexSet *)indexes forKeyPath:(NSString *)keyPath;

// NSArrays are not observable, so these methods raise exceptions when invoked on NSArrays. Instead of observing an array, observe the ordered to-many relationship for which the array is the collection of related objects.
- (void)addObserver:(NSObject *)observer forKeyPath:(NSString *)keyPath options:(NSKeyValueObservingOptions)options context:(void *)context;
- (void)removeObserver:(NSObject *)observer forKeyPath:(NSString *)keyPath;

@end

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4

@interface NSSet(NSKeyValueObserverRegistration)

// NSSets are not observable, so these methods raise exceptions when invoked on NSSets. Instead of observing a set, observe the unordered to-many relationship for which the set is the collection of related objects.
- (void)addObserver:(NSObject *)observer forKeyPath:(NSString *)keyPath options:(NSKeyValueObservingOptions)options context:(void *)context;
- (void)removeObserver:(NSObject *)observer forKeyPath:(NSString *)keyPath;

@end

#endif

@interface NSObject(NSKeyValueObserverNotification)

// Given a key that identifies a property (attribute, to-one relationship, or ordered or unordered to-many relationship), prepare to send, and send, respectively, an -observeValueForKeyPath:ofObject:change:context: notification message whose kind is NSKeyValueChangeSetting to each of the receiver's observers registered for the key. Invocations of these methods must always be paired. The change dictionaries in notifications resulting from use of these methods will contain optional entries if requested at observer registration time:
// - The NSKeyValueChangeOldKey entry, if present, contains the value returned by -valueForKey: at the instant that -willChangeValueForKey: is invoked (or an NSNull if -valueForKey: returns nil).
// - The NSKeyValueChangeNewKey entry, if present, contains the value returned by -valueForKey: at the instant that -didChangeValueForKey: is invoked (or an NSNull if -valueForKey: returns nil).
- (void)willChangeValueForKey:(NSString *)key;
- (void)didChangeValueForKey:(NSString *)key;

// Given a key that identifies an _ordered_ to-many relationship, prepare to send, and send, respectively, an -observeValueForKeyPath:ofObject:change:context: message of the passed-in change kind to each of the receiver's observers registered for the key. The passed-in kind must be NSKeyValueChangeInsertion, NSKeyValueChangeRemoval, or NSKeyValueChangeReplacement. The passed-in index set must be the indexes of the objects being inserted, removed, or replaced. Invocations of these methods must always be paired, with identical arguments. The change dictionaries in notifications resulting from use of these methods will contain optional entries if requested at observer registration time:
// - The NSKeyValueChangeOldKey entry, if present (only for NSKeyValueChangeRemoval and NSKeyValueChangeReplacement), contains an array of the indexed objects from the array returned by -valueForKey: at the instant that -willChangeValueForKey:valuesAtIndexes:forKey: is invoked.
// - The NSKeyValueChangeNewKey entry, if present (only for NSKeyValueChangeInsertion and NSKeyValueChangeReplacement), contains an array of the indexed objects from the array returned by -valueForKey: at the instant that -didChangeValueForKey:valuesAtIndexes:forKey: is invoked.
- (void)willChange:(NSKeyValueChange)changeKind valuesAtIndexes:(NSIndexSet *)indexes forKey:(NSString *)key;
- (void)didChange:(NSKeyValueChange)changeKind valuesAtIndexes:(NSIndexSet *)indexes forKey:(NSString *)key;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4

// Given a key that identifies an _unordered_ to-many relationship, prepare to send, and send, respectively, an -observeValueForKeyPath:ofObject:change:context: message. The passed-in mutation kind corresponds to an NSMutableSet method. The passed-in set must contain the set that would be passed to the corresponding NSMutableSet method. Invocations of these methods must always be paired, with identical arguments. The change dictionaries in notifications resulting from use of these methods always contain an NSKeyValueChangeKindKey entry. Its value will depend on the passed-in mutationKind value:
// - NSKeyValueUnionSetMutation -> NSKeyValueChangeInsertion
// - NSKeyValueMinusSetMutation -> NSKeyValueChangeRemoval
// - NSKeyValueIntersectSetMutation -> NSKeyValueChangeRemoval
// - NSKeyValueSetSetMutation -> NSKeyValueChangeReplacement
// The change dictionary may also contain optional entries:
// - The NSKeyValueChangeOldKey entry, if present (only for for NSKeyValueChangeRemoval and NSKeyValueChangeReplacement), contains the set of objects that were removed.
// - The NSKeyValueChangeNewKey entry, if present (only for NSKeyValueChangeInsertion and NSKeyValueChangeReplacement), contains the set of objects that were added.
- (void)willChangeValueForKey:(NSString *)key withSetMutation:(NSKeyValueSetMutationKind)mutationKind usingObjects:(NSSet *)objects;
- (void)didChangeValueForKey:(NSString *)key withSetMutation:(NSKeyValueSetMutationKind)mutationKind usingObjects:(NSSet *)objects;

#endif

@end

@interface NSObject(NSKeyValueObservingCustomization)

// Return yes if the key value observing machinery should automatically invoke -willChangeValueForKey:/-didChangeValueForKey: and -willChange:valuesAtIndexes:forKey:/-didChange:valuesAtIndexes:forKey: whenever instances of the class receive key value coding messages for the key, or mutating key-value-coding-compliant methods for the key are invoked.  Return no otherwise.  The default implementation returns yes.
+ (BOOL)automaticallyNotifiesObserversForKey:(NSString *)key;

// Register the fact that invocations of -willChangeValueForKey:/-didChangeValueForKey: and -willChange:valuesAtIndexes:forKey:/-didChange:valuesAtIndexes:forKey: for any key in the passed-in array should automatically invoke the same methods for the dependent key.
+ (void)setKeys:(NSArray *)keys triggerChangeNotificationsForDependentKey:(NSString *)dependentKey;

// Take or return a pointer that identifies information about all of the observers that are registered with the receiver, the options that were used at registration-time, etc.  The default implementation of these methods store observation info in a global dictionary keyed by the receivers' pointers.  For improved performance, these methods can be overridden to store the opaque data pointer in an instance variable.  Overrides of these methods must not attempt to send Objective-C messages to the passed-in observation info, including -retain and -release.
- (void)setObservationInfo:(void *)observationInfo;
- (void *)observationInfo;

@end

#endif
