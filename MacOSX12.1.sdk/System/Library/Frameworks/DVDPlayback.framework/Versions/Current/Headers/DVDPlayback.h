/*
     File:       DVDPlayback/DVDPlayback.h

     Contains:   API for communicating with DVD playback engine.

     Version:    Technology: Mac OS X
                 Release:    Mac OS X

     Copyright:  (c) 2001-2015 by Apple Inc. All rights reserved.

     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:

                     http://developer.apple.com/bugreporter/

*/

/*-----------------------------------------------------
	The DVD Playback application programming interface (API) gives you access to the DVDPlayback framework, 
	allowing you to offer DVD playback functionality from within your application.

	During a playback "session," the application must perform specific minimum operations, as follows:
	1.	Initialize the playback framework with DVDInitialize. The DVDPlayback framework can only be opened by one
		process at a time. If a second process attempts to initialize it, an error will be returned.
	2.	Set the playback grafport with DVDSetVideoPort(Carbon) or the window with DVDSetVideoWindowID(Cocoa).
	3.	Set the gDevice with DVDSetVideoDevice(Carbon) or the display with DVDSetVideoDisplay(Cocoa).
	4.	Set the video bounds with DVDSetVideoBounds. This is the bounds within the grafport/window and is in port coordinates.
	5.	Open the media with DVDOpenMediaVolume (DVD disc) or DVDOpenMediaFile (VIDEO_TS folder).
	6.	Play the media
	7.	When finished or switching media, close with the appropriate call (DVDCloseMediaVolume or DVDCloseMediaFile)
	8.	When quitting or finishing session, tear down the DVDPlayback framework with DVDDispose.
-----------------------------------------------------*/

#ifndef __DVDPLAYBACK__
#define __DVDPLAYBACK__

#include 	<AvailabilityMacros.h>
#include	<CoreFoundation/CFAvailability.h>
#include	<ApplicationServices/ApplicationServices.h>
#include	<Security/Authorization.h>

