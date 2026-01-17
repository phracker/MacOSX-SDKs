//
//  UTCoreTypes.h
//
//  Copyright © 2020 Apple. All rights reserved.
//

#ifndef __UNIFORMTYPEIDENTIFIERS_UTCORETYPES__
#define __UNIFORMTYPEIDENTIFIERS_UTCORETYPES__

#import <Foundation/Foundation.h>

#import <UniformTypeIdentifiers/UTDefines.h>
#import <UniformTypeIdentifiers/UTType.h>

__BEGIN_DECLS
NS_ASSUME_NONNULL_BEGIN
UT_AVAILABLE_BEGIN

#pragma mark - Abstract base types

/**
	\brief A generic base type for most things (files, directories.)

	UTI: public.item
*/
UT_EXPORT UTType *const UTTypeItem NS_REFINED_FOR_SWIFT;

/**
	\brief A base type for anything containing user-viewable document content
		(documents, pasteboard data, and document packages.)

	Types describing files or packages must also conform to \c UTTypeData or
	\c UTTypePackage in order for the system to bind documents to them.

	UTI: public.content
*/
UT_EXPORT UTType *const UTTypeContent NS_REFINED_FOR_SWIFT;

/**
	\brief A base type for content formats supporting mixed embedded content
		(i.e., compound documents).

	UTI: public.composite-content

	conforms to: public.content
*/
UT_EXPORT UTType *const UTTypeCompositeContent NS_REFINED_FOR_SWIFT;

/**
	\brief A data item mountable as a volume

	UTI: public.disk-image
*/
UT_EXPORT UTType *const UTTypeDiskImage NS_REFINED_FOR_SWIFT;

#pragma mark - Concrete base types

/**
	\brief A base type for any sort of simple byte stream, including files and
		in-memory data.

	UTI: public.data

	conforms to: public.item
*/
UT_EXPORT UTType *const UTTypeData NS_REFINED_FOR_SWIFT;

/**
	\brief A file system directory (includes packages \em and folders.)

	UTI: public.directory

	conforms to: public.item
*/
UT_EXPORT UTType *const UTTypeDirectory NS_REFINED_FOR_SWIFT;

/**
	\brief Symbolic link and alias file types conform to this type.

	UTI: com.apple.resolvable
*/
UT_EXPORT UTType *const UTTypeResolvable NS_REFINED_FOR_SWIFT;

/**
	\brief A symbolic link.

	UTI: public.symlink

	conforms to: public.item, com.apple.resolvable
*/
UT_EXPORT UTType *const UTTypeSymbolicLink NS_REFINED_FOR_SWIFT;

/**
	\brief An executable item.

	UTI: public.executable

	conforms to: public.item
*/
UT_EXPORT UTType *const UTTypeExecutable NS_REFINED_FOR_SWIFT;

/**
	\brief A volume mount point (resolvable, resolves to the root directory of a
		volume.)

	UTI: com.apple.mount-point

	conforms to: public.item, com.apple.resolvable
*/
UT_EXPORT UTType *const UTTypeMountPoint NS_REFINED_FOR_SWIFT;

/**
	\brief A fully-formed alias file.

	UTI: com.apple.alias-file

	conforms to: public.data, com.apple.resolvable
*/
UT_EXPORT UTType *const UTTypeAliasFile NS_REFINED_FOR_SWIFT;

/**
	\brief A URL bookmark.

	UTI: com.apple.bookmark

	conforms to: public.data, com.apple.resolvable
*/
UT_EXPORT UTType *const UTTypeURLBookmarkData NS_REFINED_FOR_SWIFT;

#pragma mark - URL types

/**
	\brief Any URL.

	UTI: public.url

	conforms to: public.data
*/
UT_EXPORT UTType *const UTTypeURL NS_REFINED_FOR_SWIFT;

/**
	\brief A URL with the scheme \c "file:".

	UTI: public.file-url

	conforms to: public.url
*/
UT_EXPORT UTType *const UTTypeFileURL NS_REFINED_FOR_SWIFT;

