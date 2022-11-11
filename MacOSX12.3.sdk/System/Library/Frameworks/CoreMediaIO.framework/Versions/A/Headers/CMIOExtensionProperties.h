/*
    File: CMIOExtensionProperties.h

    Contains: API for CoreMediaIO extensions

    Copyright: © 2019-2021 by Apple Inc., all rights reserved.
*/

#import <Foundation/Foundation.h>
#import <CoreMedia/CoreMedia.h>

NS_ASSUME_NONNULL_BEGIN

/*!
@group CMIOExtensionProperty string constants
@discussion
 The CMIOExtensionProperty string constants indicates a property key.
 */
typedef NSString *CMIOExtensionProperty NS_TYPED_ENUM API_AVAILABLE(macos(12.3));

/*!
@constant CMIOExtensionPropertyProviderName
@abstract
 The key for the provider property name.
@discussion
 The property state for CMIOExtensionPropertyProviderName is a string with a readonly attribute.
*/
FOUNDATION_EXTERN CMIOExtensionProperty const CMIOExtensionPropertyProviderName API_AVAILABLE(macos(12.3));

/*!
@constant CMIOExtensionPropertyProviderManufacturer
@abstract
 The key for the provider property manufacturer.
@discussion
 The property state for CMIOExtensionPropertyProviderManufacturer is a string with a readonly attribute.
*/
FOUNDATION_EXTERN CMIOExtensionProperty const CMIOExtensionPropertyProviderManufacturer API_AVAILABLE(macos(12.3));

/*!
@constant CMIOExtensionPropertyDeviceModel
@abstract
 The key for the device property model.
@discussion
 The property state for CMIOExtensionPropertyDeviceModel is a string with a readonly attribute.
*/
FOUNDATION_EXTERN CMIOExtensionProperty const CMIOExtensionPropertyDeviceModel API_AVAILABLE(macos(12.3));

/*!
@constant CMIOExtensionPropertyDeviceIsSuspended
@abstract
 The key for the device property IsSuspended, this key indicates if the device is currently suspended.
@discussion
 For example, the user might close the clamshell of the device. While suspended the device still responds
 to all requests just as if it were active, but the stream(s) will not provide any data.
 The property state for CMIOExtensionPropertyDeviceIsSuspended is a number as boolean with a readonly attribute.
*/
FOUNDATION_EXTERN CMIOExtensionProperty const CMIOExtensionPropertyDeviceIsSuspended API_AVAILABLE(macos(12.3));

/*!
@constant CMIOExtensionPropertyDeviceTransportType
@abstract
 The key for the device property transport type.
@discussion
 The property state for CMIOExtensionPropertyDeviceTransportType is a number whose value correspond to the audio transport type ( kIOAudioDeviceTransportType... ) defined in <IOKit/audio/IOAudioTypes.h> and with a readonly attribute.
*/
FOUNDATION_EXTERN CMIOExtensionProperty const CMIOExtensionPropertyDeviceTransportType API_AVAILABLE(macos(12.3));

/*!
@constant CMIOExtensionPropertyDeviceLinkedCoreAudioDeviceUID
@abstract
 The key for the device property linked CoreAudio device UID.
@discussion
 The property state for CMIOExtensionPropertyDeviceLinkedCoreAudioDeviceUID is a string with a readonly attribute.
*/
FOUNDATION_EXTERN CMIOExtensionProperty const CMIOExtensionPropertyDeviceLinkedCoreAudioDeviceUID API_AVAILABLE(macos(12.3));

/*!
@constant CMIOExtensionPropertyDeviceCanBeDefaultInputDevice
@abstract
 The key for the device property that specifies if a device can be the default input device.
@discussion
 The property state for CMIOExtensionPropertyDeviceCanBeDefaultInputDevice is a number representing a boolean value.
*/
FOUNDATION_EXTERN CMIOExtensionProperty const CMIOExtensionPropertyDeviceCanBeDefaultInputDevice API_AVAILABLE(macos(12.3));

