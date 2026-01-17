/*
     File:       Video.r
 
     Contains:   Video Driver Interfaces.
 
     Version:    Quickdraw-192.24~58
 
     Copyright:  © 1986-2006 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

#ifndef __VIDEO_R__
#define __VIDEO_R__

#ifndef __CORESERVICES_R__
#include <CoreServices/CoreServices.r>
#endif

#define mBaseOffset 					1					/* Id of mBaseOffset. */
#define mRowBytes 						2					/* Video sResource parameter Id's  */
#define mBounds 						3					/* Video sResource parameter Id's  */
#define mVersion 						4					/* Video sResource parameter Id's  */
#define mHRes 							5					/* Video sResource parameter Id's  */
#define mVRes 							6					/* Video sResource parameter Id's  */
#define mPixelType 						7					/* Video sResource parameter Id's  */
#define mPixelSize 						8					/* Video sResource parameter Id's  */
#define mCmpCount 						9					/* Video sResource parameter Id's  */
#define mCmpSize 						10					/* Video sResource parameter Id's  */
#define mPlaneBytes 					11					/* Video sResource parameter Id's  */
#define mVertRefRate 					14					/* Video sResource parameter Id's  */
#define mVidParams 						1					/* Video parameter block id. */
#define mTable 							2					/* Offset to the table. */
#define mPageCnt 						3					/* Number of pages */
#define mDevType 						4					/* Device Type */
#define oneBitMode 						128					/* Id of OneBitMode Parameter list. */
#define twoBitMode 						129					/* Id of TwoBitMode Parameter list. */
#define fourBitMode 					130					/* Id of FourBitMode Parameter list. */
#define eightBitMode 					131					/* Id of EightBitMode Parameter list. */

#define sixteenBitMode 					132					/* Id of SixteenBitMode Parameter list. */
#define thirtyTwoBitMode 				133					/* Id of ThirtyTwoBitMode Parameter list. */
#define firstVidMode 					128					/* The new, better way to do the above.  */
#define secondVidMode 					129					/*  QuickDraw only supports six video  */
#define thirdVidMode 					130					/*  at this time.       */
#define fourthVidMode 					131
#define fifthVidMode 					132
#define sixthVidMode 					133
#define spGammaDir 						64
#define spVidNamesDir 					65

#define kDeclROMtables 					'decl'
#define kDetailedTimingFormat 			'arba'				/*  Timing is a detailed timing */

#define kDDCBlockSize 					128
#define kDDCBlockTypeEDID 				0					/*  EDID block type.  */
#define kDDCForceReadBit 				0					/*  Force a new read of the EDID.  */
#define kDDCForceReadMask 				0x01				/*  Mask for kddcForceReadBit.  */