#pragma mark - Text types

/**
	\brief The base type for all text-encoded data, including text with markup
		(HTML, RTF, etc.).

	UTI: public.text

	conforms to: public.data, public.content
*/
UT_EXPORT UTType *const UTTypeText NS_REFINED_FOR_SWIFT;

/**
	\brief Text with no markup and an unspecified encoding.

	UTI: public.plain-text

	conforms to: public.text
*/
UT_EXPORT UTType *const UTTypePlainText NS_REFINED_FOR_SWIFT;

/**
	\brief Plain text encoded as UTF-8.

	UTI: public.utf8-plain-text

	conforms to: public.plain-text
*/
UT_EXPORT UTType *const UTTypeUTF8PlainText NS_REFINED_FOR_SWIFT;

/**
	\brief Plain text encoded as UTF-16 with a BOM, or if a BOM is not present,
		using "external representation" byte order (big-endian).

	UTI: public.utf16-external-plain-text

	conforms to: public.plain-text
*/
UT_EXPORT UTType *const UTTypeUTF16ExternalPlainText NS_REFINED_FOR_SWIFT;

/**
	\brief Plain text encoded as UTF-16, in native byte order, with an optional
		BOM.

	UTI: public.utf16-plain-text

	conforms to: public.plain-text
*/
UT_EXPORT UTType *const UTTypeUTF16PlainText NS_REFINED_FOR_SWIFT;

/**
	\brief Text containing delimited values.

	UTI: public.delimited-values-text

	conforms to: public.text
*/
UT_EXPORT UTType *const UTTypeDelimitedText NS_REFINED_FOR_SWIFT;

/**
	\brief Text containing comma-separated values (.csv).

	UTI: public.comma-separated-values-text

	conforms to: public.delimited-values-text
*/
UT_EXPORT UTType *const UTTypeCommaSeparatedText NS_REFINED_FOR_SWIFT;

/**
	\brief Text containing tab-separated values.

	UTI: public.tab-separated-values-text

	conforms to: public.delimited-values-text
*/
UT_EXPORT UTType *const UTTypeTabSeparatedText NS_REFINED_FOR_SWIFT;

/**
	\brief UTF-8 encoded text containing tab-separated values.

	UTI: public.utf8-tab-separated-values-text

	conforms to: public.tab-separated-values-text, public.utf8-plain-text
*/
UT_EXPORT UTType *const UTTypeUTF8TabSeparatedText NS_REFINED_FOR_SWIFT;

/**
	\brief Rich Text Format data.

	UTI: public.rtf

	conforms to: public.text
*/
UT_EXPORT UTType *const UTTypeRTF NS_REFINED_FOR_SWIFT;

#pragma mark - Markup languages

/**
	\brief Any version of HTML.

	UTI: public.html

	conforms to: public.text
*/
UT_EXPORT UTType *const UTTypeHTML NS_REFINED_FOR_SWIFT;

/**
	\brief Generic XML.

	UTI: public.xml

	conforms to: public.text
*/
UT_EXPORT UTType *const UTTypeXML NS_REFINED_FOR_SWIFT;

/**
	\brief Yet Another Markup Language.

	UTI: public.yaml

	conforms to: public.text
*/
UT_EXPORT UTType *const UTTypeYAML NS_REFINED_FOR_SWIFT;

#pragma mark - Programming languages
/**
	\brief Abstract type for source code of any language.

	UTI: public.source-code

	conforms to: public.plain-text
*/
UT_EXPORT UTType *const UTTypeSourceCode NS_REFINED_FOR_SWIFT;

/**
	\brief Assembly language source (.s)

	UTI: public.assembly-source

	conforms to: public.source-code
*/
UT_EXPORT UTType *const UTTypeAssemblyLanguageSource NS_REFINED_FOR_SWIFT;

/**
	\brief C source code (.c)

	UTI: public.c-source

	conforms to: public.source-code
*/
UT_EXPORT UTType *const UTTypeCSource NS_REFINED_FOR_SWIFT;

