//
//  HKUnit.h
//  HealthKit
//
//  Copyright (c) 2013-2014 Apple Inc. All rights reserved.
//

#import <HealthKit/HKDefines.h>

NS_ASSUME_NONNULL_BEGIN

HK_EXTERN API_AVAILABLE(ios(8.0), watchos(2.0))
@interface HKUnit : NSObject <NSSecureCoding, NSCopying>

/// Returns a unique string representation for the unit that could be used with +unitFromString:
@property (readonly, strong) NSString *unitString;

- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)unitFromString:(NSString *)string;

// Unit strings are composed of the following units:
// International System of Units (SI) units:
// g                (grams)   [Mass]
// m                (meters)  [Length]
// L,l              (liters)  [Volume]
// Pa               (pascals) [Pressure]
// s                (seconds) [Time]
// J                (joules)  [Energy]
// K                (kelvin)  [Temperature]
// S                (siemens) [Electrical Conductance]
// Hz               (hertz)   [Frequency]
// mol<molar mass>  (moles)   [Mass] <molar mass> is the number of grams per mole. For example, mol<180.1558>
// V                (volts)   [Electrical Potential Difference]

// SI units can be prefixed as follows:
// da   (deca-)   = 10                 d    (deci-)   = 1/10
// h    (hecto-)  = 100                c    (centi-)  = 1/100
// k    (kilo-)   = 1000               m    (milli-)  = 1/1000
// M    (mega-)   = 10^6               mc   (micro-)  = 10^-6
// G    (giga-)   = 10^9               n    (nano-)   = 10^-9
// T    (tera-)   = 10^12              p    (pico-)   = 10^-12
//                                     f    (femto-)  = 10^-15

// Non-SI units:
//
// [Mass]
// oz   (ounces)  = 28.3495 g                           
// lb   (pounds)  = 453.592 g                           
// st   (stones)  = 6350.0 g
//
// [Length]
// in   (inches)  = 0.0254 m                            
// ft   (feet)    = 0.3048 m                            
// mi   (miles)   = 1609.34 m                           
//
// [Pressure]
// mmHg (millimeters of Mercury)    = 133.3224 Pa
// cmAq (centimeters of water)      = 98.06650 Pa
// atm  (atmospheres)               = 101325.0 Pa
// dBASPL (sound pressure level)    = 10^(dBASPL/20) * 2.0E-05 Pa
// inHg (inches of Mercury)         = 3386.38816 Pa
//
// [Volume]
// fl_oz_us  (US customary fluid ounces)= 0.0295735295625 L
// fl_oz_imp (Imperial fluid ounces)    = 0.0284130625 L
// pt_us     (US customary pint)        = 0.473176473 L
// pt_imp    (Imperial pint)            = 0.56826125 L
// cup_us    (US customary cup)         = 0.2365882365 L
// cup_imp   (Imperial cup)             = 0.284130625 L

// [Time]
// min  (minutes) = 60 s
// hr   (hours)   = 3600 s
// d    (days)    = 86400 s
//
// [Energy]
// cal  (calories)     = 4.1840 J
// kcal (kilocalories) = 4184.0 J
//
// [Temperature]
// degC (degrees Celsius)    = 1.0 K - 273.15
// degF (degrees Fahrenheit) = 1.8 K - 459.67
//
// [Pharmacology]
// IU   (international unit)
//
// [Scalar]
// count = 1
// %     = 1/100
//
// [Hearing Sensitivity]
// dBHL (decibel Hearing Level)
//

// Units can be combined using multiplication (. or *) and division (/), and raised to integral powers (^).
// For simplicity, only a single '/' is allowed in a unit string, and multiplication is evaluated first.
// So "kg/m.s^2" is equivalent to "kg/(m.s^2)" and "kg.m^-1.s^-2".

