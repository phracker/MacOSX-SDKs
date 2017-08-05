/*
     File:       UTCoreTypes.h
 
     Contains:   String constants for core uniform type identifiers
 
     Copyright:  (c) 2004-2012 by Apple Inc. All rights reserved.
 
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



#ifdef __cplusplus
extern "C" {
#endif



CF_ASSUME_NONNULL_BEGIN



#pragma mark - Abstract base types
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
 *    (documents, pasteboard data, and document packages.) Types describing
 *    files or packages must also conform to kUTTypeData or kUTTypePackage
 *    in order for the system to bind documents to them.
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
 *
 */
extern const CFStringRef kUTTypeItem                                 __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeContent                              __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeCompositeContent                     __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeMessage                              __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeContact                              __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeArchive                              __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeDiskImage                            __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);

#pragma mark - Concrete base types
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
 *  kUTTypeExecutable
 *
 *    an executable item
 *    UTI: public.executable
 *    conforms to: public.item
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
 *  kUTTypeURLBookmarkData
 *
 *    URL bookmark
 *
 *    UTI: com.apple.bookmark
 *    conforms to: public.data, com.apple.resolvable
 *
 */
extern const CFStringRef kUTTypeData                                 __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeDirectory                            __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeResolvable                           __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeSymLink                              __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeExecutable                           __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_8_0);
extern const CFStringRef kUTTypeMountPoint                           __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeAliasFile                            __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeAliasRecord                          __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeURLBookmarkData                      __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

#pragma mark - URL types
/*
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
 *
 */
extern const CFStringRef kUTTypeURL                                  __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeFileURL                              __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);

#pragma mark - Text types
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
 *  kUTTypeDelimitedText
 *
 *    text containing delimited values
 *
 *    UTI: public.delimited-values-text
 *    conforms to: public.text
 *
 *
 *  kUTTypeCommaSeparatedText
 *
 *    text containing comma-separated values (.csv)
 *
 *    UTI: public.comma-separated-values-text
 *    conforms to: public.delimited-values-text
 *
 *
 *  kUTTypeTabSeparatedText
 *
 *    text containing tab-separated values
 *
 *    UTI: public.tab-separated-values-text
 *    conforms to: public.delimited-values-text
 *
 *
 *  kUTTypeUTF8TabSeparatedText
 *
 *    UTF-8 encoded text containing tab-separated values
 *
 *    UTI: public.utf8-tab-separated-values-text
 *    conforms to: public.tab-separated-values-text, public.utf8-plain-text
 *
 *
 *  kUTTypeRTF
 *
 *    Rich Text Format
 *
 *    UTI: public.rtf
 *    conforms to: public.text
 *
 */
extern const CFStringRef kUTTypeText                                 __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypePlainText                            __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeUTF8PlainText                        __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeUTF16ExternalPlainText               __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeUTF16PlainText                       __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeDelimitedText                        __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
extern const CFStringRef kUTTypeCommaSeparatedText                   __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
extern const CFStringRef kUTTypeTabSeparatedText                     __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
extern const CFStringRef kUTTypeUTF8TabSeparatedText                 __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
extern const CFStringRef kUTTypeRTF                                  __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);

#pragma mark - Markup languages
/*
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
 */
extern const CFStringRef kUTTypeHTML                                 __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeXML                                  __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);

