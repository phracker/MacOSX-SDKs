/*	NSValueTransformer.h
        Copyright (c) 2002-2017, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSArray<ObjectType>, NSString;

NS_ASSUME_NONNULL_BEGIN

typedef NSString *NSValueTransformerName NS_EXTENSIBLE_STRING_ENUM;

FOUNDATION_EXPORT NSValueTransformerName const NSNegateBooleanTransformerName	API_AVAILABLE(macos(10.3), ios(3.0), watchos(2.0), tvos(9.0));
FOUNDATION_EXPORT NSValueTransformerName const NSIsNilTransformerName		API_AVAILABLE(macos(10.3), ios(3.0), watchos(2.0), tvos(9.0));
FOUNDATION_EXPORT NSValueTransformerName const NSIsNotNilTransformerName		API_AVAILABLE(macos(10.3), ios(3.0), watchos(2.0), tvos(9.0));
FOUNDATION_EXPORT NSValueTransformerName const NSUnarchiveFromDataTransformerName	API_AVAILABLE(macos(10.3), ios(3.0), watchos(2.0), tvos(9.0));
FOUNDATION_EXPORT NSValueTransformerName const NSKeyedUnarchiveFromDataTransformerName	API_AVAILABLE(macos(10.5), ios(3.0), watchos(2.0), tvos(9.0));

NS_CLASS_AVAILABLE(10_3, 3_0)
@interface NSValueTransformer : NSObject {
}

// name-based registry for shared objects (especially used when loading nib files with transformers specified by name in Interface Builder) - also useful for localization (developers can register different kind of transformers or differently configured transformers at application startup and refer to them by name from within nib files or other code)
// if valueTransformerForName: does not find a registered transformer instance, it will fall back to looking up a class with the specified name - if one is found, it will instantiate a transformer with the default -init method and automatically register it
+ (void)setValueTransformer:(nullable NSValueTransformer *)transformer forName:(NSValueTransformerName)name;
+ (nullable NSValueTransformer *)valueTransformerForName:(NSValueTransformerName)name;
+ (NSArray<NSValueTransformerName> *)valueTransformerNames;

// information that can be used to analyze available transformer instances (especially used inside Interface Builder)
+ (Class)transformedValueClass;    // class of the "output" objects, as returned by transformedValue:
+ (BOOL)allowsReverseTransformation;    // flag indicating whether transformation is read-only or not

- (nullable id)transformedValue:(nullable id)value;           // by default returns value
- (nullable id)reverseTransformedValue:(nullable id)value;    // by default raises an exception if +allowsReverseTransformation returns NO and otherwise invokes transformedValue:

@end

NS_ASSUME_NONNULL_END
