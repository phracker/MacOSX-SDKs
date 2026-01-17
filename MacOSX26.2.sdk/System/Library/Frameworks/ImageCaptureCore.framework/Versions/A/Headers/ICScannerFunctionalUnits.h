
//------------------------------------------------------------------------------------------------------------------------------
//
//  ICScannerFunctionalUnits.h
//  ImageCaptureCore
//
//  Copyright (c) 2008-2011 Apple Inc., all rights reserved.
//
//  Best viewed with the following settings: Tab width 4, Indent width 2, Wrap lines, Indent wrapped lines by 3, Page guide 128.
//
//------------------------------------------------------------------------------------------------------------------------------

#pragma once

/*!
  @header ICScannerFunctionalUnit
  @abstract ICScannerFunctionalUnit is an abstract class that represents a scanner functiona unit. ImageCaptureCore defines three concrete subclasses of ICScannerFunctionalUnit: ICScannerFunctionalUnitFlatbed, ICScannerFunctionalUnitPositiveTransparency, ICScannerFunctionalUnitNegativeTransparency and ICScannerFunctionalUnitDocumentFeeder. ICScannerDevice creates instances of these concrete subclasses.
*/

//------------------------------------------------------------------------------------------------------------------------------

#import <ImageCaptureCore/ImageCapturePlatform.h>
#import <ImageCaptureCore/ImageCaptureConstants.h>
#import <Foundation/Foundation.h>

//-------------------------------------------------------------------------------------------------------------------- Constants
/*!
  @ICScannerFunctionalUnitType
  @abstract Scanner Functional Unit Types
  @constant ICScannerFunctionalUnitTypeFlatbed Flatbed functional unit.
  @constant ICScannerFunctionalUnitTypePositiveTransparency Transparency functional unit for scanning positives.
  @constant ICScannerFunctionalUnitTypeNegativeTransparency Transparency functional unit for scanning negatives.
  @constant ICScannerFunctionalUnitTypeDocumentFeeder Document feeder functional unit.
*/

typedef NS_ENUM(NSUInteger, ICScannerFunctionalUnitType)
{
    ICScannerFunctionalUnitTypeFlatbed              = 0,
    ICScannerFunctionalUnitTypePositiveTransparency = 1,
    ICScannerFunctionalUnitTypeNegativeTransparency = 2,
    ICScannerFunctionalUnitTypeDocumentFeeder       = 3
} IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
  @ICScannerMeasurementUnit
  @abstract Unit of measurement used by the scanner. This corresponds to values used for ICAP_UNITS as defined in the TWAIN Specification.
  @constant ICScannerMeasurementUnitInches      1 inch  = 2.54         cm
  @constant ICScannerMeasurementUnitCentimeters 1 cm    = 1.00         cm or 1/2.54 inches
  @constant ICScannerMeasurementUnitPicas       1 pica  = .42333333    cm or 1/6    inches
  @constant ICScannerMeasurementUnitPoints      1 point = .0352777775  cm or 1/72   inches
  @constant ICScannerMeasurementUnitTwips       1 twip  = .0001763888  cm or 1/1440 inches
  @constant ICScannerMeasurementUnitPixels
*/

typedef NS_ENUM(NSUInteger, ICScannerMeasurementUnit)
{
    ICScannerMeasurementUnitInches      = 0,
    ICScannerMeasurementUnitCentimeters = 1,
    ICScannerMeasurementUnitPicas       = 2,
    ICScannerMeasurementUnitPoints      = 3,
    ICScannerMeasurementUnitTwips       = 4,
    ICScannerMeasurementUnitPixels      = 5
} IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
  @ICScannerBitDepth
  @abstract Bits per channel in the scanned image.
  @constant ICScannerBitDepth1Bit 1-bit image.
  @constant ICScannerBitDepth8Bits Image with 8 bits per channel.
  @constant ICScannerBitDepth16Bits Image with 16 bits per channel.
*/

typedef NS_ENUM(NSUInteger, ICScannerBitDepth)
{
    ICScannerBitDepth1Bit   = 1,
    ICScannerBitDepth8Bits  = 8,
    ICScannerBitDepth16Bits = 16
} IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
  @ICScannerColorDataFormatType
  @abstract Identifies color data formats. Only relevant for multi-channel data. Corresponds to "ICAP_PLANARCHUNKY" of the TWAIN Specification.
  @constant ICScannerColorDataFormatTypeChunky For multi-channel data (e.g., RGB) data from all channels are interleaved.
  @constant ICScannerColorDataFormatTypePlanar For multi-channel data (e.g., RGB) each channel is transferred sequentially.
*/

