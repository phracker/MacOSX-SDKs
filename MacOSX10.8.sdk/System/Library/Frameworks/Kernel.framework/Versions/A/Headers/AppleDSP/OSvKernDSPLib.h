#ifndef __OSvKernDSPLib__
#define __OSvKernDSPLib__

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif


/*
 *	OSvKernDSPLib.h
 *
 *	Created by Paul Chang on Fri Mar 26 2004.
 *	Copyright 2004 Apple Computer. All rights reserved.
 *
 */


#include <sys/types.h>
typedef __darwin_ptrdiff_t ptrdiff_t;


void 
vDSP_conv(
	const float	vDSP_signal[],
	ptrdiff_t	vDSP_signalStride,
	const float	vDSP_filter[],
	ptrdiff_t	vDSP_strideFilter,
	float		vDSP_result[],
	ptrdiff_t	vDSP_strideResult,
	size_t		vDSP_lenResult,
	size_t		vDSP_lenFilter,
	char		*temp);

void 
vDSP_deq22(
	float       vDSP_input1[], 
	ptrdiff_t   vDSP_stride1, 
	float       vDSP_input2[], 
	float       vDSP_result[], 
	ptrdiff_t   vDSP_strideResult,
	size_t      vDSP_size);

void 
vDSP_maxmgv(
    const float vDSP_input1[],
    ptrdiff_t   vDSP_stride1,
    float       vDSP_result[],
    size_t      vDSP_size);

void 
vDSP_rmsqv(
    const float vDSP_input1[],
    ptrdiff_t	vDSP_stride1,
    float       vDSP_result[],
    size_t      vDSP_size);

void 
vDSP_svesq(
    const float	vDSP_input1[],
    ptrdiff_t	vDSP_stride1,
    float       vDSP_result[],
    size_t      vDSP_size);

void 
vDSP_svs(
	const float vDSP_input1[],
	ptrdiff_t   vDSP_stride1,
	float       vDSP_result[],
	size_t      vDSP_size);

void 
vDSP_vabs(
	const float vDSP_input1[], 
    ptrdiff_t   vDSP_stride1,
	float       vDSP_result[], 
    ptrdiff_t   vDSP_strideResult,
	size_t      vDSP_size);
                    
void 
vDSP_vadd(
	const float	vDSP_input1[],
	ptrdiff_t	vDSP_stride1,
	const float	vDSP_input2[],
	ptrdiff_t	vDSP_stride2,
	float		vDSP_result[],
	ptrdiff_t	vDSP_strideResult,
	size_t		vDSP_size);

void 
vDSP_vdiv(
	const float vDSP_input1[],
	ptrdiff_t	vDSP_stride1,
	const float vDSP_input2[],
	ptrdiff_t	vDSP_stride2,
	float		vDSP_result[],
	ptrdiff_t	vDSP_strideResult,
	size_t		vDSP_size);

void 
vDSP_vma(
    const float vDSP_input1[],
    ptrdiff_t   vDSP_stride1,
    const float vDSP_input2[],
    ptrdiff_t   vDSP_stride2,
    const float vDSP_input3[],
    ptrdiff_t   vDSP_stride3,
    float       vDSP_result[],
    ptrdiff_t   vDSP_strideResult,
    size_t      vDSP_size);
    
void 
vDSP_vmul(
	const float	vDSP_input1[],
	ptrdiff_t	vDSP_stride1,
	const float	vDSP_input2[],
	ptrdiff_t	vDSP_stride2,
	float		vDSP_result[],
	ptrdiff_t	vDSP_strideResult,
	size_t		vDSP_size);

void 
vDSP_vsmul(
	const float vDSP_input1[], 
    ptrdiff_t   vDSP_stride1,
	const float vDSP_input2[],
	float       vDSP_result[], 
    ptrdiff_t   vDSP_strideResult,
	size_t      vDSP_size);
        
void 
vDSP_vsub(
	const float	vDSP_input1[],
	ptrdiff_t	vDSP_stride1,
	const float	vDSP_input2[],
	ptrdiff_t	vDSP_stride2,
	float		vDSP_result[],
	ptrdiff_t	vDSP_strideResult,
	size_t		vDSP_size);


#ifdef __cplusplus
}
#endif

#endif	// __OSvKernDSPLib__