#define timingInvalid 					0					/*     Unknown timingÉ force user to confirm.  */
#define timingInvalid_SM_T24 			8					/*     Work around bug in SM Thunder24 card. */
#define timingApple_FixedRateLCD 		42					/*     Lump all fixed-rate LCDs into one category. */
#define timingApple_512x384_60hz 		130					/*   512x384  (60 Hz) Rubik timing.  */
#define timingApple_560x384_60hz 		135					/*   560x384  (60 Hz) Rubik-560 timing.  */
#define timingApple_640x480_67hz 		140					/*   640x480  (67 Hz) HR timing.  */
#define timingApple_640x400_67hz 		145					/*   640x400  (67 Hz) HR-400 timing.  */
#define timingVESA_640x480_60hz 		150					/*   640x480  (60 Hz) VGA timing.  */
#define timingVESA_640x480_72hz 		152					/*   640x480  (72 Hz) VGA timing.  */
#define timingVESA_640x480_75hz 		154					/*   640x480  (75 Hz) VGA timing.  */
#define timingVESA_640x480_85hz 		158					/*   640x480  (85 Hz) VGA timing.  */
#define timingGTF_640x480_120hz 		159					/*   640x480  (120 Hz) VESA Generalized Timing Formula  */
#define timingApple_640x870_75hz 		160					/*   640x870  (75 Hz) FPD timing. */
#define timingApple_640x818_75hz 		165					/*   640x818  (75 Hz) FPD-818 timing. */
#define timingApple_832x624_75hz 		170					/*   832x624  (75 Hz) GoldFish timing. */
#define timingVESA_800x600_56hz 		180					/*   800x600  (56 Hz) SVGA timing.  */
#define timingVESA_800x600_60hz 		182					/*   800x600  (60 Hz) SVGA timing.  */
#define timingVESA_800x600_72hz 		184					/*   800x600  (72 Hz) SVGA timing.  */
#define timingVESA_800x600_75hz 		186					/*   800x600  (75 Hz) SVGA timing.  */
#define timingVESA_800x600_85hz 		188					/*   800x600  (85 Hz) SVGA timing.  */
#define timingVESA_1024x768_60hz 		190					/*  1024x768  (60 Hz) VESA 1K-60Hz timing.  */
#define timingVESA_1024x768_70hz 		200					/*  1024x768  (70 Hz) VESA 1K-70Hz timing.  */
#define timingVESA_1024x768_75hz 		204					/*  1024x768  (75 Hz) VESA 1K-75Hz timing (very similar to timingApple_1024x768_75hz).  */
#define timingVESA_1024x768_85hz 		208					/*  1024x768  (85 Hz) VESA timing.  */
#define timingApple_1024x768_75hz 		210					/*  1024x768  (75 Hz) Apple 19" RGB.  */
#define timingApple_1152x870_75hz 		220					/*  1152x870  (75 Hz) Apple 21" RGB.  */
#define timingAppleNTSC_ST 				230					/*   512x384  (60 Hz, interlaced, non-convolved).  */
#define timingAppleNTSC_FF 				232					/*   640x480  (60 Hz, interlaced, non-convolved).  */
#define timingAppleNTSC_STconv 			234					/*   512x384  (60 Hz, interlaced, convolved).  */
#define timingAppleNTSC_FFconv 			236					/*   640x480  (60 Hz, interlaced, convolved).  */
#define timingApplePAL_ST 				238					/*   640x480  (50 Hz, interlaced, non-convolved).  */
#define timingApplePAL_FF 				240					/*   768x576  (50 Hz, interlaced, non-convolved).  */
#define timingApplePAL_STconv 			242					/*   640x480  (50 Hz, interlaced, convolved).  */
#define timingApplePAL_FFconv 			244					/*   768x576  (50 Hz, interlaced, convolved).  */
#define timingVESA_1280x960_75hz 		250					/*  1280x960  (75 Hz)  */
#define timingVESA_1280x960_60hz 		252					/*  1280x960  (60 Hz)  */
#define timingVESA_1280x960_85hz 		254					/*  1280x960  (85 Hz)  */
#define timingVESA_1280x1024_60hz 		260					/*  1280x1024 (60 Hz)  */
#define timingVESA_1280x1024_75hz 		262					/*  1280x1024 (75 Hz)  */
#define timingVESA_1280x1024_85hz 		268					/*  1280x1024 (85 Hz)  */
#define timingVESA_1600x1200_60hz 		280					/*  1600x1200 (60 Hz) VESA timing.  */
#define timingVESA_1600x1200_65hz 		282					/*  1600x1200 (65 Hz) VESA timing.  */
#define timingVESA_1600x1200_70hz 		284					/*  1600x1200 (70 Hz) VESA timing.  */
#define timingVESA_1600x1200_75hz 		286					/*  1600x1200 (75 Hz) VESA timing (pixel clock is 189.2 Mhz dot clock).  */
#define timingVESA_1600x1200_80hz 		288					/*  1600x1200 (80 Hz) VESA timing (pixel clock is 216>? Mhz dot clock) - proposed only.  */
#define timingVESA_1600x1200_85hz 		289					/*  1600x1200 (85 Hz) VESA timing (pixel clock is 229.5 Mhz dot clock).  */
#define timingVESA_1792x1344_60hz 		296					/*  1792x1344 (60 Hz) VESA timing (204.75 Mhz dot clock).  */
#define timingVESA_1792x1344_75hz 		298					/*  1792x1344 (75 Hz) VESA timing (261.75 Mhz dot clock).  */
#define timingVESA_1856x1392_60hz 		300					/*  1856x1392 (60 Hz) VESA timing (218.25 Mhz dot clock).  */
#define timingVESA_1856x1392_75hz 		302					/*  1856x1392 (75 Hz) VESA timing (288 Mhz dot clock).  */
#define timingVESA_1920x1440_60hz 		304					/*  1920x1440 (60 Hz) VESA timing (234 Mhz dot clock).  */
#define timingVESA_1920x1440_75hz 		306					/*  1920x1440 (75 Hz) VESA timing (297 Mhz dot clock).  */
#define timingSMPTE240M_60hz 			400					/*  60Hz V, 33.75KHz H, interlaced timing, 16:9 aspect, typical resolution of 1920x1035.  */
#define timingFilmRate_48hz 			410					/*  48Hz V, 25.20KHz H, non-interlaced timing, typical resolution of 640x480.  */
#define timingSony_1600x1024_76hz 		500					/*  1600x1024 (76 Hz) Sony timing (pixel clock is 170.447 Mhz dot clock).  */
#define timingSony_1920x1080_60hz 		510					/*  1920x1080 (60 Hz) Sony timing (pixel clock is 159.84 Mhz dot clock).  */
#define timingSony_1920x1080_72hz 		520					/*  1920x1080 (72 Hz) Sony timing (pixel clock is 216.023 Mhz dot clock).  */
#define timingSony_1920x1200_76hz 		540					/*  1900x1200 (76 Hz) Sony timing (pixel clock is 243.20 Mhz dot clock).  */
#define timingApple_0x0_0hz_Offline 	550					/*  Indicates that this timing will take the display off-line and remove it from the system.  */

