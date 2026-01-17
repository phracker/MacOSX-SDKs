//  
//  GCPhysicalInputElement.h
//  GameController
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 The \c GCPhysicalInputElement protocol is a base protocol for specific types
 of elements that represent controls on a device.
 */
API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0))
@protocol GCPhysicalInputElement <NSObject>

/**
 The set of aliases that can be used to access this element with keyed subscript
 notation.
 */
@property (copy, readonly) NSSet<NSString *> *aliases;

/**
 The element's localized display name.
 
 This is the string that your app should display in any on-screen messages
 instructing the user to interact with the control.  For example:
 
     "Press \(buttonA.localizedName) to jump!"
 
 Do not cache this value - it can change when the user remaps controls.
 */
@property (copy, readonly, nullable) NSString *localizedName;

/** The SF Symbols name for the element. */
@property (copy, readonly, nullable) NSString *sfSymbolsName;

@end



/**
 An instance of \c GCPhysicalInputElementCollection contains the collection of
 input elements found in a device's physical input profile.
 */
API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0)) NS_REFINED_FOR_SWIFT
@interface GCPhysicalInputElementCollection<Key: NSString*, __covariant Element: id<GCPhysicalInputElement>> : NSObject <NSFastEnumeration>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/** The number of elements in the collection. */
@property (readonly) NSUInteger count;

/**
 Returns the element associated with a given alias.
 
 @param alias
 The alias for which to return the corresponding element.  Typically, you
 pass one of the constants defined in \c GCInputNames.h.
 
 @return
 The element associated with \a alias, or nil if no element is associated
 with \a alias.
 */
- (Element _Nullable)elementForAlias:(Key)alias;
- (Element _Nullable)objectForKeyedSubscript:(Key)key;

- (NSEnumerator<Element> *)elementEnumerator;

@end

NS_ASSUME_NONNULL_END