typedef NS_ENUM(NSUInteger, ICScannerColorDataFormatType)
{
    ICScannerColorDataFormatTypeChunky  = 0,
    ICScannerColorDataFormatTypePlanar  = 1
} IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
  @ICScannerPixelDataType
  @abstract Pixel data types. Corresponds to "ICAP_PIXELTYPE" of the TWAIN Specification.
  @constant ICScannerPixelDataTypeBW Monochrome 1 bit pixel image.
  @constant ICScannerPixelDataTypeGray 8 bit pixel Gray color space.
  @constant ICScannerPixelDataTypeRGB Color image RGB color space.
  @constant ICScannerPixelDataTypePalette Indexed Color image.
  @constant ICScannerPixelDataTypeCMY Color image in CMY color space.
  @constant ICScannerPixelDataTypeCMYK Color image in CMYK color space.
  @constant ICScannerPixelDataTypeYUV Color image in YUV color space.
  @constant ICScannerPixelDataTypeYUVK Color image in YUVK color space.
  @constant ICScannerPixelDataTypeCIEXYZ Color image in CIEXYZ color space.
*/

typedef NS_ENUM(NSUInteger, ICScannerPixelDataType)
{
    ICScannerPixelDataTypeBW      = 0,
    ICScannerPixelDataTypeGray    = 1,
    ICScannerPixelDataTypeRGB     = 2,
    ICScannerPixelDataTypePalette = 3,
    ICScannerPixelDataTypeCMY     = 4,
    ICScannerPixelDataTypeCMYK    = 5,
    ICScannerPixelDataTypeYUV     = 6,
    ICScannerPixelDataTypeYUVK    = 7,
    ICScannerPixelDataTypeCIEXYZ  = 8
} IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
  @ICScannerDocumentType
  @abstract Document size types. Corresponds to "ICAP_SUPPORTEDSIZES" used by the Image Catpure scanner modules. Also refer to TWAIN 1.9 Specification, page 9-483.
  @constant ICScannerDocumentTypeDefault This is the platten size. Not valid for scanners without a platten.
  @constant ICScannerDocumentTypeA4             A4,                               210.00 mm x  297.00 mm
  @constant ICScannerDocumentTypeB5             B5/JIS B5,                        182.00 mm x  257.00 mm
  @constant ICScannerDocumentTypeUSLetter       US Letter,        8.5” x 11.0”,   215.90 mm x  279.40 mm
  @constant ICScannerDocumentTypeUSLegal        US Legal,         8.5” x 14.0”,   215.90 mm x  355.60 mm
  @constant ICScannerDocumentTypeA5             A5,                               148.00 mm x  210.00 mm
  @constant ICScannerDocumentTypeISOB4          B4/ISO B4,                        250.00 mm x  353.00 mm
  @constant ICScannerDocumentTypeISOB6          B6/ISO B6,                        125.00 mm x  176.00 mm
  @constant ICScannerDocumentTypeUSLedger       US Ledger,         11” x 17.0”,   279.40 mm x  431.80 mm
  @constant ICScannerDocumentTypeUSExecutive    US Executive,    7.25" x 10.5",   184.15 mm x  266.70 mm
  @constant ICScannerDocumentTypeA3             A3,                               297.00 mm x  420.00 mm
  @constant ICScannerDocumentTypeISOB3          B3/ISO B3,                        353.00 mm x  500.00 mm
  @constant ICScannerDocumentTypeA6             A6,                               105.00 mm x  148.00 mm
  @constant ICScannerDocumentTypeC4             C4,                               229.00 mm x  324.00 mm
  @constant ICScannerDocumentTypeC5             C5,                               162.00 mm x  229.00 mm
  @constant ICScannerDocumentTypeC6             C6,                               114.00 mm x  162.00 mm
  @constant ICScannerDocumentType4A0            4A0,                             1682.00 mm x 2378.00 mm
  @constant ICScannerDocumentType2A0            2A0,                             1189.00 mm x 1682.00 mm
  @constant ICScannerDocumentTypeA0             A0,                               841.00 mm x 1189.00 mm
  @constant ICScannerDocumentTypeA1             A1,                               594.00 mm x  841.00 mm
  @constant ICScannerDocumentTypeA2             A2,                               420.00 mm x  594.00 mm
  @constant ICScannerDocumentTypeA7             A7,                                74.00 mm x  105.00 mm
  @constant ICScannerDocumentTypeA8             A8,                                52.00 mm x   74.00 mm
  @constant ICScannerDocumentTypeA9             A9,                                37.00 mm x   52.00 mm
  @constant ICScannerDocumentType10             A10,                               26.00 mm x   37.00 mm
  @constant ICScannerDocumentTypeISOB0          ISO B0,                          1000.00 mm x 1414.00 mm
  @constant ICScannerDocumentTypeISOB1          ISO B1,                           707.00 mm x 1000.00 mm
  @constant ICScannerDocumentTypeISOB2          ISO B2,                           500.00 mm x  707.00 mm
  @constant ICScannerDocumentTypeISOB5          ISO B5,                           176.00 mm x  250.00 mm
  @constant ICScannerDocumentTypeISOB7          ISO B7,                            88.00 mm x  125.00 mm
  @constant ICScannerDocumentTypeISOB8          ISO B8,                            62.00 mm x   88.00 mm
  @constant ICScannerDocumentTypeISOB9          ISO B9,                            44.00 mm x   62.00 mm
  @constant ICScannerDocumentTypeISOB10         ISO B10,                           31.00 mm x   44.00 mm
  @constant ICScannerDocumentTypeJISB0          JIS B0,                          1030.00 mm x 1456.00 mm
  @constant ICScannerDocumentTypeJISB1          JIS B1,                           728.00 mm x 1030.00 mm
  @constant ICScannerDocumentTypeJISB2          JIS B2,                           515.00 mm x  728.00 mm
  @constant ICScannerDocumentTypeJISB3          JIS B3,                           364.00 mm x  515.00 mm
  @constant ICScannerDocumentTypeJISB4          JIS B4,                           257.00 mm x  364.00 mm
  @constant ICScannerDocumentTypeJISB6          JIS B6,                           128.00 mm x  182.00 mm
  @constant ICScannerDocumentTypeJISB7          JIS B7,                            91.00 mm x  128.00 mm
  @constant ICScannerDocumentTypeJISB8          JIS B8,                            64.00 mm x   91.00 mm
  @constant ICScannerDocumentTypeJISB9          JIS B9,                            45.00 mm x   64.00 mm
  @constant ICScannerDocumentTypeJISB10         JIS B10,                           32.00 mm x   45.00 mm
  @constant ICScannerDocumentTypeC0             C0,                               917.00 mm x 1297.00 mm
  @constant ICScannerDocumentTypeC1             C1,                               648.00 mm x  917.00 mm
  @constant ICScannerDocumentTypeC2             C2,                               458.00 mm x  648.00 mm
  @constant ICScannerDocumentTypeC3             C3,                               324.00 mm x  458.00 mm
  @constant ICScannerDocumentTypeC7             C7,                                81.00 mm x  114.00 mm
  @constant ICScannerDocumentTypeC8             C8,                                57.00 mm x   81.00 mm
  @constant ICScannerDocumentTypeC9             C9,                                40.00 mm x   57.00 mm
  @constant ICScannerDocumentTypeC10            C10,                               28.00 mm x   40.00 mm
  @constant ICScannerDocumentTypeUSStatement    US Statement,     5.5” x  8.5”,   139.70 mm x  215.90 mm
  @constant ICScannerDocumentTypeBusinessCard   Business Card,                     90.00 mm x   55.00 mm

  @constant ICScannerDocumentTypeE              Japanese E,      3.25" x 4.75"     82.55 mm x  120.65 mm      11:16
  @constant ICScannerDocumentType3R             3R,              3.5"  x 5"        88.90 mm x  127.00 mm       7:10
  @constant ICScannerDocumentType4R             4R,              4"    x 6"       101.60 mm x  152.40 mm       2:3
  @constant ICScannerDocumentType5R             5R,              5"    x 7"       127.00 mm x  177.80 mm       5:7
  @constant ICScannerDocumentType6R             6R,              6"    x 8"       152.40 mm x  203.20 mm       3:4
  @constant ICScannerDocumentType8R             8R,              8"    x 10"      203.20 mm x  254.00 mm       4:5
  @constant ICScannerDocumentTypeS8R            S8R              8"    x 12"      203.20 mm x  304.80 mm       2:3
  @constant ICScannerDocumentType10R            10R,             10"   x 12"      254.00 mm x  304.80 mm       5:6
  @constant ICScannerDocumentTypeS10R           S10R,            10"   x 15"      254.00 mm x  381.00 mm       2:3
  @constant ICScannerDocumentType11R            11R,             11"   x 14"      279.40 mm x  355.60 mm      11:14
  @constant ICScannerDocumentType12R            12R,             12"   x 15"      304.80 mm x  381.00 mm       4:5
  @constant ICScannerDocumentTypeS12R           S12R,            12"   x 18"      304.80 mm x  457.20 mm       2:3
  @constant ICScannerDocumentTypeS12R           S12R,            12"   x 18"      304.80 mm x  457.20 mm       2:3

  @constant ICScannerDocumentType110            Instamatic 110,                    13.00 mm x   17.00 mm
  @constant ICScannerDocumentTypeAPSH           APS High Definition,               30.20 mm x   16.70 mm
  @constant ICScannerDocumentTypeAPSC           APS Classic,                       25.10 mm x   16.70 mm
  @constant ICScannerDocumentTypeAPSP           APS Panoramic,                     30.20 mm x    9.50 mm
  @constant ICScannerDocumentType135            Standard 35 mm,                    36.00 mm x   24.00 mm
  @constant ICScannerDocumentTypeMF             Medium Format,                     60.00 mm x   60.00 mm
  @constant ICScannerDocumentTypeLF             Large Format,                     100.00 mm x  120.00 mm