#define kAllModesValid 					0					/*  All modes not trimmed by primary init are good close enough to try  */
#define kAllModesSafe 					1					/*  All modes not trimmed by primary init are know to be safe  */
#define kReportsTagging 				2					/*  Can detect tagged displays (to identify smart monitors)  */
#define kHasDirectConnection 			3					/*  True implies that driver can talk directly to device (e.g. serial data link via sense lines)  */
#define kIsMonoDev 						4					/*  Says whether thereÕs an RGB (0) or Monochrome (1) connection.  */
#define kUncertainConnection 			5					/*  There may not be a display (no sense lines?).  */
#define kTaggingInfoNonStandard 		6					/*  Set when csConnectTaggedType/csConnectTaggedData are non-standard (i.e., not the Apple CRT sense codes).  */
#define kReportsDDCConnection 			7					/*  Card can do ddc (set kHasDirectConnect && kHasDDCConnect if you actually found a ddc display).  */
#define kHasDDCConnection 				8					/*  Card has ddc connect now.  */
#define kConnectionInactive 			9					/*  Set when the connection is NOT currently active (generally used in a multiconnection environment).  */
#define kDependentConnection 			10					/*  Set when some ascpect of THIS connection depends on another (will generally be set in a kModeSimulscan environment).  */
#define kBuiltInConnection 				11					/*  Set when connection is KNOWN to be built-in (this is not the same as kHasDirectConnection).  */
#define kOverrideConnection 			12					/*  Set when the reported connection is not the true one, but is one that has been forced through a SetConnection call  */
#define kFastCheckForDDC 				13					/*  Set when all 3 are true: 1) sense codes indicate DDC display could be attached 2) attempted fast check 3) DDC failed  */
#define kReportsHotPlugging 			14					/*  Detects and reports hot pluggging on connector (via VSL also implies DDC will be up to date w/o force read)  */

