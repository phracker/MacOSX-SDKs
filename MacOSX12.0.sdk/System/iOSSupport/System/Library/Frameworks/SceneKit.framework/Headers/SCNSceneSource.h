//
//  SCNSceneSource.h
//  SceneKit
//
//  Copyright © 2012-2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class SCNScene;

/*! @group Scene source properties */
/*! File contributors. The values are dictionaries populated with keys documented in the "Contributor dictionary keys" group. */
SCN_EXPORT NSString * const SCNSceneSourceAssetContributorsKey;
/*! When the file was created. The value is a NSDate instance. */
SCN_EXPORT NSString * const SCNSceneSourceAssetCreatedDateKey;
/*! When the file was last modified. The value is a NSDate instance. */
SCN_EXPORT NSString * const SCNSceneSourceAssetModifiedDateKey;
/*! The up axis of the file. If the file is oriented Y-up, for example, then this is the string \@"0.0 1.0 0.0" */
SCN_EXPORT NSString * const SCNSceneSourceAssetUpAxisKey;
/*! The unit used in the file. The value is a dictionary populated with keys documented in the "Unit dictionary keys" group. */
SCN_EXPORT NSString * const SCNSceneSourceAssetUnitKey;

/*! @group Contributor dictionary keys */
/*! Authoring tool used to create the file. The corresponding value is an NSString. */
SCN_EXPORT NSString * const SCNSceneSourceAssetAuthoringToolKey;
/*! The file's author. The corresponding value is an NSString. */
SCN_EXPORT NSString * const SCNSceneSourceAssetAuthorKey;

/*! @group Unit dictionary keys */
/*! The name (NSString) of the unit */
SCN_EXPORT NSString * const SCNSceneSourceAssetUnitNameKey;
/*! A NSNumber encapsulating a floating-point value indicating how many meters the unit is. For example, if the name is \@"centimeter", then this will be 0.01. */
SCN_EXPORT NSString * const SCNSceneSourceAssetUnitMeterKey;

/*! @group Scene loading options */
typedef NSString * SCNSceneSourceLoadingOption NS_STRING_ENUM;

/*! @constant SCNSceneSourceCreateNormalsIfAbsentKey
	@abstract Enable to try to guess acceptable normals for the vertices if none are given in the file
    @discussion Use this with a boolean value encapsulated in a NSNumber. The default value is NO.
 */
SCN_EXPORT SCNSceneSourceLoadingOption const SCNSceneSourceCreateNormalsIfAbsentKey;

/*!
 @constant SCNSceneSourceCheckConsistencyKey
 @abstract Pass YES in order to perform the document validation. 
 @discussion This option can be set in the options dictionary of the SCNScene and SCNSceneSource loading methods.
 The value for this option should be a boolean NSNumber. If its boolean value is YES (the default is NO),
 SceneKit will attempt to check the document for consistency.
 If the document doesn't pass the consistency check it is then not loaded and an error is returned.
 This is slower, but for security reasons it should be set to YES if you are not sure the files you load are valid and have not been tampered with. 
 */
SCN_EXPORT SCNSceneSourceLoadingOption const SCNSceneSourceCheckConsistencyKey;

/*!
 @constant SCNSceneSourceFlattenSceneKey
 @abstract Pass YES to flatten the scene graph when possible.
 @discussion This option can be set in the options dictionary of the SCNScene and SCNSceneSource loading methods.
 The value for this option should be a boolean NSNumber. If its boolean value is YES (the default is NO),
 SceneKit will attempt to reduce the scene graph by merging the geometries.
 This option is suitable to preview a 3D scene efficiently and when manipulating the scene graph is not needed.
 */
SCN_EXPORT SCNSceneSourceLoadingOption const SCNSceneSourceFlattenSceneKey;

/*!
 @constant SCNSceneSourceUseSafeModeKey
 @abstract Pass YES in order to enable the safe mode.
 @discussion This option can be set in the options dictionary of the SCNScene and SCNSceneSource loading methods.
 The value for this option should be a boolean NSNumber. If its boolean value is YES (the default is NO),
 SceneKit will forbid network accesses, prevent the loading of resources from arbitrary directories, and will not execute
 any code present in the loaded files.
 */
