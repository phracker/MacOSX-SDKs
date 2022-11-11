/*
	Copyright (C) 2020 Apple Inc. All Rights Reserved.
*/

#pragma once

#ifndef EXPOSURE_NOTIFICATION_INDIRECT_INCLUDES
#error "Please #import <ExposureNotification/ExposureNotification.h> instead of this file directly."
#endif

#import <dispatch/dispatch.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

#ifdef __cplusplus
extern "C" {
#endif

@class ENExposureSummaryItem;
@class ENScanInstance;

//===========================================================================================================================
// MARK: -
// MARK: == Configuration ==

/// General API support available. Allows compile-time conditionalization of code.
#ifndef EN_FEATURE_GENERAL
	#if TARGET_OS_IOS
		#define EN_FEATURE_GENERAL		1
	#else
		#define EN_FEATURE_GENERAL		0
	#endif
#endif

/// Indicates the platforms this API is available for version 1 of the API. Used for non-exportable items, such as typedefs.
#define EN_API_AVAILABLE			API_AVAILABLE( ios( 12.5 ) ) API_UNAVAILABLE(macos, tvos, watchos)

/// Indicates the platforms this API is available for version 2 of the API. Used for non-exportable items, such as typedefs.
#define EN_API_AVAILABLE_V2			API_AVAILABLE( ios( 12.5 ) ) API_UNAVAILABLE(macos, tvos, watchos)

/// Indicates the platforms this API is available for version 3 of the API. Used for non-exportable items, such as typedefs.
#define EN_API_AVAILABLE_V3			API_AVAILABLE( ios( 14.4 ) ) API_UNAVAILABLE(macos, tvos, watchos)

/// Indicates the platforms this API is available for version 5 of the API. Used for non-exportable items, such as typedefs.
#define EN_API_AVAILABLE_V5			API_AVAILABLE( ios( 15.2 ) ) API_UNAVAILABLE(macos, tvos, watchos)

/// Indicates the platforms this API is available for version 1 of the API and exports the symbol via the framework.
#define EN_API_AVAILABLE_EXPORT		EN_API_AVAILABLE __attribute__( ( visibility( "default" ) ) )

/// Indicates the platforms this API is available for version 2 of the API and exports the symbol via the framework.
#define EN_API_AVAILABLE_EXPORT_V2	EN_API_AVAILABLE_V2 __attribute__( ( visibility( "default" ) ) )

/// Converts value to string
#define ENStringify( X )            # X
#define ENStringifyExpansion( X )   ENStringify( X )

//===========================================================================================================================
// MARK: -
// MARK: == Errors ==

/// NSError domain for Exposure Notification errors.
EN_API_AVAILABLE_EXPORT
extern NSErrorDomain const		ENErrorDomain;

/// Error codes used with ENErrorDomain.
typedef NS_ERROR_ENUM( ENErrorDomain, ENErrorCode )
{
	ENErrorCodeUnknown					= 1,  /// Underlying failure with an unknown cause.
	ENErrorCodeBadParameter				= 2,  /// Missing or incorrect parameter.
	ENErrorCodeNotEntitled				= 3,  /// Calling process doesn't have the correct entitlement.
	ENErrorCodeNotAuthorized			= 4,  /// User denied this process access to Exposure Notification functionality.
	ENErrorCodeUnsupported				= 5,  /// Operation is not supported.
	ENErrorCodeInvalidated				= 6,  /// Invalidate was called before the operation completed normally.
	ENErrorCodeBluetoothOff				= 7,  /// Bluetooth was turned off the by user.
	ENErrorCodeInsufficientStorage		= 8,  /// Insufficient storage space to enable Exposure Notification.
	ENErrorCodeNotEnabled				= 9,  /// Exposure Notification has not been enabled.
	ENErrorCodeAPIMisuse				= 10, /// The API was used incorrectly.
	ENErrorCodeInternal					= 11, /// Internal error. This indicates a bug in this framework.
	ENErrorCodeInsufficientMemory		= 12, /// Not enough memory to perform an operation.
	ENErrorCodeRateLimited				= 13, /// API called too frequently. See API for acceptable frequency.
	ENErrorCodeRestricted				= 14, /// Exposure Notification is disabled due to system policies.
	ENErrorCodeBadFormat				= 15, /// File or data format problem.
	ENErrorCodeDataInaccessible			= 16, /// The device must be unlocked before data is accessible.
	ENErrorCodeTravelStatusNotAvailable	= 17, /// Travel status is not available
	
}	EN_API_AVAILABLE;

/// Type for returning NSError's from functions. Avoids long and repetitious method signatures.
typedef NSError * _Nullable __autoreleasing * _Nullable		ENErrorOutType EN_API_AVAILABLE;

//===========================================================================================================================
// MARK: -
// MARK: == Misc ==

//===========================================================================================================================
/*!	@brief	Attenuation of a radio signal. This is the Advertised Transmit Power - Measured RSSI.

	Note: The attenuation value may be misleading because more attenuation doesn’t necessarily mean the device is farther 
	away. For example, two people could be very close and facing each other with their phones in their back pockets. This 
	may report higher attenuation (i.e. weaker received signal) even though the individuals are very close together.
*/
typedef uint8_t		ENAttenuation EN_API_AVAILABLE;
enum
{
	ENAttenuationMin EN_API_AVAILABLE = 0,
	ENAttenuationMax EN_API_AVAILABLE = 0xFF,
};

//===========================================================================================================================
/*!	@brief	Indicates the status of authorization for the app.
*/
typedef NS_ENUM( NSInteger, ENAuthorizationStatus )
{
	/// Authorization status has not yet been determined.
	/// This status means the user has not been prompted yet. Using the API in this state may prompt the user.
	ENAuthorizationStatusUnknown		= 0,
	
	/// This app is not authorized to use Exposure Notification. The user cannot change this app's authorization status.
	/// This status may be due to active restrictions, such as parental controls being in place.
	ENAuthorizationStatusRestricted		= 1,
	
	/// The user denied authorization for this app.
	ENAuthorizationStatusNotAuthorized	= 2,
	
	/// The user has authorized this app to use Exposure Notification.
	ENAuthorizationStatusAuthorized		= 3,
	
}	EN_API_AVAILABLE;

//===========================================================================================================================
/*!	@brief	Confidence in calibration data.
*/
typedef NS_ENUM( uint8_t, ENCalibrationConfidence )
{
	/// No calibration data.
	ENCalibrationConfidenceLowest	= 0,
	
	/// Using average calibration over phones of this manufacturer or Android beacons from EN API version < 1.5.
	ENCalibrationConfidenceLow		= 1,
	
	/// Using single-antenna orientation for a similar phone model or iPhone beacons from EN API version < 1.5.
	ENCalibrationConfidenceMedium	= 2,
	
	/// Determined using significant calibration data for this model.
	ENCalibrationConfidenceHigh		= 3,
	
}	EN_API_AVAILABLE_V2;

//===========================================================================================================================
/*!	@brief	The value used when days since onset of symptoms is unspecified.
*/
API_DEPRECATED( "Server must provide keys with days_since_onset_of_symptoms set.", ios( 14.0, 14.2 ) )
static const NSInteger ENDaysSinceOnsetOfSymptomsUnknown = NSIntegerMax;

//===========================================================================================================================
/*!	@brief	How positive diagnosis was reported.
*/
typedef NS_ENUM( uint32_t, ENDiagnosisReportType )
{
	/// Diagnosis type unknown or not available.
	ENDiagnosisReportTypeUnknown					= 0,
	
	/// Confirmed test.
	ENDiagnosisReportTypeConfirmedTest				= 1,
	
	/// Confirmed clinical diagnosis.
	ENDiagnosisReportTypeConfirmedClinicalDiagnosis	= 2,
	
	/// User reported positive diagnosis without health authority involvement.
	ENDiagnosisReportTypeSelfReported				= 3,
	
	/// Person determined to be positive based on exposure to another person confirmed to be positive. This report type
	/// is reserved for future use and keys with this report type are not matched by iOS.
	ENDiagnosisReportTypeRecursive					= 4,
	
	/// Negative test. This is mainly to negate a previous self report or clinical diagnosis that may have been in error.
	ENDiagnosisReportTypeRevoked					= 5,
	
}	EN_API_AVAILABLE_V2;

//===========================================================================================================================
/*!	@brief	How infectious based on days since onset of symptoms.
*/
typedef NS_ENUM( uint32_t, ENInfectiousness )
{
	ENInfectiousnessNone		= 0, /// Never returned through the API, but used for configuration.
	ENInfectiousnessStandard	= 1,
	ENInfectiousnessHigh		= 2,
	
}	EN_API_AVAILABLE_V2;

typedef NS_ENUM( uint32_t, ENVariantOfConcernType )
{
	ENVariantOfConcernTypeUnknown   = 0, // Unknown
	ENVariantOfConcernType1         = 1, // Vaccine is effective
	ENVariantOfConcernType2         = 2, // Highly transmissive
	ENVariantOfConcernType3         = 3, // High severity
	ENVariantOfConcernType4         = 4, // Vaccine breakthrough
}	EN_API_AVAILABLE_V5;

//===========================================================================================================================
/*!	@brief	ENIntervalNumber (ENIN)
	
	A number for each 10 minute window that is shared between all devices participating in the protocol.
	These time windows are based Unix Time (epoch 1970-01-01 00:00:00). It's calculated as:
	
	ENIN = <Seconds since 1970-01-01 00:00:00> / ( 60 * 10 )
	
	It's encoded as an unsigned 32-bit (uint32_t), little endian value.
*/
typedef uint32_t	ENIntervalNumber EN_API_AVAILABLE;

//===========================================================================================================================
/*!	@brief	Represents a risk level, ranging from 0-7.
*/
typedef uint8_t		ENRiskLevel EN_API_AVAILABLE;
enum
{
	ENRiskLevelMin EN_API_AVAILABLE = 0,
	ENRiskLevelMax EN_API_AVAILABLE = 7,
};

//===========================================================================================================================
/*!	@brief	The value, ranging from 0 to 8, that the app assigns to each Risk Level in each of the Risk Level Parameters.
*/
typedef uint8_t		ENRiskLevelValue EN_API_AVAILABLE;
enum
{
	ENRiskLevelValueMin EN_API_AVAILABLE = 0,
	ENRiskLevelValueMax EN_API_AVAILABLE = 8,
};

//===========================================================================================================================
/*!	@brief	Represents estimated risk calculated by a scoring algorithm. Range is 0-255. 255 is the highest risk.
*/
typedef uint8_t		ENRiskScore EN_API_AVAILABLE;
enum
{
	ENRiskScoreMin EN_API_AVAILABLE = 0,
	ENRiskScoreMax EN_API_AVAILABLE = 255,
};

//===========================================================================================================================
/*!	@brief	Constants for risk weights.
*/
enum
{
	ENRiskWeightDefault		EN_API_AVAILABLE	= 1,
	ENRiskWeightDefaultV2	EN_API_AVAILABLE_V2	= 100,
	ENRiskWeightMin			EN_API_AVAILABLE	= 0,
	ENRiskWeightMax			EN_API_AVAILABLE	= 100,
	ENRiskWeightMaxV2		EN_API_AVAILABLE_V2	= 250,
};

//===========================================================================================================================
// MARK: -
// MARK: == Handlers ==

/// Invoked when an operation completes. Error is nil for success or non-nil if an error occurred.
EN_API_AVAILABLE
typedef void ( ^ENErrorHandler )( NSError * _Nullable error );

// MARK: -
// MARK: == Classes ==

//===========================================================================================================================
/*!	@brief	Configuration parameters for exposure detection.

	Configuration parameters are used to calculate an exposure duration for each exposure using the following formula.
	
	exposureDuration = 
		( ( immediateDuration * immediateDurationWeight ) + 
		  ( nearDuration      * nearDurationWeight ) + 
		  ( mediumDuration    * mediumDurationWeight ) + 
		  ( otherDuration     * otherDurationWeight ) )
		* infectiousnessWeight )
		* reportTypeWeight )
*/
EN_API_AVAILABLE_EXPORT
@interface ENExposureConfiguration : NSObject

/// Weights to apply to durations at each proximity level based on attenuation. Range is 0-250%.
@property (readwrite, assign, nonatomic) double immediateDurationWeight EN_API_AVAILABLE_V2;
@property (readwrite, assign, nonatomic) double nearDurationWeight EN_API_AVAILABLE_V2;
@property (readwrite, assign, nonatomic) double mediumDurationWeight EN_API_AVAILABLE_V2;
@property (readwrite, assign, nonatomic) double otherDurationWeight EN_API_AVAILABLE_V2;

/// Maps daysSinceOnsetOfSymptoms to infectiousness. Must be configured if using V2 scoring.
/// Key is a daysSinceOnsetOfSymptoms: -14 to 14. Value is an ENInfectiousness.
/// Defaults to ENInfectiousnessNone for days not specified.
/// If a value is set to ENInfectiousnessNone, diagnosis keys for it should be ignored.
@property (readwrite, copy, nonatomic, nullable) NSDictionary <NSNumber *, NSNumber *> *infectiousnessForDaysSinceOnsetOfSymptoms EN_API_AVAILABLE_V2;

/// Weights to apply for infectiousness. Range is 0-250%.
@property (readwrite, assign, nonatomic) double infectiousnessStandardWeight EN_API_AVAILABLE_V2;
@property (readwrite, assign, nonatomic) double infectiousnessHighWeight EN_API_AVAILABLE_V2;

/// Weights to apply for each report type. Range is 0-250%.
@property (readwrite, assign, nonatomic) double reportTypeConfirmedTestWeight EN_API_AVAILABLE_V2;
@property (readwrite, assign, nonatomic) double reportTypeConfirmedClinicalDiagnosisWeight EN_API_AVAILABLE_V2;
@property (readwrite, assign, nonatomic) double reportTypeSelfReportedWeight EN_API_AVAILABLE_V2;
@property (readwrite, assign, nonatomic) double reportTypeRecursiveWeight EN_API_AVAILABLE_V2;

/// Maps scenarios when Report Type is not present into one of the available report types.
/// If this is set to ENDiagnosisReportTypeUnknown, the key will be ignored if it does not contain a report type.
@property (readwrite, assign, nonatomic) ENDiagnosisReportType reportTypeNoneMap EN_API_AVAILABLE_V2;

//---------------------------------------------------------------------------------------------------------------------------

/// Thresholds for calculating attenuationDurations. Defaults to [50, 70, 90].
///
/// Index		|0	|1	|2		
/// Variable	|X	|Y	|Z
@property (readwrite, copy, nonatomic) NSArray <NSNumber *> *		attenuationDurationThresholds;

/// Exclude exposures with daysSinceLastExposure > this value. Defaults to 0 (don't filter).
@property (readwrite, assign, nonatomic) NSInteger					daysSinceLastExposureThreshold EN_API_AVAILABLE_V2;

/// Minimum risk score. Excludes exposure incidents with scores lower than this. Full range and not capped to ENRiskScore.
@property (readwrite, assign, nonatomic) double						minimumRiskScoreFullRange;

//---------------------------------------------------------------------------------------------------------------------------
// Soon to be deprecated parameters. Use the parameters above instead.

@property (readwrite, copy, nonatomic) NSArray <NSNumber *> *		attenuationLevelValues;
@property (readwrite, assign, nonatomic) double						attenuationWeight;
@property (readwrite, copy, nonatomic) NSArray <NSNumber *> *		daysSinceLastExposureLevelValues;
@property (readwrite, assign, nonatomic) double						daysSinceLastExposureWeight;
@property (readwrite, copy, nonatomic) NSArray <NSNumber *> *		durationLevelValues;
@property (readwrite, assign, nonatomic) double						durationWeight;
@property (readwrite, copy, nullable, nonatomic) NSDictionary *		metadata;
@property (readwrite, assign, nonatomic) ENRiskScore				minimumRiskScore;
@property (readwrite, copy, nonatomic) NSArray <NSNumber *> *		transmissionRiskLevelValues;
@property (readwrite, assign, nonatomic) double						transmissionRiskWeight;

@end

//===========================================================================================================================
/*!	@brief	Summary of exposure info for a single day.
*/
EN_API_AVAILABLE_EXPORT_V2
@interface ENExposureDaySummary : NSObject

/// Day the exposure occurred.
@property (readonly, copy, nonatomic) NSDate *date;

/// Summary of all exposures on this day of a specific diagnosis report type.
@property (readonly, strong, nullable, nonatomic) ENExposureSummaryItem *confirmedTestSummary;
@property (readonly, strong, nullable, nonatomic) ENExposureSummaryItem *confirmedClinicalDiagnosisSummary;
@property (readonly, strong, nullable, nonatomic) ENExposureSummaryItem *recursiveSummary;
@property (readonly, strong, nullable, nonatomic) ENExposureSummaryItem *selfReportedSummary;

/// Summary of all exposures on this day.
@property (readonly, strong, nonatomic) ENExposureSummaryItem *daySummary;

@end

//===========================================================================================================================
/*!	@brief	Summary of exposure detection.
*/
EN_API_AVAILABLE_EXPORT
@interface ENExposureDetectionSummary : NSObject

/// Array of durations in seconds at certain radio signal attenuations.
/// Array index 0: Sum of durations for all exposures when attenuation <= X
/// Array index 1: Sum of durations for all exposures when attenuation <= Y
/// Array index 2: Sum of durations for all exposures when attenuation <= Z
/// Array index 3: Sum of durations for all exposures when attenuation >  Z
/// X, Y, Z come from the attenuationDurationThresholds on the configuration object.
@property (readonly, copy, nonatomic) NSArray <NSNumber *> *					attenuationDurations;

/// Number of days since the most recent exposure. 0 = today, 1 = yesterday, etc. Only valid if matchedKeyCount > 0.
@property (readonly, assign, nonatomic) NSInteger								daysSinceLastExposure;

/// Number of diagnosis keys that matched.
@property (readonly, assign, nonatomic) uint64_t								matchedKeyCount;

/// Highest risk score of all exposure incidents.
@property (readonly, assign, nonatomic) ENRiskScore								maximumRiskScore;

/// Highest risk score of all exposure incidents.
@property (readonly, assign, nonatomic) double									maximumRiskScoreFullRange;

/// Metadata associated with the summary.
@property (readonly, copy, nullable, nonatomic) NSDictionary *					metadata;

/// Sum of risk scores for all exposures. Summed using the full range risk scores before capping to ENRiskScore.
@property (readonly, assign, nonatomic) double									riskScoreSumFullRange;

/// Summary of each day containing an exposure.
@property (readonly, copy, nonatomic) NSArray <ENExposureDaySummary *> *		daySummaries EN_API_AVAILABLE_V2;

@end

//===========================================================================================================================
/*!	@brief	Info about an exposure.
*/
EN_API_AVAILABLE_EXPORT
@interface ENExposureInfo : NSObject

/// Array of durations in seconds at certain radio signal attenuations.
/// Array index 0: Sum of durations for this exposure when attenuation <= X
/// Array index 1: Sum of durations for this exposure when attenuation <= Y
/// Array index 2: Sum of durations for this exposure when attenuation <= Z
/// Array index 3: Sum of durations for this exposure when attenuation >  Z
/// X, Y, Z come from the attenuationDurationThresholds on the configuration object.
@property (readonly, copy, nonatomic) NSArray <NSNumber *> *		attenuationDurations;

/// Duration-weighted average of the attenuations associated with this exposure.
@property (readonly, assign, nonatomic) ENAttenuation				attenuationValue;

/// Date when the exposure occurred. This may have reduced precision, such as within 1 day of the actual time.
@property (readonly, copy, nonatomic) NSDate *						date;

/// Number of days since the onset of symptoms. Defaults to ENDaysSinceOnsetOfSymptomsUnknown.
@property (readonly, assign, nonatomic) NSInteger					daysSinceOnsetOfSymptoms EN_API_AVAILABLE_V2;

/// How positive diagnosis was reported.
@property (readonly, assign, nonatomic) ENDiagnosisReportType		diagnosisReportType EN_API_AVAILABLE_V2;

/// Length of exposure in 5 minute increments with a 30 minute maximum.
@property (readonly, assign, nonatomic) NSTimeInterval				duration;

/// Metadata associated with the exposure.
@property (readonly, copy, nullable, nonatomic) NSDictionary *		metadata;

/// Indicates the total risk calculated for this exposure incident. Capped to ENRiskScore range.
@property (readonly, assign, nonatomic) ENRiskScore					totalRiskScore;

/// Indicates the total risk calculated for this exposure incident. Full range and not capped to ENRiskScore.
@property (readonly, assign, nonatomic) double						totalRiskScoreFullRange;

/// Indicates the transmission risk associated with the diagnosis key.
@property (readonly, assign, nonatomic) ENRiskLevel					transmissionRiskLevel;

@end

//===========================================================================================================================
/*!	@brief	Summary for a specific time period or report type.
*/
EN_API_AVAILABLE_EXPORT_V2
@interface ENExposureSummaryItem : NSObject

/// Highest score of all exposures for this item.
@property (readonly, assign, nonatomic) double maximumScore;

/// Sum of scores for all exposure for this item.
@property (readonly, assign, nonatomic) double scoreSum;

/// Sum of exposure durations weighted by their attenuation.
/// weightedDurationSum = 
///		( immediateDuration * immediateDurationWeight ) +
///		( nearDuration      * nearDurationWeight ) +
///		( mediumDuration    * mediumDurationWeight ) +
///		( otherDuration     * otherDurationWeight ).
@property (readonly, assign, nonatomic) NSTimeInterval weightedDurationSum;

@end

//===========================================================================================================================
/*!	@brief	A duration of up to 30 minutes during which beacons from a TEK were observed.
*/
EN_API_AVAILABLE_EXPORT_V2
@interface ENExposureWindow : NSObject

/// Transmitting device's calibration confidence.
@property (readonly, assign, nonatomic) ENCalibrationConfidence			calibrationConfidence;

/// Day the exposure occurred.
@property (readonly, copy, nonatomic) NSDate *							date;

/// How positive diagnosis was reported for this the TEK observed for this window.
@property (readonly, assign, nonatomic) ENDiagnosisReportType			diagnosisReportType;

/// How infectious based on days since onset of symptoms.
@property (readonly, assign, nonatomic) ENInfectiousness				infectiousness;

/// Each scan instance corresponds to a scan (of a few seconds) when a beacon with a TEK causing this exposure was observed.
@property (readonly, copy, nonatomic) NSArray <ENScanInstance *> *		scanInstances;

/// Type of variant of concern
@property (readonly, assign, nonatomic) ENVariantOfConcernType			variantOfConcernType EN_API_AVAILABLE_V5;

@end

//===========================================================================================================================
/*!	@brief	Aggregation of attenuations of all of this TEK's beacons received during a scan.
*/
EN_API_AVAILABLE_EXPORT_V2
@interface ENScanInstance : NSObject

/// Minimum attenuation of all of this TEK's beacons received during the scan.
@property (readonly, assign, nonatomic) ENAttenuation		minimumAttenuation;

/// Aggregation of the attenuations of all of this TEK's beacons received during the scan.
@property (readonly, assign, nonatomic) ENAttenuation		typicalAttenuation;

/// Seconds elapsed since the the previous scan.
@property (readonly, assign, nonatomic) NSInteger			secondsSinceLastScan;

@end

//===========================================================================================================================
/*!	@brief	Key used to generate rolling proximity identifiers.
*/
EN_API_AVAILABLE_EXPORT
@interface ENTemporaryExposureKey : NSObject

/// Key material used to generate Rolling Proximity Identifiers.
@property (readwrite, copy, nonatomic) NSData *					keyData;

/// Duration this key is valid. It's the number of 10-minute windows between key rolling.
@property (readwrite, assign, nonatomic) ENIntervalNumber		rollingPeriod;

/// Interval number when the key's EKRollingPeriod started.
@property (readwrite, assign, nonatomic) ENIntervalNumber		rollingStartNumber;

/// Risk of transmission associated with the person this key came from.
@property (readwrite, assign, nonatomic) ENRiskLevel			transmissionRiskLevel;

@end

#ifdef __cplusplus
}
#endif

NS_ASSUME_NONNULL_END
