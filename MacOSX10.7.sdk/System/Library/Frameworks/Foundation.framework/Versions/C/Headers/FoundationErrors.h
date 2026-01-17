/*	FoundationErrors.h
	Copyright (c) 2004-2011, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

/* NSError codes in NSCocoaErrorDomain. Note that other frameworks (such as AppKit and CoreData) also provide additional NSCocoaErrorDomain error codes.
*/
enum {
    // File system and file I/O related errors, with NSFilePathErrorKey or NSURLErrorKey containing path or URL
    NSFileNoSuchFileError = 4,				    // Attempt to do a file system operation on a non-existent file
    NSFileLockingError = 255,				    // Couldn't get a lock on file
    NSFileReadUnknownError = 256,                           // Read error (reason unknown)
    NSFileReadNoPermissionError = 257,                      // Read error (permission problem)
    NSFileReadInvalidFileNameError = 258,                   // Read error (invalid file name)
    NSFileReadCorruptFileError = 259,                       // Read error (file corrupt, bad format, etc)
    NSFileReadNoSuchFileError = 260,                        // Read error (no such file)
    NSFileReadInapplicableStringEncodingError = 261,        // Read error (string encoding not applicable) also NSStringEncodingErrorKey
    NSFileReadUnsupportedSchemeError = 262,		    // Read error (unsupported URL scheme)
#if MAC_OS_X_VERSION_10_5 <= MAC_OS_X_VERSION_MAX_ALLOWED || __IPHONE_2_0 <= __IPHONE_OS_VERSION_MAX_ALLOWED
    NSFileReadTooLargeError = 263,			    // Read error (file too large)
    NSFileReadUnknownStringEncodingError = 264,		    // Read error (string encoding of file contents could not be determined)
#endif /* MAC_OS_X_VERSION_10_5 <= MAC_OS_X_VERSION_MAX_ALLOWED || __IPHONE_2_0 <= __IPHONE_OS_VERSION_MAX_ALLOWED */
    NSFileWriteUnknownError = 512,			    // Write error (reason unknown)
    NSFileWriteNoPermissionError = 513,                     // Write error (permission problem)
    NSFileWriteInvalidFileNameError = 514,                  // Write error (invalid file name)
#if MAC_OS_X_VERSION_10_7 <= MAC_OS_X_VERSION_MAX_ALLOWED || __IPHONE_5_0 <= __IPHONE_OS_VERSION_MAX_ALLOWED
    NSFileWriteFileExistsError = 516,			    // Write error (file exists)
#endif
    NSFileWriteInapplicableStringEncodingError = 517,       // Write error (string encoding not applicable) also NSStringEncodingErrorKey
    NSFileWriteUnsupportedSchemeError = 518,		    // Write error (unsupported URL scheme)
    NSFileWriteOutOfSpaceError = 640,                       // Write error (out of disk space)
#if MAC_OS_X_VERSION_10_6 <= MAC_OS_X_VERSION_MAX_ALLOWED || __IPHONE_4_0 <= __IPHONE_OS_VERSION_MAX_ALLOWED
    NSFileWriteVolumeReadOnlyError = 642,		    // Write error (readonly volume)
#endif

    // Other errors
    NSKeyValueValidationError = 1024,                       // KVC validation error
    NSFormattingError = 2048,                               // Formatting error
    NSUserCancelledError = 3072,			    // User cancelled operation (this one often doesn't deserve a panel and might be a good one to special case)
    
#if MAC_OS_X_VERSION_10_5 <= MAC_OS_X_VERSION_MAX_ALLOWED || __IPHONE_2_0 <= __IPHONE_OS_VERSION_MAX_ALLOWED
    // Executable loading errors
    NSExecutableNotLoadableError = 3584,                    // Executable is of a type that is not loadable in the current process
    NSExecutableArchitectureMismatchError = 3585,           // Executable does not provide an architecture compatible with the current process
    NSExecutableRuntimeMismatchError = 3586,                // Executable has Objective C runtime information incompatible with the current process
    NSExecutableLoadError = 3587,                           // Executable cannot be loaded for some other reason, such as a problem with a library it depends on
    NSExecutableLinkError = 3588,                           // Executable fails due to linking issues
#endif /* MAC_OS_X_VERSION_10_5 <= MAC_OS_X_VERSION_MAX_ALLOWED || __IPHONE_2_0 <= __IPHONE_OS_VERSION_MAX_ALLOWED */
    
    // Inclusive error range definitions, for checking future error codes
    NSFileErrorMinimum = 0,
    NSFileErrorMaximum = 1023,
    
    NSValidationErrorMinimum = 1024,
    NSValidationErrorMaximum = 2047,

#if MAC_OS_X_VERSION_10_5 <= MAC_OS_X_VERSION_MAX_ALLOWED || __IPHONE_2_0 <= __IPHONE_OS_VERSION_MAX_ALLOWED
    NSExecutableErrorMinimum = 3584,
    NSExecutableErrorMaximum = 3839,
#endif /* MAC_OS_X_VERSION_10_5 <= MAC_OS_X_VERSION_MAX_ALLOWED || __IPHONE_2_0 <= __IPHONE_OS_VERSION_MAX_ALLOWED */

    NSFormattingErrorMinimum = 2048,
    NSFormattingErrorMaximum = 2559,
    
#if MAC_OS_X_VERSION_10_6 <= MAC_OS_X_VERSION_MAX_ALLOWED || __IPHONE_4_0 <= __IPHONE_OS_VERSION_MAX_ALLOWED
    NSPropertyListReadCorruptError = 3840,                  // Error parsing a property list
    NSPropertyListReadUnknownVersionError = 3841,           // The version number in the property list is unknown
    NSPropertyListReadStreamError = 3842,                   // Stream error reading a property list
    NSPropertyListWriteStreamError = 3851,                  // Stream error writing a property list

    NSPropertyListErrorMinimum = 3840,
    NSPropertyListErrorMaximum = 4095
#endif /* MAC_OS_X_VERSION_10_6 <= MAC_OS_X_VERSION_MAX_ALLOWED || __IPHONE_4_0 <= __IPHONE_OS_VERSION_MAX_ALLOWED */
    
};

