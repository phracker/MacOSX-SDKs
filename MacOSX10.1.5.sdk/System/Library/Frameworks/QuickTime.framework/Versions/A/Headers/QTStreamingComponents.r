/*
     File:       QTStreamingComponents.r
 
     Contains:   QuickTime Interfaces.
 
     Version:    QuickTime-142~1
 
     Copyright:  © 1990-2001 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

#ifndef __QTSTREAMINGCOMPONENTS_R__
#define __QTSTREAMINGCOMPONENTS_R__

#ifndef __CONDITIONALMACROS_R__
#include <CarbonCore/ConditionalMacros.r>
#endif

#define kQTSSourcerType 				'srcr'
#define kQTSSGChannelSourcerType 		'sgch'
#define kQTSMovieTrackSourcerType 		'trak'
#define kQTSPushDataSourcerType 		'push'

#define kRTPPayloadSpeedTag 			'sped'				/*  0-255, 255 is fastest */
#define kRTPPayloadLossRecoveryTag 		'loss'				/*  0-255, 0 can't handle any loss, 128 can handle 50% packet loss */

#define kRTPPayloadTypeStaticFlag 		0x00000001
#define kRTPPayloadTypeDynamicFlag 		0x00000002

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

#define kMediaPacketizerCanPackEditRate  0x01
#define kMediaPacketizerCanPackLayer 	0x02
#define kMediaPacketizerCanPackVolume 	0x04
#define kMediaPacketizerCanPackBalance 	0x08
#define kMediaPacketizerCanPackGraphicsMode  0x10
#define kMediaPacketizerCanPackEmptyEdit  0x20


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