#define kUnknownConnect 				1					/*  Not sure how weÕll use this, but seems like a good idea.  */
#define kPanelConnect 					2					/*  For use with fixed-in-place LCD panels.  */
#define kPanelTFTConnect 				2					/*  Alias for kPanelConnect  */
#define kFixedModeCRTConnect 			3					/*   For use with fixed-mode (i.e., very limited range) displays.  */
#define kMultiModeCRT1Connect 			4					/*  320x200 maybe, 12" maybe, 13" (default), 16" certain, 19" maybe, 21" maybe  */
#define kMultiModeCRT2Connect 			5					/*  320x200 maybe, 12" maybe, 13" certain, 16" (default), 19" certain, 21" maybe  */
#define kMultiModeCRT3Connect 			6					/*  320x200 maybe, 12" maybe, 13" certain, 16" certain, 19" default, 21" certain  */
#define kMultiModeCRT4Connect 			7					/*  Expansion to large multi mode (not yet used)  */
#define kModelessConnect 				8					/*  Expansion to modeless model (not yet used)  */
#define kFullPageConnect 				9					/*  640x818 (to get 8bpp in 512K case) and 640x870 (these two only)  */
#define kVGAConnect 					10					/*  640x480 VGA default -- question everything else  */
#define kNTSCConnect 					11					/*  NTSC ST (default), FF, STconv, FFconv  */
#define kPALConnect 					12					/*  PAL ST (default), FF, STconv, FFconv  */
#define kHRConnect 						13					/*  Straight-6 connect -- 640x480 and 640x400 (to get 8bpp in 256K case) (these two only)  */
#define kPanelFSTNConnect 				14					/*  For use with fixed-in-place LCD FSTN (aka ÒSupertwistÓ) panels  */
#define kMonoTwoPageConnect 			15					/*  1152x870 Apple color two-page display  */
#define kColorTwoPageConnect 			16					/*  1152x870 Apple B&W two-page display  */
#define kColor16Connect 				17					/*  832x624 Apple B&W two-page display  */
#define kColor19Connect 				18					/*  1024x768 Apple B&W two-page display  */
#define kGenericCRT 					19					/*  Indicates nothing except that connection is CRT in nature.  */
#define kGenericLCD 					20					/*  Indicates nothing except that connection is LCD in nature.  */
#define kDDCConnect 					21					/*  DDC connection, always set kHasDDCConnection  */
#define kNoConnect 						22					/*  No display is connected - load sensing or similar level of hardware detection is assumed (used by resident drivers that support hot plugging when nothing is currently connected)  */

#define kModeValid 						0					/*  Says that this mode should NOT be trimmed.  */
#define kModeSafe 						1					/*  This mode does not need confirmation  */
#define kModeDefault 					2					/*  This is the default mode for this type of connection  */
#define kModeShowNow 					3					/*  This mode should always be shown (even though it may require a confirm)  */
#define kModeNotResize 					4					/*  This mode should not be used to resize the display (eg. mode selects a different connector on card)  */
#define kModeRequiresPan 				5					/*  This mode has more pixels than are actually displayed  */
#define kModeInterlaced 				6					/*  This mode is interlaced (single pixel lines look bad).  */
#define kModeShowNever 					7					/*  This mode should not be shown in the user interface.  */
#define kModeSimulscan 					8					/*  Indicates that more than one display connection can be driven from a single framebuffer controller.  */
#define kModeNotPreset 					9					/*  Indicates that the timing is not a factory preset for the current display (geometry may need correction)  */
#define kModeBuiltIn 					10					/*  Indicates that the display mode is for the built-in connect only (on multiconnect devices like the PB 3400) Only the driver is quieried  */
#define kModeStretched 					11					/*  Indicates that the display mode will be stretched/distorted to match the display aspect ratio  */

#define kDepthDependent 				0					/*  Says that this depth mode may cause dependent changes in other framebuffers (and .  */
#define kResolutionHasMultipleDepthSizes  0					/*  Says that this mode has different csHorizontalPixels, csVerticalLines at different depths (usually slightly larger at lower depths)  */
															/*     Power Mode constants for VDPowerStateRec.powerState.  Note the numeric order does not match the power state order  */
