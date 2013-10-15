/*
     File:       ImageCompression.r
 
     Contains:   QuickTime Image Compression Interfaces.
 
     Version:    QuickTime 7.2.1
 
     Copyright:  © 1990-2006 by Apple Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

#ifndef __IMAGECOMPRESSION_R__
#define __IMAGECOMPRESSION_R__

#ifndef __CORESERVICES_R__
#include <CoreServices/CoreServices.r>
#endif

#define kRawCodecType 					'raw '
#define kCinepakCodecType 				'cvid'
#define kGraphicsCodecType 				'smc '
#define kAnimationCodecType 			'rle '
#define kVideoCodecType 				'rpza'
#define kComponentVideoCodecType 		'yuv2'
#define kJPEGCodecType 					'jpeg'
#define kMotionJPEGACodecType 			'mjpa'
#define kMotionJPEGBCodecType 			'mjpb'
#define kSGICodecType 					'.SGI'
#define kPlanarRGBCodecType 			'8BPS'
#define kMacPaintCodecType 				'PNTG'
#define kGIFCodecType 					'gif '
#define kPhotoCDCodecType 				'kpcd'
#define kQuickDrawGXCodecType 			'qdgx'
#define kAVRJPEGCodecType 				'avr '
#define kOpenDMLJPEGCodecType 			'dmb1'
#define kBMPCodecType 					'WRLE'
#define kWindowsRawCodecType 			'WRAW'
#define kVectorCodecType 				'path'
#define kQuickDrawCodecType 			'qdrw'
#define kWaterRippleCodecType 			'ripl'
#define kFireCodecType 					'fire'
#define kCloudCodecType 				'clou'
#define kH261CodecType 					'h261'
#define kH263CodecType 					'h263'
#define kDVCNTSCCodecType 				'dvc '				/*  DV - NTSC and DVCPRO NTSC (available in QuickTime 6.0 or later) */
															/*  NOTE: kDVCProNTSCCodecType is deprecated.   */
															/*  Use kDVCNTSCCodecType instead -- as far as the codecs are concerned,  */
															/*  the two data formats are identical. */
#define kDVCPALCodecType 				'dvcp'
#define kDVCProPALCodecType 			'dvpp'				/*  available in QuickTime 6.0 or later */
#define kDVCPro50NTSCCodecType 			'dv5n'
#define kDVCPro50PALCodecType 			'dv5p'
#define kDVCPro100NTSCCodecType 		'dv1n'
#define kDVCPro100PALCodecType 			'dv1p'
#define kDVCPROHD720pCodecType 			'dvhp'
#define kDVCPROHD1080i60CodecType 		'dvh6'
#define kDVCPROHD1080i50CodecType 		'dvh5'
#define kBaseCodecType 					'base'
#define kFLCCodecType 					'flic'
#define kTargaCodecType 				'tga '
#define kPNGCodecType 					'png '
#define kTIFFCodecType 					'tiff'				/*  NOTE: despite what might seem obvious from the two constants */
															/*  below and their names, they really are correct. 'yuvu' really  */
															/*  does mean signed, and 'yuvs' really does mean unsigned. Really.  */
#define kComponentVideoSigned 			'yuvu'
#define kComponentVideoUnsigned 		'yuvs'
#define kCMYKCodecType 					'cmyk'
#define kMicrosoftVideo1CodecType 		'msvc'
#define kSorensonCodecType 				'SVQ1'
#define kSorenson3CodecType 			'SVQ3'				/*  available in QuickTime 5 and later */
#define kIndeo4CodecType 				'IV41'
#define kMPEG4VisualCodecType 			'mp4v'
#define k64ARGBCodecType 				'b64a'
#define k48RGBCodecType 				'b48r'
#define k32AlphaGrayCodecType 			'b32a'
#define k16GrayCodecType 				'b16g'
#define kMpegYUV420CodecType 			'myuv'
#define kYUV420CodecType 				'y420'
#define kSorensonYUV9CodecType 			'syv9'
#define k422YpCbCr8CodecType 			'2vuy'				/*  Component Y'CbCr 8-bit 4:2:2   */
#define k444YpCbCr8CodecType 			'v308'				/*  Component Y'CbCr 8-bit 4:4:4   */
#define k4444YpCbCrA8CodecType 			'v408'				/*  Component Y'CbCrA 8-bit 4:4:4:4  */
#define k422YpCbCr16CodecType 			'v216'				/*  Component Y'CbCr 10,12,14,16-bit 4:2:2 */
#define k422YpCbCr10CodecType 			'v210'				/*  Component Y'CbCr 10-bit 4:2:2  */
#define k444YpCbCr10CodecType 			'v410'				/*  Component Y'CbCr 10-bit 4:4:4  */
#define k4444YpCbCrA8RCodecType 		'r408'				/*  Component Y'CbCrA 8-bit 4:4:4:4, rendering format. full range alpha, zero biased yuv */
#define kJPEG2000CodecType 				'mjp2'
#define kPixletCodecType 				'pxlt'
#define kH264CodecType 					'avc1'

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
#define codecInfoDoesReorder 			0x00080000			/*  codec can rearrange frames during compression  */
#define codecInfoDoesWarp 				0x00100000			/*  codec can warp arbitrarily on decompress  */
#define codecInfoDoesMultiPass 			0x00100000			/*  codec can perform multi-pass compression  */
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

#ifndef __QTUUID__
#define __QTUUID__ 1
#endif  /* !defined(__QTUUID__) */

#define GraphicsImporterComponentType 	'grip'
#define graphicsImporterIsBaseImporter 	0x00000001
#define graphicsImporterCanValidateFile  0x00000200
#define graphicsImporterSubTypeIsFileExtension  0x00001000
#define graphicsImporterHasMIMEList 	0x00004000
#define graphicsImporterUsesImageDecompressor  0x00800000

#define kGraphicsExportGroup 			'expo'
#define kGraphicsExportFileType 		'ftyp'
#define kGraphicsExportMIMEType 		'mime'
#define kGraphicsExportExtension 		'ext '
#define kGraphicsExportDescription 		'desc'

#define GraphicsExporterComponentType 	'grex'
#define kBaseGraphicsExporterSubType 	'base'

#define graphicsExporterIsBaseExporter 	0x00000001
#define graphicsExporterCanTranscode 	0x00000002
#define graphicsExporterUsesImageCompressor  0x00000004

#define kQTComponentPropertyListenerCollectionContextVersion 1

#endif /* __IMAGECOMPRESSION_R__ */