// The following methods convert between HKUnit and Foundation formatter units for mass, length and energy.
// When converting from Foundation formatter unit to HKUnit, if there's not a match, nil will be returned.
// When converting from HKUnit to the Foundation formatter unit, if there's not a match, an exception will be thrown.
+ (instancetype)unitFromMassFormatterUnit:(NSMassFormatterUnit)massFormatterUnit;
+ (NSMassFormatterUnit)massFormatterUnitFromUnit:(HKUnit *)unit;

+ (instancetype)unitFromLengthFormatterUnit:(NSLengthFormatterUnit)lengthFormatterUnit;
+ (NSLengthFormatterUnit)lengthFormatterUnitFromUnit:(HKUnit *)unit;

+ (instancetype)unitFromEnergyFormatterUnit:(NSEnergyFormatterUnit)energyFormatterUnit;
+ (NSEnergyFormatterUnit)energyFormatterUnitFromUnit:(HKUnit *)unit;

- (BOOL)isNull;

@end

typedef NS_ENUM(NSInteger, HKMetricPrefix) {
    HKMetricPrefixNone      = 0,    //10^0
    
    HKMetricPrefixFemto     API_AVAILABLE(ios(13.0), watchos(6.0)) = 13, //10^-15
    HKMetricPrefixPico      = 1,    //10^-12
    HKMetricPrefixNano      = 2,    //10^-9
    HKMetricPrefixMicro     = 3,    //10^-6
    HKMetricPrefixMilli     = 4,    //10^-3
    HKMetricPrefixCenti     = 5,    //10^-2
    HKMetricPrefixDeci      = 6,    //10^-1
    HKMetricPrefixDeca      = 7,    //10^1
    HKMetricPrefixHecto     = 8,    //10^2
    HKMetricPrefixKilo      = 9,    //10^3
    HKMetricPrefixMega      = 10,   //10^6
    HKMetricPrefixGiga      = 11,   //10^9
    HKMetricPrefixTera      = 12,   //10^12
} API_AVAILABLE(ios(8.0), watchos(2.0));

/* Mass Units */
@interface HKUnit (Mass)
+ (instancetype)gramUnitWithMetricPrefix:(HKMetricPrefix)prefix;       // g
+ (instancetype)gramUnit;   // g
+ (instancetype)ounceUnit;  // oz
+ (instancetype)poundUnit;  // lb
+ (instancetype)stoneUnit;  // st
+ (instancetype)moleUnitWithMetricPrefix:(HKMetricPrefix)prefix molarMass:(double)gramsPerMole;   // mol<double>
+ (instancetype)moleUnitWithMolarMass:(double)gramsPerMole; // mol<double>
@end

/* Length Units */
@interface HKUnit (Length)
+ (instancetype)meterUnitWithMetricPrefix:(HKMetricPrefix)prefix;      // m
+ (instancetype)meterUnit;  // m
+ (instancetype)inchUnit;   // in
+ (instancetype)footUnit;   // ft
+ (instancetype)yardUnit API_AVAILABLE(ios(9.0), watchos(2.0));   // yd
+ (instancetype)mileUnit;   // mi
@end

/* Volume Units */
@interface HKUnit (Volume)
+ (instancetype)literUnitWithMetricPrefix:(HKMetricPrefix)prefix;      // L
+ (instancetype)literUnit;              // L
+ (instancetype)fluidOunceUSUnit;       // fl_oz_us
+ (instancetype)fluidOunceImperialUnit; // fl_oz_imp
+ (instancetype)pintUSUnit;             // pt_us
+ (instancetype)pintImperialUnit;       // pt_imp
+ (instancetype)cupUSUnit API_AVAILABLE(ios(9.0), watchos(2.0));       // cup_us
+ (instancetype)cupImperialUnit API_AVAILABLE(ios(9.0), watchos(2.0)); // cup_imp
@end

