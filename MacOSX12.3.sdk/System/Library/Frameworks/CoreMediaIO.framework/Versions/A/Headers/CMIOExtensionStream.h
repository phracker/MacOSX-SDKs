/*
    File: CMIOExtensionStream.h

    Contains: API for CoreMediaIO extensions

    Copyright: © 2019-2021 by Apple Inc., all rights reserved.
*/

#import <Foundation/Foundation.h>
#import <CoreMediaIO/CMIOExtensionProperties.h>

NS_ASSUME_NONNULL_BEGIN

/*!
@enum CMIOExtensionStreamDirection
@abstract
 Constants indicating the direction of the stream.
@constant CMIOExtensionStreamDirectionSource
 Indicates that the stream is a source; i.e., provides sample buffers for capture.
@constant CMIOExtensionStreamDirectionSink
 Indicates that the stream is a sink; i.e., consumes sample buffers for playback.
*/
typedef NS_ENUM(NSInteger, CMIOExtensionStreamDirection) {
    CMIOExtensionStreamDirectionSource      = 0,
    CMIOExtensionStreamDirectionSink        = 1,
} NS_SWIFT_NAME(CMIOExtensionStream.Direction) API_AVAILABLE(macos(12.3));

/*!
@enum CMIOExtensionStreamClockType
@abstract
 Constants indicating the clock of the stream.
@constant CMIOExtensionStreamClockTypeHostTime
 Indicates that the stream's clock is the host time clock.
@constant CMIOExtensionStreamClockTypeLinkedCoreAudioDeviceUID
 Indicates that the stream's clock is the clock from the linked CoreAudio device.
@constant CMIOExtensionStreamClockTypeCustom
 Indicates that the stream's clock is specific to the device hosting the stream; this clock type cannot be set directly by the extension, but instead is set automatically when a  CMIOExtensionStreamCustomClockConfiguration is used when creating a CMIOExtensionStream.
*/
typedef NS_ENUM(NSInteger, CMIOExtensionStreamClockType) {
    CMIOExtensionStreamClockTypeHostTime                    = 0,
    CMIOExtensionStreamClockTypeLinkedCoreAudioDeviceUID    = 1,
    CMIOExtensionStreamClockTypeCustom                      = 2,
} NS_SWIFT_NAME(CMIOExtensionStream.ClockType) API_AVAILABLE(macos(12.3));

/*!
@enum CMIOExtensionStreamDiscontinuityFlags
@abstract
 Constants indicating the state of a stream discontinuity.
@constant CMIOExtensionStreamDiscontinuityFlagNone
 Indicates that there is no stream discontinuity.
@constant CMIOExtensionStreamDiscontinuityFlagUnknown
 Indicates that there is a stream discontinuity of type unknown.
@constant CMIOExtensionStreamDiscontinuityFlagTime
 Indicates that there is a stream discontinuity of type time.
@constant CMIOExtensionStreamDiscontinuityFlagSampleDropped
 Indicates that there is a stream discontinuity of type dropped sample.
*/
typedef NS_OPTIONS(uint32_t, CMIOExtensionStreamDiscontinuityFlags) {
    CMIOExtensionStreamDiscontinuityFlagNone            = 0,
    CMIOExtensionStreamDiscontinuityFlagUnknown         = (1L << 0),
    CMIOExtensionStreamDiscontinuityFlagTime            = (1L << 1),
    CMIOExtensionStreamDiscontinuityFlagSampleDropped   = (1L << 6),
} NS_SWIFT_NAME(CMIOExtensionStream.DiscontinuityFlags) API_AVAILABLE(macos(12.3));

/*!
@class CMIOExtensionStreamProperties
@abstract
 A CMIOExtensionStreamProperties describes a CoreMediaIO extension stream properties.
*/
API_AVAILABLE(macos(12.3))
@interface CMIOExtensionStreamProperties : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
@method streamPropertiesWithDictionary:
@abstract
 Return a stream properties instance.
@param propertiesDictionary
 The dictionary of properties.
@result
 A CMIOExtensionStreamProperties instance.
*/
+ (instancetype)streamPropertiesWithDictionary:(NSDictionary<CMIOExtensionProperty, CMIOExtensionPropertyState *> *)propertiesDictionary;