SCN_EXPORT SCNSceneSourceLoadingOption const SCNSceneSourceUseSafeModeKey API_DEPRECATED("No longer supported", macos(10.8, 10.13), ios(8.0, 11.0), tvos(9.0, 11.0), watchos(3.0, 4.0));

/*!
 @constant SCNSceneSourceAssetDirectoryURLsKey
 @abstract Pass an array of directory URLs where SceneKit should look for resources
 @discussion By default, SceneKit will look for the external resources it cannot find in the parent directory of the imported file.
 You can add additional directories by setting an array of URLs for this key when calling sceneWithOptions:error:.
 This is recommended if you want to construct your scene source from a data object, not from an URL,
 and need to load resources whose paths are not absolute.
 */
SCN_EXPORT SCNSceneSourceLoadingOption const SCNSceneSourceAssetDirectoryURLsKey;

/*!
 @constant SCNSceneSourceOverrideAssetURLsKey
 @abstract Pass YES in order to override assets URLs with the directory URLs passed via SCNSceneSourceAssetDirectoryURLsKey.
 @discussion By default, SceneKit will look for the external resources using the paths/urls as described in the imported file.
 You can force SceneKit to only search for extern resources within the directories specified by the SCNSceneSourceAssetDirectoryURLsKey key.
 This can be useful to load a file and its resources from a specific bundle for instance.
 */
SCN_EXPORT SCNSceneSourceLoadingOption const SCNSceneSourceOverrideAssetURLsKey;

/*!
 @constant SCNSceneSourceStrictConformanceKey
 @abstract Pass YES to interpret the 3D format of the file in a strict way.
 @discussion This option defaults to NO. In this case SceneKit will try to read any additional metadata present in the file to
			 enable additional features and make the rendering as close as possible to the original intent. If you pass YES,
             SceneKit will instead only consider features which are part of the file format specification.
 */
SCN_EXPORT SCNSceneSourceLoadingOption const SCNSceneSourceStrictConformanceKey;

/*!
 @constant SCNSceneSourceConvertUnitsToMetersKey
 @abstract Pass the units you want the scene to be converted to (in meter).
 @discussion Use this with a floating value encapsulated in a NSNumber. The default value is nil which means no conversion done. Passing a non-zero value will convert the scene coordinates so that 1 unit corresponds to N meters. For example pass 0.01 for 1 unit == 1 centimeter, pass 0.3048 for 1 unit == 1 foot...
     For better physics simulation it is recommended to use 1 unit equals to 1 meter.
     This option has no effect for SCN files or if the asset is already compressed by Xcode (use the compression options instead).
 */
SCN_EXPORT SCNSceneSourceLoadingOption const SCNSceneSourceConvertUnitsToMetersKey API_AVAILABLE(macos(10.10), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @constant SCNSceneSourceConvertToYUpKey
 @abstract Pass YES if a scene should be converted to Y up if it currently has a different up axis.
 @discussion Use this with a boolean value encapsulated in a NSNumber. The default value is NO.
 This option has no effect for SCN files or if the asset is already compressed by Xcode (use the compression options instead).
 */
SCN_EXPORT SCNSceneSourceLoadingOption const SCNSceneSourceConvertToYUpKey API_AVAILABLE(macos(10.10), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @constant SCNSceneSourceAnimationImportPolicyKey
 @abstract Pass one of the value below to specify what to do with loaded animations.
 @discussion See below for the description of each individual key. Defaults to SCNSceneSourceAnimationImportPolicyPlayRepeatedly. On 10.9 and before the behavior is SCNSceneSourceAnimationImportPolicyPlayUsingSceneTimeBase. For compatibility reason if the application was built on 10.9 or before the default behavior is SCNSceneSourceAnimationImportPolicyPlayUsingSceneTimeBase.
 */
SCN_EXPORT SCNSceneSourceLoadingOption const SCNSceneSourceAnimationImportPolicyKey API_AVAILABLE(macos(10.10));

/*!
 @constant SCNSceneSourceLoadingOptionPreserveOriginalTopology
 @abstract Pass YES to make SceneKit preserve the original topology instead of triangulating at load time. This can be useful to get better results when subdividing a geometry.
 @discussion Defaults to YES starting macOS 10.15, iOS 13, tvOS 13 and watchOS 6. Defaults to NO in previous versions.
 */
SCN_EXPORT SCNSceneSourceLoadingOption const SCNSceneSourceLoadingOptionPreserveOriginalTopology API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));

