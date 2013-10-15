/*
	File:		QTCaptureDevice.h
 
	Copyright:	(c)2007-2012 by Apple Inc., all rights reserved.

*/

/*
  QTKit has been deprecated in 10.9.

  AVFoundation and AVKit are the frameworks recommended for all new development 
  involving time-based audiovisual media on OS X.  In order to transition your 
  project from QTKit to AVFoundation please refer to:
  "Technical Note TN2300 Transitioning QTKit code to AV Foundation".
*/

#import <Foundation/Foundation.h>
#import <QTKit/QTKitDefines.h>

#if (QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4)

//==================================================================================================
// Notifications
//==================================================================================================
QTKIT_EXTERN NSString * const QTCaptureDeviceWasConnectedNotification					AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
QTKIT_EXTERN NSString * const QTCaptureDeviceWasDisconnectedNotification				AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
QTKIT_EXTERN NSString * const QTCaptureDeviceFormatDescriptionsWillChangeNotification	AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
QTKIT_EXTERN NSString * const QTCaptureDeviceFormatDescriptionsDidChangeNotification	AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
QTKIT_EXTERN NSString * const QTCaptureDeviceAttributeWillChangeNotification			AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
QTKIT_EXTERN NSString * const QTCaptureDeviceAttributeDidChangeNotification				AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

// userInfo key for QTCaptureDeviceAttributeWillChangeNotification and QTCaptureDeviceAttributeDidChangeNotification - returns the key of the attribute that changed
QTKIT_EXTERN NSString * const QTCaptureDeviceChangedAttributeKey						AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

//==================================================================================================
// Attributes
//==================================================================================================

// This attribute returns whether or not data capture on the device is suspended due to a feature on the device.
// For example, this attribute is YES for the external iSight when its privacy iris is closed, or for the internal iSight on a notebook when the notebook's display is closed.
QTKIT_EXTERN NSString * const QTCaptureDeviceSuspendedAttribute							AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSNumber interpreted as a BOOL
                                                                                                                                    // Read Only. KVC key name: @"suspended"

// This attribute returns an array of QTCaptureDevice objects that, although they are separate devices on the system, are a part of the same physical device as the receiver.
// For example, for the external iSight camera, this attribute returns an array containing a QTCaptureDevice for the external iSight microphone.
QTKIT_EXTERN NSString * const QTCaptureDeviceLinkedDevicesAttribute						AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSArray of QTCaptureDevice objects
                                                                                                                                    // Read Only. KVC key name: @"linkedDevices"

// Some devices can capture data from one of multiple data sources (different input jacks on the same audio device, for example).
// For devices with multiple possible data sources these attributes can be used to get and set which data source the device is currently using.
QTKIT_EXTERN NSString * const QTCaptureDeviceAvailableInputSourcesAttribute             AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSArray of NSDictionary objects containing keys and values described below
                                                                                                                                    // Read Only. KVC key name: @"availableInputSources"
QTKIT_EXTERN NSString * const QTCaptureDeviceInputSourceIdentifierAttribute             AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // An object returned by the QTCaptureDeviceInputSourceIdentifierKey key in one of the dictionaries returned by QTCaptureDeviceAvailableInputSourcesAttribute
                                                                                                                                    // Read/Write. KVC key name: @"inputSourceIdentifier"

// keys for the dictionaries returned by QTCaptureDeviceAvailableInputSourcesAttribute:
QTKIT_EXTERN NSString * const QTCaptureDeviceInputSourceIdentifierKey                   AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // An object representing a unique ID for the input source. This ID is not guaranteed to persist between device connections or changes in device configuration.
                                                                                                                                    // KVC key name: @"identifier"
QTKIT_EXTERN NSString * const QTCaptureDeviceInputSourceLocalizedDisplayNameKey         AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSString containing a name for the data source suitable for display in a user interface
                                                                                                                                    // KVC key name: @"localizedDisplayName"

// If a device was intialized using a legacy Sequence Grabber component, this attribute returns the component instance responsible for capturing from the device
#if !__LP64__
QTKIT_EXTERN NSString * const QTCaptureDeviceLegacySequenceGrabberAttribute				AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSValue interpreted as a Sequence Grabber ComponentInstance
                                                                                                                                    // Read Only. KVC key name: @"legacySequenceGrabber"
#endif

// For AVC devices with transport controls, such as tape-based camcorders, this attribute can be used to control the media on the device
QTKIT_EXTERN NSString * const QTCaptureDeviceAVCTransportControlsAttribute				AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSDictionary containing keys and values described below
                                                                                                                                    // Read/Write. KVC key name: @"AVCTransportControls"

// keys for the dictionary passed to QTCaptureDeviceAVCTransportControlsAttribute
QTKIT_EXTERN NSString * const QTCaptureDeviceAVCTransportControlsPlaybackModeKey		AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSNumber interpreted as a  QTCaptureDeviceAVCTransportControlsPlaybackMode
                                                                                                                                    // KVC key name: @"playbackMode"
QTKIT_EXTERN NSString * const QTCaptureDeviceAVCTransportControlsSpeedKey				AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;      // NSNumber interpreted as a QTCaptureDeviceAVCTransportControlsSpeed
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
	QTCaptureDeviceInternal	*_internal;
	long					_reserved1;
	long					_reserved2;
	long					_reserved3;
}

+ (NSArray *)inputDevices AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
+ (NSArray *)inputDevicesWithMediaType:(NSString *)mediaType AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;				// media types are defined in QTMedia.h
+ (QTCaptureDevice *)defaultInputDeviceWithMediaType:(NSString *)mediaType AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;	// media types are defined in QTMedia.h
+ (QTCaptureDevice *)deviceWithUniqueID:(NSString *)deviceUniqueID AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

- (NSString *)uniqueID AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (NSString *)modelUniqueID AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (NSString *)localizedDisplayName AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

- (NSArray *)formatDescriptions AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (BOOL)hasMediaType:(NSString *)mediaType AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;	// media types are defined in QTMedia.h

- (NSDictionary *)deviceAttributes AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (void)setDeviceAttributes:(NSDictionary *)deviceAttributes AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (BOOL)attributeIsReadOnly:(NSString *)attributeKey AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (id)attributeForKey:(NSString *)attributeKey AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (void)setAttribute:(id)attribute forKey:(NSString *)attributeKey AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

// Applications can use KVO with the @"connected" and @"inUseByAnotherApplication" keys to be notified of changes.
- (BOOL)isConnected AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (BOOL)isInUseByAnotherApplication AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

- (BOOL)isOpen AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (BOOL)open:(NSError **)errorPtr AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (void)close AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

@end

#endif /* (QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4) */
