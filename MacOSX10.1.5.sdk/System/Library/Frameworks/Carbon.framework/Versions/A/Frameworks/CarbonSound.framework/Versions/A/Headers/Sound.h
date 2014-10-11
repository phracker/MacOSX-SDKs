/*
     File:       CarbonSound/Sound.h
 
     Contains:   Sound Manager Interfaces.
 
     Version:    CarbonSound-65~5
 
     Copyright:  © 1986-2001 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __SOUND__
#define __SOUND__

#ifndef __MACTYPES__
#include <CarbonCore/MacTypes.h>
#endif

#ifndef __COMPONENTS__
#include <CarbonCore/Components.h>
#endif

#ifndef __MIXEDMODE__
#include <CarbonCore/MixedMode.h>
#endif

#ifndef __DIALOGS__
#include <HIToolbox/Dialogs.h>
#endif




#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if PRAGMA_STRUCT_ALIGN
    #pragma options align=mac68k
#elif PRAGMA_STRUCT_PACKPUSH
    #pragma pack(push, 2)
#elif PRAGMA_STRUCT_PACK
    #pragma pack(2)
#endif

/*
                        * * *  N O T E  * * *

    This file has been updated to include Sound Manager 3.3 interfaces.

    Some of the Sound Manager 3.0 interfaces were not put into the InterfaceLib
    that originally shipped with the PowerMacs. These missing functions and the
    new 3.3 interfaces have been released in the SoundLib library for PowerPC
    developers to link with. The runtime library for these functions are
    installed by the Sound Manager. The following functions are found in SoundLib.

        GetCompressionInfo(), GetSoundPreference(), SetSoundPreference(),
        UnsignedFixedMulDiv(), SndGetInfo(), SndSetInfo(), GetSoundOutputInfo(),
        SetSoundOutputInfo(), GetCompressionName(), SoundConverterOpen(),
        SoundConverterClose(), SoundConverterGetBufferSizes(), SoundConverterBeginConversion(),
        SoundConverterConvertBuffer(), SoundConverterEndConversion(),
        AudioGetBass(), AudioGetInfo(), AudioGetMute(), AudioGetOutputDevice(),
        AudioGetTreble(), AudioGetVolume(), AudioMuteOnEvent(), AudioSetBass(),
        AudioSetMute(), AudioSetToDefaults(), AudioSetTreble(), AudioSetVolume(),
        OpenMixerSoundComponent(), CloseMixerSoundComponent(), SoundComponentAddSource(),
        SoundComponentGetInfo(), SoundComponentGetSource(), SoundComponentGetSourceData(),
        SoundComponentInitOutputDevice(), SoundComponentPauseSource(),
        SoundComponentPlaySourceBuffer(), SoundComponentRemoveSource(),
        SoundComponentSetInfo(), SoundComponentSetOutput(), SoundComponentSetSource(),
        SoundComponentStartSource(), SoundComponentStopSource(),
        ParseAIFFHeader(), ParseSndHeader(), SoundConverterGetInfo(), SoundConverterSetInfo()
*/
/*
    Interfaces for Sound Driver, !!! OBSOLETE and NOT SUPPORTED !!!

    These items are no longer defined, but appear here so that someone
    searching the interfaces might find them. If you are using one of these
    items, you must change your code to support the Sound Manager.

        swMode, ftMode, ffMode
        FreeWave, FFSynthRec, Tone, SWSynthRec, Wave, FTSoundRec
        SndCompletionProcPtr
        StartSound, StopSound, SoundDone
        SetSoundVol, GetSoundVol
*/
/*
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   constants
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
#define twelfthRootTwo 1.05946309435

enum {
  soundListRsrc                 = 'snd ' /*Resource type used by Sound Manager*/
};

enum {
  kSimpleBeepID                 = 1     /*reserved resource ID for Simple Beep*/
};

enum {
  rate48khz                     = (long)0xBB800000, /*48000.00000 in fixed-point*/
  rate44khz                     = (long)0xAC440000, /*44100.00000 in fixed-point*/
  rate32khz                     = 0x7D000000, /*32000.00000 in fixed-point*/
  rate22050hz                   = 0x56220000, /*22050.00000 in fixed-point*/
  rate22khz                     = 0x56EE8BA3, /*22254.54545 in fixed-point*/
  rate16khz                     = 0x3E800000, /*16000.00000 in fixed-point*/
  rate11khz                     = 0x2B7745D1, /*11127.27273 in fixed-point*/
  rate11025hz                   = 0x2B110000, /*11025.00000 in fixed-point*/
  rate8khz                      = 0x1F400000 /* 8000.00000 in fixed-point*/
};

/*synthesizer numbers for SndNewChannel*/
enum {
  sampledSynth                  = 5     /*sampled sound synthesizer*/
};

#if CALL_NOT_IN_CARBON
enum {
  squareWaveSynth               = 1,    /*square wave synthesizer*/
  waveTableSynth                = 3,    /*wave table synthesizer*/
                                        /*old Sound Manager MACE synthesizer numbers*/
  MACE3snthID                   = 11,
  MACE6snthID                   = 13
};

#endif  /* CALL_NOT_IN_CARBON */

enum {
  kMiddleC                      = 60    /*MIDI note value for middle C*/
};

enum {
  kNoVolume                     = 0,    /*setting for no sound volume*/
  kFullVolume                   = 0x0100 /*1.0, setting for full hardware output volume*/
};

enum {
  stdQLength                    = 128
};

enum {
  dataOffsetFlag                = 0x8000
};

enum {
  kUseOptionalOutputDevice      = -1    /*only for Sound Manager 3.0 or later*/
};

enum {
  notCompressed                 = 0,    /*compression ID's*/
  fixedCompression              = -1,   /*compression ID for fixed-sized compression*/
  variableCompression           = -2    /*compression ID for variable-sized compression*/
};

enum {
  twoToOne                      = 1,
  eightToThree                  = 2,
  threeToOne                    = 3,
  sixToOne                      = 4,
  sixToOnePacketSize            = 8,
  threeToOnePacketSize          = 16
};

enum {
  stateBlockSize                = 64,
  leftOverBlockSize             = 32
};

enum {
  firstSoundFormat              = 0x0001, /*general sound format*/
  secondSoundFormat             = 0x0002 /*special sampled sound format (HyperCard)*/
};

#if CALL_NOT_IN_CARBON
enum {
  dbBufferReady                 = 0x00000001, /*double buffer is filled*/
  dbLastBuffer                  = 0x00000004 /*last double buffer to play*/
};

#endif  /* CALL_NOT_IN_CARBON */

enum {
  sysBeepDisable                = 0x0000, /*SysBeep() enable flags*/
  sysBeepEnable                 = (1 << 0),
  sysBeepSynchronous            = (1 << 1) /*if bit set, make alert sounds synchronous*/
};

enum {
  unitTypeNoSelection           = 0xFFFF, /*unitTypes for AudioSelection.unitType*/
  unitTypeSeconds               = 0x0000
};

enum {
  stdSH                         = 0x00, /*Standard sound header encode value*/
  extSH                         = 0xFF, /*Extended sound header encode value*/
  cmpSH                         = 0xFE  /*Compressed sound header encode value*/
};

/*command numbers for SndDoCommand and SndDoImmediate*/
enum {
  nullCmd                       = 0,
  quietCmd                      = 3,
  flushCmd                      = 4,
  reInitCmd                     = 5,
  waitCmd                       = 10,
  pauseCmd                      = 11,
  resumeCmd                     = 12,
  callBackCmd                   = 13,
  syncCmd                       = 14,
  availableCmd                  = 24,
  versionCmd                    = 25,
  volumeCmd                     = 46,   /*sound manager 3.0 or later only*/
  getVolumeCmd                  = 47,   /*sound manager 3.0 or later only*/
  clockComponentCmd             = 50,   /*sound manager 3.2.1 or later only*/
  getClockComponentCmd          = 51,   /*sound manager 3.2.1 or later only*/
  scheduledSoundCmd             = 52,   /*sound manager 3.3 or later only*/
  linkSoundComponentsCmd        = 53,   /*sound manager 3.3 or later only*/
  soundCmd                      = 80,
  bufferCmd                     = 81,
  rateMultiplierCmd             = 86,
  getRateMultiplierCmd          = 87
};

#if CALL_NOT_IN_CARBON
/*command numbers for SndDoCommand and SndDoImmediate that are not available for use in Carbon */
enum {
  initCmd                       = 1,
  freeCmd                       = 2,
  totalLoadCmd                  = 26,
  loadCmd                       = 27,
  freqDurationCmd               = 40,
  restCmd                       = 41,
  freqCmd                       = 42,
  ampCmd                        = 43,
  timbreCmd                     = 44,
  getAmpCmd                     = 45,
  waveTableCmd                  = 60,
  phaseCmd                      = 61,
  rateCmd                       = 82,
  continueCmd                   = 83,
  doubleBufferCmd               = 84,
  getRateCmd                    = 85,
  sizeCmd                       = 90,   /*obsolete command*/
  convertCmd                    = 91    /*obsolete MACE command*/
};

#endif  /* CALL_NOT_IN_CARBON */