/**
	\brief Objective-C source code (.m)

	UTI: public.objective-c-source

	conforms to: public.source-code
*/
UT_EXPORT UTType *const UTTypeObjectiveCSource NS_REFINED_FOR_SWIFT;

/**
	\brief Swift source code (.swift)

	UTI: public.swift-source

	conforms to: public.source-code
*/
UT_EXPORT UTType *const UTTypeSwiftSource NS_REFINED_FOR_SWIFT;

/**
	\brief C++ source code (.cp, etc.)

	UTI: public.c-plus-plus-source

	conforms to: public.source-code
*/
UT_EXPORT UTType *const UTTypeCPlusPlusSource NS_REFINED_FOR_SWIFT;

/**
	\brief Objective-C++ source code.

	UTI: public.objective-c-plus-plus-source

	conforms to: public.source-code
*/
UT_EXPORT UTType *const UTTypeObjectiveCPlusPlusSource NS_REFINED_FOR_SWIFT;

/**
	\brief A C header.

	UTI: public.c-header

	conforms to: public.source-code
*/
UT_EXPORT UTType *const UTTypeCHeader NS_REFINED_FOR_SWIFT;

/**
	\brief A C++ header.

	UTI: public.c-plus-plus-header

	conforms to: public.source-code
*/
UT_EXPORT UTType *const UTTypeCPlusPlusHeader NS_REFINED_FOR_SWIFT;

#pragma mark - Scripting languages

/**
	\brief A base type for any scripting language source.

	UTI: public.script

	conforms to: public.source-code
*/
UT_EXPORT UTType *const UTTypeScript NS_REFINED_FOR_SWIFT;

/**
	\brief An AppleScript text-based script (.applescript).

	UTI: com.apple.applescript.text

	conforms to: public.script
*/
UT_EXPORT UTType *const UTTypeAppleScript NS_REFINED_FOR_SWIFT;

/**
	\brief An Open Scripting Architecture binary script (.scpt).

	UTI: com.apple.applescript.script

	conforms to: public.data, public.script
*/
UT_EXPORT UTType *const UTTypeOSAScript NS_REFINED_FOR_SWIFT;

/**
	\brief An Open Scripting Architecture script bundle (.scptd).

	UTI: com.apple.applescript.script-bundle

	conforms to: com.apple.bundle, com.apple.package, public.script
*/
UT_EXPORT UTType *const UTTypeOSAScriptBundle NS_REFINED_FOR_SWIFT;

/**
	\brief JavaScript source code

	UTI: com.netscape.javascript-source

	conforms to: public.source-code, public.executable
*/
UT_EXPORT UTType *const UTTypeJavaScript NS_REFINED_FOR_SWIFT;

/**
	\brief The base type for shell scripts.

	UTI: public.shell-script

	conforms to: public.script
*/
UT_EXPORT UTType *const UTTypeShellScript NS_REFINED_FOR_SWIFT;

/**
	\brief A Perl script.

	UTI: public.perl-script

	conforms to: public.shell-script
*/
UT_EXPORT UTType *const UTTypePerlScript NS_REFINED_FOR_SWIFT;

/**
	\brief A Python script.

	UTI: public.python-script

	conforms to: public.shell-script
*/
UT_EXPORT UTType *const UTTypePythonScript NS_REFINED_FOR_SWIFT;

/**
	\brief A Ruby script.

	UTI: public.ruby-script

	conforms to: public.shell-script
*/
UT_EXPORT UTType *const UTTypeRubyScript NS_REFINED_FOR_SWIFT;

/**
	\brief A PHP script.

	UTI: public.php-script

	conforms to: public.shell-script
*/
UT_EXPORT UTType *const UTTypePHPScript NS_REFINED_FOR_SWIFT;

#pragma mark - Serialized data types
/**
	\brief JavaScript object notation (JSON) data

	UTI: public.json

	conforms to: public.text

	\note JSON almost (but doesn't quite) conforms to
		com.netscape.javascript-source.
*/
UT_EXPORT UTType *const UTTypeJSON NS_REFINED_FOR_SWIFT;

