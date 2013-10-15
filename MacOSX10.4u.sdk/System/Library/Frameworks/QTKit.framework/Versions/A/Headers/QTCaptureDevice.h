/*
	File:		QTCaptureDevice.h
 
	Copyright:	(c)2007 by Apple Inc., all rights reserved.

 */

#import <Foundation/Foundation.h>
#import <QTKit/QTKitDefines.h>

#if (QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4)

//==================================================================================================
// Notifications
//==================================================================================================
QTKIT_EXTERN NSString * const QTCaptureDeviceWasConnectedNotification					AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
QTKIT_EXTERN NSString * const QTCaptureDeviceWasDisconnectedNotification				AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
QTKIT_EXTERN NSString * const QTCaptureDeviceFormatDescriptionsWillChangeNotification	AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
QTKIT_EXTERN NSString * const QTCaptureDeviceFormatDescriptionsDidChangeNotification	AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
QTKIT_EXTERN NSString * const QTCaptureDeviceAttributeWillChangeNotification			AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
QTKIT_EXTERN NSString * const QTCaptureDeviceAttributeDidChangeNotification				AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

// userInfo key for QTCaptureDeviceAttributeWillChangeNotification and QTCaptureDeviceAttributeDidChangeNotification - returns the key of the attribute that changed
QTKIT_EXTERN NSString * const QTCaptureDeviceChangedAttributeKey						AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

//==================================================================================================
// Attributes
//==================================================================================================

// This attribute returns whether or not data capture on the device is suspended due to a feature on the device.
// For example, this attribute is YES for the external iSight when its privacy iris is closed, or for the internal iSight on a notebook when the notebook's display is closed.
QTKIT_EXTERN NSString * const QTCaptureDeviceSuspendedAttribute							AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;	// NSNumber interpreted as a BOOL
                                                                                                                                    // Read Only. KVC key name: @"suspended"

// This attribute returns an array of QTCaptureDevice objects that, although they are separate devices on the system, are a part of the same physical device as the receiver.
// For example, for the external iSight camera, this attribute returns an array containing a QTCaptureDevice for the external iSight microphone.
QTKIT_EXTERN NSString * const QTCaptureDeviceLinkedDevicesAttribute						AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;	// NSArray of QTCaptureDevice objects
                                                                                                                                    // Read Only. KVC key name: @"linkedDevices"

// Some devices can capture data from one of multiple data sources (different input jacks on the same audio device, for example).
// For devices with multiple possible data sources these attributes can be used to get and set which data source the device is currently using.
QTKIT_EXTERN NSString * const QTCaptureDeviceAvailableInputSourcesAttribute             AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;	// NSArray of NSDictionary objects containing keys and values described below
                                                                                                                                    // Read Only. KVC key name: @"availableInputSources"
QTKIT_EXTERN NSString * const QTCaptureDeviceInputSourceIdentifierAttribute             AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;	// An object returned by the QTCaptureDeviceInputSourceIdentifierKey key in one of the dictionaries returned by QTCaptureDeviceAvailableInputSourcesAttribute
                                                                                                                                    // Read/Write. KVC key name: @"inputSourceIdentifier"

// keys for the dictionaries returned by QTCaptureDeviceAvailableInputSourcesAttribute:
QTKIT_EXTERN NSString * const QTCaptureDeviceInputSourceIdentifierKey                   AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;	// An object representing a unique ID for the input source. This ID is not guaranteed to persist between device connections or changes in device configuration.
                                                                                                                                    // KVC key name: @"identifier"
QTKIT_EXTERN NSString * const QTCaptureDeviceInputSourceLocalizedDisplayNameKey         AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;	// NSString containing a name for the data source suitable for display in a user interface
                                                                                                                                    // KVC key name: @"localizedDisplayName"

// If a device was intialized using a legacy Sequence Grabber component, this attribute returns the component instance responsible for capturing from the device
#if !__LP64__
QTKIT_EXTERN NSString * const QTCaptureDeviceLegacySequenceGrabberAttribute				AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;	// NSValue interpreted as a Sequence Grabber ComponentInstance
                                                                                                                                    // Read Only. KVC key name: @"legacySequenceGrabber"
#endif

// For AVC devices with transport controls, such as tape-based camcorders, this attribute can be used to control the media on the device
QTKIT_EXTERN NSString * const QTCaptureDeviceAVCTransportControlsAttribute				AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;	// NSDictionary containing keys and values described below
                                                                                                                                    // Read/Write. KVC key name: @"AVCTransportControls"