#if OLDROUTINENAMES
/*channel initialization parameters*/
enum {
  waveInitChannelMask           = 0x07,
  waveInitChannel0              = 0x04, /*wave table only, Sound Manager 2.0 and earlier*/
  waveInitChannel1              = 0x05, /*wave table only, Sound Manager 2.0 and earlier*/
  waveInitChannel2              = 0x06, /*wave table only, Sound Manager 2.0 and earlier*/
  waveInitChannel3              = 0x07, /*wave table only, Sound Manager 2.0 and earlier*/
  initChan0                     = waveInitChannel0, /*obsolete spelling*/
  initChan1                     = waveInitChannel1, /*obsolete spelling*/
  initChan2                     = waveInitChannel2, /*obsolete spelling*/
  initChan3                     = waveInitChannel3 /*obsolete spelling*/
};

enum {
  outsideCmpSH                  = 0,    /*obsolete MACE constant*/
  insideCmpSH                   = 1,    /*obsolete MACE constant*/
  aceSuccess                    = 0,    /*obsolete MACE constant*/
  aceMemFull                    = 1,    /*obsolete MACE constant*/
  aceNilBlock                   = 2,    /*obsolete MACE constant*/
  aceBadComp                    = 3,    /*obsolete MACE constant*/
  aceBadEncode                  = 4,    /*obsolete MACE constant*/
  aceBadDest                    = 5,    /*obsolete MACE constant*/
  aceBadCmd                     = 6     /*obsolete MACE constant*/
};

#endif  /* OLDROUTINENAMES */

enum {
  initChanLeft                  = 0x0002, /*left stereo channel*/
  initChanRight                 = 0x0003, /*right stereo channel*/
  initNoInterp                  = 0x0004, /*no linear interpolation*/
  initNoDrop                    = 0x0008, /*no drop-sample conversion*/
  initMono                      = 0x0080, /*monophonic channel*/
  initStereo                    = 0x00C0, /*stereo channel*/
  initMACE3                     = 0x0300, /*MACE 3:1*/
  initMACE6                     = 0x0400, /*MACE 6:1*/
  initPanMask                   = 0x0003, /*mask for right/left pan values*/
  initSRateMask                 = 0x0030, /*mask for sample rate values*/
  initStereoMask                = 0x00C0, /*mask for mono/stereo values*/
  initCompMask                  = 0xFF00 /*mask for compression IDs*/
};

/*Get&Set Sound Information Selectors*/
enum {
  siActiveChannels              = 'chac', /*active channels*/
  siActiveLevels                = 'lmac', /*active meter levels*/
  siAGCOnOff                    = 'agc ', /*automatic gain control state*/
  siAsync                       = 'asyn', /*asynchronous capability*/
  siAVDisplayBehavior           = 'avdb',
  siChannelAvailable            = 'chav', /*number of channels available*/
  siCompressionAvailable        = 'cmav', /*compression types available*/
  siCompressionChannels         = 'cpct', /*compressor's number of channels*/
  siCompressionFactor           = 'cmfa', /*current compression factor*/
  siCompressionHeader           = 'cmhd', /*return compression header*/
  siCompressionNames            = 'cnam', /*compression type names available*/
  siCompressionParams           = 'evaw', /*compression parameters*/
  siCompressionSampleRate       = 'cprt', /*compressor's sample rate*/
  siCompressionType             = 'comp', /*current compression type*/
  siContinuous                  = 'cont', /*continous recording*/
  siDecompressionParams         = 'wave', /*decompression parameters*/
  siDeviceBufferInfo            = 'dbin', /*size of interrupt buffer*/
  siDeviceConnected             = 'dcon', /*input device connection status*/
  siDeviceIcon                  = 'icon', /*input device icon*/
  siDeviceName                  = 'name', /*input device name*/
  siEQSpectrumBands             = 'eqsb', /* number of spectrum bands*/
  siEQSpectrumLevels            = 'eqlv', /* gets spectum meter levels*/
  siEQSpectrumOnOff             = 'eqlo', /* turn on/off spectum meter levels*/
  siEQSpectrumResolution        = 'eqrs', /* set the resolution of the FFT, 0 = low res (<=16 bands), 1 = high res (16-64 bands)*/
  siEQToneControlGain           = 'eqtg', /* set the bass and treble gain*/
  siEQToneControlOnOff          = 'eqtc', /* turn on equalizer attenuation*/
  siHardwareBalance             = 'hbal',
  siHardwareBalanceSteps        = 'hbls',
  siHardwareBass                = 'hbas',
  siHardwareBassSteps           = 'hbst',
  siHardwareBusy                = 'hwbs', /*sound hardware is in use*/
  siHardwareFormat              = 'hwfm', /*get hardware format*/
  siHardwareMute                = 'hmut', /*mute state of all hardware*/
  siHardwareMuteNoPrefs         = 'hmnp', /*mute state of all hardware, but don't store in prefs */
  siHardwareTreble              = 'htrb',
  siHardwareTrebleSteps         = 'hwts',
  siHardwareVolume              = 'hvol', /*volume level of all hardware*/
  siHardwareVolumeSteps         = 'hstp', /*number of volume steps for hardware*/
  siHeadphoneMute               = 'pmut', /*mute state of headphones*/
  siHeadphoneVolume             = 'pvol', /*volume level of headphones*/
  siHeadphoneVolumeSteps        = 'hdst', /*number of volume steps for headphones*/
  siInputAvailable              = 'inav', /*input sources available*/
  siInputGain                   = 'gain', /*input gain*/
  siInputSource                 = 'sour', /*input source selector*/
  siInputSourceNames            = 'snam', /*input source names*/
  siLevelMeterOnOff             = 'lmet', /*level meter state*/
  siModemGain                   = 'mgai', /*modem input gain*/
  siMonitorAvailable            = 'mnav',
  siMonitorSource               = 'mons',
  siNumberChannels              = 'chan', /*current number of channels*/
  siOptionsDialog               = 'optd', /*display options dialog*/
  siOSTypeInputSource           = 'inpt', /*input source by OSType*/
  siOSTypeInputAvailable        = 'inav', /*list of available input source OSTypes*/
  siOutputDeviceName            = 'onam', /*output device name*/
  siPlayThruOnOff               = 'plth', /*playthrough state*/
  siPostMixerSoundComponent     = 'psmx', /*install post-mixer effect*/
  siPreMixerSoundComponent      = 'prmx', /*install pre-mixer effect*/
  siQuality                     = 'qual', /*quality setting*/
  siRateMultiplier              = 'rmul', /*throttle rate setting*/
  siRecordingQuality            = 'qual', /*recording quality*/
  siSampleRate                  = 'srat', /*current sample rate*/
  siSampleRateAvailable         = 'srav', /*sample rates available*/
  siSampleSize                  = 'ssiz', /*current sample size*/
  siSampleSizeAvailable         = 'ssav', /*sample sizes available*/
  siSetupCDAudio                = 'sucd', /*setup sound hardware for CD audio*/
  siSetupModemAudio             = 'sumd', /*setup sound hardware for modem audio*/
  siSlopeAndIntercept           = 'flap', /*floating point variables for conversion*/
  siSoundClock                  = 'sclk',
  siUseThisSoundClock           = 'sclc', /*sdev uses this to tell the mixer to use his sound clock*/
  siSpeakerMute                 = 'smut', /*mute state of all built-in speaker*/
  siSpeakerVolume               = 'svol', /*volume level of built-in speaker*/
  siSSpCPULoadLimit             = '3dll',
  siSSpLocalization             = '3dif',
  siSSpSpeakerSetup             = '3dst',
  siStereoInputGain             = 'sgai', /*stereo input gain*/
  siSubwooferMute               = 'bmut', /*mute state of sub-woofer*/
  siTerminalType                = 'ttyp', /* usb terminal type */
  siTwosComplementOnOff         = 'twos', /*two's complement state*/
  siVendorProduct               = 'vpro', /* vendor and product ID */
  siVolume                      = 'volu', /*volume level of source*/
  siVoxRecordInfo               = 'voxr', /*VOX record parameters*/
  siVoxStopInfo                 = 'voxs', /*VOX stop parameters*/
  siWideStereo                  = 'wide', /*wide stereo setting*/
  siSupportedExtendedFlags      = 'exfl', /*which flags are supported in Extended sound data structures*/
  siRateConverterRollOffSlope   = 'rcdb', /*the roll-off slope for the rate converter's filter, in whole dB as a long this value is a long whose range is from 20 (worst quality/fastest performance) to 90 (best quality/slowest performance)*/
  siOutputLatency               = 'olte', /*latency of sound output component*/
  siHALAudioDeviceID            = 'hlid' /*audio device id*/
};

enum {
  siCloseDriver                 = 'clos', /*reserved for internal use only*/
  siInitializeDriver            = 'init', /*reserved for internal use only*/
  siPauseRecording              = 'paus', /*reserved for internal use only*/
  siUserInterruptProc           = 'user' /*reserved for internal use only*/
};

