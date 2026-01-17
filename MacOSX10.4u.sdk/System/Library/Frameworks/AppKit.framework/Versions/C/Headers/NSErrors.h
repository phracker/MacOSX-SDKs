/*
	NSErrors.h
	Application Kit
	Copyright (c) 1994-2005, Apple Computer, Inc.
	All rights reserved.
*/

#import <AppKit/AppKitDefines.h>

@class NSString;

// The following strings are the names of exceptions the AppKit can raise

APPKIT_EXTERN NSString *NSTextLineTooLongException;
APPKIT_EXTERN NSString *NSTextNoSelectionException;
APPKIT_EXTERN NSString *NSWordTablesWriteException;
APPKIT_EXTERN NSString *NSWordTablesReadException;
APPKIT_EXTERN NSString *NSTextReadException;
APPKIT_EXTERN NSString *NSTextWriteException;
APPKIT_EXTERN NSString *NSPasteboardCommunicationException;
APPKIT_EXTERN NSString *NSPrintingCommunicationException;
APPKIT_EXTERN NSString *NSAbortModalException;
APPKIT_EXTERN NSString *NSAbortPrintingException;
APPKIT_EXTERN NSString *NSIllegalSelectorException;
APPKIT_EXTERN NSString *NSAppKitVirtualMemoryException;
APPKIT_EXTERN NSString *NSBadRTFDirectiveException;
APPKIT_EXTERN NSString *NSBadRTFFontTableException;
APPKIT_EXTERN NSString *NSBadRTFStyleSheetException;
APPKIT_EXTERN NSString *NSTypedStreamVersionException;
APPKIT_EXTERN NSString *NSTIFFException;
APPKIT_EXTERN NSString *NSPrintPackageException;
APPKIT_EXTERN NSString *NSBadRTFColorTableException;
APPKIT_EXTERN NSString *NSDraggingException;
APPKIT_EXTERN NSString *NSColorListIOException;
APPKIT_EXTERN NSString *NSColorListNotEditableException;
APPKIT_EXTERN NSString *NSBadBitmapParametersException;
APPKIT_EXTERN NSString *NSWindowServerCommunicationException;
APPKIT_EXTERN NSString *NSFontUnavailableException;
APPKIT_EXTERN NSString *NSPPDIncludeNotFoundException;
APPKIT_EXTERN NSString *NSPPDParseException;
APPKIT_EXTERN NSString *NSPPDIncludeStackOverflowException;
APPKIT_EXTERN NSString *NSPPDIncludeStackUnderflowException;
APPKIT_EXTERN NSString *NSRTFPropertyStackOverflowException;
APPKIT_EXTERN NSString *NSAppKitIgnoredException;
APPKIT_EXTERN NSString *NSBadComparisonException;
APPKIT_EXTERN NSString *NSImageCacheException;
APPKIT_EXTERN NSString *NSNibLoadingException;
APPKIT_EXTERN NSString *NSBrowserIllegalDelegateException;
APPKIT_EXTERN NSString *NSAccessibilityException;

