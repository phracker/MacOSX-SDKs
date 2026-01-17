/*	CFURL.h
	Copyright (c) 1998-2009, Apple Inc. All rights reserved.
*/

#if !defined(__COREFOUNDATION_CFURL__)
#define __COREFOUNDATION_CFURL__ 1

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFData.h>
#include <CoreFoundation/CFError.h>
#include <CoreFoundation/CFString.h>

CF_EXTERN_C_BEGIN

enum {
    kCFURLPOSIXPathStyle = 0,
    kCFURLHFSPathStyle,
    kCFURLWindowsPathStyle
};
typedef CFIndex CFURLPathStyle;
    
typedef const struct __CFURL * CFURLRef;

/* CFURLs are composed of two fundamental pieces - their string, and a */
/* (possibly NULL) base URL.  A relative URL is one in which the string */
/* by itself does not fully specify the URL (for instance "myDir/image.tiff"); */
/* an absolute URL is one in which the string does fully specify the URL */
/* ("file://localhost/myDir/image.tiff").  Absolute URLs always have NULL */
/* base URLs; however, it is possible for a URL to have a NULL base, and still */
/* not be absolute.  Such a URL has only a relative string, and cannot be */
/* resolved.  Two CFURLs are considered equal if and only if their strings */
/* are equal and their bases are equal.  In other words, */
/* "file://localhost/myDir/image.tiff" is NOT equal to the URL with relative */
/* string "myDir/image.tiff" and base URL "file://localhost/".  Clients that */
/* need these less strict form of equality should convert all URLs to their */
/* absolute form via CFURLCopyAbsoluteURL(), then compare the absolute forms. */

CF_EXPORT
CFTypeID CFURLGetTypeID(void);

/* encoding will be used both to interpret the bytes of URLBytes, and to */
/* interpret any percent-escapes within the bytes. */
CF_EXPORT
CFURLRef CFURLCreateWithBytes(CFAllocatorRef allocator, const UInt8 *URLBytes, CFIndex length, CFStringEncoding encoding, CFURLRef baseURL);

/* Escapes any character that is not 7-bit ASCII with the byte-code */
/* for the given encoding.  If escapeWhitespace is true, whitespace */
/* characters (' ', '\t', '\r', '\n') will be escaped also (desirable */
/* if embedding the URL into a larger text stream like HTML) */
CF_EXPORT
CFDataRef CFURLCreateData(CFAllocatorRef allocator, CFURLRef url, CFStringEncoding encoding, Boolean escapeWhitespace);

/* Any escape sequences in URLString will be interpreted via UTF-8. */
CF_EXPORT
CFURLRef CFURLCreateWithString(CFAllocatorRef allocator, CFStringRef URLString, CFURLRef baseURL);

#if MAC_OS_X_VERSION_10_3 <= MAC_OS_X_VERSION_MAX_ALLOWED

/* Create an absolute URL directly, without requiring the extra step */
/* of calling CFURLCopyAbsoluteURL().  If useCompatibilityMode is  */
/* true, the rules historically used on the web are used to resolve */
/* relativeString against baseURL - these rules are generally listed */
/* in the RFC as optional or alternate interpretations.  Otherwise, */
/* the strict rules from the RFC are used.  The major differences are */
/* that in compatibility mode, we are lenient of the scheme appearing */
/* in relative portion, leading "../" components are removed from the */
/* final URL's path, and if the relative portion contains only */
/* resource specifier pieces (query, parameters, and fragment), then */
/* the last path component of the base URL will not be deleted  */
CF_EXPORT
CFURLRef CFURLCreateAbsoluteURLWithBytes(CFAllocatorRef alloc, const UInt8 *relativeURLBytes, CFIndex length, CFStringEncoding encoding, CFURLRef baseURL, Boolean useCompatibilityMode) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
#endif

/* filePath should be the URL's path expressed as a path of the type */
/* fsType.  If filePath is not absolute, the resulting URL will be */
/* considered relative to the current working directory (evaluated */
/* at creation time).  isDirectory determines whether filePath is */
/* treated as a directory path when resolving against relative path */
/* components */
CF_EXPORT
CFURLRef CFURLCreateWithFileSystemPath(CFAllocatorRef allocator, CFStringRef filePath, CFURLPathStyle pathStyle, Boolean isDirectory);

CF_EXPORT
CFURLRef CFURLCreateFromFileSystemRepresentation(CFAllocatorRef allocator, const UInt8 *buffer, CFIndex bufLen, Boolean isDirectory);

/* The path style of the baseURL must match the path style of the relative */
/* url or the results are undefined.  If the provided filePath looks like an */
/* absolute path ( starting with '/' if pathStyle is kCFURLPosixPathStyle, */
/* not starting with ':' for kCFURLHFSPathStyle, or starting with what looks */
/* like a drive letter and colon for kCFURLWindowsPathStyle ) then the baseURL */
/* is ignored. */
CF_EXPORT
CFURLRef CFURLCreateWithFileSystemPathRelativeToBase(CFAllocatorRef allocator, CFStringRef filePath, CFURLPathStyle pathStyle, Boolean isDirectory, CFURLRef baseURL); 

