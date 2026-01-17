/*
     File:       ImageCompression.r
 
     Contains:   QuickTime Image Compression Interfaces.
 
     Version:    QuickTime-142~1
 
     Copyright:  © 1990-2001 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

#ifndef __IMAGECOMPRESSION_R__
#define __IMAGECOMPRESSION_R__

#ifndef __CONDITIONALMACROS_R__
#include <CarbonCore/ConditionalMacros.r>
#endif

#define codecInfoDoes1 					0x00000001			/*  codec can work with 1-bit pixels  */
#define codecInfoDoes2 					0x00000002			/*  codec can work with 2-bit pixels  */
#define codecInfoDoes4 					0x00000004			/*  codec can work with 4-bit pixels  */
#define codecInfoDoes8 					0x00000008			/*  codec can work with 8-bit pixels  */
#define codecInfoDoes16 				0x00000010			/*  codec can work with 16-bit pixels  */
#define codecInfoDoes32 				0x00000020			/*  codec can work with 32-bit pixels  */
#define codecInfoDoesDither 			0x00000040			/*  codec can do ditherMode  */
#define codecInfoDoesStretch 			0x00000080			/*  codec can stretch to arbitrary sizes  */
#define codecInfoDoesShrink 			0x00000100			/*  codec can shrink to arbitrary sizes  */
#define codecInfoDoesMask 				0x00000200			/*  codec can mask to clipping regions  */
#define codecInfoDoesTemporal 			0x00000400			/*  codec can handle temporal redundancy  */
#define codecInfoDoesDouble 			0x00000800			/*  codec can stretch to double size exactly  */
#define codecInfoDoesQuad 				0x00001000			/*  codec can stretch to quadruple size exactly  */
#define codecInfoDoesHalf 				0x00002000			/*  codec can shrink to half size  */
#define codecInfoDoesQuarter 			0x00004000			/*  codec can shrink to quarter size  */
#define codecInfoDoesRotate 			0x00008000			/*  codec can rotate on decompress  */
#define codecInfoDoesHorizFlip 			0x00010000			/*  codec can flip horizontally on decompress  */
#define codecInfoDoesVertFlip 			0x00020000			/*  codec can flip vertically on decompress  */
#define codecInfoHasEffectParameterList  0x00040000			/*  codec implements get effects parameter list call, once was codecInfoDoesSkew  */
#define codecInfoDoesBlend 				0x00080000			/*  codec can blend on decompress  */
#define codecInfoDoesWarp 				0x00100000			/*  codec can warp arbitrarily on decompress  */
#define codecInfoDoesRecompress 		0x00200000			/*  codec can recompress image without accumulating errors  */
#define codecInfoDoesSpool 				0x00400000			/*  codec can spool image data  */
#define codecInfoDoesRateConstrain 		0x00800000			/*  codec can data rate constrain  */

#define codecInfoDepth1 				0x00000001			/*  compressed data at 1 bpp depth available  */
#define codecInfoDepth2 				0x00000002			/*  compressed data at 2 bpp depth available  */
#define codecInfoDepth4 				0x00000004			/*  compressed data at 4 bpp depth available  */
#define codecInfoDepth8 				0x00000008			/*  compressed data at 8 bpp depth available  */
#define codecInfoDepth16 				0x00000010			/*  compressed data at 16 bpp depth available  */
#define codecInfoDepth32 				0x00000020			/*  compressed data at 32 bpp depth available  */
#define codecInfoDepth24 				0x00000040			/*  compressed data at 24 bpp depth available  */
#define codecInfoDepth33 				0x00000080			/*  compressed data at 1 bpp monochrome depth  available  */
#define codecInfoDepth34 				0x00000100			/*  compressed data at 2 bpp grayscale depth available  */
#define codecInfoDepth36 				0x00000200			/*  compressed data at 4 bpp grayscale depth available  */
#define codecInfoDepth40 				0x00000400			/*  compressed data at 8 bpp grayscale depth available  */
#define codecInfoStoresClut 			0x00000800			/*  compressed data can have custom cluts  */
#define codecInfoDoesLossless 			0x00001000			/*  compressed data can be stored in lossless format  */
#define codecInfoSequenceSensitive 		0x00002000			/*  compressed data is sensitive to out of sequence decoding  */

#define codecFlagUseImageBuffer 		0x00000001			/*  decompress */
#define codecFlagUseScreenBuffer 		0x00000002			/*  decompress */
#define codecFlagUpdatePrevious 		0x00000004			/*  compress */
#define codecFlagNoScreenUpdate 		0x00000008			/*  decompress */
#define codecFlagWasCompressed 			0x00000010			/*  compress */
#define codecFlagDontOffscreen 			0x00000020			/*  decompress */
#define codecFlagUpdatePreviousComp 	0x00000040			/*  compress */
#define codecFlagForceKeyFrame 			0x00000080			/*  compress */
#define codecFlagOnlyScreenUpdate 		0x00000100			/*  decompress */
#define codecFlagLiveGrab 				0x00000200			/*  compress */
#define codecFlagDiffFrame 				0x00000200			/*  decompress */
#define codecFlagDontUseNewImageBuffer 	0x00000400			/*  decompress */
#define codecFlagInterlaceUpdate 		0x00000800			/*  decompress */
#define codecFlagCatchUpDiff 			0x00001000			/*  decompress */
#define codecFlagSupportDisable 		0x00002000			/*  decompress */
#define codecFlagReenable 				0x00004000			/*  decompress */

#define codecFlagOutUpdateOnNextIdle 	0x00000200
#define codecFlagOutUpdateOnDataSourceChange  0x00000400
#define codecFlagSequenceSensitive 		0x00000800
#define codecFlagOutUpdateOnTimeChange 	0x00001000
#define codecFlagImageBufferNotSourceImage  0x00002000
#define codecFlagUsedNewImageBuffer 	0x00004000
#define codecFlagUsedImageBuffer 		0x00008000

#define compressorComponentType 		'imco'				/*  the type for "Components" which compress images  */
#define decompressorComponentType 		'imdc'				/*  the type for "Components" which decompress images  */

#define graphicsImporterUsesImageDecompressor  0x00800000
#define kGraphicsExportGroup 			'expo'
#define kGraphicsExportFileType 		'ftyp'
#define kGraphicsExportMIMEType 		'mime'
#define kGraphicsExportExtension 		'ext '
#define kGraphicsExportDescription 		'desc'

#define graphicsExporterIsBaseExporter 	0x00000001
#define graphicsExporterCanTranscode 	0x00000002
#define graphicsExporterUsesImageCompressor  0x00000004


#endif /* __IMAGECOMPRESSION_R__ */

