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
 *  kUTTypeItem   *** DEPRECATED ***
 *
 *    generic base type for most things
 *    (files, directories)
 *
 *    UTI: public.item
 *
 *
 *  kUTTypeContent   *** DEPRECATED ***
 *
 *    base type for anything containing user-viewable document content
 *    (documents, pasteboard data, and document packages.) Types describing
 *    files or packages must also conform to kUTTypeData or kUTTypePackage
 *    in order for the system to bind documents to them.
 *
 *    UTI: public.content
 *
 *
 *  kUTTypeCompositeContent   *** DEPRECATED ***
 *
 *    base type for content formats supporting mixed embedded content
 *    (i.e., compound documents)
 *
 *    UTI: public.composite-content
 *    conforms to: public.content
 *
 *
 *  kUTTypeMessage   *** DEPRECATED ***
 *
 *    base type for messages (email, IM, etc.)
 *
 *    UTI: public.message
 *
 *
 *  kUTTypeContact   *** DEPRECATED ***
 *
 *    contact information, e.g. for a person, group, organization
 *
 *    UTI: public.contact
 *
 *
 *  kUTTypeArchive   *** DEPRECATED ***
 *
 *    an archive of files and directories
 *
 *    UTI: public.archive
 *
 *
 *  kUTTypeDiskImage   *** DEPRECATED ***
 *
 *    a data item mountable as a volume
 *
 *    UTI: public.disk-image
 *
 */
