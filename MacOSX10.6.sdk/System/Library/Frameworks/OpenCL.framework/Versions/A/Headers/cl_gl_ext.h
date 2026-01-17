/*******************************************************************************
 * Copyright:  (c) 2007-2009 by Apple, Inc., All Rights Reserved.
 ******************************************************************************/

#ifndef __CL_GL_EXT_H
#define __CL_GL_EXT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <OpenCL/cl.h>
#include <OpenCL/cl_gl.h>
#include <AvailabilityMacros.h>

// Context GL sharing
//
// Please check for the "cl_APPLE_gl_sharing" extension using clGetDeviceInfo(CL_DEVICE_EXTENSIONS)
// before using these extensions.

// Apple extension for creating a CL context from a CGL share group
//
// This enumerated value can be specified as part of the <properties> argument passed to clCreateContext 
// to allow OpenCL compliant devices in an existing CGL share group to be used as the devices in 
// the newly created CL context. GL objects that were allocated in the given CGL share group can 
// now be shared between CL and GL.
//
// If the <num_devices> and <devices> argument values to clCreateContext are 0 and NULL respectively,
// all CL compliant devices in the CGL share group will be used to create the context.
// Additional CL devices can also be specified using the <num_devices> and <devices> arguments.
// These, however, cannot be GPU devices. On Mac OS X, you can add the CPU to the list of CL devices
// (in addition to the CL compliant devices in the CGL share group) used to create the CL context. 
// Note that if a CPU device is specified, the CGL share group must also include the GL float renderer; 
// Otherwise CL_INVALID_DEVICE will be returned.
//
// NOTE:  Make sure that appropriate cl_gl.h header file is included separately
//
#define CL_CONTEXT_PROPERTY_USE_CGL_SHAREGROUP_APPLE        0x10000000 /* Introduced in Mac OS X 10.6 */

// Apple extension for retrieving OpenGL context information for a CL context 
// created via the above method.
//
// Provides a query mechanism to retrieve OpenGL context specific information 
// from an OpenCL context to help identify device specific mappings and usage.
// 
// For example, one possible usage would be to allow the client to map a CGL 
// virtual screen index to an appropriate CL device id to insure that the 
// rendering device and the compute device are the same, thus guaranteeing 
// any shared OpenGL memory that is attached o a CL memory object remains 
// resident on the active device.
//
cl_int	clGetGLContextInfoAPPLE ( cl_context /* context */,
								  void * /* platform_gl_ctx */,
								  cl_gl_platform_info /* param_name */,
								  size_t /* param_value_size */,
								  void * /* param_value */,
								  size_t * /* param_value_size_ret */)  AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;  

// The list of supported param_name values and the information returned in param_value by 
// clGetContextInfo are listed below:

// Returns a cl_device_id for the CL device associated with the virtual screen for 
// the given CGL context.  Return type: cl_device_id
//
#define CL_CGL_DEVICE_FOR_CURRENT_VIRTUAL_SCREEN_APPLE 		0x10000002 /* Introduced in Mac OS X 10.6 */

// Returns an array of cl_device_ids for the CL device(s) corresponding to 
// the virtual screen(s) for the given CGL context.   Return type: cl_device_id[]
//
#define CL_CGL_DEVICES_FOR_SUPPORTED_VIRTUAL_SCREENS_APPLE	0x10000003 /* Introduced in Mac OS X 10.6 */

// Error code returned by clGetGLContextInfoAPPLE if an invalid platform_gl_ctx
// is provided
#define CL_INVALID_GL_CONTEXT_APPLE                         -1000      /* Introduced in Mac OS X 10.6 */



#ifdef __cplusplus
}
#endif


#endif /* __CL_GL_EXT_H */