/*!
@method initWithDictionary:
@abstract
 Initialize a stream properties instance.
 @param propertiesDictionary
  The dictionary of properties.
@result
 A CMIOExtensionStreamProperties instance.
*/
- (instancetype)initWithDictionary:(NSDictionary<CMIOExtensionProperty, CMIOExtensionPropertyState *> *)propertiesDictionary NS_DESIGNATED_INITIALIZER;

/*!
@property activeFormatIndex
@abstract
 The active format index.
@discussion
 The property key is CMIOExtensionPropertyStreamActiveFormatIndex.
*/
@property(atomic, strong, nullable) NSNumber *activeFormatIndex NS_REFINED_FOR_SWIFT;

/*!
@property frameDuration
@abstract
 The frame duration.
@discussion
 The property key is CMIOExtensionPropertyStreamFrameDuration.
 The dictionary needs to be a dictionary representing a CMTime struct that is consistent with the frame duration specification provided by the current active format.
*/
@property(atomic, strong, nullable) NSDictionary *frameDuration NS_REFINED_FOR_SWIFT;

/*!
@property maxFrameDuration
@abstract
 The maximum frame duration.
@discussion
 The property key is CMIOExtensionPropertyStreamMaxFrameDuration.
 The dictionary needs to be a dictionary representing a CMTime struct that is consistent with the frame duration specification provided by the current active format.
*/
@property(atomic, strong, nullable) NSDictionary *maxFrameDuration NS_REFINED_FOR_SWIFT;

/*!
@property sinkBufferQueueSize
@abstract
 The sink stream property buffer queue size.
@discussion
 The property key is CMIOExtensionPropertyStreamSinkBufferQueueSize.
*/
@property(atomic, strong, nullable) NSNumber *sinkBufferQueueSize NS_REFINED_FOR_SWIFT;

/*!
@property sinkBuffersRequiredForStartup
@abstract
 The sink stream property for number of buffers required for startup.
@discussion
 The property key is CMIOExtensionPropertyStreamSinkBuffersRequiredForStartup.
*/
@property(atomic, strong, nullable) NSNumber *sinkBuffersRequiredForStartup NS_REFINED_FOR_SWIFT;

/*!
@property sinkBufferUnderrunCount
@abstract
 The sink stream property buffer underrun count.
@discussion
 The property key is CMIOExtensionPropertyStreamSinkBufferUnderrunCount.
*/
@property(atomic, strong, nullable) NSNumber *sinkBufferUnderrunCount NS_REFINED_FOR_SWIFT;

/*!
@property sinkEndOfData
@abstract
 The sink stream property end of data.
@discussion
 The property key is CMIOExtensionPropertyStreamSinkEndOfData.
*/
@property(atomic, strong, nullable) NSNumber *sinkEndOfData NS_REFINED_FOR_SWIFT;

/*!
@property setPropertyState:forProperty:
@abstract
 Set the property value.
@param propertyState
 The property state.
@param property
 The property key.
@discussion
 Setting nil to propertyState does remove the property.
*/
- (void)setPropertyState:(nullable CMIOExtensionPropertyState *)propertyState forProperty:(CMIOExtensionProperty)property;

/*!
@property propertiesDictionary
@abstract
 The dictionary of properties.
@discussion
 The dictionary containing all keys and values.
*/
@property(atomic, copy) NSDictionary<CMIOExtensionProperty, CMIOExtensionPropertyState *> *propertiesDictionary;

@end


API_AVAILABLE(macos(12.3))
@protocol CMIOExtensionStreamSource <NSObject>
@required

/*!
@property formats
@abstract
 The supported formats for the stream.
@discussion
 formats should not change during the life cycle of the associated stream.
*/
@property(atomic, readonly) NSArray<CMIOExtensionStreamFormat *> *formats;

/*!
@property availableProperties
@abstract
 The set of available properties.
@discussion
 The availableProperties should not change during the life cycle of the associated stream.
*/
@property(atomic, readonly, copy) NSSet<CMIOExtensionProperty> *availableProperties;

/*!
@method streamPropertiesForProperties:error:
@abstract
 Get the state of properties.
@param properties
 The addresses of properties from which to get the state.
@param outError
 An error return on failure.
@result
 A stream properties instance containing the properties states.
*/
- (nullable CMIOExtensionStreamProperties *)streamPropertiesForProperties:(NSSet<CMIOExtensionProperty> *)properties error:(NSError * _Nullable *)outError;

