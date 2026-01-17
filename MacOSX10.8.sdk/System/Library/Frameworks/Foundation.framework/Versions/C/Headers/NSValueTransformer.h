/*	NSValueTransformer.h
        Copyright (c) 2002-2012, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSArray, NSString;

FOUNDATION_EXPORT NSString * const NSNegateBooleanTransformerName	NS_AVAILABLE(10_3, 3_0);
FOUNDATION_EXPORT NSString * const NSIsNilTransformerName		NS_AVAILABLE(10_3, 3_0);
FOUNDATION_EXPORT NSString * const NSIsNotNilTransformerName		NS_AVAILABLE(10_3, 3_0);
FOUNDATION_EXPORT NSString * const NSUnarchiveFromDataTransformerName	NS_AVAILABLE(10_3, 3_0);
FOUNDATION_EXPORT NSString * const NSKeyedUnarchiveFromDataTransformerName	NS_AVAILABLE(10_5, 3_0);

NS_CLASS_AVAILABLE(10_3, 3_0)
@interface NSValueTransformer : NSObject {
}

// name-based registry for shared objects (especially used when loading nib files with transformers specified by name in Interface Builder) - also useful for localization (developers can register different kind of transformers or differently configured transformers at application startup and refer to them by name from within nib files or other code)
// if valueTransformerForName: does not find a registered transformer instance, it will fall back to looking up a class with the specified name - if one is found, it will instantiate a transformer with the default -init method and automatically register it
+ (void)setValueTransformer:(NSValueTransformer *)transformer forName:(NSString *)name;
+ (NSValueTransformer *)valueTransformerForName:(NSString *)name;
+ (NSArray *)valueTransformerNames;

// information that can be used to analyze available transformer instances (especially used inside Interface Builder)
+ (Class)transformedValueClass;    // class of the "output" objects, as returned by transformedValue:
+ (BOOL)allowsReverseTransformation;    // flag indicating whether transformation is read-only or not

- (id)transformedValue:(id)value;           // by default returns value
- (id)reverseTransformedValue:(id)value;    // by default raises an exception if +allowsReverseTransformation returns NO and otherwise invokes transformedValue:

@end

