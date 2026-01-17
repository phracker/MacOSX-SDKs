/*
	File:  VTProfessionalVideoWorkflow.h
 
	Framework:  VideoToolbox
 
	Copyright © 2013-2014 Apple Inc. All rights reserved.
 
*/

#ifndef VTPROFESSIONALVIDEOWORKFLOW_H
#define VTPROFESSIONALVIDEOWORKFLOW_H

#include <VideoToolbox/VTBase.h>
#include <CoreMedia/CMBase.h>

#if defined(__cplusplus)
extern "C"
{
#endif
    
#pragma pack(push, 4)

/*!
	@function	VTRegisterProfessionalVideoWorkflowVideoDecoders
	@abstract	Allows the client to use video decoders appropriate for professional video workflows.
	@discussion	By calling this function, a client indicates to VideoToolbox that it wishes to support Media Extension video decoders. Any associated Video RAW Processors will also be supported as well. Note that this functionality is intended for applications supporting professional video workflows. It is not recommended for network-facing applications such as web browsers, messaging clients, mail clients, etc.
*/
VT_EXPORT void VTRegisterProfessionalVideoWorkflowVideoDecoders( void )
	API_AVAILABLE(macos(10.9)) API_UNAVAILABLE(ios, tvos, watchos, visionos);

/*!
	@function	VTRegisterProfessionalVideoWorkflowVideoEncoders
	@abstract	Allows the client to use encoders appropriate for professional video workflows.
*/
VT_EXPORT void VTRegisterProfessionalVideoWorkflowVideoEncoders( void )
	API_AVAILABLE(macos(10.10)) API_UNAVAILABLE(ios, tvos, watchos, visionos);

#pragma pack(pop)

#if defined(__cplusplus)
}
#endif

#endif // VTPROFESSIONALVIDEOWORKFLOW_H