*/

typedef NS_ENUM(NSUInteger, ICScannerDocumentType)
{
    ICScannerDocumentTypeDefault      = 0,
    ICScannerDocumentTypeA4           = 1,
    ICScannerDocumentTypeB5           = 2,
    ICScannerDocumentTypeUSLetter     = 3,
    ICScannerDocumentTypeUSLegal      = 4,
    ICScannerDocumentTypeA5           = 5,
    ICScannerDocumentTypeISOB4        = 6,
    ICScannerDocumentTypeISOB6        = 7,
    ICScannerDocumentTypeUSLedger     = 9,
    ICScannerDocumentTypeUSExecutive  = 10,
    ICScannerDocumentTypeA3           = 11,
    ICScannerDocumentTypeISOB3        = 12,
    ICScannerDocumentTypeA6           = 13,
    ICScannerDocumentTypeC4           = 14,
    ICScannerDocumentTypeC5           = 15,
    ICScannerDocumentTypeC6           = 16,
    ICScannerDocumentType4A0          = 17,
    ICScannerDocumentType2A0          = 18,
    ICScannerDocumentTypeA0           = 19,
    ICScannerDocumentTypeA1           = 20,
    ICScannerDocumentTypeA2           = 21,
    ICScannerDocumentTypeA7           = 22,
    ICScannerDocumentTypeA8           = 23,
    ICScannerDocumentTypeA9           = 24,
    ICScannerDocumentType10           = 25,
    ICScannerDocumentTypeISOB0        = 26,
    ICScannerDocumentTypeISOB1        = 27,
    ICScannerDocumentTypeISOB2        = 28,
    ICScannerDocumentTypeISOB5        = 29,
    ICScannerDocumentTypeISOB7        = 30,
    ICScannerDocumentTypeISOB8        = 31,
    ICScannerDocumentTypeISOB9        = 32,
    ICScannerDocumentTypeISOB10       = 33,
    ICScannerDocumentTypeJISB0        = 34,
    ICScannerDocumentTypeJISB1        = 35,
    ICScannerDocumentTypeJISB2        = 36,
    ICScannerDocumentTypeJISB3        = 37,
    ICScannerDocumentTypeJISB4        = 38,
    ICScannerDocumentTypeJISB6        = 39,
    ICScannerDocumentTypeJISB7        = 40,
    ICScannerDocumentTypeJISB8        = 41,
    ICScannerDocumentTypeJISB9        = 42,
    ICScannerDocumentTypeJISB10       = 43,
    ICScannerDocumentTypeC0           = 44,
    ICScannerDocumentTypeC1           = 45,
    ICScannerDocumentTypeC2           = 46,
    ICScannerDocumentTypeC3           = 47,
    ICScannerDocumentTypeC7           = 48,
    ICScannerDocumentTypeC8           = 49,
    ICScannerDocumentTypeC9           = 50,
    ICScannerDocumentTypeC10          = 51,
    ICScannerDocumentTypeUSStatement  = 52,
    ICScannerDocumentTypeBusinessCard = 53,
    
    ICScannerDocumentTypeE            = 60,
    ICScannerDocumentType3R           = 61,
    ICScannerDocumentType4R           = 62,
    ICScannerDocumentType5R           = 63,
    ICScannerDocumentType6R           = 64,
    ICScannerDocumentType8R           = 65,
    ICScannerDocumentTypeS8R          = 66,
    ICScannerDocumentType10R          = 67,
    ICScannerDocumentTypeS10R         = 68,
    ICScannerDocumentType11R          = 69,
    ICScannerDocumentType12R          = 70,
    ICScannerDocumentTypeS12R         = 71,
    ICScannerDocumentType110          = 72,
    ICScannerDocumentTypeAPSH         = 73,
    ICScannerDocumentTypeAPSC         = 74,
    ICScannerDocumentTypeAPSP         = 75,
    ICScannerDocumentType135          = 76,
    ICScannerDocumentTypeMF           = 77,
    ICScannerDocumentTypeLF           = 78
} IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
  @ICScannerFunctionalUnitState
  @abstract A flag to indicate the scanner functional unit's state
  @constant ICScannerStateReady The scanner functional unit is ready for operation.
  @constant ICScannerStateScanInProgress The scanner functional unit is performing a scan.
  @constant ICScannerStateOverviewScanInProgress The scanner functional unit is performing an overview scan.
