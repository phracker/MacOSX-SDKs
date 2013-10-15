/*
     File:       AUNTComponent.r
 
     Contains:   AudioUnit Version 1 Specific Interfaces
 
     Version:    Technology: System 9, X
                 Release:    Mac OS X
 
     Copyright:  © 2002-2003 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

#ifndef __AUNTCOMPONENT_R__
#define __AUNTCOMPONENT_R__

#ifndef __CONDITIONALMACROS_R__
#include "ConditionalMacros.r"
#endif

#define kAudioUnitComponentType 				'aunt'
#define kAudioUnitSubType_Output 				'out '
#define kAudioUnitID_HALOutput 					'ahal'
#define kAudioUnitID_DefaultOutput 				'def '
#define kAudioUnitID_SystemOutput 				'sys '
#define kAudioUnitID_GenericOutput 				'genr'
#define kAudioUnitSubType_MusicDevice 			'musd'
#define kAudioUnitID_DLSSynth 					'dls '
#define kAudioUnitSubType_SampleRateConverter 	'srcv'
#define kAudioUnitID_PolyphaseSRC 				'poly'
#define kAudioUnitSubType_FormatConverter 		'fmtc'
#define kAudioUnitID_Interleaver 				'inlv'
#define kAudioUnitID_Deinterleaver 				'dnlv'
#define kAudioUnitID_AUConverter		 		'conv'
#define kAudioUnitSubType_Effect 				'efct'
#define kAudioUnitID_MatrixReverb 				'mrev'
#define kAudioUnitID_Delay 						'dely'
#define kAudioUnitID_LowPassFilter 				'lpas'
#define kAudioUnitID_HighPassFilter 			'hpas'
#define kAudioUnitID_BandPassFilter 			'bpas'
#define kAudioUnitID_PeakLimiter 				'lmtr'
#define kAudioUnitID_DynamicsProcessor 			'dcmp'
#define kAudioUnitSubType_Mixer 				'mixr'
#define kAudioUnitID_StereoMixer 				'smxr'
#define kAudioUnitID_3DMixer 					'3dmx'


#endif /* __AUNTCOMPONENT_R__ */

