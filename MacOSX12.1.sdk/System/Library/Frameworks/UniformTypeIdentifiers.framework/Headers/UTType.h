//
//  UTType.h
//
//  Copyright © 2020 Apple. All rights reserved.
//

#ifndef __UNIFORMTYPEIDENTIFIERS_UTTYPE__
#define __UNIFORMTYPEIDENTIFIERS_UTTYPE__

#import <Foundation/Foundation.h>

#import <UniformTypeIdentifiers/UTDefines.h>
#import <UniformTypeIdentifiers/UTTagClass.h>

__BEGIN_DECLS
NS_ASSUME_NONNULL_BEGIN
UT_AVAILABLE_BEGIN

/**
	\brief A class representing a type in a type hierarchy.

	Types may represent files on disk, abstract data types with no on-disk
	representation, or even entirely unrelated hierarchical classification
	systems such as hardware.

	Older API that does not use \c UTType typically uses an untyped \c NSString
	or \c CFStringRef to refer to a type by its identifier. To get the
	identifier of a type for use with these APIs, use the \c identifier property
	of this class.

	\sa https://developer.apple.com/library/archive/documentation/FileManagement/Conceptual/understanding_utis/
*/
UT_EXPORT_CLASS UT_SUBCLASSING_RESTRICTED @interface UTType : NSObject <NSCopying, NSSecureCoding>
+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/**
	\brief Create a type given a type identifier.

	\param identifier The type identifier.

	\result A type, or \c nil if the type identifier is not known to the system.
*/
+ (nullable instancetype)typeWithIdentifier:(NSString *)identifier;

/**
	\brief Create a type given a filename extension that conforms to
		\c UTTypeData.

	\param filenameExtension The filename extension for which a type is desired.

	\result A type. If no types are known to the system with the specified
		filename extension and conformance but the inputs were otherwise valid,
		a dynamic type may be provided. If the inputs were not valid, returns
		\c nil.

	This method is equivalent to:

\code
[UTType typeWithTag:filenameExtension tagClass:UTTagClassFilenameExtension conformingToType:UTTypeData]
\endcode

	To get the type of a file on disk, use the \c NSURLContentTypeKey property.
	You should not attempt to derive the type of a file system object based
	solely on its path extension.
*/
+ (nullable instancetype)typeWithFilenameExtension:(NSString *)filenameExtension;

/**
	\brief Create a type given a filename extension.

	\param filenameExtension The filename extension for which a type is desired.
	\param supertype Another type that the resulting type must conform to.
		 Typically, you would pass \c UTTypeData or \c UTTypePackage.

	\result A type. If no types are known to the system with the specified
		filename extension and conformance but the inputs were otherwise valid,
		a dynamic type may be provided. If the inputs were not valid, returns
		\c nil.

	This method is equivalent to:

\code
[UTType typeWithTag:filenameExtension tagClass:UTTagClassFilenameExtension conformingToType:supertype]
\endcode

	To get the type of a file on disk, use the \c NSURLContentTypeKey property.
	You should not attempt to derive the type of a file system object based
	solely on its path extension.
*/
+ (nullable instancetype)typeWithFilenameExtension:(NSString *)filenameExtension conformingToType:(UTType *)supertype;

/**
	\brief Create a type given a MIME type that conforms to \c UTTypeData.

	\param mimeType The MIME type for which a type is desired.

	\result A type. If no types are known to the system with the specified
		MIME type and conformance but the inputs were otherwise valid, a dynamic
		type may be provided. If the inputs were not valid, returns \c nil.

	This method is equivalent to:

\code
[UTType typeWithTag:mimeType tagClass:UTTagClassMIMEType conformingToType:UTTypeData]
\endcode
*/
+ (nullable instancetype)typeWithMIMEType:(NSString *)mimeType;

/**
	\brief Create a type given a MIME type.

	\param mimeType The MIME type for which a type is desired.
	\param supertype Another type that the resulting type must conform to.
		Typically, you would pass \c UTTypeData.

	\result A type. If no types are known to the system with the specified
		MIME type and conformance but the inputs were otherwise valid, a dynamic
		type may be provided. If the inputs were not valid, returns \c nil.

	This method is equivalent to:

\code
[UTType typeWithTag:mimeType tagClass:UTTagClassMIMEType conformingToType:supertype]
\endcode
*/
+ (nullable instancetype)typeWithMIMEType:(NSString *)mimeType conformingToType:(UTType *)supertype;

/**
	\brief The receiver's identifier.

 	A type is \em identified \em by its Uniform Type Identifier (UTI), a
	reverse-DNS string such as \c "public.jpeg" or \c "com.adobe.pdf". The type
	itself \em has a UTI, but is not itself the UTI. This terminology is not
	consistently used across Apple's documentation.
*/
@property (readonly) NSString *identifier;