// keys for the dictionary passed to QTCaptureDeviceAVCTransportControlsAttribute
QTKIT_EXTERN NSString * const QTCaptureDeviceAVCTransportControlsPlaybackModeKey		AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;	// NSNumber interpreted as a  QTCaptureDeviceAVCTransportControlsPlaybackMode
                                                                                                                                    // KVC key name: @"playbackMode"
QTKIT_EXTERN NSString * const QTCaptureDeviceAVCTransportControlsSpeedKey				AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;	// NSNumber interpreted as a QTCaptureDeviceAVCTransportControlsSpeed
                                                                                                                                    // KVC key name: @"speed"

// values for the dictionary passed to QTCaptureDeviceAVCTransportControlsAttribute
enum {
	QTCaptureDeviceAVCTransportControlsNotPlayingMode		= 0,
	QTCaptureDeviceAVCTransportControlsPlayingMode			= 1
};
typedef NSUInteger QTCaptureDeviceAVCTransportControlsPlaybackMode;

enum {
	QTCaptureDeviceAVCTransportControlsFastestReverseSpeed	= -19000,	
	QTCaptureDeviceAVCTransportControlsVeryFastReverseSpeed	= -16000,
	QTCaptureDeviceAVCTransportControlsFastReverseSpeed		= -13000,
	QTCaptureDeviceAVCTransportControlsNormalReverseSpeed	= -10000,
	QTCaptureDeviceAVCTransportControlsSlowReverseSpeed		= -7000,
	QTCaptureDeviceAVCTransportControlsVerySlowReverseSpeed = -4000,
	QTCaptureDeviceAVCTransportControlsSlowestReverseSpeed	= -1000,
	QTCaptureDeviceAVCTransportControlsStoppedSpeed			= 0,	
	QTCaptureDeviceAVCTransportControlsSlowestForwardSpeed	= 1000,
	QTCaptureDeviceAVCTransportControlsVerySlowForwardSpeed = 4000,
	QTCaptureDeviceAVCTransportControlsSlowForwardSpeed		= 7000,
	QTCaptureDeviceAVCTransportControlsNormalForwardSpeed	= 10000,
	QTCaptureDeviceAVCTransportControlsFastForwardSpeed		= 13000,
	QTCaptureDeviceAVCTransportControlsVeryFastForwardSpeed	= 16000,
	QTCaptureDeviceAVCTransportControlsFastestForwardSpeed	= 19000,
};
typedef NSInteger QTCaptureDeviceAVCTransportControlsSpeed;

//==================================================================================================
// QTCaptureDevice Class
//==================================================================================================

@class QTCaptureDeviceInternal;

@interface QTCaptureDevice : NSObject <NSCoding> {
@private
#if __LP64__
	int32_t					_proxy;
#else
	QTCaptureDeviceInternal	*_internal;
#endif
	long					_reserved1;
	long					_reserved2;
	long					_reserved3;
}

+ (NSArray *)inputDevices;
+ (NSArray *)inputDevicesWithMediaType:(NSString *)mediaType;				// media types are defined in QTMedia.h
+ (QTCaptureDevice *)defaultInputDeviceWithMediaType:(NSString *)mediaType;	// media types are defined in QTMedia.h
+ (QTCaptureDevice *)deviceWithUniqueID:(NSString *)deviceUniqueID;

- (NSString *)uniqueID;
- (NSString *)modelUniqueID;
- (NSString *)localizedDisplayName;

- (NSArray *)formatDescriptions;
- (BOOL)hasMediaType:(NSString *)mediaType;	// media types are defined in QTMedia.h

- (NSDictionary *)deviceAttributes;
- (void)setDeviceAttributes:(NSDictionary *)deviceAttributes;
- (BOOL)attributeIsReadOnly:(NSString *)attributeKey;
- (id)attributeForKey:(NSString *)attributeKey;
- (void)setAttribute:(id)attribute forKey:(NSString *)attributeKey;

// Applications can use KVO with the @"connected" and @"inUseByAnotherApplication" keys to be notified of changes.
- (BOOL)isConnected;
- (BOOL)isInUseByAnotherApplication;

- (BOOL)isOpen;
- (BOOL)open:(NSError **)errorPtr;
- (void)close;

@end

#endif /* (QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4) */
