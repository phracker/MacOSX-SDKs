/*	FoundationErrors.h
	Copyright (c) 2004-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

/* NSError codes in NSCocoaErrorDomain. Note that other frameworks (such as AppKit and CoreData) also provide additional NSCocoaErrorDomain error codes.
*/
NS_ENUM(NSInteger) {
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

    // NSFileManager unmount errors
    NSFileManagerUnmountUnknownError NS_ENUM_AVAILABLE(10_11, NA) = 768,    // The volume could not be unmounted (reason unknown)
    NSFileManagerUnmountBusyError NS_ENUM_AVAILABLE(10_11, NA) = 769,       // The volume could not be unmounted because it is in use

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
    NSPropertyListWriteInvalidError NS_ENUM_AVAILABLE(10_10, 8_0) = 3852,       // Invalid property list object or invalid property list type specified when writing

    NSPropertyListErrorMinimum NS_ENUM_AVAILABLE(10_6, 4_0) = 3840,
    NSPropertyListErrorMaximum NS_ENUM_AVAILABLE(10_6, 4_0) = 4095,

    NSXPCConnectionInterrupted NS_ENUM_AVAILABLE(10_8, 6_0) = 4097,
    NSXPCConnectionInvalid NS_ENUM_AVAILABLE(10_8, 6_0) = 4099,
    NSXPCConnectionReplyInvalid NS_ENUM_AVAILABLE(10_8, 6_0) = 4101,
    
    NSXPCConnectionErrorMinimum NS_ENUM_AVAILABLE(10_8, 6_0) = 4096,
    NSXPCConnectionErrorMaximum NS_ENUM_AVAILABLE(10_8, 6_0) = 4224,

    NSUbiquitousFileUnavailableError NS_ENUM_AVAILABLE(10_9, 7_0) = 4353, // NSURLUbiquitousItemDownloadingErrorKey contains an error with this code when the item has not been uploaded to iCloud by the other devices yet
    NSUbiquitousFileNotUploadedDueToQuotaError NS_ENUM_AVAILABLE(10_9, 7_0) = 4354, // NSURLUbiquitousItemUploadingErrorKey contains an error with this code when the item has not been uploaded to iCloud because it would make the account go over-quota
    NSUbiquitousFileUbiquityServerNotAvailable NS_ENUM_AVAILABLE(10_9, 7_0) = 4355, // NSURLUbiquitousItemDownloadingErrorKey and NSURLUbiquitousItemUploadingErrorKey contain an error with this code when connecting to the iCloud servers failed

    NSUbiquitousFileErrorMinimum NS_ENUM_AVAILABLE(10_9, 7_0) = 4352,
    NSUbiquitousFileErrorMaximum NS_ENUM_AVAILABLE(10_9, 7_0) = 4607,

    NSUserActivityHandoffFailedError NS_ENUM_AVAILABLE(10_10, 8_0) = 4608,	// The data for the user activity was not available (e.g. if the remote device became unavailable.)
    NSUserActivityConnectionUnavailableError NS_ENUM_AVAILABLE(10_10, 8_0) = 4609,  // The user activity could not be continued because a required connection was not available
    NSUserActivityRemoteApplicationTimedOutError NS_ENUM_AVAILABLE(10_10, 8_0) = 4610, // The remote application failed to send data in time
    NSUserActivityHandoffUserInfoTooLargeError NS_ENUM_AVAILABLE(10_10, 8_0) = 4611, // The NSUserActivity userInfo dictionary was too large to receive

    NSUserActivityErrorMinimum NS_ENUM_AVAILABLE(10_10, 8_0) = 4608,
    NSUserActivityErrorMaximum NS_ENUM_AVAILABLE(10_10, 8_0) = 4863,
    
    NSCoderReadCorruptError NS_ENUM_AVAILABLE(10_11, 9_0) = 4864, // Error parsing data during decode
    NSCoderValueNotFoundError NS_ENUM_AVAILABLE(10_11, 9_0) = 4865, // Data requested was not found
    NSCoderErrorMinimum NS_ENUM_AVAILABLE(10_11, 9_0) = 4864,
    NSCoderErrorMaximum NS_ENUM_AVAILABLE(10_11, 9_0) = 4991,
    
    NSBundleErrorMinimum NS_ENUM_AVAILABLE(10_11, 9_0) = 4992,
    NSBundleErrorMaximum NS_ENUM_AVAILABLE(10_11, 9_0) = 5119,
    
    NSBundleOnDemandResourceOutOfSpaceError NS_ENUM_AVAILABLE(NA, 9_0) = 4992, // There was not enough space available to download the requested On Demand Resources.
    NSBundleOnDemandResourceExceededMaximumSizeError NS_ENUM_AVAILABLE(NA, 9_0) = 4993, // The application exceeded the amount of On Demand Resources content in use at one time
    NSBundleOnDemandResourceInvalidTagError NS_ENUM_AVAILABLE(NA, 9_0) = 4994, // The application specified a tag which the system could not find in the application tag manifest
};