CF_EXPORT
CFURLRef CFURLCreateFromFileSystemRepresentationRelativeToBase(CFAllocatorRef allocator, const UInt8 *buffer, CFIndex bufLen, Boolean isDirectory, CFURLRef baseURL);
                                                                         
/* Fills buffer with the file system's native representation of */
/* url's path. No more than maxBufLen bytes are written to buffer. */
/* The buffer should be at least the maximum path length for */
/* the file system in question to avoid failures for insufficiently */
/* large buffers.  If resolveAgainstBase is true, the url's relative */
/* portion is resolved against its base before the path is computed. */
/* Returns success or failure. */
CF_EXPORT
Boolean CFURLGetFileSystemRepresentation(CFURLRef url, Boolean resolveAgainstBase, UInt8 *buffer, CFIndex maxBufLen);

/* Creates a new URL by resolving the relative portion of relativeURL against its base. */
CF_EXPORT
CFURLRef CFURLCopyAbsoluteURL(CFURLRef relativeURL);

/* Returns the URL's string. */
CF_EXPORT
CFStringRef CFURLGetString(CFURLRef anURL);

/* Returns the base URL if it exists */
CF_EXPORT
CFURLRef CFURLGetBaseURL(CFURLRef anURL);

/*
All URLs can be broken into two pieces - the scheme (preceding the
first colon) and the resource specifier (following the first colon).
Most URLs are also "standard" URLs conforming to RFC 1808 (available
from www.w3c.org).  This category includes URLs of the file, http,
https, and ftp schemes, to name a few.  Standard URLs start the
resource specifier with two slashes ("//"), and can be broken into
four distinct pieces - the scheme, the net location, the path, and
further resource specifiers (typically an optional parameter, query,
and/or fragment).  The net location appears immediately following
the two slashes and goes up to the next slash; it's format is
scheme-specific, but is usually composed of some or all of a username,
password, host name, and port.  The path is a series of path components
separated by slashes; if the net location is present, the path always
begins with a slash.  Standard URLs can be relative to another URL,
in which case at least the scheme and possibly other pieces as well
come from the base URL (see RFC 1808 for precise details when resolving
a relative URL against its base).  The full URL is therefore

<scheme> "://" <net location> <path, always starting with slash> <add'l resource specifiers>

If a given CFURL can be decomposed (that is, conforms to RFC 1808), you
can ask for each of the four basic pieces (scheme, net location, path,
and resource specifer) separately, as well as for its base URL.  The
basic pieces are returned with any percent escape sequences still in
place (although note that the scheme may not legally include any
percent escapes); this is to allow the caller to distinguish between
percent sequences that may have syntactic meaning if replaced by the
character being escaped (for instance, a '/' in a path component).
Since only the individual schemes know which characters are
syntactically significant, CFURL cannot safely replace any percent
escape sequences.  However, you can use
CFURLCreateStringByReplacingPercentEscapes() to create a new string with
the percent escapes removed; see below.

If a given CFURL can not be decomposed, you can ask for its scheme and its
resource specifier; asking it for its net location or path will return NULL.

To get more refined information about the components of a decomposable
CFURL, you may ask for more specific pieces of the URL, expressed with
the percent escapes removed.  The available functions are CFURLCopyHostName(),
CFURLGetPortNumber() (returns an Int32), CFURLCopyUserName(),
CFURLCopyPassword(), CFURLCopyQuery(), CFURLCopyParameters(), and
CFURLCopyFragment().  Because the parameters, query, and fragment of an
URL may contain scheme-specific syntaxes, these methods take a second
argument, giving a list of characters which should NOT be replaced if
percent escaped.  For instance, the ftp parameter syntax gives simple
key-value pairs as "<key>=<value>;"  Clearly if a key or value includes
either '=' or ';', it must be escaped to avoid corrupting the meaning of
the parameters, so the caller may request the parameter string as

CFStringRef myParams = CFURLCopyParameters(ftpURL, CFSTR("=;%"));

requesting that all percent escape sequences be replaced by the represented
characters, except for escaped '=', '%' or ';' characters.  Pass the empty
string (CFSTR("")) to request that all percent escapes be replaced, or NULL
to request that none be.
*/

/* Returns true if anURL conforms to RFC 1808 */
CF_EXPORT
Boolean CFURLCanBeDecomposed(CFURLRef anURL); 

/* The next several methods leave any percent escape sequences intact */

CF_EXPORT
CFStringRef CFURLCopyScheme(CFURLRef anURL);

/* NULL if CFURLCanBeDecomposed(anURL) is false */
CF_EXPORT
CFStringRef CFURLCopyNetLocation(CFURLRef anURL); 

/* NULL if CFURLCanBeDecomposed(anURL) is false; also does not resolve the URL */
/* against its base.  See also CFURLCopyAbsoluteURL().  Note that, strictly */
/* speaking, any leading '/' is not considered part of the URL's path, although */
/* its presence or absence determines whether the path is absolute. */
/* CFURLCopyPath()'s return value includes any leading slash (giving the path */
/* the normal POSIX appearance); CFURLCopyStrictPath()'s return value omits any */
/* leading slash, and uses isAbsolute to report whether the URL's path is absolute. */

