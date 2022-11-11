/*
     File:       vecLib/vDSP_translate.h
 
     Contains:   Master include for vecLib framework
 
     Version:    vecLib-794.100
 
     Copyright:  Copyright (c) 2000-2022 by Apple Inc. All rights reserved.
 
     Bugs:       For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __VDSP_TRANSLATE__
#define __VDSP_TRANSLATE__


#include <os/availability.h>

#if PRAGMA_ONCE
#pragma once
#endif

#if defined __MAC_OS_X_VERSION_MIN_REQUIRED && __MAC_OS_X_VERSION_MIN_REQUIRED < __MAC_10_11

/*	When compiling for an OS X target earlier than 10.11, the legacy translates
	are defined.
*/
#define vDSP_create_fftsetup create_fftsetup
#define vDSP_destroy_fftsetup destroy_fftsetup
#define vDSP_ctoz ctoz
#define vDSP_ztoc ztoc
#define vDSP_fft_zip fft_zip
#define vDSP_fft_zipt fft_zipt
#define vDSP_fft_zop fft_zop
#define vDSP_fft_zopt fft_zopt
#define vDSP_fft_zrip fft_zrip
#define vDSP_fft_zript fft_zript
#define vDSP_fft_zrop fft_zrop
#define vDSP_fft_zropt fft_zropt
#define vDSP_fft2d_zip fft2d_zip
#define vDSP_fft2d_zipt fft2d_zipt
#define vDSP_fft2d_zop fft2d_zop
#define vDSP_fft2d_zopt fft2d_zopt
#define vDSP_fft2d_zrip fft2d_zrip
#define vDSP_fft2d_zript fft2d_zript
#define vDSP_fft2d_zrop fft2d_zrop
#define vDSP_fft2d_zropt fft2d_zropt
#define vDSP_fft3_zop fft3_zop
#define vDSP_fft5_zop fft5_zop
#define vDSP_fft_cip fft_cip
#define vDSP_fft_cipt fft_cipt
#define vDSP_fft_cop fft_cop
#define vDSP_fft_copt fft_copt
#define vDSP_fftm_zop fftm_zop
#define vDSP_fftm_zopt fftm_zopt
#define vDSP_fftm_zip fftm_zip
#define vDSP_fftm_zipt fftm_zipt
#define vDSP_fftm_zrop fftm_zrop
#define vDSP_fftm_zropt fftm_zropt
#define vDSP_fftm_zrip fftm_zrip
#define vDSP_fftm_zript fftm_zript
#define vDSP_f3x3 f3x3
#define vDSP_f5x5 f5x5
#define vDSP_conv conv
#define vDSP_dotpr dotpr
#define vDSP_imgfir imgfir
#define vDSP_mtrans mtrans
#define vDSP_mmul mmul
#define vDSP_vadd vadd
#define vDSP_vsub vsub
#define vDSP_vmul vmul
#define vDSP_vsmul vsmul
#define vDSP_vam vam
#define vDSP_vsq vsq
#define vDSP_vssq vssq
#define vDSP_zvadd zvadd
#define vDSP_zvsub zvsub
#define vDSP_zdotpr zdotpr
#define vDSP_zconv zconv
#define vDSP_zvcma zvcma
#define vDSP_zvmul zvmul
#define vDSP_zidotpr zidotpr
#define vDSP_zmma zmma
#define vDSP_zmms zmms
#define vDSP_zmsm zmsm
#define vDSP_zmmul zmmul
#define vDSP_zrvadd zrvadd
#define vDSP_zrvmul zrvmul
#define vDSP_zrvsub zrvsub
#define vDSP_zrdotpr zrdotpr
#define vDSP_fft_zipD fft_zipD
#define vDSP_fft_ziptD fft_ziptD
#define vDSP_fft_zopD fft_zopD
#define vDSP_fft_zoptD fft_zoptD
#define vDSP_fft_zripD fft_zripD
#define vDSP_fft_zriptD fft_zriptD
#define vDSP_fft_zropD fft_zropD
#define vDSP_fft_zroptD fft_zroptD
#define vDSP_fft2d_zipD fft2d_zipD
#define vDSP_fft2d_ziptD fft2d_ziptD
#define vDSP_fft2d_zopD fft2d_zopD
#define vDSP_fft2d_zoptD fft2d_zoptD
#define vDSP_fft2d_zripD fft2d_zripD
#define vDSP_fft2d_zriptD fft2d_zriptD
#define vDSP_fft2d_zropD fft2d_zropD
#define vDSP_fft2d_zroptD fft2d_zroptD
#define vDSP_fftm_zipD fftm_zipD
#define vDSP_fftm_ziptD fftm_ziptD
#define vDSP_fftm_zopD fftm_zopD
#define vDSP_fftm_zoptD fftm_zoptD
#define vDSP_fftm_zripD fftm_zripD
#define vDSP_fftm_zriptD fftm_zriptD
#define vDSP_fftm_zropD fftm_zropD
#define vDSP_fftm_zroptD fftm_zroptD
#define vDSP_fft3_zopD fft3_zopD
#define vDSP_fft5_zopD fft5_zopD
#define vDSP_ctozD ctozD
#define vDSP_ztocD ztocD
#define vDSP_vsmulD vsmulD
#define vDSP_create_fftsetupD create_fftsetupD
#define vDSP_destroy_fftsetupD destroy_fftsetupD
#define vDSP_f3x3D f3x3D
#define vDSP_f5x5D f5x5D
#define vDSP_convD convD
#define vDSP_dotprD dotprD
#define vDSP_imgfirD imgfirD
#define vDSP_mtransD mtransD
#define vDSP_mmulD mmulD
#define vDSP_vaddD vaddD
#define vDSP_vsubD vsubD
#define vDSP_vmulD vmulD
#define vDSP_vamD vamD
#define vDSP_vsqD vsqD
#define vDSP_vssqD vssqD
#define vDSP_zvaddD zvaddD
#define vDSP_zvsubD zvsubD
#define vDSP_zdotprD zdotprD
#define vDSP_zconvD zconvD
#define vDSP_zvcmaD zvcmaD
#define vDSP_zvmulD zvmulD
#define vDSP_zidotprD zidotprD
#define vDSP_zmmaD zmmaD
#define vDSP_zmmsD zmmsD
#define vDSP_zmsmD zmsmD
#define vDSP_zmmulD zmmulD
#define vDSP_zrvaddD zrvaddD
#define vDSP_zrvmulD zrvmulD
#define vDSP_zrvsubD zrvsubD
#define vDSP_zrdotprD zrdotprD

#else	//	#if __MAC_OS_X_VERSION_MIN_REQUIRED < __MAC_10_11

/*	When compiling for OS X 10.11 or later, the legacy translates are not
	defined, and the old names are marked deprecated.  To do this, we define
	a symbol telling vDSP.h to make such declarations.
*/
#define	vDSP_DeprecateTranslations


#endif	//	#if __MAC_OS_X_VERSION_MIN_REQUIRED < __MAC_10_11


#endif /* __VDSP_TRANSLATE__ */
