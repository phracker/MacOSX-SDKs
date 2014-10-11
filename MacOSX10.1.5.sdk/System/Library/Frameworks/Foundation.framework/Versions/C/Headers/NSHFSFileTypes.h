/*	NSHFSFileTypes.h
	Copyright 2000-2001, Apple, Inc. All rights reserved.
*/

/*
Functions that help manage HFS file type strings.

The file type strings that are accepted or returned by many Cocoa methods may contain either a file name extension or an encoded HFS file type surrounded by apostrophes, like so:

"'<HFS Four Character File Type Code>'"

For example, the type of a typical Mac OS 9 text file can be specified by the string "'TEXT'".
*/


#import <CoreFoundation/CFBase.h>


@class NSString;


// Given an HFS file type code, this function returns a string that encodes the file type as described above.  The string will have been autoreleased.
NSString *NSFileTypeForHFSTypeCode(OSType hfsFileTypeCode);

// Given a string of the sort encoded by NSFileTypeForHFSTypeCode(), this function returns the corresponding HFS file type code.  It returns zero otherwise.
OSType NSHFSTypeCodeFromFileType(NSString *fileTypeString);

// Given the full absolute path of a file, this function returns a string that encodes the file's HFS file type as described above, or nil if the operation was not successful.  The string will have been autoreleased.
NSString *NSHFSTypeOfFile(NSString *fullFilePath);
