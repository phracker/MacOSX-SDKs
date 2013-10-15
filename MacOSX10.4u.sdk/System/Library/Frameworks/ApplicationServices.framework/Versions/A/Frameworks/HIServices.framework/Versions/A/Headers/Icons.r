/*
     File:       Icons.r
 
     Contains:   Icon Utilities and Icon Services Interfaces.
 
     Version:    HIServices-169~651
 
     Copyright:  © 1990-2006 by Apple Computer, Inc. All rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

#ifndef __ICONS_R__
#define __ICONS_R__

#ifndef __QUICKDRAW_R__
#include <QD/Quickdraw.r>
#endif

#ifndef __CORESERVICES_R__
#include <CoreServices/CoreServices.r>
#endif

#define kGenericDocumentIconResource 	(-4000)
#define kGenericStationeryIconResource 	(-3985)
#define kGenericEditionFileIconResource  (-3989)
#define kGenericApplicationIconResource  (-3996)
#define kGenericDeskAccessoryIconResource  (-3991)
#define kGenericFolderIconResource 		(-3999)
#define kPrivateFolderIconResource 		(-3994)
#define kFloppyIconResource 			(-3998)
#define kTrashIconResource 				(-3993)
#define kGenericRAMDiskIconResource 	(-3988)
#define kGenericCDROMIconResource 		(-3987)

#define kDesktopIconResource 			(-3992)
#define kOpenFolderIconResource 		(-3997)
#define kGenericHardDiskIconResource 	(-3995)
#define kGenericFileServerIconResource 	(-3972)
#define kGenericSuitcaseIconResource 	(-3970)
#define kGenericMoverObjectIconResource  (-3969)

#define kGenericPreferencesIconResource  (-3971)
#define kGenericQueryDocumentIconResource  (-16506)
#define kGenericExtensionIconResource 	(-16415)
#define kSystemFolderIconResource 		(-3983)
#define kHelpIconResource 				(-20271)
#define kAppleMenuFolderIconResource 	(-3982)

#define genericDocumentIconResource 	(-4000)
#define genericStationeryIconResource 	(-3985)
#define genericEditionFileIconResource 	(-3989)
#define genericApplicationIconResource 	(-3996)
#define genericDeskAccessoryIconResource  (-3991)
#define genericFolderIconResource 		(-3999)
#define privateFolderIconResource 		(-3994)
#define floppyIconResource 				(-3998)
#define trashIconResource 				(-3993)
#define genericRAMDiskIconResource 		(-3988)
#define genericCDROMIconResource 		(-3987)
#define desktopIconResource 			(-3992)
#define openFolderIconResource 			(-3997)
#define genericHardDiskIconResource 	(-3995)
#define genericFileServerIconResource 	(-3972)
#define genericSuitcaseIconResource 	(-3970)
#define genericMoverObjectIconResource 	(-3969)
#define genericPreferencesIconResource 	(-3971)
#define genericQueryDocumentIconResource  (-16506)
#define genericExtensionIconResource 	(-16415)
#define systemFolderIconResource 		(-3983)
#define appleMenuFolderIconResource 	(-3982)

#define kStartupFolderIconResource 		(-3981)
#define kOwnedFolderIconResource 		(-3980)
#define kDropFolderIconResource 		(-3979)
#define kSharedFolderIconResource 		(-3978)
#define kMountedFolderIconResource 		(-3977)
#define kControlPanelFolderIconResource  (-3976)
#define kPrintMonitorFolderIconResource  (-3975)
#define kPreferencesFolderIconResource 	(-3974)
#define kExtensionsFolderIconResource 	(-3973)
#define kFontsFolderIconResource 		(-3968)
#define kFullTrashIconResource 			(-3984)

#define startupFolderIconResource 		(-3981)
#define ownedFolderIconResource 		(-3980)
#define dropFolderIconResource 			(-3979)
#define sharedFolderIconResource 		(-3978)
#define mountedFolderIconResource 		(-3977)
#define controlPanelFolderIconResource 	(-3976)
#define printMonitorFolderIconResource 	(-3975)
#define preferencesFolderIconResource 	(-3974)
#define extensionsFolderIconResource 	(-3973)
#define fontsFolderIconResource 		(-3968)
#define fullTrashIconResource 			(-3984)

#define kAlignNone 						0x00
#define kAlignVerticalCenter 			0x01
#define kAlignTop 						0x02
#define kAlignBottom 					0x03
#define kAlignHorizontalCenter 			0x04
#define kAlignAbsoluteCenter 			0x05
#define kAlignCenterTop 				0x06
#define kAlignCenterBottom 				0x07
#define kAlignLeft 						0x08
#define kAlignCenterLeft 				0x09
#define kAlignTopLeft 					0x0A
#define kAlignBottomLeft 				0x0B
#define kAlignRight 					0x0C
#define kAlignCenterRight 				0x0D
#define kAlignTopRight 					0x0E
#define kAlignBottomRight 				0x0F

#define atNone 							0x00
#define atVerticalCenter 				0x01
#define atTop 							0x02
#define atBottom 						0x03
#define atHorizontalCenter 				0x04
#define atAbsoluteCenter 				0x05
#define atCenterTop 					0x06
#define atCenterBottom 					0x07
#define atLeft 							0x08
#define atCenterLeft 					0x09
#define atTopLeft 						0x0A
#define atBottomLeft 					0x0B
#define atRight 						0x0C
#define atCenterRight 					0x0D
#define atTopRight 						0x0E
#define atBottomRight 					0x0F

#define kTransformNone 					0x00
#define kTransformDisabled 				0x01
#define kTransformOffline 				0x02
#define kTransformOpen 					0x03
#define kTransformLabel1 				0x0100
#define kTransformLabel2 				0x0200
#define kTransformLabel3 				0x0300
#define kTransformLabel4 				0x0400
#define kTransformLabel5 				0x0500
#define kTransformLabel6 				0x0600
#define kTransformLabel7 				0x0700
#define kTransformSelected 				0x4000
#define kTransformSelectedDisabled 		0x4001
#define kTransformSelectedOffline 		0x4002
#define kTransformSelectedOpen 			0x4003

#define ttNone 							0x00
#define ttDisabled 						0x01
#define ttOffline 						0x02
#define ttOpen 							0x03
#define ttLabel1 						0x0100
#define ttLabel2 						0x0200
#define ttLabel3 						0x0300
#define ttLabel4 						0x0400
#define ttLabel5 						0x0500
#define ttLabel6 						0x0600
#define ttLabel7 						0x0700
#define ttSelected 						0x4000
#define ttSelectedDisabled 				0x4001
#define ttSelectedOffline 				0x4002
#define ttSelectedOpen 					0x4003

#define kSelectorLarge1Bit 				0x00000001
#define kSelectorLarge4Bit 				0x00000002
#define kSelectorLarge8Bit 				0x00000004
#define kSelectorLarge32Bit 			0x00000008
#define kSelectorLarge8BitMask 			0x00000010
#define kSelectorSmall1Bit 				0x00000100
#define kSelectorSmall4Bit 				0x00000200
#define kSelectorSmall8Bit 				0x00000400
#define kSelectorSmall32Bit 			0x00000800
#define kSelectorSmall8BitMask 			0x00001000
#define kSelectorMini1Bit 				0x00010000
#define kSelectorMini4Bit 				0x00020000
#define kSelectorMini8Bit 				0x00040000
#define kSelectorHuge1Bit 				0x01000000
#define kSelectorHuge4Bit 				0x02000000
#define kSelectorHuge8Bit 				0x04000000
#define kSelectorHuge32Bit 				0x08000000
#define kSelectorHuge8BitMask 			0x10000000
#define kSelectorAllLargeData 			0x000000FF
#define kSelectorAllSmallData 			0x0000FF00
#define kSelectorAllMiniData 			0x00FF0000
#define kSelectorAllHugeData 			0xFF000000
#define kSelectorAll1BitData 			0x01010101
#define kSelectorAll4BitData 			0x02020202
#define kSelectorAll8BitData 			0x04040404
#define kSelectorAll32BitData 			0x08000808
#define kSelectorAllAvailableData 		0xFFFFFFFF

#define svLarge1Bit 					0x00000001
#define svLarge4Bit 					0x00000002
#define svLarge8Bit 					0x00000004
#define svSmall1Bit 					0x00000100
#define svSmall4Bit 					0x00000200
#define svSmall8Bit 					0x00000400
#define svMini1Bit 						0x00010000
#define svMini4Bit 						0x00020000
#define svMini8Bit 						0x00040000
#define svAllLargeData 					0x000000FF
#define svAllSmallData 					0x0000FF00
#define svAllMiniData 					0x00FF0000
#define svAll1BitData 					0x01010101
#define svAll4BitData 					0x02020202
#define svAll8BitData 					0x04040404
#define svAllAvailableData 				0xFFFFFFFF


/*-----------------------------------cicn ¥ Color Icon -------------------------------------------*/
/*
   cicn_RezTemplateVersion:
       0 - original 
      1 - auto calculate much of internal data                <-- default
*/
#ifndef cicn_RezTemplateVersion
 #ifdef oldTemp                          /* grandfather in use of ÒoldTempÓ */
      #define cicn_RezTemplateVersion 0
  #else
      #define cicn_RezTemplateVersion 1
  #endif
