/*
	File:		QTDataReference.h

	Copyright:	(c)2004-2007 by Apple Inc., all rights reserved.

*/


#import <Foundation/Foundation.h>
#if !__LP64__
	#import <QuickTime/QuickTime.h>
#endif
#import <QTKit/QTKitDefines.h>

// data handler types
QTKIT_EXTERN NSString * const QTDataReferenceTypeFile						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString * const QTDataReferenceTypeHandle						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString * const QTDataReferenceTypePointer					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString * const QTDataReferenceTypeResource					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString * const QTDataReferenceTypeURL						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

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
+ (id)dataReferenceWithDataRef:(Handle)dataRef type:(NSString *)type;
+ (id)dataReferenceWithDataRefData:(NSData *)dataRefData type:(NSString *)type;
+ (id)dataReferenceWithReferenceToFile:(NSString *)fileName;
+ (id)dataReferenceWithReferenceToURL:(NSURL *)url;
+ (id)dataReferenceWithReferenceToData:(NSData *)data;
+ (id)dataReferenceWithReferenceToData:(NSData *)data name:(NSString *)name MIMEType:(NSString *)MIMEType;

	// init
- (id)initWithDataRef:(Handle)dataRef type:(NSString *)type;
- (id)initWithDataRefData:(NSData *)dataRefData type:(NSString *)type;
- (id)initWithReferenceToFile:(NSString *)fileName;
- (id)initWithReferenceToURL:(NSURL *)url;
- (id)initWithReferenceToData:(NSData *)data;
- (id)initWithReferenceToData:(NSData *)data name:(NSString *)name MIMEType:(NSString *)MIMEType;

	// getters
- (Handle)dataRef;
- (NSData *)dataRefData;
- (NSString *)dataRefType;
- (NSString *)referenceFile;
- (NSURL *)referenceURL;
- (NSData *)referenceData;
- (NSString *)name;
- (NSString *)MIMEType;

	// setters
- (void)setDataRef:(Handle)dataRef;
- (void)setDataRefType:(NSString *)type;

@end