/* CFURLCopyFileSystemPath() returns the URL's path as a file system path for the */
/* given path style.  All percent escape sequences are replaced.  The URL is not */
/* resolved against its base before computing the path. */
CF_EXPORT
CFStringRef CFURLCopyPath(CFURLRef anURL);

CF_EXPORT
CFStringRef CFURLCopyStrictPath(CFURLRef anURL, Boolean *isAbsolute);

CF_EXPORT
CFStringRef CFURLCopyFileSystemPath(CFURLRef anURL, CFURLPathStyle pathStyle);

/* Returns whether anURL's path represents a directory */
/* (true returned) or a simple file (false returned) */
CF_EXPORT
Boolean CFURLHasDirectoryPath(CFURLRef anURL);

/* Any additional resource specifiers after the path.  For URLs */
/* that cannot be decomposed, this is everything except the scheme itself. */
CF_EXPORT
CFStringRef CFURLCopyResourceSpecifier(CFURLRef anURL); 

CF_EXPORT
CFStringRef CFURLCopyHostName(CFURLRef anURL);

CF_EXPORT
SInt32 CFURLGetPortNumber(CFURLRef anURL); /* Returns -1 if no port number is specified */

CF_EXPORT
CFStringRef CFURLCopyUserName(CFURLRef anURL);

CF_EXPORT
CFStringRef CFURLCopyPassword(CFURLRef anURL);

/* These remove all percent escape sequences except those for */
/* characters in charactersToLeaveEscaped.  If charactersToLeaveEscaped */
/* is empty (""), all percent escape sequences are replaced by their */
/* corresponding characters.  If charactersToLeaveEscaped is NULL, */
/* then no escape sequences are removed at all */
CF_EXPORT
CFStringRef CFURLCopyParameterString(CFURLRef anURL, CFStringRef charactersToLeaveEscaped);

CF_EXPORT
CFStringRef CFURLCopyQueryString(CFURLRef anURL, CFStringRef charactersToLeaveEscaped);

CF_EXPORT
CFStringRef CFURLCopyFragment(CFURLRef anURL, CFStringRef charactersToLeaveEscaped);

CF_EXPORT
CFStringRef CFURLCopyLastPathComponent(CFURLRef url);

CF_EXPORT
CFStringRef CFURLCopyPathExtension(CFURLRef url);

/* These functions all treat the base URL of the supplied url as */
/* invariant.  In other words, the URL returned will always have */
/* the same base as the URL supplied as an argument. */

CF_EXPORT
CFURLRef CFURLCreateCopyAppendingPathComponent(CFAllocatorRef allocator, CFURLRef url, CFStringRef pathComponent, Boolean isDirectory);

CF_EXPORT
CFURLRef CFURLCreateCopyDeletingLastPathComponent(CFAllocatorRef allocator, CFURLRef url);

CF_EXPORT
CFURLRef CFURLCreateCopyAppendingPathExtension(CFAllocatorRef allocator, CFURLRef url, CFStringRef extension);

CF_EXPORT
CFURLRef CFURLCreateCopyDeletingPathExtension(CFAllocatorRef allocator, CFURLRef url);

#if MAC_OS_X_VERSION_10_3 <= MAC_OS_X_VERSION_MAX_ALLOWED
/* Fills buffer with the bytes for url, returning the number of bytes */
/* filled.  If buffer is of insufficient size, returns -1 and no bytes */
/* are placed in buffer.  If buffer is NULL, the needed length is */
/* computed and returned.  The returned bytes are the original bytes */ 
/* from which the URL was created; if the URL was created from a */
/* string, the bytes will be the bytes of the string encoded via UTF-8  */
CF_EXPORT
CFIndex CFURLGetBytes(CFURLRef url, UInt8 *buffer, CFIndex bufferLength) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

enum {
	kCFURLComponentScheme = 1,
	kCFURLComponentNetLocation = 2,
	kCFURLComponentPath = 3,
	kCFURLComponentResourceSpecifier = 4,

	kCFURLComponentUser = 5,
	kCFURLComponentPassword = 6,
	kCFURLComponentUserInfo = 7,
	kCFURLComponentHost = 8,
	kCFURLComponentPort = 9,
	kCFURLComponentParameterString = 10,
	kCFURLComponentQuery = 11,
	kCFURLComponentFragment = 12
};
typedef CFIndex CFURLComponentType;
 