/* input source Types*/
enum {
  kInvalidSource                = (long)0xFFFFFFFF, /*this source may be returned from GetInfo if no other source is the monitored source*/
  kNoSource                     = 'none', /*no source selection*/
  kCDSource                     = 'cd  ', /*internal CD player input*/
  kExtMicSource                 = 'emic', /*external mic input*/
  kSoundInSource                = 'sinj', /*sound input jack*/
  kRCAInSource                  = 'irca', /*RCA jack input*/
  kTVFMTunerSource              = 'tvfm',
  kDAVInSource                  = 'idav', /*DAV analog input*/
  kIntMicSource                 = 'imic', /*internal mic input*/
  kMediaBaySource               = 'mbay', /*media bay input*/
  kModemSource                  = 'modm', /*modem input (internal modem on desktops, PCI input on PowerBooks)*/
  kPCCardSource                 = 'pcm ', /*PC Card pwm input*/
  kZoomVideoSource              = 'zvpc', /*zoom video input*/
  kDVDSource                    = 'dvda', /* DVD audio input*/
  kMicrophoneArray              = 'mica' /* microphone array*/
};

/*Sound Component Types and Subtypes*/
enum {
  kNoSoundComponentType         = '****',
  kSoundComponentType           = 'sift', /*component type*/
  kSoundComponentPPCType        = 'nift', /*component type for PowerPC code*/
  kRate8SubType                 = 'ratb', /*8-bit rate converter*/
  kRate16SubType                = 'ratw', /*16-bit rate converter*/
  kConverterSubType             = 'conv', /*sample format converter*/
  kSndSourceSubType             = 'sour', /*generic source component*/
  kMixerType                    = 'mixr',
  kMixer8SubType                = 'mixb', /*8-bit mixer*/
  kMixer16SubType               = 'mixw', /*16-bit mixer*/
  kSoundInputDeviceType         = 'sinp', /*sound input component*/
  kWaveInSubType                = 'wavi', /*Windows waveIn*/
  kWaveInSnifferSubType         = 'wisn', /*Windows waveIn sniffer*/
  kSoundOutputDeviceType        = 'sdev', /*sound output component*/
  kClassicSubType               = 'clas', /*classic hardware, i.e. Mac Plus*/
  kASCSubType                   = 'asc ', /*Apple Sound Chip device*/
  kDSPSubType                   = 'dsp ', /*DSP device*/
  kAwacsSubType                 = 'awac', /*Another of Will's Audio Chips device*/
  kGCAwacsSubType               = 'awgc', /*Awacs audio with Grand Central DMA*/
  kSingerSubType                = 'sing', /*Singer (via Whitney) based sound*/
  kSinger2SubType               = 'sng2', /*Singer 2 (via Whitney) for Acme*/
  kWhitSubType                  = 'whit', /*Whit sound component for PrimeTime 3*/
  kSoundBlasterSubType          = 'sbls', /*Sound Blaster for CHRP*/
  kWaveOutSubType               = 'wavo', /*Windows waveOut*/
  kWaveOutSnifferSubType        = 'wosn', /*Windows waveOut sniffer*/
  kDirectSoundSubType           = 'dsnd', /*Windows DirectSound*/
  kDirectSoundSnifferSubType    = 'dssn', /*Windows DirectSound sniffer*/
  kUNIXsdevSubType              = 'un1x', /*UNIX base sdev*/
  kUSBSubType                   = 'usb ', /*USB device*/
  kBlueBoxSubType               = 'bsnd', /*Blue Box sound component*/
  kSoundCompressor              = 'scom',
  kSoundDecompressor            = 'sdec',
  kAudioComponentType           = 'adio', /*Audio components and sub-types*/
  kAwacsPhoneSubType            = 'hphn',
  kAudioVisionSpeakerSubType    = 'telc',
  kAudioVisionHeadphoneSubType  = 'telh',
  kPhilipsFaderSubType          = 'tvav',
  kSGSToneSubType               = 'sgs0',
  kSoundEffectsType             = 'snfx', /*sound effects type*/
  kEqualizerSubType             = 'eqal', /*frequency equalizer*/
  kSSpLocalizationSubType       = 'snd3'
};

/*Format Types*/
enum {
  kSoundNotCompressed           = 'NONE', /*sound is not compressed*/
  k8BitOffsetBinaryFormat       = 'raw ', /*8-bit offset binary*/
  k16BitBigEndianFormat         = 'twos', /*16-bit big endian*/
  k16BitLittleEndianFormat      = 'sowt', /*16-bit little endian*/
  kFloat32Format                = 'fl32', /*32-bit floating point*/
  kFloat64Format                = 'fl64', /*64-bit floating point*/
  k24BitFormat                  = 'in24', /*24-bit integer*/
  k32BitFormat                  = 'in32', /*32-bit integer*/
  k32BitLittleEndianFormat      = '23ni', /*32-bit little endian integer */
  kMACE3Compression             = 'MAC3', /*MACE 3:1*/
  kMACE6Compression             = 'MAC6', /*MACE 6:1*/
  kCDXA4Compression             = 'cdx4', /*CD/XA 4:1*/
  kCDXA2Compression             = 'cdx2', /*CD/XA 2:1*/
  kIMACompression               = 'ima4', /*IMA 4:1*/
  kULawCompression              = 'ulaw', /*µLaw 2:1*/
  kALawCompression              = 'alaw', /*aLaw 2:1*/
  kMicrosoftADPCMFormat         = 0x6D730002, /*Microsoft ADPCM - ACM code 2*/
  kDVIIntelIMAFormat            = 0x6D730011, /*DVI/Intel IMA ADPCM - ACM code 17*/
  kDVAudioFormat                = 'dvca', /*DV Audio*/
  kQDesignCompression           = 'QDMC', /*QDesign music*/
  kQDesign2Compression          = 'QDM2', /*QDesign2 music*/
  kQUALCOMMCompression          = 'Qclp', /*QUALCOMM PureVoice*/
  kOffsetBinary                 = k8BitOffsetBinaryFormat, /*for compatibility*/
  kTwosComplement               = k16BitBigEndianFormat, /*for compatibility*/
  kLittleEndianFormat           = k16BitLittleEndianFormat, /*for compatibility*/
  kMPEGLayer3Format             = 0x6D730055, /*MPEG Layer 3, CBR only (pre QT4.1)*/
  kFullMPEGLay3Format           = '.mp3' /*MPEG Layer 3, CBR & VBR (QT4.1 and later)*/
};

#if TARGET_RT_LITTLE_ENDIAN
enum {
  k16BitNativeEndianFormat      = k16BitLittleEndianFormat,
  k16BitNonNativeEndianFormat   = k16BitBigEndianFormat
};

#else
enum {
  k16BitNativeEndianFormat      = k16BitBigEndianFormat,
  k16BitNonNativeEndianFormat   = k16BitLittleEndianFormat
};

#endif  /* TARGET_RT_LITTLE_ENDIAN */

/*Features Flags*/
enum {
  k8BitRawIn                    = (1 << 0), /*data description*/
  k8BitTwosIn                   = (1 << 1),
  k16BitIn                      = (1 << 2),
  kStereoIn                     = (1 << 3),
  k8BitRawOut                   = (1 << 8),
  k8BitTwosOut                  = (1 << 9),
  k16BitOut                     = (1 << 10),
  kStereoOut                    = (1 << 11),
  kReverse                      = (1L << 16), /*  function description*/
  kRateConvert                  = (1L << 17),
  kCreateSoundSource            = (1L << 18),
  kVMAwareness                  = (1L << 21), /* component will hold its memory*/
  kHighQuality                  = (1L << 22), /*  performance description*/
  kNonRealTime                  = (1L << 23)
};

/*SoundComponentPlaySourceBuffer action flags*/
enum {
  kSourcePaused                 = (1 << 0),
  kPassThrough                  = (1L << 16),
  kNoSoundComponentChain        = (1L << 17)
};

/*SoundParamBlock flags, usefull for OpenMixerSoundComponent*/
enum {
  kNoMixing                     = (1 << 0), /*don't mix source*/
  kNoSampleRateConversion       = (1 << 1), /*don't convert sample rate (i.e. 11 kHz -> 22 kHz)*/
  kNoSampleSizeConversion       = (1 << 2), /*don't convert sample size (i.e. 16 -> 8)*/
  kNoSampleFormatConversion     = (1 << 3), /*don't convert sample format (i.e. 'twos' -> 'raw ')*/
  kNoChannelConversion          = (1 << 4), /*don't convert stereo/mono*/
  kNoDecompression              = (1 << 5), /*don't decompress (i.e. 'MAC3' -> 'raw ')*/
  kNoVolumeConversion           = (1 << 6), /*don't apply volume*/
  kNoRealtimeProcessing         = (1 << 7), /*won't run at interrupt time*/
  kScheduledSource              = (1 << 8), /*source is scheduled*/
  kNonInterleavedBuffer         = (1 << 9), /*buffer is not interleaved samples*/
  kNonPagingMixer               = (1 << 10), /*if VM is on, use the non-paging mixer*/
  kSoundConverterMixer          = (1 << 11), /*the mixer is to be used by the SoundConverter*/
  kPagingMixer                  = (1 << 12), /*the mixer is to be used as a paging mixer when VM is on*/
  kVMAwareMixer                 = (1 << 13), /*passed to the output device when the SM is going to deal with VM safety*/
  kExtendedSoundData            = (1 << 14) /*SoundComponentData record is actually an ExtendedSoundComponentData*/
};

