/*
     File:       Sound.r
 
     Contains:   Sound Manager Interfaces.
 
     Version:    CarbonSound-103.1~889
 
     Copyright:  © 1986-2006 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

#ifndef __SOUND_R__
#define __SOUND_R__

#ifndef __CORESERVICES_R__
#include <CoreServices/CoreServices.r>
#endif

#define kInvalidSource 					0xFFFFFFFF			/* this source may be returned from GetInfo if no other source is the monitored source */
#define kNoSource 						'none'				/* no source selection */
#define kCDSource 						'cd  '				/* internal CD player input */
#define kExtMicSource 					'emic'				/* external mic input */
#define kSoundInSource 					'sinj'				/* sound input jack */
#define kRCAInSource 					'irca'				/* RCA jack input */
#define kTVFMTunerSource 				'tvfm'
#define kDAVInSource 					'idav'				/* DAV analog input */
#define kIntMicSource 					'imic'				/* internal mic input */
#define kMediaBaySource 				'mbay'				/* media bay input */
#define kModemSource 					'modm'				/* modem input (internal modem on desktops, PCI input on PowerBooks) */
#define kPCCardSource 					'pcm '				/* PC Card pwm input */
#define kZoomVideoSource 				'zvpc'				/* zoom video input */
#define kDVDSource 						'dvda'				/*  DVD audio input */
#define kMicrophoneArray 				'mica'				/*  microphone array */

#define kNoSoundComponentType 			'****'
#define kSoundComponentType 			'sift'				/* component type */
#define kSoundComponentPPCType 			'nift'				/* component type for PowerPC code */
#define kRate8SubType 					'ratb'				/* 8-bit rate converter */
#define kRate16SubType 					'ratw'				/* 16-bit rate converter */
#define kConverterSubType 				'conv'				/* sample format converter */
#define kSndSourceSubType 				'sour'				/* generic source component */
#define kMixerType 						'mixr'
#define kMixer8SubType 					'mixb'				/* 8-bit mixer */
#define kMixer16SubType 				'mixw'				/* 16-bit mixer */
#define kSoundInputDeviceType 			'sinp'				/* sound input component */
#define kWaveInSubType 					'wavi'				/* Windows waveIn */
#define kWaveInSnifferSubType 			'wisn'				/* Windows waveIn sniffer */
#define kSoundOutputDeviceType 			'sdev'				/* sound output component */
#define kClassicSubType 				'clas'				/* classic hardware, i.e. Mac Plus */
#define kASCSubType 					'asc '				/* Apple Sound Chip device */
#define kDSPSubType 					'dsp '				/* DSP device */
#define kAwacsSubType 					'awac'				/* Another of Will's Audio Chips device */
#define kGCAwacsSubType 				'awgc'				/* Awacs audio with Grand Central DMA */
#define kSingerSubType 					'sing'				/* Singer (via Whitney) based sound */
#define kSinger2SubType 				'sng2'				/* Singer 2 (via Whitney) for Acme */
#define kWhitSubType 					'whit'				/* Whit sound component for PrimeTime 3 */
#define kSoundBlasterSubType 			'sbls'				/* Sound Blaster for CHRP */
#define kWaveOutSubType 				'wavo'				/* Windows waveOut */
#define kWaveOutSnifferSubType 			'wosn'				/* Windows waveOut sniffer */
#define kDirectSoundSubType 			'dsnd'				/* Windows DirectSound */
#define kDirectSoundSnifferSubType 		'dssn'				/* Windows DirectSound sniffer */
#define kUNIXsdevSubType 				'un1x'				/* UNIX base sdev */
#define kUSBSubType 					'usb '				/* USB device */
#define kBlueBoxSubType 				'bsnd'				/* Blue Box sound component */
#define kHALCustomComponentSubType 		'halx'				/* Registered by the HAL output component ('hal!') for each HAL output device */
#define kSoundCompressor 				'scom'
#define kSoundDecompressor 				'sdec'
#define kAudioComponentType 			'adio'				/* Audio components and sub-types */
#define kAwacsPhoneSubType 				'hphn'
#define kAudioVisionSpeakerSubType 		'telc'
#define kAudioVisionHeadphoneSubType 	'telh'
#define kPhilipsFaderSubType 			'tvav'
#define kSGSToneSubType 				'sgs0'
#define kSoundEffectsType 				'snfx'				/* sound effects type */
#define kEqualizerSubType 				'eqal'				/* frequency equalizer */
#define kSSpLocalizationSubType 		'snd3'

