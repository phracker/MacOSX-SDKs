/*
	NSKeyValueObserving.h
	Copyright (c) 2003, Apple Computer, Inc.
	All rights reserved.
*/

#import <Foundation/NSArray.h>

#if MAC_OS_X_VERSION_10_3 <= MAC_OS_X_VERSION_MAX_ALLOWED

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

FOUNDATION_EXPORT NSString *NSKeyValueChangeKindKey;
FOUNDATION_EXPORT NSString *NSKeyValueChangeNewKey;
FOUNDATION_EXPORT NSString *NSKeyValueChangeOldKey;
FOUNDATION_EXPORT NSString *NSKeyValueChangeIndexesKey;

@interface NSObject(NSKeyValueObserving)

// Given that the receiver has been registered as an observer of the value at the key path relative to the object, be notified that the value has changed.  context is the same pointer that was passed in at observer-registration time, and the change dictionary contains the following entries:
// NSKeyValueChangeKindKey - An NSNumber containing an NSKeyValueChange, indicating what sort of change has happened (use -[NSNumber intValue]).  A value of NSKeyValueChangeSetting indicates that the observed object has received a -setValue:forKey: message, or that the key-value-coding-compliant set method for the key has been invoked, or that -willChangeValueForKey:/-didChangeValueForKey: has otherwise been invoked.  A value of NSKeyValueChangeInsertion, NSKeyValueChangeRemoval, or NSKeyValueChangeReplacement indicates that mutating messages have been sent to the array returned by a -mutableArrayValueForKey: message sent to the object, or that one of the key-value-coding-compliant array mutation methods for the key has been invoked, or that -willChange:valuesAtIndexes:forKey:/-didChange:valuesAtIndexes:forKey: has otherwise been invoked.
// NSKeyValueChangeNewKey - If the value of the NSKeyValueChangeKindKey entry is NSKeyValueChangeSetting, and NSKeyValueObservingOptionNew was specified when the observer was registered, the value after the setting has taken place (or an NSNull if the new value is nil).  For NSKeyValueChangeInsertion or NSKeyValueChangeReplacement, if NSKeyValueObservingOptionNew was specified when the observer was registered, an NSArray of the objects that have been inserted, or have replaced other objects, respectively.
// NSKeyValueChangeOldKey - If the value of the NSKeyValueChangeKindKey entry is NSKeyValueChangeSetting, and NSKeyValueObservingOptionOld was specified when the observer was registered, the value from before the setting took place (or an NSNull if the old value was nil).  For NSKeyValueChangeRemoval or NSKeyValueChangeReplacement, if NSKeyValueObservingOptionOld was specified when the observer was registered, an NSArray of the objects that have been removed, or have been replaced by other objects, respectively.
// NSKeyValueChangeIndexesKey - If the value of the NSKeyValueChangeKindKey entry is NSKeyValueChangeInsertion, NSKeyValueChangeRemoval, or NSKeyValueChangeReplacement, an NSIndexSet containing the indexes of the inserted, removed, or replaced objects.
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

@end

@interface NSObject(NSKeyValueObserverNotification)

// Prepare to send, and send, respectively, an -observeValueForKeyPath:ofObject:change:context: message whose kind is NSKeyValueChangeSetting to each registered observer of the receiver.
- (void)willChangeValueForKey:(NSString *)key;
- (void)didChangeValueForKey:(NSString *)key;

// Prepare to send, and send, respectively, an -observeValueForKeyPath:ofObject:change:context: message whose message is of the passed-in kind to each registered observer of the receiver.
- (void)willChange:(NSKeyValueChange)change valuesAtIndexes:(NSIndexSet *)indexes forKey:(NSString *)key;
- (void)didChange:(NSKeyValueChange)change valuesAtIndexes:(NSIndexSet *)indexes forKey:(NSString *)key;

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