#define kAVPowerOff 					0					/*  Power fully off */
#define kAVPowerStandby 				1
#define kAVPowerSuspend 				2
#define kAVPowerOn 						3
#define kHardwareSleep 					128
#define kHardwareWake 					129
#define kHardwareWakeFromSuspend 		130
#define kHardwareWakeToDoze 			131
#define kHardwareWakeToDozeFromSuspend 	132

															/*     Power Mode masks and bits for VDPowerStateRec.powerFlags.   */
#define kPowerStateNeedsRefresh 		0					/*  When leaving this power mode, a display will need refreshing    */
#define kPowerStateSleepAwareBit 		1					/*  if gestaltPCCardDockingSelectorFix, Docking mgr checks this bit before checking kPowerStateSleepAllowedBit  */
#define kPowerStateSleepForbiddenBit 	2					/*  if kPowerStateSleepAwareBit, Docking mgr checks this bit before sleeping  */
#define kPowerStateSleepCanPowerOffBit 	3					/*  supports power down sleep (ie PCI power off) */
#define kPowerStateSleepNoDPMSBit 		4					/*  Bug #2425210.  Do not use DPMS with this display. */
#define kPowerStateSleepWaketoDozeBit 	5					/*  Supports Wake to Doze  */
#define kPowerStateNeedsRefreshMask 	0x00000001
#define kPowerStateSleepAwareMask 		0x00000002
#define kPowerStateSleepForbiddenMask 	0x00000004
#define kPowerStateSleepCanPowerOffMask  0x00000008
#define kPowerStateSleepNoDPMSMask 		0x00000010
#define kPowerStateSleepWaketoDozeMask 	0x00000020

															/*  Control Codes  */
#define cscReset 						0
#define cscKillIO 						1
#define cscSetMode 						2
#define cscSetEntries 					3
#define cscSetGamma 					4
#define cscGrayPage 					5
#define cscGrayScreen 					5
#define cscSetGray 						6
#define cscSetInterrupt 				7
#define cscDirectSetEntries 			8
#define cscSetDefaultMode 				9
#define cscSwitchMode 					10					/*  Takes a VDSwitchInfoPtr  */
#define cscSetSync 						11					/*  Takes a VDSyncInfoPtr  */
#define cscSavePreferredConfiguration 	16					/*  Takes a VDSwitchInfoPtr  */
#define cscSetHardwareCursor 			22					/*  Takes a VDSetHardwareCursorPtr  */
#define cscDrawHardwareCursor 			23					/*  Takes a VDDrawHardwareCursorPtr  */
#define cscSetConvolution 				24					/*  Takes a VDConvolutionInfoPtr  */
#define cscSetPowerState 				25					/*  Takes a VDPowerStatePtr  */
#define cscPrivateControlCall 			26					/*  Takes a VDPrivateSelectorDataPtr  */
#define cscSetMultiConnect 				28					/*  Takes a VDMultiConnectInfoPtr  */
#define cscSetClutBehavior 				29					/*  Takes a VDClutBehavior  */
#define cscSetDetailedTiming 			31					/*  Takes a VDDetailedTimingPtr  */
#define cscDoCommunication 				33					/*  Takes a VDCommunicationPtr  */
#define cscProbeConnection 				34					/*  Takes nil pointer (may generate a kFBConnectInterruptServiceType service interrupt) */
#define cscUnusedCall 					127					/*  This call used to expend the scrn resource.  Its imbedded data contains more control info  */

															/*  Status Codes  */