#define kSoundNotCompressed 			'NONE'				/* sound is not compressed */
#define k8BitOffsetBinaryFormat 		'raw '				/* 8-bit offset binary */
#define k16BitBigEndianFormat 			'twos'				/* 16-bit big endian */
#define k16BitLittleEndianFormat 		'sowt'				/* 16-bit little endian */
#define kFloat32Format 					'fl32'				/* 32-bit floating point */
#define kFloat64Format 					'fl64'				/* 64-bit floating point */
#define k24BitFormat 					'in24'				/* 24-bit integer */
#define k32BitFormat 					'in32'				/* 32-bit integer */
#define k32BitLittleEndianFormat 		'23ni'				/* 32-bit little endian integer  */
#define kMACE3Compression 				'MAC3'				/* MACE 3:1 */
#define kMACE6Compression 				'MAC6'				/* MACE 6:1 */
#define kCDXA4Compression 				'cdx4'				/* CD/XA 4:1 */
#define kCDXA2Compression 				'cdx2'				/* CD/XA 2:1 */
#define kIMACompression 				'ima4'				/* IMA 4:1 */
#define kULawCompression 				'ulaw'				/* µLaw 2:1 */
#define kALawCompression 				'alaw'				/* aLaw 2:1 */
#define kMicrosoftADPCMFormat 			0x6D730002			/* Microsoft ADPCM - ACM code 2 */
#define kDVIIntelIMAFormat 				0x6D730011			/* DVI/Intel IMA ADPCM - ACM code 17 */
#define kMicrosoftGSMCompression 		0x6D730031			/* Microsoft GSM 6.10 - ACM code 49 */
#define kDVAudioFormat 					'dvca'				/* DV Audio */
#define kQDesignCompression 			'QDMC'				/* QDesign music */
#define kQDesign2Compression 			'QDM2'				/* QDesign2 music */
#define kQUALCOMMCompression 			'Qclp'				/* QUALCOMM PureVoice */
#define kOffsetBinary 					'raw '				/* for compatibility */
#define kTwosComplement 				'twos'				/* for compatibility */
#define kLittleEndianFormat 			'sowt'				/* for compatibility */
#define kMPEGLayer3Format 				0x6D730055			/* MPEG Layer 3, CBR only (pre QT4.1) */
#define kFullMPEGLay3Format 			'.mp3'				/* MPEG Layer 3, CBR & VBR (QT4.1 and later) */
#define kVariableDurationDVAudioFormat 	'vdva'				/* Variable Duration DV Audio */
#define kMPEG4AudioFormat 				'mp4a'

#define k8BitRawIn 						0x01				/* data description */
#define k8BitTwosIn 					0x02
#define k16BitIn 						0x04
#define kStereoIn 						0x08
#define k8BitRawOut 					0x0100
#define k8BitTwosOut 					0x0200
#define k16BitOut 						0x0400
#define kStereoOut 						0x0800
#define kReverse 						0x00010000			/*   function description */
#define kRateConvert 					0x00020000
#define kCreateSoundSource 				0x00040000
#define kVMAwareness 					0x00200000			/*  component will hold its memory */
#define kHighQuality 					0x00400000			/*   performance description */
#define kNonRealTime 					0x00800000

#define kSoundCodecInfoFixedCompression  0x00000001			/*  has fixed compression format */
#define kSoundCodecInfoVariableCompression  0x00000002		/*  has variable compression format */
#define kSoundCodecInfoHasRestrictedInputRates  0x00000004	/*  compressor has restricted set of input sample rates */
#define kSoundCodecInfoCanChangeOutputRate  0x00000008		/*  compressor may output a different sample rate than it receives */
#define kSoundCodecInfoRequiresExternalFraming  0x00000010	/*  format requires external framing information during decode/encode */
#define kSoundCodecInfoVariableDuration  0x00000020			/*  audio packets can vary in duration */


