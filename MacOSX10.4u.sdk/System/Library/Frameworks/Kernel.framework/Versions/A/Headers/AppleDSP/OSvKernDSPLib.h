/*
 *	OSvKernDSPLib.h
 *
 *	Created by Paul Chang on Fri Mar 26 2004.
 *	Copyright 2004 Apple Computer. All rights reserved.
 *
 */


#include <sys/types.h>
typedef __darwin_ptrdiff_t ptrdiff_t;


void vDSP_conv(
	const float	vDSP_signal[],
	ptrdiff_t	vDSP_signalStride,
	const float	vDSP_filter[],
	ptrdiff_t	vDSP_strideFilter,
	float		vDSP_result[],
	ptrdiff_t	vDSP_strideResult,
	size_t		vDSP_lenResult,
	size_t		vDSP_lenFilter,
	char		*temp);

void vDSP_vadd(
	const float	vDSP_input1[],
	ptrdiff_t	vDSP_stride1,
	const float	vDSP_input2[],
	ptrdiff_t	vDSP_stride2,
	float		vDSP_result[],
	ptrdiff_t	vDSP_strideResult,
	size_t		vDSP_size);

void vDSP_vsub(
	const float	vDSP_input1[],
	ptrdiff_t	vDSP_stride1,
	const float	vDSP_input2[],
	ptrdiff_t	vDSP_stride2,
	float		vDSP_result[],
	ptrdiff_t	vDSP_strideResult,
	size_t		vDSP_size);

void vDSP_vmul(
	const float	vDSP_input1[],
	ptrdiff_t	vDSP_stride1,
	const float	vDSP_input2[],
	ptrdiff_t	vDSP_stride2,
	float		vDSP_result[],
	ptrdiff_t	vDSP_strideResult,
	size_t		vDSP_size);

void vDSP_vdiv(
	const float vDSP_input1[],
	ptrdiff_t	vDSP_stride1,
	const float vDSP_input2[],
	ptrdiff_t	vDSP_stride2,
	float		vDSP_result[],
	ptrdiff_t	vDSP_strideResult,
	size_t		vDSP_size);
