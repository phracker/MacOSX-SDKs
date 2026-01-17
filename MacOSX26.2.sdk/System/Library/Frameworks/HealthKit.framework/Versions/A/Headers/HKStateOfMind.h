//
//  HKStateOfMind.h
//  HealthKit
//
//  Copyright © 2022-2024 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HealthKit/HKDefines.h>
#import <HealthKit/HKSample.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @enum          HKStateOfMindValenceClassification
 @abstract      A general region of pleasantness derived from valence logged on a state of mind sample.
 */
typedef NS_ENUM(NSInteger, HKStateOfMindValenceClassification) {
    HKStateOfMindValenceClassificationVeryUnpleasant = 1,
    HKStateOfMindValenceClassificationUnpleasant,
    HKStateOfMindValenceClassificationSlightlyUnpleasant,
    HKStateOfMindValenceClassificationNeutral,
    HKStateOfMindValenceClassificationSlightlyPleasant,
    HKStateOfMindValenceClassificationPleasant,
    HKStateOfMindValenceClassificationVeryPleasant,
} NS_SWIFT_NAME(HKStateOfMind.ValenceClassification) API_AVAILABLE(ios(18.0), watchos(11.0), macCatalyst(18.0), macos(15.0), visionos(2.0));

/// Returns the valence classification appropriate for a valence value.
/// If the given valence is outside the supported range of values, this function returns @c nil.
HK_EXTERN NSNumber /* HKStateOfMindValenceClassification */ * _Nullable HKStateOfMindValenceClassificationForValence(double valence) NS_REFINED_FOR_SWIFT;

/*!
 @enum          HKStateOfMindLabel
 @abstract      A specific word describing a felt experience.
 */
typedef NS_ENUM(NSInteger, HKStateOfMindLabel) {
    HKStateOfMindLabelAmazed = 1,
    HKStateOfMindLabelAmused,
    HKStateOfMindLabelAngry,
    HKStateOfMindLabelAnxious,
    HKStateOfMindLabelAshamed,
    HKStateOfMindLabelBrave,
    HKStateOfMindLabelCalm,
    HKStateOfMindLabelContent,
    HKStateOfMindLabelDisappointed,
    HKStateOfMindLabelDiscouraged,
    HKStateOfMindLabelDisgusted,
    HKStateOfMindLabelEmbarrassed,
    HKStateOfMindLabelExcited,
    HKStateOfMindLabelFrustrated,
    HKStateOfMindLabelGrateful,
    HKStateOfMindLabelGuilty,
    HKStateOfMindLabelHappy,
    HKStateOfMindLabelHopeless,
    HKStateOfMindLabelIrritated,
    HKStateOfMindLabelJealous,
    HKStateOfMindLabelJoyful,
    HKStateOfMindLabelLonely,
    HKStateOfMindLabelPassionate,
    HKStateOfMindLabelPeaceful,
    HKStateOfMindLabelProud,
    HKStateOfMindLabelRelieved,
    HKStateOfMindLabelSad,
    HKStateOfMindLabelScared,
    HKStateOfMindLabelStressed,
    HKStateOfMindLabelSurprised,
    HKStateOfMindLabelWorried,
    HKStateOfMindLabelAnnoyed,
    HKStateOfMindLabelConfident,
    HKStateOfMindLabelDrained,
    HKStateOfMindLabelHopeful,
    HKStateOfMindLabelIndifferent,
    HKStateOfMindLabelOverwhelmed,
    HKStateOfMindLabelSatisfied,
} NS_SWIFT_NAME(HKStateOfMind.Label) API_AVAILABLE(ios(18.0), watchos(11.0), macCatalyst(18.0), macos(15.0), visionos(2.0));

/*!
 @enum          HKStateOfMindAssociation
 @abstract      A general facet of life with which a felt experience may be associated.
 */