#define cscGetMode 						2
#define cscGetEntries 					3
#define cscGetPageCnt 					4
#define cscGetPages 					4					/*  This is what C&D 2 calls it.  */
#define cscGetPageBase 					5
#define cscGetBaseAddr 					5					/*  This is what C&D 2 calls it.  */
#define cscGetGray 						6
#define cscGetInterrupt 				7
#define cscGetGamma 					8
#define cscGetDefaultMode 				9
#define cscGetCurMode 					10					/*  Takes a VDSwitchInfoPtr  */
#define cscGetSync 						11					/*  Takes a VDSyncInfoPtr  */
#define cscGetConnection 				12					/*  Return information about the connection to the display  */
#define cscGetModeTiming 				13					/*  Return timing info for a mode  */
#define cscGetModeBaseAddress 			14					/*  Return base address information about a particular mode  */
#define cscGetScanProc 					15					/*  QuickTime scan chasing routine  */
#define cscGetPreferredConfiguration 	16					/*  Takes a VDSwitchInfoPtr  */
#define cscGetNextResolution 			17					/*  Takes a VDResolutionInfoPtr  */
#define cscGetVideoParameters 			18					/*  Takes a VDVideoParametersInfoPtr  */
#define cscGetGammaInfoList 			20					/*  Takes a VDGetGammaListPtr  */
#define cscRetrieveGammaTable 			21					/*  Takes a VDRetrieveGammaPtr  */
#define cscSupportsHardwareCursor 		22					/*  Takes a VDSupportsHardwareCursorPtr  */
#define cscGetHardwareCursorDrawState 	23					/*  Takes a VDHardwareCursorDrawStatePtr  */
#define cscGetConvolution 				24					/*  Takes a VDConvolutionInfoPtr  */
#define cscGetPowerState 				25					/*  Takes a VDPowerStatePtr  */
#define cscPrivateStatusCall 			26					/*  Takes a VDPrivateSelectorDataPtr  */
#define cscGetDDCBlock 					27					/*  Takes a VDDDCBlockPtr   */
#define cscGetMultiConnect 				28					/*  Takes a VDMultiConnectInfoPtr  */
#define cscGetClutBehavior 				29					/*  Takes a VDClutBehaviorPtr  */
#define cscGetTimingRanges 				30					/*  Takes a VDDisplayTimingRangePtr  */
#define cscGetDetailedTiming 			31					/*  Takes a VDDetailedTimingPtr  */
#define cscGetCommunicationInfo 		32					/*  Takes a VDCommunicationInfoPtr  */

#define kDisableHorizontalSyncBit 		0
#define kDisableVerticalSyncBit 		1
#define kDisableCompositeSyncBit 		2
#define kEnableSyncOnBlue 				3
#define kEnableSyncOnGreen 				4
#define kEnableSyncOnRed 				5
#define kNoSeparateSyncControlBit 		6
#define kTriStateSyncBit 				7
#define kHorizontalSyncMask 			0x01
#define kVerticalSyncMask 				0x02
#define kCompositeSyncMask 				0x04
#define kDPMSSyncMask 					0x07
#define kTriStateSyncMask 				0x80
#define kSyncOnBlueMask 				0x08
#define kSyncOnGreenMask 				0x10
#define kSyncOnRedMask 					0x20
#define kSyncOnMask 					0x38

															/*     Power Mode constants for translating DPMS modes to Get/SetSync calls.   */
#define kDPMSSyncOn 					0
#define kDPMSSyncStandby 				1
#define kDPMSSyncSuspend 				2
#define kDPMSSyncOff 					7

#define kConvolved 						0
#define kLiveVideoPassThru 				1
#define kConvolvedMask 					0x01
#define kLiveVideoPassThruMask 			0x02

#define kRSCZero 						0
#define kRSCOne 						1
#define kRSCTwo 						2
#define kRSCThree 						3
#define kRSCFour 						4
#define kRSCFive 						5
#define kRSCSix 						6
#define kRSCSeven 						7

