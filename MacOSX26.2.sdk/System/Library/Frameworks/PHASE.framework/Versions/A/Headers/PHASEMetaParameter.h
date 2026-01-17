//
//  PHASEMetaParameter.h
//  PHASE
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#ifndef PHASEMetaParameter_h
#define PHASEMetaParameter_h

#import <PHASE/PHASEEnvelope.h>
#import <PHASE/PHASETypes.h>
#import <PHASE/PHASEDefinition.h>

NS_ASSUME_NONNULL_BEGIN

#pragma mark - PHASEMetaParameterDefinition

/****************************************************************************************************/
/*!
    @interface PHASEMetaParameterDefinition
    @abstract A base object for metaparameter definitions
 */
OS_EXPORT API_AVAILABLE(macos(12.0), ios(15.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface PHASEMetaParameterDefinition : PHASEDefinition

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
    @property value
    @abstract The value of the metaparameter.
*/
@property(nonatomic, readonly, strong) id value;

@end

#pragma mark - PHASENumberMetaParameterDefinition

/****************************************************************************************************/
/*!
    @interface PHASENumberMetaParameterDefinition
    @abstract A metaparameter that has a numeric value
 */
OS_EXPORT API_AVAILABLE(macos(12.0), ios(15.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface PHASENumberMetaParameterDefinition : PHASEMetaParameterDefinition

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
    @method initWithValue:identifier
    @abstract
        Create a new numeric metaparameter definition
    @param value
        The initial value of the metaparameter
    @param identifier
        An optional custom identifier to give to this object
    @return
        The new PHASENumberMetaParameterDefinition object
*/
- (instancetype)initWithValue:(double)value identifier:(NSString*)identifier;

/*!
    @method initWithValue
    @abstract
        Create a new numeric metaparameter definition
    @param value
        The initial value of the metaparameter
    @return
        The new PHASENumberMetaParameterDefinition object
*/
- (instancetype)initWithValue:(double)value;

/*!
    @method initWithValue:minimum:maximum:identifier
    @abstract
        Create a new numeric metaparameter definition and a predefined min and maximum range
    @param value
        The initial value of the metaparameter
    @param minimum
        The minimum value for this metaparameter.  Values set to this metaparamter less than the minimum will be clamped.
    @param maximum
        The maximum value for this metaparameter.  Values set to this metaparamter less than the minimum will be clamped.
    @param identifier
        An optional custom identifier to give to this object
    @return
        The new PHASENumberMetaParameterDefinition object
*/
- (instancetype)initWithValue:(double)value minimum:(double)minimum maximum:(double)maximum identifier:(NSString*)identifier;

/*!
    @method initWithValue:minimum:maximum
    @abstract
        Create a new numeric metaparameter definition and a predefined min and maximum range
    @param value
        The initial value of the metaparameter
    @param minimum
        The minimum value for this metaparameter.  Values set to this metaparamter less than the minimum will be clamped.
    @param maximum
        The maximum value for this metaparameter.  Values set to this metaparamter less than the minimum will be clamped.
    @return
        The new PHASENumberMetaParameterDefinition object
*/
- (instancetype)initWithValue:(double)value minimum:(double)minimum maximum:(double)maximum NS_DESIGNATED_INITIALIZER;


/*!
    @property minimum
    @abstract The readonly minimum that this metaparameter definition was initialized with
*/
@property(nonatomic, readonly) double minimum;

/*!
    @property maximum
    @abstract The readonly maximum that this metaparameter definition was initialized with
*/
@property(nonatomic, readonly) double maximum;

@end

#pragma mark - PHASEStringMetaParameterDefinition

/****************************************************************************************************/
/*!
    @interface PHASEStringMetaParameterDefinition
    @abstract A Metaparameter that has a string value
 */
OS_EXPORT API_AVAILABLE(macos(12.0), ios(15.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface PHASEStringMetaParameterDefinition : PHASEMetaParameterDefinition

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
    @method initWithValue:identifier
    @abstract
        Create a new string metaparameter definition
    @param value
        The initial value of the metaparameter
    @param identifier
        An optional custom identifier to give to this object
    @return
        The new PHASEStringMetaParameterDefinition object
*/
- (instancetype)initWithValue:(NSString*)value identifier:(NSString*)identifier;

/*!
    @method initWithValue
    @abstract
        Create a new string metaparameter definition
    @param value
        The initial value of the metaparameter
    @return
        The new PHASEStringMetaParameterDefinition object
*/
- (instancetype)initWithValue:(NSString*)value NS_DESIGNATED_INITIALIZER;

@end

#pragma mark - PHASEMappedMetaParameterDefinition

/****************************************************************************************************/
/*!
    @interface PHASEMappedMetaParameterDefinition
    @abstract An object to define a Mapped Metaparameter when building an sound event.
 */
OS_EXPORT API_AVAILABLE(macos(12.0), ios(15.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface PHASEMappedMetaParameterDefinition : PHASENumberMetaParameterDefinition

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

- (instancetype)initWithValue:(double)value identifier:(NSString*)identifier NS_UNAVAILABLE;

- (instancetype)initWithValue:(double)value NS_UNAVAILABLE;

- (instancetype)initWithValue:(double)value minimum:(double)minimum maximum:(double)maximum identifier:(NSString*)identifier NS_UNAVAILABLE;

- (instancetype)initWithValue:(double)value minimum:(double)minimum maximum:(double)maximum NS_UNAVAILABLE;

/*!
    @method initWithInputMetaParameterDefinition:identifier
    @abstract
        Create a new mapped range metaparameter definition
    @param inputMetaParameterDefinition
        The metaparameter that will provide an input for this mapped metaparameter
    @param envelope
        The envelope to use.
    @param identifier
        An optional custom identifier to give to this object
    @return
        The new PHASEMappedMetaParameterDefinition object
*/
- (instancetype)initWithInputMetaParameterDefinition:(PHASENumberMetaParameterDefinition*)inputMetaParameterDefinition
                                            envelope:(PHASEEnvelope*)envelope
                                          identifier:(NSString*)identifier;

/*!
    @method initWithInputMetaParameterDefinition
    @abstract
        Create a new mapped range metaparameter definition
    @param inputMetaParameterDefinition
        The metaparameter that will provide an input for this mapped metaparameter
    @param envelope
        The envelope to use.
    @return
        The new PHASEMappedMetaParameterDefinition object
*/
- (instancetype)initWithInputMetaParameterDefinition:(PHASENumberMetaParameterDefinition*)inputMetaParameterDefinition
                                            envelope:(PHASEEnvelope*)envelope NS_DESIGNATED_INITIALIZER;

/*!
    @property envelope
    @abstract An Envelope to define segments of curves
*/
@property(nonatomic, readonly, strong) PHASEEnvelope* envelope;

/*!
    @property inputMetaParameterDefinition
    @abstract The readonly PHASENumberMetaParameterDefinition that this metaparameter definition was initialized with
*/
@property(nonatomic, readonly, strong) PHASENumberMetaParameterDefinition* inputMetaParameterDefinition;

@property(nonatomic, readonly) double minimum NS_UNAVAILABLE;

@property(nonatomic, readonly) double maximum NS_UNAVAILABLE;

@end

#pragma mark - PHASEMetaParameter

/****************************************************************************************************/
/*!
    @interface PHASEMetaParameter
    @abstract A generic object that represents an active metaparameter in the system
 */
OS_EXPORT API_AVAILABLE(macos(12.0), ios(15.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface PHASEMetaParameter : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
    @property identifier
    @abstract The identifier that uniquely represents this metaparameter.
*/
@property(nonatomic, readonly, strong) NSString* identifier;

/*!
    @property value
    @abstract The value of this metaparameter
*/
@property(nonatomic, readwrite, strong) id value;

@end

#pragma mark - PHASENumberMetaParameter

/****************************************************************************************************/
/*!
    @interface PHASENumberMetaParameter
    @abstract An object that represents an active numeric metaparameter in the system
 */
OS_EXPORT API_AVAILABLE(macos(12.0), ios(15.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface PHASENumberMetaParameter : PHASEMetaParameter

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
    @property minimum
    @abstract The minimum value this metaparameter can be set to
*/
@property(nonatomic, readonly) double minimum;

/*!
    @property maximum
    @abstract The maximum value this metaparameter can be set to
*/
@property(nonatomic, readonly) double maximum;

/*!
    @method fadeToValue
    @abstract
        Fades to a new value over an interval of time
    @param value
        The new destination value to fade to
    @param duration
        The length of time it takes to arrive at the destination value
*/
- (void)fadeToValue:(double)value duration:(NSTimeInterval)duration
NS_SWIFT_NAME(fade(value:duration:));

@end

#pragma mark - PHASEStringMetaParameter

/****************************************************************************************************/
/*!
    @interface PHASEStringMetaParameter
    @abstract An object that represents an active string metaparameter in the system
 */
OS_EXPORT API_AVAILABLE(macos(12.0), ios(15.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface PHASEStringMetaParameter : PHASEMetaParameter

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

#endif /* PHASEMetaParameter_h */
