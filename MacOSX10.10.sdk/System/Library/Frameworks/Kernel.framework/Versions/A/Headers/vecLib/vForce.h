/*
vForce.h (from vecLib-516.0)
Copyright 1999-2015 Apple Inc.  All rights reserved.

@APPLE_LICENSE_HEADER_START@

This file contains Original Code and/or Modifications of Original Code
as defined in and that are subject to the Apple Public Source License
Version 2.0 (the 'License'). You may not use this file except in
compliance with the License. Please obtain a copy of the License at
http://www.opensource.apple.com/apsl/ and read it before using this
file.

The Original Code and all software distributed under the License are
distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
Please see the License for the specific language governing rights and
limitations under the License.

@APPLE_LICENSE_HEADER_END@
*/

#ifndef __VFORCE_H
#define __VFORCE_H


#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <Availability.h>
/* Set y[i] to the exponential function of x[i], for i=0,..,n-1 */
void vvexpf (float * /* y */, const float * /* x */, const int * /* n */) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_5_0); 
#ifdef __cplusplus
}
#endif
#endif /* __VFORCE_H */