/*!
@constant CMIOExtensionPropertyDeviceCanBeDefaultOutputDevice
@abstract
 The key for the device property that specifies if a device can be the default output device.
@discussion
 The property state for CMIOExtensionPropertyDeviceCanBeDefaultOutputDevice is a number representing a boolean value.
*/
FOUNDATION_EXTERN CMIOExtensionProperty const CMIOExtensionPropertyDeviceCanBeDefaultOutputDevice API_AVAILABLE(macos(12.3));

/*!
@constant CMIOExtensionPropertyStreamActiveFormatIndex
@abstract
 The key for the stream property active format index.
@discussion
 The property state for CMIOExtensionPropertyStreamActiveFormatIndex is a number.
*/
FOUNDATION_EXTERN CMIOExtensionProperty const CMIOExtensionPropertyStreamActiveFormatIndex API_AVAILABLE(macos(12.3));

/*!
@constant CMIOExtensionPropertyStreamFrameDuration
@abstract
 The key for the stream property frame duration.
@discussion
 The property state for CMIOExtensionPropertyStreamFrameDuration needs to be a dictionary representing a CMTime struct that is consistent with the frame duration specification provided by the current active format.
*/
FOUNDATION_EXTERN CMIOExtensionProperty const CMIOExtensionPropertyStreamFrameDuration API_AVAILABLE(macos(12.3));

/*!
@constant CMIOExtensionPropertyStreamMaxFrameDuration
@abstract
 The key for the stream property maximum frame duration.
@discussion
 The property state for CMIOExtensionPropertyStreamMaxFrameDuration needs to be a dictionary representing a CMTime struct.
*/
FOUNDATION_EXTERN CMIOExtensionProperty const CMIOExtensionPropertyStreamMaxFrameDuration API_AVAILABLE(macos(12.3));

/*!
@constant CMIOExtensionPropertyStreamSinkBufferQueueSize
@abstract
 The key for the sink stream property buffer queue size.
@discussion
 The property state for CMIOExtensionPropertyStreamSinkBufferQueueSize is a number. This property translates to the kCMIOStreamPropertyOutputBufferQueueSize property.
*/
FOUNDATION_EXTERN CMIOExtensionProperty const CMIOExtensionPropertyStreamSinkBufferQueueSize API_AVAILABLE(macos(12.3));

/*!
@constant CMIOExtensionPropertyStreamSinkBuffersRequiredForStartup
@abstract
 The key for the sink stream property for number of buffers required for startup.
@discussion
 The property state for CMIOExtensionPropertyStreamSinkBuffersRequiredForStartup is a number. This property translates to the kCMIOStreamPropertyOutputBuffersRequiredForStartup property.
*/
FOUNDATION_EXTERN CMIOExtensionProperty const CMIOExtensionPropertyStreamSinkBuffersRequiredForStartup API_AVAILABLE(macos(12.3));

/*!
@constant CMIOExtensionPropertyStreamSinkBufferUnderrunCount
@abstract
 The key for the sink stream property buffer underrun count.
@discussion
 A number that is incremented every time a stream's buffers are not being serviced fast enough.
 The property state for CMIOExtensionPropertyStreamSinkBufferUnderrunCount is a number with a readonly attribute. This property translates to the kCMIOStreamPropertyOutputBufferUnderrunCount property.
*/
FOUNDATION_EXTERN CMIOExtensionProperty const CMIOExtensionPropertyStreamSinkBufferUnderrunCount API_AVAILABLE(macos(12.3));

/*!
@constant CMIOExtensionPropertyStreamSinkEndOfData
@abstract
 The key for the sink stream property end of data.
@discussion
 The property state for CMIOExtensionPropertyStreamSinkEndOfData is a number, 1 means that the stream has reached the end and a value of 0 means that more data is (or will be) available. This property translates to the kCMIOStreamPropertyEndOfData property.
*/
FOUNDATION_EXTERN CMIOExtensionProperty const CMIOExtensionPropertyStreamSinkEndOfData API_AVAILABLE(macos(12.3));

