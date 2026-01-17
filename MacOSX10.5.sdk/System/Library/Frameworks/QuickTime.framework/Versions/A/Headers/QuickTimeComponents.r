/*
     File:       QuickTimeComponents.r
 
     Contains:   QuickTime Interfaces.
 
     Version:    QuickTime 7.2.1
 
     Copyright:  © 1990-2006 by Apple Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

#ifndef __QUICKTIMECOMPONENTS_R__
#define __QUICKTIMECOMPONENTS_R__

#ifndef __CORESERVICES_R__
#include <CoreServices/CoreServices.r>
#endif

#define canMovieImportHandles 			0x01
#define canMovieImportFiles 			0x02
#define hasMovieImportUserInterface 	0x04
#define canMovieExportHandles 			0x08
#define canMovieExportFiles 			0x10
#define hasMovieExportUserInterface 	0x20
#define movieImporterIsXMLBased 		0x20
#define dontAutoFileMovieImport 		0x40
#define canMovieExportAuxDataHandle 	0x80
#define canMovieImportValidateHandles 	0x0100
#define canMovieImportValidateFile 		0x0200
#define dontRegisterWithEasyOpen 		0x0400
#define canMovieImportInPlace 			0x0800
#define movieImportSubTypeIsFileExtension  0x1000
#define canMovieImportPartial 			0x2000
#define hasMovieImportMIMEList 			0x4000
#define canMovieImportAvoidBlocking 	0x8000
#define canMovieExportFromProcedures 	0x8000
#define canMovieExportValidateMovie 	0x00010000
#define movieImportMustGetDestinationMediaType  0x00010000
#define movieExportNeedsResourceFork 	0x00020000
#define canMovieImportDataReferences 	0x00040000
#define movieExportMustGetSourceMediaType  0x00080000
#define canMovieImportWithIdle 			0x00100000
#define canMovieImportValidateDataReferences  0x00200000
#define reservedForUseByGraphicsImporters  0x00800000

#define kQTMediaConfigResourceType 		'mcfg'
#define kQTMediaConfigResourceVersion 	2
#define kQTMediaGroupResourceType 		'mgrp'
#define kQTMediaGroupResourceVersion 	1
#define kQTBrowserInfoResourceType 		'brws'
#define kQTBrowserInfoResourceVersion 	1

#define kQTMediaMIMEInfoHasChanged 		0x00000002			/*  the MIME type(s) is(are) new or has changed since the last time */
															/*   someone asked about it */
#define kQTMediaFileInfoHasChanged 		0x00000004			/*  the file extension(s) is(are) new or has changed since the last time */
															/*   anyone asked about it */
#define kQTMediaConfigCanUseApp 		0x00040000			/*  this MIME type can be configured to use app */
#define kQTMediaConfigCanUsePlugin 		0x00080000			/*  this MIME type can be configured to use plug-in */
#define kQTMediaConfigUNUSED 			0x00100000			/*  currently unused */
#define kQTMediaConfigBinaryFile 		0x00800000			/*  file should be transfered in binary mode */
#define kQTMediaConfigTextFile 			0					/*  not a bit, defined for clarity */
#define kQTMediaConfigMacintoshFile 	0x01000000			/*  file's resource fork is significant */
#define kQTMediaConfigCanDoFileAssociation  0x04000000		/*  can configure this file association  */
#define kQTMediaConfigAssociateByDefault  0x08000000		/*  Deprecated, use kQTMediaConfigTakeFileAssociationByDefault instead */
#define kQTMediaConfigTakeFileAssociationByDefault  0x08000000 /*  take this file association by default */
#define kQTMediaConfigUseAppByDefault 	0x10000000			/*  use the app by default for this MIME type */
#define kQTMediaConfigUsePluginByDefault  0x20000000		/*  use the plug-in by default for this MIME type */
#define kQTMediaConfigDefaultsMask 		0x30000000
#define kQTMediaConfigDefaultsShift 	12					/*  ((flags & kQTMediaConfigDefaultsMask) >> kQTMediaConfigDefaultsShift) to get default setting  */
#define kQTMediaConfigHasFileHasQTAtoms  0x40000000			/*  the file has a "QuickTime like" file format  */

#define kQTMediaConfigStreamGroupID 	'strm'
#define kQTMediaConfigInteractiveGroupID  'intr'
#define kQTMediaConfigVideoGroupID 		'eyes'
#define kQTMediaConfigAudioGroupID 		'ears'
#define kQTMediaConfigMPEGGroupID 		'mpeg'
#define kQTMediaConfigMP3GroupID 		'mp3 '
#define kQTMediaConfigImageGroupID 		'ogle'
#define kQTMediaConfigMiscGroupID 		'misc'

#define kQTMediaInfoNetGroup 			'net '
#define kQTMediaInfoWinGroup 			'win '
#define kQTMediaInfoMacGroup 			'mac '
#define kQTMediaInfoMiscGroup 			0x3F3F3F3F			/*  '????' */

#define kMimeInfoMimeTypeTag 			'mime'
#define kMimeInfoFileExtensionTag 		'ext '
#define kMimeInfoDescriptionTag 		'desc'
#define kMimeInfoGroupTag 				'grop'
#define kMimeInfoDoNotOverrideExistingFileTypeAssociation  'nofa'


type 'mime' {
 // 10 bytes of reserved
    longint = 0;
   longint = 0;
   integer = 0;
   // 2 bytes of lock count
   integer = 0;
   
   // size of this atom
   parentStart:
   longint = ( (parentEnd - parentStart) / 8 );
   
   // atom type
   literal longint = 'sean';
  
   // atom id
 longint = 1;
   integer = 0;
   integer =  $$CountOf(AtomArray);
   longint = 0;
   
   array AtomArray {
      atomStart:
     // size of this atom
       longint = ((atomEnd[$$ArrayIndex(AtomArray)] - atomStart[$$ArrayIndex(AtomArray)]) / 8);
       
       // atom type
       literal longint;
       
       // atom id
     longint;
       integer = 0;
       integer = 0; // no children
        longint = 0;
       string;
        atomEnd:
       };
 parentEnd:
     
};