/**
	\brief A base type for property lists.

	UTI: com.apple.property-list

	conforms to: public.data
*/
UT_EXPORT UTType *const UTTypePropertyList NS_REFINED_FOR_SWIFT;

/**
	\brief An XML property list.

	UTI: com.apple.xml-property-list

	conforms to: public.xml, com.apple.property-list
*/
UT_EXPORT UTType *const UTTypeXMLPropertyList NS_REFINED_FOR_SWIFT;

/**
	\brief A binary property list.

	UTI: com.apple.binary-property-list

	conforms to: com.apple.property-list
*/
UT_EXPORT UTType *const UTTypeBinaryPropertyList NS_REFINED_FOR_SWIFT;

#pragma mark - Composite content types

/**
	\brief An Adobe PDF document.

	UTI: com.adobe.pdf

	conforms to: public.data, public.composite-content
*/
UT_EXPORT UTType *const UTTypePDF NS_REFINED_FOR_SWIFT;

/**
	\brief A Rich Text Format Directory document (RTF with content embedding
		in its on-disk format.)

	UTI: com.apple.rtfd

	conforms to: com.apple.package, public.composite-content
*/
UT_EXPORT UTType *const UTTypeRTFD NS_REFINED_FOR_SWIFT;

/**
	\brief A flattened RTFD document (formatted for the pasteboard.)

	UTI: com.apple.flat-rtfd

	conforms to: public.data, public.composite-content
*/
UT_EXPORT UTType *const UTTypeFlatRTFD NS_REFINED_FOR_SWIFT;

/**
	\brief The WebKit webarchive format.

	UTI: com.apple.webarchive

	conforms to: public.data, public.composite-content
*/
UT_EXPORT UTType *const UTTypeWebArchive NS_REFINED_FOR_SWIFT;

#pragma mark - Image content types

/**
	\brief A base type for abstract image data.

	UTI: public.image

	conforms to: public.data, public.content
*/
UT_EXPORT UTType *const UTTypeImage NS_REFINED_FOR_SWIFT;

/**
	\brief A JPEG image.

	UTI: public.jpeg

	conforms to: public.image
*/
UT_EXPORT UTType *const UTTypeJPEG NS_REFINED_FOR_SWIFT;

/**
	\brief A TIFF image.

	UTI: public.tiff

	conforms to: public.image
*/
UT_EXPORT UTType *const UTTypeTIFF NS_REFINED_FOR_SWIFT;

/**
	\brief A GIF image.

	UTI: com.compuserve.gif

	conforms to: public.image
*/
UT_EXPORT UTType *const UTTypeGIF NS_REFINED_FOR_SWIFT;

/**
	\brief A PNG image.

	UTI: public.png

	conforms to: public.image
*/
UT_EXPORT UTType *const UTTypePNG NS_REFINED_FOR_SWIFT;

/**
	\brief Apple icon data

	UTI: com.apple.icns

	conforms to: public.image
*/
UT_EXPORT UTType *const UTTypeICNS NS_REFINED_FOR_SWIFT;

/**
	\brief A Windows bitmap.

	UTI: com.microsoft.bmp

	conforms to: public.image
*/
UT_EXPORT UTType *const UTTypeBMP NS_REFINED_FOR_SWIFT;

/**
	\brief Windows icon data

	UTI: com.microsoft.ico

	conforms to: public.image
*/
UT_EXPORT UTType *const UTTypeICO NS_REFINED_FOR_SWIFT;

/**
	\brief A base type for raw image data (.raw).

	UTI: public.camera-raw-image

	conforms to: public.image
*/
UT_EXPORT UTType *const UTTypeRAWImage NS_REFINED_FOR_SWIFT;

/**
	\brief A Scalable Vector Graphics image.

	UTI: public.svg-image

	conforms to: public.image
*/
UT_EXPORT UTType *const UTTypeSVG NS_REFINED_FOR_SWIFT;