/* 
Gets the  range of the requested component in the bytes of url, as
returned by CFURLGetBytes().  This range is only good for use in the
bytes returned by CFURLGetBytes!

If non-NULL, rangeIncludingSeparators gives the range of component
including the sequences that separate component from the previous and
next components.  If there is no previous or next component, that end of
rangeIncludingSeparators will match the range of the component itself.
If url does not contain the given component type, (kCFNotFound, 0) is
returned, and rangeIncludingSeparators is set to the location where the
component would be inserted.  Some examples -

For the URL http://www.apple.com/hotnews/

Component           returned range      rangeIncludingSeparators
scheme              (0, 4)              (0, 7)
net location        (7, 13)             (4, 16)
path                (20, 9)             (20, 9)    
resource specifier  (kCFNotFound, 0)    (29, 0)
user                (kCFNotFound, 0)    (7, 0)
password            (kCFNotFound, 0)    (7, 0)
user info           (kCFNotFound, 0)    (7, 0)
host                (7, 13)             (4, 16)
port                (kCFNotFound, 0)    (20, 0)
parameter           (kCFNotFound, 0)    (29, 0)
query               (kCFNotFound, 0)    (29, 0)
fragment            (kCFNotFound, 0)    (29, 0)


For the URL ./relPath/file.html#fragment

Component           returned range      rangeIncludingSeparators
scheme              (kCFNotFound, 0)    (0, 0)
net location        (kCFNotFound, 0)    (0, 0)
path                (0, 19)             (0, 20)
resource specifier  (20, 8)             (19, 9)
user                (kCFNotFound, 0)    (0, 0)
password            (kCFNotFound, 0)    (0, 0)
user info           (kCFNotFound, 0)    (0, 0)
host                (kCFNotFound, 0)    (0, 0)
port                (kCFNotFound, 0)    (0, 0)
parameter           (kCFNotFound, 0)    (19, 0)
query               (kCFNotFound, 0)    (19, 0)
fragment            (20, 8)             (19, 9)


For the URL scheme://user:pass@host:1/path/path2/file.html;params?query#fragment

Component           returned range      rangeIncludingSeparators
scheme              (0, 6)              (0, 9)
net location        (9, 16)             (6, 19)
path                (25, 21)            (25, 22) 
resource specifier  (47, 21)            (46, 22)
user                (9, 4)              (6, 8)
password            (14, 4)             (13, 6)
user info           (9, 9)              (6, 13)
host                (19, 4)             (18, 6)
port                (24, 1)             (23, 2)
parameter           (47, 6)             (46, 8)
query               (54, 5)             (53, 7)
fragment            (60, 8)             (59, 9)
*/
CF_EXPORT
CFRange CFURLGetByteRangeForComponent(CFURLRef url, CFURLComponentType component, CFRange *rangeIncludingSeparators) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
#endif

/* Returns a string with any percent escape sequences that do NOT */
/* correspond to characters in charactersToLeaveEscaped with their */
/* equivalent.  Returns NULL on failure (if an invalid percent sequence */
/* is encountered), or the original string (retained) if no characters */
/* need to be replaced. Pass NULL to request that no percent escapes be */
/* replaced, or the empty string (CFSTR("")) to request that all percent */
/* escapes be replaced.  Uses UTF8 to interpret percent escapes. */
CF_EXPORT
CFStringRef CFURLCreateStringByReplacingPercentEscapes(CFAllocatorRef allocator, CFStringRef originalString, CFStringRef charactersToLeaveEscaped);

#if MAC_OS_X_VERSION_10_3 <= MAC_OS_X_VERSION_MAX_ALLOWED
/* As above, but allows you to specify the encoding to use when interpreting percent escapes */
CF_EXPORT
CFStringRef CFURLCreateStringByReplacingPercentEscapesUsingEncoding(CFAllocatorRef allocator, CFStringRef origString, CFStringRef charsToLeaveEscaped, CFStringEncoding encoding) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
#endif

/* Creates a copy or originalString, replacing certain characters with */
/* the equivalent percent escape sequence based on the encoding specified. */
/* If the originalString does not need to be modified (no percent escape */
/* sequences are missing), may retain and return originalString. */
/* If you are uncertain of the correct encoding, you should use UTF-8, */
/* which is the encoding designated by RFC 2396 as the correct encoding */
/* for use in URLs.  The characters so escaped are all characters that */
/* are not legal URL characters (based on RFC 2396), plus any characters */
/* in legalURLCharactersToBeEscaped, less any characters in */
/* charactersToLeaveUnescaped.  To simply correct any non-URL characters */
/* in an otherwise correct URL string, do: */

/* newString = CFURLCreateStringByAddingPercentEscapes(kCFAllocatorDefault, origString, NULL, NULL, kCFStringEncodingUTF8); */
CF_EXPORT
CFStringRef CFURLCreateStringByAddingPercentEscapes(CFAllocatorRef allocator, CFStringRef originalString, CFStringRef charactersToLeaveUnescaped, CFStringRef legalURLCharactersToBeEscaped, CFStringEncoding encoding);


/* Returns a file reference URL, a path-idependent form of file URL. */
/* Converts a file path URL if necessary. For non-file URLs, returns NULL. */
/* Also returns NULL when the conversion fails because the target resource doesn't exist. */
/* Optional output error: The error is set to a valid CFErrorRef when the function */
/* result is NULL. A valid output error must be released by the caller. */
CF_EXPORT
CFURLRef CFURLCreateFileReferenceURL(CFAllocatorRef allocator, CFURLRef url, CFErrorRef *error) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;


/* Returns a file path URL, converting a file reference URL if necessary. */
/* For non-file URLs, returns NULL. Also returns NULL when the conversion fails */
/* because the target resource doesn't exist. */
/* Optional output error: The error is set to a valid CFErrorRef when the function */
/* result is NULL. A valid output error must be released by the caller. */
CF_EXPORT
CFURLRef CFURLCreateFilePathURL(CFAllocatorRef allocator, CFURLRef url, CFErrorRef *error) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;