/*SoundParamBlock quality settings*/
enum {
  kBestQuality                  = (1 << 0) /*use interpolation in rate conversion*/
};

/*useful bit masks*/
enum {
  kInputMask                    = 0x000000FF, /*masks off input bits*/
  kOutputMask                   = 0x0000FF00, /*masks off output bits*/
  kOutputShift                  = 8,    /*amount output bits are shifted*/
  kActionMask                   = 0x00FF0000, /*masks off action bits*/
  kSoundComponentBits           = 0x00FFFFFF
};

/*audio atom types*/
enum {
  kAudioFormatAtomType          = 'frma',
  kAudioEndianAtomType          = 'enda',
  kAudioVBRAtomType             = 'vbra',
  kAudioTerminatorAtomType      = 0
};

/*siAVDisplayBehavior types*/
enum {
  kAVDisplayHeadphoneRemove     = 0,    /* monitor does not have a headphone attached*/
  kAVDisplayHeadphoneInsert     = 1,    /* monitor has a headphone attached*/
  kAVDisplayPlainTalkRemove     = 2,    /* monitor either sending no input through CPU input port or unable to tell if input is coming in*/
  kAVDisplayPlainTalkInsert     = 3     /* monitor sending PlainTalk level microphone source input through sound input port*/
};

/*Audio Component constants*/
enum {
                                        /*Values for whichChannel parameter*/
  audioAllChannels              = 0,    /*All channels (usually interpreted as both left and right)*/
  audioLeftChannel              = 1,    /*Left channel*/
  audioRightChannel             = 2,    /*Right channel*/
                                        /*Values for mute parameter*/
  audioUnmuted                  = 0,    /*Device is unmuted*/
  audioMuted                    = 1,    /*Device is muted*/
                                        /*Capabilities flags definitions*/
  audioDoesMono                 = (1L << 0), /*Device supports mono output*/
  audioDoesStereo               = (1L << 1), /*Device supports stereo output*/
  audioDoesIndependentChannels  = (1L << 2) /*Device supports independent software control of each channel*/
};

/*Sound Input Qualities*/
enum {
  siCDQuality                   = 'cd  ', /*44.1kHz, stereo, 16 bit*/
  siBestQuality                 = 'best', /*22kHz, mono, 8 bit*/
  siBetterQuality               = 'betr', /*22kHz, mono, MACE 3:1*/
  siGoodQuality                 = 'good', /*22kHz, mono, MACE 6:1*/
  siNoneQuality                 = 'none' /*settings don't match any quality for a get call*/
};

enum {
  siDeviceIsConnected           = 1,    /*input device is connected and ready for input*/
  siDeviceNotConnected          = 0,    /*input device is not connected*/
  siDontKnowIfConnected         = -1,   /*can't tell if input device is connected*/
  siReadPermission              = 0,    /*permission passed to SPBOpenDevice*/
  siWritePermission             = 1     /*permission passed to SPBOpenDevice*/
};

/*flags that SoundConverterFillBuffer will return*/
enum {
  kSoundConverterDidntFillBuffer = (1 << 0), /*set if the converter couldn't completely satisfy a SoundConverterFillBuffer request*/
  kSoundConverterHasLeftOverData = (1 << 1) /*set if the converter had left over data after completely satisfying a SoundConverterFillBuffer call*/
};

/* flags for extendedFlags fields of ExtendedSoundComponentData, ExtendedSoundParamBlock, and ExtendedScheduledSoundHeader*/
enum {
  kExtendedSoundSampleCountNotValid = 1L << 0, /* set if sampleCount of SoundComponentData isn't meaningful; use buffer size instead*/
  kExtendedSoundBufferSizeValid = 1L << 1 /* set if bufferSize field is valid*/
};

/*
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   typedefs
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

struct SndCommand {
  unsigned short      cmd;
  short               param1;
  long                param2;
};
typedef struct SndCommand               SndCommand;
typedef struct SndChannel               SndChannel;

typedef SndChannel *                    SndChannelPtr;
typedef CALLBACK_API( void , SndCallBackProcPtr )(SndChannelPtr chan, SndCommand *cmd);
typedef STACK_UPP_TYPE(SndCallBackProcPtr)                      SndCallBackUPP;
struct SndChannel {
  SndChannelPtr       nextChan;
  Ptr                 firstMod;               /* reserved for the Sound Manager */
  SndCallBackUPP      callBack;
  long                userInfo;
  long                wait;                   /* The following is for internal Sound Manager use only.*/
  SndCommand          cmdInProgress;
  short               flags;
  short               qLength;
  short               qHead;
  short               qTail;
  SndCommand          queue[128];
};

/*
 *  NewSndCallBackUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern SndCallBackUPP
NewSndCallBackUPP(SndCallBackProcPtr userRoutine);

/*
 *  DisposeSndCallBackUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeSndCallBackUPP(SndCallBackUPP userUPP);

/*
 *  InvokeSndCallBackUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeSndCallBackUPP(
  SndChannelPtr   chan,
  SndCommand *    cmd,
  SndCallBackUPP  userUPP);

/*MACE structures*/
struct StateBlock {
  short               stateVar[64];
};
typedef struct StateBlock               StateBlock;
typedef StateBlock *                    StateBlockPtr;
struct LeftOverBlock {
  unsigned long       count;
  SInt8               sampleArea[32];
};
typedef struct LeftOverBlock            LeftOverBlock;
typedef LeftOverBlock *                 LeftOverBlockPtr;
struct ModRef {
  unsigned short      modNumber;
  long                modInit;
};
typedef struct ModRef                   ModRef;
struct SndListResource {
  short               format;
  short               numModifiers;
  ModRef              modifierPart[1];
  short               numCommands;
  SndCommand          commandPart[1];
  UInt8               dataPart[1];
};
typedef struct SndListResource          SndListResource;
typedef SndListResource *               SndListPtr;
typedef SndListPtr *                    SndListHandle;
typedef SndListHandle                   SndListHndl;
/*HyperCard sound resource format*/
struct Snd2ListResource {
  short               format;
  short               refCount;
  short               numCommands;
  SndCommand          commandPart[1];
  UInt8               dataPart[1];
};
typedef struct Snd2ListResource         Snd2ListResource;
typedef Snd2ListResource *              Snd2ListPtr;
typedef Snd2ListPtr *                   Snd2ListHandle;
typedef Snd2ListHandle                  Snd2ListHndl;
struct SoundHeader {
  Ptr                 samplePtr;              /*if NIL then samples are in sampleArea*/
  unsigned long       length;                 /*length of sound in bytes*/
  UnsignedFixed       sampleRate;             /*sample rate for this sound*/
  unsigned long       loopStart;              /*start of looping portion*/
  unsigned long       loopEnd;                /*end of looping portion*/
  UInt8               encode;                 /*header encoding*/
  UInt8               baseFrequency;          /*baseFrequency value*/
  UInt8               sampleArea[1];          /*space for when samples follow directly*/
};
typedef struct SoundHeader              SoundHeader;
typedef SoundHeader *                   SoundHeaderPtr;
struct CmpSoundHeader {
  Ptr                 samplePtr;              /*if nil then samples are in sample area*/
  unsigned long       numChannels;            /*number of channels i.e. mono = 1*/
  UnsignedFixed       sampleRate;             /*sample rate in Apples Fixed point representation*/
  unsigned long       loopStart;              /*loopStart of sound before compression*/
  unsigned long       loopEnd;                /*loopEnd of sound before compression*/
  UInt8               encode;                 /*data structure used , stdSH, extSH, or cmpSH*/
  UInt8               baseFrequency;          /*same meaning as regular SoundHeader*/
  unsigned long       numFrames;              /*length in frames ( packetFrames or sampleFrames )*/
  extended80          AIFFSampleRate;         /*IEEE sample rate*/
  Ptr                 markerChunk;            /*sync track*/
  OSType              format;                 /*data format type, was futureUse1*/
  unsigned long       futureUse2;             /*reserved by Apple*/
  StateBlockPtr       stateVars;              /*pointer to State Block*/
  LeftOverBlockPtr    leftOverSamples;        /*used to save truncated samples between compression calls*/
  short               compressionID;          /*0 means no compression, non zero means compressionID*/
  unsigned short      packetSize;             /*number of bits in compressed sample packet*/
  unsigned short      snthID;                 /*resource ID of Sound Manager snth that contains NRT C/E*/
  unsigned short      sampleSize;             /*number of bits in non-compressed sample*/
  UInt8               sampleArea[1];          /*space for when samples follow directly*/
};
typedef struct CmpSoundHeader           CmpSoundHeader;
typedef CmpSoundHeader *                CmpSoundHeaderPtr;
struct ExtSoundHeader {
  Ptr                 samplePtr;              /*if nil then samples are in sample area*/
  unsigned long       numChannels;            /*number of channels,  ie mono = 1*/
  UnsignedFixed       sampleRate;             /*sample rate in Apples Fixed point representation*/
  unsigned long       loopStart;              /*same meaning as regular SoundHeader*/
  unsigned long       loopEnd;                /*same meaning as regular SoundHeader*/
  UInt8               encode;                 /*data structure used , stdSH, extSH, or cmpSH*/
  UInt8               baseFrequency;          /*same meaning as regular SoundHeader*/
  unsigned long       numFrames;              /*length in total number of frames*/
  extended80          AIFFSampleRate;         /*IEEE sample rate*/
  Ptr                 markerChunk;            /*sync track*/
  Ptr                 instrumentChunks;       /*AIFF instrument chunks*/
  Ptr                 AESRecording;
  unsigned short      sampleSize;             /*number of bits in sample*/
  unsigned short      futureUse1;             /*reserved by Apple*/
  unsigned long       futureUse2;             /*reserved by Apple*/
  unsigned long       futureUse3;             /*reserved by Apple*/
  unsigned long       futureUse4;             /*reserved by Apple*/
  UInt8               sampleArea[1];          /*space for when samples follow directly*/
};
typedef struct ExtSoundHeader           ExtSoundHeader;
typedef ExtSoundHeader *                ExtSoundHeaderPtr;
union SoundHeaderUnion {
  SoundHeader         stdHeader;
  CmpSoundHeader      cmpHeader;
  ExtSoundHeader      extHeader;
};
typedef union SoundHeaderUnion          SoundHeaderUnion;
struct ConversionBlock {
  short               destination;
  short               unused;
  CmpSoundHeaderPtr   inputPtr;
  CmpSoundHeaderPtr   outputPtr;
};
typedef struct ConversionBlock          ConversionBlock;
typedef ConversionBlock *               ConversionBlockPtr;
/* ScheduledSoundHeader flags*/
enum {
  kScheduledSoundDoScheduled    = 1 << 0,
  kScheduledSoundDoCallBack     = 1 << 1,
  kScheduledSoundExtendedHdr    = 1 << 2
};

