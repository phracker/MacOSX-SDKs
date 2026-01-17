/*  Copyright (c) 2014 Apple Inc.  All rights reserved.                       */

#ifndef __LA_OBJECT_HEADER__
#define __LA_OBJECT_HEADER__

#include <vecLib/LinearAlgebra/base.h>

#if __has_feature(assume_nonnull)
////  If assume_nonnull is available, use it and use nullability qualifiers.
_Pragma("clang assume_nonnull begin")
#else
////  Otherwise, neuter the nullability qualifiers.
#define __nullable
#define __nonnull
#endif

/*!
 @class la_object_t

 @abstract
 Type used by all functions in the LinearAlgebra library.

 @discussion LinearAlgebra objects behave rather differently depending on 
 whether you are writing Objective-C or C.  For details of semantics and memory 
 management consult the appropriate section below.  For further information, 
 consult the comments in <os/object.h>.

 Objective-C with ARC:
 LinearAlgebra objects are objective-c objects.  This means that
 they participate in ARC, may be used with collections, etc.  Thus, if you are 
 using ARC, you must not retain or release LinearAlgebra objects; the compiler 
 will take care of it for you.

 Objective-C without ARC:
 If you are not using ARC, you send -[retain] and -[release] messages to
 LinearAlgebra objects, just like you would with objects of any other 
 Objective-C type.

 C:
 LinearAlgebra objects are reference counted and must be retained and released
 via the la_retain( ) and la_release( ) functions.  Do not attempt to
 call free( ) on LinearAlgebra objects; this will typically result in leaks.
 */
#if OS_OBJECT_USE_OBJC
    OS_OBJECT_DECL(la_object);
#   define LA_RETURNS_RETAINED OS_OBJECT_RETURNS_RETAINED
#else
typedef struct la_s *la_object_t;
#   define LA_RETURNS_RETAINED
#endif

/*!
 @abstract
 Increment the reference count of a la_object_t object.

 @param object
 The object to retain.

 @result
 The retained object.

 @discussion
 On a platform with the modern Objective-C runtime this is exactly equivalent
 to sending the object the -[retain] message.
 */
LA_FUNCTION LA_AVAILABILITY
la_object_t la_retain(la_object_t object);
#if OS_OBJECT_USE_OBJC
#   undef la_retain
#   define la_retain(object) [object retain]
#endif

/*!
 @abstract
 Decrement the reference count of an la_object_t object.

 @param object
 The object to release.

 @discussion
 On a platform with the modern Objective-C runtime this is exactly equivalent
 to sending the object the -[release] message.
 */
LA_FUNCTION LA_AVAILABILITY
void la_release(la_object_t object);
#if OS_OBJECT_USE_OBJC
#   undef la_release
#   define la_release(object) [object release]
#endif

/*!
 @abstract
 Add attributes to an la_object_t object.

 @param object
 The object that will have its attributes modified.

 @param attributes
 Attributes which are to be added to the object's existing attributes
 to create its new set of attributes.  This value should be constructed by
 or'ing together LA_ATTRIBUTE_* constants.

 @discussion
 This operation does not remove any existing attributes from the LinearAlgebra 
 object, though it is possible that some attributes will override others (if so, 
 this will be documented in the discussion of those attributes above).  
 Following this function call, the specified object has all of the attributes it 
 had before the call, plus any new attributes specified by the second parameter.
 
 Adding an attribute that the object already has does not change the object.
 
 This function is not reentrant or thread-safe.  Attempting to add or remove
 attributes from multiple threads will have unpredictable results.
 */
LA_FUNCTION LA_AVAILABILITY
void la_add_attributes(la_object_t object, la_attribute_t attributes);

/*!
 @abstract
 Remove attributes from an la_object_t object.

 @param object
 The object that will have its attributes modified.

 @param attributes
 Attributes which are to be removed from the object's existing attributes
 to create its new set of attributes.  This value should be constructed by
 or'ing together LA_ATTRIBUTE_* constants.
 
 @discussion
 This function removes the specified attributes from the LinearAlgebra object.
 Removing an attribute that the object does not have is harmless and does not
 change the object.

 This function is not reentrant or thread-safe.  Attempting to add or remove
 attributes from multiple threads will have unpredictable results.
 */
LA_FUNCTION LA_AVAILABILITY
void la_remove_attributes(la_object_t object, la_attribute_t attributes);

/*!
 @abstract Query the status of an la_object.
 
 @param object
 The object whose status is being requested.
 
 @return
 The status of the supplied object.

 @discussion Returns the status of a LinearAlgebra object.  The status will be 
 one of the codes defined in LinearAlgebra/base.h.  New status codes may be
 added in the future, but the following basic principle will continue to hold: 
 zero indicates success, status codes greater than zero are warnings, and
 status codes less than zero are errors.  Thus, careful error handling
 might look like the following:

 <pre>
 @textblock
 la_status_t status = la_status(result_object);
 if (status == LA_SUCCESS) {
    // Everything is copacetic.  Get your data from result_object.
 } else if (status > 0) {
    // No errors occured, but the result does not have full accuracy due to
    // numerical considerations.  Here, you might re-compute the result using
    // a more careful or stable algorithm.
 } else {
    // An error occured.  Something is seriously amiss and you will need
    // to handle it however makes sense for your application.
 }
 @/textblock
 </pre>

 Note that errors and warnings are propagated.  In general, there is no need
 to check the status of each subcomputation.  Rather, the preferred idiom is
 to do a complete computation, then check to see if anything went wrong.
 Querying status may force evaluation of parts of your computation that might
 otherwise be deferred until their results were actually needed.
 */
LA_FUNCTION LA_AVAILABILITY
la_status_t la_status(la_object_t object);

#if __has_feature(assume_nonnull)
_Pragma("clang assume_nonnull end")
#endif

#endif // __LA_OBJECTS_HEADER__