#ifndef CF_OPEN_SOURCE
#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)) || (TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)

struct FSRef;

CF_EXPORT
CFURLRef CFURLCreateFromFSRef(CFAllocatorRef allocator, const struct FSRef *fsRef);

CF_EXPORT
Boolean CFURLGetFSRef(CFURLRef url, struct FSRef *fsRef);

#endif
#endif


#if TARGET_OS_MAC

/* The following APIs provide efficient access to resource properties. Properties 
are identified by keys, and values are represented as Core Foundation objects. The 
type of each value is fixed for each property, e.g. the modification date is a CFDateRef, 
the file size is a CFNumberRef.

Values are fetched on-demand, synchronously, from the resource's backing store. They
are cached and reused when fetched again through the same URL instance, until the 
client clears the value. The client has complete control over the cache lifetime.

Some resource property values can be changed, given sufficient access permission to the resource. 
When a resource property value is set, the change is written to backing store synchronously.
*/

/* Assigns the requested resource property value to the typeRefValuePtr output */
/* argument. Returns true if the output value was set. Note that NULL is a valid output value. */
/* The value is fetched synchronously from the resource backing store only if a value is not */
/* already cached. The type of the output value type varies by property (see property key */
/* definitions). Returns false if an error occurs. Optional output error: the error is set to */
/* a valid CFErrorRef when the function returns false. A valid output error must be */
/* released by the caller. */
CF_EXPORT
Boolean CFURLCopyResourcePropertyForKey(CFURLRef url, CFStringRef key, void *propertyValueTypeRefPtr, CFErrorRef *error) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;


/* Returns any number of resource property values as a dictionary of keyed values. */
/* The requested values are specified as an array of keys to appear in */
/* the result dictionary. Values are fetched synchronously from the resource backing store unless */
/* already cached. The type of each value type varies (see key definitions, below). */
/* Returns an empty dictionary if no values are found. Returns NULL when an error occurs. */
/* Optional output error: the error is set to a valid CFErrorRef when the */
/* function returns NULL. A valid output error must be released by the caller. */
CF_EXPORT
CFDictionaryRef CFURLCopyResourcePropertiesForKeys(CFURLRef url, CFArrayRef keys, CFErrorRef *error) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;


/* Changes a resource property value. Synchronously writes the value to the resource backing */
/* store. The input value type must be a valid CFTypeRef, of the type required for the specified */
/* key (see key definitions). Returns true upon success, false when an error occurs. */
/* Optional output error: the error is set to a valid CFErrorRef when the function */
/* returns false. A valid output error must be released by the caller. */
/* Note that some values are read-only. Attempting to set a read-only property */
/* results in an error. */
CF_EXPORT
Boolean CFURLSetResourcePropertyForKey(CFURLRef url, CFStringRef key, CFTypeRef propertValue, CFErrorRef *error) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;


/* Changes any number of resource property values, specified as a dictionary of keyed values. */
/* Synchronously writes values to the resource backing store. The input dictionary's value types must conform */
/* to the type required for its key (see key definitions). Returns true when all values are set successfully, */
/* and false if an error occurs. Optional output error: the error is set to a valid CFErrorRef when the function returns */
/* false. A valid output error must be released by the caller. When an error occurs after some properties have been */
/* successfully changed, the user dictionary in the error contains an array of keys that */
/* were not set. Note that some values are read-only. Attempting to set a read-only value */
/* results in an error. */
CF_EXPORT
Boolean CFURLSetResourcePropertiesForKeys(CFURLRef url, CFDictionaryRef keyedPropertyValues, CFErrorRef *error) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;


/* Discards a cached property value for a specific key */
CF_EXPORT
void CFURLClearResourcePropertyCacheForKey(CFURLRef url, CFStringRef key) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;


/* Discards all cached property values */
CF_EXPORT
void CFURLClearResourcePropertyCache(CFURLRef url) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;


/* Sets a temporary property value. Temporary properties exist only in memory and are never */
/* written to resource backing store. Once set, a temporary property value can be fetched */
/* with CFURLCopyResourcePropertyForKey and CFURLCopyResourcePropertiesForKeys. Temporary property */
/* values are for client use. Values must be valid Core Foundation types, and will be retained. */
/* To remove a temporary property value, use CFURLClearResourcePropertyCacheForKey. */
CF_EXPORT
void CFURLSetTemporaryResourcePropertyForKey(CFURLRef url, CFStringRef key, CFTypeRef propertyValue) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;


/* Synchronously checks if the resource's backing store is reachable and the resource exists, */
/* returning true if so. The optional output error can be used to determine the type of reachability */
/* failure (e.g., file not found, network error, etc.). The error is set to a valid CFErrorRef if */
/* and only if the function returns false. A valid output error must be released by */
/* the caller. Checking for resource existence and reachability is appropriate when making decisions */
/* that do not require other immediate operations on the resource. An example would be */
/* periodic maintenance of UI state that depends on the existence of a particular document. */
/* When performing an operation such as opening a file, it is more efficient to */
/* simply try the operation and handle failures than to check first for reachability. */
CF_EXPORT
Boolean CFURLResourceIsReachable(CFURLRef url, CFErrorRef *error) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;