struct ScheduledSoundHeader {
  SoundHeaderUnion    u;
  long                flags;
  short               reserved;
  short               callBackParam1;
  long                callBackParam2;
  TimeRecord          startTime;
};
typedef struct ScheduledSoundHeader     ScheduledSoundHeader;
typedef ScheduledSoundHeader *          ScheduledSoundHeaderPtr;
struct ExtendedScheduledSoundHeader {
  SoundHeaderUnion    u;
  long                flags;
  short               reserved;
  short               callBackParam1;
  long                callBackParam2;
  TimeRecord          startTime;
  long                recordSize;
  long                extendedFlags;
  long                bufferSize;
};
typedef struct ExtendedScheduledSoundHeader ExtendedScheduledSoundHeader;
typedef ExtendedScheduledSoundHeader *  ExtendedScheduledSoundHeaderPtr;
struct SMStatus {
  short               smMaxCPULoad;
  short               smNumChannels;
  short               smCurCPULoad;
};
typedef struct SMStatus                 SMStatus;
typedef SMStatus *                      SMStatusPtr;
struct SCStatus {
  UnsignedFixed       scStartTime;
  UnsignedFixed       scEndTime;
  UnsignedFixed       scCurrentTime;
  Boolean             scChannelBusy;
  Boolean             scChannelDisposed;
  Boolean             scChannelPaused;
  Boolean             scUnused;
  unsigned long       scChannelAttributes;
  long                scCPULoad;
};
typedef struct SCStatus                 SCStatus;
typedef SCStatus *                      SCStatusPtr;
struct AudioSelection {
  long                unitType;
  UnsignedFixed       selStart;
  UnsignedFixed       selEnd;
};
typedef struct AudioSelection           AudioSelection;
typedef AudioSelection *                AudioSelectionPtr;
#if CALL_NOT_IN_CARBON
struct SndDoubleBuffer {
  long                dbNumFrames;
  long                dbFlags;
  long                dbUserInfo[2];
  SInt8               dbSoundData[1];
};
typedef struct SndDoubleBuffer          SndDoubleBuffer;
typedef SndDoubleBuffer *               SndDoubleBufferPtr;


typedef CALLBACK_API( void , SndDoubleBackProcPtr )(SndChannelPtr channel, SndDoubleBufferPtr doubleBufferPtr);
typedef STACK_UPP_TYPE(SndDoubleBackProcPtr)                    SndDoubleBackUPP;
/*
 *  NewSndDoubleBackUPP()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */

/*
 *  DisposeSndDoubleBackUPP()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */

/*
 *  InvokeSndDoubleBackUPP()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */

struct SndDoubleBufferHeader {
  short               dbhNumChannels;
  short               dbhSampleSize;
  short               dbhCompressionID;
  short               dbhPacketSize;
  UnsignedFixed       dbhSampleRate;
  SndDoubleBufferPtr  dbhBufferPtr[2];
  SndDoubleBackUPP    dbhDoubleBack;
};
typedef struct SndDoubleBufferHeader    SndDoubleBufferHeader;
typedef SndDoubleBufferHeader *         SndDoubleBufferHeaderPtr;
struct SndDoubleBufferHeader2 {
  short               dbhNumChannels;
  short               dbhSampleSize;
  short               dbhCompressionID;
  short               dbhPacketSize;
  UnsignedFixed       dbhSampleRate;
  SndDoubleBufferPtr  dbhBufferPtr[2];
  SndDoubleBackUPP    dbhDoubleBack;
  OSType              dbhFormat;
};
typedef struct SndDoubleBufferHeader2   SndDoubleBufferHeader2;
typedef SndDoubleBufferHeader2 *        SndDoubleBufferHeader2Ptr;
#endif  /* CALL_NOT_IN_CARBON */

struct SoundInfoList {
  short               count;
  Handle              infoHandle;
};
typedef struct SoundInfoList            SoundInfoList;
typedef SoundInfoList *                 SoundInfoListPtr;
struct SoundComponentData {
  long                flags;
  OSType              format;
  short               numChannels;
  short               sampleSize;
  UnsignedFixed       sampleRate;
  long                sampleCount;
  Byte *              buffer;
  long                reserved;
};
typedef struct SoundComponentData       SoundComponentData;
typedef SoundComponentData *            SoundComponentDataPtr;
struct ExtendedSoundComponentData {
  SoundComponentData  desc;                   /*description of sound buffer*/
  long                recordSize;             /*size of this record in bytes*/
  long                extendedFlags;          /*flags for extended record*/
  long                bufferSize;             /*size of buffer in bytes*/
};
typedef struct ExtendedSoundComponentData ExtendedSoundComponentData;
typedef ExtendedSoundComponentData *    ExtendedSoundComponentDataPtr;
typedef struct SoundParamBlock          SoundParamBlock;
typedef SoundParamBlock *               SoundParamBlockPtr;
typedef CALLBACK_API( Boolean , SoundParamProcPtr )(SoundParamBlockPtr * pb);
typedef STACK_UPP_TYPE(SoundParamProcPtr)                       SoundParamUPP;
struct SoundParamBlock {
  long                recordSize;             /*size of this record in bytes*/
  SoundComponentData  desc;                   /*description of sound buffer*/
  UnsignedFixed       rateMultiplier;         /*rate multiplier to apply to sound*/
  short               leftVolume;             /*volumes to apply to sound*/
  short               rightVolume;
  long                quality;                /*quality to apply to sound*/
  ComponentInstance   filter;                 /*filter to apply to sound*/
  SoundParamUPP       moreRtn;                /*routine to call to get more data*/
  SoundParamUPP       completionRtn;          /*routine to call when buffer is complete*/
  long                refCon;                 /*user refcon*/
  short               result;                 /*result*/
};

struct ExtendedSoundParamBlock {
  SoundParamBlock     pb;                     /*classic SoundParamBlock except recordSize == sizeof(ExtendedSoundParamBlock)*/
  short               reserved;
  long                extendedFlags;          /*flags*/
  long                bufferSize;             /*size of buffer in bytes*/
};
typedef struct ExtendedSoundParamBlock  ExtendedSoundParamBlock;
typedef ExtendedSoundParamBlock *       ExtendedSoundParamBlockPtr;
struct CompressionInfo {
  long                recordSize;
  OSType              format;
  short               compressionID;
  unsigned short      samplesPerPacket;
  unsigned short      bytesPerPacket;
  unsigned short      bytesPerFrame;
  unsigned short      bytesPerSample;
  unsigned short      futureUse1;
};
typedef struct CompressionInfo          CompressionInfo;
typedef CompressionInfo *               CompressionInfoPtr;
typedef CompressionInfoPtr *            CompressionInfoHandle;
/*variables for floating point conversion*/
struct SoundSlopeAndInterceptRecord {
  Float64             slope;
  Float64             intercept;
  Float64             minClip;
  Float64             maxClip;
};
typedef struct SoundSlopeAndInterceptRecord SoundSlopeAndInterceptRecord;
typedef SoundSlopeAndInterceptRecord *  SoundSlopeAndInterceptPtr;
/*private thing to use as a reference to a Sound Converter*/
typedef struct OpaqueSoundConverter*    SoundConverter;
/*callback routine to provide data to the Sound Converter*/
typedef CALLBACK_API( Boolean , SoundConverterFillBufferDataProcPtr )(SoundComponentDataPtr *data, void *refCon);
typedef STACK_UPP_TYPE(SoundConverterFillBufferDataProcPtr)     SoundConverterFillBufferDataUPP;
/*private thing to use as a reference to a Sound Source*/
typedef struct OpaqueSoundSource*       SoundSource;
typedef SoundSource *                   SoundSourcePtr;