/*!
@class CMIOExtensionPropertyAttributes
@abstract
 A CMIOExtensionPropertyAttributes describes attributes of a property's value.
*/
API_AVAILABLE(macos(12.3))
@interface CMIOExtensionPropertyAttributes<ObjectType> : NSObject<NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
@method propertyAttributesWithMinValue:maxValue:validValues:readonly:
@abstract
 Returns a property attributes instance.
@param minValue
 The minimum value of the property.
@param maxValue
 The maximum value of the property.
@param validValues
 The array of valid values.
@param readOnly
 A readOnly flag.
@result
 A CMIOExtensionPropertyAttributes instance that describes the attributes of a property.
@discussion
 Property attributes may contain a minValue in which case the property is bounded by a minimum value.
 Property attributes may contain a maxValue in which case the property is bounded by a maximum value.
 Property attributes may contain both minValue and maxValue in which case the property is bounded within a range.
 Property attributes may contain a validValues in which case the property is discrete and can only have a certain set of value.
 If a property does not have a minValue/maxValue/validValues attributes, the property can have any value.
*/
+ (instancetype)propertyAttributesWithMinValue:(nullable ObjectType)minValue maxValue:(nullable ObjectType)maxValue validValues:(nullable NSArray<ObjectType> *)validValues readOnly:(BOOL)readOnly;

/*!
@method propertyAttributesWithMinValue:maxValue:validValues:readonly:
@abstract
 Initialize a property attributes instance.
@param minValue
 The minimum value of the property.
@param maxValue
 The maximum value of the property.
@param validValues
 The array of valid values.
@param readOnly
 A readOnly flag.
@result
 A CMIOExtensionPropertyAttributes instance that describes the attributes of a property.
@discussion
 Property attributes may contain a minValue in which case the property is bounded by a minimum value.
 Property attributes may contain a maxValue in which case the property is bounded by a maximum value.
 Property attributes may contain both minValue and maxValue in which case the property is bounded within a range.
 Property attributes may contain a validValues in which case the property is discrete and can only have a certain set of value.
 If a property does not have a minValue/maxValue/validValues attributes, the property can have any value.
*/
- (instancetype)initWithMinValue:(nullable ObjectType)minValue maxValue:(nullable ObjectType)maxValue validValues:(nullable NSArray<ObjectType> *)validValues readOnly:(BOOL)readOnly NS_DESIGNATED_INITIALIZER;

/*!
@property readOnlyPropertyAttribute
@abstract
 The class property representing a readOnly property attribute with no minValue/maxValue/validValues.
*/
@property(class, readonly) CMIOExtensionPropertyAttributes *readOnlyPropertyAttribute;

/*!
@property minValue
@abstract
 The minimum value of a property.
*/
@property(atomic, readonly, copy, nullable) ObjectType minValue;

/*!
@property maxValue
@abstract
 The maximum value of a property.
*/
@property(atomic, readonly, copy, nullable) ObjectType maxValue;

/*!
@property validValues
@abstract
 An array of valid values.
*/
@property(atomic, readonly, copy, nullable) NSArray<ObjectType> *validValues;

/*!
@property readOnly
@abstract
 The readOnly flag attribute.
*/
@property(atomic, readonly, getter=isReadOnly) BOOL readOnly;

@end

/*!
@class CMIOExtensionPropertyState
@abstract
 A CMIOExtensionPropertyState describes a property state.
*/
API_AVAILABLE(macos(12.3))
@interface CMIOExtensionPropertyState<ObjectType> : NSObject<NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
@method propertyStateWithValue:
@abstract
 Returns a property state instance.
@param value
 The value associated with a property state.
@result
 A CMIOExtensionPropertyState instance with a nil attributes.
*/
+ (instancetype)propertyStateWithValue:(nullable ObjectType)value;

/*!
@method propertyStateWithValue:attributes:
@abstract
 Returns a property state instance.
@param value
 The value associated with a property state.
@param attributes
 The property attributes associated with a property state.
@result
 A CMIOExtensionPropertyState instance.
@discussion
 A nil property attributes defaults to a read/write property that doesn't have a minValue/maxValue/validValues.
 The supported value types are NSDictionary/NSArray/NSString/NSData/NSNumber.
*/
+ (instancetype)propertyStateWithValue:(nullable ObjectType)value attributes:(nullable CMIOExtensionPropertyAttributes<ObjectType> *)attributes;

