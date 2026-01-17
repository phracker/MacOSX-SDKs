/*  Copyright (c) 2014 Apple Inc.  All rights reserved.                       */

#ifndef __LA_VECTOR_HEADER__
#define __LA_VECTOR_HEADER__

/*!
 @abstract
 Create a vector using data from a buffer of floats.  Ownership of the buffer
 remains in control of the caller.

 @param buffer
 Pointer to float data providing the elements of the vector.  

 @param vector_length
 The length of the vector.

 @param buffer_stride
 The offset in the buffer (measured in floats) between consecutive elements
 of the vector.

 @param attributes
 Attributes to attach to the new la_object_t object.  Pass LA_DEFAULT_ATTRIBUTES
 to create a normal object.

 @return a new la_object_t object representing the vector.

 @discussion
 This function creates an object representing a vector whose entries are copied
 out of the supplied buffer of floats.  Negative or zero strides are not
 supported by this function (but note that you can reverse the elements in a
 vector using the la_vector_reverse macro defined below).

 The stride determines the offset (measured in floats) between the values
 providing consecutive vector elements in the buffer.  For example, if
 buffer_stride is 1, then the vector is:

 { buffer[0], buffer[1], buffer[2], ... , buffer[vector_length-1] }

 If buffer_stride is 3, the vector is:

 { buffer[0], buffer[3], buffer[6], ... , buffer[3*(vector_length-1)] }

 Thus, the size of the buffer (in floats) should be at least

 buffer_stride*(vector_length-1) + 1.
 
 Always returns a vector_length x 1 vector.
 */
#define la_vector_from_float_buffer(buffer, vector_length, buffer_stride, attributes) \
    la_matrix_from_float_buffer(buffer, vector_length, 1, buffer_stride, LA_NO_HINT, attributes)

/*!
 @abstract
 Create a vector using data from a buffer of doubles.  Ownership of the buffer
 remains in control of the caller.

 @param buffer
 Pointer to double data providing the elements of the vector.

 @param vector_length
 The length of the vector.

 @param buffer_stride
 The offset in the buffer (measured in doubles) between consecutive elements
 of the vector.

 @param attributes
 Attributes to attach to the new la_object_t object.  Pass LA_DEFAULT_ATTRIBUTES
 to create a normal object.

 @return a new la_object_t object representing the vector.

 @discussion
 This function creates an object representing a vector whose entries are copied
 out of the supplied buffer of doubles.  Negative or zero strides are not
 supported by this function (but note that you can reverse the elements in a
 vector using the la_vector_reverse macro defined below).

 The stride determines the offset (measured in doubles) between the values
 providing consecutive vector elements in the buffer.  For example, if
 buffer_stride is 1, then the vector is:

 { buffer[0], buffer[1], buffer[2], ... , buffer[vector_length-1] }

 If buffer_stride is 3, the vector is:

 { buffer[0], buffer[3], buffer[6], ... , buffer[3*(vector_length-1)] }

 Thus, the size of the buffer (in doubles) should be at least

 buffer_stride*(vector_length-1) + 1.
 
 Always returns a vector_length x 1 vector.
 */
#define la_vector_from_double_buffer(buffer, vector_length, buffer_stride, attributes) \
    la_matrix_from_double_buffer(buffer, vector_length, 1, buffer_stride, LA_NO_HINT, attributes)

/*!
 @abstract
 Create a vector using data from a buffer of floats.  Ownership of the buffer
 is transferred from the caller to the returned object.

 @param buffer
 Pointer to float data providing the elements of the vector.

 @param vector_length
 The length of the vector.

 @param deallocator
 Callback to be used to deallocate the buffer when the returned vector object
 is destroyed.

 @param attributes
 Attributes to attach to the new la_object_t object.  Pass LA_DEFAULT_ATTRIBUTES
 to create a normal object.

 @return a new la_object_t object representing the vector.

 @discussion
 This function creates an object representing a vector whose entries are the
 supplied buffer of floats.  Ownership of the buffer is transferred to the new
 vector object, meaning that you must not read, modify, or destroy it after
 calling this function.

 Strides are not supported with this function, as there is no way to take
 ownership of (say) every third element in a region of memory.  Instead,
 you would create a vector with this function, then create a slice using
 la_vector_slice to achieve the same effect without copying.
 
 Always returns a vector_length x 1 vector.
 */
#define la_vector_from_float_buffer_nocopy(buffer, vector_length, deallocator, attributes) \
    la_matrix_from_float_buffer_nocopy(buffer, vector_length, 1, 1, LA_NO_HINT, deallocator, attributes)

/*!
 @abstract
 Create a vector using data from a buffer of doubles.  Ownership of the buffer
 is transferred from the caller to the returned object.

 @param buffer
 Pointer to double data providing the elements of the vector.

 @param vector_length
 The length of the vector.

 @param deallocator
 Callback to be used to deallocate the buffer when the returned vector object
 is destroyed.

 @param attributes
 Attributes to attach to the new la_object_t object.  Pass LA_DEFAULT_ATTRIBUTES
 to create a normal object.

 @return a new la_object_t object representing the vector.

 @discussion
 This function creates an object representing a vector whose entries are the
 supplied buffer of doubles.  Ownership of the buffer is transferred to the new
 vector object, meaning that you must not read, modify, or destroy it after
 calling this function.

 Strides are not supported with this function, as there is no way to take
 ownership of (say) every third element in a region of memory.  Instead,
 you would create a vector with this function, then create a slice using
 la_vector_slice to achieve the same effect without copying.
 
 Always returns a vector_length x 1 vector.
 */
#define la_vector_from_double_buffer_nocopy(buffer, vector_length, deallocator, attributes) \
    la_matrix_from_double_buffer_nocopy(buffer, vector_length, 1, 1, LA_NO_HINT, deallocator, attributes)