/**
	\brief A Live Photo.

	UTI: com.apple.live-photo
*/
UT_EXPORT UTType *const UTTypeLivePhoto NS_REFINED_FOR_SWIFT;

/**
	\brief A High Efficiency Image File Format image.

	UTI: public.heif

	conforms to: public.heif-standard
*/
UT_EXPORT UTType *const UTTypeHEIF NS_REFINED_FOR_SWIFT;

/**
	\brief A High Efficiency Image Coding image.

	UTI: public.heic

	conforms to: public.heif-standard
*/
UT_EXPORT UTType *const UTTypeHEIC NS_REFINED_FOR_SWIFT;

/**
	\brief The WebP image format.

	UTI: org.webmproject.webp

	conforms to: public.image
*/
UT_EXPORT UTType *const UTTypeWebP NS_REFINED_FOR_SWIFT;

#pragma mark - 3D Content

/**
	\brief A base type for 3D content.

	UTI: public.3d-content

	conforms to: public.content
*/
UT_EXPORT UTType *const UTType3DContent NS_REFINED_FOR_SWIFT;

/**
	\brief Universal Scene Description content.

	UTI: com.pixar.universal-scene-description

	conforms to: public.3d-content, public.data
*/
UT_EXPORT UTType *const UTTypeUSD NS_REFINED_FOR_SWIFT;

/**
	\brief Universal Scene Description Package content.

	UTI: com.pixar.universal-scene-description-mobile

	conforms to: public.3d-content, public.data
*/
UT_EXPORT UTType *const UTTypeUSDZ NS_REFINED_FOR_SWIFT;

/**
	\brief A Reality File.

	UTI: com.apple.reality

	conforms to: public.data
*/
UT_EXPORT UTType *const UTTypeRealityFile NS_REFINED_FOR_SWIFT;

/**
	\brief A SceneKit serialized scene.

	UTI: com.apple.scenekit.scene

	conforms to: public.3d-content, public.data
*/
UT_EXPORT UTType *const UTTypeSceneKitScene NS_REFINED_FOR_SWIFT;

/**
	\brief An AR reference object.

	UTI: com.apple.arobject

	conforms to: public.data
*/
UT_EXPORT UTType *const UTTypeARReferenceObject NS_REFINED_FOR_SWIFT;

/**
	\brief Any audio and/or video content.

	UTI: public.audiovisual-content

	conforms to: public.data, public.content
*/
UT_EXPORT UTType *const UTTypeAudiovisualContent NS_REFINED_FOR_SWIFT;

/**
	\brief A media format which may contain both video and audio.

	This type corresponds to what users would label a "movie".

	UTI: public.movie

	conforms to: public.audiovisual-content
*/
UT_EXPORT UTType *const UTTypeMovie NS_REFINED_FOR_SWIFT;

/**
	\brief Pure video data with no audio data.

	UTI: public.video

	conforms to: public.movie
*/
UT_EXPORT UTType *const UTTypeVideo NS_REFINED_FOR_SWIFT;

/**
	\brief Pure audio data with no video data.

	UTI: public.audio

	conforms to: public.audiovisual-content
*/
UT_EXPORT UTType *const UTTypeAudio NS_REFINED_FOR_SWIFT;

/**
	\brief A QuickTime movie.

	UTI: com.apple.quicktime-movie

	conforms to: public.movie
*/
UT_EXPORT UTType *const UTTypeQuickTimeMovie NS_REFINED_FOR_SWIFT;

/**
	\brief An MPEG-1 or MPEG-2 movie.

	UTI: public.mpeg

	conforms to: public.movie
*/
UT_EXPORT UTType *const UTTypeMPEG NS_REFINED_FOR_SWIFT;

/**
	\brief An MPEG-2 video.

	UTI: public.mpeg-2-video

	conforms to: public.video
*/
UT_EXPORT UTType *const UTTypeMPEG2Video NS_REFINED_FOR_SWIFT;

