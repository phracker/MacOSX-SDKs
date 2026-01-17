/*
     File:       LaunchServices/UTCoreTypes.h
 
     Contains:   String constants for core uniform type identifiers
 
     Version:    LaunchServices-182~2
 
     Copyright:  © 2004-2006 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __UTCORETYPES__
#define __UTCORETYPES__

#ifndef __CORESERVICES__
#include <CoreServices/CoreServices.h>
#endif


#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

/* ================================================================================ *
 *  Abstract base types                                                             *
 * ================================================================================ */
/*
 *  kUTTypeItem
 *
 *    generic base type for most things
 *    (files, directories)
 *
 *    UTI: public.item
 *
 *
 *  kUTTypeContent
 *
 *    base type for anything containing user-viewable document content
 *    (documents, pasteboard data, and document packages)
 *
 *    UTI: public.content
 *
 *
 *  kUTTypeCompositeContent
 *
 *    base type for content formats supporting mixed embedded content
 *    (i.e., compound documents)
 *
 *    UTI: public.composite-content
 *    conforms to: public.content
 *
 *
 *  kUTTypeApplication
 *
 *    base type for Mac OS X applications, launchable items
 *
 *    UTI: com.apple.application
 *
 *
 *  kUTTypeMessage
 *
 *    base type for messages (email, IM, etc.)
 *
 *    UTI: public.message
 *
 *
 *  kUTTypeContact
 *
 *    contact information, e.g. for a person, group, organization
 *
 *    UTI: public.contact
 *
 *
 *  kUTTypeArchive
 *
 *    an archive of files and directories
 *
 *    UTI: public.archive
 *
 *
 *  kUTTypeDiskImage
 *
 *    a data item mountable as a volume
 *
 *    UTI: public.disk-image
 */
/*
 *  kUTTypeItem
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeItem                                 AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kUTTypeContent
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeContent                              AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kUTTypeCompositeContent
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeCompositeContent                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kUTTypeApplication
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeApplication                          AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kUTTypeMessage
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeMessage                              AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kUTTypeContact
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeContact                              AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kUTTypeArchive
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeArchive                              AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kUTTypeDiskImage
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeDiskImage                            AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/* ================================================================================ *
 *  Concrete base types                                                             *
 * ================================================================================ */
/*
 *  kUTTypeData
 *
 *    base type for any sort of simple byte stream,
 *    including files and in-memory data
 *
 *    UTI: public.data
 *    conforms to: public.item
 *
 *
 *  kUTTypeDirectory
 *
 *    file system directory 
 *    (includes packages AND folders)
 *
 *    UTI: public.directory
 *    conforms to: public.item
 *
 *
 *  kUTTypeResolvable
 *
 *    anything the Alias Manager can resolve
 *
 *    UTI: com.apple.resolvable
 *
 *
 *  kUTTypeSymLink
 *
 *    a symbolic link
 *
 *    UTI: public.symlink
 *    conforms to: public.item, com.apple.resolvable
 *
 *
 *  kUTTypeMountPoint
 *
 *    a volume mount point (resolvable, resolves to the root dir of a volume)
 *
 *    UTI: com.apple.mount-point
 *    conforms to: public.item, com.apple.resolvable
 *
 *
 *  kUTTypeAliasFile
 *
 *    a fully-formed alias file
 *
 *    UTI: com.apple.alias-file
 *    conforms to: public.data, com.apple.resolvable
 *
 *
 *  kUTTypeAliasRecord
 *
 *    raw alias data
 *
 *    UTI: com.apple.alias-record
 *    conforms to: public.data, com.apple.resolvable
 *
 *
 *  kUTTypeURL
 *
 *    The bytes of a URL
 *    (OSType 'url ')
 *
 *    UTI: public.url
 *    conforms to: public.data
 *
 *
 *  kUTTypeFileURL
 *
 *    The text of a "file:" URL 
 *    (OSType 'furl')
 *
 *    UTI: public.file-url
 *    conforms to: public.url
 */
/*
 *  kUTTypeData
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeData                                 AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kUTTypeDirectory
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeDirectory                            AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kUTTypeResolvable
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeResolvable                           AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kUTTypeSymLink
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeSymLink                              AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kUTTypeMountPoint
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeMountPoint                           AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kUTTypeAliasFile
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeAliasFile                            AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kUTTypeAliasRecord
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeAliasRecord                          AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kUTTypeURL
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeURL                                  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kUTTypeFileURL
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeFileURL                              AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/* ================================================================================ *
 *  Text types                                                                      *
 * ================================================================================ */