*/

typedef NS_ENUM(NSUInteger, ICScannerFunctionalUnitState)
{
    ICScannerFunctionalUnitStateReady                  = (1 << 0),
    ICScannerFunctionalUnitStateScanInProgress         = (1 << 1),
    ICScannerFunctionalUnitStateOverviewScanInProgress = (1 << 2)
}IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
  @ICScannerFeatureType
  @abstract Scanner Feature Types
  @constant ICScannerFeatureTypeEnumeration This feature can have one of several discrete values, strings or numbers.
  @constant ICScannerFeatureTypeRange This value of this feature lies within a range.
  @constant ICScannerFeatureTypeBoolean The value of this feature can be YES or NO.
*/

typedef NS_ENUM(NSUInteger, ICScannerFeatureType)
{
    ICScannerFeatureTypeEnumeration = 0,
    ICScannerFeatureTypeRange       = 1,
    ICScannerFeatureTypeBoolean     = 2,
    ICScannerFeatureTypeTemplate    = 3
}IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

//------------------------------------------------------------------------------------------------------------- ICScannerFeature
/*!
  @class ICScannerFeature
  @abstract ICScannerFeature class is an abstract base class used to describe a scanner feature. ImageCaptureCore defines three concrete subclasses of ICScannerFeature: ICScannerFeatureEnumeration, ICScannerFeatureRange and ICScannerFeatureBoolean.
  @discussion The scanner functional units may have one or more instances of these classes to allow users to choose scanner-specific settings or operations before performing a scan.
*/

IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios)
@interface ICScannerFeature : NSObject
{
@private
    id _sfProps;
}

/*!
  @property type
  @abstract ￼Scanner feature type.
*/
@property (readonly) ICScannerFeatureType type;

/*!
  @property internalName
  @abstract ￼The internal name of this feature.
*/
@property (readonly, nullable) NSString* internalName;

/*!
  @property humanReadableName
  @abstract The human readable name of this feature.
*/
@property (readonly, nullable) NSString* humanReadableName;

/*!
  @property tooltip
  @abstract ￼Tooltip text describing the feature.
*/
@property (readonly, nullable) NSString* tooltip;
@end

    //-------------------------------------------------------------------------------------------------- ICScannerFeatureEnumeration
    /*!
  @class ICScannerFeatureEnumeration
  @abstract ICScannerFeatureEnumeration object is used to represent a feature of a scanner functional unit that can have one of several discrete values.
*/

NS_ASSUME_NONNULL_BEGIN

IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios)
@interface ICScannerFeatureEnumeration : ICScannerFeature
{
@private
    id _evProps;
}

/*!
  @property currentValue
  @abstract The current value. The current value can be set to one of the possible values in the "values" property below￼.
*/
@property (assign) id currentValue;

/*!
  @property defaultValue
  @abstract ￼The default value. The default value can be set to one of the possible values in the "values" property below.
*/
@property (readonly) id defaultValue;

/*!
  @property values
  @abstract An array of possible values. All items in this array must be of same type￼.
*/
@property (readonly) NSArray<NSNumber*>* values;

/*!
  @property menuItemLabels
  @abstract ￼The human readable menu item labels to be used in a menu to allow the user to select the current value from an array of possible values.
*/
@property (readonly) NSArray<NSString*>* menuItemLabels;

/*!
  @property menuItemLabelsTooltips
  @abstract ￼Tooltip text associated with the menu items.
*/
@property (readonly) NSArray<NSString*>* menuItemLabelsTooltips;
@end

    //-------------------------------------------------------------------------------------------------------- ICScannerFeatureRange
    /*!
  @class ICScannerFeatureRange
  @abstract ICScannerFeatureRange object is used to represent a property of a scanner functional unit whose value lies within a range.
*/

IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios)
@interface ICScannerFeatureRange : ICScannerFeature
{
@private
    id _rvProps;
}

/*!
  @property currentValue
  @abstract ￼The current value. Attempting to set the current value to a value that is not coincident with a step will result in a value corresponding to the nearest step being assigned to the current value.
*/
@property (assign) CGFloat currentValue;