/**
	\brief If available, the preferred (first available) tag of class
		\c UTTagClassFilenameExtension.

	Many uses of types require the generation of a filename (e.g. when saving a
	file to disk.) If not \c nil, the value of this property is the best
	available filename extension for the given type. The value of this property
	is equivalent to, but more efficient than:

\code
type.tags[UTTagClassFilenameExtension].firstObject
\endcode
*/
@property (readonly, nullable) NSString *preferredFilenameExtension;

/**
	\brief If available, the preferred (first available) tag of class
		\c UTTagClassMIMEType.

	If not \c nil, the value of this property is the best available MIME type
	for the given type, according to its declaration. The value of this property
	is equivalent to, but more efficient than:

\code
type.tags[UTTagClassMIMEType].firstObject
\endcode
*/
@property (readonly, nullable) NSString *preferredMIMEType;

/**
	\brief The localized description of the type.

	If the type does not provide a description, the system may search its
	supertypes for one. Dynamic types never have localized descriptions even if
	their supertypes do.
*/
@property (readonly, nullable) NSString *localizedDescription;

/**
	\brief The type's version.

	Most types do not specify a version.
*/
@property (readonly, nullable) NSNumber *version;

/**
	\brief The reference URL of the type.

	A reference URL is a human-readable document describing a type. Most types
	do not specify reference URLs.

	\warning This URL is not validated in any way by the system, nor is its
		scheme or structure guaranteed in any way.
*/
@property (readonly, nullable) NSURL *referenceURL;

/**
	\brief Whether or not the receiver is a dynamically generated type.

	Dynamic types are recognized by the system, but may not be directly declared
	or claimed by an application. They are used when a file is encountered whose
	metadata has no corresponding type known to the system.

	A type cannot be both declared \em and dynamic.
*/
@property (readonly, getter=isDynamic) BOOL dynamic;

/**
	\brief Whether or not the receiver is a type known to the system.

	A type cannot be both declared \em and dynamic.
*/
@property (readonly, getter=isDeclared) BOOL declared;

/**
	\brief Whether or not the type is in the public domain.

	Types in the public domain have identifiers starting with \c "public." and
	are generally defined by a standards body or by convention. They are never
	dynamic.
*/
@property (readonly, getter=isPublicType) BOOL publicType;
@end

#pragma mark -

@interface UTType (Conformance)
/**
	\brief Tests for a conformance relationship between the receiver and another
		type.

	\param type The type against which conformance should be tested.

	\result If the two types are equal, returns \c YES. If the receiver
		conforms, directly or indirectly, to \a type, returns \c YES. Otherwise,
		returns \c NO.

	\sa -isSupertypeOfType:
	\sa -isSubtypeOfType:
*/
- (BOOL)conformsToType:(UTType *)type;

/**
	\brief Tests if the receiver is a supertype of another type.

	\param type The type against which conformance should be tested.

	\result If \a type conforms, directly or indirectly, to the receiver and is
		not equal to it, returns \c YES. Otherwise, returns \c NO.

	\sa -conformsToType:
	\sa -isSubtypeOfType:
*/
- (BOOL)isSupertypeOfType:(UTType *)type;

/**
	\brief Tests if the receiver is a subtype of another type.

	\param type The type against which conformance should be tested.

	\result If the receiver conforms, directly or indirectly, to \a type and is
		not equal to it, returns \c YES. Otherwise, returns \c NO.

	\sa -conformsToType:
	\sa -isSupertypeOfType:
*/
- (BOOL)isSubtypeOfType:(UTType *)type;

/**
	\brief The set of types to which the receiving type conforms, directly or
		indirectly.

	If you are just interested in checking if one type conforms to another, it
	is more efficient to use \c -conformsToType: than this property.
*/
@property (readonly) NSSet<UTType *> *supertypes;
@end

#pragma mark -

@interface UTType (UTTagSpecification)
/**
	\brief Create a type given a type tag.

	\param tag The tag, such as the path extension, for which a type is desired.
	\param tagClass The class of the tag, such as \c UTTagClassFilenameExtension.
	\param supertype Another type that the resulting type must conform to. If
		\c nil, no conformance is required.

	\result A type. If no types are known to the system with the specified tag
		but the inputs were otherwise valid, a dynamic type may be provided. If
		the inputs were not valid, returns \c nil.
*/
+ (nullable instancetype)typeWithTag:(NSString *)tag tagClass:(NSString *)tagClass conformingToType:(nullable UTType *)supertype;

/**
	\brief Create an array of types given a type tag.

	\param tag The tag, such as the path extension, for which a set of types is
		desired.
	\param tagClass The class of the tag, such as \c UTTagClassFilenameExtension.
	\param supertype Another type that the resulting types must conform to. If
		\c nil, no conformance is required.

	\result An array of types, or the empty array if no such types were
		available. If no types are known to the system with the specified tag
		but the inputs were otherwise valid, a dynamic type may be provided.
*/
+ (NSArray<UTType *> *)typesWithTag:(NSString *)tag tagClass:(NSString *)tagClass conformingToType:(nullable UTType *)supertype;