#ifdef __cplusplus
extern "C" {
#endif

// some pre-defines to support Swift based clients

#if defined(__has_feature) && __has_feature(nullability)
	#define DVD_ASSUME_NONNULL_BEGIN _Pragma("clang assume_nonnull begin")
	#define DVD_ASSUME_NONNULL_END   _Pragma("clang assume_nonnull end")
	#define DVD_NULLABLE __nullable
	#define DVD_NONNULL __nonnull
#else
	#define DVD_ASSUME_NONNULL_BEGIN 
	#define DVD_ASSUME_NONNULL_END 
	#define DVD_NULLABLE
	#define DVD_NONNULL
#endif

DVD_ASSUME_NONNULL_BEGIN

//-----------------------------------------------------
// DVDErrorCode - Errors returned by the framework (-70000 to -70099)
//-----------------------------------------------------
enum {
	kDVDErrorUnknown					= -70001,	//	Catch all error
	kDVDErrorInitializingLib			= -70002,	//	There was an error initializing the playback framework
	kDVDErrorUninitializedLib			= -70003,	//	The playback framework has not been initialized.
	kDVDErrorNotAllowedDuringPlayback	= -70004,	//	action is not allowed during playback
	kDVDErrorUnassignedGrafPort			= -70005,	//	A grafport was not set.
	kDVDErrorAlreadyPlaying				= -70006,	//	Media is already being played.
	kDVDErrorNoFatalErrCallBack			= -70007,	//	The application did not install a callback routine for fatal errors returned by the framework.
	kDVDErrorIsAlreadySleeping			= -70008,	//	The framework has already been notified to sleep.
	kDVDErrorDontNeedWakeup				= -70009,	//	DVDWakeUp was called when the framework was not asleep.
	kDVDErrorTimeOutOfRange				= -70010,	//	Time code is outside the valid range for the current title.
	kDVDErrorUserActionNoOp				= -70011,	//	The operation was not allowed by the media at this time.
	kDVDErrorMissingDrive				= -70012,	//	The DVD drive is not available.
	kDVDErrorNotSupportedConfiguration	= -70013,	//	The current system configuration is not supported.
	kDVDErrorNotSupportedFunction		= -70014,	//	The operation is not supported. For example, trying to slow mo backwards.
	kDVDErrorNoValidMedia				= -70015,	//	The media was not valid for playback.
	kDVDErrorWrongParam					= -70016,	//	The invalid parameter was passed.
	kDVDErrorMissingGraphicsDevice		= -70017,	//	A valid graphics device is not available.
	kDVDErrorGraphicsDevice				= -70018,	//	A graphics device error was encountered.
	kDVDErrorPlaybackOpen				= -70019,	//	The framework is already open (probably by another process).
	kDVDErrorInvalidRegionCode			= -70020,	//	The region code was not valid.
	kDVDErrorRgnMgrInstall				= -70021,	//	The region manager was not properly installed or missing from the system.
	kDVDErrorMismatchedRegionCode		= -70022,	//	The disc region code and the drive region code do not match.
	kDVDErrorNoMoreRegionSets			= -70023,	//	The drive does not have any region changes left.
	kDVDErrordRegionCodeUninitialized	= -70024,	//	The drive region code was not initialized.
	kDVDErrorAuthentification			= -70025,	//	The user attempting to change the region code could not be authenticated.
	kDVDErrorOutOfVideoMemory			= -70026,	//	The video driver does not have enough video memory available to playback the media.
	kDVDErrorNoAudioOutputDevice		= -70027,	//	An appropriate audio output device could not be found.
	kDVDErrorSystem						= -70028,	//	A system error was encountered.
	kDVDErrorNavigation					= -70029,	//	The user has made a selection not supported in the current menu.
	kDVDErrorInvalidBookmarkVersion		= -70030,	//	invalid bookmark version
	kDVDErrorInvalidBookmarkSize		= -70031,	//	invalid bookmark size
	kDVDErrorInvalidBookmarkForMedia	= -70032,	//	invalid bookmark for media
	kDVDErrorNoValidBookmarkForLastPlay	= -70033,	//	no valid last play bookmark
	kDVDErrorDisplayAuthentification	= -70034	//	invalid display authentication: e.g. HDCP failure, ...

};
typedef OSStatus	DVDErrorCode;



//-----------------------------------------------------
// DVDState - The current play state of the framework.
//-----------------------------------------------------
typedef CF_ENUM(OSStatus, DVDState) {
	kDVDStateUnknown,
	kDVDStatePlaying,		// playing 1x or less (slow mo)
	kDVDStatePlayingStill,
	kDVDStatePaused,		// pause and step frame
	kDVDStateStopped,		// the DVDEvent for stopping has a 2nd parameter to indicate that the stop was initiated by the DVD disc
							// 0: user, 1: disc initiated
	kDVDStateScanning,		// playing greater than 1x
	kDVDStateIdle,
	kDVDStatePlayingSlow	// playing less than 1x
};


//-----------------------------------------------------
// DVDMenu - Which menu we are currently on (if any).
//-----------------------------------------------------
typedef CF_ENUM(UInt32, DVDMenu) {
	kDVDMenuTitle,
	kDVDMenuRoot,
	kDVDMenuSubPicture,
	kDVDMenuAudio,
	kDVDMenuAngle,
	kDVDMenuPTT,
	kDVDMenuNone
};


//-----------------------------------------------------
// DVDButtonIndex - Index of the selected menu button.
//-----------------------------------------------------
enum {
	kDVDButtonIndexNone = -1
};
typedef SInt32	DVDButtonIndex;


//-----------------------------------------------------
// DVDUserNavigation - The direction the user is trying to navigate on the menu.
//-----------------------------------------------------
typedef CF_ENUM(UInt32, DVDUserNavigation) {
	kDVDUserNavigationMoveUp = 1,
	kDVDUserNavigationMoveDown,
	kDVDUserNavigationMoveLeft,
	kDVDUserNavigationMoveRight,
	kDVDUserNavigationEnter
};


//-----------------------------------------------------
//	DVDTimePosition -	Used in conjunction with the DVDTimeCode to find an exact 
//						temporal location within the current title/chapter.
//-----------------------------------------------------
typedef UInt32	DVDTimePosition;


//-----------------------------------------------------
// DVDTimeCode -	Used in conjunction with the DVDTimePosition to find an exact 
//					temporal location within the current title/chapter.
//-----------------------------------------------------
enum {
	kDVDTimeCodeUninitialized,
	kDVDTimeCodeElapsedSeconds,
	kDVDTimeCodeRemainingSeconds,
	kDVDTimeCodeTitleDurationSeconds,			// only useable for GetTime
	kDVDTimeCodeChapterElapsedSeconds,			// "
	kDVDTimeCodeChapterRemainingSeconds,		// "
	kDVDTimeCodeChapterDurationSeconds			// "
};
typedef SInt16	DVDTimeCode;


//-----------------------------------------------------
// DVDScan Direction -	Direction of play (backward or forward). Backward is currently not supported.
//-----------------------------------------------------
typedef CF_ENUM(SInt8, DVDScanDirection) {
	kDVDScanDirectionForward,
	kDVDScanDirectionBackward
};


//-----------------------------------------------------
// DVDScanRate - The rate at which to scan (used with DVDScanDirection).
//-----------------------------------------------------
typedef CF_ENUM(SInt16, DVDScanRate) {
	kDVDScanRateOneEigth				= -8,
	kDVDScanRateOneFourth				= -4,
	kDVDScanRateOneHalf					= -2,
	kDVDScanRate1x						= 1,
	kDVDScanRate2x						= 2,
	kDVDScanRate4x						= 4,
	kDVDScanRate8x						= 8,
	kDVDScanRate16x						= 16,
	kDVDScanRate32x						= 32
};


//-----------------------------------------------------
// DVDAspectRatio - The current aspect ratio (could be different when on menus 
//					or in the body of the title).
//-----------------------------------------------------
typedef CF_ENUM(SInt16, DVDAspectRatio) {
	kDVDAspectRatioUninitialized,
	kDVDAspectRatio4x3,
	kDVDAspectRatio4x3PanAndScan,
	kDVDAspectRatio16x9,
	kDVDAspectRatioLetterBox
};


//-----------------------------------------------------
// DVDFormat - The format of the title.
//-----------------------------------------------------
typedef CF_ENUM(SInt16, DVDFormat) {
	kDVDFormatUninitialized,
	kDVDFormatNTSC,
	kDVDFormatPAL,
	kDVDFormatNTSC_HDTV,
	kDVDFormatPAL_HDTV
};


//-----------------------------------------------------
// DVDAudioMode - The supported audio output formats
//-----------------------------------------------------
enum {
	kDVDAudioModeUninitialized 		= 0,
	kDVDAudioModeProLogic 			= 1 << 0,
	kDVDAudioModeSPDIF				= 1 << 1
};
typedef SInt32	DVDAudioMode;


//-----------------------------------------------------
// DVDAudioStreamFormat - The different possible audio stream formats.
//-----------------------------------------------------
typedef CF_ENUM(SInt16, DVDAudioFormat) {
	kDVDAudioUnknownFormat,
	kDVDAudioAC3Format,
	kDVDAudioMPEG1Format,
	kDVDAudioMPEG2Format,
	kDVDAudioPCMFormat,
	kDVDAudioDTSFormat,
	kDVDAudioSDDSFormat,
	kDVDAudioMLPFormat,
	kDVDAudioDDPlusFormat,
	kDVDAudioDTSHDFormat
};


//-----------------------------------------------------
// DVDLanguageCode - The different possible language codes.
//-----------------------------------------------------
enum {
	kDVDLanguageCodeUninitialized 	= FOUR_CHAR_CODE('??  '),
	kDVDLanguageNoPreference		= FOUR_CHAR_CODE('**  '),
	kDVDLanguageCodeNone			= FOUR_CHAR_CODE('00  '),
	
	kDVDLanguageCodeAfar			= FOUR_CHAR_CODE('aa  '),
	kDVDLanguageCodeAbkhazian		= FOUR_CHAR_CODE('ab  '),
	kDVDLanguageCodeAfrikaans		= FOUR_CHAR_CODE('af  '),
	kDVDLanguageCodeAmharic			= FOUR_CHAR_CODE('am  '),
	kDVDLanguageCodeArabic			= FOUR_CHAR_CODE('ar  '),
	kDVDLanguageCodeAssamese		= FOUR_CHAR_CODE('as  '),
	kDVDLanguageCodeAymara			= FOUR_CHAR_CODE('ay  '),
	kDVDLanguageCodeAzerbaijani		= FOUR_CHAR_CODE('az  '),
	kDVDLanguageCodeBashkir			= FOUR_CHAR_CODE('ba  '),
	kDVDLanguageCodeByelorussian	= FOUR_CHAR_CODE('be  '),
	kDVDLanguageCodeBulgarian		= FOUR_CHAR_CODE('bg  '),
	kDVDLanguageCodeBihari			= FOUR_CHAR_CODE('bh  '),
	kDVDLanguageCodeBislama			= FOUR_CHAR_CODE('bi  '),
	kDVDLanguageCodeBengali			= FOUR_CHAR_CODE('bn  '),
	kDVDLanguageCodeTibetan			= FOUR_CHAR_CODE('bo  '),
	kDVDLanguageCodeBreton			= FOUR_CHAR_CODE('br  '),
	kDVDLanguageCodeCatalan			= FOUR_CHAR_CODE('ca  '),
	kDVDLanguageCodeCorsican		= FOUR_CHAR_CODE('co  '),
	kDVDLanguageCodeCzech			= FOUR_CHAR_CODE('cs  '),
	kDVDLanguageCodeWelsh			= FOUR_CHAR_CODE('cy  '),
	kDVDLanguageCodeDanish			= FOUR_CHAR_CODE('da  '),
	kDVDLanguageCodeGerman			= FOUR_CHAR_CODE('de  '),
	kDVDLanguageCodeBhutani			= FOUR_CHAR_CODE('dz  '),
	kDVDLanguageCodeGreek			= FOUR_CHAR_CODE('el  '),
	kDVDLanguageCodeEnglish			= FOUR_CHAR_CODE('en  '),
	kDVDLanguageCodeEsperanto		= FOUR_CHAR_CODE('eo  '),
	kDVDLanguageCodeSpanish			= FOUR_CHAR_CODE('es  '),
	kDVDLanguageCodeEstonian		= FOUR_CHAR_CODE('et  '),
	kDVDLanguageCodeBasque			= FOUR_CHAR_CODE('eu  '),
	kDVDLanguageCodePersian			= FOUR_CHAR_CODE('fa  '),
	kDVDLanguageCodeFinnish			= FOUR_CHAR_CODE('fi  '),
	kDVDLanguageCodeFiji			= FOUR_CHAR_CODE('fj  '),
	kDVDLanguageCodeFaeroese		= FOUR_CHAR_CODE('fo  '),
	kDVDLanguageCodeFrench			= FOUR_CHAR_CODE('fr  '),
	kDVDLanguageCodeFrisian			= FOUR_CHAR_CODE('fy  '),
	kDVDLanguageCodeIrish			= FOUR_CHAR_CODE('ga  '),
	kDVDLanguageCodeScotsGaelic		= FOUR_CHAR_CODE('gd  '),
	kDVDLanguageCodeGalician		= FOUR_CHAR_CODE('gl  '),
	kDVDLanguageCodeGuarani			= FOUR_CHAR_CODE('gn  '),
	kDVDLanguageCodeGujarati		= FOUR_CHAR_CODE('gu  '),
	kDVDLanguageCodeHausa			= FOUR_CHAR_CODE('ha  '),
	kDVDLanguageCodeHindi			= FOUR_CHAR_CODE('hi  '),
	kDVDLanguageCodeCroatian		= FOUR_CHAR_CODE('hr  '),
	kDVDLanguageCodeHungarian		= FOUR_CHAR_CODE('hu  '),
	kDVDLanguageCodeArmenian		= FOUR_CHAR_CODE('hy  '),
	kDVDLanguageCodeInterlingua		= FOUR_CHAR_CODE('ia  '),
	kDVDLanguageCodeInterlingue		= FOUR_CHAR_CODE('ie  '),
	kDVDLanguageCodeInupiak			= FOUR_CHAR_CODE('ik  '),
	kDVDLanguageCodeIndonesian		= FOUR_CHAR_CODE('in  '),
	kDVDLanguageCodeIcelandic		= FOUR_CHAR_CODE('is  '),
	kDVDLanguageCodeItalian			= FOUR_CHAR_CODE('it  '),
	kDVDLanguageCodeHebrew			= FOUR_CHAR_CODE('iw  '),
	kDVDLanguageCodeJapanese		= FOUR_CHAR_CODE('ja  '),
	kDVDLanguageCodeYiddish			= FOUR_CHAR_CODE('ji  '),
	kDVDLanguageCodeJavanese		= FOUR_CHAR_CODE('jw  '),
	kDVDLanguageCodeGeorgian		= FOUR_CHAR_CODE('ka  '),
	kDVDLanguageCodeKazakh			= FOUR_CHAR_CODE('kk  '),
	kDVDLanguageCodeGreenlandic		= FOUR_CHAR_CODE('kl  '),
	kDVDLanguageCodeCambodian		= FOUR_CHAR_CODE('km  '),
	kDVDLanguageCodeKannada			= FOUR_CHAR_CODE('kn  '),
	kDVDLanguageCodeKorean			= FOUR_CHAR_CODE('ko  '),
	kDVDLanguageCodeKashmiri		= FOUR_CHAR_CODE('ks  '),
	kDVDLanguageCodeKurdish			= FOUR_CHAR_CODE('ku  '),
	kDVDLanguageCodeKirghiz			= FOUR_CHAR_CODE('ky  '),
	kDVDLanguageCodeLatin			= FOUR_CHAR_CODE('la  '),
	kDVDLanguageCodeLingala			= FOUR_CHAR_CODE('ln  '),
	kDVDLanguageCodeLaothian		= FOUR_CHAR_CODE('lo  '),
	kDVDLanguageCodeLithuanian		= FOUR_CHAR_CODE('lt  '),
	kDVDLanguageCodeLatvian			= FOUR_CHAR_CODE('lv  '),
	kDVDLanguageCodeMalagasy		= FOUR_CHAR_CODE('mg  '),
	kDVDLanguageCodeMaori			= FOUR_CHAR_CODE('mi  '),
	kDVDLanguageCodeMacedonian		= FOUR_CHAR_CODE('mk  '),
	kDVDLanguageCodeMalayalam		= FOUR_CHAR_CODE('ml  '),
	kDVDLanguageCodeMongolian		= FOUR_CHAR_CODE('mn  '),
	kDVDLanguageCodeMoldavian		= FOUR_CHAR_CODE('mo  '),
	kDVDLanguageCodeMarathi			= FOUR_CHAR_CODE('mr  '),
	kDVDLanguageCodeMalay			= FOUR_CHAR_CODE('ms  '),
	kDVDLanguageCodeMaltese			= FOUR_CHAR_CODE('mt  '),
	kDVDLanguageCodeBurmese			= FOUR_CHAR_CODE('my  '),
	kDVDLanguageCodeNauru			= FOUR_CHAR_CODE('na  '),
	kDVDLanguageCodeNepali			= FOUR_CHAR_CODE('ne  '),
	kDVDLanguageCodeDutch			= FOUR_CHAR_CODE('nl  '),
	kDVDLanguageCodeNorwegian		= FOUR_CHAR_CODE('no  '),
	kDVDLanguageCodeOccitan			= FOUR_CHAR_CODE('oc  '),
	kDVDLanguageCodeOromo			= FOUR_CHAR_CODE('om  '),
	kDVDLanguageCodeOriya			= FOUR_CHAR_CODE('or  '),
	kDVDLanguageCodePunjabi			= FOUR_CHAR_CODE('pa  '),
	kDVDLanguageCodePolish			= FOUR_CHAR_CODE('pl  '),
	kDVDLanguageCodePashto			= FOUR_CHAR_CODE('ps  '),
	kDVDLanguageCodePortugese		= FOUR_CHAR_CODE('pt  '),
	kDVDLanguageCodeQuechua			= FOUR_CHAR_CODE('qu  '),
	kDVDLanguageCodeRhaetoRomance	= FOUR_CHAR_CODE('rm  '),
	kDVDLanguageCodeKirundi			= FOUR_CHAR_CODE('rn  '),
	kDVDLanguageCodeRomanian		= FOUR_CHAR_CODE('ro  '),
	kDVDLanguageCodeRussian			= FOUR_CHAR_CODE('ru  '),
	kDVDLanguageCodeKinyarwanda		= FOUR_CHAR_CODE('rw  '),
	kDVDLanguageCodeSanskrit		= FOUR_CHAR_CODE('sa  '),
	kDVDLanguageCodeSindhi			= FOUR_CHAR_CODE('sd  '),
	kDVDLanguageCodeSangro			= FOUR_CHAR_CODE('sg  '),
	kDVDLanguageCodeSerboCroatian	= FOUR_CHAR_CODE('sh  '),
	kDVDLanguageCodeSinghalese		= FOUR_CHAR_CODE('si  '),
	kDVDLanguageCodeSlovak			= FOUR_CHAR_CODE('sk  '),
	kDVDLanguageCodeSlovenian		= FOUR_CHAR_CODE('sl  '),
	kDVDLanguageCodeSamoan			= FOUR_CHAR_CODE('sm  '),
	kDVDLanguageCodeShona			= FOUR_CHAR_CODE('sn  '),
	kDVDLanguageCodeSomali			= FOUR_CHAR_CODE('so  '),
	kDVDLanguageCodeAlbanian		= FOUR_CHAR_CODE('sq  '),
	kDVDLanguageCodeSerbian			= FOUR_CHAR_CODE('sr  '),
	kDVDLanguageCodeSiswati			= FOUR_CHAR_CODE('ss  '),
	kDVDLanguageCodeSesotho			= FOUR_CHAR_CODE('st  '),
	kDVDLanguageCodeSudanese		= FOUR_CHAR_CODE('su  '),
	kDVDLanguageCodeSwedish			= FOUR_CHAR_CODE('sv  '),
	kDVDLanguageCodeSwahili			= FOUR_CHAR_CODE('sw  '),
	kDVDLanguageCodeTamil			= FOUR_CHAR_CODE('ta  '),
	kDVDLanguageCodeTelugu			= FOUR_CHAR_CODE('te  '),
	kDVDLanguageCodeTajik			= FOUR_CHAR_CODE('tg  '),
	kDVDLanguageCodeThai			= FOUR_CHAR_CODE('th  '),
	kDVDLanguageCodeTigrinya		= FOUR_CHAR_CODE('ti  '),
	kDVDLanguageCodeTurkmen			= FOUR_CHAR_CODE('tk  '),
	kDVDLanguageCodeTagalog			= FOUR_CHAR_CODE('tl  '),
	kDVDLanguageCodeSetswana		= FOUR_CHAR_CODE('tn  '),
	kDVDLanguageCodeTonga			= FOUR_CHAR_CODE('to  '),
	kDVDLanguageCodeTurkish			= FOUR_CHAR_CODE('tr  '),
	kDVDLanguageCodeTsonga			= FOUR_CHAR_CODE('ts  '),
	kDVDLanguageCodeTatar			= FOUR_CHAR_CODE('tt  '),
	kDVDLanguageCodeTwi				= FOUR_CHAR_CODE('tw  '),
	kDVDLanguageCodeUkranian		= FOUR_CHAR_CODE('uk  '),
	kDVDLanguageCodeUrdu			= FOUR_CHAR_CODE('ur  '),
	kDVDLanguageCodeUzbek			= FOUR_CHAR_CODE('uz  '),
	kDVDLanguageCodeVietnamese		= FOUR_CHAR_CODE('vi  '),
	kDVDLanguageCodeVolapuk			= FOUR_CHAR_CODE('vo  '),
	kDVDLanguageCodeWolof			= FOUR_CHAR_CODE('wo  '),
	kDVDLanguageCodeXhosa			= FOUR_CHAR_CODE('xh  '),
	kDVDLanguageCodeYoruba			= FOUR_CHAR_CODE('yo  '),
	kDVDLanguageCodeChinese			= FOUR_CHAR_CODE('zh  '),
	kDVDLanguageCodeZulu			= FOUR_CHAR_CODE('zu  ')
};
typedef OSType	DVDLanguageCode;


//-----------------------------------------------------
// DVDAudioExtensionCode - The different possible audio extension codes.
//-----------------------------------------------------
enum {
	kDVDAudioExtensionCodeNotSpecified 		= 0,
	kDVDAudioExtensionCodeNormalCaptions 	= 1,
	kDVDAudioExtensionCodeNVisualImpaired	= 2,
	kDVDAudioExtensionCodeDirectorsComment1	= 3,
	kDVDAudioExtensionCodeDirectorsComment2	= 4
	// 0x05 tp 0x7F reserved
	// 0x80 to 0xFF provider defined
};
typedef OSType	DVDAudioExtensionCode;


//-----------------------------------------------------
// DVDSubpictureExtensionCode - The different possible subpicture extension codes.
//-----------------------------------------------------
enum {
	kDVDSubpictureExtensionCodeNotSpecified 			= 0,
	kDVDSubpictureExtensionCodeCaptionNormalSize 		= 1,
	kDVDSubpictureExtensionCodeCaptionBiggerSize 		= 2,
	kDVDSubpictureExtensionCodeCaption4Children 		= 3,
	kDVDSubpictureExtensionCodeClosedCaptionNormalSize 	= 5,
	kDVDSubpictureExtensionCodeClosedCaptionBiggerSize 	= 6,
	kDVDSubpictureExtensionCodeClosedCaption4Children 	= 7,
	kDVDSubpictureExtensionCodeForcedCaption		 	= 9,
	kDVDSubpictureExtensionDirectorsCommentNormalSize	= 13,
	kDVDSubpictureExtensionDirectorsCommentBiggerSize	= 14,
	kDVDSubpictureExtensionDirectorsComment4Children	= 15
	// 0x10 tp 0x7F reserved
	// 0x80 to 0xFF provider defined
};
typedef OSType	DVDSubpictureExtensionCode;


//-----------------------------------------------------
// DVD Disc ID
//-----------------------------------------------------
typedef	UInt8	DVDDiscID[8];


//-----------------------------------------------------
// DVDRegionCode - The different possible region codes (used for both the disc and the drive).
//-----------------------------------------------------
enum {
	kDVDRegionCodeUninitialized	= 0xff,
	kDVDRegionCode1 			= 0xfe,
	kDVDRegionCode2 			= 0xfd,
	kDVDRegionCode3 			= 0xfb,
	kDVDRegionCode4 			= 0xf7,
	kDVDRegionCode5 			= 0xef,
	kDVDRegionCode6 			= 0xdf,
	kDVDRegionCode7 			= 0xbf,
	kDVDRegionCode8 			= 0x7f

};
typedef UInt32	DVDRegionCode;



//-----------------------------------------------------
// DVDDomainCode - The DVD Domain code...
//-----------------------------------------------------
typedef CF_ENUM(UInt32, DVDDomainCode) {
	kDVDFPDomain				= 0,	// First Play Domain
	kDVDVMGMDomain				= 1,	// Video Manager Menu Domain
	kDVDVTSMDomain				= 2,	// Video Title Set Menu Domain
	kDVDTTDomain				= 3,	// Title Domain
	kDVDSTOPDomain				= 4,	// Stop State
	kDVDAMGMDomain				= 5,	// Audio Manager Menu Domain (DVD-Audio only, not used)
	kDVDTTGRDomain				= 6		// Title Group Domain (DVD-Audio only, not used)
};



//-----------------------------------------------------
// DVDUOPCode - The DVD UOP code(s)...
//-----------------------------------------------------
enum {
	kDVDUOPTimePlaySearch			= 0x00000001,
	kDVDUOPPTTPlaySearch			= 0x00000002,
	kDVDUOPTitlePlay				= 0x00000004,
	kDVDUOPStop						= 0x00000008,
	kDVDUOPGoUp						= 0x00000010,
	kDVDUOPTimePTTSearch			= 0x00000020,
	kDVDUOPPrevTopPGSearch			= 0x00000040,
	kDVDUOPNextPGSearch				= 0x00000080,
	kDVDUOPForwardScan				= 0x00000100,
	kDVDUOPBackwardScan				= 0x00000200,
	kDVDUOPMenuCallTitle			= 0x00000400,
	kDVDUOPMenuCallRoot				= 0x00000800,
	kDVDUOPMenuCallSubPicture		= 0x00001000,
	kDVDUOPMenuCallAudio			= 0x00002000,
	kDVDUOPMenuCallAngle			= 0x00004000,
	kDVDUOPMenuCallPTT				= 0x00008000,
	kDVDUOPResume					= 0x00010000,
	kDVDUOPButton					= 0x00020000,
	kDVDUOPStillOff					= 0x00040000,
	kDVDUOPPauseOn					= 0x00080000,
	kDVDUOPAudioStreamChange		= 0x00100000,
	kDVDUOPSubPictureStreamChange	= 0x00200000,
	kDVDUOPAngleChange				= 0x00400000,
	kDVDUOPKaraokeModeChange		= 0x00800000,
	kDVDUOPVideoModeChange			= 0x01000000,
	kDVDUOPScanOff					= 0x02000000,
	kDVDUOPPauseOff					= 0x04000000
};
typedef UInt32	DVDUOPCode;



//-----------------------------------------------------
// DVDEventCode - The different event a client can register for to get notified (return value: UInt32)
//-----------------------------------------------------
typedef CF_ENUM(UInt32, DVDEventCode) {
	kDVDEventTitle				= 1, 		// Returned value1: Title
	kDVDEventPTT				= 2, 		// Returned value1: Chapter
	kDVDEventValidUOP			= 3,		// Returned value1: UOP code mask (DVDUOPCode)
	kDVDEventAngle				= 4,		// Returned value1: StreamID
	kDVDEventAudioStream		= 5,		// Returned value1: StreamID
	kDVDEventSubpictureStream	= 6,		// Returned value1: streamID  / (value2 != 0): visible
	kDVDEventDisplayMode		= 7,		// Returned value1: DVDAspectRatio
	kDVDEventDomain				= 8,		// Returned value1: DVDDomainCode
	kDVDEventBitrate			= 9,		// Returned value1: Bits / sec
	kDVDEventStill				= 10,		// Returned value1: On (1) - Off (0)
	kDVDEventPlayback			= 11,		// Returned value1: DVDState
	kDVDEventVideoStandard		= 12,		// Returned value1: DVDFormat
	kDVDEventStreams			= 13,		// Returned value1: None (trigger for general stream change)
	kDVDEventScanSpeed			= 14,		// Returned value1: Speed (1x,2x,3x,...)
	kDVDEventMenuCalled			= 15,		// Returned value1: DVDMenu
	kDVDEventParental			= 16,		// Returned value1: parental level number
	kDVDEventPGC				= 17,		// Returned value1: PGC number
	kDVDEventGPRM				= 18,		// Returned value1: GPRM index / value2: data 
	kDVDEventRegionMismatch		= 19,		// Returned value1: disc region
	kDVDEventTitleTime			= 20,		// Returned value1: elapsed time / value2: duration of title [ms] 
	kDVDEventSubpictureStreamNumbers = 21,	// Returned value1: number of subpicture streams in title
	kDVDEventAudioStreamNumbers = 22,		// Returned value1: number of audio streams in title
	kDVDEventAngleNumbers 		= 23,		// Returned value1: number of angles in title
	kDVDEventError		 		= 24,		// Returned value1: DVDErrorCode
    kDVDEventCCInfo				= 25,		// Returned value1: cc event opcode, value2: cc event data
	kDVDEventChapterTime		= 26		// Returned value1: elapsed time / value2: duration of current chapter [ms]
};

//-----------------------------------------------------
// DVDEventValue - The value for a registered event
//-----------------------------------------------------
typedef unsigned long	DVDEventValue;

//-----------------------------------------------------
// DVDEventCallBackRef - The reference to a registered event callback
//-----------------------------------------------------
typedef void *	DVDEventCallBackRef;



//-----------------------------------------------------
// Callback definitions
//
//	WARNING:	The callbaks will be called from a different thread. Do not attempt to draw directly from the callback.
//				Store the information and do any actually drawing when you are back in your thread.
//
//	DVDFatalErrCallBackFunctionPtr -	Called when the playback framework encountered an unrecoverable error.
//										inRefCon is the refcon passed in when the callback was registered.
//	DVDEventCallBackFunctionPtr -		Called when the playback framework encountered an event change.
//										Arguments are the actual event, the specific data for that event (title num, angle, etc.),
//										and inRefCon is the refcon passed in when the callback was registered.
//										If the call was registered for multiple events, each event will be called separately.
//-----------------------------------------------------
typedef void	(*DVDFatalErrCallBackFunctionPtr)(DVDErrorCode inError, void *inRefCon);
typedef void	(*DVDEventCallBackFunctionPtr)(DVDEventCode inEventCode, DVDEventValue inEventValue1, DVDEventValue inEventValue2, void *inRefCon);




#pragma export on

//-----------------------------------------------------
//	API Calls
//-----------------------------------------------------

//-----------------------------------------------------
//	Set up and tear down:
//
//	You must initialize the playback framework before using it and dispose of it when done.
//	Usually called upon application startup and quit. Only one application can use the playback framework 
//	at a time.
//	  
//	DVDInitialize	-	Call when preparing for playback. Usually when the application is initializing.
//						Returns an error of kDVDErrorInitializingLib if the playback framework is already being used.
//	DVDDispose		- 	Call when completely done with playback. Usually when the application is quitting.
//-----------------------------------------------------
extern	OSStatus	DVDInitialize()																			    API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDDispose()																				API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);