/*----------------------------'mgrp' ¥ importer MIME configuration info ------------------------*/
type 'mgrp'
{
  longint = kQTMediaGroupResourceVersion;     // resource version (long)

    // component version this applies to
   longint kVersionDoesntMatter = 0;

 // array of group information, optional unless you are defining new group(s)
   longint = $$Countof(MIMEGroupArray);
   array MIMEGroupArray 
  {
      literal longint;                // group ID (OSType)
       pstring;                        // name of the grouping
        pstring;                        // description
     align long;                     // align
   };
};


/*----------------------------'mcfg' ¥ importer MIME configuration info ------------------------*/
type 'mcfg'
{
  longint = kQTMediaConfigResourceVersion;        // resource version (long)

    // version of the component this applies to
    longint kVersionDoesntMatter = 0;

 // array, one entry for each media type
    longint = $$Countof(MIMEInfoArray);
    array MIMEInfoArray 
   {
      literal longint;                // ID of the group this type belongs with
                                      //  (OSType, one of kQTMediaConfigStreamGroupID, etc.)
     literal longint;                // MIME config flags (unsigned long, one or more of kQTMediaConfigCanUseApp, etc.)

        literal longint;                // MacOS file type when saved (OSType)
     literal longint;                // MacOS file creator when saved (OSType)

     literal longint;                // component type (OSType)
     literal longint;                // component subtype (OSType)
      literal longint;                // component manufacturer (OSType)
     unsigned hex longint;           // component flags
     unsigned hex longint    kAnyComponentFlagsMask = 0;     // component flags mask

       literal longint;                // default file extension (OSType) -- all caps to match subType of eat and grip components
     
       literal longint;                // QT file group (OSType, one of kQTMediaInfoNetGroup, etc.)
       


       longint = $$Countof(QTMediaSynonymsArray);
     array QTMediaSynonymsArray
     {
          pstring;                    // array of media type synonyms
        };
     align long;                     // align

      wide array [5] 
        {
          pstring;
           // array of 5 Pascal strings: 
         //  + media type description
           //  + file extension(s)
            //  + opening application name
         //  + missing software description
         //  + vendor info string (copyright, version, etc)
     };
     align long;                     // align

      // array of MIME types that describe this (eg. audio/mpeg, audio/x-mpeg, etc.)
     longint = $$Countof(MIMETypeArray);
        array MIMETypeArray
        {
          pstring;
       };
     align long;                     // align
   };
};

#define kQTBrowserInfoCanUseSystemFolderPlugin  0x00000001	/*  Mac browser can use plug-in from System "Internet Plug-ins" folder  */

type 'brws' 
{
    longint = kQTBrowserInfoResourceVersion;        // resource version (long) 

   literal longint;                    // flags (kQTBrowserInfoCanUseSystemFolderPlugin, etc) 

   literal longint;                    // browser Mac OS creator code 

   pstring;                            // name of plug-ins folder if kQTBrowserInfoCanUseSystemFolderPlugin not set 
};

#define kQTPreFlightOpenComponent 		0x00000002			/*  Open component as preflight check */

type 'prfl' {
    longint;
};


/*----------------------------'stg#'  ¥ QuickTime preset list ------------------------*/
/*
   
 */
type 'stg#' {
 hex longint;                /* flags */
    longint = $$CountOf(PresetDescriptionArray);
   longint = 0;
   
   array PresetDescriptionArray {
     literal longint;            /*  preset key ID */
       unsigned hex longint noFlags = 0,
                           kQTPresetInfoIsDivider = 1;    /*  preset flags */
        literal longint;            /*  preset resource type */
        integer;                    /*  preset resource ID */
      integer = 0;                /*  padding but also reserved */
       integer;                    /*  preset name string list ID */
      integer;                    /*  preset name string index */
        integer;                    /*  preset description string list ID */
       integer;                    /*  preset description string index */
 };
};


/*----------------------------'stgp'  ¥ QuickTime preset platform list ------------------------*/
/*
  
 */
type 'stgp' {
     longint = 0;                                            /* reserved */
     literal longint;                                        /* default settings list resource type */
      integer;                                                /* default settings list resource id */
        integer = $$CountOf(SettingsPlatformInfo);
     wide array SettingsPlatformInfo {
          unsigned hex longint = 0;                           /* reserved */
         literal longint;                                    /* platform settings list resource Type */
         integer;                                            /* platform settings list resource ID */
           integer platform68k = 1,                            /* platform type (response from gestaltSysArchitecture) */
                 platformPowerPC = 2,
                   platformInterpreted = 3,
                   platformWin32 = 4;
     };
};


/*----------------------------'src#'  ¥ MovieExporter source list ------------------------*/
/*
   
 */
type 'src#' {
 longint = $$CountOf(SourceArray);
  longint = 0;                    /* reserved */

    array SourceArray {
        literal longint;            /* Media type of source */
     integer;                    /* min number of sources of this kind required, zero if none required */
       integer;                    /* max number of sources of this kind allowed, 65535 if unlimited allowed */
       longint isMediaType = 0x01, isMediaCharacteristic = 0x02, isSourceType = 0x04;
 };
};

type 'trk#' as 'src#';

#define channelFlagDontOpenResFile 		2
#define channelFlagHasDependency 		4


#endif /* __QUICKTIMECOMPONENTS_R__ */