struct SoundComponentLink {
  ComponentDescription  description;          /*Describes the sound component*/
  SoundSource         mixerID;                /*Reserved by Apple*/
  SoundSource *       linkID;                 /*Reserved by Apple*/
};
typedef struct SoundComponentLink       SoundComponentLink;
typedef SoundComponentLink *            SoundComponentLinkPtr;
struct AudioInfo {
  long                capabilitiesFlags;      /*Describes device capabilities*/
  long                reserved;               /*Reserved by Apple*/
  unsigned short      numVolumeSteps;         /*Number of significant increments between min and max volume*/
};
typedef struct AudioInfo                AudioInfo;
typedef AudioInfo *                     AudioInfoPtr;
struct AudioFormatAtom {
  long                size;                   /* = sizeof(AudioFormatAtom)*/
  OSType              atomType;               /* = kAudioFormatAtomType*/
  OSType              format;
};
typedef struct AudioFormatAtom          AudioFormatAtom;
typedef AudioFormatAtom *               AudioFormatAtomPtr;
struct AudioEndianAtom {
  long                size;                   /* = sizeof(AudioEndianAtom)*/
  OSType              atomType;               /* = kAudioEndianAtomType*/
  short               littleEndian;
};
typedef struct AudioEndianAtom          AudioEndianAtom;
typedef AudioEndianAtom *               AudioEndianAtomPtr;
struct AudioTerminatorAtom {
  long                size;                   /* = sizeof(AudioTerminatorAtom)*/
  OSType              atomType;               /* = kAudioTerminatorAtomType*/
};
typedef struct AudioTerminatorAtom      AudioTerminatorAtom;
typedef AudioTerminatorAtom *           AudioTerminatorAtomPtr;
struct LevelMeterInfo {
  short               numChannels;            /* mono or stereo source*/
  UInt8               leftMeter;              /* 0-255 range*/
  UInt8               rightMeter;             /* 0-255 range*/
};
typedef struct LevelMeterInfo           LevelMeterInfo;
typedef LevelMeterInfo *                LevelMeterInfoPtr;
struct EQSpectrumBandsRecord {
  short               count;
  UnsignedFixedPtr    frequency;              /* pointer to array of frequencies*/
};
typedef struct EQSpectrumBandsRecord    EQSpectrumBandsRecord;
typedef EQSpectrumBandsRecord *         EQSpectrumBandsRecordPtr;


/* Sound Input Structures*/
typedef struct SPB                      SPB;
typedef SPB *                           SPBPtr;


/*user procedures called by sound input routines*/
typedef CALLBACK_API( void , SIInterruptProcPtr )(SPBPtr inParamPtr, Ptr dataBuffer, short peakAmplitude, long sampleSize);
typedef CALLBACK_API( void , SICompletionProcPtr )(SPBPtr inParamPtr);
typedef STACK_UPP_TYPE(SIInterruptProcPtr)                      SIInterruptUPP;
typedef STACK_UPP_TYPE(SICompletionProcPtr)                     SICompletionUPP;


/*Sound Input Parameter Block*/
struct SPB {
  long                inRefNum;               /*reference number of sound input device*/
  unsigned long       count;                  /*number of bytes to record*/
  unsigned long       milliseconds;           /*number of milliseconds to record*/
  unsigned long       bufferLength;           /*length of buffer in bytes*/
  Ptr                 bufferPtr;              /*buffer to store sound data in*/
  SICompletionUPP     completionRoutine;      /*completion routine*/
  SIInterruptUPP      interruptRoutine;       /*interrupt routine*/
  long                userLong;               /*user-defined field*/
  OSErr               error;                  /*error*/
  long                unused1;                /*reserved - must be zero*/
};

/*
 *  NewSoundParamUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern SoundParamUPP
NewSoundParamUPP(SoundParamProcPtr userRoutine);

/*
 *  NewSoundConverterFillBufferDataUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern SoundConverterFillBufferDataUPP
NewSoundConverterFillBufferDataUPP(SoundConverterFillBufferDataProcPtr userRoutine);

/*
 *  NewSIInterruptUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern SIInterruptUPP
NewSIInterruptUPP(SIInterruptProcPtr userRoutine);

/*
 *  NewSICompletionUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern SICompletionUPP
NewSICompletionUPP(SICompletionProcPtr userRoutine);

/*
 *  DisposeSoundParamUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeSoundParamUPP(SoundParamUPP userUPP);

/*
 *  DisposeSoundConverterFillBufferDataUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeSoundConverterFillBufferDataUPP(SoundConverterFillBufferDataUPP userUPP);

/*
 *  DisposeSIInterruptUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeSIInterruptUPP(SIInterruptUPP userUPP);

/*
 *  DisposeSICompletionUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeSICompletionUPP(SICompletionUPP userUPP);

/*
 *  InvokeSoundParamUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern Boolean
InvokeSoundParamUPP(
  SoundParamBlockPtr *  pb,
  SoundParamUPP         userUPP);

/*
 *  InvokeSoundConverterFillBufferDataUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern Boolean
InvokeSoundConverterFillBufferDataUPP(
  SoundComponentDataPtr *          data,
  void *                           refCon,
  SoundConverterFillBufferDataUPP  userUPP);

/*
 *  InvokeSIInterruptUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeSIInterruptUPP(
  SPBPtr          inParamPtr,
  Ptr             dataBuffer,
  short           peakAmplitude,
  long            sampleSize,
  SIInterruptUPP  userUPP);

/*
 *  InvokeSICompletionUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeSICompletionUPP(
  SPBPtr           inParamPtr,
  SICompletionUPP  userUPP);

typedef CALLBACK_API( void , FilePlayCompletionProcPtr )(SndChannelPtr chan);
typedef STACK_UPP_TYPE(FilePlayCompletionProcPtr)               FilePlayCompletionUPP;
/*
 *  NewFilePlayCompletionUPP()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */

/*
 *  DisposeFilePlayCompletionUPP()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */

/*
 *  InvokeFilePlayCompletionUPP()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */

/*
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   prototypes
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/


/* Sound Manager routines */
/*
 *  SysBeep()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SysBeep(short duration);


/*
 *  SndDoCommand()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
SndDoCommand(
  SndChannelPtr       chan,
  const SndCommand *  cmd,
  Boolean             noWait);


/*
 *  SndDoImmediate()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
SndDoImmediate(
  SndChannelPtr       chan,
  const SndCommand *  cmd);


/*
 *  SndNewChannel()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
SndNewChannel(
  SndChannelPtr *  chan,
  short            synth,
  long             init,
  SndCallBackUPP   userRoutine);


/*
 *  SndDisposeChannel()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
SndDisposeChannel(
  SndChannelPtr   chan,
  Boolean         quietNow);


/*
 *  SndPlay()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
SndPlay(
  SndChannelPtr   chan,
  SndListHandle   sndHandle,
  Boolean         async);


#if OLDROUTINENAMES
/*
 *  SndAddModifier()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


#endif  /* OLDROUTINENAMES */

/*
 *  SndControl()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/* Sound Manager 2.0 and later, uses _SoundDispatch */
/*
 *  SndSoundManagerVersion()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern NumVersion 
SndSoundManagerVersion(void);


/*
 *  SndStartFilePlay()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  SndPauseFilePlay()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  SndStopFilePlay()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  SndChannelStatus()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
SndChannelStatus(
  SndChannelPtr   chan,
  short           theLength,
  SCStatusPtr     theStatus);


/*
 *  SndManagerStatus()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
SndManagerStatus(
  short         theLength,
  SMStatusPtr   theStatus);


/*
 *  SndGetSysBeepState()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SndGetSysBeepState(short * sysBeepState);


/*
 *  SndSetSysBeepState()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
SndSetSysBeepState(short sysBeepState);


/*
 *  SndPlayDoubleBuffer()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/* MACE compression routines, uses _SoundDispatch */
/*
 *  MACEVersion()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  Comp3to1()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  Exp1to3()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  Comp6to1()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  Exp1to6()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/* Sound Manager 3.0 and later calls, uses _SoundDispatch */
/*
 *  GetSysBeepVolume()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
GetSysBeepVolume(long * level);


/*
 *  SetSysBeepVolume()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
SetSysBeepVolume(long level);


/*
 *  GetDefaultOutputVolume()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
GetDefaultOutputVolume(long * level);


/*
 *  SetDefaultOutputVolume()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
SetDefaultOutputVolume(long level);


/*
 *  GetSoundHeaderOffset()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
GetSoundHeaderOffset(
  SndListHandle   sndHandle,
  long *          offset);


/*
 *  UnsignedFixedMulDiv()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in SoundLib 3.0 and later
 */