#endif


type 'cicn' {
     /* IconPMap (pixMap) record */
     fill long;                                              /* Base address         */
     unsigned bitstring[1] = 1;                              /* New pixMap flag      */
     unsigned bitstring[2] = 0;                              /* Must be 0            */
#if cicn_RezTemplateVersion == 0
    pMapRowBytes:
      unsigned bitstring[13];                                 /* Offset to next row   */
 Bounds:
        rect;                                                   /* Bitmap bounds        */
     integer;                                                /* pixMap vers number   */
     integer unpacked;                                       /* Packing format       */
     unsigned longint;                                       /* Size of pixel data   */
     unsigned hex longint;                                   /* h. resolution (ppi) (fixed) */
      unsigned hex longint;                                   /* v. resolution (ppi) (fixed) */
      integer         chunky, chunkyPlanar, planar;           /* Pixel storage format */
     integer;                                                /* # bits in pixel      */
     integer;                                                /* # components in pixel*/
     integer;                                                /* # bits per field     */
     unsigned longint;                                       /* Offset to next plane */
     unsigned longint;                                       /* Offset to color table*/
     fill long;                                              /* Reserved             */

        /* IconMask (bitMap) record */
     fill long;                                              /* Base address         */
 maskRowBytes:
      integer;                                                /* Row bytes            */
     rect;                                                   /* Bitmap bounds        */


       /* IconBMap (bitMap) record */
     fill long;                                              /* Base address         */
 iconBMapRowBytes:
      integer;                                                /* Row bytes            */
     rect;                                                   /* Bitmap bounds        */

        fill long;                                              /* Handle placeholder   */

        /* Mask data */
        hex string [$$Word(maskRowBytes) * PIXMAPHEIGHT];

     /* BitMap data */
      hex string [$$Word(iconBMapRowBytes) * PIXMAPHEIGHT];

     /* Color Table */
      unsigned hex longint;                                   /* ctSeed               */
     integer;                                                /* ctFlags              */
     integer = $$Countof(ColorSpec) - 1;                     /* ctSize               */
     wide array ColorSpec {
             integer;                                        /* value                */
             unsigned integer;                               /* RGB: red             */
             unsigned integer;                               /*      green           */
             unsigned integer;                               /*      blue            */
     };

        /* PixelMap data */
        hex string [$$BitField(pMapRowBytes, 0, 13) * PIXMAPHEIGHT];


#else
 pMapRowBytes:
      unsigned bitstring[13] k32x32x4 = 16;                   /* Offset to next row   */
 Bounds: 
       rect;                                                   /* Bitmap bounds        */
     integer = 0;                                            /* pixMap vers number   */
     integer = 0;                                            /* Packing format       */
     fill long;                                              /* Size of pixel data   */
     unsigned hex longint = $00480000;                       /* h. resolution (ppi)  */
     unsigned hex longint = $00480000;                       /* v. resolution (ppi)  */
     integer = 0 /* chunky */;                               /* Pixel storage format */
 PixelSize:
     integer;                                                /* # bits in pixel      */
     integer = 1;                                            /* # components in pixel*/
     integer = $$Word(PixelSize);                            /* # bits per field     */
     fill long;
     fill long;
     fill long;

        /* IconMask (bitMap) record */
     fill long;                                              /* Base address         */
     integer = BitMapRowBytes;                               /* Row bytes            */
     PixMapBounds;                                           /* Bitmap bounds        */

        /* IconBMap (bitMap) record */
     fill long;                                              /* Base address         */
     integer = BitMapRowBytes;                               /* Row bytes            */
     PixMapBounds;                                           /* Bitmap bounds        */

        fill long;                                              /* Handle placeholder   */

        /* Mask data */
        hex string [BitMapRowBytes * PixMapHeight];

       /* BitMap data */
      hex string [BitMapRowBytes * PixMapHeight];

   ColorTable:
        unsigned hex longint = 0;                               /* ctSeed               */
     integer = 0;                                            /* ctFlags              */
     integer = $$Countof(ColorSpec) - 1;                     /* ctSize               */
     wide array ColorSpec {
             integer = $$ArrayIndex(ColorSpec) - 1;          /* value                */
             unsigned integer;                               /* RGB: red             */
             unsigned integer;                               /*      green           */
             unsigned integer;                               /*      blue            */
     };

    PixelData:
     hex string [PixMapRowBytes * PixMapHeight];             /* more of the pixmap   */
#endif
};


