//
//  UTAdditions.h
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#ifndef __UNIFORMTYPEIDENTIFIERS_UTADDITIONS__
#define __UNIFORMTYPEIDENTIFIERS_UTADDITIONS__

#import <UniformTypeIdentifiers/UTDefines.h>
#import <UniformTypeIdentifiers/UTType.h>

#import <Foundation/Foundation.h>

__BEGIN_DECLS
NS_ASSUME_NONNULL_BEGIN
UT_AVAILABLE_BEGIN

@interface NSString (UTAdditions)
/**
	\brief Generate a path component based on a partial filename and a file
		type, then append it to a copy of the receiver.

	\param partialName The partial filename that should be expanded upon,
		e.g. \c "readme".
	\param contentType The type the resulting file should conform to, e.g.
		\c UTTypePlainText.

	\result A complete file path. Using the argument examples above, this method
		would return a string with a last path component of \c "readme.txt".

	Use this method when you have partial input from a user or other source and
	need to produce a complete filename suitable for that input. For example, if
	you are downloading a file from the Internet and know its MIME type, you can
	use this method to ensure the correct filename extension is applied to the
	URL where you save the file.

	If \a partialName already has a path extension, and that path extension is
	valid for file system objects of type \a contentType, no additional
	extension is appended to the path component before constructing the string.
	For example, if the inputs are \c "puppy.jpg" and \c UTTypeImage
	respectively, then the resulting string will have a last path component of
	\c "puppy.jpg" . On the other hand, if the inputs are \c "puppy.jpg" and
	\c UTTypePlainText respectively, the resulting string will have a last path
	component of \c "puppy.jpg.txt" . If you want to ensure any existing path
	extension is replaced, you can use the \c stringByDeletingPathExtension
	property first.

	If the path component could not be appended, this method returns a copy of
	\c self .
*/
- (NSString *)stringByAppendingPathComponent:(NSString *)partialName conformingToType:(UTType *)contentType;

/**
	\brief Generate a string based on a partial filename or path and a
		file type.

	\param contentType The type the resulting file should conform to, e.g.
		\c UTTypePlainText.

	\result A complete file path. Using the argument example above and assuming
		the receiver equals \c "readme" , this method would return
		\c "readme.txt".

	Use this method when you have partial input from a user or other source and
	need to produce a complete filename suitable for that input. For example, if
	you are downloading a file from the Internet and know its MIME type, you can
	use this method to ensure the correct filename extension is applied to the
	URL where you save the file.

	If the receiver already has a path extension, and that path extension is
	valid for file system objects of type \a contentType, no additional
	extension is appended to the receiver before constructing the result.
	For example, if the receiver equals \c "puppy.jpg" and \a contentType equals
	\c UTTypeImage , then the resulting string will equal \c "puppy.jpg" . On
	the other hand, if the inputs are \c "puppy.jpg" and \c UTTypePlainText
	respectively, the resulting string will equal \c "puppy.jpg.txt" . If you
	want to ensure any existing path extension is replaced, you can use the
	\c stringByDeletingPathExtension property first.

	If the extension could not be appended, this method returns a copy of
	\c self .
*/
- (NSString *)stringByAppendingPathExtensionForType:(UTType *)contentType;
@end

#pragma mark -

@interface NSURL (UTAdditions)
/**
	\brief Generate a path component based on a partial filename and a file
		type, then append it to a copy of the receiver.

	\param partialName The partial filename that should be expanded upon,
		e.g. \c "readme".
	\param contentType The type the resulting file should conform to, e.g.
		\c UTTypePlainText.

	\result A complete URL. Using the argument examples above, this method would
		return a URL with a last path component of \c "readme.txt".

	Use this method when you have partial input from a user or other source and
	need to produce a complete filename suitable for that input. For example, if
	you are downloading a file from the Internet and know its MIME type, you can
	use this method to ensure the correct filename extension is applied to the
	URL where you save the file.

	If \a partialName already has a path extension, and that path extension is
	valid for file system objects of type \a contentType, no additional
	extension is appended to the path component before constructing the URL. For
	example, if the inputs are \c "puppy.jpg" and \c UTTypeImage respectively,
	then the resulting URL will have a last path component of \c "puppy.jpg" .
	On the other hand, if the inputs are \c "puppy.jpg" and \c UTTypePlainText
	respectively, the resulting URL will have a last path component of
	\c "puppy.jpg.txt" . If you want to ensure any existing path extension is
	replaced, you can use the \c URLByDeletingPathExtension property first.

	If the path component could not be appended, this method returns a copy of
	\c self .

	\note The resulting URL has a directory path if \c contentType conforms to
		\c UTTypeDirectory .
*/
- (NSURL *)URLByAppendingPathComponent:(NSString *)partialName conformingToType:(UTType *)contentType;

/**
	\brief Generate a path component based on the last path component of the
		receiver and a file type, then append it to a copy of the receiver.

	\param contentType The type the resulting file should conform to, e.g.
		\c UTTypePlainText.

	\result A complete URL. Using the argument example above and assuming
		the receiver equals \c "file:///readme" , this method would return
		\c "file:///readme.txt".

	Use this method when you have partial input from a user or other source and
	need to produce a complete filename suitable for that input. For example, if
	you are downloading a file from the Internet and know its MIME type, you can
	use this method to ensure the correct filename extension is applied to the
	URL where you save the file.

	If the receiver already has a path extension, and that path extension is
	valid for file system objects of type \a contentType, no additional
	extension is appended to the path component before constructing the URL.
	For example, if the receiver's last path component equals \c "puppy.jpg" and
	\a contentType equals \c UTTypeImage , then the resulting URL will have a
	last path component of \c "puppy.jpg" . On the other hand, if the inputs are
	\c "puppy.jpg" and \c UTTypePlainText respectively, the resulting URL will
	have a last path component of \c "puppy.jpg.txt" . If you want to ensure any
	existing path extension is replaced, you can use the
	\c URLByDeletingPathExtension property first.

	If the extension could not be appended, this method returns a copy of
	\c self .

	\note The resulting URL has a directory path if \c contentType conforms to
		\c UTTypeDirectory .
*/
- (NSURL *)URLByAppendingPathExtensionForType:(UTType *)contentType;
@end

UT_AVAILABLE_END
NS_ASSUME_NONNULL_END
__END_DECLS

#endif // __UNIFORMTYPEIDENTIFIERS_UTADDITIONS__