/*!
  @property defaultValue
  @abstract The default value￼. Attempting to set the default value to a value that is not coincident with a step will result in a value corresponding to the nearest step being assigned to the default value.
*/
@property (readonly) CGFloat defaultValue;

/*!
  @property minValue
  @abstract The minimum value.
*/
@property (readonly) CGFloat minValue;

/*!
  @property maxValue
  @abstract ￼The maximum value.
*/
@property (readonly) CGFloat maxValue;

/*!
  @property stepSize
  @abstract ￼The step size.
*/
@property (readonly) CGFloat stepSize;
@end

    //----------------------------------------------------------------------------------------------------- ICScannerFeatureBoolean
    /*!
  @class ICScannerFeatureBoolean
  @abstract ICScannerFeatureBoolean object is used to represent a property of a scanner functional unit whose value can be YES or NO.
*/

IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios)
@interface ICScannerFeatureBoolean : ICScannerFeature
{
@private
    id _bvProps;
}

/*!
  @property value
  @abstract ￼The value of this feature.
*/
@property (readwrite) BOOL value;
@end

    //---------------------------------------------------------------------------------------------------- ICScannerFeatureTemplate
    /*!
  @class ICScannerFeatureTemplate
  @abstract ICScannerFeatureTemplate object is used to define a group of one or more rectangular scan areas that can be used with a scanner functional unit.
*/

    IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios) @interface ICScannerFeatureTemplate : ICScannerFeature
{
@private
    id _tvProps;
}

@property (readonly) NSArray<NSMutableArray*>* targets;
@end

    //------------------------------------------------------------------------------------------------------ ICScannerFunctionalUnit
    /*!
  @class ICScannerFunctionalUnit
  @abstract ICScannerFunctionalUnit is an abstract class that represents a scanner functiona unit. ImageCaptureCore defines three concrete subclasses of ICScannerFunctionalUnit: ICScannerFunctionalUnitFlatbed, ICScannerFunctionalUnitPositiveTransparency, ICScannerFunctionalUnitNegativeTransparency and ICScannerFunctionalUnitDocumentFeeder. ICScannerDevice creates instances of these concrete subclasses.
*/

    IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios) @interface ICScannerFunctionalUnit : NSObject
{
@private
    id _fuProps;
}

/*!
  @property type
  @abstract ￼Functional unit type.
*/
@property (readonly) ICScannerFunctionalUnitType type;

/*!
  @property pixelDataType
  @abstract ￼The pixel data type.
*/
@property (readwrite) ICScannerPixelDataType pixelDataType;

/*!
  @property supportedBitDepths
  @abstract ￼Supported bit depths. The values in this set are valid values defined by ICScannerBitDepth.
*/
@property (readonly) NSIndexSet* supportedBitDepths;

/*!
  @property bitDepth
  @abstract ￼The bit depth to use when performing the final scan. This will always be one of the supported bit depths.
*/
@property (readwrite) ICScannerBitDepth bitDepth;

/*!
  @property supportedMeasurementUnits
  @abstract ￼Supported measurement units. The values in this set are valid values defined by ICScannerMeasurementUnit.
*/
@property (readonly) NSIndexSet* supportedMeasurementUnits;

/*!
  @property measurementUnit
  @abstract ￼Current measurement unit. This will always be one of the supported measurement units.
*/
@property (readwrite) ICScannerMeasurementUnit measurementUnit;

/*!
  @property supportedResolutions
  @abstract ￼Supported scan resolutions in DPI.
*/
@property (readonly) NSIndexSet* supportedResolutions;

/*!
  @property preferredResolutions
  @abstract ￼Preferred scan resolutions in DPI.
*/
@property (readonly) NSIndexSet* preferredResolutions;

/*!
  @property resolution
  @abstract ￼Current scan resolution. This will always be one of the supported resolution values.
*/
@property (readwrite) NSUInteger resolution;

/*!
  @property nativeXResolution
  @abstract ￼Optical resolution along the X axis.
*/
@property (readonly) NSUInteger nativeXResolution;

/*!
  @property nativeYResolution
  @abstract ￼Optical resolution along the Y axis.
*/
@property (readonly) NSUInteger nativeYResolution;

/*!
  @property supportedScaleFactors
  @abstract ￼Supported scale factors in percentage.
*/
@property (readonly) NSIndexSet* supportedScaleFactors;

/*!
  @property preferredScaleFactors
  @abstract ￼Preferred scale factors in percentage.
*/
@property (readonly) NSIndexSet* preferredScaleFactors;

/*!
  @property scaleFactor
  @abstract ￼Current scale factor. This will always be one of the supported scale factor values.
*/
@property (readwrite) NSUInteger scaleFactor;