/* Properties of File System Resources */

CF_EXPORT 
const CFStringRef kCFURLNameKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* The resource name provided by the file system (value type CFString) */

CF_EXPORT
const CFStringRef kCFURLLocalizedNameKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* Localized or extension-hidden name as displayed to users (Read-only, value type CFString) */

CF_EXPORT
const CFStringRef kCFURLIsRegularFileKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* True for regular files (Read-only, value type CFBoolean) */

CF_EXPORT
const CFStringRef kCFURLIsDirectoryKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* True for directories (Read-only, CFBoolean) */

CF_EXPORT
const CFStringRef kCFURLIsSymbolicLinkKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* True for symlinks (Read-only, value type CFBoolean) */

CF_EXPORT
const CFStringRef kCFURLIsVolumeKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* True for the root directory of a volume (Read-only, value type CFBoolean) */

CF_EXPORT
const CFStringRef kCFURLIsPackageKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* True for packaged directories (value type CFBoolean) */

CF_EXPORT
const CFStringRef kCFURLIsSystemImmutableKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* True for system-immutable resources (value type CFBoolean) */

CF_EXPORT
const CFStringRef kCFURLIsUserImmutableKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* True for user-immutable resources (value type CFBoolean) */

CF_EXPORT
const CFStringRef kCFURLIsHiddenKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* True for resources normally hidden from users (value type CFBoolean) */

CF_EXPORT
const CFStringRef kCFURLHasHiddenExtensionKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* True for resources whose filename extension is hiden (value type CFBoolean) */

CF_EXPORT
const CFStringRef kCFURLCreationDateKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* Value type CFDate */

CF_EXPORT
const CFStringRef kCFURLContentAccessDateKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* Value type CFDate */

CF_EXPORT
const CFStringRef kCFURLContentModificationDateKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* Value type CFDate */

CF_EXPORT
const CFStringRef kCFURLAttributeModificationDateKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* Value type CFDate */

CF_EXPORT
const CFStringRef kCFURLLinkCountKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* Number of hard links to the resource (Read-only, CFNumber) */

CF_EXPORT
const CFStringRef kCFURLParentDirectoryURLKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* URL of the parent directory, if any (Read-only, value type CFURL) */

CF_EXPORT
const CFStringRef kCFURLVolumeURLKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* URL of the volume on which the resource is stored (Read-only, value type CFURL) */

CF_EXPORT
const CFStringRef kCFURLTypeIdentifierKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* Uniform type identifier for the resource (Read-only, value type CFString) */

CF_EXPORT
const CFStringRef kCFURLLocalizedTypeDescriptionKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* User-visible type or "kind" descriptiopn (Read-only, value type CFString) */

CF_EXPORT
const CFStringRef kCFURLLabelNumberKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* The label number assigned to the resource (value type CFNumber) */

CF_EXPORT
const CFStringRef kCFURLLabelColorKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* The color of the assigned label (Read-only, value type CGColorRef, must link with Application Services) */

CF_EXPORT
const CFStringRef kCFURLLocalizedLabelKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* The user-visible label text (Read-only, value type CFString) */

CF_EXPORT
const CFStringRef kCFURLEffectiveIconKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* The icon normally displayed for the resource (Read-only, value type CGImageRef, must link with Application Services) */

CF_EXPORT
const CFStringRef kCFURLCustomIconKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* The custom icon assigned to the resource, if any (value type CGImageRef, must link with Application Services) */


/* File Properties */

CF_EXPORT
const CFStringRef kCFURLFileSizeKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* Total file size, in bytes (Read-only, value type CFNumber) */

CF_EXPORT
const CFStringRef kCFURLFileAllocatedSizeKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* Total size of blocks allocated (Read-only, value type CFNumber) */

CF_EXPORT
const CFStringRef kCFURLIsAliasFileKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
/*  true if the url is a Finder alias file, false otherwise ( Read-only, value type CFBooleanRef) */


/* Volume Properties */

/* For convenience, volume properties may be requested from any resource on a volume. */

CF_EXPORT
const CFStringRef kCFURLVolumeLocalizedFormatDescriptionKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* The user-visible volume format (Read-only, value type CFString) */

CF_EXPORT
const CFStringRef kCFURLVolumeTotalCapacityKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* Total volume capacity in bytes (Read-only, value type CFNumber) */

CF_EXPORT
const CFStringRef kCFURLVolumeAvailableCapacityKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* Total free space, in bytes (Read-only, value type CFNumber) */

CF_EXPORT
const CFStringRef kCFURLVolumeResourceCountKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* Total number of resources on the volume (Read-only, value type CFNumber) */

CF_EXPORT
const CFStringRef kCFURLVolumeSupportsPersistentIDsKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* Read-only, value type CFBoolean */

CF_EXPORT
const CFStringRef kCFURLVolumeSupportsSymbolicLinksKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* Read-only, value type CFBoolean */

