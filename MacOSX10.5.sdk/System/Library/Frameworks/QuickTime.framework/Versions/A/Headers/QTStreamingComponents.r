/*
     File:       QTStreamingComponents.r
 
     Contains:   QuickTime Interfaces.
 
     Version:    QuickTime 7.2.1
 
     Copyright:  © 1990-2006 by Apple Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

#ifndef __QTSTREAMINGCOMPONENTS_R__
#define __QTSTREAMINGCOMPONENTS_R__

#ifndef __CORESERVICES_R__
#include <CoreServices/CoreServices.r>
#endif

#define kQTSSourcerType 				'srcr'
#define kQTSSGChannelSourcerType 		'sgch'
#define kQTSMovieTrackSourcerType 		'trak'
#define kQTSPushDataSourcerType 		'push'

#define kRTPPayload_PCMU 				0					/*  8kHz PCM mu-law mono  */
#define kRTPPayload_1016 				1					/*  8kHz CELP (Fed Std 1016) mono  */
#define kRTPPayload_G721 				2					/*  8kHz G.721 ADPCM mono  */
#define kRTPPayload_GSM 				3					/*  8kHz GSM mono  */
#define kRTPPayload_G723 				4					/*  8kHz G.723 ADPCM mono  */
#define kRTPPayload_DVI_8 				5					/*  8kHz Intel DVI ADPCM mono  */
#define kRTPPayload_DVI_16 				6					/*  16kHz Intel DVI ADPCM mono  */
#define kRTPPayload_LPC 				7					/*  8kHz LPC  */
#define kRTPPayload_PCMA 				8					/*  8kHz PCM a-law mono  */
#define kRTPPayload_L16_44_2 			10					/*  44.1kHz 16-bit linear stereo  */
#define kRTPPayload_L16_44_1 			11					/*  44.1kHz 16-bit linear mono  */
#define kRTPPayload_PureVoice 			12					/*  8kHz PureVoice mono (QCELP)  */
#define kRTPPayload_MPEGAUDIO 			14					/*  MPEG I and II audio  */
#define kRTPPayload_DVI_11 				16					/*  11kHz Intel DVI ADPCM mono  */
#define kRTPPayload_DVI_22 				17					/*  22kHz Intel DVI ADPCM mono  */

#define kRTPPayload_CELLB 				25					/*  Sun CellB  */
#define kRTPPayload_JPEG 				26					/*  JPEG  */
#define kRTPPayload_CUSEEME 			27					/*  Cornell CU-SeeMe  */
#define kRTPPayload_NV 					28					/*  Xerox PARC nv  */
#define kRTPPayload_PICWIN 				29					/*  BBN Picture Window  */
#define kRTPPayload_CPV 				30					/*  Bolter CPV  */
#define kRTPPayload_H261 				31					/*  CCITT H.261  */
#define kRTPPayload_MPEGVIDEO 			32					/*  MPEG I and II video  */
#define kRTPPayload_H263 				34					/*  CCITT H.263  */

#define kRTPPayload_MPEG2T 				33					/*  MPEG 2 Transport  */
#define kRTPPayload_FirstDynamic 		96
#define kRTPPayload_LastDynamic 		127
#define kRTPPayload_Unknown 			0xFF

#define kRTPPayloadSpeedTag 			'sped'				/*  0-255, 255 is fastest */
#define kRTPPayloadLossRecoveryTag 		'loss'				/*  0-255, 0 can't handle any loss, 128 can handle 50% packet loss */
#define kRTPPayloadConformanceTag 		'conf'				/*  more than one of these can be present */

#define kRTPPayloadTypeStaticFlag 		0x00000001
#define kRTPPayloadTypeDynamicFlag 		0x00000002

#define kRTPReassemblerType 			'rtpr'
#define kRTPBaseReassemblerType 		'gnrc'
#define kRTP261ReassemblerType 			'h261'
#define kRTP263ReassemblerType 			'h263'
#define kRTP263PlusReassemblerType 		'263+'
#define kRTPAudioReassemblerType 		'soun'
#define kRTPQTReassemblerType 			'qtim'
#define kRTPPureVoiceReassemblerType 	'Qclp'
#define kRTPJPEGReassemblerType 		'jpeg'
#define kRTPQDesign2ReassemblerType 	'QDM2'
#define kRTPSorensonReassemblerType 	'SVQ1'
#define kRTPMP3ReassemblerType 			'mp3 '
#define kRTPMPEG4AudioReassemblerType 	'mp4a'
#define kRTPMPEG4VideoReassemblerType 	'mp4v'
#define kRTPAMRReassemblerType 			'amr '

#define kRTPReassemblerInfoResType 		'rsmi'

type 'rsmi' {
 array infoArray {
      align long;
        longint = $$CountOf(characteristicArray);       /* Array size           */
     array characteristicArray {
            hex longint tag;
           hex longint value;
     };

        hex longint payloadFlags;
      byte        payloadID;              /* if static payload */
        byte = 0;
      byte = 0;
      byte = 0;
      cstring;
   };
};

#define kRTPMediaPacketizerType 		'rtpm'
#define kRTPBaseMediaPacketizerType 	'gnrc'
#define kRTP261MediaPacketizerType 		'h261'
#define kRTP263PlusMediaPacketizerType 	'263+'
#define kRTPAudioMediaPacketizerType 	'soun'
#define kRTPQTMediaPacketizerType 		'qtim'
#define kRTPPureVoiceMediaPacketizerType  'Qclp'
#define kRTPJPEGMediaPacketizerType 	'jpeg'
#define kRTPQDesign2MediaPacketizerType  'QDM2'
#define kRTPSorensonMediaPacketizerType  'SVQ1'
#define kRTPMP3MediaPacketizerType 		'mp3 '
#define kRTPMPEG4AudioMediaPacketizerType  'mp4a'
#define kRTPMPEG4VideoMediaPacketizerType  'mp4v'
#define kRTPAMRMediaPacketizerType 		'amr '

#define kMediaPacketizerCanPackEditRate  0x01
#define kMediaPacketizerCanPackLayer 	0x02
#define kMediaPacketizerCanPackVolume 	0x04
#define kMediaPacketizerCanPackBalance 	0x08
#define kMediaPacketizerCanPackGraphicsMode  0x10
#define kMediaPacketizerCanPackEmptyEdit  0x20

#define kRTPMediaPacketizerInfoRezType 	'pcki'

#define canPackIdentityMatrixType          0x00        /* matrix is identity */
#define canPackTranslateMatrixType         0x01        /* matrix translates */
#define canPackScaleMatrixType              0x02        /* matrix scales */
#define canPackScaleTranslateMatrixType     0x03        /* matrix scales and translates */
#define canPackLinearMatrixType              0x04        /* matrix is general 2 x 2 */
#define canPackLinearTranslateMatrixType  0x05        /* matrix is general 2 x 2 and translates */
#define canPackPerspectiveMatrixType       0x06        /* matrix is general 3 x 3 */


type 'pcki' {
 array infoArray {
      align long;
        hex longint mediaType;
     hex longint dataFormat;
        hex longint vendor;
        hex longint capabilityFlags;
       byte        canPackMatrixType;
     byte = 0;
      byte = 0;
      byte = 0;
      longint = $$CountOf(characteristicArray);                   /* Array size           */
     array characteristicArray {
            hex longint tag;
           hex longint value;
     };
     hex longint payloadFlags;
      byte        payloadID;              /* if static payload */
        byte = 0;
      byte = 0;
      byte = 0;
      cstring;
   };
};


#endif /* __QTSTREAMINGCOMPONENTS_R__ */