/*----------------------------ICON ¥ Icon-----------------------------------------------*/
type 'ICON' {
      hex string[128];                                        /* Icon data            */
};


/*----------------------------ICN# ¥ Icon List------------------------------------------*/
type 'ICN#' {
      array {
                hex string[128];                                /* Icon data            */
     };
};


/*----------------------------SICN ¥ Small Icon-----------------------------------------*/
type 'SICN' {
      array {
                hex string[32];                                 /* SICN data            */
     };
};


/*--------------------------ics# ¥ small icons with masks-------------------------------*/
type 'ics#' {
  array [2] {
        hex string[32];
    };
};


/*--------------------------icm# ¥ mini icons with masks--------------------------------*/
type 'icm#' {
  array [2] {
        hex string[24];
    };
};


/*--------------------------icm8 ¥ 8-bit mini icon no mask------------------------------*/
type 'icm8' {
  hex string[192];
};


/*--------------------------icm4 ¥ 4-bit mini icon no mask------------------------------*/
type 'icm4' {
  hex string[96];
};


/*--------------------------icl8 ¥ 8-bit large icon no mask-----------------------------*/
type 'icl8' {
  hex string[1024];
};


/*--------------------------icl4 ¥ 4-bit large icon no mask-----------------------------*/
type 'icl4' {
  hex string[512];
};