#define SCNSceneSourceLoadingOptionCreateNormalsIfAbsent    SCNSceneSourceCreateNormalsIfAbsentKey
#define SCNSceneSourceLoadingOptionCheckConsistency         SCNSceneSourceCheckConsistencyKey
#define SCNSceneSourceLoadingOptionFlattenScene             SCNSceneSourceFlattenSceneKey
#define SCNSceneSourceLoadingOptionUseSafeMode              SCNSceneSourceUseSafeModeKey
#define SCNSceneSourceLoadingOptionAssetDirectoryURLs       SCNSceneSourceAssetDirectoryURLsKey
#define SCNSceneSourceLoadingOptionOverrideAssetURLs        SCNSceneSourceOverrideAssetURLsKey
#define SCNSceneSourceLoadingOptionStrictConformance        SCNSceneSourceStrictConformanceKey
#define SCNSceneSourceLoadingOptionConvertUnitsToMeters     SCNSceneSourceConvertUnitsToMetersKey
#define SCNSceneSourceLoadingOptionConvertToYUp             SCNSceneSourceConvertToYUpKey
#define SCNSceneSourceLoadingOptionAnimationImportPolicy    SCNSceneSourceAnimationImportPolicyKey

/* Values for SCNSceneSourceLoadingOptionAnimationImportPolicy */
typedef NSString * SCNSceneSourceAnimationImportPolicy NS_STRING_ENUM;

/*!
 @constant SCNSceneSourceAnimationImportPolicyPlay
 @abstract Add animations to the scene and play them once (repeatCount set to 1).
 */
SCN_EXPORT SCNSceneSourceAnimationImportPolicy const SCNSceneSourceAnimationImportPolicyPlay API_AVAILABLE(macos(10.10));

/*!
 @constant SCNSceneSourceAnimationImportPolicyPlayRepeatedly
 @abstract Add animations to the scene and play them repeatedly (repeatCount set to infinity).
 */
SCN_EXPORT SCNSceneSourceAnimationImportPolicy const SCNSceneSourceAnimationImportPolicyPlayRepeatedly API_AVAILABLE(macos(10.10));

/*!
 @constant SCNSceneSourceAnimationImportPolicyDoNotPlay
 @abstract Only keep animations in the SCNSceneSource and don't add to the animatable elements of the scene.
 */
SCN_EXPORT SCNSceneSourceAnimationImportPolicy const SCNSceneSourceAnimationImportPolicyDoNotPlay API_AVAILABLE(macos(10.10));

/*!
 @constant SCNSceneSourceAnimationImportPolicyPlayUsingSceneTimeBase
 @abstract Add animations to the scene and play them using the SCNView/SCNRenderer's scene time (usesSceneTimeBase set to YES)
 */
SCN_EXPORT SCNSceneSourceAnimationImportPolicy const SCNSceneSourceAnimationImportPolicyPlayUsingSceneTimeBase API_AVAILABLE(macos(10.10));


/*!
 @constant SCNDetailedErrorsKey
 @abstract Key to access the detailed validation errors.
 @discussion This key will be present in the user info dictionary of errors created by the various sceneWithOptions: methods.
             When present, the value associated with it is an array of detailed errors found by the consistency checker
             which represent consistency errors in the 3D file. Some metadata about these detailed errors is available
             in their user info dictionary using the other keys (SCNConsistency*) defined in this file.
 */

SCN_EXPORT NSString * const SCNDetailedErrorsKey;

/*!
 @constant SCNConsistencyElementIDErrorKey
 @abstract For XML-based formats, the ID of the element where the error occurred.
 @discussion When the element does not have an ID, the ID of the closest parent element which has one is returned.
 */