CF_EXPORT
const CFStringRef kCFURLVolumeSupportsHardLinksKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* Read-only, value type CFBoolean */

CF_EXPORT
const CFStringRef kCFURLVolumeSupportsJournalingKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* Read-only, value type CFBoolean */

CF_EXPORT
const CFStringRef kCFURLVolumeIsJournalingKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* Read-only, value type CFBoolean */

CF_EXPORT
const CFStringRef kCFURLVolumeSupportsSparseFilesKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* Read-only, value type CFBoolean */

CF_EXPORT
const CFStringRef kCFURLVolumeSupportsZeroRunsKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* Read-only, value type CFBoolean */

CF_EXPORT
const CFStringRef kCFURLVolumeSupportsCaseSensitiveNamesKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* Read-only, value type CFBoolean */

CF_EXPORT
const CFStringRef kCFURLVolumeSupportsCasePreservedNamesKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* Read-only, value type CFBoolean */

enum {
    kCFURLBookmarkCreationPreferFileIDResolutionMask = ( 1UL << 8 ),  // At resolution time, this alias will prefer resolving by the embedded fileID to the path
    kCFURLBookmarkCreationMinimalBookmarkMask = ( 1UL << 9 ), // Creates a bookmark with "less" information, which may be smaller but still be able to resolve in certain ways
    kCFURLBookmarkCreationSuitableForBookmarkFile = ( 1UL << 10 ), // includes in the created bookmark those properties which are needed for a bookmark/alias file
};
typedef CFOptionFlags CFURLBookmarkCreationOptions;

enum  {
    kCFBookmarkResolutionWithoutUIMask = ( 1UL << 8 ),		// don't perform any UI during bookmark resolution
    kCFBookmarkResolutionWithoutMountingMask = ( 1UL << 9 ),	// don't mount a volume during bookmark resolution
};
typedef CFOptionFlags CFURLBookmarkResolutionOptions;

typedef CFOptionFlags CFURLBookmarkFileCreationOptions;

/*	@function CFURLCreateBookmarkData
	@discussion	Create a CFDataRef containing an externalizable representation from a CFURLRef, modified with the given options, including ( at the minimum ) any
		properties in the propertiesToInclude array which are retrievable from the given url.
	@param	allocator		the CFAllocator to use to create this object
	@param	url	the CFURLRef to create a bookmark data from.
	@param	options	a set of options which control creation of the bookmark data
	@param resourcePropertiesToInclude	If non-NULL, an CFArrayRef of additional properties copied from the url to include in the created bookmark data.
	@param relativeToURL If non-NULL, the created bookmark will be relative to the given url
	@param error	If non-NULL, on exit will be filled in with a CFErrorRef representing any error which occured during creation of the bookmark data
	@result	A CFDataRef containing an data, which can be later be passed to CFURLCreateByResolvingBookmarkData() or to CFURLCopyPropertiesForKeysFromBookmarkData() / CFURLCopyPropertyForKeyFromBookmarkData() */
CFDataRef CFURLCreateBookmarkData ( CFAllocatorRef allocator, CFURLRef url, CFURLBookmarkCreationOptions options, CFArrayRef resourcePropertiesToInclude, CFURLRef relativeToURL, CFErrorRef* error ) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/*	@function CFURLCreateByResolvingBookmarkData
	@discussion Given a CFDataRef created with CFURLCreateBookmarkRepresentation(), return a CFURLRef of the item it was a bookmark to, and
		attempt to pre-cache those properties in propertiesToInclude in the resulting url.  If in the process of resolving the bookmark into the CFURLRef
	 	it points to this determines that  some properties in the bookmark are out of date or not correct for the item it resolves to, set *isStale to YES,
		which the client may want to use to decide to make a new bookmark from the returned item and replace the saved bookmark it has.  If the bookmarked
		item cannot be found, return NULL.  If an error ( other than "original item can not be found" ) occurs during the process, return NULL and fill in error )
	@param	allocator	 the CFAllocator to use to create this object
	@param	 bookmark a CFDataRef containing a bookmark data, created with CFURLCreateBookmarkData
	@param	options options which affect the resolution
	@param relativeToURL If non-NULL, and if the bookmark was created relative to another url, then resolve it relative to this url
	@param resourcePropertiesToInclude If non-NULL, a CFArray containing those properties which the caller would like to already be cached on the given url
	@param isStale If non-NULL, on exit will be set to true if during resolution any of the properties in the bookmark no longer seemed to match the
		corresponding properties on the returned file.  Clients, upon seeing a stale representation, may want to replace whatever stored bookmark data they
		have saved and create a new one.
	@param error	If non-NULL, on exit will be filled in with a CFErrorRef representing any error which occured during resolution of the bookmark data
	@result A CFURLRef of a file which is the closest match to the file the bookmark data */