typedef NS_ENUM(NSInteger, HKStateOfMindAssociation) {
    HKStateOfMindAssociationCommunity = 1,
    HKStateOfMindAssociationCurrentEvents,
    HKStateOfMindAssociationDating,
    HKStateOfMindAssociationEducation,
    HKStateOfMindAssociationFamily,
    HKStateOfMindAssociationFitness,
    HKStateOfMindAssociationFriends,
    HKStateOfMindAssociationHealth,
    HKStateOfMindAssociationHobbies,
    HKStateOfMindAssociationIdentity,
    HKStateOfMindAssociationMoney,
    HKStateOfMindAssociationPartner,
    HKStateOfMindAssociationSelfCare,
    HKStateOfMindAssociationSpirituality,
    HKStateOfMindAssociationTasks,
    HKStateOfMindAssociationTravel,
    HKStateOfMindAssociationWork,
    HKStateOfMindAssociationWeather,
} NS_SWIFT_NAME(HKStateOfMind.Association) API_AVAILABLE(ios(18.0), watchos(11.0), macCatalyst(18.0), macos(15.0), visionos(2.0));

/*!
 @enum          HKStateOfMindKind
 @abstract      The kind of feeling type captured by a state of mind log, considering the period of time the reflection concerns.
 */
typedef NS_ENUM(NSInteger, HKStateOfMindKind) {
    HKStateOfMindKindMomentaryEmotion = 1,
    HKStateOfMindKindDailyMood = 2,
} NS_SWIFT_NAME(HKStateOfMind.Kind) API_AVAILABLE(ios(18.0), watchos(11.0), macCatalyst(18.0), macos(15.0), visionos(2.0));

/// Represents how one feels, including descriptors of a feeling and optionally, its source.
HK_EXTERN
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(18.0), watchos(11.0), macCatalyst(18.0), macos(15.0), visionos(2.0))
@interface HKStateOfMind : HKSample <NSSecureCoding, NSCopying>

/// A description of the kind of feeling type captured by this state of mind.
///
/// Feeling types can be understood by the timeframe considered to create this log, possibly indicated by the context used to create it.
/// For example, a `momentary emotion` log might be in response to 'how are you feeling right now?' while a `daily mood` log
/// might be in response to 'how have you been feeling today?'.
@property (nonatomic, assign, readonly) HKStateOfMindKind kind;

/// A signed, self-reported measure of how positive or negative one is feeling, on a continuous scale from -1 to +1.
@property (nonatomic, assign, readonly) double valence;

/// A general region of pleasantness based on this sample's valence value.
@property (nonatomic, assign, readonly) HKStateOfMindValenceClassification valenceClassification;

/// Zero or more specific sentiments selected to represent a felt experience.
@property (nonatomic, copy, readonly) NSArray<NSNumber /* HKStateOfMindLabel */ *> *labels NS_REFINED_FOR_SWIFT;

/// Zero or more facets of life with which this felt experience is associated.
@property (nonatomic, copy, readonly) NSArray<NSNumber /* HKStateOfMindAssociation */ *> *associations NS_REFINED_FOR_SWIFT;

/// Creates a new log describing an experienced emotion at a moment in time.
+ (instancetype)stateOfMindWithDate:(NSDate *)date
                               kind:(HKStateOfMindKind)kind
                            valence:(double)valence
                             labels:(NSArray<NSNumber /* HKStateOfMindLabel */ *> *)labels
                       associations:(NSArray<NSNumber /* HKStateOfMindAssociation */ *> *)associations NS_REFINED_FOR_SWIFT;

/// Creates a new log describing an experienced emotion at a moment in time.
+ (instancetype)stateOfMindWithDate:(NSDate *)date
                               kind:(HKStateOfMindKind)kind
                            valence:(double)valence
                             labels:(NSArray<NSNumber /* HKStateOfMindLabel */ *> *)labels
                       associations:(NSArray<NSNumber /* HKStateOfMindAssociation */ *> *)associations
                           metadata:(nullable NSDictionary<NSString *, id> *)metadata NS_REFINED_FOR_SWIFT;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end


NS_ASSUME_NONNULL_END
