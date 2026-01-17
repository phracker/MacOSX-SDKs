//
//  PHASEAssetRegistry.h
//  PHASE
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#ifndef PHASEAssetRegistry_h
#define PHASEAssetRegistry_h

#import <CoreAudioTypes/CoreAudioTypes.h>
#import <AVFAudio/AVAudioFormat.h>
#import <PHASE/PHASESoundEventNodes.h>
#import <PHASE/PHASETypes.h>

NS_ASSUME_NONNULL_BEGIN

@class PHASEMetaParameter;

#pragma mark - PHASEAsset

/**************************************************************************************************/
/*!
    @interface PHASEAsset
    @abstract An object that represents a registered asset in the asset registry.
 */
OS_EXPORT API_AVAILABLE(macos(12.0), ios(15.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface PHASEAsset : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
    @property identifier
    @abstract The identifier that uniquely represents this asset.
*/
@property(readonly) NSString* identifier;

@end

#pragma mark - PHASESoundAsset

/****************************************************************************************************/
/*!
    @interface PHASESoundAsset
    @abstract An object that represents a registered sound asset in the asset registry.
 */
OS_EXPORT API_AVAILABLE(macos(12.0), ios(15.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface PHASESoundAsset : PHASEAsset

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
    @property url
    @abstract The URL of the sound asset, if applicable.
*/
@property(readonly, nullable) NSURL* url;

/*!
    @property data
    @abstract The buffer for the sound asset, if applicable.
*/
@property(readonly, nullable) NSData* data;

/*!
    @property type
    @abstract The sound asset type.
*/
@property(readonly) PHASEAssetType type;

@end

#pragma mark - PHASESoundEventNodeAsset

/****************************************************************************************************/
/*!
    @interface PHASESoundEventNodeAsset
    @abstract An object that represents a registered sound event asset in the asset registry.
 */
OS_EXPORT API_AVAILABLE(macos(12.0), ios(15.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface PHASESoundEventNodeAsset : PHASEAsset

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

#pragma mark - PHASEGlobalMetaParameterAsset

/****************************************************************************************************/
/*!
    @interface PHASEGlobalMetaParameterAsset
    @abstract An object that represents a registered global metaparameter asset in the asset registry.
 */
OS_EXPORT API_AVAILABLE(macos(12.0), ios(15.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface PHASEGlobalMetaParameterAsset : PHASEAsset

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

#pragma mark - PHASEAssetRegistry

/****************************************************************************************************/
/*!
    @interface PHASEAssetRegistry
    @abstract Asset registry
 */
OS_EXPORT API_AVAILABLE(macos(12.0), ios(15.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface PHASEAssetRegistry : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
    @method registerGlobalMetaParameter:error
    @abstract Register a global metaparameter with the asset registry.
    @note
        This function is synchronous and thread-safe.
        Clients can safely run this function to register multiple global metaparameters from multiple threads, if required.
    @param metaParameterDefinition
        The metaparameter object to register.
    @param error
        The error object in case of an error.
    @return
        A PHASEGlobalMetaParameterAsset object.
*/
- (nullable PHASEGlobalMetaParameterAsset*)registerGlobalMetaParameter:(PHASEMetaParameterDefinition*)metaParameterDefinition
                                                              error:(NSError**)error
NS_SWIFT_NAME(registerGlobalMetaParameter(metaParameterDefinition:));


/*!
    @method registerSoundEventAssetWithRootNode:identifier:error
    @abstract Register a sound event asset with the asset registry.
    @note
        This function is synchronous and thread-safe.
        Clients can safely run this function to register multiple sound event assets from multiple threads, if required.
    @param rootNode
        The root node of the sound event asset to register.
    @param identifier
        An identifier that uniquely represents this sound event asset. Nil generates an automatic identifier.
    @param error
        The error object in case of an error
    @return
        A PHASESoundEventNodeAsset object
*/
- (nullable PHASESoundEventNodeAsset*)registerSoundEventAssetWithRootNode:(PHASESoundEventNodeDefinition*)rootNode
                                                               identifier:(nullable NSString*)identifier
                                                                    error:(NSError**)error
NS_SWIFT_NAME(registerSoundEventAsset(rootNode:identifier:));

/*!
    @method registerSoundAssetAtURL:identifier:assetType:channelLayout:normalizationMode:error
    @abstract Register an audio file as a sound asset in the system.
    @note
        This function is synchronous and thread-safe.
        Clients can safely run this function to register multiple sound assets from multiple threads, if required.
    @param url
        The URL of the audio file.
    @param identifier
        An identifier that uniquely represents this sound event asset. Nil generates an automatic identifier.
    @param assetType
        The asset type for this sound asset.
    @param channelLayout
        The audio channel layout for this sound asset.
        If a valid channel layout definition is read from the file being registered, this will override it.
        If nil is passed as a value for this property, the file must either be mono or stereo, or already contain a vaild channel layout definition.
        This channel layout must have the same channel count as the audio file being loaded.
    @param normalizationMode
        The normalization mode.
    @param error
        The error object in case of an error
    @return
        A PHASESoundAsset object
*/
- (nullable PHASESoundAsset*)registerSoundAssetAtURL:(NSURL*)url
                                          identifier:(nullable NSString*)identifier
                                           assetType:(PHASEAssetType)assetType
                                       channelLayout:(nullable AVAudioChannelLayout*)channelLayout
                                   normalizationMode:(PHASENormalizationMode)normalizationMode
                                               error:(NSError**)error
NS_SWIFT_NAME(registerSoundAsset(url:identifier:assetType:channelLayout:normalizationMode:));

/*!
    @method registerSoundAssetWithData:identifier:format:normalizationMode:error
    @abstract Register audio data as a sound asset in the system.
    @note
        This function is synchronous and thread-safe.
        Clients can safely run this function to register multiple sound assets from multiple threads, if required.
    @param data
        A buffer containing the audio data to register as a sound asset.
        Audio data must either be a single PCM buffer of interleaved channels or multiple deinterleaved PCM buffers per channel packed back to back.
    @param identifier
        The identifier to assign to this sound asset. Nil generates an automatic identifier.
    @param format
        The AVAudioFormat object that describes the audio data in the buffer.
    @param normalizationMode
        The normalization mode.
    @param error
        The error object in case of an error.
    @return
        A PHASESoundAsset object.
*/
- (nullable PHASESoundAsset*)registerSoundAssetWithData:(NSData*)data
                                             identifier:(nullable NSString*)identifier
                                                 format:(AVAudioFormat*)format
                                      normalizationMode:(PHASENormalizationMode)normalizationMode
                                                  error:(NSError**)error
NS_SWIFT_NAME(registerSoundAsset(data:identifier:format:normalizationMode:));


/*!
    @method unregisterAssetWithIdentifier:completion:
    @abstract Unregister and unload an asset.
    @param identifier
        The identifier of the PHASEAsset object to unregister
    @param handler
        An optional completion block that will be called when the asset has been unregistered.
        Once you receive this callback, it's safe to deallocate external resources, if applicable.
*/
- (void)unregisterAssetWithIdentifier:(NSString*)identifier completion:(void (^_Nullable)(bool success))handler
NS_SWIFT_NAME(unregisterAsset(identifier:completion:));

/*!
    @method assetForIdentifier
    @abstract Finds an asset in the asset registry, given an identifier.
    @param identifier
        The identifier of this asset
    @return
        A PHASEAsset object, or nil if one could not be found.
*/
- (nullable PHASEAsset*)assetForIdentifier:(NSString*)identifier;

/*!
    @property globalMetaParameters
    @abstract A dictionary of global metaparameters
*/
@property(atomic, readonly, copy) NSDictionary<NSString*, PHASEMetaParameter*>* globalMetaParameters;

@end

NS_ASSUME_NONNULL_END

#endif /* PHASEAssetRegistry_h */