/*!
@method initWithValue:
@abstract
 Initialize a property state instance.
@param value
 The value associated with a property state.
@result
 A CMIOExtensionPropertyState instance.
@discussion
 A nil property attributes defaults to a read/write property that doesn't have a minValue/maxValue/validValues.
 The supported value types are NSDictionary/NSArray/NSString/NSData/NSNumber.
*/
- (instancetype)initWithValue:(nullable ObjectType)value;

/*!
@method initWithValue:attributes:
@abstract
 Initialize a property state instance.
@param value
 The value associated with a property state.
@param attributes
 The property attributes associated with a property state.
@result
 A CMIOExtensionPropertyState instance.
@discussion
 A nil property attributes defaults to a read/write property that doesn't have a minValue/maxValue/validValues.
 The supported value types are NSDictionary/NSArray/NSString/NSData/NSNumber.
*/
- (instancetype)initWithValue:(nullable ObjectType)value attributes:(nullable CMIOExtensionPropertyAttributes<ObjectType> *)attributes NS_DESIGNATED_INITIALIZER;

/*!
@property value
@abstract
 The value of the property.
*/
@property(atomic, readonly, copy, nullable) ObjectType value;

/*!
@property attributes
@abstract
 The property attributes of the property.
*/
@property(atomic, readonly, strong, nullable) CMIOExtensionPropertyAttributes<ObjectType> *attributes;

@end

/*!
@class CMIOExtensionStreamCustomClockConfiguration
@abstract
 A CMIOExtensionStreamCustomClockProperties describes the parameters used to create a custom clock on the host side (as opposed to the stream using hosttime or a linked Core Audio clock.
*/
API_AVAILABLE(macos(12.3))
@interface CMIOExtensionStreamCustomClockConfiguration : NSObject<NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
@method customClockConfigurationWithName:sourceIdentifier:getTimeCallMinimumInterval:numberOfEventsForRateSmoothing:numberOfAveragesForRateSmoothing:
@abstract
 Return a custom clock configuration instance.
@param clockName
 The name of the clock being specified.
@param sourceIdentifier
 An unique identifier that is used to indicate the entity that is driving the clock. This value is used internally to determine if two custom clocks have the same hardware source, and thus determine whether or not they will drift relative to one another. This parameter is used in the following way: if a device supports multiple active streams that are internally clocked by a common source, then instead of sharing one clock between each stream, a clock per stream can be configured with the sourceIdentifier for each clock set to be the same value.
@param getTimeCallMinimumInterval
 If the clock is queried for its current time more often than this interval, an interpolated value will be returned.
@param numberOfEventsForRateSmoothing
 The number of events to use for rate smoothing; must be > 0.
@param numberOfAveragesForRateSmoothing
 The number of averages used for rate smoothing; if 0, the default smoothing algorithm is used.
@result
 A CMIOExtensionStreamCustomClockConfiguration instance.
*/
+ (instancetype)customClockConfigurationWithClockName:(NSString *)clockName sourceIdentifier:(NSUUID *)sourceIdentifier getTimeCallMinimumInterval:(CMTime)getTimeCallMinimumInterval numberOfEventsForRateSmoothing:(uint32_t)numberOfEventsForRateSmoothing numberOfAveragesForRateSmoothing:(uint32_t)numberOfAveragesForRateSmoothing;