/*----------------------------snd  ¥ Sound----------------------------------------------*/
type 'snd ' {
        switch {
            case FormatOne:
                key unsigned integer = $0001;
                unsigned integer = $$CountOf(Synthesizers);
                wide array Synthesizers {
                    /* Resource ID of synthesizer/modifer */
                    integer     squareWaveSynth     = $0001,
                                waveTableSynth      = $0003,
                                sampledSynth        = $0005;
                    longint;                                    /* init parameter       */
                };

            case FormatTwo:
                key unsigned integer = $0002;
                integer     free = 0, keepInMemory = 256+1;     /* Space for refe count */
        };
        unsigned integer = $$CountOf(SoundCmnds);
        wide array SoundCmnds {
            boolean     noData, hasData;
            switch {
                case nullCmd:
                    key bitstring[15] = 0;
                    fill word;                                  /* Param 1 = nil        */
                    fill long;                                  /* Param 2 = nil        */
                case quietCmd:
                    key bitstring[15] = 3;
                    fill word;                                  /* Param 1 = nil        */
                    fill long;                                  /* Param 2 = nil        */
                case flushCmd:
                    key bitstring[15] = 4;
                    fill word;                                  /* Param 1 = nil        */
                    fill long;                                  /* Param 2 = nil        */
                case waitCmd:
                    key bitstring[15] = 10;
                    integer     oneSecond = 2000;               /* Duration             */
                    fill long;                                  /* Param 2 = nil        */
                case pauseCmd:
                    key bitstring[15] = 11;
                    fill word;                                  /* Param 1 = nil        */
                    fill long;                                  /* Param 2 = nil        */
                case resumeCmd:
                    key bitstring[15] = 12;
                    fill word;                                  /* Param 1 = nil        */
                    fill long;                                  /* Param 2 = nil        */
                case callBackCmd:
                    key bitstring[15] = 13;
                    integer;                                    /* User-defined         */
                    longint;                                    /* User-defined         */
                case syncCmd:
                    key bitstring[15] = 14;
                    integer;                                    /* Count                */
                    longint;                                    /* Identifier           */
                case emptyCmd:
                    key bitstring[15] = 15;
                    fill word;                                  /* Param 1 = nil        */
                    fill long;                                  /* Param 2 = nil        */
                case freqDurationCmd:
                    key bitstring[15] = 40;
                    integer     oneSecond = 2000;               /* Duration             */
                    longint;                                    /* frequency            */
                case restCmd:
                    key bitstring[15] = 41;
                    integer     oneSecond = 2000;               /* Duration             */
                    fill long;                                  /* Param 2 = nil        */
                case freqCmd:
                    key bitstring[15] = 42;
                    fill word;                                  /* Param 1 = nil        */
                    longint;                                    /* Frequency            */
                case ampCmd:
                    key bitstring[15] = 43;
                    integer;                                    /* Amplitude            */
                    fill long;                                  /* Param 2              */
                case timbreCmd:
                    key bitstring[15] = 44;
                    integer     sineWave, squareWave = 255;     /* Timbre               */
                    fill long;                                  /* Param 2              */
                case waveTableCmd:
                    key bitstring[15] = 60;
                    unsigned integer;                           /* Length               */
                    longint;                                    /* Pointer to table     */
                case phaseCmd:
                    key bitstring[15] = 61;
                    integer;                                    /* Shift                */
                    longint;                                    /* chanPtr              */
                case soundCmd:
                    key bitstring[15] = 80;
                    fill word;                                  /* Param 1 = nil        */
                    longint;                                    /* Pointer to sound     */
                case bufferCmd:
                    key bitstring[15] = 81;
                    fill word;                                  /* Param 1 = nil        */
                    longint;                                    /* Pointer to buffer    */
                case rateCmd:
                    key bitstring[15] = 82;
                    fill word;                                  /* Param 1 = nil        */
                    longint;                                    /* Rate                 */
            };
        };
        array DataTables {
    DataTable:
            fill long;                                          /* Pointer to data      */
    SampleCnt:
            unsigned longint;                                   /* # of sound samples   */
            unsigned hex longint
                    Rate22K = $56EE8BA3;                        /* Sampling rate        */
            unsigned longint;                                   /* Start of loop        */
            unsigned longint;                                   /* End of loop          */
            hex byte;                                           /* encode (header type) */
            hex byte;                                           /* baseFrequency        */
            hex string [$$Long(SampleCnt[$$ArrayIndex(DataTables)])];
        };
};

/*----------------------------snfo ¥ Sound Codec Info   --------------------------------*/
type 'snfo' {
    longint = 0;
    longint;    // feature flags
};


#endif /* __SOUND_R__ */