/*--------------------------ics8 ¥ 8-bit small icon no mask-----------------------------*/
type 'ics8' {
  hex string[256];
};


/*--------------------------ics4 ¥ 4-bit small icon no mask-----------------------------*/
type 'ics4' {
  hex string[128];
};


/*-------------------------------¥ Keyboard Icons---------------------------------------*/
type 'KCN#' as 'ICN#';                      
type 'kcs#' as 'ics#';                             /* Keyboard small icon */
type 'kcl8' as 'icl8';                                /* Keyboard 8-bit color icon */
type 'kcl4' as 'icl4';                              /* Keyboard 4-bit color icon */
type 'kcs8' as 'ics8';                              /* Keyboard 8-bit small color icon */
type 'kcs4' as 'ics4';                                /* Keyboard 4-bit small color icon */

#define kSystemIconsCreator 			'macs'
#define kClipboardIcon 					'CLIP'
#define kClippingUnknownTypeIcon 		'clpu'
#define kClippingPictureTypeIcon 		'clpp'
#define kClippingTextTypeIcon 			'clpt'
#define kClippingSoundTypeIcon 			'clps'
#define kDesktopIcon 					'desk'
#define kFinderIcon 					'FNDR'
#define kComputerIcon 					'root'
#define kFontSuitcaseIcon 				'FFIL'
#define kFullTrashIcon 					'ftrh'
#define kGenericApplicationIcon 		'APPL'
#define kGenericCDROMIcon 				'cddr'
#define kGenericControlPanelIcon 		'APPC'
#define kGenericControlStripModuleIcon 	'sdev'
#define kGenericComponentIcon 			'thng'
#define kGenericDeskAccessoryIcon 		'APPD'
#define kGenericDocumentIcon 			'docu'
#define kGenericEditionFileIcon 		'edtf'
#define kGenericExtensionIcon 			'INIT'
#define kGenericFileServerIcon 			'srvr'
#define kGenericFontIcon 				'ffil'
#define kGenericFontScalerIcon 			'sclr'
#define kGenericFloppyIcon 				'flpy'
#define kGenericHardDiskIcon 			'hdsk'
#define kGenericIDiskIcon 				'idsk'
#define kGenericRemovableMediaIcon 		'rmov'
#define kGenericMoverObjectIcon 		'movr'
#define kGenericPCCardIcon 				'pcmc'
#define kGenericPreferencesIcon 		'pref'
#define kGenericQueryDocumentIcon 		'qery'
#define kGenericRAMDiskIcon 			'ramd'
#define kGenericSharedLibaryIcon 		'shlb'
#define kGenericStationeryIcon 			'sdoc'
#define kGenericSuitcaseIcon 			'suit'
#define kGenericURLIcon 				'gurl'
#define kGenericWORMIcon 				'worm'
#define kInternationalResourcesIcon 	'ifil'
#define kKeyboardLayoutIcon 			'kfil'
#define kSoundFileIcon 					'sfil'
#define kSystemSuitcaseIcon 			'zsys'
#define kTrashIcon 						'trsh'
#define kTrueTypeFontIcon 				'tfil'
#define kTrueTypeFlatFontIcon 			'sfnt'
#define kTrueTypeMultiFlatFontIcon 		'ttcf'
#define kUserIDiskIcon 					'udsk'
#define kUnknownFSObjectIcon 			'unfs'
#define kInternationResourcesIcon 		'ifil'				/*  old name */