#pragma mark - Programming languages
/*
 *  kUTTypeSourceCode
 *
 *    abstract type for source code (any language)
 *
 *    UTI: public.source-code
 *    conforms to: public.plain-text
 *
 *
 *  kUTTypeAssemblyLanguageSource
 *
 *    assembly language source (.s)
 *
 *    UTI: public.assembly-source
 *    conforms to: public.source-code
 *
 *
 *  kUTTypeCSource
 *
 *    C source code (.c)
 *
 *    UTI: public.c-source
 *    conforms to: public.source-code
 *
 *
 *  kUTTypeObjectiveCSource
 *
 *    Objective-C source code (.m)
 *
 *    UTI: public.objective-c-source
 *    conforms to: public.source-code
 *
 *
 *  kUTTypeSwiftSource
 *
 *    Swift source code (.swift)
 *
 *    UTI: public.swift-source
 *    conforms to: public.source-code
 *
 *
 *  kUTTypeCPlusPlusSource
 *
 *    C++ source code (.cp, etc.)
 *
 *    UTI: public.c-plus-plus-source
 *    conforms to: public.source-code
 *
 *
 *  kUTTypeObjectiveCPlusPlusSource
 *
 *    Objective-C++ source code
 *
 *    UTI: public.objective-c-plus-plus-source
 *    conforms to: public.source-code
 *
 *
 *  kUTTypeCHeader
 *
 *    C header
 *
 *    UTI: public.c-header
 *    conforms to: public.source-code
 *
 *
 *  kUTTypeCPlusPlusHeader
 *
 *    C++ header
 *
 *    UTI: public.c-plus-plus-header
 *    conforms to: public.source-code
 *
 *
 *  kUTTypeJavaSource
 *
 *    Java source code
 *
 *    UTI: com.sun.java-source
 *    conforms to: public.source-code
 *
 */
extern const CFStringRef kUTTypeSourceCode                           __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeAssemblyLanguageSource               __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
extern const CFStringRef kUTTypeCSource                              __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeObjectiveCSource                     __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeSwiftSource                          __OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);
extern const CFStringRef kUTTypeCPlusPlusSource                      __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeObjectiveCPlusPlusSource             __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeCHeader                              __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeCPlusPlusHeader                      __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeJavaSource                           __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);

#pragma mark - Scripting languages
/*
 *  kUTTypeScript
 *
 *    scripting language source
 *
 *    UTI: public.script
 *    conforms to: public.source-code
 *
 *
 *  kUTTypeAppleScript
 *
 *    AppleScript text format (.applescript)
 *
 *    UTI: com.apple.applescript.text
 *    conforms to: public.script
 *
 *
 *  kUTTypeOSAScript
 *
 *    Open Scripting Architecture script binary format (.scpt)
 *
 *    UTI: com.apple.applescript.script
 *    conforms to: public.data, public.script
 *
 *
 *  kUTTypeOSAScriptBundle
 *
 *    Open Scripting Architecture script bundle format (.scptd)
 *
 *    UTI: com.apple.applescript.script-bundle
 *    conforms to: com.apple.bundle, com.apple.package, public.script
 *
 *
 *  kUTTypeJavaScript
 *
 *    JavaScript source code
 *
 *    UTI: com.netscape.javascript-source
 *    conforms to: public.source-code, public.executable
 *
 *
 *  kUTTypeShellScript
 *
 *    base type for shell scripts
 *
 *    UTI: public.shell-script
 *    conforms to: public.script
 *
 *
 *  kUTTypePerlScript
 *
 *    Perl script
 *
 *    UTI: public.perl-script
 *    conforms to: public.shell-script
 *
 *
 *  kUTTypePythonScript
 *
 *    Python script
 *
 *    UTI: public.python-script
 *    conforms to: public.shell-script
 *
 *
 *  kUTTypeRubyScript
 *
 *    Ruby script
 *
 *    UTI: public.ruby-script
 *    conforms to: public.shell-script
 *
 *
 *  kUTTypePHPScript
 *
 *    PHP script
 *
 *    UTI: public.php-script
 *    conforms to: public.shell-script
 *
 */
extern const CFStringRef kUTTypeScript                               __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
extern const CFStringRef kUTTypeAppleScript                          __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
extern const CFStringRef kUTTypeOSAScript                            __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
extern const CFStringRef kUTTypeOSAScriptBundle                      __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
extern const CFStringRef kUTTypeJavaScript                           __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
extern const CFStringRef kUTTypeShellScript                          __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
extern const CFStringRef kUTTypePerlScript                           __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
extern const CFStringRef kUTTypePythonScript                         __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
extern const CFStringRef kUTTypeRubyScript                           __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
extern const CFStringRef kUTTypePHPScript                            __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

