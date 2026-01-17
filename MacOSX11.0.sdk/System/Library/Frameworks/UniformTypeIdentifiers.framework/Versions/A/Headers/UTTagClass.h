//
//  UTTagClass.h
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#ifndef __UNIFORMTYPEIDENTIFIERS_UTTAGCLASS__
#define __UNIFORMTYPEIDENTIFIERS_UTTAGCLASS__

#import <Foundation/Foundation.h>

#import <UniformTypeIdentifiers/UTDefines.h>

__BEGIN_DECLS
NS_ASSUME_NONNULL_BEGIN
UT_AVAILABLE_BEGIN

/**
	\brief The tag class for filename extensions such as \c "txt".

	The leading period character is not part of the filename extension and
	should not be included in the tag.
*/
UT_EXPORT NSString *const UTTagClassFilenameExtension NS_REFINED_FOR_SWIFT;

/** \brief The tag class for MIME types such as \c "text/plain". */
UT_EXPORT NSString *const UTTagClassMIMEType NS_REFINED_FOR_SWIFT;

UT_AVAILABLE_END
NS_ASSUME_NONNULL_END
__END_DECLS

#endif // __UNIFORMTYPEIDENTIFIERS_UTTAGCLASS__
