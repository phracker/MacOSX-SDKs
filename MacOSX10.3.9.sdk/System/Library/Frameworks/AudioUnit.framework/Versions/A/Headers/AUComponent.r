/*
	File:   AUComponent.r
 
	Contains:   AudioUnit Interfaces
 
	Version:	Mac OS X
 
	Copyright:  © 2002-2003 by Apple Computer, Inc., all rights reserved.
 
	Bugs?:		For bug reports, consult the following page on
                the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

#ifndef __AUCOMPONENT_R__
#define __AUCOMPONENT_R__

#ifndef __CONDITIONALMACROS_R__
#include "ConditionalMacros.r"
#endif

#define kAudioUnitType_Output					'auou'
#define kAudioUnitSubType_HALOutput				'ahal'
#define kAudioUnitSubType_DefaultOutput			'def '
#define kAudioUnitSubType_SystemOutput			'sys '
#define kAudioUnitSubType_GenericOutput			'genr'

#define kAudioUnitType_MusicDevice				'aumu'
#define kAudioUnitSubType_DLSSynth				'dls '

#define kAudioUnitType_MusicEffect				'aumf'

#define kAudioUnitType_FormatConverter			'aufc'
#define kAudioUnitSubType_AUConverter			'conv'
#define kAudioUnitSubType_Varispeed				'vari'
#define kAudioUnitSubType_TimePitch				'tmpt'


#define kAudioUnitType_Effect					'aufx'
#define kAudioUnitSubType_Delay					'dely'
#define kAudioUnitSubType_LowPassFilter			'lpas'
#define kAudioUnitSubType_HighPassFilter		'hpas'
#define kAudioUnitSubType_BandPassFilter		'bpas'
#define kAudioUnitSubType_HighShelfFilter		'hshf'
#define kAudioUnitSubType_LowShelfFilter		'lshf'
#define kAudioUnitSubType_ParametricEQ			'pmeq'
#define kAudioUnitSubType_GraphicEQ				'greq'
#define kAudioUnitSubType_PeakLimiter			'lmtr'
#define kAudioUnitSubType_DynamicsProcessor		'dcmp'
#define kAudioUnitSubType_MultiBandCompressor	'mcmp'
#define kAudioUnitSubType_MatrixReverb			'mrev'

#define kAudioUnitType_Mixer					'aumx'
#define kAudioUnitSubType_StereoMixer			'smxr'
#define kAudioUnitSubType_3DMixer				'3dmx'
#define kAudioUnitSubType_MatrixMixer			'mxmx'

#define kAudioUnitType_Panner					'aupn'

#define kAudioUnitType_OfflineEffect			'auol'

#define kAudioUnitType_Generator				'augn'

#define kAudioUnitManufacturer_Apple			'appl'


#endif /* __AUCOMPONENT_R__ */