/*
 *  kUTTypeText
 *
 *    base type for all text-encoded data, 
 *    including text with markup (HTML, RTF, etc.)
 *
 *    UTI: public.text
 *    conforms to: public.data, public.content
 *
 *
 *  kUTTypePlainText
 *
 *    text with no markup, unspecified encoding
 *
 *    UTI: public.plain-text
 *    conforms to: public.text
 *
 *
 *  kUTTypeUTF8PlainText
 *
 *    plain text, UTF-8 encoding
 *    (OSType 'utf8', NSPasteboardType "NSStringPBoardType")
 *
 *    UTI: public.utf8-plain-text
 *    conforms to: public.plain-text
 *
 *
 *  kUTTypeUTF16ExternalPlainText
 *
 *    plain text, UTF-16 encoding, with BOM, or if BOM 
 *    is not present, has "external representation" 
 *    byte order (big-endian).
 *    (OSType 'ut16')
 *
 *    UTI: public.utf16-external-plain-text
 *    conforms to: public.plain-text
 *
 *
 *  kUTTypeUTF16PlainText
 *
 *    plain text, UTF-16 encoding, native byte order, no BOM
 *    (OSType 'utxt')
 *
 *    UTI: public.utf16-plain-text
 *    conforms to: public.plain-text
 *
 *
 *  kUTTypeRTF
 *
 *    Rich Text Format
 *
 *    UTI: public.rtf
 *    conforms to: public.text
 *
 *
 *  kUTTypeHTML
 *
 *    HTML, any version
 *
 *    UTI: public.html
 *    conforms to: public.text
 *
 *
 *  kUTTypeXML
 *
 *    generic XML
 *
 *    UTI: public.xml
 *    conforms to: public.text
 *
 *
 *  kUTTypeSourceCode
 *
 *    abstract type for source code (any language)
 *
 *    UTI: public.source-code
 *    conforms to: public.plain-text
 *
 *
 *  kUTTypeCSource
 *
 *    C source code (.c)
 *
 *    UTI: public.c-source
 *    conforms to: public.plain-text
 *
 *
 *  kUTTypeObjectiveCSource
 *
 *    Objective-C source code (.m)
 *
 *    UTI: public.objective-c-source
 *    conforms to: public.plain-text
 *
 *
 *  kUTTypeCPlusPlusSource
 *
 *    C++ source code (.cp, etc.)
 *
 *    UTI: public.c-plus-plus-source
 *    conforms to: public.plain-text
 *
 *
 *  kUTTypeObjectiveCPlusPlusSource
 *
 *    Objective-C++ source code
 *
 *    UTI: public.objective-c-plus-plus-source
 *    conforms to: public.plain-text
 *
 *
 *  kUTTypeCHeader
 *
 *    C header
 *
 *    UTI: public.c-header
 *    conforms to: public.plain-text
 *
 *
 *  kUTTypeCPlusPlusHeader
 *
 *    C++ header
 *
 *    UTI: public.c-plus-plus-header
 *    conforms to: public.plain-text
 *
 *
 *  kUTTypeJavaSource
 *
 *    Java source code
 *
 *    UTI: com.sun.java-source
 *    conforms to: public.plain-text
 */
/*
 *  kUTTypeText
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeText                                 AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kUTTypePlainText
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypePlainText                            AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kUTTypeUTF8PlainText
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeUTF8PlainText                        AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kUTTypeUTF16ExternalPlainText
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeUTF16ExternalPlainText               AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kUTTypeUTF16PlainText
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeUTF16PlainText                       AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kUTTypeRTF
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeRTF                                  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kUTTypeHTML
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeHTML                                 AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kUTTypeXML
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeXML                                  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kUTTypeSourceCode
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeSourceCode                           AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kUTTypeCSource
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeCSource                              AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kUTTypeObjectiveCSource
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeObjectiveCSource                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kUTTypeCPlusPlusSource
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeCPlusPlusSource                      AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kUTTypeObjectiveCPlusPlusSource
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeObjectiveCPlusPlusSource             AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kUTTypeCHeader
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeCHeader                              AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kUTTypeCPlusPlusHeader
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeCPlusPlusHeader                      AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kUTTypeJavaSource
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeJavaSource                           AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* ================================================================================ *
 *  Composite content types                                                         *
 * ================================================================================ */