/**
	\brief The tag specification dictionary of the type.

	The system does not store tag information for non-standard tag classes. It
	normalizes string values into arrays containing those strings. For instance,
	a value of:

\code
{
	"public.mime-type": "x/y",
	"nonstandard-tag-class": "abc",
}
\endcode

Is normalized to:

\code
{
	"public.mime-type": [ "x/y" ]
}
\endcode

	If you are simply looking for the preferred filename extension or MIME
	type of a type, it is more efficient for you to use the
	\c preferredFilenameExtension and \c preferredMIMEType properties
	respectively.
*/
@property (readonly) NSDictionary<NSString *, NSArray<NSString *> *> *tags;
@end

#pragma mark -

@interface UTType (LocalConstants)
/**
	\brief Gets an active \c UTType corresponding to a type that is declared as
		"exported" by the current process.

	\param identifier The type identifier for which a type is desired.

	\result A type.

	Use this method to get types that are exported by your application. If
	\a identifier does not correspond to any type known to the system, the
	result is undefined.

	Conformance to either \c UTTypeData or \c UTTypePackage is assumed.

	You would generally use this method with \c dispatch_once():

\code
UTType *GetMyFileFormat(void) {
	static UTType *result = nil;

	static dispatch_once_t once;
	dispatch_once(&once, ^ {
		result = [UTType exportedTypeWithIdentifier:@"com.example.myfileformat"];
	});

	return result;
}
\endcode
*/
+ (UTType *)exportedTypeWithIdentifier:(NSString *)identifier;

/**
	\brief Gets an active \c UTType corresponding to a type that is declared as
		"exported" by the current process.

	\param identifier The type identifier for which a type is desired.
	\param parentType A parent type that the resulting type is expected to
		conform to.

	\result A type.

	Use this method to get types that are exported by your application. If
	\a identifier does not correspond to any type known to the system, the
	result is undefined.

	You would generally use this method with \c dispatch_once():

\code
UTType *GetMyFileFormat(void) {
	static UTType *result = nil;

	static dispatch_once_t once;
	dispatch_once(&once, ^ {
		result = [UTType exportedTypeWithIdentifier:@"com.example.myfileformat" conformingToType:UTTypeData];
	});

	return result;
}
\endcode
*/
+ (UTType *)exportedTypeWithIdentifier:(NSString *)identifier conformingToType:(UTType *)parentType;

/**
	\brief Gets an active \c UTType corresponding to a type that is declared as
		"imported" by the current process.

	\param identifier The type identifier for which a type is desired.

	\result A type whose identifier may or may not be equal to \a identifier,
		but which is functionally equivalent.

	Use this method to get types that are imported by your application. If
	\a identifier does not correspond to any type known to the system, the
	result is undefined.

	Conformance to either \c UTTypeData or \c UTTypePackage is assumed.

	You would generally use this method in the body of a funcion or method and
	would \em not use \c dispatch_once() as the type can change over time:

\code
UTType *GetCompetitorFileFormat(void) {
	return [UTType importedTypeWithIdentifier:@"com.example.competitorfileformat"];
}
\endcode

	In the general case, this method returns a type with the same identifier,
	but if that type has a preferred filename extension and \em another type is
	the preferred type for that extension, then that \em other type is
	substituted.
*/
+ (UTType *)importedTypeWithIdentifier:(NSString *)identifier;

/**
	\brief Gets an active \c UTType corresponding to a type that is declared as
		"imported" by the current process.

	\param identifier The type identifier for which a type is desired.
	\param parentType A parent type that the resulting type is expected to
		conform to.

	\result A type whose identifier may or may not be equal to \a identifier,
		but which is functionally equivalent.

	Use this method to get types that are imported by your application. If
	\a identifier does not correspond to any type known to the system, the
	result is undefined.

	You would generally use this method in the body of a funcion or method and
	would \em not use \c dispatch_once() as the type can change over time:

\code
UTType *GetCompetitorFileFormat(void) {
	return [UTType importedTypeWithIdentifier:@"com.example.competitorfileformat" conformingToType:UTTypeData];
}
\endcode

	In the general case, this method returns a type with the same identifier,
	but if that type has a preferred filename extension and \em another type is
	the preferred type for that extension, then that \em other type is
	substituted.
*/
+ (UTType *)importedTypeWithIdentifier:(NSString *)identifier conformingToType:(UTType *)parentType;
@end

UT_AVAILABLE_END
NS_ASSUME_NONNULL_END
__END_DECLS

#endif // __UNIFORMTYPEIDENTIFIERS_UTTYPE__