#define kInternetLocationHTTPIcon 		'ilht'
#define kInternetLocationFTPIcon 		'ilft'
#define kInternetLocationAppleShareIcon  'ilaf'
#define kInternetLocationAppleTalkZoneIcon  'ilat'
#define kInternetLocationFileIcon 		'ilfi'
#define kInternetLocationMailIcon 		'ilma'
#define kInternetLocationNewsIcon 		'ilnw'
#define kInternetLocationNSLNeighborhoodIcon  'ilns'
#define kInternetLocationGenericIcon 	'ilge'

#define kGenericFolderIcon 				'fldr'
#define kDropFolderIcon 				'dbox'
#define kMountedFolderIcon 				'mntd'
#define kOpenFolderIcon 				'ofld'
#define kOwnedFolderIcon 				'ownd'
#define kPrivateFolderIcon 				'prvf'
#define kSharedFolderIcon 				'shfl'

#define kSharingPrivsNotApplicableIcon 	'shna'
#define kSharingPrivsReadOnlyIcon 		'shro'
#define kSharingPrivsReadWriteIcon 		'shrw'
#define kSharingPrivsUnknownIcon 		'shuk'
#define kSharingPrivsWritableIcon 		'writ'

#define kUserFolderIcon 				'ufld'
#define kWorkgroupFolderIcon 			'wfld'
#define kGuestUserIcon 					'gusr'
#define kUserIcon 						'user'
#define kOwnerIcon 						'susr'
#define kGroupIcon 						'grup'

#define kAppearanceFolderIcon 			'appr'
#define kAppleExtrasFolderIcon 			'aexÄ'
#define kAppleMenuFolderIcon 			'amnu'
#define kApplicationsFolderIcon 		'apps'
#define kApplicationSupportFolderIcon 	'asup'
#define kAssistantsFolderIcon 			'astÄ'
#define kColorSyncFolderIcon 			'prof'
#define kContextualMenuItemsFolderIcon 	'cmnu'
#define kControlPanelDisabledFolderIcon  'ctrD'
#define kControlPanelFolderIcon 		'ctrl'
#define kControlStripModulesFolderIcon 	'sdvÄ'
#define kDocumentsFolderIcon 			'docs'
#define kExtensionsDisabledFolderIcon 	'extD'
#define kExtensionsFolderIcon 			'extn'
#define kFavoritesFolderIcon 			'favs'
#define kFontsFolderIcon 				'font'
#define kHelpFolderIcon 				'Ählp'
#define kInternetFolderIcon 			'intÄ'
#define kInternetPlugInFolderIcon 		'Änet'
#define kInternetSearchSitesFolderIcon 	'issf'
#define kLocalesFolderIcon 				'Äloc'
#define kMacOSReadMeFolderIcon 			'morÄ'
#define kPublicFolderIcon 				'pubf'
#define kPreferencesFolderIcon 			'prfÄ'
#define kPrinterDescriptionFolderIcon 	'ppdf'
#define kPrinterDriverFolderIcon 		'Äprd'
#define kPrintMonitorFolderIcon 		'prnt'
#define kRecentApplicationsFolderIcon 	'rapp'
#define kRecentDocumentsFolderIcon 		'rdoc'
#define kRecentServersFolderIcon 		'rsrv'
#define kScriptingAdditionsFolderIcon 	'Äscr'
#define kSharedLibrariesFolderIcon 		'Älib'
#define kScriptsFolderIcon 				'scrÄ'
#define kShutdownItemsDisabledFolderIcon  'shdD'
#define kShutdownItemsFolderIcon 		'shdf'
#define kSpeakableItemsFolder 			'spki'
#define kStartupItemsDisabledFolderIcon  'strD'
#define kStartupItemsFolderIcon 		'strt'
#define kSystemExtensionDisabledFolderIcon  'macD'
#define kSystemFolderIcon 				'macs'
#define kTextEncodingsFolderIcon 		'Ätex'
#define kUsersFolderIcon 				'usrÄ'
#define kUtilitiesFolderIcon 			'utiÄ'
#define kVoicesFolderIcon 				'fvoc'

