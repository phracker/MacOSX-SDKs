/*
     File:       UTCoreTypes.h
 
     Contains:   String constants for core uniform type identifiers
 
     Copyright:  2004-2009 by Apple Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
*/
#ifndef __UTCORETYPES__
#define __UTCORETYPES__

#ifndef __COREFOUNDATION__
#include <CoreFoundation/CoreFoundation.h>
#endif


#include <Availability.h>

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
 *    base type for OS X applications, launchable items
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
extern const CFStringRef kUTTypeItem                                 __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeContent                              __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeCompositeContent                     __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeApplication                          __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeMessage                              __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeContact                              __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeArchive                              __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeDiskImage                            __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);


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
 *    symlink and alias file types conform to this UTI
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
extern const CFStringRef kUTTypeData                                 __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeDirectory                            __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeResolvable                           __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeSymLink                              __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeMountPoint                           __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeAliasFile                            __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeAliasRecord                          __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeURL                                  __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeFileURL                              __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);


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
 *    plain text, UTF-16 encoding, native byte order, optional BOM
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
extern const CFStringRef kUTTypeText                                 __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypePlainText                            __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeUTF8PlainText                        __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeUTF16ExternalPlainText               __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeUTF16PlainText                       __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeRTF                                  __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeHTML                                 __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeXML                                  __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeSourceCode                           __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeCSource                              __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeObjectiveCSource                     __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeCPlusPlusSource                      __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeObjectiveCPlusPlusSource             __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeCHeader                              __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeCPlusPlusHeader                      __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeJavaSource                           __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);


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
extern const CFStringRef kUTTypePDF                                  __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeRTFD                                 __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeFlatRTFD                             __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeTXNTextAndMultimediaData             __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeWebArchive                           __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);


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
extern const CFStringRef kUTTypeImage                                __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeJPEG                                 __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeJPEG2000                             __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeTIFF                                 __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypePICT                                 __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeGIF                                  __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypePNG                                  __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeQuickTimeImage                       __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeAppleICNS                            __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeBMP                                  __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeICO                                  __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);


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
extern const CFStringRef kUTTypeAudiovisualContent                   __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeMovie                                __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeVideo                                __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeAudio                                __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeQuickTimeMovie                       __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeMPEG                                 __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeMPEG4                                __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeMP3                                  __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeMPEG4Audio                           __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeAppleProtectedMPEG4Audio             __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);


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
extern const CFStringRef kUTTypeFolder                               __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeVolume                               __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypePackage                              __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeBundle                               __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeFramework                            __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);


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
extern const CFStringRef kUTTypeApplicationBundle                    __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeApplicationFile                      __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);


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
extern const CFStringRef kUTTypeVCard                                __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);


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
extern const CFStringRef kUTTypeInkText                              __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);


#endif /* __UTCORETYPES__ */