/*!
@method setStreamProperties:error:
@abstract
 Set the provider properties.
@param streamProperties
 The stream properties instance containing the properties states.
@param outError
 An error return on failure.
@result
 Return YES on success, NO otherwise.
@discussion
 The property attributes associated with a property state are always nil in setter.
 In case of error, it is highly advisable to pass more detailed information regarding the property or properties that failed in the localizedDescription of the NSError.
*/
- (BOOL)setStreamProperties:(CMIOExtensionStreamProperties *)streamProperties error:(NSError * _Nullable *)outError;

/*!
@method authorizedToStartStreamForClient:
@abstract
 Accept or reject streaming for a client.
@param client
 The client.
@result
 Return YES to accept streaming to a client, NO otherwise.
*/
- (BOOL)authorizedToStartStreamForClient:(CMIOExtensionClient *)client;

/*!
@method startStreamAndReturnError:
@abstract
 Start streaming media.
@param outError
 An error return on failure.
@result
 Return YES on success, NO otherwise.
*/
- (BOOL)startStreamAndReturnError:(NSError * _Nullable *)outError;

/*!
@method stopStreamAndReturnError:
@abstract
 Stop streaming media.
@param outError
 An error return on failure.
@result
 Return YES on success, NO otherwise.
*/
- (BOOL)stopStreamAndReturnError:(NSError * _Nullable *)outError;

@end

/*!
@class CMIOExtensionStream
@abstract
 A CMIOExtensionStream describes a stream of media data.
*/
API_AVAILABLE(macos(12.3))
@interface CMIOExtensionStream : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
@method streamWithLocalizedName:streamID:direction:clockType:source:
@abstract
 Returns a stream instance.
@param localizedName
 The localized name of the stream.
@param streamID
 The stream identifier.
@param direction
 The stream direction.
@param clockType
 The stream clock type.
@param source
 The stream source.
@result
 A CMIOExtensionStream instance that provides data.
@discussion
 Note that the clockType parameter may not be CMIOExtensionStreamClockTypeCustom; that value is reserved for streams created with a custom clock configuration. For streams that have a custom clock, use streamWithLocalizedName:streamID:direction:customClockConfiguration:source:.
*/
+ (instancetype)streamWithLocalizedName:(NSString *)localizedName streamID:(NSUUID *)streamID direction:(CMIOExtensionStreamDirection)direction clockType:(CMIOExtensionStreamClockType)clockType source:(id<CMIOExtensionStreamSource>)source;

/*!
@method streamWithLocalizedName:streamID:direction:customClockConfiguration:source:
@abstract
 Returns a stream instance.
@param localizedName
 The localized name of the stream.
@param streamID
 The stream identifier.
@param direction
 The stream direction.
@param customClockConfiguration
 A CMIOExtensionStreamCustomClockConfiguration object that defines the custom clock configuration.
@param source
 The stream source.
@result
 A CMIOExtensionStream instance that provides data.
*/
+ (instancetype)streamWithLocalizedName:(NSString *)localizedName streamID:(NSUUID *)streamID direction:(CMIOExtensionStreamDirection)direction customClockConfiguration:(CMIOExtensionStreamCustomClockConfiguration *)customClockConfiguration source:(id<CMIOExtensionStreamSource>)source;

/*!
@method initWithLocalizedName:streamID:direction:clockType:source:
@abstract
 Initialize a stream instance.
@param localizedName
 The localized name of the stream.
@param streamID
 The stream identifier.
@param direction
 The stream direction.
@param clockType
 The stream clock type.
@param source
 The stream source.
@result
 A CMIOExtensionStream instance that provides data.
@discussion
 Note that the clockType parameter may not be CMIOExtensionStreamClockTypeCustom; that value is reserved for streams created with a custom clock configuration. For streams that have a custom clock, use streamWithLocalizedName:streamID:direction:customClockConfiguration:source:.
*/
- (instancetype)initWithLocalizedName:(NSString *)localizedName streamID:(NSUUID *)streamID direction:(CMIOExtensionStreamDirection)direction clockType:(CMIOExtensionStreamClockType)clockType source:(id<CMIOExtensionStreamSource>)source;