SCN_EXPORT NSString * const SCNConsistencyElementIDErrorKey;

/*!
 @constant SCNConsistencyElementTypeErrorKey
 @abstract For XML-based formats, the tag name of the element where the error occurred.
 */

SCN_EXPORT NSString * const SCNConsistencyElementTypeErrorKey;

/*!
 @constant SCNConsistencyLineNumberErrorKey
 @abstract For text-based formats, the line number where an error occurred.
 */

SCN_EXPORT NSString * const SCNConsistencyLineNumberErrorKey;

/*!
 @enum SCNConsistencyErrorCode
 @abstract Error codes returned by the consistency checker
 @discussion Each of the detailed errors found in the master error's SCNDetailedErrorsKey, when present, will have an error
             code in this enumeration and some additional metadata associated with the SCNConsistency* keys.
 */
enum {
	SCNConsistencyInvalidURIError = 1000,
	SCNConsistencyInvalidCountError,
	SCNConsistencyInvalidArgumentError,
	SCNConsistencyMissingElementError,
	SCNConsistencyMissingAttributeError,
	SCNConsistencyXMLSchemaValidationError,
};

/*!
 @enum SCNSceneSourceStatus
 @abstract Represents a phase of the loading process.
 @discussion Each of these constants (except SCNSceneSourceStatusError) represents a phase of the loading process. "Parsing" means that the document is being deserialized, "validating" that it's being checked for consistency, "processing" that the resulting object is being loaded. New values might be added to this enumeration to make it more detailed; however the values will always be ordered in the same order as the corresponding phases are executed.
 */
typedef NS_ENUM(NSInteger, SCNSceneSourceStatus) {
	SCNSceneSourceStatusError      = -1,
	SCNSceneSourceStatusParsing    = 4,
	SCNSceneSourceStatusValidating = 8,
	SCNSceneSourceStatusProcessing = 12,
	SCNSceneSourceStatusComplete   = 16
};

typedef void (^SCNSceneSourceStatusHandler)(float totalProgress, SCNSceneSourceStatus status, NSError * _Nullable error, BOOL *stop);


/*!
 @class SCNSceneSource
 @abstract SCNSceneSource objects, abstract the data-reading task. A scene source can read scene data from a URL or a NSData object.
 After creating a SCNSceneSource object for the appropriate source, you can obtain scenes using SCNSceneSource methods.
 */

SCN_EXPORT
@interface SCNSceneSource : NSObject 

/*!
 @method sceneSourceWithURL:options:
 @abstract Creates and initialize a SCNSceneSource instance.
 @param url The URL to read scenes from.
 @param options An optional dictionary for future extensions. 
 */
+ (nullable instancetype)sceneSourceWithURL:(NSURL *)url options:(nullable NSDictionary<SCNSceneSourceLoadingOption, id> *)options;

/*!
 @method sceneSourceWithData:options:
 @abstract Creates and initialize a SCNSceneSource instance.
 @param data The scene data.
 @param options An optional dictionary for future extensions. 
 */
+ (nullable instancetype)sceneSourceWithData:(NSData *)data options:(nullable NSDictionary<SCNSceneSourceLoadingOption, id> *)options;

/*!
 @method initWithURL:options:
 @abstract Initialize a SCNSceneSource instance from a URL.
 @param url The URL to read scenes from.
 @param options An optional dictionary for future extensions. 
 */
- (nullable instancetype)initWithURL:(NSURL *)url options:(nullable NSDictionary<SCNSceneSourceLoadingOption, id> *)options;

/*!
 @method initWithData:options:
 @abstract Initialize a SCNSceneSource instance from a NSData object.
 @param data The data to read scenes from.
 @param options An optional dictionary for future extensions. 
 */
- (nullable instancetype)initWithData:(NSData *)data options:(nullable NSDictionary<SCNSceneSourceLoadingOption, id> *)options;

/*!
 @property url
 @abstract The receiver's URL (if any).
 */
@property(readonly, nullable) NSURL *url;

