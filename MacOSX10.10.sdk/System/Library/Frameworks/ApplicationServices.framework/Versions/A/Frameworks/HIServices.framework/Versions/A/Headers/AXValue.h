/*
 *  AXValue.h
 *  Accessibility
 *
 *  Copyright (c) 2002 Apple Computer, Inc. All rights reserved.
 *
 */

#ifndef __AXVALUE__
#define __AXVALUE__

#include <AvailabilityMacros.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <CoreServices/CoreServices.h>
#include <CoreFoundation/CoreFoundation.h>

/* Need discussion for following */

/*! @header AXValue.h
	@discussion
		This header contains functions and data types for
		working with AXValueType wrappers.
*/

/*!
  @enum AXValueType Wrappers
  
  @discussion
  These are AXValueType wrappers for other structures. You must use the AXValueCreate
  and AXValueGetValue functions to convert between the wrapped structure and the native structure.
  
  @constant kAXValueCGPointType a wrapper for CGPoint; see CoreGraphics.h
  @constant kAXValueCGSizeType a wrapper for CGSize; see CoreGraphics.h
  @constant kAXValueCGRectType a wrapper for CGRect; see CoreGraphics.h
  @constant kAXValueCFRangeType a wrapper for CFRange; see CFBase.h
  @constant kAXValueAXErrorType See AXError.h
  @constant kAXValueIllegalType a wrapper for unsupported structures
*/
typedef enum {
    kAXValueCGPointType = 1,
    kAXValueCGSizeType = 2,
    kAXValueCGRectType = 3,
    kAXValueCFRangeType = 4,
    kAXValueAXErrorType = 5,
    kAXValueIllegalType = 0


} AXValueType;

/* Need discussion for following */

/*!
    @typedef AXValueRef
    
*/
typedef const struct __AXValue *AXValueRef;

/* Need discussion for following */

/*!
	@function AXValueGetTypeID
		
	@result
	
	@availability Mac OS X version 10.3 or later
*/
extern CFTypeID		AXValueGetTypeID() AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*!
	@function AXValueCreate
	
	@discussion
	Encodes a structure pointed to by valuePtr into a CFTypeRef.
	
	@param theType
	@param valuePtr
	
	@result
*/
extern AXValueRef 	AXValueCreate (AXValueType theType, const void *valuePtr);

/*!
	@function AXValueGetType
	
	@discussion
	Returns the structure type encoded in value. If the type is not recognized, it returns kAXValueIllegalType.
	
	@param value
		
	@result
*/
extern AXValueType 	AXValueGetType(AXValueRef value);

/*!
	@function AXValueGetValue
	
	@discussion
	Decodes the structure stored in value and copies it into valuePtr. If the structure stored in value is not
	the same as requested by theType, the function returns false.
	
	@param value
		
	@result
*/
extern Boolean 		AXValueGetValue(AXValueRef value, AXValueType theType, void *valuePtr);


#ifdef __cplusplus
}
#endif

#endif // __AXVALUE__