/*!
  @property templates
  @abstract An array of objects of type ICScannerFeatureTemplate.
*/
@property (readonly) NSArray<ICScannerFeatureTemplate*>* templates;

/*!
  @property vendorFeatures
  @abstract An array of objects of type ICScannerFeature.
*/
@property (readonly, nullable) NSArray<ICScannerFeature*>* vendorFeatures;

/*!
  @property physicalSize
  @abstract ￼Physical size of the scan area in current measurement unit.
*/
@property (readonly) ICSize physicalSize;

/*!
  @property scanArea
  @abstract ￼This property along with scanAreaOrientation describes the area to be scanned.
*/
@property (readwrite) ICRect scanArea;

/*!
  @property scanAreaOrientation
  @abstract ￼Desired orientation of the scan area. This property along with scanArea describes the area to be scanned.
  @discussion This property is set to ICEXIFOrientation1 initially. This property is not used by the ICScannerFunctionalUnitDocumentFeeder subclass.
*/
@property (readwrite) ICEXIFOrientationType scanAreaOrientation;

/*!
  @property acceptsThresholdForBlackAndWhiteScanning
  @abstract ￼Indicates if this functional unit accepts threshold value to be used when performing a scan in black & white.
*/
@property (readonly) BOOL acceptsThresholdForBlackAndWhiteScanning;

/*!
  @property usesThresholdForBlackAndWhiteScanning
  @abstract ￼Indicates if this functional unit uses threshold value to be used when performing a scan in black & white.
*/
@property (readwrite) BOOL usesThresholdForBlackAndWhiteScanning;

/*!
  @property defaultThresholdForBlackAndWhiteScanning
  @abstract ￼Default threshold value used when performing a scan in black & white. This value is from 0 to 255.
*/
@property (readonly) unsigned char defaultThresholdForBlackAndWhiteScanning;

/*!
  @property thresholdForBlackAndWhiteScanning
  @abstract ￼Threshold value to be used when performing a scan in black & white. This value should be from 0 to 255.
*/
@property (readwrite) unsigned char thresholdForBlackAndWhiteScanning;

/*!
  @property state
  @abstract ￼Indicates the current state of the functional unit.
*/
@property (readonly) ICScannerFunctionalUnitState state;

/*!
  @property scanInProgress
  @abstract ￼Indicates if a scan is in progress.
*/
@property (readonly) BOOL scanInProgress;

/*!
  @property scanProgressPercentDone
  @abstract ￼Indicates percentage of scan completed.
*/
@property (readonly) CGFloat scanProgressPercentDone;

/*!
  @property canPerformOverviewScan
  @abstract ￼Indicates if this functional unit can perfrom an overview scan. Not all functional units can perform an overview scan. For example, a document feeder or a sheet feeder unit cannot perform an overview scan.
*/
@property (readonly) BOOL canPerformOverviewScan;

/*!
  @property overviewScanInProgress
  @abstract ￼Indicates if an overview scan is in progress.
*/
@property (readonly) BOOL overviewScanInProgress;

/*!
  @property overviewImage
  @abstract ￼Overview scan image. This property will be NULL for functional units that do not support overview scans.
*/
@property (readonly, nullable) CGImageRef overviewImage;

/*!
  @property overviewResolution
  @abstract ￼Overview image resolution. Value assigned to this will be contrained by resolutions allowed by the device.
*/
@property (readwrite) NSUInteger overviewResolution;

@end

    //----------------------------------------------------------------------------------------------- ICScannerFunctionalUnitFlatbed
    /*!
  @class ICScannerFunctionalUnitFlatbed
  @abstract ICScannerFunctionalUnitFlatbed is a concrete subclass of ICScannerFunctionalUnit class. ICScannerDevice creates instances of this class.
  @discussion This represents the flatbed  unit on the scanner.
*/

IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios)
@interface ICScannerFunctionalUnitFlatbed : ICScannerFunctionalUnit
{
@private
    id _fbProps;
}

/*!
  @property supportedDocumentTypes
  @abstract ￼Supported document types. The values in this set are valid values defined by ICScannerDocumentType.
*/
@property (readonly, nonnull) NSIndexSet* supportedDocumentTypes;

/*!
  @property documentType
  @abstract ￼Current document type. This will always be one of the supported document types.
*/
@property (readwrite) ICScannerDocumentType documentType;

/*!
  @property documentSize
  @abstract ￼Document size of the current document type expressed in current measurement unit.
*/
@property (readonly) ICSize documentSize;