extern UnsignedFixed 
UnsignedFixedMulDiv(
  UnsignedFixed   value,
  UnsignedFixed   multiplier,
  UnsignedFixed   divisor);


/*
 *  GetCompressionInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in SoundLib 3.0 and later
 */
extern OSErr 
GetCompressionInfo(
  short                compressionID,
  OSType               format,
  short                numChannels,
  short                sampleSize,
  CompressionInfoPtr   cp);


/*
 *  SetSoundPreference()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in SoundLib 3.0 and later
 */
extern OSErr 
SetSoundPreference(
  OSType   theType,
  Str255   name,
  Handle   settings);


/*
 *  GetSoundPreference()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in SoundLib 3.0 and later
 */
extern OSErr 
GetSoundPreference(
  OSType   theType,
  Str255   name,
  Handle   settings);


/*
 *  OpenMixerSoundComponent()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in SoundLib 3.0 and later
 */
extern OSErr 
OpenMixerSoundComponent(
  SoundComponentDataPtr   outputDescription,
  long                    outputFlags,
  ComponentInstance *     mixerComponent);


/*
 *  CloseMixerSoundComponent()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in SoundLib 3.0 and later
 */
extern OSErr 
CloseMixerSoundComponent(ComponentInstance ci);


/* Sound Manager 3.1 and later calls, uses _SoundDispatch */
/*
 *  SndGetInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in SoundLib 3.1 and later
 */
extern OSErr 
SndGetInfo(
  SndChannelPtr   chan,
  OSType          selector,
  void *          infoPtr);


/*
 *  SndSetInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in SoundLib 3.1 and later
 */
extern OSErr 
SndSetInfo(
  SndChannelPtr   chan,
  OSType          selector,
  const void *    infoPtr);


/*
 *  GetSoundOutputInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in SoundLib 3.1 and later
 */
extern OSErr 
GetSoundOutputInfo(
  Component   outputDevice,
  OSType      selector,
  void *      infoPtr);


/*
 *  SetSoundOutputInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in SoundLib 3.1 and later
 */
extern OSErr 
SetSoundOutputInfo(
  Component     outputDevice,
  OSType        selector,
  const void *  infoPtr);


/* Sound Manager 3.2 and later calls, uses _SoundDispatch */
/*
 *  GetCompressionName()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in SoundLib 3.2 and later
 */
extern OSErr 
GetCompressionName(
  OSType   compressionType,
  Str255   compressionName);


/*
 *  SoundConverterOpen()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in SoundLib 3.2 and later
 */
extern OSErr 
SoundConverterOpen(
  const SoundComponentData *  inputFormat,
  const SoundComponentData *  outputFormat,
  SoundConverter *            sc);


/*
 *  SoundConverterClose()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in SoundLib 3.2 and later
 */
extern OSErr 
SoundConverterClose(SoundConverter sc);


/*
 *  SoundConverterGetBufferSizes()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in SoundLib 3.2 and later
 */
extern OSErr 
SoundConverterGetBufferSizes(
  SoundConverter   sc,
  unsigned long    inputBytesTarget,
  unsigned long *  inputFrames,
  unsigned long *  inputBytes,
  unsigned long *  outputBytes);


/*
 *  SoundConverterBeginConversion()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in SoundLib 3.2 and later
 */
extern OSErr 
SoundConverterBeginConversion(SoundConverter sc);


/*
 *  SoundConverterConvertBuffer()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in SoundLib 3.2 and later
 */
extern OSErr 
SoundConverterConvertBuffer(
  SoundConverter   sc,
  const void *     inputPtr,
  unsigned long    inputFrames,
  void *           outputPtr,
  unsigned long *  outputFrames,
  unsigned long *  outputBytes);


/*
 *  SoundConverterEndConversion()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in SoundLib 3.2 and later
 */
extern OSErr 
SoundConverterEndConversion(
  SoundConverter   sc,
  void *           outputPtr,
  unsigned long *  outputFrames,
  unsigned long *  outputBytes);


/* Sound Manager 3.3 and later calls, uses _SoundDispatch */
/*
 *  SoundConverterGetInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in SoundLib 3.3 and later
 */
extern OSErr 
SoundConverterGetInfo(
  SoundConverter   sc,
  OSType           selector,
  void *           infoPtr);


/*
 *  SoundConverterSetInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in SoundLib 3.3 and later
 */
extern OSErr 
SoundConverterSetInfo(
  SoundConverter   sc,
  OSType           selector,
  void *           infoPtr);


/* Sound Manager 3.6 and later calls, uses _SoundDispatch */
/*
 *  SoundConverterFillBuffer()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in SoundLib 3.6 and later
 */
extern OSErr 
SoundConverterFillBuffer(
  SoundConverter                    sc,
  SoundConverterFillBufferDataUPP   fillBufferDataUPP,
  void *                            fillBufferDataRefCon,
  void *                            outputBuffer,
  unsigned long                     outputBufferByteSize,
  unsigned long *                   bytesWritten,
  unsigned long *                   framesWritten,
  unsigned long *                   outputFlags);


/*
 *  SoundManagerGetInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in SoundLib 3.6 and later
 */
extern OSErr 
SoundManagerGetInfo(
  OSType   selector,
  void *   infoPtr);


/*
 *  SoundManagerSetInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in SoundLib 3.6 and later
 */
extern OSErr 
SoundManagerSetInfo(
  OSType        selector,
  const void *  infoPtr);


/*
  Sound Component Functions
   basic sound component functions
*/

/*
 *  SoundComponentInitOutputDevice()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in SoundLib 3.0 and later
 */
extern ComponentResult 
SoundComponentInitOutputDevice(
  ComponentInstance   ti,
  long                actions);


/*
 *  SoundComponentSetSource()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in SoundLib 3.0 and later
 */
extern ComponentResult 
SoundComponentSetSource(
  ComponentInstance   ti,
  SoundSource         sourceID,
  ComponentInstance   source);


/*
 *  SoundComponentGetSource()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in SoundLib 3.0 and later
 */
extern ComponentResult 
SoundComponentGetSource(
  ComponentInstance    ti,
  SoundSource          sourceID,
  ComponentInstance *  source);


/*
 *  SoundComponentGetSourceData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in SoundLib 3.0 and later
 */
extern ComponentResult 
SoundComponentGetSourceData(
  ComponentInstance        ti,
  SoundComponentDataPtr *  sourceData);


/*
 *  SoundComponentSetOutput()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in SoundLib 3.0 and later
 */
extern ComponentResult 
SoundComponentSetOutput(
  ComponentInstance        ti,
  SoundComponentDataPtr    requested,
  SoundComponentDataPtr *  actual);


/* junction methods for the mixer, must be called at non-interrupt level*/
/*
 *  SoundComponentAddSource()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in SoundLib 3.0 and later
 */
extern ComponentResult 
SoundComponentAddSource(
  ComponentInstance   ti,
  SoundSource *       sourceID);


/*
 *  SoundComponentRemoveSource()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in SoundLib 3.0 and later
 */
extern ComponentResult 
SoundComponentRemoveSource(
  ComponentInstance   ti,
  SoundSource         sourceID);


/* info methods*/
/*
 *  SoundComponentGetInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in SoundLib 3.0 and later
 */
extern ComponentResult 
SoundComponentGetInfo(
  ComponentInstance   ti,
  SoundSource         sourceID,
  OSType              selector,
  void *              infoPtr);


/*
 *  SoundComponentSetInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in SoundLib 3.0 and later
 */
extern ComponentResult 
SoundComponentSetInfo(
  ComponentInstance   ti,
  SoundSource         sourceID,
  OSType              selector,
  void *              infoPtr);


/* control methods*/
/*
 *  SoundComponentStartSource()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in SoundLib 3.0 and later
 */
extern ComponentResult 
SoundComponentStartSource(
  ComponentInstance   ti,
  short               count,
  SoundSource *       sources);


/*
 *  SoundComponentStopSource()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in SoundLib 3.0 and later
 */
extern ComponentResult 
SoundComponentStopSource(
  ComponentInstance   ti,
  short               count,
  SoundSource *       sources);


/*
 *  SoundComponentPauseSource()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in SoundLib 3.0 and later
 */
extern ComponentResult 
SoundComponentPauseSource(
  ComponentInstance   ti,
  short               count,
  SoundSource *       sources);


/*
 *  SoundComponentPlaySourceBuffer()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in SoundLib 3.0 and later
 */
extern ComponentResult 
SoundComponentPlaySourceBuffer(
  ComponentInstance    ti,
  SoundSource          sourceID,
  SoundParamBlockPtr   pb,
  long                 actions);