//-----------------------------------------------------
//	Opening and closing media:
//
//	These calls allow opening media from disc (DVDOpenMediaVolume) or from a VIDEO_TS
//	folder (DVDOpenMediaFile).  You must close any currently open disc or file before opening
//	a new one.  For both Open calls you must provide an CFURLRef - FSRef now deprecated -  to the VIDEO_TS folder.
//	
//	DVDIsValidMediaRef			- 	Returns true if the FSRef points to a valid media layout.
//	DVDIsValidMediaURL			- 	Returns true if the CFURLRef points to a valid media layout.
//	DVDHasMedia					- 	Returns true if the playback framework has media to play and
//									the framework had recveived an Open call on the media.
//	DVDOpenMediaFile			- 	Opens a VIDEO_TS folder (can be on a hard drive or a dvd disc).
//	DVDOpenMediaFileWithURL		- 	Opens a VIDEO_TS folder with a CFURLRef (can be on a hard drive or a dvd disc).
//	DVDCloseMediaFile			- 	Closes a previously opened VIDEO_TS folder.
//	DVDOpenMediaVolume			- 	Opens a DVD disc for playback.
//	DVDOpenMediaVolumeWithURL	- 	Opens a DVD disc for playback with a CFURLRef.
//	DVDCloseMediaVolume			-	Closes a previously opened DVD disc.
//-----------------------------------------------------
extern	OSStatus	DVDIsValidMediaRef(FSRef *inRef,Boolean *outIsValid)										API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDIsValidMediaURL(CFURLRef inRef,Boolean *outIsValid)										API_DEPRECATED("No longer supported", macos(10.5, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDHasMedia(Boolean *outHasMedia)															API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDOpenMediaFile(FSRef *inFile)																API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDOpenMediaFileWithURL(CFURLRef inFile)													API_DEPRECATED("No longer supported", macos(10.5, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDCloseMediaFile()																			API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDOpenMediaVolume(FSRef *inVolume)															API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDOpenMediaVolumeWithURL(CFURLRef inVolume)												API_DEPRECATED("No longer supported", macos(10.5, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDCloseMediaVolume()																		API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);




//-----------------------------------------------------
//	Video device:
//
//	These calls are used to get and set the screen used for playback typical for Carbon.
//
//	DVDIsSupportedDevice	-	Returns TRUE if this device is known to support DVD playback.  Could 
//							 	return FALSE for a device capable DVD playback but using a different 
//								video driver than the one currently in use.  DVDSetVideoPort must have 
//								been previously called with a valid port for this call to work properly.
//	DVDSwitchToDevice		- 	Switches active to the new playback device. It will return with an error
//								if the new device is not suppported and keep the old device
//	DVDSetVideoDevice		- 	Set the device to playback video on.
//	DVDGetVideoDevice		- 	Returns the device video playback is on.
//-----------------------------------------------------
#if !__LP64__
extern	OSStatus	DVDIsSupportedDevice(GDHandle inDevice,Boolean* outSupported)					AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;
extern	OSStatus	DVDSwitchToDevice(GDHandle newDevice,Boolean* outSupported)						AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;
extern	OSStatus	DVDSetVideoDevice(GDHandle inDevice)											AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;
extern	OSStatus	DVDGetVideoDevice(GDHandle* outDevice)											AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;
#endif


//-----------------------------------------------------
//	Video display:
//
//	These calls are used to get and set the screen used for playback typical for Appkit/CoreGraphics.
//
//	DVDIsSupportedDisplay	-	Returns TRUE if this display is known to support DVD playback.  Could 
//							 	return FALSE for a display capable DVD playback but using a different 
//								video driver than the one currently in use.  DVDSetVideoWindowID must have 
//								been previously called with a valid window for this call to work properly.
//	DVDSwitchToDisplay		- 	Switches active to the new playback display. It will return with an error
//								if the new display is not suppported and keep the old display
//	DVDSetVideoDisplay		- 	Set the display to playback video on.
//	DVDGetVideoDisplay		- 	Returns the display video playback is on.
//-----------------------------------------------------
extern	OSStatus	DVDIsSupportedDisplay(CGDirectDisplayID inDisplay, Boolean* outSupported)		API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDSwitchToDisplay(CGDirectDisplayID newDisplay, Boolean* outSupported)			API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDSetVideoDisplay(CGDirectDisplayID inDisplay)									API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDGetVideoDisplay(CGDirectDisplayID *outDisplay)								API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);



//-----------------------------------------------------
//	Video:
//
//	These calls are used to get and set video related information.
//
//	DVDSetVideoPort			-	Sets the grafport to play into and causes the appropriate
//							 	video driver to be loaded.  Passing NULL causes the
//								low-level DVD driver to close.
//	DVDGetVideoPort			- 	Returns the grafport the playback framework is set to.
//	DVDSetVideoWindowID		-	Sets the window id to play into and causes the appropriate
//							 	video driver to be loaded.  Passing NULL causes the
//								low-level DVD driver to close.
//	DVDGetVideoWindowID		- 	Returns the window id the playback framework is set to.
//	DVDSetVideoBounds		- 	Sets (in port coordinates) the rect to play the video in.
//	DVDGetVideoBounds		- 	Returns (in port coordinates) the rect used to play video.
//	DVDGetVideoKeyColor		- 	Returns the key color used but the video driver.
//	DVDGetNativeVideoSize	- 	Returns the default width and height for the title.
//	DVDGetAspectRatio		- 	Returns the aspect ratio of the current title. Use this 
//							  	with the native video size to calculate the video bounds.
//	DVDSetAspectRatio		- 	Set the aspect ratio to use for the current title.
//	DVDGetFormatStandard	- 	Returns the format of the title.
//
//	DVDSetVideoWindowRef	- 	Sets the window to play into and causes the appropriate
//							 	video driver to be loaded.  Passing NULL causes the
//								low-level DVD driver to close.
//	DVDGetVideoWindowRef	- 	Returns the window the playback framework is set to.
//	DVDSetVideoCGBounds		- 	Sets (in window root view coordinates) the rect to play the video in.
//	DVDGetVideoCGBounds		- 	Returns (in window root view coordinates) the rect used to play video.
//-----------------------------------------------------
#if !__LP64__
extern	OSStatus	DVDSetVideoPort(CGrafPtr inVidPort)															AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;
extern	OSStatus	DVDGetVideoPort(CGrafPtr* outVidPort)														AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;
#endif
extern	OSStatus	DVDSetVideoWindowID(UInt32 inVidWindowID)													API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDGetVideoWindowID(UInt32 *outVidWindowID)													API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
#if !__LP64__
extern	OSStatus	DVDSetVideoBounds(Rect *inPortRect)															AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;
extern	OSStatus	DVDGetVideoBounds(Rect *outPortRect)														AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;
extern	OSStatus	DVDGetVideoKeyColor(RGBColor *outKeyColor)													AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;
#endif
extern	OSStatus	DVDGetNativeVideoSize(UInt16 *outWidth, UInt16 *outHeight)									API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDGetAspectRatio(DVDAspectRatio *outRatio)													API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDSetAspectRatio(DVDAspectRatio inRatio)													API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDGetFormatStandard(DVDFormat *outFormat)													API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);

extern	OSStatus	DVDSetVideoWindowRef(WindowRef DVD_NULLABLE inWindowRef)									API_DEPRECATED("No longer supported", macos(10.5, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDGetVideoWindowRef(WindowRef DVD_NONNULL * DVD_NONNULL outWindowRef)						API_DEPRECATED("No longer supported", macos(10.5, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDSetVideoCGBounds(CGRect *inRect)															API_DEPRECATED("No longer supported", macos(10.5, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDGetVideoCGBounds(CGRect *outRect)														API_DEPRECATED("No longer supported", macos(10.5, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);




//-----------------------------------------------------
//	Audio:
//
//	These calls are used to get and set audio related information.
//	
//	DVDGetAudioStreamFormat			-	Gets the current audio format (AC3,for example).
//	DVDGetAudioStreamFormatByStream	-	Gets the audio format for selected stream (1,2,3...).
//
//	DVDGetAudioOutputModeCapabilities	- returns the current possible audio output mode possibilities
//										  outModes returns a mask of supported modes
//	DVDSetAudioOutputMode				- set the audio mode
//	DVDGetAudioOutputMode				- gets the current audio mode setting
//	DVDGetSPDIFDataOutDeviceCount		- gets the number of SPDIF capable audio devices
//	DVDGetSPDIFDataOutDeviceCFName		- gets the name - CFStringRef - of a SPDIF capable audio device
//	DVDSetSPDIFDataOutDevice			- selects a SPDIF capable audio device
//	DVDGetSPDIFDataOutDevice			- returns the selected SPDIF capable audio device
//-----------------------------------------------------
extern	OSStatus	DVDGetAudioStreamFormat(DVDAudioFormat* DVD_NULLABLE outFormat, UInt32* DVD_NULLABLE outBitsPerSample, UInt32* DVD_NULLABLE outSamplesPerSecond, UInt32* DVD_NULLABLE outChannels)								API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDGetAudioStreamFormatByStream(UInt32 inStreamNum, DVDAudioFormat* DVD_NULLABLE outFormat, UInt32* DVD_NULLABLE outBitsPerSample, UInt32* DVD_NULLABLE outSamplesPerSecond, UInt32* DVD_NULLABLE outChannels)	API_DEPRECATED("No longer supported", macos(10.4, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);

extern	OSStatus	DVDGetAudioOutputModeCapabilities(DVDAudioMode *outModes)										API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDSetAudioOutputMode(DVDAudioMode inMode)														API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDGetAudioOutputMode(DVDAudioMode *outMode)													API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDGetSPDIFDataOutDeviceCount(UInt32 *outCount)													API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDGetSPDIFDataOutDeviceCFName(UInt32 inIndex, CFStringRef DVD_NONNULL * DVD_NONNULL outName)	API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDSetSPDIFDataOutDevice(UInt32 inIndex)														API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDGetSPDIFDataOutDevice(UInt32 *outIndex)														API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);



//-----------------------------------------------------
//	Time:
//
//	These calls are used to get and set the current playback position relative to the 
//	beginning or end of the title.
//	
//	DVDSetTime	-	Sets the current playback position in the current title based on a time 
//				  	position in seconds relative to the time code (elapsed,remaining).
//	DVDGetTime	- 	Gets the current playback position in the current title in seconds relative 
//				  	to the requested time code (elapsed,remaining).
//-----------------------------------------------------
extern	OSStatus	DVDSetTime(DVDTimeCode inTimeCode,DVDTimePosition inTime,UInt16 inFrames)					API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDGetTime(DVDTimeCode inTimeCode,DVDTimePosition *outTime,UInt16 *outFrames)				API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);




//-----------------------------------------------------
//	Miscellaneous:
//	
//	DVDGetState		- 	Returns the current play state of the DVDPlayback framework.
//	DVDIdle			- 	Allows the framework to get a consistent time to process at. (Might be removed in the future).
//	DVDUpdateVideo	- 	Forces the video to be updated.
//-----------------------------------------------------
extern	OSStatus	DVDGetState(DVDState *outState)																API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDIdle()																					API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDUpdateVideo()																			API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);




//-----------------------------------------------------
//	Playback control:
//	
//	DVDIsPlaying	- 	Returns true if the framework has media and is playing (even if paused).
//	DVDIsPaused		- 	Returns true if the framework has media and is paused.
//	DVDPlay			- 	Starts playing the media.
//	DVDPause		- 	Pauses the media if currently playing.
//	DVDResume		-	Starts playing if currently paused.
//	DVDStop			- 	Stops if playing.
//	DVDScan			- 	Fast forwards or rewinds depending on DVDScanDirection at the speed
//						specified in DVDScanRate.
//	DVDGetScanRate	- 	Returns the current scan direction and rate.
//	DVDStepFrame	- 	Steps one frame in the direction specified in DVDScanDirection.
//						Currently only supports kDVDScanDirectionForward.
//-----------------------------------------------------
extern	OSStatus	DVDIsPlaying(Boolean *outIsPlaying)															API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDIsPaused(Boolean *outIsPaused)															API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDPlay()																					API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDPause()																					API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDResume()																					API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDStop()																					API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDScan(DVDScanRate inRate,DVDScanDirection inDirection)									API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);	// fast forward, rewind, slow mo
extern	OSStatus	DVDGetScanRate(DVDScanRate* DVD_NULLABLE outRate, DVDScanDirection* DVD_NULLABLE outDirection)	API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);	// get the current play rate (fast forward, etc)
extern	OSStatus	DVDStepFrame(DVDScanDirection inDirection)													API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);




//-----------------------------------------------------
//	Volume:
//
//	These calls are used to adjust the playback volume. The playback volume is relative
//	to the current system volume.
//
//	DVDIsMuted				-	Returns true if the playback volume is currently muted.
//	DVDMute					- 	Toggles the mute setting on or off.
//	DVDSetAudioVolume		- 	Sets the playback volume (0 - 255).
//	DVDGetAudioVolume		- 	Gets the current playback volume (0 - 255).
//	DVDGetAudioVolumeInfo	- 	Gets the playback volume info (minimum, maximum, and current volume).
//-----------------------------------------------------
extern	OSStatus	DVDIsMuted(Boolean *outIsMuted)																API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDMute(Boolean inMute)																		API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDSetAudioVolume(UInt16 inVolume)															API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDGetAudioVolume(UInt16 *outVolume)														API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDGetAudioVolumeInfo(UInt16* DVD_NULLABLE outMinVolume, UInt16* DVD_NULLABLE outCurVolume, UInt16* DVD_NULLABLE outMaxVolume)	API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos); // can pass null




//-----------------------------------------------------
//	DVD Menu Navigation:
//	
//	DVDHasMenu				-	Returns if input menu type is available.
//	DVDIsOnMenu				-	Are we currently on a menu, and if so, which one.
//	DVDGoToMenu				- 	Jump to a particular menu (Root Menu,Sub Picture Menu, etc.).
//	DVDReturnToTitle		- 	Returns from the menu back to the current position within the title.
//	DVDGoBackOneLevel		- 	If in a sub menu, move back up one level.
//	DVDDoUserNavigation		-	Allows the user to navigate between menu buttons. This is usually done
//								using keyboard keys (arrow keys to move and Enter key to choose a menu item).
//	DVDDoMenuClick			-	If the point (in port coordinates) coincides with a menu button, it will be selected.
//	DVDDoMenuMouseOver		-	If the point (in port coordinates) coincides with a menu button, it will be hightlighted
//								and it's index returned in outIndex.
//	DVDDoButtonActivate		-	selects and activates button by index.
//	DVDGetButtoninfo		-	returns current info of all available buttons in current title/domain/content.
//	DVDGetButtonPosition	-	returns position/auto actiuon of button.
//	
//	DVDDoMenuCGClick		-	If the point (in window root view coordinates) coincides with a menu button, it will be selected.
//	DVDDoMenuCGMouseOver	-	If the point (in window root view coordinates) coincides with a menu button, it will be hightlighted
//-----------------------------------------------------
extern	OSStatus	DVDHasMenu(DVDMenu inMenu, Boolean *outHasMenu)												API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDIsOnMenu(Boolean* DVD_NULLABLE outOnMenu, DVDMenu* DVD_NULLABLE outMenu)					API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDGoToMenu(DVDMenu inMenu)																	API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDReturnToTitle()																			API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDGoBackOneLevel()																			API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDDoUserNavigation(DVDUserNavigation inNavigation)											API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
#if !__LP64__
extern	OSStatus	DVDDoMenuClick(Point inPortPt, SInt32 *outIndex)											AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;
extern	OSStatus	DVDDoMenuMouseOver(Point inPortPt, SInt32 *outIndex)										AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;
#endif
extern	OSStatus	DVDDoButtonActivate(SInt32 inIndex)															API_DEPRECATED("No longer supported", macos(10.4, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);

extern	OSStatus	DVDGetButtoninfo(UInt32* DVD_NULLABLE numberOfButtons,
									 UInt32* DVD_NULLABLE selectedButton,
									 UInt32* DVD_NULLABLE forcedActivateButton,
									 UInt32* DVD_NULLABLE userButtonOffset,
									 UInt32* DVD_NULLABLE numberOfUserButtons)									API_DEPRECATED("No longer supported", macos(10.4, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDGetButtonPosition(UInt32 index, CGRect *outRect, UInt32 *autoAction)						API_DEPRECATED("No longer supported", macos(10.4, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);

extern	OSStatus	DVDDoMenuCGClick(CGPoint *inPt, SInt32 *outIndex)											API_DEPRECATED("No longer supported", macos(10.5, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDDoMenuCGMouseOver(CGPoint *inPt, SInt32 *outIndex)										API_DEPRECATED("No longer supported", macos(10.5, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);



//-----------------------------------------------------
//	Media:
//	These calls are used to get and set audio related information.
//	
//	DVDGetMediaUniqueID		- returns a unique identifier for the media to play
//	DVDGetMediaVolumeName	- returns the volume name of the current disc/media
//	DVDGetMediaVolumeCFName	- returns the volume name of the current disc/media as a CFSring
//-----------------------------------------------------
extern	OSStatus	DVDGetMediaUniqueID(DVDDiscID outDiscID)													API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDGetMediaVolumeName(char* DVD_NONNULL * DVD_NONNULL outDiscVolumeName)					API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDGetMediaVolumeCFName(CFStringRef DVD_NONNULL * DVD_NONNULL outDiscVolumeCFName)			API_DEPRECATED("No longer supported", macos(10.4, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);



//-----------------------------------------------------
//	Title:
//	
//	DVDSetTitle		-	Set the title to play (1 - 99).
//	DVDGetTitle		- 	Gets the current title.
//	DVDGetNumTitles	- 	Gets the number of titles available on the media.
//-----------------------------------------------------
extern	OSStatus	DVDSetTitle(UInt16 inTitleNum)																API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDGetTitle(UInt16 *outTitleNum)															API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDGetNumTitles(UInt16 *outNumTitles)														API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);




//-----------------------------------------------------
//	Chapters:
//
// 	These calls are made within the context of the currently playing title.
//	
//	DVDHasPreviousChapter	-	Returns true if there is a chapter before the current chapter.
//	DVDHasNextChapter		-	Returns true if there is a chapter after the current chapter.
//	DVDSetChapter			- 	Sets the chapter to play.
//	DVDGetChapter			- 	Gets the current chapter.
//	DVDGetNumChapters		- 	Gets the number of chapters in the current title.
//	DVDPreviousChapter		- 	Sets to the previous chapter on the current title.
//	DVDNextChapter			-	Sets to the next chapter on the current title.
//-----------------------------------------------------
extern	OSStatus	DVDHasPreviousChapter(Boolean *outHasChapter)												API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDHasNextChapter(Boolean *outHasChapter)													API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDSetChapter(UInt16 inChapterNum)															API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDGetChapter(UInt16 *outChapterNum)														API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDGetNumChapters(UInt16 inTitleNum, UInt16 *outNumChapters)								API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDPreviousChapter()																		API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDNextChapter()																			API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);




//-----------------------------------------------------
//	Angles:
//
// 	These calls are made within the context of the currently playing title.
//	
//	DVDSetAngle		-	Sets the angle to display.
//	DVDGetAngle		-	Gets the angle displayed.
//	DVDGetNumAngles	-	Gets the number of angles currently available.
//-----------------------------------------------------
extern	OSStatus	DVDSetAngle(UInt16 inAngleNum)																API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDGetAngle(UInt16 *outAngleNum)															API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDGetNumAngles(UInt16 *outNumAngles)														API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);




//-----------------------------------------------------
//	SubPictures:
//
// 	These calls are made within the context of the currently playing title.
//	
//	DVDDisplaySubPicture		-	Turns the displaying of subpictures on or off.
//	DVDIsDisplayingSubPicture	- 	Returns true if subpictures are currently being displayed.
//	DVDSetSubPictureStream		- 	Sets the sub picture stream to display.
//	DVDGetSubPictureStream		-	Gets the sub picture stream being displayed.
//	DVDGetNumSubPictureStreams	-	Gets the number of sub pictures streams currently available.
//-----------------------------------------------------
extern	OSStatus	DVDDisplaySubPicture(Boolean inDisplay)											API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDIsDisplayingSubPicture(Boolean *outDisplayingSubPicture)						API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDSetSubPictureStream(UInt16 inStreamNum)										API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDGetSubPictureStream(UInt16 *outStreamNum)									API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDGetNumSubPictureStreams(UInt16 *outNumStreams)								API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);




//-----------------------------------------------------
//	Audio Stream:
//
// 	These calls are made within the context of the currently playing title.
//	
//	DVDSetAudioStream		-	Sets the audio stream to use.
//	DVDGetAudioStream		-	Gets the audio stream currently being used.
//	DVDGetNumAudioStreams	-	Gets the number of audio streams currently available.
//-----------------------------------------------------
extern	OSStatus	DVDSetAudioStream(UInt16 inStreamNum)											API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDGetAudioStream(UInt16 *outStreamNum)											API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDGetNumAudioStreams(UInt16 *outNumStreams)									API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);




//-----------------------------------------------------
//	Language Codes:
//	
//	The Set calls set the default language codes to be used if the user does not specifically change them. The
//	language code decides which stream will be used.
//	The Get calls return the language code in use or to be used by a particular stream.
//	
//	DVDSetDefaultSubPictureLanguageCode		-	Sets the default subpicture language and extension to be used 
//												when subpictures are turned on.
//	DVDGetSubPictureLanguageCode			- 	Returns the subpicture language code and extension to be used 
//												when subpictures are on.
//	DVDGetSubPictureLanguageCodeByStream	-	Returns the subpicture language code and extension for a 
//												particular subpicture stream.
//	
//	DVDSetDefaultAudioLanguageCode			-	Sets the default audio language code and extension to be used.
//	DVDGetAudioLanguageCode					- 	Returns the audio language code and extension currently used.
//	DVDGetAudioLanguageCodeByStream			- 	Returns the audio language code and extension for a particular stream.
//	
//	DVDSetDefaultMenuLanguageCode			-	Sets the default menu language code to be used.
//	DVDGetMenuLanguageCode					-	Returns the menu language code being used.
//-----------------------------------------------------
extern	OSStatus	DVDSetDefaultSubPictureLanguageCode(DVDLanguageCode inCode, DVDSubpictureExtensionCode inExtension)								API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDGetSubPictureLanguageCode(DVDLanguageCode* DVD_NULLABLE outCode, DVDSubpictureExtensionCode* DVD_NULLABLE outExtension)		API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDGetSubPictureLanguageCodeByStream(UInt16 inStreamNum, DVDLanguageCode* DVD_NULLABLE outCode, DVDSubpictureExtensionCode* DVD_NULLABLE outExtension)	API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);

extern	OSStatus	DVDSetDefaultAudioLanguageCode(DVDLanguageCode inCode, DVDAudioExtensionCode inExtension)														API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDGetAudioLanguageCode(DVDLanguageCode* DVD_NULLABLE outCode, DVDAudioExtensionCode* DVD_NULLABLE outExtension)								API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDGetAudioLanguageCodeByStream(UInt16 inStreamNum, DVDLanguageCode* DVD_NULLABLE outCode, DVDAudioExtensionCode* DVD_NULLABLE outExtension)	API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);

extern	OSStatus	DVDSetDefaultMenuLanguageCode(DVDLanguageCode inCode)																			API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDGetMenuLanguageCode(DVDLanguageCode *outCode)																				API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);



//-----------------------------------------------------
//	Bookmarks:
//	These calls are used to get and set bookmark information.
//	
//	DVDGetBookmark				- returns a bookmark (pass 0 as outBookMarkData to aquire data length)
//	DVDGotoBookmark				- goto a saved bookmark
//	
//	DVDGetLastPlayBookmark		- returns last play bookmark after 1st Stop command
//	DVDSetLastPlayBookmark		- sets last play bookmark for next Play command
//	DVDClearLastPlayBookmark	- clears last play bookmark for next Play command
//-----------------------------------------------------
extern	OSStatus	DVDGetBookmark(void* DVD_NULLABLE outBookMarkData, UInt32 *ioBookMarkDataSize)			API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDGotoBookmark(void *inBookMarkData, UInt32 inBookMarkDataSize)						API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);

extern	OSStatus	DVDGetLastPlayBookmark(void* DVD_NULLABLE outBookMarkData, UInt32 *ioBookMarkDataSize)	API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDSetLastPlayBookmark(void *inBookMarkData, UInt32 inBookMarkDataSize)					API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDClearLastPlayBookmark()																API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);

 

//-----------------------------------------------------
//	Region Codes:
//
//	The drive region code must match the DVD disc region code. These calls allow getting the disc region code
//	and getting or setting the drive region code. 
//	NOTE:	The drive region code is stored in the drive and can only be set a total of 5 times. 
//		  	On the last time, the drive will be permanently locked to that region code.
//	
//	DVDGetDiscRegionCode	-	Returns the region codes available on the disc (can be more than one).
//	DVDGetDriveRegionCode	-	Returns the region code the drive is set to and how many changes are left.
//	DVDSetDriveRegionCode	-	Sets the drive region code (requires user authentication). 
//-----------------------------------------------------	
extern	OSStatus	DVDGetDiscRegionCode(DVDRegionCode *outCode)											API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDGetDriveRegionCode(DVDRegionCode* DVD_NULLABLE outCode, SInt16* DVD_NULLABLE outNumberChangesLeft)	API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDSetDriveRegionCode(DVDRegionCode inCode, AuthorizationRef inAuthorization)			API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);




//-----------------------------------------------------
//	Features:
//
//	DVDEnableWebAccess	-	Turns DVD@ccess support on or off.
//	DVDGetGPRMValue		-	Returns current value of a GPRM register [index:0...16]
//-----------------------------------------------------
extern	OSStatus	DVDEnableWebAccess(Boolean inEnable)													API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDGetGPRMValue(UInt32 index, UInt32 *value)											API_DEPRECATED("No longer supported", macos(10.4, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);



//-----------------------------------------------------
//	Call Backs:
//
//	DVDSetFatalErrorCallBack		-	Required. Allows the framework to return an unrecoverable error.
//										After receiving the fatal error, the framework can not continue, but
//										must still be properly released.
//	DVDRegisterEventCallBack		-	Optional. Allows the client to register to get notified about DVD playback changes.
//										More than one call back can be registered and multiple events can be registered per callback.
//	DVDUnregisterEventCallBack		-	Unregister an event callback.
//	DVDIsRegisteredEventCallBack	-	Check if event callback is already registered.
//
//	DVDSetTimeEventRate				-	Sets the rate of the time DVD event "kDVDEventTime"; default:900 ms.
//	DVDGetTimeEventRate				-	Gets the rate of the time DVD event.
//
//-----------------------------------------------------
extern	OSStatus	DVDSetFatalErrorCallBack(DVDFatalErrCallBackFunctionPtr inCallBackProc, void* DVD_NULLABLE inRefCon)		API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);

extern	OSStatus	DVDRegisterEventCallBack(DVDEventCallBackFunctionPtr inCallBackProc, DVDEventCode* inCode, UInt32 inCodeCount, void* DVD_NULLABLE inRefCon, DVDEventCallBackRef DVD_NONNULL * DVD_NONNULL outCallBackID)	API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDUnregisterEventCallBack(DVDEventCallBackRef inCallBackID)												API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	Boolean		DVDIsRegisteredEventCallBack(DVDEventCallBackRef inCallBackID)												API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);

extern	OSStatus	DVDSetTimeEventRate(UInt32 inMilliseconds)																	API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDGetTimeEventRate(UInt32 *outMilliseconds)																API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);




//-----------------------------------------------------
//	Sleep:
//
//	The client must register for sleep notifications with the system so that it can notify the
//	framework of sleep and wake notifications.
//
//	DVDSleep	- Call when system is putting machine to sleep so playback information can be saved.
//	DVDWakeUp	- Call when system is waking up so playback information can be reset.
//-----------------------------------------------------
extern	OSStatus	DVDSleep(void)																				API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);
extern	OSStatus	DVDWakeUp(void)																				API_DEPRECATED("No longer supported", macos(10.3, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);



#pragma export reset


#ifdef __cplusplus
}
#endif

DVD_ASSUME_NONNULL_END



#endif /* __DVDPLAYBACK__ */