extern const CFStringRef kUTTypeItem                                 API_DEPRECATED("Use UTTypeItem or UTType.item (swift) instead.", ios(3.0, 15.0), macos(10.4, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeContent                              API_DEPRECATED("Use UTTypeContent or UTType.content (swift) instead.", ios(3.0, 15.0), macos(10.4, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeCompositeContent                     API_DEPRECATED("Use UTTypeCompositeContent or UTType.compositeContent (swift) instead.", ios(3.0, 15.0), macos(10.4, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeMessage                              API_DEPRECATED("Use UTTypeMessage or UTType.message (swift) instead.", ios(3.0, 15.0), macos(10.4, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeContact                              API_DEPRECATED("Use UTTypeContact or UTType.contact (swift) instead.", ios(3.0, 15.0), macos(10.4, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeArchive                              API_DEPRECATED("Use UTTypeArchive or UTType.archive (swift) instead.", ios(3.0, 15.0), macos(10.4, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeDiskImage                            API_DEPRECATED("Use UTTypeDiskImage or UTType.diskImage (swift) instead.", ios(3.0, 15.0), macos(10.4, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));

#pragma mark - Concrete base types
/*
 *  kUTTypeData   *** DEPRECATED ***
 *
 *    base type for any sort of simple byte stream,
 *    including files and in-memory data
 *
 *    UTI: public.data
 *    conforms to: public.item
 *
 *
 *  kUTTypeDirectory   *** DEPRECATED ***
 *
 *    file system directory 
 *    (includes packages AND folders)
 *
 *    UTI: public.directory
 *    conforms to: public.item
 *
 *
 *  kUTTypeResolvable   *** DEPRECATED ***
 *
 *    symlink and alias file types conform to this UTI
 *
 *    UTI: com.apple.resolvable
 *
 *
 *  kUTTypeSymLink   *** DEPRECATED ***
 *
 *    a symbolic link
 *
 *    UTI: public.symlink
 *    conforms to: public.item, com.apple.resolvable
 *
 *
 *  kUTTypeExecutable   *** DEPRECATED ***
 *
 *    an executable item
 *    UTI: public.executable
 *    conforms to: public.item
 *
 *
 *  kUTTypeMountPoint   *** DEPRECATED ***
 *
 *    a volume mount point (resolvable, resolves to the root dir of a volume)
 *
 *    UTI: com.apple.mount-point
 *    conforms to: public.item, com.apple.resolvable
 *
 *
 *  kUTTypeAliasFile   *** DEPRECATED ***
 *
 *    a fully-formed alias file
 *
 *    UTI: com.apple.alias-file
 *    conforms to: public.data, com.apple.resolvable
 *
 *
 *  kUTTypeAliasRecord   *** DEPRECATED ***
 *
 *    raw alias data
 *
 *    UTI: com.apple.alias-record
 *    conforms to: public.data, com.apple.resolvable
 *
 *
 *  kUTTypeURLBookmarkData   *** DEPRECATED ***
 *
 *    URL bookmark
 *
 *    UTI: com.apple.bookmark
 *    conforms to: public.data, com.apple.resolvable
 *
 */
extern const CFStringRef kUTTypeAliasRecord                          API_DEPRECATED("The Alias Manager is obsolete.", ios(3.0, 15.0), macos(10.4, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));;
extern const CFStringRef kUTTypeData                                 API_DEPRECATED("Use UTTypeData or UTType.data (swift) instead.", ios(3.0, 15.0), macos(10.4, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeDirectory                            API_DEPRECATED("Use UTTypeDirectory or UTType.directory (swift) instead.", ios(3.0, 15.0), macos(10.4, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeResolvable                           API_DEPRECATED("Use UTTypeResolvable or UTType.resolvable (swift) instead.", ios(3.0, 15.0), macos(10.4, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeSymLink                              API_DEPRECATED("Use UTTypeSymbolicLink or UTType.symbolicLink (swift) instead.", ios(3.0, 15.0), macos(10.4, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeExecutable                           API_DEPRECATED("Use UTTypeExecutable or UTType.executable (swift) instead.", ios(8.0, 15.0), macos(10.5, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeMountPoint                           API_DEPRECATED("Use UTTypeMountPoint or UTType.mountPoint (swift) instead.", ios(3.0, 15.0), macos(10.4, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeAliasFile                            API_DEPRECATED("Use UTTypeAliasFile or UTType.aliasFile (swift) instead.", ios(3.0, 15.0), macos(10.4, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeURLBookmarkData                      API_DEPRECATED("Use UTTypeURLBookmarkData or UTType.urlBookmarkData (swift) instead.", ios(8.0, 15.0), macos(10.10, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));

#pragma mark - URL types
/*
 *  kUTTypeURL   *** DEPRECATED ***
 *
 *    The bytes of a URL
 *    (OSType 'url ')
 *
 *    UTI: public.url
 *    conforms to: public.data
 *
 *
 *  kUTTypeFileURL   *** DEPRECATED ***
 *
 *    The text of a "file:" URL 
 *    (OSType 'furl')
 *
 *    UTI: public.file-url
 *    conforms to: public.url
 *
 */
extern const CFStringRef kUTTypeURL                                  API_DEPRECATED("Use UTTypeURL or UTType.url (swift) instead.", ios(3.0, 15.0), macos(10.4, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeFileURL                              API_DEPRECATED("Use UTTypeFileURL or UTType.fileURL (swift) instead.", ios(3.0, 15.0), macos(10.4, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));

#pragma mark - Text types
/*
 *  kUTTypeText   *** DEPRECATED ***
 *
 *    base type for all text-encoded data, 
 *    including text with markup (HTML, RTF, etc.)
 *
 *    UTI: public.text
 *    conforms to: public.data, public.content
 *
 *
 *  kUTTypePlainText   *** DEPRECATED ***
 *
 *    text with no markup, unspecified encoding
 *
 *    UTI: public.plain-text
 *    conforms to: public.text
 *
 *
 *  kUTTypeUTF8PlainText   *** DEPRECATED ***
 *
 *    plain text, UTF-8 encoding
 *    (OSType 'utf8', NSPasteboardType "NSStringPBoardType")
 *
 *    UTI: public.utf8-plain-text
 *    conforms to: public.plain-text
 *
 *
 *  kUTTypeUTF16ExternalPlainText   *** DEPRECATED ***
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
 *  kUTTypeUTF16PlainText   *** DEPRECATED ***
 *
 *    plain text, UTF-16 encoding, native byte order, optional BOM
 *    (OSType 'utxt')
 *
 *    UTI: public.utf16-plain-text
 *    conforms to: public.plain-text
 *
 *
 *  kUTTypeDelimitedText   *** DEPRECATED ***
 *
 *    text containing delimited values
 *
 *    UTI: public.delimited-values-text
 *    conforms to: public.text
 *
 *
 *  kUTTypeCommaSeparatedText   *** DEPRECATED ***
 *
 *    text containing comma-separated values (.csv)
 *
 *    UTI: public.comma-separated-values-text
 *    conforms to: public.delimited-values-text
 *
 *
 *  kUTTypeTabSeparatedText   *** DEPRECATED ***
 *
 *    text containing tab-separated values
 *
 *    UTI: public.tab-separated-values-text
 *    conforms to: public.delimited-values-text
 *
 *
 *  kUTTypeUTF8TabSeparatedText   *** DEPRECATED ***
 *
 *    UTF-8 encoded text containing tab-separated values
 *
 *    UTI: public.utf8-tab-separated-values-text
 *    conforms to: public.tab-separated-values-text, public.utf8-plain-text
 *
 *
 *  kUTTypeRTF   *** DEPRECATED ***
 *
 *    Rich Text Format
 *
 *    UTI: public.rtf
 *    conforms to: public.text
 *
 */
extern const CFStringRef kUTTypeText                                 API_DEPRECATED("Use UTTypeText or UTType.text (swift) instead.", ios(3.0, 15.0), macos(10.4, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypePlainText                            API_DEPRECATED("Use UTTypePlainText or UTType.plainText (swift) instead.", ios(3.0, 15.0), macos(10.4, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeUTF8PlainText                        API_DEPRECATED("Use UTTypeUTF8PlainText or UTType.utf8PlainText (swift) instead.", ios(3.0, 15.0), macos(10.4, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeUTF16ExternalPlainText               API_DEPRECATED("Use UTTypeUTF16ExternalPlainText or UTType.utf16ExternalPlainText (swift) instead.", ios(3.0, 15.0), macos(10.4, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeUTF16PlainText                       API_DEPRECATED("Use UTTypeUTF16PlainText or UTType.utf16PlainText (swift) instead.", ios(3.0, 15.0), macos(10.4, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeDelimitedText                        API_DEPRECATED("Use UTTypeDelimitedText or UTType.delimitedText (swift) instead.", ios(8.0, 15.0), macos(10.10, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeCommaSeparatedText                   API_DEPRECATED("Use UTTypeCommaSeparatedText or UTType.commaSeparatedText (swift) instead.", ios(8.0, 15.0), macos(10.10, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeTabSeparatedText                     API_DEPRECATED("Use UTTypeTabSeparatedText or UTType.tabSeparatedText (swift) instead.", ios(8.0, 15.0), macos(10.10, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeUTF8TabSeparatedText                 API_DEPRECATED("Use UTTypeUTF8TabSeparatedText or UTType.utf8tabSeparatedText (swift) instead.", ios(8.0, 15.0), macos(10.10, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeRTF                                  API_DEPRECATED("Use UTTypeRTF or UTType.rtf (swift) instead.", ios(3.0, 15.0), macos(10.4, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));

#pragma mark - Markup languages
/*
 *  kUTTypeHTML   *** DEPRECATED ***
 *
 *    HTML, any version
 *
 *    UTI: public.html
 *    conforms to: public.text
 *
 *
 *  kUTTypeXML   *** DEPRECATED ***
 *
 *    generic XML
 *
 *    UTI: public.xml
 *    conforms to: public.text
 *
 */
extern const CFStringRef kUTTypeHTML                                 API_DEPRECATED("Use UTTypeHTML or UTType.html (swift) instead.", ios(3.0, 15.0), macos(10.4, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeXML                                  API_DEPRECATED("Use UTTypeXML or UTType.xml (swift) instead.", ios(3.0, 15.0), macos(10.4, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));

#pragma mark - Programming languages
/*
 *  kUTTypeSourceCode   *** DEPRECATED ***
 *
 *    abstract type for source code (any language)
 *
 *    UTI: public.source-code
 *    conforms to: public.plain-text
 *
 *
 *  kUTTypeAssemblyLanguageSource   *** DEPRECATED ***
 *
 *    assembly language source (.s)
 *
 *    UTI: public.assembly-source
 *    conforms to: public.source-code
 *
 *
 *  kUTTypeCSource   *** DEPRECATED ***
 *
 *    C source code (.c)
 *
 *    UTI: public.c-source
 *    conforms to: public.source-code
 *
 *
 *  kUTTypeObjectiveCSource   *** DEPRECATED ***
 *
 *    Objective-C source code (.m)
 *
 *    UTI: public.objective-c-source
 *    conforms to: public.source-code
 *
 *
 *  kUTTypeSwiftSource   *** DEPRECATED ***
 *
 *    Swift source code (.swift)
 *
 *    UTI: public.swift-source
 *    conforms to: public.source-code
 *
 *
 *  kUTTypeCPlusPlusSource   *** DEPRECATED ***
 *
 *    C++ source code (.cp, etc.)
 *
 *    UTI: public.c-plus-plus-source
 *    conforms to: public.source-code
 *
 *
 *  kUTTypeObjectiveCPlusPlusSource   *** DEPRECATED ***
 *
 *    Objective-C++ source code
 *
 *    UTI: public.objective-c-plus-plus-source
 *    conforms to: public.source-code
 *
 *
 *  kUTTypeCHeader   *** DEPRECATED ***
 *
 *    C header
 *
 *    UTI: public.c-header
 *    conforms to: public.source-code
 *
 *
 *  kUTTypeCPlusPlusHeader   *** DEPRECATED ***
 *
 *    C++ header
 *
 *    UTI: public.c-plus-plus-header
 *    conforms to: public.source-code
 *
 *
 *  kUTTypeJavaSource   *** DEPRECATED ***
 *
 *    Java source code
 *
 *    UTI: com.sun.java-source
 *    conforms to: public.source-code
 *
 */
extern const CFStringRef kUTTypeJavaSource                           API_DEPRECATED("Java support is no longer provided by this operating system. Install a JDK to use Java.", ios(3.0, 15.0), macos(10.4, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));;
extern const CFStringRef kUTTypeSourceCode                           API_DEPRECATED("Use UTTypeSourceCode or UTType.sourceCode (swift) instead.", ios(3.0, 15.0), macos(10.4, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeAssemblyLanguageSource               API_DEPRECATED("Use UTTypeAssemblyLanguageSource or UTType.assemblyLanguageSource (swift) instead.", ios(8.0, 15.0), macos(10.10, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeCSource                              API_DEPRECATED("Use UTTypeCSource or UTType.cSource (swift) instead.", ios(3.0, 15.0), macos(10.4, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeObjectiveCSource                     API_DEPRECATED("Use UTTypeObjectiveCSource or UTType.objectiveCSource (swift) instead.", ios(3.0, 15.0), macos(10.4, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeSwiftSource                          API_DEPRECATED("Use UTTypeSwiftSource or UTType.swiftSource (swift) instead.", ios(9.0, 15.0), macos(10.11, 12.0), tvos(9.0, 15.0), watchos(2.0, 8.0));
extern const CFStringRef kUTTypeCPlusPlusSource                      API_DEPRECATED("Use UTTypeCPlusPlusSource or UTType.cPlusPlusSource (swift) instead.", ios(3.0, 15.0), macos(10.4, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeObjectiveCPlusPlusSource             API_DEPRECATED("Use UTTypeObjectiveCPlusPlusSource or UTType.objectiveCPlusPlusSource (swift) instead.", ios(3.0, 15.0), macos(10.4, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeCHeader                              API_DEPRECATED("Use UTTypeCHeader or UTType.cHeader (swift) instead.", ios(3.0, 15.0), macos(10.4, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeCPlusPlusHeader                      API_DEPRECATED("Use UTTypeCPlusPlusHeader or UTType.cPlusPlusHeader (swift) instead.", ios(3.0, 15.0), macos(10.4, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));

#pragma mark - Scripting languages
/*
 *  kUTTypeScript   *** DEPRECATED ***
 *
 *    scripting language source
 *
 *    UTI: public.script
 *    conforms to: public.source-code
 *
 *
 *  kUTTypeAppleScript   *** DEPRECATED ***
 *
 *    AppleScript text format (.applescript)
 *
 *    UTI: com.apple.applescript.text
 *    conforms to: public.script
 *
 *
 *  kUTTypeOSAScript   *** DEPRECATED ***
 *
 *    Open Scripting Architecture script binary format (.scpt)
 *
 *    UTI: com.apple.applescript.script
 *    conforms to: public.data, public.script
 *
 *
 *  kUTTypeOSAScriptBundle   *** DEPRECATED ***
 *
 *    Open Scripting Architecture script bundle format (.scptd)
 *
 *    UTI: com.apple.applescript.script-bundle
 *    conforms to: com.apple.bundle, com.apple.package, public.script
 *
 *
 *  kUTTypeJavaScript   *** DEPRECATED ***
 *
 *    JavaScript source code
 *
 *    UTI: com.netscape.javascript-source
 *    conforms to: public.source-code, public.executable
 *
 *
 *  kUTTypeShellScript   *** DEPRECATED ***
 *
 *    base type for shell scripts
 *
 *    UTI: public.shell-script
 *    conforms to: public.script
 *
 *
 *  kUTTypePerlScript   *** DEPRECATED ***
 *
 *    Perl script
 *
 *    UTI: public.perl-script
 *    conforms to: public.shell-script
 *
 *
 *  kUTTypePythonScript   *** DEPRECATED ***
 *
 *    Python script
 *
 *    UTI: public.python-script
 *    conforms to: public.shell-script
 *
 *
 *  kUTTypeRubyScript   *** DEPRECATED ***
 *
 *    Ruby script
 *
 *    UTI: public.ruby-script
 *    conforms to: public.shell-script
 *
 *
 *  kUTTypePHPScript   *** DEPRECATED ***
 *
 *    PHP script
 *
 *    UTI: public.php-script
 *    conforms to: public.shell-script
 *
 */
extern const CFStringRef kUTTypeScript                               API_DEPRECATED("Use UTTypeScript or UTType.script (swift) instead.", ios(8.0, 15.0), macos(10.10, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeAppleScript                          API_DEPRECATED("Use UTTypeAppleScript or UTType.appleScript (swift) instead.", ios(8.0, 15.0), macos(10.10, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeOSAScript                            API_DEPRECATED("Use UTTypeOSAScript or UTType.osaScript (swift) instead.", ios(8.0, 15.0), macos(10.10, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeOSAScriptBundle                      API_DEPRECATED("Use UTTypeOSAScriptBundle or UTType.osaScriptBundle (swift) instead.", ios(8.0, 15.0), macos(10.10, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeJavaScript                           API_DEPRECATED("Use UTTypeJavaScript or UTType.javaScript (swift) instead.", ios(8.0, 15.0), macos(10.10, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeShellScript                          API_DEPRECATED("Use UTTypeShellScript or UTType.shellScript (swift) instead.", ios(8.0, 15.0), macos(10.10, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypePerlScript                           API_DEPRECATED("Use UTTypePerlScript or UTType.perlScript (swift) instead.", ios(8.0, 15.0), macos(10.10, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypePythonScript                         API_DEPRECATED("Use UTTypePythonScript or UTType.pythonScript (swift) instead.", ios(8.0, 15.0), macos(10.10, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeRubyScript                           API_DEPRECATED("Use UTTypeRubyScript or UTType.rubyScript (swift) instead.", ios(8.0, 15.0), macos(10.10, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypePHPScript                            API_DEPRECATED("Use UTTypePHPScript or UTType.phpScript (swift) instead.", ios(8.0, 15.0), macos(10.10, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));

#pragma mark - Serialized data types
/*
 *  kUTTypeJSON   *** DEPRECATED ***
 *
 *    JavaScript object notation (JSON) data
 *    NOTE: JSON almost but doesn't quite conform to
 *    com.netscape.javascript-source
 *
 *    UTI: public.json
 *    conforms to: public.text
 *
 *
 *  kUTTypePropertyList   *** DEPRECATED ***
 *
 *    base type for property lists
 *
 *    UTI: com.apple.property-list
 *    conforms to: public.data
 *
 *
 *  kUTTypeXMLPropertyList   *** DEPRECATED ***
 *
 *    XML property list
 *
 *    UTI: com.apple.xml-property-list
 *    conforms to: public.xml, com.apple.property-list
 *
 *
 *  kUTTypeBinaryPropertyList   *** DEPRECATED ***
 *
 *    XML property list
 *
 *    UTI: com.apple.binary-property-list
 *    conforms to: com.apple.property-list
 *
 */
extern const CFStringRef kUTTypeJSON                                 API_DEPRECATED("Use UTTypeJSON or UTType.json (swift) instead.", ios(8.0, 15.0), macos(10.10, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypePropertyList                         API_DEPRECATED("Use UTTypePropertyList or UTType.propertyList (swift) instead.", ios(8.0, 15.0), macos(10.10, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeXMLPropertyList                      API_DEPRECATED("Use UTTypeXMLPropertyList or UTType.xmlPropertyList (swift) instead.", ios(8.0, 15.0), macos(10.10, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeBinaryPropertyList                   API_DEPRECATED("Use UTTypeBinaryPropertyList or UTType.binaryPropertyList (swift) instead.", ios(8.0, 15.0), macos(10.10, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));

#pragma mark - Composite content types
/*
 *  kUTTypePDF   *** DEPRECATED ***
 *
 *    Adobe PDF
 *
 *    UTI: com.adobe.pdf
 *    conforms to: public.data, public.composite-content
 *
 *
 *  kUTTypeRTFD   *** DEPRECATED ***
 *
 *    Rich Text Format Directory 
 *    (RTF with content embedding, on-disk format)
 *
 *    UTI: com.apple.rtfd
 *    conforms to: com.apple.package, public.composite-content
 *
 *
 *  kUTTypeFlatRTFD   *** DEPRECATED ***
 *
 *    Flattened RTFD (pasteboard format)
 *
 *    UTI: com.apple.flat-rtfd
 *    conforms to: public.data, public.composite-content
 *
 *
 *  kUTTypeTXNTextAndMultimediaData   *** DEPRECATED ***
 *
 *    MLTE (Textension) format for mixed text & multimedia data
 *    (OSType 'txtn')
 *
 *    UTI: com.apple.txn.text-multimedia-data
 *    conforms to: public.data, public.composite-content
 *
 *
 *  kUTTypeWebArchive   *** DEPRECATED ***
 *
 *    The WebKit webarchive format
 *
 *    UTI: com.apple.webarchive
 *    conforms to: public.data, public.composite-content
 */
extern const CFStringRef kUTTypeTXNTextAndMultimediaData             API_DEPRECATED("The Multilingual Text Engine is obsolete.", ios(3.0, 15.0), macos(10.4, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));;
extern const CFStringRef kUTTypePDF                                  API_DEPRECATED("Use UTTypePDF or UTType.pdf (swift) instead.", ios(3.0, 15.0), macos(10.4, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeRTFD                                 API_DEPRECATED("Use UTTypeRTFD or UTType.RTFD (swift) instead.", ios(3.0, 15.0), macos(10.4, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeFlatRTFD                             API_DEPRECATED("Use UTTypeFlatRTFD or UTType.flatRTFD (swift) instead.", ios(3.0, 15.0), macos(10.4, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeWebArchive                           API_DEPRECATED("Use UTTypeWebArchive or UTType.webArchive (swift) instead.", ios(3.0, 15.0), macos(10.4, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));


#pragma mark - Image content types
/*
 *  kUTTypeImage   *** DEPRECATED ***
 *
 *    abstract image data
 *
 *    UTI: public.image
 *    conforms to: public.data, public.content
 *
 *
 *  kUTTypeJPEG   *** DEPRECATED ***
 *
 *    JPEG image
 *
 *    UTI: public.jpeg
 *    conforms to: public.image
 *
 *
 *  kUTTypeJPEG2000   *** DEPRECATED ***
 *
 *    JPEG-2000 image
 *
 *    UTI: public.jpeg-2000
 *    conforms to: public.image
 *
 *
 *  kUTTypeTIFF   *** DEPRECATED ***
 *
 *    TIFF image
 *
 *    UTI: public.tiff
 *    conforms to: public.image
 *
 *
 *  kUTTypePICT   *** DEPRECATED ***
 *
 *    Quickdraw PICT format
 *
 *    UTI: com.apple.pict
 *    conforms to: public.image
 *
 *
 *  kUTTypeGIF   *** DEPRECATED ***
 *
 *    GIF image
 *
 *    UTI: com.compuserve.gif
 *    conforms to: public.image
 *
 *
 *  kUTTypePNG   *** DEPRECATED ***
 *
 *    PNG image
 *
 *    UTI: public.png
 *    conforms to: public.image
 *
 *
 *  kUTTypeQuickTimeImage   *** DEPRECATED ***
 *
 *    QuickTime image format (OSType 'qtif')
 *
 *    UTI: com.apple.quicktime-image
 *    conforms to: public.image
 *
 *
 *  kUTTypeAppleICNS   *** DEPRECATED ***
 *
 *    Apple icon data
 *
 *    UTI: com.apple.icns
 *    conforms to: public.image
 *
 *
 *  kUTTypeBMP   *** DEPRECATED ***
 *
 *    Windows bitmap
 *
 *    UTI: com.microsoft.bmp
 *    conforms to: public.image
 *
 *
 *  kUTTypeICO   *** DEPRECATED ***
 *
 *    Windows icon data
 *
 *    UTI: com.microsoft.ico
 *    conforms to: public.image
 *
 *
 *  kUTTypeRawImage   *** DEPRECATED ***
 *
 *    base type for raw image data (.raw)
 *
 *    UTI: public.camera-raw-image
 *    conforms to: public.image
 *
 *
 *  kUTTypeScalableVectorGraphics   *** DEPRECATED ***
 *
 *    SVG image
 *
 *    UTI: public.svg-image
 *    conforms to: public.image
 *
 *  kUTTypeLivePhoto   *** DEPRECATED ***
 *
 *    Live Photo
 *
 *    UTI: com.apple.live-photo
 *
 *
 */
extern const CFStringRef kUTTypeJPEG2000                             API_DEPRECATED("JPEG2000 is no longer supported by this operating system.", ios(3.0, 15.0), macos(10.4, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));;
extern const CFStringRef kUTTypeQuickTimeImage                       API_DEPRECATED("The QuickTime Image file format is obsolete.", ios(3.0, 15.0), macos(10.4, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));;
extern const CFStringRef kUTTypeImage                                API_DEPRECATED("Use UTTypeImage or UTType.image (swift) instead.", ios(3.0, 15.0), macos(10.4, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeJPEG                                 API_DEPRECATED("Use UTTypeJPEG or UTType.jpeg (swift) instead.", ios(3.0, 15.0), macos(10.4, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeTIFF                                 API_DEPRECATED("Use UTTypeTIFF or UTType.tiff (swift) instead.", ios(3.0, 15.0), macos(10.4, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypePICT                                 API_DEPRECATED("QuickDraw is obsolete.", ios(3.0, 15.0), macos(10.4, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeGIF                                  API_DEPRECATED("Use UTTypeGIF or UTType.gif (swift) instead.", ios(3.0, 15.0), macos(10.4, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypePNG                                  API_DEPRECATED("Use UTTypePNG or UTType.png (swift) instead.", ios(3.0, 15.0), macos(10.4, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeAppleICNS                            API_DEPRECATED("Use UTTypeICNS or UTType.icns (swift) instead.", ios(3.0, 15.0), macos(10.4, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeBMP                                  API_DEPRECATED("Use UTTypeBMP or UTType.bmp (swift) instead.", ios(3.0, 15.0), macos(10.4, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeICO                                  API_DEPRECATED("Use UTTypeICO or UTType.ico (swift) instead.", ios(3.0, 15.0), macos(10.4, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeRawImage                             API_DEPRECATED("Use UTTypeRAWImage or UTType.rawImage (swift) instead.", ios(8.0, 15.0), macos(10.10, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeScalableVectorGraphics               API_DEPRECATED("Use UTTypeSVG or UTType.svg (swift) instead.", ios(8.0, 15.0), macos(10.10, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeLivePhoto                            API_DEPRECATED("Use UTTypeLivePhoto or UTType.livePhoto (swift) instead.", ios(9.1, 15.0), macos(10.12, 12.0), tvos(9.0, 15.0), watchos(2.1, 8.0));

#pragma mark - Audiovisual content types
/*
 *  kUTTypeAudiovisualContent   *** DEPRECATED ***
 *
 *    audio and/or video content
 *
 *    UTI: public.audiovisual-content
 *    conforms to: public.data, public.content
 *
 *
 *  kUTTypeMovie   *** DEPRECATED ***
 *
 *    A media format which may contain both video and audio
 *    Corresponds to what users would label a "movie"
 *
 *    UTI: public.movie
 *    conforms to: public.audiovisual-content
 *
 *
 *  kUTTypeVideo   *** DEPRECATED ***
 *
 *    pure video (no audio)
 *
 *    UTI: public.video
 *    conforms to: public.movie
 *
 *
 *  kUTTypeAudio   *** DEPRECATED ***
 *
 *    pure audio (no video)
 *
 *    UTI: public.audio
 *    conforms to: public.audiovisual-content
 *
 *
 *  kUTTypeQuickTimeMovie   *** DEPRECATED ***
 *
 *    QuickTime movie
 *
 *    UTI: com.apple.quicktime-movie
 *    conforms to: public.movie
 *
 *
 *  kUTTypeMPEG   *** DEPRECATED ***
 *
 *    MPEG-1 or MPEG-2 movie
 *
 *    UTI: public.mpeg
 *    conforms to: public.movie
 *
 *
 *  kUTTypeMPEG2Video   *** DEPRECATED ***
 *
 *    MPEG-2 video
 *
 *    UTI: public.mpeg-2-video
 *    conforms to: public.video
 *
 *
 *  kUTTypeMPEG2TransportStream   *** DEPRECATED ***
 *
 *    MPEG-2 Transport Stream movie format
 *
 *    UTI: public.mpeg-2-transport-stream
 *    conforms to: public.movie
 *
 *
 *  kUTTypeMP3   *** DEPRECATED ***
 *
 *    MP3 audio
 *
 *    UTI: public.mp3
 *    conforms to: public.audio
 *
 *
 *  kUTTypeMPEG4   *** DEPRECATED ***
 *
 *    MPEG-4 movie
 *
 *    UTI: public.mpeg-4
 *    conforms to: public.movie
 *
 *
 *  kUTTypeMPEG4Audio   *** DEPRECATED ***
 *
 *    MPEG-4 audio layer
 *
 *    UTI: public.mpeg-4-audio
 *    conforms to: public.mpeg-4, public.audio
 *
 *
 *  kUTTypeAppleProtectedMPEG4Audio   *** DEPRECATED ***
 *
 *    Apple protected MPEG4 format
 *    (.m4p, iTunes music store format)
 *
 *    UTI: com.apple.protected-mpeg-4-audio
 *    conforms to: public.audio
 *
 *
 *  kUTTypeAppleProtectedMPEG4Video   *** DEPRECATED ***
 *
 *    Apple protected MPEG-4 movie
 *
 *    UTI: com.apple.protected-mpeg-4-video
 *    conforms to: com.apple.m4v-video
 *
 *
 *  kUTTypeAVIMovie   *** DEPRECATED ***
 *
 *    Audio Video Interleaved (AVI) movie format
 *
 *    UTI: public.avi
 *    conforms to: public.movie
 *
 *
 *  kUTTypeAudioInterchangeFileFormat   *** DEPRECATED ***
 *
 *    AIFF audio format
 *
 *    UTI: public.aiff-audio
 *    conforms to: public.aifc-audio
 *
 *
 *  kUTTypeWaveformAudio   *** DEPRECATED ***
 *
 *    Waveform audio format (.wav)
 *
 *    UTI: com.microsoft.waveform-audio
 *    conforms to: public.audio
 *
 *
 *  kUTTypeMIDIAudio   *** DEPRECATED ***
 *
 *    MIDI audio format
 *
 *    UTI: public.midi-audio
 *    conforms to: public.audio
 *
 *
 */
extern const CFStringRef kUTTypeAudiovisualContent                   API_DEPRECATED("Use UTTypeAudiovisualContent or UTType.audiovisualcontent (swift) instead.", ios(3.0, 15.0), macos(10.4, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeMovie                                API_DEPRECATED("Use UTTypeMovie or UTType.movie (swift) instead.", ios(3.0, 15.0), macos(10.4, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeVideo                                API_DEPRECATED("Use UTTypeVideo or UTType.video (swift) instead.", ios(3.0, 15.0), macos(10.4, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeAudio                                API_DEPRECATED("Use UTTypeAudio or UTType.audio (swift) instead.", ios(3.0, 15.0), macos(10.4, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeQuickTimeMovie                       API_DEPRECATED("Use UTTypeQuickTimeMovie or UTType.quickTimeMovie (swift) instead.", ios(3.0, 15.0), macos(10.4, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeMPEG                                 API_DEPRECATED("Use UTTypeMPEG or UTType.mpeg (swift) instead.", ios(3.0, 15.0), macos(10.4, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeMPEG2Video                           API_DEPRECATED("Use UTTypeMPEG2Video or UTType.mpeg2Video (swift) instead.", ios(8.0, 15.0), macos(10.10, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeMPEG2TransportStream                 API_DEPRECATED("Use UTTypeMPEG2TransportStream or UTType.mpeg2TransportStream (swift) instead.", ios(8.0, 15.0), macos(10.10, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeMP3                                  API_DEPRECATED("Use UTTypeMP3 or UTType.mp3 (swift) instead.", ios(3.0, 15.0), macos(10.4, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeMPEG4                                API_DEPRECATED("Use UTTypeMPEG4Movie or UTType.mpeg4 (swift) instead.", ios(3.0, 15.0), macos(10.4, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeMPEG4Audio                           API_DEPRECATED("Use UTTypeMPEG4Audio or UTType.mpeg4Audio (swift) instead.", ios(3.0, 15.0), macos(10.4, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeAppleProtectedMPEG4Audio             API_DEPRECATED("Use UTTypeAppleProtectedMPEG4Audio or UTType.appleProtectedMPEG4Audio (swift) instead.", ios(3.0, 15.0), macos(10.4, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeAppleProtectedMPEG4Video             API_DEPRECATED("Use UTTypeAppleProtectedMPEG4Video or UTType.appleProtectedMPEG4Video (swift) instead.", ios(8.0, 15.0), macos(10.10, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeAVIMovie                             API_DEPRECATED("Use UTTypeAVI or UTType.avi (swift) instead.", ios(8.0, 15.0), macos(10.10, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeAudioInterchangeFileFormat           API_DEPRECATED("Use UTTypeAIFF or UTType.aiff (swift) instead.", ios(8.0, 15.0), macos(10.10, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeWaveformAudio                        API_DEPRECATED("Use UTTypeWAV or UTType.wav (swift) instead.", ios(8.0, 15.0), macos(10.10, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeMIDIAudio                            API_DEPRECATED("Use UTTypeMIDI or UTType.MIDIAudio (swift) instead.", ios(8.0, 15.0), macos(10.10, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));

/*
 *  kUTTypePlaylist   *** DEPRECATED ***
 *
 *    base type for playlists
 *
 *    UTI: public.playlist
 *
 *
 *  kUTTypeM3UPlaylist   *** DEPRECATED ***
 *
 *    M3U or M3U8 playlist
 *
 *    UTI: public.m3u-playlist
 *    conforms to: public.text, public.playlist
 *
 */
extern const CFStringRef kUTTypePlaylist                             API_DEPRECATED("Use UTTypePlaylist or UTType.playlist (swift) instead.", ios(8.0, 15.0), macos(10.10, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeM3UPlaylist                          API_DEPRECATED("Use UTTypeM3UPlaylist or UTType.m3uPlaylist (swift) instead.", ios(8.0, 15.0), macos(10.10, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));

#pragma mark - Directory types
/*
 *  kUTTypeFolder   *** DEPRECATED ***
 *
 *    a user-browsable directory (i.e., not a package)
 *
 *    UTI: public.folder
 *    conforms to: public.directory
 *
 *
 *  kUTTypeVolume   *** DEPRECATED ***
 *
 *    the root folder of a volume/mount point
 *
 *    UTI: public.volume
 *    conforms to: public.folder
 *
 *
 *  kUTTypePackage   *** DEPRECATED ***
 *
 *    a packaged directory
 *
 *    UTI: com.apple.package
 *    conforms to: public.directory
 *
 *
 *  kUTTypeBundle   *** DEPRECATED ***
 *
 *    a directory conforming to one of the CFBundle layouts
 *
 *    UTI: com.apple.bundle
 *    conforms to: public.directory
 *
 *
 *  kUTTypePluginBundle   *** DEPRECATED ***
 *
 *    base type for bundle-based plugins
 *
 *    UTI: com.apple.plugin
 *    conforms to: com.apple.bundle, com.apple.package
 *
 *
 *  kUTTypeSpotlightImporter   *** DEPRECATED ***
 *
 *    a Spotlight metadata importer
 *
 *    UTI: com.apple.metadata-importer
 *    conforms to: com.apple.plugin
 *
 *
 *  kUTTypeQuickLookGenerator   *** DEPRECATED ***
 *
 *    a QuickLook preview generator
 *
 *    UTI: com.apple.quicklook-generator
 *    conforms to: com.apple.plugin
 *
 *
 *  kUTTypeXPCService   *** DEPRECATED ***
 *
 *    an XPC service
 *
 *    UTI: com.apple.xpc-service
 *    conforms to: com.apple.bundle, com.apple.package
 *
 *
 *  kUTTypeFramework   *** DEPRECATED ***
 *
 *    a Mac OS X framework
 *
 *    UTI: com.apple.framework
 *    conforms to: com.apple.bundle
 *
 */
extern const CFStringRef kUTTypeFolder                               API_DEPRECATED("Use UTTypeFolder or UTType.folder (swift) instead.", ios(3.0, 15.0), macos(10.4, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeVolume                               API_DEPRECATED("Use UTTypeVolume or UTType.volume (swift) instead.", ios(3.0, 15.0), macos(10.4, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypePackage                              API_DEPRECATED("Use UTTypePackage or UTType.package (swift) instead.", ios(3.0, 15.0), macos(10.4, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeBundle                               API_DEPRECATED("Use UTTypeBundle or UTType.bundle (swift) instead.", ios(3.0, 15.0), macos(10.4, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypePluginBundle                         API_DEPRECATED("Use UTTypePluginBundle or UTType.pluginBundle (swift) instead.", ios(8.0, 15.0), macos(10.10, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeSpotlightImporter                    API_DEPRECATED("Use UTTypeSpotlightImporter or UTType.spotlightImporter (swift) instead.", ios(8.0, 15.0), macos(10.10, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeQuickLookGenerator                   API_DEPRECATED("Use UTTypeQuickLookGenerator or UTType.quickLookGenerator (swift) instead.", ios(8.0, 15.0), macos(10.10, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeXPCService                           API_DEPRECATED("Use UTTypeXPCService or UTType.xpcService (swift) instead.", ios(8.0, 15.0), macos(10.10, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeFramework                            API_DEPRECATED("Use UTTypeFramework or UTType.framework (swift) instead.", ios(3.0, 15.0), macos(10.4, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));


#pragma mark - Application and executable types
/*
 *  kUTTypeApplication   *** DEPRECATED ***
 *
 *    base type for OS X applications, launchable items
 *
 *    UTI: com.apple.application
 *    conforms to: public.executable
 *
 *
 *  kUTTypeApplicationBundle   *** DEPRECATED ***
 *
 *    a bundled application
 *
 *    UTI: com.apple.application-bundle
 *    conforms to: com.apple.application, com.apple.bundle, com.apple.package
 *
 *
 *  kUTTypeApplicationFile   *** DEPRECATED ***
 *
 *    a single-file Carbon/Classic application 
 *
 *    UTI: com.apple.application-file
 *    conforms to: com.apple.application, public.data
 *
 *
 *  kUTTypeUnixExecutable   *** DEPRECATED ***
 *
 *    a UNIX executable (flat file)
 *
 *    UTI: public.unix-executable
 *    conforms to: public.data, public.executable
 *
 *
 *  kUTTypeWindowsExecutable   *** DEPRECATED ***
 *
 *    a Windows executable (.exe files)
 *
 *    UTI: com.microsoft.windows-executable
 *    conforms to: public.data, public.executable
 *
 *
 *  kUTTypeJavaClass   *** DEPRECATED ***
 *
 *    a Java class
 *
 *    UTI: com.sun.java-class
 *    conforms to: public.data, public.executable
 *
 *
 *  kUTTypeJavaArchive   *** DEPRECATED ***
 *
 *    a Java archive (.jar)
 *
 *    UTI: com.sun.java-archive
 *    conforms to: public.zip-archive, public.executable
 *
 *
 *  kUTTypeSystemPreferencesPane   *** DEPRECATED ***
 *
 *    a System Preferences pane
 *
 *    UTI: com.apple.systempreference.prefpane
 *    conforms to: com.apple.package, com.apple.bundle
 *
 */
// Abstract executable types
extern const CFStringRef kUTTypeApplication                          API_DEPRECATED("Use UTTypeApplication or UTType.application (swift) instead.", ios(3.0, 15.0), macos(10.4, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeApplicationBundle                    API_DEPRECATED("Use UTTypeApplicationBundle or UTType.applicationBundle (swift) instead.", ios(3.0, 15.0), macos(10.4, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeApplicationFile                      API_DEPRECATED("Classic applications are obsolete.", ios(3.0, 15.0), macos(10.4, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeUnixExecutable                       API_DEPRECATED("Use UTTypeUnixExecutable or UTType.unixExecutable (swift) instead.", ios(8.0, 15.0), macos(10.10, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));

// Other platform binaries
extern const CFStringRef kUTTypeJavaClass                            API_DEPRECATED("Java support is no longer provided by this operating system. Install a JDK to use Java.", ios(8.0, 15.0), macos(10.10, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));;
extern const CFStringRef kUTTypeJavaArchive                          API_DEPRECATED("Java support is no longer provided by this operating system. Install a JDK to use Java.", ios(8.0, 15.0), macos(10.10, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));;
extern const CFStringRef kUTTypeWindowsExecutable                    API_DEPRECATED("Use UTTypeEXE or UTType.windowsExecutable (swift) instead.", ios(8.0, 15.0), macos(10.10, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));

// Misc. binaries
extern const CFStringRef kUTTypeSystemPreferencesPane                API_DEPRECATED("Use UTTypeSystemPreferencesPane or UTType.systemPreferencesPane (swift) instead.", ios(8.0, 15.0), macos(10.10, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));

#pragma mark - Archival and compression types
/*
 *  kUTTypeGNUZipArchive   *** DEPRECATED ***
 *
 *    a GNU zip archive (gzip)
 *
 *    UTI: org.gnu.gnu-zip-archive
 *    conforms to: public.data, public.archive
 *
 *
 *  kUTTypeBzip2Archive   *** DEPRECATED ***
 *
 *    a bzip2 archive (.bz2)
 *
 *    UTI: public.bzip2-archive
 *    conforms to: public.data, public.archive
 *
 *
 *  kUTTypeZipArchive   *** DEPRECATED ***
 *
 *    a zip archive
 *
 *    UTI: public.zip-archive
 *    conforms to: com.pkware.zip-archive
 *
 */
extern const CFStringRef kUTTypeGNUZipArchive                        API_DEPRECATED("Use UTTypeGZIP or UTType.gnu (swift) instead.", ios(8.0, 15.0), macos(10.10, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeBzip2Archive                         API_DEPRECATED("Use UTTypeBZ2 or UTType.bzip2 (swift) instead.", ios(8.0, 15.0), macos(10.10, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeZipArchive                           API_DEPRECATED("Use UTTypeZIP or UTType.zip (swift) instead.", ios(8.0, 15.0), macos(10.10, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));


#pragma mark - Document types
/*
 *  kUTTypeSpreadsheet   *** DEPRECATED ***
 *
 *    base spreadsheet document type
 *
 *    UTI: public.spreadsheet
 *    conforms to: public.content
 *
 *
 *  kUTTypePresentation   *** DEPRECATED ***
 *
 *    base presentation document type
 *
 *    UTI: public.presentation
 *    conforms to: public.composite-content
 *
 *
 *  kUTTypeDatabase   *** DEPRECATED ***
 *
 *    a database store
 *
 *    UTI: public.database
 *
 */
extern const CFStringRef kUTTypeSpreadsheet                          API_DEPRECATED("Use UTTypeSpreadsheet or UTType.spreadsheet (swift) instead.", ios(8.0, 15.0), macos(10.10, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypePresentation                         API_DEPRECATED("Use UTTypePresentation or UTType.presentation (swift) instead.", ios(8.0, 15.0), macos(10.10, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeDatabase                             API_DEPRECATED("Use UTTypeDatabase or UTType.database (swift) instead.", ios(8.0, 15.0), macos(10.4, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));


#pragma mark - Messages, contacts, and calendar types
/*
 *  kUTTypeVCard   *** DEPRECATED ***
 *
 *    VCard format
 *
 *    UTI: public.vcard
 *    conforms to: public.text, public.contact
 *
 *
 *  kUTTypeToDoItem   *** DEPRECATED ***
 *
 *    to-do item
 *
 *    UTI: public.to-do-item
 *
 *
 *  kUTTypeCalendarEvent   *** DEPRECATED ***
 *
 *    calendar event
 *
 *    UTI: public.calendar-event
 *
 *
 *  kUTTypeEmailMessage   *** DEPRECATED ***
 *
 *    e-mail message
 *
 *    UTI: public.email-message
 *    conforms to: public.message
 *
 */
extern const CFStringRef kUTTypeVCard                                API_DEPRECATED("Use UTTypeVCard or UTType.vCard (swift) instead.", ios(3.0, 15.0), macos(10.4, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeToDoItem                             API_DEPRECATED("Use UTTypeToDoItem or UTType.toDoItem (swift) instead.", ios(8.0, 15.0), macos(10.10, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeCalendarEvent                        API_DEPRECATED("Use UTTypeCalendarEvent or UTType.calendarEvent (swift) instead.", ios(8.0, 15.0), macos(10.10, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeEmailMessage                         API_DEPRECATED("Use UTTypeEmailMessage or UTType.emailMessage (swift) instead.", ios(8.0, 15.0), macos(10.10, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));

#pragma mark - Internet locations
/*
 *  kUTTypeInternetLocation   *** DEPRECATED ***
 *
 *    base type for Apple Internet locations
 *
 *    UTI: com.apple.internet-location
 *    conforms to: public.data
 *
 */
extern const CFStringRef kUTTypeInternetLocation                     API_DEPRECATED("Use UTTypeInternetLocation or UTType.internetLocation (swift) instead.", ios(8.0, 15.0), macos(10.10, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));


#pragma mark - Miscellaneous types
/*
 *  kUTTypeInkText   *** DEPRECATED ***
 *
 *    Opaque InkText data
 *
 *    UTI: com.apple.ink.inktext
 *    conforms to: public.data
 *
 *
 *  kUTTypeFont   *** DEPRECATED ***
 *
 *    base type for fonts
 *
 *    UTI: public.font
 *
 *
 *  kUTTypeBookmark   *** DEPRECATED ***
 *
 *    bookmark
 *
 *    UTI: public.bookmark
 *
 *
 *  kUTType3DContent   *** DEPRECATED ***
 *
 *    base type for 3D content
 *
 *    UTI: public.3d-content
 *    conforms to: public.content
 *
 *
 *  kUTTypePKCS12   *** DEPRECATED ***
 *
 *    PKCS#12 format
 *
 *    UTI: com.rsa.pkcs-12
 *    conforms to: public.data
 *
 *
 *  kUTTypeX509Certificate   *** DEPRECATED ***
 *
 *    X.509 certificate format
 *
 *    UTI: public.x509-certificate
 *    conforms to: public.data
 *
 *
 *  kUTTypeElectronicPublication   *** DEPRECATED ***
 *
 *    ePub format
 *
 *    UTI: org.idpf.epub-container
 *    conforms to: public.data, public.composite-content
 *
 *
 *  kUTTypeLog   *** DEPRECATED ***
 *
 *    console log
 *
 *    UTI: public.log
 *
 */
extern const CFStringRef kUTTypeInkText                              API_DEPRECATED("The Ink framework is obsolete.", ios(3.0, 15.0), macos(10.4, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));;
extern const CFStringRef kUTTypeFont                                 API_DEPRECATED("Use UTTypeFont or UTType.font (swift) instead.", ios(8.0, 15.0), macos(10.10, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeBookmark                             API_DEPRECATED("Use UTTypeBookmark or UTType.bookmark (swift) instead.", ios(8.0, 15.0), macos(10.10, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTType3DContent                            API_DEPRECATED("Use UTType3DContent or UTType.threeDContent (swift) instead.", ios(8.0, 15.0), macos(10.10, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypePKCS12                               API_DEPRECATED("Use UTTypePKCS12 or UTType.pkcs12 (swift) instead.", ios(8.0, 15.0), macos(10.10, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeX509Certificate                      API_DEPRECATED("Use UTTypeX509Certificate or UTType.x509Certificate (swift) instead.", ios(8.0, 15.0), macos(10.10, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeElectronicPublication                API_DEPRECATED("Use UTTypeEPUB or UTType.electronicPublication (swift) instead.", ios(8.0, 15.0), macos(10.10, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));
extern const CFStringRef kUTTypeLog                                  API_DEPRECATED("Use UTTypeLog or UTType.log (swift) instead.", ios(8.0, 15.0), macos(10.10, 12.0), tvos(9.0, 15.0), watchos(1.0, 8.0));



CF_ASSUME_NONNULL_END



#ifdef __cplusplus
}
#endif



#endif /* __UTCORETYPES__ */