/*!
 @property data
 @abstract The receiver's data (if any).
 */
@property(readonly, nullable) NSData *data;

/*!
 @method sceneWithOptions:statusHandler:
 @abstract Creates and initializes the scene described in the 3D file with the specified options and lets you monitor the progress.
 @param options A dictionary of options. The valid keys are described in the "Scene loading options" section.
 @param statusHandler This block will be called repeatedly while the scene is being loaded.
                      - The first argument, overallProgress, is a floating-point number between 0 and 1. 0 means the loading process has just started and 1 that it is complete.
					  - The second argument, status, tells you what the source is currently doing. It takes one of the values in the SCNSceneSourceStatus enum. New values might be added to this enum in the future.
					  - If status == SCNSceneStatusError, then error will contain more information about the failure, and the method will return nil after having called the block. Otherwise error will be nil.
					  - Set *stop to YES if you want the source to abort the loading operation.
 */
- (nullable SCNScene *)sceneWithOptions:(nullable NSDictionary<SCNSceneSourceLoadingOption, id> *)options statusHandler:(nullable SCNSceneSourceStatusHandler)statusHandler;

/*!
 @method sceneWithOptions:error:
 @abstract Creates and initializes the scene described in the 3D file with the specified options.
 @param options A dictionary of options. The valid keys are described in the "Scene loading options" section.
 @param error If this method returns nil, an error providing more information is returned by reference.
 @discussion This simpler version is equivalent to providing a block to sceneWithOptions:statusHandler: and checking the "error"
 parameter of the block if the status is SCNSceneStatusError.
 */
- (nullable SCNScene *)sceneWithOptions:(nullable NSDictionary<SCNSceneSourceLoadingOption, id> *)options error:(NSError **)error;

/*!
 @method propertyForKey:
 @param key The key for which to return the corresponding property.
 @abstract Returns the property as defined in the 3D file for the given key. See keys above.
 */
- (nullable id)propertyForKey:(NSString *)key;

/*!
 @method entryWithIdentifier:classType:
 @abstract Returns the instance of "entryClass" found in the receiver's library with the id "uid".
 @param uid The id of the entry to find as specified in the source file
 @param entryClass Specifies the type of the object to be returned. It can be one of the following classes: SCNMaterial, SCNGeometry, SCNScene, SCNNode, CAAnimation, SCNLight, SCNCamera, SCNSkinner, SCNMorpher, NSImage
 @discussion Returns NULL if the receiver's library doesn't contains such an uid for the specified type.
 */
- (nullable id)entryWithIdentifier:(NSString *)uid withClass:(Class)entryClass NS_REFINED_FOR_SWIFT;

/*!
 @method identifiersOfEntriesWithClass:
 @abstract Returns the IDs found in the receiver's library for the class "entryClass".
 @param entryClass Specifies the type of the object referenced by the returned IDs. It can be one of the following classes: SCNMaterial, SCNScene, SCNGeometry, SCNNode, CAAnimation, SCNLight, SCNCamera, SCNSkinner, SCNMorpher, NSImage
 */
- (NSArray<NSString *> *)identifiersOfEntriesWithClass:(Class)entryClass;

/*!
 @method entriesPassingTest:
 @abstract Returns the entries in the receiver's library that pass a test in a given Block.
 @param predicate The block to apply to entries in the library. The block takes three arguments: "entry" is an entry in the library, "identifier" is the ID of this entry and "stop" is a reference to a Boolean value. The block can set the value to YES to stop further processing of the library. The stop argument is an out-only argument. You should only ever set this Boolean to YES within the Block. The Block returns a Boolean value that indicates whether "entry" passed the test.
 @discussion The entry is an instance of one of following classes: SCNMaterial, SCNScene, SCNGeometry, SCNNode, CAAnimation, SCNLight, SCNCamera, SCNSkinner, SCNMorpher, NSImage.
 */
- (NSArray<id> *)entriesPassingTest:(NS_NOESCAPE BOOL (^)(id entry, NSString *identifier, BOOL *stop))predicate API_AVAILABLE(macos(10.9));

@end

NS_ASSUME_NONNULL_END
