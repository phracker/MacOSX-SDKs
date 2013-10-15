/*
	AppKitErrors.h
	Application Kit
	Copyright (c) 2004-2005, Apple Computer, Inc.
	All rights reserved.
*/

#import <Foundation/NSObject.h>

#if MAC_OS_X_VERSION_10_4 <= MAC_OS_X_VERSION_MAX_ALLOWED

/* NSError codes for AppKit added errors in NSCocoaErrorDomain.  Foundation error codes can be found in <Foundation/FoundationErrors.h>; CoreData error codes in <CoreData/CoreDataErrors.h>.
*/
enum {
    NSTextReadInapplicableDocumentTypeError = 65806,		// NSAttributedString parsing error
    NSTextWriteInapplicableDocumentTypeError = 66062,		// NSAttributedString generating error

    // Inclusive error range definitions, for checking future error codes
    NSTextReadWriteErrorMinimum = 65792,
    NSTextReadWriteErrorMaximum = 66303
};

#endif