@end

    //---------------------------------------------------------------------------------- ICScannerFunctionalUnitPositiveTransparency
    /*!
  @class ICScannerFunctionalUnitPositiveTransparency
  @abstract ICScannerFunctionalUnitPositiveTransparency is a concrete subclass of ICScannerFunctionalUnit class. ICScannerDevice creates instances of this class.
  @discussion This represents the transparency unit on the scanner for scanning postives
*/

IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios)
@interface ICScannerFunctionalUnitPositiveTransparency : ICScannerFunctionalUnit
{
@private
    id _ptrProps;
}

/*!
  @property supportedDocumentTypes
  @abstract ￼Supported document types. The values in this set are valid values defined by ICScannerDocumentType.
*/
@property (readonly) NSIndexSet* supportedDocumentTypes;

/*!
  @property documentType
  @abstract ￼Current document type. This will always be one of the supported document types.
*/
@property (readwrite) ICScannerDocumentType documentType;

/*!
  @property documentSize
  @abstract ￼Document size of the current document type expressed in current measurement unit.
*/
@property (readonly) ICSize documentSize;

@end

    //---------------------------------------------------------------------------------- ICScannerFunctionalUnitNegativeTransparency
    /*!
  @class ICScannerFunctionalUnitNegativeTransparency
  @abstract ICScannerFunctionalUnitNegativeTransparency is a concrete subclass of ICScannerFunctionalUnit class. ICScannerDevice creates instances of this class.
  @discussion This represents the transparency unit on the scanner for scanning negatives.
*/

IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios)
@interface ICScannerFunctionalUnitNegativeTransparency : ICScannerFunctionalUnit
{
@private
    id _ntrProps;
}

/*!
  @property supportedDocumentTypes
  @abstract ￼Supported document types. The values in this set are valid values defined by ICScannerDocumentType.
*/
@property (readonly) NSIndexSet* supportedDocumentTypes;

/*!
  @property documentType
  @abstract ￼Current document type. This will always be one of the supported document types.
*/
@property (readwrite) ICScannerDocumentType documentType;

/*!
  @property documentSize
  @abstract ￼Document size of the current document type expressed in current measurement unit.
*/
@property (readonly) ICSize documentSize;

@end

    //---------------------------------------------------------------------------------------- ICScannerFunctionalUnitDocumentFeeder
    /*!
  @class ICScannerFunctionalUnitDocumentFeeder
  @abstract ICScannerFunctionalUnitDocumentFeeder is a concrete subclass of ICScannerFunctionalUnit class. ICScannerDevice creates instances of this class.
  @discussion This represents the document feeder unit on the scanner.
*/

IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios)
@interface ICScannerFunctionalUnitDocumentFeeder : ICScannerFunctionalUnit
{
@private
    id _dfProps;
}

/*!
  @property supportedDocumentTypes
  @abstract ￼Supported document types. The values in this set are valid values defined by ICScannerDocumentType.
*/
@property (readonly) NSIndexSet* supportedDocumentTypes;

/*!
  @property documentType
  @abstract ￼Current document type. This will always be one of the supported document types.
*/
@property (readwrite) ICScannerDocumentType documentType;

/*!
  @property documentSize
  @abstract ￼Document size of the current document type expressed in current measurement unit.
*/
@property (readonly) ICSize documentSize;

/*!
  @property supportsDuplexScanning
  @abstract ￼Indicates whether duplex scanning is supported.
*/
@property (readonly) BOOL supportsDuplexScanning;

/*!
  @property duplexScanningEnabled
  @abstract ￼Indicates whether duplex scanning is enabled.
*/
@property (readwrite) BOOL duplexScanningEnabled;

/*!
  @property documentLoaded
  @abstract ￼Indicates whether the feeder has documents to scan.
  @discussion This value will change when the document is loaded or removed from the feeder, if the scanner module has the capability to detect this state.
*/
@property (readonly) BOOL documentLoaded;

/*!
  @property oddPageOrientation
  @abstract ￼Desired orientation of the odd pages of the scanned document.
  @discussion This property is set to ICEXIFOrientation1 initially.
*/
@property (readwrite) ICEXIFOrientationType oddPageOrientation;

/*!
  @property evenPageOrientation
  @abstract ￼Desired orientation of the even pages of the scanned document.
  @discussion This property is set to ICEXIFOrientation1 initially.
*/
@property (readwrite) ICEXIFOrientationType evenPageOrientation;

/*!
 @property reverseFeederPageOrder
 @abstract ￼Indicates whether the document feeder reads pages from back to front.
 
 */
@property (readonly) BOOL reverseFeederPageOrder;

NS_ASSUME_NONNULL_END

@end

//------------------------------------------------------------------------------------------------------------------------------