/*
 *  kUTTypePDF
 *
 *    Adobe PDF
 *
 *    UTI: com.adobe.pdf
 *    conforms to: public.data, public.composite-content
 *
 *
 *  kUTTypeRTFD
 *
 *    Rich Text Format Directory 
 *    (RTF with content embedding, on-disk format)
 *
 *    UTI: com.apple.rtfd
 *    conforms to: com.apple.package, public.composite-content
 *
 *
 *  kUTTypeFlatRTFD
 *
 *    Flattened RTFD (pasteboard format)
 *
 *    UTI: com.apple.flat-rtfd
 *    conforms to: public.data, public.composite-content
 *
 *
 *  kUTTypeTXNTextAndMultimediaData
 *
 *    MLTE (Textension) format for mixed text & multimedia data
 *    (OSType 'txtn')
 *
 *    UTI: com.apple.txn.text-multimedia-data
 *    conforms to: public.data, public.composite-content
 *
 *
 *  kUTTypeWebArchive
 *
 *    The WebKit webarchive format
 *
 *    UTI: com.apple.webarchive
 *    conforms to: public.data, public.composite-content
 */
/*
 *  kUTTypePDF
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypePDF                                  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kUTTypeRTFD
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeRTFD                                 AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kUTTypeFlatRTFD
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeFlatRTFD                             AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kUTTypeTXNTextAndMultimediaData
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeTXNTextAndMultimediaData             AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kUTTypeWebArchive
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeWebArchive                           AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* ================================================================================ *
 *  Image content types                                                             *
 * ================================================================================ */
/*
 *  kUTTypeImage
 *
 *    abstract image data
 *
 *    UTI: public.image
 *    conforms to: public.data, public.content
 *
 *
 *  kUTTypeJPEG
 *
 *    JPEG image
 *
 *    UTI: public.jpeg
 *    conforms to: public.image
 *
 *
 *  kUTTypeJPEG2000
 *
 *    JPEG-2000 image
 *
 *    UTI: public.jpeg-2000
 *    conforms to: public.image
 *
 *
 *  kUTTypeTIFF
 *
 *    TIFF image
 *
 *    UTI: public.tiff
 *    conforms to: public.image
 *
 *
 *  kUTTypePICT
 *
 *    Quickdraw PICT format
 *
 *    UTI: com.apple.pict
 *    conforms to: public.image
 *
 *
 *  kUTTypeGIF
 *
 *    GIF image
 *
 *    UTI: com.compuserve.gif
 *    conforms to: public.image
 *
 *
 *  kUTTypePNG
 *
 *    PNG image
 *
 *    UTI: public.png
 *    conforms to: public.image
 *
 *
 *  kUTTypeQuickTimeImage
 *
 *    QuickTime image format (OSType 'qtif')
 *
 *    UTI: com.apple.quicktime-image
 *    conforms to: public.image
 *
 *
 *  kUTTypeAppleICNS
 *
 *    Apple icon data
 *
 *    UTI: com.apple.icns
 *    conforms to: public.image
 *
 *
 *  kUTTypeBMP
 *
 *    Windows bitmap
 *
 *    UTI: com.microsoft.bmp
 *    conforms to: public.image
 *
 *
 *  kUTTypeICO
 *
 *    Windows icon data
 *
 *    UTI: com.microsoft.ico
 *    conforms to: public.image
 */
/*
 *  kUTTypeImage
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeImage                                AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kUTTypeJPEG
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeJPEG                                 AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kUTTypeJPEG2000
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeJPEG2000                             AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kUTTypeTIFF
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeTIFF                                 AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kUTTypePICT
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypePICT                                 AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kUTTypeGIF
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeGIF                                  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kUTTypePNG
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypePNG                                  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kUTTypeQuickTimeImage
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeQuickTimeImage                       AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kUTTypeAppleICNS
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeAppleICNS                            AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kUTTypeBMP
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeBMP                                  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kUTTypeICO
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeICO                                  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* ================================================================================ *
 *  Audiovisual content types                                                       *
 * ================================================================================ */