#pragma mark - Serialized data types
/*
 *  kUTTypeJSON
 *
 *    JavaScript object notation (JSON) data
 *    NOTE: JSON almost but doesn't quite conform to
 *    com.netscape.javascript-source
 *
 *    UTI: public.json
 *    conforms to: public.text
 *
 *
 *  kUTTypePropertyList
 *
 *    base type for property lists
 *
 *    UTI: com.apple.property-list
 *    conforms to: public.data
 *
 *
 *  kUTTypeXMLPropertyList
 *
 *    XML property list
 *
 *    UTI: com.apple.xml-property-list
 *    conforms to: public.xml, com.apple.property-list
 *
 *
 *  kUTTypeBinaryPropertyList
 *
 *    XML property list
 *
 *    UTI: com.apple.binary-property-list
 *    conforms to: com.apple.property-list
 *
 */
extern const CFStringRef kUTTypeJSON                                 __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
extern const CFStringRef kUTTypePropertyList                         __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
extern const CFStringRef kUTTypeXMLPropertyList                      __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
extern const CFStringRef kUTTypeBinaryPropertyList                   __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

#pragma mark - Composite content types
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


#pragma mark - Image content types
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
 *
 *
 *  kUTTypeRawImage
 *
 *    base type for raw image data (.raw)
 *
 *    UTI: public.camera-raw-image
 *    conforms to: public.image
 *
 *
 *  kUTTypeScalableVectorGraphics
 *
 *    SVG image
 *
 *    UTI: public.svg-image
 *    conforms to: public.image
 *
 *  kUTTypeLivePhoto
 *
 *    Live Photo
 *
 *    UTI: com.apple.live-photo
 *
 *
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
extern const CFStringRef kUTTypeRawImage                             __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
extern const CFStringRef kUTTypeScalableVectorGraphics               __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
extern const CFStringRef kUTTypeLivePhoto                            __OSX_AVAILABLE_STARTING(__MAC_10_12,__IPHONE_9_1);

#pragma mark - Audiovisual content types
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
 *  kUTTypeMPEG2Video
 *
 *    MPEG-2 video
 *
 *    UTI: public.mpeg-2-video
 *    conforms to: public.video
 *
 *
 *  kUTTypeMPEG2TransportStream
 *
 *    MPEG-2 Transport Stream movie format
 *
 *    UTI: public.mpeg-2-transport-stream
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
 *  kUTTypeMPEG4
 *
 *    MPEG-4 movie
 *
 *    UTI: public.mpeg-4
 *    conforms to: public.movie
 *
 *
 *  kUTTypeMPEG4Audio
 *
 *    MPEG-4 audio layer
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
 *
 *
 *  kUTTypeAppleProtectedMPEG4Video
 *
 *    Apple protected MPEG-4 movie
 *
 *    UTI: com.apple.protected-mpeg-4-video
 *    conforms to: com.apple.m4v-video
 *
 *
 *  kUTTypeAVIMovie
 *
 *    Audio Video Interleaved (AVI) movie format
 *
 *    UTI: public.avi
 *    conforms to: public.movie
 *
 *
 *  kUTTypeAudioInterchangeFileFormat
 *
 *    AIFF audio format
 *
 *    UTI: public.aiff-audio
 *    conforms to: public.aifc-audio
 *
 *
 *  kUTTypeWaveformAudio
 *
 *    Waveform audio format (.wav)
 *
 *    UTI: com.microsoft.waveform-audio
 *    conforms to: public.audio
 *
 *
 *  kUTTypeMIDIAudio
 *
 *    MIDI audio format
 *
 *    UTI: public.midi-audio
 *    conforms to: public.audio
 *
 *
 */
extern const CFStringRef kUTTypeAudiovisualContent                   __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeMovie                                __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeVideo                                __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeAudio                                __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeQuickTimeMovie                       __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeMPEG                                 __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeMPEG2Video                           __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
extern const CFStringRef kUTTypeMPEG2TransportStream                 __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
extern const CFStringRef kUTTypeMP3                                  __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeMPEG4                                __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeMPEG4Audio                           __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeAppleProtectedMPEG4Audio             __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeAppleProtectedMPEG4Video             __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
extern const CFStringRef kUTTypeAVIMovie                             __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
extern const CFStringRef kUTTypeAudioInterchangeFileFormat           __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
extern const CFStringRef kUTTypeWaveformAudio                        __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
extern const CFStringRef kUTTypeMIDIAudio                            __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