/*!
@method initWithLocalizedName:streamID:direction:clockType:source:
@abstract
 Initialize a stream instance.
@param localizedName
 The localized name of the stream.
@param streamID
 The stream identifier.
@param direction
 The stream direction.
@param customClockConfiguration
 A CMIOExtensionStreamCustomClockConfiguration object that defines the custom clock configuration.
@param source
 The stream source.
@result
 A CMIOExtensionStream instance that provides data.
*/

- (instancetype)initWithLocalizedName:(NSString *)localizedName streamID:(NSUUID *)streamID direction:(CMIOExtensionStreamDirection)direction customClockConfiguration:(CMIOExtensionStreamCustomClockConfiguration *)customClockConfiguration source:(id<CMIOExtensionStreamSource>)source;

/*!
@property localizedName
@abstract
 The localized name of the stream.
*/
@property(atomic, readonly, copy) NSString *localizedName;

/*!
@property streamID
@abstract
 The stream identifier.
*/
@property(atomic, readonly, copy) NSUUID *streamID;

/*!
@property direction
@abstract
 The stream direction.
*/
@property(atomic, readonly) CMIOExtensionStreamDirection direction;

/*!
@property clockType
@abstract
 The stream clock type.
@discussion
 If the stream was specified with a custom clock configuration, the returned value will be CMIOExtensionStreamClockTypeCustom.
*/
@property(atomic, readonly) CMIOExtensionStreamClockType clockType;

/*!
@property customClockConfiguration
@abstract
 Custom clock configuration.
@discussion
 If the stream was specified using a clockType, the returned value will be nil.
*/
@property(atomic, readonly, strong, nullable) CMIOExtensionStreamCustomClockConfiguration *customClockConfiguration;

/*!
@property source
@abstract
 The stream source.
*/
@property(atomic, readonly, weak) id<CMIOExtensionStreamSource> source;

/*!
@property streamingClients
@abstract
 The array of streaming clients.
@discussion
 This property is key-value observable.
*/
@property(atomic, readonly, copy) NSArray<CMIOExtensionClient *> *streamingClients;

/*!
@method notifyPropertiesChanged:
@abstract
 Notify client(s) of stream properties changes.
@param propertyStates
 The dictionary of properties having changed.
*/
- (void)notifyPropertiesChanged:(NSDictionary<CMIOExtensionProperty, CMIOExtensionPropertyState *> *)propertyStates;

/*!
@method sendSampleBuffer:discontinuity:hostTimeInNanoseconds:
@abstract
 Send media sample to client(s).
@param sampleBuffer
 The sample buffer containing media data.
@param discontinuity
 The discontinuity flag indicating if the sample buffer represents a discontinuity boundary.
@param hostTimeInNanoseconds
 The host time in nanoseconds when the buffer was captured.
@discussion
 The sample will be deliver to clients whose media type authorization status is authorized.
 The sample buffer timestamps should be relative to the clock timebase specified with clockType.
 Attempting to send a sample buffer on a sink stream will throw an exception.
*/
- (void)sendSampleBuffer:(CMSampleBufferRef)sampleBuffer discontinuity:(CMIOExtensionStreamDiscontinuityFlags)discontinuity hostTimeInNanoseconds:(uint64_t)hostTimeInNanoseconds;

/*!
@method consumeSampleBufferFromClient:completionHandler:
@abstract
 Consume a sample buffer from a client.
@param client
 The client.
@param completionHandler
 A block that will be called when the operation is completed.
 If the capture request is successful, the "sampleBuffer" parameter contains a valid CMSampleBuffer, the "sampleBufferSequenceNumber" parameter is the sample buffer sequence number,
 the "discontinuity" parameter is the discontinuity flag, the "hasMoreSampleBuffers" parameter indicates whether or not more sample buffers are available, the "error" parameter is nil.
*/
- (void)consumeSampleBufferFromClient:(CMIOExtensionClient *)client completionHandler:(void (^)(CMSampleBufferRef _Nullable sampleBuffer, uint64_t sampleBufferSequenceNumber, CMIOExtensionStreamDiscontinuityFlags discontinuity, BOOL hasMoreSampleBuffers, NSError * _Nullable error))completionHandler;

/*!
@method notifyScheduledOutputChanged:
@abstract
 Notify client(s) when a particular buffer was output.
@param scheduledOutput
 The stream scheduled output.
*/
- (void)notifyScheduledOutputChanged:(CMIOExtensionScheduledOutput *)scheduledOutput;

@end

NS_ASSUME_NONNULL_END
