//
//  NSKeyValueSharedObservers.h
//  Foundation
//
//  Copyright (c) 2024, Apple Inc.
//  All rights reserved.
//

#import <Foundation/NSKeyValueObserving.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// A collection of key-value observations which may be registered with multiple
/// observable objects. Create using ``-[NSKeyValueSharedObservers snapshot]``
API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0), visionos(2.0))
@interface NSKeyValueSharedObserversSnapshot: NSObject
- (id)init NS_UNAVAILABLE;
+ (id)new NS_UNAVAILABLE;
@end

/// A collection of key-value observations which may be registered with multiple
/// observable objects
API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0), visionos(2.0))
@interface NSKeyValueSharedObservers: NSObject
/// A new collection of observables for an observable object of the given class
- (id)initWithObservableClass:(Class)observableClass;
- (id)init NS_UNAVAILABLE;
+ (id)new NS_UNAVAILABLE;

/// Add a new observer to the collection.
///
/// This method works like `-[NSObject addObserver: forKey: options: context:]`,
/// but observations on nested and computed properties are disallowed. Observers
/// are not registered until `setSharedObservers` is called on the observable.
///
/// - Parameter observer: The observer object to register for KVO notifications.
///   The observer must implement the key-value observing method ``observeValue:
///   forKeyPath: of: change: context:``
/// - Parameter key: key of the property being observed. This cannot be a nested
///   key path or a computed property
/// - Parameter options: A combination of NSKeyValueObservingOptions values that
///   specify what is included in observation notifications. For possible values
///   see NSKeyValueObservingOptions.
/// - Parameter context: Arbitrary data which is passed to the observer object
- (void)addSharedObserver:(NSObject *)observer
                   forKey:(NSString *)key
                  options:(NSKeyValueObservingOptions)options
                  context:(nullable void *)context;

- (void)addObserver:(NSObject *)observer forKeyPath:(NSString *)keyPath options:(NSKeyValueObservingOptions)options context:(nullable void *)context NS_UNAVAILABLE;

/// A momentary snapshot of all observers added to the collection thus far, that
/// can be assigned to an observable using ``-[NSObject setSharedObservers:]``
- (NSKeyValueSharedObserversSnapshot *)snapshot;
@end

@interface NSObject(NSKeyValueSharedObserverRegistration)
/// Register shared observations.
///
/// A shared observation collection might be shared between multiple observables
/// to minimise registration work. Shared observers remain registered throughout
/// the object's lifetime and do not need to be removed using `removeObserver:`.
///
/// An observable may only have one set of shared observations. Subsequent calls
/// to this method will replace existing shared observations.
///
/// - Parameter sharedObservers: shared observer collection that was initialized
///   with the class of this object
/// - Invariant: `sharedObserers` was initialized with the class of this object
/// - Throws: Exception if the class of the receiving observable object does not
///   match the class with which `sharedObserers` was initialized.
- (void)setSharedObservers:(NSKeyValueSharedObserversSnapshot * _Nullable)sharedObservers API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0), visionos(2.0));


@end

NS_HEADER_AUDIT_END(nullability, sendability)