/*
 *  kUTTypeAudiovisualContent
 *
 *    audio and/or video content
 *
 *    UTI: public.audiovisual-content
 *    conforms to: public.data, public.content
 *
 *
 *  kUTTypeMovie
 *
 *    A media format which may contain both video and audio
 *    Corresponds to what users would label a "movie"
 *
 *    UTI: public.movie
 *    conforms to: public.audiovisual-content
 *
 *
 *  kUTTypeVideo
 *
 *    pure video (no audio)
 *
 *    UTI: public.video
 *    conforms to: public.movie
 *
 *
 *  kUTTypeAudio
 *
 *    pure audio (no video)
 *
 *    UTI: public.audio
 *    conforms to: public.audiovisual-content
 *
 *
 *  kUTTypeQuickTimeMovie
 *
 *    QuickTime movie
 *
 *    UTI: com.apple.quicktime-movie
 *    conforms to: public.movie
 *
 *
 *  kUTTypeMPEG
 *
 *    MPEG-1 or MPEG-2 movie
 *
 *    UTI: public.mpeg
 *    conforms to: public.movie
 *
 *
 *  kUTTypeMPEG4
 *
 *    MPEG-4 movie
 *
 *    UTI: public.mpeg-4
 *    conforms to: public.movie
 *
 *
 *  kUTTypeMP3
 *
 *    MP3 audio
 *
 *    UTI: public.mp3
 *    conforms to: public.audio
 *
 *
 *  kUTTypeMPEG4Audio
 *
 *    MPEG-4 audio layer
 *    (.m4a)
 *
 *    UTI: public.mpeg-4-audio
 *    conforms to: public.mpeg-4, public.audio
 *
 *
 *  kUTTypeAppleProtectedMPEG4Audio
 *
 *    Apple protected MPEG4 format
 *    (.m4p, iTunes music store format)
 *
 *    UTI: com.apple.protected-mpeg-4-audio
 *    conforms to: public.audio
 */
/*
 *  kUTTypeAudiovisualContent
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeAudiovisualContent                   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kUTTypeMovie
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeMovie                                AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kUTTypeVideo
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeVideo                                AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kUTTypeAudio
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeAudio                                AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kUTTypeQuickTimeMovie
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeQuickTimeMovie                       AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kUTTypeMPEG
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeMPEG                                 AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kUTTypeMPEG4
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeMPEG4                                AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kUTTypeMP3
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeMP3                                  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kUTTypeMPEG4Audio
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeMPEG4Audio                           AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kUTTypeAppleProtectedMPEG4Audio
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeAppleProtectedMPEG4Audio             AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/* ================================================================================ *
 *  Directory types                                                                 *
 * ================================================================================ */
/*
 *  kUTTypeFolder
 *
 *    a user-browsable directory (i.e., not a package)
 *
 *    UTI: public.folder
 *    conforms to: public.directory
 *
 *
 *  kUTTypeVolume
 *
 *    the root folder of a volume/mount point
 *
 *    UTI: public.volume
 *    conforms to: public.folder
 *
 *
 *  kUTTypePackage
 *
 *    a packaged directory
 *
 *    UTI: com.apple.package
 *    conforms to: public.directory
 *
 *
 *  kUTTypeBundle
 *
 *    a directory conforming to one of the CFBundle layouts
 *
 *    UTI: com.apple.bundle
 *    conforms to: public.directory
 *
 *
 *  kUTTypeFramework
 *
 *    a Mac OS X framework
 *
 *    UTI: com.apple.framework
 *    conforms to: com.apple.bundle
 */
/*
 *  kUTTypeFolder
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeFolder                               AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kUTTypeVolume
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeVolume                               AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kUTTypePackage
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypePackage                              AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kUTTypeBundle
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeBundle                               AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kUTTypeFramework
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeFramework                            AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/* ================================================================================ *
 *  Application types                                                               *
 * ================================================================================ */
/*
 *  kUTTypeApplicationBundle
 *
 *    a bundled application
 *
 *    UTI: com.apple.application-bundle
 *    conforms to: com.apple.application, com.apple.bundle, com.apple.package
 *
 *
 *  kUTTypeApplicationFile
 *
 *    a single-file Carbon/Classic application 
 *
 *    UTI: com.apple.application-file
 *    conforms to: com.apple.application, public.data
 */
/*
 *  kUTTypeApplicationBundle
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeApplicationBundle                    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kUTTypeApplicationFile
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeApplicationFile                      AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/* ================================================================================ *
 *  Contact types                                                                   *
 * ================================================================================ */
/*
 *  kUTTypeVCard
 *
 *    VCard format
 *
 *    UTI: public.vcard
 *    conforms to: public.data, public.contact
 */
/*
 *  kUTTypeVCard
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeVCard                                AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/* ================================================================================ *
 *  Misc. types                                                                     *
 * ================================================================================ */
/*
 *  kUTTypeInkText
 *
 *    Opaque InkText data
 *
 *    UTI: com.apple.ink.inktext
 *    conforms to: public.data
 */
/*
 *  kUTTypeInkText
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeInkText                              AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;



#endif /* __UTCORETYPES__ */

