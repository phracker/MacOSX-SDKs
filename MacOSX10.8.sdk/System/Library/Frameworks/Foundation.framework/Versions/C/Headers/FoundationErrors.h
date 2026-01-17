/*	FoundationErrors.h
	Copyright (c) 2004-2012, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

/* NSError codes in NSCocoaErrorDomain. Note that other frameworks (such as AppKit and CoreData) also provide additional NSCocoaErrorDomain error codes.
*/
enum {
    // File system and file I/O related errors, with NSFilePathErrorKey or NSURLErrorKey containing path or URL
    NSFileNoSuchFileError = 4,                                              // Attempt to do a file system operation on a non-existent file
    NSFileLockingError = 255,                                               // Couldn't get a lock on file
    NSFileReadUnknownError = 256,                                           // Read error (reason unknown)
    NSFileReadNoPermissionError = 257,                                      // Read error (permission problem)
    NSFileReadInvalidFileNameError = 258,                                   // Read error (invalid file name)
    NSFileReadCorruptFileError = 259,                                       // Read error (file corrupt, bad format, etc)
    NSFileReadNoSuchFileError = 260,                                        // Read error (no such file)
    NSFileReadInapplicableStringEncodingError = 261,                        // Read error (string encoding not applicable) also NSStringEncodingErrorKey
    NSFileReadUnsupportedSchemeError = 262,                                 // Read error (unsupported URL scheme)
    NSFileReadTooLargeError NS_ENUM_AVAILABLE(10_5, 2_0) = 263,             // Read error (file too large)
    NSFileReadUnknownStringEncodingError NS_ENUM_AVAILABLE(10_5, 2_0) = 264, // Read error (string encoding of file contents could not be determined)
    NSFileWriteUnknownError = 512,                                          // Write error (reason unknown)
    NSFileWriteNoPermissionError = 513,                                     // Write error (permission problem)
    NSFileWriteInvalidFileNameError = 514,                                  // Write error (invalid file name)
    NSFileWriteFileExistsError NS_ENUM_AVAILABLE(10_7, 5_0) = 516,          // Write error (file exists)
    NSFileWriteInapplicableStringEncodingError = 517,                       // Write error (string encoding not applicable) also NSStringEncodingErrorKey
    NSFileWriteUnsupportedSchemeError = 518,                                // Write error (unsupported URL scheme)
    NSFileWriteOutOfSpaceError = 640,                                       // Write error (out of disk space)
    NSFileWriteVolumeReadOnlyError NS_ENUM_AVAILABLE(10_6, 4_0) = 642,      // Write error (readonly volume)

    // Other errors
    NSKeyValueValidationError = 1024,                                       // KVC validation error
    NSFormattingError = 2048,                                               // Formatting error
    NSUserCancelledError = 3072,                                            // User cancelled operation (this one often doesn't deserve a panel and might be a good one to special case)
    NSFeatureUnsupportedError NS_ENUM_AVAILABLE(10_8, 6_0) = 3328,          // Feature unsupported error
    
    // Executable loading errors
    NSExecutableNotLoadableError NS_ENUM_AVAILABLE(10_5, 2_0) = 3584,           // Executable is of a type that is not loadable in the current process
    NSExecutableArchitectureMismatchError NS_ENUM_AVAILABLE(10_5, 2_0) = 3585,  // Executable does not provide an architecture compatible with the current process
    NSExecutableRuntimeMismatchError NS_ENUM_AVAILABLE(10_5, 2_0) = 3586,       // Executable has Objective C runtime information incompatible with the current process
    NSExecutableLoadError NS_ENUM_AVAILABLE(10_5, 2_0) = 3587,                  // Executable cannot be loaded for some other reason, such as a problem with a library it depends on
    NSExecutableLinkError NS_ENUM_AVAILABLE(10_5, 2_0) = 3588,                  // Executable fails due to linking issues
    
    // Inclusive error range definitions, for checking future error codes
    NSFileErrorMinimum = 0,
    NSFileErrorMaximum = 1023,
    
    NSValidationErrorMinimum = 1024,
    NSValidationErrorMaximum = 2047,

    NSExecutableErrorMinimum NS_ENUM_AVAILABLE(10_5, 2_0) = 3584,
    NSExecutableErrorMaximum NS_ENUM_AVAILABLE(10_5, 2_0) = 3839,

    NSFormattingErrorMinimum = 2048,
    NSFormattingErrorMaximum = 2559,
    
    NSPropertyListReadCorruptError NS_ENUM_AVAILABLE(10_6, 4_0) = 3840,         // Error parsing a property list
    NSPropertyListReadUnknownVersionError NS_ENUM_AVAILABLE(10_6, 4_0) = 3841,  // The version number in the property list is unknown
    NSPropertyListReadStreamError NS_ENUM_AVAILABLE(10_6, 4_0) = 3842,          // Stream error reading a property list
    NSPropertyListWriteStreamError NS_ENUM_AVAILABLE(10_6, 4_0) = 3851,         // Stream error writing a property list

    NSPropertyListErrorMinimum NS_ENUM_AVAILABLE(10_6, 4_0) = 3840,
    NSPropertyListErrorMaximum NS_ENUM_AVAILABLE(10_6, 4_0) = 4095,

    NSXPCConnectionInterrupted NS_ENUM_AVAILABLE(10_8, 6_0) = 4097,
    NSXPCConnectionInvalid NS_ENUM_AVAILABLE(10_8, 6_0) = 4099,
    NSXPCConnectionReplyInvalid NS_ENUM_AVAILABLE(10_8, 6_0) = 4101,
    
    NSXPCConnectionErrorMinimum NS_ENUM_AVAILABLE(10_8, 6_0) = 4096,
    NSXPCConnectionErrorMaximum NS_ENUM_AVAILABLE(10_8, 6_0) = 4224
};