#define kESCZero21Inch 					0x00				/*  21" RGB                      */
#define kESCOnePortraitMono 			0x14				/*  Portrait Monochrome               */
#define kESCTwo12Inch 					0x21				/*  12" RGB                     */
#define kESCThree21InchRadius 			0x31				/*  21" RGB (Radius)                */
#define kESCThree21InchMonoRadius 		0x34				/*  21" Monochrome (Radius)            */
#define kESCThree21InchMono 			0x35				/*  21" Monochrome                */
#define kESCFourNTSC 					0x0A				/*  NTSC                      */
#define kESCFivePortrait 				0x1E				/*  Portrait RGB               */
#define kESCSixMSB1 					0x03				/*  MultiScan Band-1 (12" thru 1Six")   */
#define kESCSixMSB2 					0x0B				/*  MultiScan Band-2 (13" thru 19")        */
#define kESCSixMSB3 					0x23				/*  MultiScan Band-3 (13" thru 21")        */
#define kESCSixStandard 				0x2B				/*  13"/14" RGB or 12" Monochrome    */
#define kESCSevenPAL 					0x00				/*  PAL                         */
#define kESCSevenNTSC 					0x14				/*  NTSC                      */
#define kESCSevenVGA 					0x17				/*  VGA                         */
#define kESCSeven16Inch 				0x2D				/*  16" RGB (GoldFish)                */
#define kESCSevenPALAlternate 			0x30				/*  PAL (Alternate)                 */
#define kESCSeven19Inch 				0x3A				/*  Third-Party 19Ó                  */
#define kESCSevenDDC 					0x3E				/*  DDC display                    */
#define kESCSevenNoDisplay 				0x3F				/*  No display connected            */

#define kDepthMode1 					128
#define kDepthMode2 					129
#define kDepthMode3 					130
#define kDepthMode4 					131
#define kDepthMode5 					132
#define kDepthMode6 					133

#define kFirstDepthMode 				128					/*  These constants are obsolete, and just included     */
#define kSecondDepthMode 				129					/*  for clients that have converted to the above      */
#define kThirdDepthMode 				130					/*  kDepthModeXXX constants.                 */
#define kFourthDepthMode 				131
#define kFifthDepthMode 				132
#define kSixthDepthMode 				133

#define kDisplayModeIDCurrent 			0x00				/*  Reference the Current DisplayModeID  */
#define kDisplayModeIDInvalid 			0xFFFFFFFF			/*  A bogus DisplayModeID in all cases  */
#define kDisplayModeIDFindFirstResolution  0xFFFFFFFE		/*  Used in cscGetNextResolution to reset iterator  */
#define kDisplayModeIDNoMoreResolutions  0xFFFFFFFD			/*  Used in cscGetNextResolution to indicate End Of List  */
#define kDisplayModeIDFindFirstProgrammable  0xFFFFFFFC		/*  Used in cscGetNextResolution to find unused programmable timing  */
#define kDisplayModeIDBootProgrammable 	0xFFFFFFFB			/*  This is the ID given at boot time by the OF driver to a programmable timing  */
#define kDisplayModeIDReservedBase 		0x80000000			/*  Lowest (unsigned) DisplayModeID reserved by Apple  */

#define kGammaTableIDFindFirst 			0xFFFFFFFE			/*  Get the first gamma table ID  */
#define kGammaTableIDNoMoreTables 		0xFFFFFFFD			/*  Used to indicate end of list  */
#define kGammaTableIDSpecific 			0x00				/*  Return the info for the given table id  */

#define kGetConnectionCount 			0xFFFFFFFF			/*  Used to get the number of possible connections in a Òmulti-headedÓ framebuffer environment. */
#define kActivateConnection 			0x00				/*  Used for activating a connection (csConnectFlags value). */
#define kDeactivateConnection 			0x0200				/*  Used for deactivating a connection (csConnectFlags value.) */

#define kVideoDefaultBus 				0
#define kVideoBusTypeInvalid 			0
#define kVideoBusTypeI2C 				1

#define kVideoNoTransactionType 		0					/*  No transaction */
#define kVideoSimpleI2CType 			1					/*  Simple I2C message */
#define kVideoDDCciReplyType 			2					/*  DDC/ci message (with imbedded length) */