CFURLRef CFURLCreateByResolvingBookmarkData ( CFAllocatorRef allocator, CFDataRef bookmark, CFURLBookmarkResolutionOptions options, CFURLRef relativeToURL, CFArrayRef resourcePropertiesToInclude, Boolean* isStale, CFErrorRef* error ) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/*	@function	CFURLCreatePropertiesForKeysFromBookmarkData
	@discussion	Given a bookmark, return a dictionary of properties ( all properties if propertiesToReturn == NULL ).
				This returns only the properties stored within the bookmark and will not attempt to resolve the bookmark or do i/o.
	@param	allocator	 the CFAllocator to use to create this object
	@param	 bookmark a CFDataRef containing a bookmark data, created with CFURLCreateBookmarkData
	@param	propertiesToReturn a CFArrayRef of the properties of the bookmark data which the client would like returned.
	@result	a CFDictionaryRef containing the values for the properties passed in obtained from the bookmark data ( not by attempting to resolve it or do i/o in any way ) */
CFDictionaryRef CFURLCreateResourcePropertiesForKeysFromBookmarkData ( CFAllocatorRef allocator, CFArrayRef resourcePropertiesToReturn, CFDataRef bookmark ) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/*	@function	CFURLCreatePropertyForKeyFromBookmarkData
	@discussion	Given a bookmark, return the value for a given property from the bookmark data
				This returns only the properties stored within the bookmark and will not attempt to resolve the bookmark or do i/o.
	@param	allocator	 the CFAllocator to use to create this object
	@param	 bookmark a CFDataRef containing a bookmark data, created with CFURLCreateBookmarkData
	@param	propertyKey the property key to return.
	@result	a CFTypeRef value for the property passed in obtained from the bookmark data ( not by attempting to resolve it or do i/o in any way ) */
CFTypeRef  CFURLCreateResourcePropertyForKeyFromBookmarkData( CFAllocatorRef allocator, CFStringRef resourcePropertyKey, CFDataRef bookmark ) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/*!	@function 	CFURLCreateBookmarkDataFromFile
	@description	Given a fileURL of a file which is a Finder "alias" file, return a CFDataRef with the bookmark data from the file.  If urlRef points to an alias file
			created before SnowLeopard which contains Alias Manager information and no bookmark data, then a CFDataRef will be synthesized which contains
			a approximation of the alias information in a format which can be used to resolve the bookmark.  If an error prevents reading the data or
			if it is corrupt, NULL will be returned and error will be filled in if errorRef is non-NULL.
	@param	allocator the CFAllocator to use to create this object
	@param	fileURL a CFURLRef to to the alias file to create the bookmark data from
	@param	errorRef    if non-NULL, on exit will be filled in with a CFErrorRef representing any error which occurred during the creation of the bookmark data from the file
	@result	A CFDataRef containing bookmark data, or NULL if there was an error creating bookmark data from the file, such as if the file is not an alias file.
 */
CFDataRef CFURLCreateBookmarkDataFromFile(CFAllocatorRef allocator, CFURLRef fileURL, CFErrorRef *errorRef );

/*!	@function	CFURLWriteBookmarkDataToFile
	@description	Given a created bookmarkData object, create a new Finder "alias" file at fileURL which contains the bookmark data.  If fileURL is a url to a directory, an alias file
			will be created with the same name as the bookmarked item and a ".alias" extension.  If fileURL is a url for a file and it exists it will be overwritten.  If a
			.alias extension is not present it will be added.  In addition to the bookmark data, sufficient pre-SnowLeopard alias data will added to the file to allow
			systems running something before SnowLeopard to resolve this file using Alias Manager routines and get back the same file as the bookmark routines.
			The bookmark data must have been created with the kCFURLBookmarkCreationSuitableForBookmarkFile option and an error will be returned if not.
	@param	allocator	 the CFAllocator to use to create this object
	@param	 bookmark a CFDataRef containing a bookmark data, created with CFURLCreateBookmarkData
	@param	options	options flags 
	@param	errorRef    if non-NULL, on exit will be filled in with a CFErrorRef representing any error which occurred during the creation of the alias file
 */
Boolean CFURLWriteBookmarkDataToFile( CFDataRef bookmarkRef, CFURLRef fileURL, CFURLBookmarkFileCreationOptions options, CFErrorRef *errorRef );

/*!	@function	CFURLCreateBookmarkDataFromAliasRecord
	@discussion	Create a CFDataRef containing bookmarkdata by converting the alias data in aliasRecordDataRef, which should be the contents of an AliasRecord copied into a CFDataRef object.
		The created bookmarkdata can be passed into CFURLCreateByResolvingBookmarkData() to resolve the item into a CFURLRef, or a small set of information can be returned from
		CFURLCreateResourcePropertiesForKeysFromBookmarkData() / CFURLCreateResourcePropertyForKeyFromBookmarkData().
		@param	allocator		the CFAllocator to use to create this object
		@param	aliasRecordDataRef	the contents of an AliasRecord to create bookmark data for
		@result	A CFDataRef containing an data, which can be later be passed to CFURLCreateByResolvingBookmarkData() or to CFURLCopyPropertiesForKeysFromBookmarkData() / CFURLCopyPropertyForKeyFromBookmarkData()
 */
CFDataRef CFURLCreateBookmarkDataFromAliasRecord ( CFAllocatorRef allocatorRef, CFDataRef aliasRecordDataRef );

#endif /* TARGET_OS_MAC */

CF_EXTERN_C_END

#endif /* ! __COREFOUNDATION_CFURL__ */