/**
	\brief The MPEG-2 Transport Stream movie format.

	UTI: public.mpeg-2-transport-stream

	conforms to: public.movie
*/
UT_EXPORT UTType *const UTTypeMPEG2TransportStream NS_REFINED_FOR_SWIFT;

/**
	\brief MP3 audio.

	UTI: public.mp3

	conforms to: public.audio
*/
UT_EXPORT UTType *const UTTypeMP3 NS_REFINED_FOR_SWIFT;

/**
	\brief MPEG-4 movie

	UTI: public.mpeg-4

	conforms to: public.movie
*/
UT_EXPORT UTType *const UTTypeMPEG4Movie NS_REFINED_FOR_SWIFT;

/**
	\brief An MPEG-4 audio layer file.

	UTI: public.mpeg-4-audio

	conforms to: public.mpeg-4, public.audio
*/
UT_EXPORT UTType *const UTTypeMPEG4Audio NS_REFINED_FOR_SWIFT;

/**
	\brief The Apple protected MPEG4 format (.m4p, iTunes music store format.)

	UTI: com.apple.protected-mpeg-4-audio

	conforms to: public.audio
*/
UT_EXPORT UTType *const UTTypeAppleProtectedMPEG4Audio NS_REFINED_FOR_SWIFT;

/**
	\brief An Apple protected MPEG-4 movie.

	UTI: com.apple.protected-mpeg-4-video

	conforms to: com.apple.m4v-video
*/
UT_EXPORT UTType *const UTTypeAppleProtectedMPEG4Video NS_REFINED_FOR_SWIFT;

/**
	\brief The AVI movie format.

	UTI: public.avi

	conforms to: public.movie
*/
UT_EXPORT UTType *const UTTypeAVI NS_REFINED_FOR_SWIFT;

/**
	\brief The AIFF audio format

	UTI: public.aiff-audio

	conforms to: public.aifc-audio
*/
UT_EXPORT UTType *const UTTypeAIFF NS_REFINED_FOR_SWIFT;

/**
	\brief The Microsoft waveform audio format (.wav).

	UTI: com.microsoft.waveform-audio

	conforms to: public.audio
*/
UT_EXPORT UTType *const UTTypeWAV NS_REFINED_FOR_SWIFT;

/**
	\brief The MIDI audio format.

	UTI: public.midi-audio

	conforms to: public.audio
*/
UT_EXPORT UTType *const UTTypeMIDI NS_REFINED_FOR_SWIFT;

/**
	\brief The base type for playlists.

	UTI: public.playlist
*/
UT_EXPORT UTType *const UTTypePlaylist NS_REFINED_FOR_SWIFT;

/**
	\brief An M3U or M3U8 playlist

	UTI: public.m3u-playlist

	conforms to: public.text, public.playlist
*/
UT_EXPORT UTType *const UTTypeM3UPlaylist NS_REFINED_FOR_SWIFT;

#pragma mark - Directory types

/**
	\brief A user-browsable directory (i.e. not a package.)

	UTI: public.folder

	conforms to: public.directory
*/
UT_EXPORT UTType *const UTTypeFolder NS_REFINED_FOR_SWIFT;

/**
	\brief The root folder of a volume or mount point.

	UTI: public.volume

	conforms to: public.folder
*/
UT_EXPORT UTType *const UTTypeVolume NS_REFINED_FOR_SWIFT;

/**
	\brief A packaged directory.

	Bundles differ from packages in that a bundle has an internal file hierarchy
	that \c CFBundle can read, while packages are displayed to the user as if
	they were regular files. A single file system object can be both a package
	and a bundle.

	UTI: com.apple.package

	conforms to: public.directory
*/
UT_EXPORT UTType *const UTTypePackage NS_REFINED_FOR_SWIFT;

/**
	\brief A directory conforming to one of the \c CFBundle layouts.

	Bundles differ from packages in that a bundle has an internal file hierarchy
	that \c CFBundle can read, while packages are displayed to the user as if
	they were regular files. A single file system object can be both a package
	and a bundle.

	UTI: com.apple.bundle

	conforms to: public.directory
*/
UT_EXPORT UTType *const UTTypeBundle NS_REFINED_FOR_SWIFT;