/*!
@method initWithName:sourceIdentifier:getTimeCallMinimumInterval:numberOfEventsForRateSmoothing:numberOfAveragesForRateSmoothing:
@abstract
 Initialize a custom clock configuration instance.
@param clockName
 The name of the clock being specified.
@param sourceIdentifier
 An unique identifier that is used to indicate the entity that is driving the clock. This value is used internally to determine if two custom clocks have the same hardware source, and thus determine whether or not they will drift relative to one another. This parameter is used in the following way: if a device supports multiple active streams that are internally clocked by a common source, then instead of sharing one clock between each stream, a clock per stream can be configured with the sourceIdentifier for each clock set to be the same value.
@param getTimeCallMinimumInterval
 If the clock is queried for its current time more often than this interval, an interpolated value will be returned.
@param numberOfEventsForRateSmoothing
 The number of events to use for rate smoothing; must be > 0.
@param numberOfAveragesForRateSmoothing
 The number of averages used for rate smoothing; if 0, the default smoothing algorithm is used.
@result
 A CMIOExtensionStreamCustomClockConfiguration instance.
*/
- (instancetype)initWithClockName:(NSString *)clockName sourceIdentifier:(NSUUID *)sourceIdentifier getTimeCallMinimumInterval:(CMTime)getTimeCallMinimumInterval numberOfEventsForRateSmoothing:(uint32_t)numberOfEventsForRateSmoothing numberOfAveragesForRateSmoothing:(uint32_t)numberOfAveragesForRateSmoothing NS_DESIGNATED_INITIALIZER;

/*!
@property clockName
@abstract
 The name of the clock.
*/
@property(atomic, strong, readonly) NSString *clockName;

/*!
@property sourceIdentifier
@abstract
 The identifier of the entity driving the clock.
@discussion
 An unique identifier that is used to indicate the entity that is driving the clock. This value is used internally to determine if two custom clocks have the same hardware source, and thus determine whether or not they will drift relative to one another. This parameter is used in the following way: if a device supports multiple active streams that are internally clocked by a common source, then instead of sharing one clock between each stream, a clock per stream can be configured with the sourceIdentifier for each clock set to be the same value.
*/
@property(atomic, strong, readonly) NSUUID *sourceIdentifier;

/*!
@property getTimeCallMinimumInterval
@abstract
 If the clock is queried for its current time more often than this interval, an interpolated value will be returned.
*/
@property(atomic, readonly) CMTime getTimeCallMinimumInterval;

/*!
@property numberOfEventsForRateSmoothing
@abstract
 The number of events to use for rate smoothing; will be > 0.
*/
@property(atomic, readonly) uint32_t numberOfEventsForRateSmoothing;

/*!
@property numberOfAveragesForRateSmoothing
@abstract
 The number of averages used for rate smoothing; 0 indicates that the default smoothing algorithm is used.
*/
@property(atomic, readonly) uint32_t numberOfAveragesForRateSmoothing;

@end

/*!
@class CMIOExtensionStreamFormat
@abstract
 A CMIOExtensionStreamFormat describes a stream format.
*/
API_AVAILABLE(macos(12.3))
@interface CMIOExtensionStreamFormat : NSObject<NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
@method streamFormatWithFormatDescription:maxFrameDuration:minFrameDuration:validFrameDurations:
@abstract
 Returns a stream format instance.
@param formatDescription
 The format description of the samples delivered by the stream.
@param maxFrameDuration
 The maximum frame duration.
@param minFrameDuration
 The minimum frame duration.
@param validFrameDurations
 The list of valid CMTime as dictionaries. If nil the full range between min and max is valid. The CMTime in dictionary format are made with CMTimeCopyAsDictionary.
@result
 A CMIOExtensionStreamFormat instance that describes the stream format.
@discussion
 A frame duration is the reciprocal of a frame rate.
 If a CMIOExtensionStreamFormat's validFrameDurations property is not nil and not empty, the frame duration are discrete and can only have a certain set of value. Current frame duration and maximum frame duration can be changed with the properties CMIOExtensionPropertyStreamFrameDuration and CMIOExtensionPropertyStreamMaxFrameDuration.
*/
+ (instancetype)streamFormatWithFormatDescription:(CMFormatDescriptionRef)formatDescription maxFrameDuration:(CMTime)maxFrameDuration minFrameDuration:(CMTime)minFrameDuration validFrameDurations:(nullable NSArray<NSDictionary *> *)validFrameDurations NS_REFINED_FOR_SWIFT;

