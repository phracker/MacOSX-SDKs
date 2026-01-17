/*	FoundationErrors.h
	Copyright 2004-2005, Apple, Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

#if MAC_OS_X_VERSION_10_4 <= MAC_OS_X_VERSION_MAX_ALLOWED

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
    NSFileWriteUnknownError = 512,			    // Write error (reason unknown)
    NSFileWriteNoPermissionError = 513,                     // Write error (permission problem)
    NSFileWriteInvalidFileNameError = 514,                  // Write error (invalid file name)
    NSFileWriteInapplicableStringEncodingError = 517,       // Write error (string encoding not applicable) also NSStringEncodingErrorKey
    NSFileWriteUnsupportedSchemeError = 518,		    // Write error (unsupported URL scheme)
    NSFileWriteOutOfSpaceError = 640,                       // Write error (out of disk space)

    // Other errors
    NSKeyValueValidationError = 1024,                       // KVC validation error
    NSFormattingError = 2048,                               // Formatting error
    NSUserCancelledError = 3072,			    // User cancelled operation (this one often doesn't deserve a panel and might be a good one to special case)

    // Inclusive error range definitions, for checking future error codes
    NSFileErrorMinimum = 0,
    NSFileErrorMaximum = 1023,
    
    NSValidationErrorMinimum = 1024,
    NSValidationErrorMaximum = 2047,

    NSFormattingErrorMinimum = 2048,
    NSFormattingErrorMaximum = 2559
};

#endif

