/*------------------------------------------------------------------------------------------------------------------------------
 *
 *  ImageCapture/ICADevice.h
 *
 *  Copyright (c) 2000-2006 Apple Computer, Inc. All rights reserved.
 *
 *  For bug reports, consult the following page onthe World Wide Web:
 *  http://developer.apple.com/bugreporter/
 *
 *----------------------------------------------------------------------------------------------------------------------------*/

#pragma once

#ifndef __ICADEVICE__
#define __ICADEVICE__

//------------------------------------------------------------------------------------------------------------------------------

#ifndef __ICAAPPLICATION__
#include <ImageCapture/ICAApplication.h>
#endif

#ifndef __AVAILABILITYMACROS__
#include <AvailabilityMacros.h>
#endif

//------------------------------------------------------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(push, 2)

//------------------------------------------------------------------------------------------------------------------------------
/*!
    @header ICADevice.h
    @discussion
        ICADevice.h defines structures and functions that are used by native Image Capture device modules. 
*/

//-------------------------------------------------------------------------------------------------------------------- ICDHeader
/*!
    @struct ICDHeader
    @discussion
        This is the first field in all parameter blocks used by APIs defined in ICADevices.h.
        Type of parameter passed to a callback function used by APIs defined in ICADevices.h.
        The parameter for the completion proc should to be casted to an appropriate type such as ICD_NewObjectPB* for it to be useful.
    @field err
        Error returned by an API. -->
    @field refcon
        An arbitrary refcon value passed to the callback. <--
*/
typedef struct ICDHeader {
  ICAError            err;
  unsigned long       refcon;
} ICDHeader;

//--------------------------------------------------------------------------------------------------------------- Callback procs

/*!
    @typedef ICDCompletion
    @discussion
        Type of callback function used by APIs defined in ICADevices.h.
    @param pb
        The parameter pb is a pointer to the parameter block passed to the API.
*/

typedef CALLBACK_API_C( void , ICDCompletion )(ICDHeader * pb);

//----------------------------------------------------------------------------------------------------------------- ICDNewObject
/*!
    @struct ICD_NewObjectPB
    @discussion
        Parameter block passed to function <code>ICDNewObject</code>.
    @field header
        The function returns error code in the <code>err</code> field of this structure. 
        The <code>refcon</code> field of this structure is used to pass a pointer to the callback function if <code>ICDNewObject</code> is called asynchronously.
    @field  parentObject
        Parent object of the new object.
    @field  objectInfo
        <code>ICAObjectInfo</code> struct filled with information about the new object.
    @field  object
        New object.
*/
typedef struct ICD_NewObjectPB {
  ICDHeader           header;
  ICAObject           parentObject;
  ICAObjectInfo       objectInfo;
  ICAObject           object;
} ICD_NewObjectPB;

/*!
    @function ICDNewObject
    @abstract
        A function to create a new object.
    @discussion
        Call this function to create a new object.
    @param pb
        An <code>ICD_NewObjectPB</code> structure.
    @param completion
        A pointer to a callback function that conforms to the interface of <code>ICDCompletion</code>. Pass <code>NULL</code> to make a synchronous call. 
    @result
        Returns an error code. If the function is called asynchronously, it returns <code>0</code> if the the call is accepted for asynchronous
        processing and returns an error code in the header passed to the callback function.
*/
extern ICAError 
ICDNewObject(
    ICD_NewObjectPB*  pb,
    ICDCompletion     completion
)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_7;

//------------------------------------------------------------------------------------------------------------- ICDDisposeObject
/*!
    @struct ICD_DisposeObjectPB
    @discussion
        Parameter block passed to function <code>ICDDisposeObject</code>.
    @field header
        The function returns error code in the <code>err</code> field of this structure. 
        The <code>refcon</code> field of this structure is used to pass a pointer to the callback function if <code>ICDDisposeObject</code> is called asynchronously.
    @field object
        Object to be disposed.
*/
typedef struct ICD_DisposeObjectPB {
  ICDHeader           header;
  ICAObject           object;
} ICD_DisposeObjectPB;

/*!
    @function ICDDisposeObject
    @abstract
        A function to dispose an object.
    @discussion
        Call this function to dispose an object.
    @param pb
        An <code>ICD_DisposeObjectPB</code> structure.
    @param completion
        A pointer to a callback function that conforms to the interface of <code>ICDCompletion</code>. Pass <code>NULL</code> to make a synchronous call. 
    @result
        Returns an error code. If the function is called asynchronously, it returns <code>0</code> if the the call is accepted for asynchronous 
        processing and returns an error code in the header passed to the callback function.
*/
extern ICAError 
ICDDisposeObject(
    ICD_DisposeObjectPB*  pb,
    ICDCompletion         completion
)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_7;

//------------------------------------------------------------------------------------------------------------------------------

#pragma pack(pop)

#ifdef __cplusplus
}
#endif

//------------------------------------------------------------------------------------------------------------------------------

#endif /* __ICADEVICE__ */

//------------------------------------------------------------------------------------------------------------------------------