/*
 *  kUTTypePlaylist
 *
 *    base type for playlists
 *
 *    UTI: public.playlist
 *
 *
 *  kUTTypeM3UPlaylist
 *
 *    M3U or M3U8 playlist
 *
 *    UTI: public.m3u-playlist
 *    conforms to: public.text, public.playlist
 *
 */
extern const CFStringRef kUTTypePlaylist                             __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
extern const CFStringRef kUTTypeM3UPlaylist                          __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

#pragma mark - Directory types
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
 *  kUTTypePluginBundle
 *
 *    base type for bundle-based plugins
 *
 *    UTI: com.apple.plugin
 *    conforms to: com.apple.bundle, com.apple.package
 *
 *
 *  kUTTypeSpotlightImporter
 *
 *    a Spotlight metadata importer
 *
 *    UTI: com.apple.metadata-importer
 *    conforms to: com.apple.plugin
 *
 *
 *  kUTTypeQuickLookGenerator
 *
 *    a QuickLook preview generator
 *
 *    UTI: com.apple.quicklook-generator
 *    conforms to: com.apple.plugin
 *
 *
 *  kUTTypeXPCService
 *
 *    an XPC service
 *
 *    UTI: com.apple.xpc-service
 *    conforms to: com.apple.bundle, com.apple.package
 *
 *
 *  kUTTypeFramework
 *
 *    a Mac OS X framework
 *
 *    UTI: com.apple.framework
 *    conforms to: com.apple.bundle
 *
 */
extern const CFStringRef kUTTypeFolder                               __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeVolume                               __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypePackage                              __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeBundle                               __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypePluginBundle                         __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
extern const CFStringRef kUTTypeSpotlightImporter                    __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
extern const CFStringRef kUTTypeQuickLookGenerator                   __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
extern const CFStringRef kUTTypeXPCService                           __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
extern const CFStringRef kUTTypeFramework                            __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);


#pragma mark - Application and executable types
/*
 *  kUTTypeApplication
 *
 *    base type for OS X applications, launchable items
 *
 *    UTI: com.apple.application
 *    conforms to: public.executable
 *
 *
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
 *
 *
 *  kUTTypeUnixExecutable
 *
 *    a UNIX executable (flat file)
 *
 *    UTI: public.unix-executable
 *    conforms to: public.data, public.executable
 *
 *
 *  kUTTypeWindowsExecutable
 *
 *    a Windows executable (.exe files)
 *
 *    UTI: com.microsoft.windows-executable
 *    conforms to: public.data, public.executable
 *
 *
 *  kUTTypeJavaClass
 *
 *    a Java class
 *
 *    UTI: com.sun.java-class
 *    conforms to: public.data, public.executable
 *
 *
 *  kUTTypeJavaArchive
 *
 *    a Java archive (.jar)
 *
 *    UTI: com.sun.java-archive
 *    conforms to: public.zip-archive, public.executable
 *
 *
 *  kUTTypeSystemPreferencesPane
 *
 *    a System Preferences pane
 *
 *    UTI: com.apple.systempreference.prefpane
 *    conforms to: com.apple.package, com.apple.bundle
 *
 */
// Abstract executable types
extern const CFStringRef kUTTypeApplication                          __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeApplicationBundle                    __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeApplicationFile                      __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeUnixExecutable                       __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

// Other platform binaries
extern const CFStringRef kUTTypeWindowsExecutable                    __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
extern const CFStringRef kUTTypeJavaClass                            __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
extern const CFStringRef kUTTypeJavaArchive                          __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

// Misc. binaries
extern const CFStringRef kUTTypeSystemPreferencesPane                __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

#pragma mark - Archival and compression types
/*
 *  kUTTypeGNUZipArchive
 *
 *    a GNU zip archive (gzip)
 *
 *    UTI: org.gnu.gnu-zip-archive
 *    conforms to: public.data, public.archive
 *
 *
 *  kUTTypeBzip2Archive
 *
 *    a bzip2 archive (.bz2)
 *
 *    UTI: public.bzip2-archive
 *    conforms to: public.data, public.archive
 *
 *
 *  kUTTypeZipArchive
 *
 *    a zip archive
 *
 *    UTI: public.zip-archive
 *    conforms to: com.pkware.zip-archive
 *
 */