/* selectors for component calls */
enum {
    kSoundComponentInitOutputDeviceSelect      = 0x0001,
    kSoundComponentSetSourceSelect             = 0x0002,
    kSoundComponentGetSourceSelect             = 0x0003,
    kSoundComponentGetSourceDataSelect         = 0x0004,
    kSoundComponentSetOutputSelect             = 0x0005,
    kSoundComponentAddSourceSelect             = 0x0101,
    kSoundComponentRemoveSourceSelect          = 0x0102,
    kSoundComponentGetInfoSelect               = 0x0103,
    kSoundComponentSetInfoSelect               = 0x0104,
    kSoundComponentStartSourceSelect           = 0x0105,
    kSoundComponentStopSourceSelect            = 0x0106,
    kSoundComponentPauseSourceSelect           = 0x0107,
    kSoundComponentPlaySourceBufferSelect      = 0x0108
};
/*Audio Components*/
/*Volume is described as a value between 0 and 1, with 0 indicating minimum
  volume and 1 indicating maximum volume; if the device doesn't support
  software control of volume, then a value of unimpErr is returned, indicating
  that these functions are not supported by the device
*/
/*
 *  AudioGetVolume()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in SoundLib 3.0 and later
 */


/*
 *  AudioSetVolume()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in SoundLib 3.0 and later
 */


/*If the device doesn't support software control of mute, then a value of unimpErr is
returned, indicating that these functions are not supported by the device.*/
/*
 *  AudioGetMute()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in SoundLib 3.0 and later
 */


/*
 *  AudioSetMute()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in SoundLib 3.0 and later
 */


/*AudioSetToDefaults causes the associated device to reset its volume and mute values
(and perhaps other characteristics, e.g. attenuation) to "factory default" settings*/
/*
 *  AudioSetToDefaults()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in SoundLib 3.0 and later
 */


/*This routine is required; it must be implemented by all audio components*/

/*
 *  AudioGetInfo()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in SoundLib 3.0 and later
 */


/*
 *  AudioGetBass()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in SoundLib 3.0 and later
 */


/*
 *  AudioSetBass()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in SoundLib 3.0 and later
 */


/*
 *  AudioGetTreble()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in SoundLib 3.0 and later
 */


/*
 *  AudioSetTreble()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in SoundLib 3.0 and later
 */


/*
 *  AudioGetOutputDevice()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in SoundLib 3.0 and later
 */


/*This is routine is private to the AudioVision component.  It enables the watching of the mute key.*/
/*
 *  AudioMuteOnEvent()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in SoundLib 3.0 and later
 */



enum {
  kDelegatedSoundComponentSelectors = 0x0100
};



/* Sound Input Manager routines, uses _SoundDispatch */
/*
 *  SPBVersion()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern NumVersion 
SPBVersion(void);


/*
 *  SndRecord()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
SndRecord(
  ModalFilterUPP   filterProc,
  Point            corner,
  OSType           quality,
  SndListHandle *  sndHandle);


/*
 *  SndRecordToFile()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  SPBSignInDevice()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
SPBSignInDevice(
  short              deviceRefNum,
  ConstStr255Param   deviceName);


/*
 *  SPBSignOutDevice()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
SPBSignOutDevice(short deviceRefNum);


/*
 *  SPBGetIndexedDevice()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
SPBGetIndexedDevice(
  short     count,
  Str255    deviceName,
  Handle *  deviceIconHandle);


/*
 *  SPBOpenDevice()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
SPBOpenDevice(
  ConstStr255Param   deviceName,
  short              permission,
  long *             inRefNum);


/*
 *  SPBCloseDevice()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
SPBCloseDevice(long inRefNum);


/*
 *  SPBRecord()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
SPBRecord(
  SPBPtr    inParamPtr,
  Boolean   asynchFlag);


/*
 *  SPBRecordToFile()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  SPBPauseRecording()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
SPBPauseRecording(long inRefNum);


/*
 *  SPBResumeRecording()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
SPBResumeRecording(long inRefNum);


/*
 *  SPBStopRecording()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
SPBStopRecording(long inRefNum);


/*
 *  SPBGetRecordingStatus()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
SPBGetRecordingStatus(
  long             inRefNum,
  short *          recordingStatus,
  short *          meterLevel,
  unsigned long *  totalSamplesToRecord,
  unsigned long *  numberOfSamplesRecorded,
  unsigned long *  totalMsecsToRecord,
  unsigned long *  numberOfMsecsRecorded);


/*
 *  SPBGetDeviceInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
SPBGetDeviceInfo(
  long     inRefNum,
  OSType   infoType,
  void *   infoData);


/*
 *  SPBSetDeviceInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
SPBSetDeviceInfo(
  long     inRefNum,
  OSType   infoType,
  void *   infoData);


/*
 *  SPBMillisecondsToBytes()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
SPBMillisecondsToBytes(
  long    inRefNum,
  long *  milliseconds);


/*
 *  SPBBytesToMilliseconds()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
SPBBytesToMilliseconds(
  long    inRefNum,
  long *  byteCount);


/*
 *  SetupSndHeader()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
SetupSndHeader(
  SndListHandle   sndHandle,
  short           numChannels,
  UnsignedFixed   sampleRate,
  short           sampleSize,
  OSType          compressionType,
  short           baseNote,
  unsigned long   numBytes,
  short *         headerLen);


/*
 *  SetupAIFFHeader()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
SetupAIFFHeader(
  short           fRefNum,
  short           numChannels,
  UnsignedFixed   sampleRate,
  short           sampleSize,
  OSType          compressionType,
  unsigned long   numBytes,
  unsigned long   numFrames);


/* Sound Input Manager 1.1 and later calls, uses _SoundDispatch */
/*
 *  ParseAIFFHeader()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in SoundLib 3.0 and later
 */
extern OSErr 
ParseAIFFHeader(
  short                 fRefNum,
  SoundComponentData *  sndInfo,
  unsigned long *       numFrames,
  unsigned long *       dataOffset);


/*
 *  ParseSndHeader()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in SoundLib 3.0 and later
 */
extern OSErr 
ParseSndHeader(
  SndListHandle         sndHandle,
  SoundComponentData *  sndInfo,
  unsigned long *       numFrames,
  unsigned long *       dataOffset);






#if TARGET_API_MAC_CARBON
/*  Only to be used if you are writing a sound input component; this */
/*  is the param block for a read request from the SoundMgr to the   */
/*  sound input component.  Not to be confused with the SPB struct   */
/*  above, which is the param block for a read request from an app   */
/*  to the SoundMgr.                                                 */
typedef struct SndInputCmpParam         SndInputCmpParam;
typedef SndInputCmpParam *              SndInputCmpParamPtr;
typedef CALLBACK_API( void , SICCompletionProcPtr )(SndInputCmpParamPtr SICParmPtr);
struct SndInputCmpParam {
  SICCompletionProcPtr  ioCompletion;         /* completion routine [pointer]*/
  SIInterruptProcPtr  ioInterrupt;            /* interrupt routine [pointer]*/
  OSErr               ioResult;               /* I/O result code [word]*/
  short               pad;
  unsigned long       ioReqCount;
  unsigned long       ioActCount;
  Ptr                 ioBuffer;
  Ptr                 ioMisc;
};

/*
 *  SndInputReadAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern ComponentResult 
SndInputReadAsync(
  ComponentInstance     self,
  SndInputCmpParamPtr   SICParmPtr);


/*
 *  SndInputReadSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern ComponentResult 
SndInputReadSync(
  ComponentInstance     self,
  SndInputCmpParamPtr   SICParmPtr);


/*
 *  SndInputPauseRecording()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern ComponentResult 
SndInputPauseRecording(ComponentInstance self);


/*
 *  SndInputResumeRecording()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern ComponentResult 
SndInputResumeRecording(ComponentInstance self);


/*
 *  SndInputStopRecording()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern ComponentResult 
SndInputStopRecording(ComponentInstance self);


/*
 *  SndInputGetStatus()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern ComponentResult 
SndInputGetStatus(
  ComponentInstance   self,
  short *             recordingStatus,
  unsigned long *     totalSamplesToRecord,
  unsigned long *     numberOfSamplesRecorded);


/*
 *  SndInputGetDeviceInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern ComponentResult 
SndInputGetDeviceInfo(
  ComponentInstance   self,
  OSType              infoType,
  void *              infoData);


/*
 *  SndInputSetDeviceInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern ComponentResult 
SndInputSetDeviceInfo(
  ComponentInstance   self,
  OSType              infoType,
  void *              infoData);


/*
 *  SndInputInitHardware()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern ComponentResult 
SndInputInitHardware(ComponentInstance self);



/* selectors for component calls */
enum {
    kSndInputReadAsyncSelect                   = 0x0001,
    kSndInputReadSyncSelect                    = 0x0002,
    kSndInputPauseRecordingSelect              = 0x0003,
    kSndInputResumeRecordingSelect             = 0x0004,
    kSndInputStopRecordingSelect               = 0x0005,
    kSndInputGetStatusSelect                   = 0x0006,
    kSndInputGetDeviceInfoSelect               = 0x0007,
    kSndInputSetDeviceInfoSelect               = 0x0008,
    kSndInputInitHardwareSelect                = 0x0009
};
#endif  /* TARGET_API_MAC_CARBON */



#if PRAGMA_STRUCT_ALIGN
    #pragma options align=reset
#elif PRAGMA_STRUCT_PACKPUSH
    #pragma pack(pop)
#elif PRAGMA_STRUCT_PACK
    #pragma pack()
#endif

#ifdef __cplusplus
}
#endif

#endif /* __SOUND__ */