#define kVideoReplyMicroSecDelayMask 	0x01				/*  If set, the driver should delay csMinReplyDelay micro seconds between send and recieve */
															/*  timingSyncConfiguration */
#define kSyncInterlaceMask 				0x80
#define kSyncAnalogCompositeMask 		0
#define kSyncAnalogCompositeSerrateMask  0x04
#define kSyncAnalogCompositeRGBSyncMask  0x02
#define kSyncAnalogBipolarMask 			0x08
#define kSyncAnalogBipolarSerrateMask 	0x04
#define kSyncAnalogBipolarSRGBSyncMask 	0x02
#define kSyncDigitalCompositeMask 		0x10
#define kSyncDigitalCompositeSerrateMask  0x04
#define kSyncDigitalCompositeMatchHSyncMask  0x04
#define kSyncDigitalSeperateMask 		0x18
#define kSyncDigitalVSyncPositiveMask 	0x04
#define kSyncDigitalHSyncPositiveMask 	0x02

															/*  csDisplayModeState */
#define kDMSModeReady 					0					/*  Display Mode ID is configured and ready */
#define kDMSModeNotReady 				1					/*  Display Mode ID is is being programmed */
#define kDMSModeFree 					2					/*  Display Mode ID is not associated with a timing */

#define kTimingChangeRestrictedErr 		(-10930)
#define kVideoI2CReplyPendingErr 		(-10931)
#define kVideoI2CTransactionErr 		(-10932)
#define kVideoI2CBusyErr 				(-10933)
#define kVideoI2CTransactionTypeErr 	(-10934)
#define kVideoBufferSizeErr 			(-10935)

															/*  csTimingRangeSignalLevels */
#define kRangeSupportsSignal_0700_0300_Bit  0
#define kRangeSupportsSignal_0714_0286_Bit  1
#define kRangeSupportsSignal_1000_0400_Bit  2
#define kRangeSupportsSignal_0700_0000_Bit  3
#define kRangeSupportsSignal_0700_0300_Mask  0x01
#define kRangeSupportsSignal_0714_0286_Mask  0x02
#define kRangeSupportsSignal_1000_0400_Mask  0x04
#define kRangeSupportsSignal_0700_0000_Mask  0x08

															/*  csSignalConfig */
#define kDigitalSignalBit 				0					/*  Do not set.  Mac OS does not currently support arbitrary digital timings */
#define kAnalogSetupExpectedBit 		1					/*  Analog displays - display expects a blank-to-black setup or pedestal.  See VESA signal standards. */
#define kDigitalSignalMask 				0x01
#define kAnalogSetupExpectedMask 		0x02

															/*  csSignalLevels for analog */
#define kAnalogSignalLevel_0700_0300 	0
#define kAnalogSignalLevel_0714_0286 	1
#define kAnalogSignalLevel_1000_0400 	2
#define kAnalogSignalLevel_0700_0000 	3

															/*  csTimingRangeSyncFlags */
#define kRangeSupportsSeperateSyncsBit 	0
#define kRangeSupportsSyncOnGreenBit 	1
#define kRangeSupportsCompositeSyncBit 	2
#define kRangeSupportsVSyncSerrationBit  3
#define kRangeSupportsSeperateSyncsMask  0x01
#define kRangeSupportsSyncOnGreenMask 	0x02
#define kRangeSupportsCompositeSyncMask  0x04
#define kRangeSupportsVSyncSerrationMask  0x08

															/*  csHorizontalSyncConfig and csVerticalSyncConfig */
#define kSyncPositivePolarityBit 		0					/*  Digital separate sync polarity for analog interfaces (0 => negative polarity) */
#define kSyncPositivePolarityMask 		0x01

#define kSetClutAtSetEntries 			0					/*  SetEntries behavior is to update clut during SetEntries call */
#define kSetClutAtVBL 					1					/*  SetEntries behavior is to upate clut at next vbl */


#endif /* __VIDEO_R__ */