/**
	\brief The base type for bundle-based plugins.

	UTI: com.apple.plugin

	conforms to: com.apple.bundle, com.apple.package
*/
UT_EXPORT UTType *const UTTypePluginBundle NS_REFINED_FOR_SWIFT;

/**
	\brief A Spotlight metadata importer bundle.

	UTI: com.apple.metadata-importer

	conforms to: com.apple.plugin
*/
UT_EXPORT UTType *const UTTypeSpotlightImporter NS_REFINED_FOR_SWIFT;

/**
	\brief A QuickLook preview generator bundle.

	UTI: com.apple.quicklook-generator

	conforms to: com.apple.plugin
*/
UT_EXPORT UTType *const UTTypeQuickLookGenerator NS_REFINED_FOR_SWIFT;

/**
	\brief An XPC service bundle.

	UTI: com.apple.xpc-service

	conforms to: com.apple.bundle, com.apple.package
*/
UT_EXPORT UTType *const UTTypeXPCService NS_REFINED_FOR_SWIFT;

/**
	\brief A macOS or iOS framework bundle.

	UTI: com.apple.framework

	conforms to: com.apple.bundle
*/
UT_EXPORT UTType *const UTTypeFramework NS_REFINED_FOR_SWIFT;

#pragma mark - Application and executable types

/**
	\brief The base type for macOS and iOS applications.

	UTI: com.apple.application

	conforms to: public.executable
*/
UT_EXPORT UTType *const UTTypeApplication NS_REFINED_FOR_SWIFT;

/**
	\brief A bundled application.

	UTI: com.apple.application-bundle

	conforms to: com.apple.application, com.apple.bundle, com.apple.package
*/
UT_EXPORT UTType *const UTTypeApplicationBundle NS_REFINED_FOR_SWIFT;

/**
	\brief An application extension (.appex).

	UTI: com.apple.application-and-system-extension

	conforms to: com.apple.xpc-service
*/
UT_EXPORT UTType *const UTTypeApplicationExtension NS_REFINED_FOR_SWIFT;

/**
	\brief A UNIX executable (flat file.)

	UTI: public.unix-executable

	conforms to: public.data, public.executable
*/
UT_EXPORT UTType *const UTTypeUnixExecutable NS_REFINED_FOR_SWIFT;

/**
	\brief A Windows executable (.exe).

	UTI: com.microsoft.windows-executable

	conforms to: public.data, public.executable
*/
UT_EXPORT UTType *const UTTypeEXE NS_REFINED_FOR_SWIFT;

/**
	\brief A System Preferences pane.

	UTI: com.apple.systempreference.prefpane

	conforms to: com.apple.package, com.apple.bundle
*/
UT_EXPORT UTType *const UTTypeSystemPreferencesPane NS_REFINED_FOR_SWIFT;

#pragma mark - Archival and compression types

/**
	\brief an archive of files and directories

	UTI: public.archive
*/
UT_EXPORT UTType *const UTTypeArchive NS_REFINED_FOR_SWIFT;

/**
	\brief A GNU zip archive.

	UTI: org.gnu.gnu-zip-archive

	conforms to: public.data, public.archive
*/
UT_EXPORT UTType *const UTTypeGZIP NS_REFINED_FOR_SWIFT;

/**
	\brief A bzip2 archive.

	UTI: public.bzip2-archive

	conforms to: public.data, public.archive
*/
UT_EXPORT UTType *const UTTypeBZ2 NS_REFINED_FOR_SWIFT;

/**
	\brief A zip archive.

	UTI: public.zip-archive

	conforms to: com.pkware.zip-archive
*/
UT_EXPORT UTType *const UTTypeZIP NS_REFINED_FOR_SWIFT;