/* Pressure Units */
@interface HKUnit (Pressure)
+ (instancetype)pascalUnitWithMetricPrefix:(HKMetricPrefix)prefix;     // Pa
+ (instancetype)pascalUnit;                 // Pa
+ (instancetype)millimeterOfMercuryUnit;    // mmHg
+ (instancetype)centimeterOfWaterUnit;      // cmAq
+ (instancetype)atmosphereUnit;             // atm
+ (instancetype)decibelAWeightedSoundPressureLevelUnit API_AVAILABLE(ios(13.0), watchos(6.0)); // dBASPL
+ (instancetype)inchesOfMercuryUnit API_AVAILABLE(ios(14.0), watchos(7.0)); // inHg
@end

/* Time Units */
@interface HKUnit (Time)
+ (instancetype)secondUnitWithMetricPrefix:(HKMetricPrefix)prefix;     // s
+ (instancetype)secondUnit; // s
+ (instancetype)minuteUnit; // min
+ (instancetype)hourUnit;   // hr
+ (instancetype)dayUnit;    // d
@end

/* Energy Units */
@interface HKUnit (Energy)
+ (instancetype)jouleUnitWithMetricPrefix:(HKMetricPrefix)prefix;      // J
+ (instancetype)jouleUnit;          // J
+ (instancetype)kilocalorieUnit;    // 1 kcal = 4184.0 J
+ (instancetype)smallCalorieUnit API_AVAILABLE(ios(11.0), watchos(4.0));    // 1 cal = 4.1840 J
+ (instancetype)largeCalorieUnit API_AVAILABLE(ios(11.0), watchos(4.0));    // 1 Cal = 4184.0 J
+ (instancetype)calorieUnit API_DEPRECATED("Use smallCalorieUnit or largeCalorieUnit, depending on which you mean", ios(8.0, 11.0), watchos(2.0, 4.0));
@end

/* Temperature Units */
@interface HKUnit (Temperature)
+ (instancetype)degreeCelsiusUnit;          // degC
+ (instancetype)degreeFahrenheitUnit;       // degF
+ (instancetype)kelvinUnit;                 // K
@end

/* Electrical Conductance Units */
@interface HKUnit (Conductance)
+ (instancetype)siemenUnitWithMetricPrefix:(HKMetricPrefix)prefix;     // S
+ (instancetype)siemenUnit; // S
@end

/* Pharmacology Units */
@interface HKUnit (Pharmacology)
+ (instancetype)internationalUnit NS_SWIFT_NAME(internationalUnit()) API_AVAILABLE(ios(11.0), watchos(4.0));  // IU
@end

/* Scalar Units */
@interface HKUnit (Scalar)
+ (instancetype)countUnit;      // count
+ (instancetype)percentUnit;    // % (0.0 - 1.0)
@end

/* Hearing Sensitivity */
@interface HKUnit (HearingSensitivity)
+ (instancetype)decibelHearingLevelUnit API_AVAILABLE(ios(13.0), watchos(6.0));  // dBHL
@end

@interface HKUnit (Math)
- (HKUnit *)unitMultipliedByUnit:(HKUnit *)unit;
- (HKUnit *)unitDividedByUnit:(HKUnit *)unit;
- (HKUnit *)unitRaisedToPower:(NSInteger)power;
- (HKUnit *)reciprocalUnit;
@end

/* Frequency Units */
@interface HKUnit (Frequency)
+ (instancetype)hertzUnitWithMetricPrefix:(HKMetricPrefix)prefix API_AVAILABLE(ios(13.0), watchos(6.0));      // Hz
+ (instancetype)hertzUnit API_AVAILABLE(ios(13.0), watchos(6.0));  // Hz
@end

/* Electrical Potential Difference Units */
@interface HKUnit (ElectricPotentialDifference)
+ (instancetype)voltUnitWithMetricPrefix:(HKMetricPrefix)prefix API_AVAILABLE(ios(14.0), watchos(7.0));      // V
+ (instancetype)voltUnit API_AVAILABLE(ios(14.0), watchos(7.0));  // V
@end

/* Mole Constants */
#define HKUnitMolarMassBloodGlucose (180.15588000005408)

NS_ASSUME_NONNULL_END
