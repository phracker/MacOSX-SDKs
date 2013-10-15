// EOModelExtensions.h
// Copyright (c) 1996, 1998 Apple Computer, Inc.
// All rights reserved.

#import <EOInterface/EOInterface.h>
#import <EOAccess/EOAccess.h>

@interface EOEntity (EOModelExtensions)
- (NSArray *)classAttributes;
- (NSArray *)classScalarAttributes;
- (NSArray *)classNonScalarAttributes;
- (NSArray *)classToManyRelationships;
- (NSArray *)classToOneRelationships;
- (NSArray *)referencedClasses;
    // non-generic record relationship destination classNames
- (NSString *)referenceClassName;
- (NSString *)referenceJavaClassName;
    // Returns "id" (or "CustomObject" fo Java") if className == "EOGenericRecord"
    // or "<className> *" otherwise
- (NSString *)parentClassName;
- (NSString *)javaParentClassName;
    // Returns "NSObject" (or "CustomObject" for Java) for EOGenericRecord's
    // or the className otherwise
- (NSArray *)arrayWithParentClassNameIfNeeded;
    // This methods will return an array with the className of the entity's
    // parentEntity if the entity has a parent and that parent has a class
    // name. This method is used in the EOInterfaceFile.template and
    // EOJavaClass.template files in order to get the parent's class imported
    // before we declare the class which subclasses from it.
- (NSString *)classNameWithoutPackage;
    // Class name for the entity, but without the package prefix
- (NSArray *)classPackage;
    // If the className has a package, this method will return an
    // array of one item, the package name. If there is no package name,
    // This method will return an empty array.
@end

@interface EOAttribute (EOModelExtensions)
- (BOOL)isScalar;
- (NSString *)cScalarTypeString;
- (BOOL)isDeclaredBySuperClass;
    // is attribute inherited from a real class, so it does not need to be declared again?
- (NSString *)javaValueClassName;
    // Converts objective-C classes (NSNumber, NSCalendarDate, etc.) to their
    // wrapped equivalents (com.apple.yellow.foundation.NSGregorianDate)
@end

@interface EORelationship (EOModelExtensions)
- (BOOL)isDeclaredBySuperClass;
    // is relationShip inherited from a real class, so it does not need to be declared again?
@end

@interface NSMutableAttributedString (_EOModelerErrorConstruction)
+ (NSMutableAttributedString *)mutableAttributedStringWithBoldSubstitutionsWithFormat:(NSString *)format, ...;
    // This method doesn't handle most format strings. Actually, it expects
    // every substitution to be "%@" and every variable to be an NSString.
    // Kind of limited, but it works well for generating errors messages for
    // consistency checking.
@end