extern const CFStringRef kUTTypeGNUZipArchive                        __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
extern const CFStringRef kUTTypeBzip2Archive                         __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
extern const CFStringRef kUTTypeZipArchive                           __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);


#pragma mark - Document types
/*
 *  kUTTypeSpreadsheet
 *
 *    base spreadsheet document type
 *
 *    UTI: public.spreadsheet
 *    conforms to: public.content
 *
 *
 *  kUTTypePresentation
 *
 *    base presentation document type
 *
 *    UTI: public.presentation
 *    conforms to: public.composite-content
 *
 *
 *  kUTTypeDatabase
 *
 *    a database store
 *
 *    UTI: public.database
 *
 */
extern const CFStringRef kUTTypeSpreadsheet                          __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
extern const CFStringRef kUTTypePresentation                         __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
extern const CFStringRef kUTTypeDatabase                             __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_8_0);


#pragma mark - Messages, contacts, and calendar types
/*
 *  kUTTypeVCard
 *
 *    VCard format
 *
 *    UTI: public.vcard
 *    conforms to: public.text, public.contact
 *
 *
 *  kUTTypeToDoItem
 *
 *    to-do item
 *
 *    UTI: public.to-do-item
 *
 *
 *  kUTTypeCalendarEvent
 *
 *    calendar event
 *
 *    UTI: public.calendar-event
 *
 *
 *  kUTTypeEmailMessage
 *
 *    e-mail message
 *
 *    UTI: public.email-message
 *    conforms to: public.message
 *
 */
extern const CFStringRef kUTTypeVCard                                __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeToDoItem                             __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
extern const CFStringRef kUTTypeCalendarEvent                        __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
extern const CFStringRef kUTTypeEmailMessage                         __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

#pragma mark - Internet locations
/*
 *  kUTTypeInternetLocation
 *
 *    base type for Apple Internet locations
 *
 *    UTI: com.apple.internet-location
 *    conforms to: public.data
 *
 */
extern const CFStringRef kUTTypeInternetLocation                     __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);


#pragma mark - Miscellaneous types
/*
 *  kUTTypeInkText
 *
 *    Opaque InkText data
 *
 *    UTI: com.apple.ink.inktext
 *    conforms to: public.data
 *
 *
 *  kUTTypeFont
 *
 *    base type for fonts
 *
 *    UTI: public.font
 *
 *
 *  kUTTypeBookmark
 *
 *    bookmark
 *
 *    UTI: public.bookmark
 *
 *
 *  kUTType3DContent
 *
 *    base type for 3D content
 *
 *    UTI: public.3d-content
 *    conforms to: public.content
 *
 *
 *  kUTTypePKCS12
 *
 *    PKCS#12 format
 *
 *    UTI: com.rsa.pkcs-12
 *    conforms to: public.data
 *
 *
 *  kUTTypeX509Certificate
 *
 *    X.509 certificate format
 *
 *    UTI: public.x509-certificate
 *    conforms to: public.data
 *
 *
 *  kUTTypeElectronicPublication
 *
 *    ePub format
 *
 *    UTI: org.idpf.epub-container
 *    conforms to: public.data, public.composite-content
 *
 *
 *  kUTTypeLog
 *
 *    console log
 *
 *    UTI: public.log
 *
 */
extern const CFStringRef kUTTypeInkText                              __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_3_0);
extern const CFStringRef kUTTypeFont                                 __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
extern const CFStringRef kUTTypeBookmark                             __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
extern const CFStringRef kUTType3DContent                            __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
extern const CFStringRef kUTTypePKCS12                               __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
extern const CFStringRef kUTTypeX509Certificate                      __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
extern const CFStringRef kUTTypeElectronicPublication                __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
extern const CFStringRef kUTTypeLog                                  __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);



CF_ASSUME_NONNULL_END



#ifdef __cplusplus
}
#endif



#endif /* __UTCORETYPES__ */
