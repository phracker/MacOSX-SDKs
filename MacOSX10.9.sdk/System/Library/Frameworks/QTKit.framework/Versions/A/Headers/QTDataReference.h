/*
	File:		QTDataReference.h

	Copyright:	(c)2004-2012 by Apple Inc., all rights reserved.

*/

/*
  QTKit has been deprecated in 10.9.

  AVFoundation and AVKit are the frameworks recommended for all new development 
  involving time-based audiovisual media on OS X.  In order to transition your 
  project from QTKit to AVFoundation please refer to:
  "Technical Note TN2300 Transitioning QTKit code to AV Foundation".
*/

#import <Foundation/Foundation.h>
#if !__LP64__
	#import <QuickTime/QuickTime.h>
#endif
#import <QTKit/QTKitDefines.h>

// data handler types
QTKIT_EXTERN NSString * const QTDataReferenceTypeFile       AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
QTKIT_EXTERN NSString * const QTDataReferenceTypeHandle     AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
QTKIT_EXTERN NSString * const QTDataReferenceTypePointer    AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
QTKIT_EXTERN NSString * const QTDataReferenceTypeResource   AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
QTKIT_EXTERN NSString * const QTDataReferenceTypeURL        AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

@interface QTDataReference : NSObject <NSCoding>
{
@private
#if __LP64__
	int32_t		_proxy;
#else
	NSString	*_fileName;
	NSURL		*_url;
	NSData		*_data;
	NSString	*_name;
	NSString	*_MIMEType;
	Handle		_dataRef;
	OSType		_dataRefType;
#endif
	long		_reserved1;
	long		_reserved2;
	long		_reserved3;
}

	// class methods
+ (id)dataReferenceWithDataRef:(Handle)dataRef type:(NSString *)type AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
+ (id)dataReferenceWithDataRefData:(NSData *)dataRefData type:(NSString *)type AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
+ (id)dataReferenceWithReferenceToFile:(NSString *)fileName AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
+ (id)dataReferenceWithReferenceToURL:(NSURL *)url AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
+ (id)dataReferenceWithReferenceToData:(NSData *)data AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
+ (id)dataReferenceWithReferenceToData:(NSData *)data name:(NSString *)name MIMEType:(NSString *)MIMEType AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

	// init
- (id)initWithDataRef:(Handle)dataRef type:(NSString *)type AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (id)initWithDataRefData:(NSData *)dataRefData type:(NSString *)type AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (id)initWithReferenceToFile:(NSString *)fileName AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (id)initWithReferenceToURL:(NSURL *)url AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (id)initWithReferenceToData:(NSData *)data AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (id)initWithReferenceToData:(NSData *)data name:(NSString *)name MIMEType:(NSString *)MIMEType AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

	// getters
- (Handle)dataRef AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (NSData *)dataRefData AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (NSString *)dataRefType AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (NSString *)referenceFile AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (NSURL *)referenceURL AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (NSData *)referenceData AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (NSString *)name AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (NSString *)MIMEType AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

	// setters
- (void)setDataRef:(Handle)dataRef AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (void)setDataRefType:(NSString *)type AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

@end
