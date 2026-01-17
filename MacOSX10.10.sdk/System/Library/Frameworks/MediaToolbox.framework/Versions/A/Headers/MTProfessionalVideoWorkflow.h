/*
	File:  MTProfessionalVideoWorkflow.h
 
	Framework:  MediaToolbox
 
	Copyright © 2014 Apple Inc. All rights reserved.

	To report bugs, go to:  http://developer.apple.com/bugreporter/
*/

#ifndef MTPROFESSIONALVIDEOWORKFLOW_H
#define MTPROFESSIONALVIDEOWORKFLOW_H

#include <CoreMedia/CMBase.h>

#if defined(__cplusplus)
extern "C"
{
#endif
    
#pragma pack(push, 4)

/*!
	@function	MTRegisterProfessionalVideoWorkflowFormatReaders
	@abstract	Allows the client to use file format readers appropriate for professional video workflows.
*/
MT_EXPORT void MTRegisterProfessionalVideoWorkflowFormatReaders( void )  __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_NA);

#pragma pack(pop)

#if defined(__cplusplus)
}
#endif

#endif // MTPROFESSIONALVIDEOWORKFLOW_H
