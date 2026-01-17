/*
	File:		QTUtilities.h

	Copyright:	(c)2004 by Apple Computer, Inc., all rights reserved.

*/


#import <Foundation/Foundation.h>
#import <QuickTime/QuickTime.h>
#import <QTKit/QTKitDefines.h>

	// helper functions
QTKIT_EXTERN NSString *QTStringForOSType (OSType type)				AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN OSType QTOSTypeForString (NSString *string)			AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