#define kAppleScriptBadgeIcon 			'scrp'
#define kLockedBadgeIcon 				'lbdg'
#define kMountedBadgeIcon 				'mbdg'
#define kSharedBadgeIcon 				'sbdg'
#define kAliasBadgeIcon 				'abdg'
#define kAlertCautionBadgeIcon 			'cbdg'

#define kAlertNoteIcon 					'note'
#define kAlertCautionIcon 				'caut'
#define kAlertStopIcon 					'stop'

#define kAppleTalkIcon 					'atlk'
#define kAppleTalkZoneIcon 				'atzn'
#define kAFPServerIcon 					'afps'
#define kFTPServerIcon 					'ftps'
#define kHTTPServerIcon 				'htps'
#define kGenericNetworkIcon 			'gnet'
#define kIPFileServerIcon 				'isrv'

#define kToolbarCustomizeIcon 			'tcus'
#define kToolbarDeleteIcon 				'tdel'
#define kToolbarFavoritesIcon 			'tfav'
#define kToolbarHomeIcon 				'thom'

#define kAppleLogoIcon 					'capl'
#define kAppleMenuIcon 					'sapl'
#define kBackwardArrowIcon 				'baro'
#define kFavoriteItemsIcon 				'favr'
#define kForwardArrowIcon 				'faro'
#define kGridIcon 						'grid'
#define kHelpIcon 						'help'
#define kKeepArrangedIcon 				'arng'
#define kLockedIcon 					'lock'
#define kNoFilesIcon 					'nfil'
#define kNoFolderIcon 					'nfld'
#define kNoWriteIcon 					'nwrt'
#define kProtectedApplicationFolderIcon  'papp'
#define kProtectedSystemFolderIcon 		'psys'
#define kRecentItemsIcon 				'rcnt'
#define kShortcutIcon 					'shrt'
#define kSortAscendingIcon 				'asnd'
#define kSortDescendingIcon 			'dsnd'
#define kUnlockedIcon 					'ulck'
#define kConnectToIcon 					'cnct'
#define kGenericWindowIcon 				'gwin'
#define kQuestionMarkIcon 				'ques'
#define kDeleteAliasIcon 				'dali'
#define kEjectMediaIcon 				'ejec'
#define kBurningIcon 					'burn'
#define kRightContainerArrowIcon 		'rcar'

#define kIconServicesNormalUsageFlag 	0x00000000
#define kIconServicesNoBadgeFlag 		0x00000001			/*  available on Panther and later  */
#define kIconServicesUpdateIfNeededFlag  0x00000002			/*  available on Panther and later  */

#define kIconServicesCatalogInfoMask 	0x00081C5E
#define kPlotIconRefNormalFlags 		0
#define kPlotIconRefNoImage 			0x02
#define kPlotIconRefNoMask 				0x04


/*--------------------------icns ¥ icon family-----------------------------*/
type 'icns' {
iconFamilyBegin:
  literal longint = 'icns';
  unsigned longint = (iconFamilyEnd - iconFamilyBegin) >> 3;
 array elementArray {
       literal longint;
#if derez
len:
        fill long;
     hex string[$$Long(len[$$ArrayIndex(elementArray)]) - 8];
#else
elementBegin:
       longint =   (elementEnd[$$ArrayIndex(elementArray)] -
                  elementBegin[$$ArrayIndex(elementArray)] >> 3) + 4;
        hex string;
elementEnd:
#endif
 };
iconFamilyEnd:
};


#endif /* __ICONS_R__ */