/*!
@method initWithFormatDescription:maxFrameDuration:minFrameDuration:validFrameDurations:
@abstract
 Initialize a stream format instance.
@param formatDescription
 The format description of the samples delivered by the stream.
@param maxFrameDuration
 The maximum frame duration.
@param minFrameDuration
 The minimum frame duration.
@param validFrameDurations
 The list of valid CMTime as dictionaries if nil the full range between min and max is valid. The CMTime in dictionary format are made with CMTimeCopyAsDictionary.
@result
 A CMIOExtensionStreamFormat instance that describes the stream format.
@discussion
 A frame duration is the reciprocal of a frame rate.
 If a CMIOExtensionStreamFormat's validFrameDurations property is not nil and not empty, the frame duration are discrete and can only have a certain set of value. Current frame duration and maximum frame duration can be changed with the properties CMIOExtensionPropertyStreamFrameDuration and CMIOExtensionPropertyStreamMaxFrameDuration.
*/
- (instancetype)initWithFormatDescription:(CMFormatDescriptionRef)formatDescription maxFrameDuration:(CMTime)maxFrameDuration minFrameDuration:(CMTime)minFrameDuration validFrameDurations:(nullable NSArray<NSDictionary *> *)validFrameDurations NS_REFINED_FOR_SWIFT NS_DESIGNATED_INITIALIZER;

/*!
@property formatDescription
@abstract
 The format description of the samples delivered by the stream.
*/
@property(atomic, readonly, strong) __attribute__((NSObject)) CMFormatDescriptionRef formatDescription;

/*!
@property minFrameDuration
@abstract
 The minimum frame duration (AKA maximum frame rate).
*/
@property(atomic, readonly) CMTime minFrameDuration;

/*!
@property maxFrameDuration
@abstract
 The maximum frame duration (AKA minimum frame rate).
*/
@property(atomic, readonly) CMTime maxFrameDuration;

/*!
@property validFrameDurations
@abstract
 The valid frame durations as an array of CMTime as dictionaries. The CMTime in dictionary format are made with CMTimeCopyAsDictionary.
*/
@property(atomic, readonly, strong, nullable) NSArray<NSDictionary *> *validFrameDurations NS_REFINED_FOR_SWIFT;

@end

API_AVAILABLE(macos(12.3))
@interface CMIOExtensionScheduledOutput : NSObject<NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
@method scheduledOutputWithSequenceNumber:hostTimeInNanoseconds:
@abstract
 Return a stream scheduled output instance.
@param sequenceNumber
 The buffer sequence number that was output.
@param hostTimeInNanoseconds
 The host time in nanoseconds when the buffer was output.
@result
 A CMIOExtensionScheduledOutput instance that describes the state of the stream.
*/
+ (instancetype)scheduledOutputWithSequenceNumber:(uint64_t)sequenceNumber hostTimeInNanoseconds:(uint64_t)hostTimeInNanoseconds;

/*!
@method initWithSequenceNumber:hostTimeInNanoseconds:
@abstract
 Initialize a stream scheduled output instance.
@param sequenceNumber
 The buffer sequence number that was output.
@param hostTimeInNanoseconds
 The host time in nanoseconds when the buffer was output.
@result
 A CMIOExtensionScheduledOutput instance that describes the state of the stream.
*/
- (instancetype)initWithSequenceNumber:(uint64_t)sequenceNumber hostTimeInNanoseconds:(uint64_t)hostTimeInNanoseconds NS_DESIGNATED_INITIALIZER;

/*!
@property sequenceNumber
@abstract
 The buffer sequence number that was output.
*/
@property(atomic, readonly) uint64_t sequenceNumber;

/*!
@property hostTimeInNanoseconds
@abstract
 The host time in nanoseconds when the buffer was output.
*/
@property(atomic, readonly) uint64_t hostTimeInNanoseconds;

@end

API_AVAILABLE(macos(12.3))
@interface CMIOExtensionClient : NSObject<NSCopying>

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
@property clientID
@abstract
 The client unique identifier.
*/
@property(atomic, readonly, copy) NSUUID *clientID;

/*!
@property pid
@abstract
 The pid of the client application.
*/
@property(atomic, readonly) pid_t pid;

@end

NS_ASSUME_NONNULL_END