/*!
 @abstract
 Stores the elements of a vector to a buffer.

 @param buffer
 Pointer to the destination buffer.

 @param buffer_stride
 Offset (in floats) between the destinations of consecutive vector elements
 in the buffer.  Negative strides are not supported (you can get the same
 effect by reversing the vector before calling this function).

 @param vector
 The vector to store.

 @discussion
 The buffer must be large enough to accomodate the vector being stored.
 Specifically, it must have have sufficient space to hold

 buffer_stride*(la_vector_length(vector)-1) + 1

 float elements.  Real usage in the most common case (stride = 1) will
 look roughly like this:

 <pre>
 @textblock
 la_count_t length = la_vector_length(vector);
 if (!length) {
 	// an error occured.
 }
 float *buffer = malloc(length * sizeof buffer[0]);
 la_vector_to_float_buffer(buffer, 1, vector);
 @/textblock
 </pre>

 This function supports storing the contents of a vector, or a matrix that
 has only one row or only one column.  If the object satisfies those
 requirements, and it does not have an error status, its contents are stored
 to the buffer.  If it has an error status, NaNs are stored to the buffer.

 If the object is not a matrix or vector, or if it is a matrix with both
 dimensions larger than one, nothing is written to the buffer and
 LA_INVALID_PARAMETER_ERROR is returned.
 */
LA_FUNCTION LA_NONNULL LA_AVAILABILITY
la_status_t la_vector_to_float_buffer(float *buffer,
                                            la_index_t buffer_stride,
                                            la_object_t vector);

/*!
 @abstract
 Stores the elements of a vector to a buffer.

 @param buffer
 Pointer to the destination buffer.

 @param buffer_stride
 Offset (in doubles) between the destinations of consecutive vector elements
 in the buffer.  Negative strides are not supported (you can get the same
 effect by reversing the vector before calling this function).

 @param vector
 The vector to store.

 @return
 If vector is a valid vector object, its status is returned.  Otherwise
 the return value is LA_INVALID_PARAMETER_ERROR.

 @discussion
 The buffer must be large enough to accomodate the vector being stored.
 Specifically, it must have have sufficient space to hold

 buffer_stride*(la_vector_length(vector)-1) + 1

 double elements.  Real usage in the most common case (stride = 1) will
 look roughly like this:

 <pre>
 @textblock
 la_count_t length = la_vector_length(vector);
 if (!length) {
 	// an error occured.
 }
 double *buffer = malloc(length * sizeof buffer[0]);
 la_vector_to_double_buffer(buffer, 1, vector);
 @/textblock
 </pre>

 This function supports storing the contents of a vector, or a matrix that
 has only one row or only one column.  If the object satisfies those
 requirements, and it does not have an error status, its contents are stored
 to the buffer.  If it has an error status, NaNs are stored to the buffer.

 If the object is not a matrix or vector, or if it is a matrix with both
 dimensions larger than one, nothing is written to the buffer and
 LA_INVALID_PARAMETER_ERROR is returned.
 */
LA_FUNCTION LA_NONNULL LA_AVAILABILITY
la_status_t la_vector_to_double_buffer(double *buffer,
                                             la_index_t buffer_stride,
                                             la_object_t vector);

/*!
 @abstract
 Get the length of a vector.

 @discussion
 If the argument has an error status, zero is returned.
 If the argument is a vector, its length is returned.
 If the argument is a matrix with only one row or only one column, the other
 dimension is returned.
 Otherwise, zero is returned.
 */
LA_FUNCTION LA_CONST LA_NONNULL LA_AVAILABILITY
la_count_t la_vector_length(la_object_t vector);

/*!
 @abstract
 Create a slice of a vector.

 @param vector
 The vector to be sliced.

 @param vector_first
 The index of the source vector element that will become the first element
 of the new slice vector.

 @param vector_stride
 The offset in the source vector between elements that will be consecutive in
 the new slice vector.

 @param slice_length
 The length of the resulting slice vector.

 @return
 A new vector with length slice_length whose elements are taken from vector.

 @discussion
 The result object is the vector:

 [ vector[vector_first], vector[vector_first+vector_stride], ...
 ... , vector[vector_first + (slice_length-1)*vector_stride] ]
 
 Slices provide an efficient means to operate on subvectors and strides.
 These are lightweight objects that reference the storage of the vector from
 which they originate.  Creating a vector slice does not require any allocation
 beyond the object representing the slice, nor does it require copying.

 This function supports slicing a vector, or a matrix that has only one row
 or only one column.  If the object is not a matrix or vector, or if it is
 a matrix with both dimensions larger than one, the returned object will have
 status LA_INVALID_PARAMETER_ERROR.

 If the slice references indices that are less than zero or greater than or
 equal to the length of the vector, LA_SLICE_OUT_OF_BOUNDS_ERROR is returned.
 
 Always return a vector with the same orientation as the input.  If input is
 vector_length x 1, output is vector_length x 1 and if input is
 1 x vector_length, output is 1 x vector_length.
 */
LA_FUNCTION LA_NONNULL LA_AVAILABILITY LA_RETURNS_RETAINED
la_object_t la_vector_slice(la_object_t vector,
                               la_index_t vector_first,
                               la_index_t vector_stride,
                               la_count_t slice_length);

/*!
 @abstract
 Generate a new vector that is the reverse of the supplied vector.
 
 Always return a vector with the same orientation as the input.  If input is
 vector_length x 1, output is vector_length x 1 and if input is 
 1 x vector_length, output is 1 x vector_length.
 */
#define la_vector_reverse(vector) \
la_vector_slice(vector, la_vector_length(vector)-1, -1, la_vector_length(vector))



#endif // __LA_VECTOR_HEADER__