/**
    \brief An Apple Archive.

    UTI: com.apple.archive

    conforms to: public.data, public.archive
*/
UT_EXPORT UTType *const UTTypeAppleArchive NS_REFINED_FOR_SWIFT;

#pragma mark - Document types

/**
	\brief A base type for spreadsheet documents.

	UTI: public.spreadsheet

	conforms to: public.content
*/
UT_EXPORT UTType *const UTTypeSpreadsheet NS_REFINED_FOR_SWIFT;

/**
	\brief A base type for presentation documents.

	UTI: public.presentation

	conforms to: public.composite-content
*/
UT_EXPORT UTType *const UTTypePresentation NS_REFINED_FOR_SWIFT;

/**
	\brief A database store.

	UTI: public.database
*/
UT_EXPORT UTType *const UTTypeDatabase NS_REFINED_FOR_SWIFT;

#pragma mark - Messages, contacts, and calendar types

/**
	\brief A base type for messages (email, IM, etc.)

	UTI: public.message
*/
UT_EXPORT UTType *const UTTypeMessage NS_REFINED_FOR_SWIFT;

/**
	\brief contact information, e.g. for a person, group, organization

	UTI: public.contact
*/
UT_EXPORT UTType *const UTTypeContact NS_REFINED_FOR_SWIFT;

/**
	\brief A vCard file.

	UTI: public.vcard

	conforms to: public.text, public.contact
*/
UT_EXPORT UTType *const UTTypeVCard NS_REFINED_FOR_SWIFT;

/**
	\brief A to-do item.

	UTI: public.to-do-item
*/
UT_EXPORT UTType *const UTTypeToDoItem NS_REFINED_FOR_SWIFT;

/**
	\brief A calendar event.

	UTI: public.calendar-event
*/
UT_EXPORT UTType *const UTTypeCalendarEvent NS_REFINED_FOR_SWIFT;

/**
	\brief An e-mail message.

	UTI: public.email-message

	conforms to: public.message
*/
UT_EXPORT UTType *const UTTypeEmailMessage NS_REFINED_FOR_SWIFT;

#pragma mark - Internet locations

/**
	\brief A base type for Apple Internet location files.

	UTI: com.apple.internet-location

	conforms to: public.data
*/
UT_EXPORT UTType *const UTTypeInternetLocation NS_REFINED_FOR_SWIFT;

/**
	\brief Microsoft Internet shortcut files (.url).

	UTI: com.apple.internet-location

	conforms to: public.data
*/
UT_EXPORT UTType *const UTTypeInternetShortcut NS_REFINED_FOR_SWIFT;

#pragma mark - Miscellaneous types

/**
	\brief A base type for fonts.

	UTI: public.font
*/
UT_EXPORT UTType *const UTTypeFont NS_REFINED_FOR_SWIFT;

/**
	\brief A bookmark.

	UTI: public.bookmark

	\sa UTTypeURLBookmarkData
*/
UT_EXPORT UTType *const UTTypeBookmark NS_REFINED_FOR_SWIFT;

/**
	\brief PKCS#12 data.

	UTI: com.rsa.pkcs-12

	conforms to: public.data
*/
UT_EXPORT UTType *const UTTypePKCS12 NS_REFINED_FOR_SWIFT;

/**
	\brief An X.509 certificate.

	UTI: public.x509-certificate

	conforms to: public.data
*/
UT_EXPORT UTType *const UTTypeX509Certificate NS_REFINED_FOR_SWIFT;

/**
	\brief The EPUB format.

	UTI: org.idpf.epub-container

	conforms to: public.data, public.composite-content
*/
UT_EXPORT UTType *const UTTypeEPUB NS_REFINED_FOR_SWIFT;

/**
	\brief A base type for console logs.

	UTI: public.log
*/
UT_EXPORT UTType *const UTTypeLog NS_REFINED_FOR_SWIFT;

UT_AVAILABLE_END
NS_ASSUME_NONNULL_END
__END_DECLS

#endif // __UNIFORMTYPEIDENTIFIERS_UTCORETYPES__
