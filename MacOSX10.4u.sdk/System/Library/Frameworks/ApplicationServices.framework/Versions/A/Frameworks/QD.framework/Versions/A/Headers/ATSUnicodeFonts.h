/*
     File:       QD/ATSUnicodeFonts.h
 
     Contains:   ATSUI font handling functions.
 
     Version:    Quickdraw-192.24~58
 
     Copyright:  © 2003-2006 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __ATSUNICODEFONTS__
#define __ATSUNICODEFONTS__

#ifndef __ATSUNICODETYPES__
#include <QD/ATSUnicodeTypes.h>
#endif


/* ---------------------------------------------------------------------------- */
/*  Font features                                                               */
/* ---------------------------------------------------------------------------- */

#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ATSUSetFontFeatures()
 *  
 *  Summary:
 *    Sets font features in a style object.
 *  
 *  Discussion:
 *    This function enables you to set multiple font features for a
 *    style object. Any unset font features retain their font-defined
 *    default values. To set style attributes and font variations for a
 *    style object, call the functions ATSUSetAttributes and
 *    ATSUSetVariations, respectively. The constants that represent
 *    font feature types are defined in the header file
 *    SFNTLayoutTypes.h. When you use ATSUI to access and set font
 *    features, you must use the constants defined in this header file,
 *    which are described in "Inside Mac OS X: Rendering Unicode Text
 *    With ATSUI". As feature types can be added at any time, you
 *    should check Apple's font feature registry website for the most
 *    up-to-date list of font feature types and selectors:
 *    http://developer.apple.com/fonts/Registry/index.html.
 *  
 *  Parameters:
 *    
 *    iStyle:
 *      The style object for which to set font features.
 *    
 *    iFeatureCount:
 *      The number of font features to set. This value should
 *      correspond to the number of elements in the iType and iSelector
 *      arrays.
 *    
 *    iType:
 *      An array of feature types. Each element in the array must
 *      contain a valid feature type that corresponds to a feature
 *      selector in the iSelector array. To obtain the valid feature
 *      types for a font, call the function ATSUGetFontFeatureTypes .
 *    
 *    iSelector:
 *      An array of feature selectors. Each element in the array must
 *      contain a valid feature selector that corresponds to a feature
 *      type in the iType array. To obtain the valid feature selectors
 *      for a font, call the function ATSUGetFontFeatureSelectors .
 *  
 *  Result:
 *    On success, noErr is returned. See MacErrors.h for possible error
 *    codes.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUSetFontFeatures(
  ATSUStyle                       iStyle,
  ItemCount                       iFeatureCount,
  const ATSUFontFeatureType       iType[],
  const ATSUFontFeatureSelector   iSelector[])                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUGetFontFeature()
 *  
 *  Summary:
 *    Obtains the font feature corresponding to an index into an array
 *    of font features for a style object.
 *  
 *  Discussion:
 *    You might typically call ATSUGetFontFeature if you need to obtain
 *    one previously set feature after another within your program's
 *    processing loop. To obtain all previously set font features for a
 *    given style object, you can call the function
 *    ATSUGetAllFontFeatures. Before calling ATSUGetFontFeature, you
 *    should call the function ATSUGetAllFontFeatures to obtain a count
 *    of the font features that are set in the style object. You can
 *    then pass the index for the feature whose setting you want to
 *    obtain in the iTag and iMaximumValueSize parameters of
 *    ATSUGetFontFeature.
 *  
 *  Parameters:
 *    
 *    iStyle:
 *      The style you wish to obtain font feature information for.
 *    
 *    iFeatureIndex:
 *      An index into the array of font features for the style object.
 *      This index identifies the font feature to examine. Because this
 *      index is zero-based, you must pass a value between 0 and one
 *      less than the value produced in the oActualFeatureCount
 *      parameter of the function ATSUGetAllFontFeatures.
 *    
 *    oFeatureType:
 *      On return, the value identifies the font feature type
 *      corresponding to the index passed in the iFeatureIndex
 *      parameter. You must allocate space for ATSUGetFontFeature to
 *      store this value.
 *    
 *    oFeatureSelector:
 *      On return, the value identifies the font feature selector that
 *      corresponds to the feature type produced in the oFeatureType
 *      parameter. ou must allocate space for ATSUGetFontFeature to
 *      store this value.
 *  
 *  Result:
 *    On success, noErr is returned. See MacErrors.h for possible error
 *    codes.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUGetFontFeature(
  ATSUStyle                  iStyle,
  ItemCount                  iFeatureIndex,
  ATSUFontFeatureType *      oFeatureType,
  ATSUFontFeatureSelector *  oFeatureSelector)                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUGetAllFontFeatures()
 *  
 *  Summary:
 *    Obtains the font features of a style object that are not at
 *    default settings.
 *  
 *  Discussion:
 *    The ATSUGetAllFontFeatures function obtains all of a style
 *    object's font features that are not at default settings. Font
 *    features are grouped into categories called feature types, within
 *    which individual feature selectors define particular feature
 *    settings. The arrays produced by ATSUGetAllFontFeatures contain
 *    constants identifying the object's font types and their
 *    corresponding font selectors. Typically you use the function
 *    ATSUGetAllFontFeatures by calling it twice, as follows: (1) Pass
 *    a reference to the style object to examine in the iStyle
 *    parameter, a valid pointer to an ItemCount value in the
 *    oActualFeatureCount parameter, NULL for the oFeatureType and
 *    oFeatureSelector parameters, and 0 for the iMaximumFeatureCount
 *    parameter. ATSUGetAllFontFeatures returns the size in the
 *    oActualFeatureCount parameter to use for the feature type and
 *    selector arrays. (2) Allocate enough space for arrays of the
 *    returned size, then call ATSUGetAllFontFeatures again, passing a
 *    pointer to the arrays in the oFeatureType and oFeatureSelector
 *    parameters. On return, the arrays contain the font feature types
 *    and selectors, respectively, for the style object.
 *  
 *  Parameters:
 *    
 *    iStyle:
 *      The style for which you wish to obtain font feature information.
 *    
 *    iMaximumFeatureCount:
 *      The maximum number of feature types and selectors to obtain for
 *      the style object. Typically, this is equivalent to the number
 *      of ATSUFontFeatureType and ATSUFontFeatureSelector values for
 *      which you have allocated memory in the oFeatureType and
 *      oFeatureSelector parameters, respectively. To determine this
 *      value, see the Discussion.
 *    
 *    oFeatureType:
 *      On return, the array contains constants identifying each type
 *      of font feature that is at a nondefault setting in the style
 *      object. If you are uncertain of how much memory to allocate for
 *      this array, see the Discussion.
 *    
 *    oFeatureSelector:
 *      On return, the array contains constants identifying the feature
 *      selectors that are at nondefault settings in the style object.
 *      Each selector determines the setting for a corresponding
 *      feature type produced in the oFeatureType parameter. If you are
 *      uncertain of how much memory to allocate for this array, see
 *      the Discussion.
 *    
 *    oActualFeatureCount:
 *      On return, the value specifies the actual number of font
 *      feature types and selectors in the style object. This may be
 *      greater than the value you specified in the
 *      iMaximumFeatureCount parameter.
 *  
 *  Result:
 *    On success, noErr is returned. See MacErrors.h for possible error
 *    codes.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUGetAllFontFeatures(
  ATSUStyle                 iStyle,
  ItemCount                 iMaximumFeatureCount,
  ATSUFontFeatureType       oFeatureType[],             /* can be NULL */
  ATSUFontFeatureSelector   oFeatureSelector[],         /* can be NULL */
  ItemCount *               oActualFeatureCount)        /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUClearFontFeatures()
 *  
 *  Summary:
 *    Restores default settings to the specified font features of a
 *    style object.
 *  
 *  Discussion:
 *    This function removes those font features that are identified by
 *    the feature selector and type constants in the iSelector and
 *    iType arrays and replaces them with their font-defined default
 *    values. Note that if you pass ATSUClearFontFeatures a font
 *    feature and selector that are already at default settings, the
 *    function does not return an error. To restore default font
 *    variations to a style object, call the function
 *    ATSUClearFontVariations. To restore default style attributes to a
 *    style object, call ATSUClearAttributes. To restore all default
 *    settings to a style object (for font features, variations, and
 *    style attributes), call the function ATSUClearStyle.
 *  
 *  Parameters:
 *    
 *    iStyle:
 *      A style whose font features you wish to clear.
 *    
 *    iFeatureCount:
 *      The number of font features to restore to default settings.
 *      This value should correspond to the number of elements in the
 *      iType and iSelector arrays. To restore default settings to all
 *      the font features in the specified style object, pass the
 *      constant kATSUClearAll in this parameter. In this case, the
 *      values in the iType and iSelector parameters are ignored.
 *    
 *    iType:
 *      An array of feature types. Each value should identify a font
 *      feature to restore to its default setting. To obtain all
 *      previously set font features for a given style object, you can
 *      call the function ATSUGetAllFontFeatures. You may pass NULL for
 *      this parameter if you are passing kATSUClearAll for the
 *      iFeatureCount parameter.
 *    
 *    iSelector:
 *      An array of feature selectors. Each element in the array must
 *      contain a valid feature selector corresponding to a font
 *      feature you provide in the iType parameter. To obtain all
 *      previously set feature selectors for a given style object, you
 *      can call the function ATSUGetAllFontFeatures. You may pass NULL
 *      for this parameter if you are passing kATSUClearAll for the
 *      iFeatureCount parameter.
 *  
 *  Result:
 *    On success, noErr is returned. See MacErrors.h for possible error
 *    codes.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUClearFontFeatures(
  ATSUStyle                       iStyle,
  ItemCount                       iFeatureCount,
  const ATSUFontFeatureType       iType[],             /* can be NULL */
  const ATSUFontFeatureSelector   iSelector[])         /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* ---------------------------------------------------------------------------- */
/*  Font variations                                                             */
/* ---------------------------------------------------------------------------- */
/*
 *  ATSUSetVariations()
 *  
 *  Summary:
 *    Sets font variation axes and values in a style object.
 *  
 *  Discussion:
 *    If you supply font variation axes and values to the
 *    ATSUSetVariations function, you can change the appearance of a
 *    style object's font accordingly. You may specify any number of
 *    variation axes and values in a style object. Any of the font's
 *    variations that you do not set retain their font-defined default
 *    values. You can also use the ATSUSetVariations function to supply
 *    your own value within any variation axes defined for the font.
 *    However, if the font does not support the variation axis you
 *    specify, your custom variation has no visual effect. By calling
 *    the function ATSUGetIndFontVariation, you can obtain a variation
 *    axis and its maximum, minimum, and default values for a font.
 *  
 *  Parameters:
 *    
 *    iStyle:
 *      The style object for which to set font variation values.
 *    
 *    iVariationCount:
 *      The number of font variation values to set. This value should
 *      correspond to the number of elements in the iAxes and iValue
 *      arrays.
 *    
 *    iAxes:
 *      An array of font variation axes. Each element in the array must
 *      represent a valid variation axis tag that corresponds to a
 *      variation value in the iValue array. To obtain a valid
 *      variation axis tag for a font, you can call the functions
 *      ATSUGetIndFontVariation or ATSUGetFontInstance.
 *    
 *    iValue:
 *      An array of font variation values. Each element in the array
 *      must contain a value that is valid for the corresponding
 *      variation axis in the iAxes parameter. You can obtain a font's
 *      maximum, minimum, and default values for a given variation axis
 *      by calling the function ATSUGetIndFontVariation . You can
 *      obtain the font variation axis values for a font instance by
 *      calling ATSUGetFontInstance.
 *  
 *  Result:
 *    On success, noErr is returned. See MacErrors.h for possible error
 *    codes.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUSetVariations(
  ATSUStyle                      iStyle,
  ItemCount                      iVariationCount,
  const ATSUFontVariationAxis    iAxes[],
  const ATSUFontVariationValue   iValue[])                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUGetFontVariationValue()
 *  
 *  Summary:
 *    Obtains the current value for a single font variation axis in a
 *    style object.
 *  
 *  Discussion:
 *    This function obtains the setting for a specified font variation
 *    axis in a style object. You might typically call
 *    ATSUGetFontVariationValue if you need to obtain one previously
 *    set variation axis value after another within your program's
 *    processing loop. To obtain all nondefault font variation axis
 *    values for a given style object, you can call the function
 *    ATSUGetAllFontVariations. Before calling
 *    ATSUGetFontVariationValue, call the function
 *    ATSUGetAllFontVariations to obtain the font variation axes that
 *    are set for the style object.
 *  
 *  Parameters:
 *    
 *    iStyle:
 *      The style for which you want to obtain a variation value.
 *    
 *    iFontVariationAxis:
 *      A tag specifying the style object's variation axis to examine.
 *      You can obtain a list of variation axis tags that are set to
 *      non-default values in a particular style object from the
 *      function ATSUGetAllFontVariations.
 *    
 *    oFontVariationValue:
 *      On return, ATSUGetFontVariationValue produces the currently set
 *      value for the style object's specified variation axis. If this
 *      value has not been set, ATSUGetFontVariationValue produces the
 *      font-defined default value.
 *  
 *  Result:
 *    On success, noErr is returned. See MacErrors.h for possible error
 *    codes.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUGetFontVariationValue(
  ATSUStyle                 iStyle,
  ATSUFontVariationAxis     iFontVariationAxis,
  ATSUFontVariationValue *  oFontVariationValue)              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUGetAllFontVariations()
 *  
 *  Summary:
 *    Obtains a style object's font variation values that are not at
 *    default settings.
 *  
 *  Discussion:
 *    This function obtains all of a style object's font variation axes
 *    that are not at default settings, as well as the current values
 *    for the axes. Typically you use the function
 *    ATSUGetAllFontVariations by calling it twice, as follows: (1)
 *    Pass a reference to the style object to examine in the iStyle
 *    parameter, a pointer to an ItemCount value in the
 *    oActualVariationCount parameter, NULL for the oVariationAxes and
 *    oFontVariationValues parameters, and 0 for the iVariationCount
 *    parameter. ATSUGetAllFontVariations returns the size to use for
 *    the variation axes and value arrays in the oActualVariationCount
 *    parameter. (2) Allocate enough space for arrays of the returned
 *    size, then call ATSUGetAllFontVariations again, passing a pointer
 *    to the arrays in the oVariationAxes and oFontVariationValues
 *    parameters. On return, the arrays contain the font variation axes
 *    and their corresponding values, respectively, for the style
 *    object.
 *  
 *  Parameters:
 *    
 *    iStyle:
 *      A style for which you wish to obtain information about current
 *      variation settings.
 *    
 *    iVariationCount:
 *      The maximum number of font variation values to obtain for the
 *      style object. Typically, this is equivalent to the number of
 *      ATSUFontVariationAxis and ATSUFontVariationValue values for
 *      which you have allocated memory in the oVariationAxes and
 *      oFontVariationValues parameters, respectively. To determine
 *      this value, see the Discussion.
 *    
 *    oVariationAxes:
 *      On return, the array contains the current font variation values
 *      for the font variation axes produced in the oVariationAxes
 *      array. If you are uncertain of how much memory to allocate for
 *      this array, see the Discussion.
 *    
 *    oFontVariationValues:
 *      On return, the value specifies the actual number of nondefault
 *      font variation values in the style object. This may be greater
 *      than the value you passed in the iVariationCount parameter. If
 *      you are uncertain of how much memory to allocate for this
 *      array, see the Discussion.
 *    
 *    oActualVariationCount:
 *      On return, the value specifies the actual number of nondefault
 *      font variation values in the style object. This may be greater
 *      than the value you passed in the iVariationCount parameter.
 *  
 *  Result:
 *    On success, noErr is returned. See MacErrors.h for possible error
 *    codes.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUGetAllFontVariations(
  ATSUStyle                iStyle,
  ItemCount                iVariationCount,
  ATSUFontVariationAxis    oVariationAxes[],            /* can be NULL */
  ATSUFontVariationValue   oFontVariationValues[],      /* can be NULL */
  ItemCount *              oActualVariationCount)       /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUClearFontVariations()
 *  
 *  Summary:
 *    Restores default values to the specified font variation axes of a
 *    style object.
 *  
 *  Discussion:
 *    The ATSUClearFontVariations function removes those font variation
 *    axis values identified by variation axis tags in the iAxis array
 *    and replaces them with their font-defined default values. You can
 *    remove unset font variation values from a style object without a
 *    function error. To restore default font features to a style
 *    object, call the function ATSUClearFontFeatures. To restore
 *    default style attributes, call ATSUClearAttributes. To restore
 *    all default settings to a style object (for font features,
 *    variations, and style attributes), call the function
 *    ATSUClearStyle.
 *  
 *  Parameters:
 *    
 *    iStyle:
 *      The style in which you wish to clear font variation settings.
 *    
 *    iAxisCount:
 *      The number of font variation axes to restore to default
 *      settings. This value should correspond to the number of
 *      elements in the iAxis array. To restore default values to all
 *      the font variation axes in the style object, pass the constant
 *      kATSUClearAll in this parameter. If you pass kATSUClearAll the
 *      value in the iAxis parameter is ignored.
 *    
 *    iAxis:
 *      An array of font variation axes. Each element in the array must
 *      contain a valid tag that corresponds to a font variation axis
 *      to restore to its default setting. You can obtain variation
 *      axis tags for a style object from the function
 *      ATSUGetAllFontVariations. You may pass NULL for this parameter
 *      if you are passing kATSUClearAll for the iAxisCount parameter.
 *  
 *  Result:
 *    On success, noErr is returned. See MacErrors.h for possible error
 *    codes.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUClearFontVariations(
  ATSUStyle                     iStyle,
  ItemCount                     iAxisCount,
  const ATSUFontVariationAxis   iAxis[])          /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* ---------------------------------------------------------------------------- */
/*  Font ID's                                                                   */
/* ---------------------------------------------------------------------------- */
/*
 *  ATSUFontCount()
 *  
 *  Summary:
 *    Obtains the number of ATSUI-compatible fonts installed on a
 *    user's system.
 *  
 *  Discussion:
 *    The ATSUFontCount function obtains the number of fonts on a
 *    user's system that are compatible with ATSUI. Incompatible fonts
 *    include those that cannot be used to represent Unicode, the
 *    missing-character glyph font, and fonts whose names begin with a
 *    period or a percent sign. You can use the count produced in the
 *    oFontCount parameter to determine the amount of memory to
 *    allocate for the oFontIDs array in the function ATSUGetFontIDs.
 *    It is important to note that the set of installed
 *    ATSUI-compatible fonts may change while your application is
 *    running. In Mac OS X, the set of installed fonts may change at
 *    any time. Although in Mac OS 9, fonts cannot be removed from the
 *    Fonts folder while an application other than the Finder is
 *    running, they can be removed from other locations, and it is
 *    possible for fonts to be added. Additionally, just because the
 *    number of fonts stays the same between two successive calls to
 *    ATSUFontCount , this does not mean that the font lists are the
 *    same. It is possible for a font to be added and another removed
 *    between two successive calls to ATSUFontCount , leaving the total
 *    number unchanged.
 *  
 *  Parameters:
 *    
 *    oFontCount:
 *      On return, the number of ATSUI-compatible fonts installed on a
 *      user's system.
 *  
 *  Result:
 *    On success, noErr is returned. See MacErrors.h for possible error
 *    codes.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUFontCount(ItemCount * oFontCount)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUGetFontIDs()
 *  
 *  Summary:
 *    Obtains a list of all the ATSUI-compatible fonts installed on the
 *    user's system.
 *  
 *  Discussion:
 *    Use the function ATSUFontCount to determine how much memory to
 *    allocate before calling this function. Also see the discussion
 *    for the ATSUFontCount function.
 *  
 *  Parameters:
 *    
 *    oFontIDs:
 *      On return, the array contains unique identifiers for each of
 *      the ATSUI-compatible fonts installed on the user's system. You
 *      should allocate enough memory to contain an array the size of
 *      the count produced by the function ATSUFontCount.
 *    
 *    iArraySize:
 *      The maximum number of fonts to obtain. Typically, this is
 *      equivalent to the number of ATSUFontID values for which you
 *      have allocated memory in the oFontIDs parameter.
 *    
 *    oFontCount:
 *      On return, the value specifies the actual number of
 *      ATSUI-compatible fonts installed on the user's system. This may
 *      be greater than the value you specified in the iArraySize
 *      parameter.
 *  
 *  Result:
 *    On success, noErr is returned. See MacErrors.h for possible error
 *    codes.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUGetFontIDs(
  ATSUFontID   oFontIDs[],
  ItemCount    iArraySize,
  ItemCount *  oFontCount)       /* can be NULL */            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUFONDtoFontID()
 *  
 *  Summary:
 *    Finds the ATSUI font ID that corresponds to a font family number,
 *    if one exists.
 *  
 *  Discussion:
 *    This function is not recommended. It is specifically associated
 *    with old QD data types (i.e. the QD font family or 'FOND'
 *    identifier) that has no equivalent in the newer API sets. The
 *    concept of FOND ID and font family instances are all QD-specific
 *    concepts that are not supported in Cocoa, Quartz, and the
 *    non-deprecated parts of ATS and ATSUI.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUFONDtoFontID(
  short         iFONDNumber,
  Style         iFONDStyle,
  ATSUFontID *  oFontID)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUFontIDtoFOND()
 *  
 *  Summary:
 *    Finds the font family number and style that correspond to an
 *    ATSUI font ID, if these exist.
 *  
 *  Discussion:
 *    This function is not recommended. It is specifically associated
 *    with old QD data types (i.e. the QD font family or 'FOND'
 *    identifier) that has no equivalent in the newer API sets. The
 *    concept of FOND ID and font family instances are all QD-specific
 *    concepts that are not supported in Cocoa, Quartz, and the
 *    non-deprecated parts of ATS and ATSUI.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUFontIDtoFOND(
  ATSUFontID   iFontID,
  short *      oFONDNumber,
  Style *      oFONDStyle)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* ---------------------------------------------------------------------------- */
/*  Font names                                                                  */
/* ---------------------------------------------------------------------------- */
/*
 *  ATSUCountFontNames()
 *  
 *  Summary:
 *    Obtains the number of font names that correspond to a given ATSUI
 *    font ID.
 *  
 *  Discussion:
 *    This function obtains the number of font names defined in a font
 *    name table for a given ATSUI font ID. This number includes
 *    repetitions of the same name in different platforms, languages,
 *    and scripts; names of font features, variations, tracking
 *    settings, and instances for the font; and font names identified
 *    by name code constants. You can pass an index value based on this
 *    count to the function ATSUGetIndFontName to obtain a name string,
 *    name code, platform, script, and language for a given ATSUI font
 *    ID.
 *  
 *  Parameters:
 *    
 *    iFontID:
 *      The font for which you wish to obtain the font name count.
 *    
 *    oFontNameCount:
 *      On return, the value specifies the number of entries in the
 *      font name table corresponding to the given ATSUI font ID.
 *  
 *  Result:
 *    On success, noErr is returned. See MacErrors.h for possible error
 *    codes.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUCountFontNames(
  ATSUFontID   iFontID,
  ItemCount *  oFontNameCount)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUGetIndFontName()
 *  
 *  Summary:
 *    Obtains a name string, name code, platform, script, and language
 *    for the font that matches an ATSUI font ID and name table index
 *    value.
 *  
 *  Discussion:
 *    Typically you use the ATSUGetIndFontName function by calling it
 *    twice, as follows: (1) Pass valid values for the iFontID,
 *    iFontNameIndex, and oActualNameLength parameters, 0 for the
 *    iMaximumNameLength parameter, and NULL for the other parameters.
 *    ATSUGetIndFontName returns the length of the font name string in
 *    the oActualNameLength parameter. (2) Allocate enough space for a
 *    buffer of the returned size, then call the function again,
 *    passing a valid pointer to the buffer in the oName parameter. On
 *    return, the buffer contains the font name string. To find a name
 *    string and index value for the first font in a name table that
 *    matches an ATSUI font ID and the specified font parameters, call
 *    the function ATSUFindFontName. To obtain an ATSUI font ID for the
 *    first font in a name table that matches the specified name
 *    string, name code, platform, script, and/or language, call the
 *    function ATSUFindFontFromName.
 *  
 *  Parameters:
 *    
 *    iFontID:
 *      The font for which to obtain information. Note that because
 *      Apple Type Services assigns ATSUFontID values systemwide at
 *      runtime, font IDs can change across system restarts.
 *    
 *    iFontNameIndex:
 *      An index to the font for which to obtain information. Because
 *      this index must be 0-based, you should pass a value between 0
 *      and one less than the count produced by the function
 *      ATSUCountFontNames.
 *    
 *    iMaximumNameLength:
 *      The maximum length of the font name string to obtain.
 *      Typically, this is equivalent to the size of the buffer that
 *      you have allocated in the oName parameter. To determine this
 *      length, see the Discussion.
 *    
 *    oName:
 *      On return, the buffer contains the name string of the font
 *      matching the ATSUI font ID and name table index value being
 *      passed. If the buffer you allocate is not large enough to
 *      contain the name string, ATSUGetIndFontName produces a partial
 *      string. If you are unsure how much memory to allocate for this
 *      parameter, see the Discussion.
 *    
 *    oActualNameLength:
 *      On return, the value specifies the actual length of the
 *      complete name string. This may be greater than the value passed
 *      in the iMaximumNameLength parameter. You should check this
 *      value to ensure that you have allocated sufficient memory and
 *      therefore obtained the complete name string for the font.
 *    
 *    oFontNameCode:
 *      On return, a value specifying the type of name returned (i.e.,
 *      full name, postscript name) of the font. See SFNTTypes.h for a
 *      list of possible values.
 *    
 *    oFontNamePlatform:
 *      On return, a value specifying the encoding of the font. See
 *      SFNTTypes.h for a list of possible values.
 *    
 *    oFontNameScript:
 *      On return, a value specifying the script of the font. See
 *      SFNTTypes.h for a list of possible values.
 *    
 *    oFontNameLanguage:
 *      On return, a value specifying the language of the font. See
 *      SFNTTypes.h for a list of possible values.
 *  
 *  Result:
 *    On success, noErr is returned. See MacErrors.h for possible error
 *    codes.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUGetIndFontName(
  ATSUFontID          iFontID,
  ItemCount           iFontNameIndex,
  ByteCount           iMaximumNameLength,
  Ptr                 oName,
  ByteCount *         oActualNameLength,        /* can be NULL */
  FontNameCode *      oFontNameCode,            /* can be NULL */
  FontPlatformCode *  oFontNamePlatform,        /* can be NULL */
  FontScriptCode *    oFontNameScript,          /* can be NULL */
  FontLanguageCode *  oFontNameLanguage)        /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUFindFontName()
 *  
 *  Summary:
 *    Obtains a name string and index value for the first font in a
 *    name table that matches the specified ATSUI font ID, name code,
 *    platform, script, and/or language.
 *  
 *  Discussion:
 *    Typically you use the ATSUFindFontName function by calling it
 *    twice, as follows: (1) Pass NULL for the oName and oFontNameIndex
 *    parameters, 0 for the iMaximumNameLength parameter, and valid
 *    values for the other parameters. ATSUFindFontName returns the
 *    length of the font name string in the oActualNameLength
 *    parameter. (2) Allocate enough space for a buffer of the returned
 *    size, then call the function again, passing a valid pointer to
 *    the buffer in the oName parameter. On return, the buffer contains
 *    the font name string. To obtain an ATSUI font ID for the first
 *    font in a name table that matches the specified name string, name
 *    code, platform, script, and/or language, call the function
 *    ATSUFindFontFromName. To obtain the font name string, name code,
 *    platform, script, and language for the font that matches an ATSUI
 *    font ID and name table index, call the function
 *    ATSUGetIndFontName. Although they will each accept NULL on input
 *    individually, you must pass a vaild pointer to at least one of
 *    the three parameters oName, oActualNameLength, or oFontNameIndex,
 *    or ATSUFindFontName will return paramErr.
 *  
 *  Parameters:
 *    
 *    iFontID:
 *      The font for which to obtain a name string. Note that because
 *      Apple Type Services assigns ATSUFontID values systemwide at
 *      runtime, font IDs can change across system restarts.
 *    
 *    iFontNameCode:
 *      A constant specifying the FontNameCode value of the font for
 *      which to obtain a name string. See the SFNTTypes.h header file
 *      for a definition of the FontNameCode type and a list of
 *      possible values.
 *    
 *    iFontNamePlatform:
 *      A constant specifying the encoding of the font. See SFNTTypes.h
 *      for possible values to pass for this parameter. If you pass the
 *      kFontNoPlatformCode constant, ATSUFindFontName produces the
 *      first font in the name table matching the other specified
 *      parameters.
 *    
 *    iFontNameScript:
 *      A constant specifying the script of the font. See SFNTTypes.h
 *      for possible values to pass for this parameter. If you pass the
 *      kFontNoScriptCode constant, ATSUFindFontName produces the first
 *      font in the name table matching the other specified parameters.
 *    
 *    iFontNameLanguage:
 *      A constant specifying the language of the font you are
 *      searching for. See SFNTLayoutTypes.h for possible values to
 *      pass for this parameter.
 *    
 *    iMaximumNameLength:
 *      The maximum size of string you want ATSUFindFontName to return.
 *      Typically, this value is equal to the size of the buffer you
 *      have allocated for the oName parameter. To determine this
 *      length, see the Discussion.
 *    
 *    oName:
 *      On return, the name string of the first font in the font name
 *      table matching your specified parameters. If the buffer you
 *      allocate is not large enough, ATSUFindFontName produces a
 *      partial string. If you are unsure how much space to allocate
 *      for this parameter, see the Discussion.
 *    
 *    oActualNameLength:
 *      On return, specifies the actual length of the complete name
 *      string. This may be greater than the value passed in the
 *      iMaximumNameLength parameter. You should check this value to
 *      ensure that you have allocated sufficient memory and therefore
 *      obtained the complete name string for the font.
 *    
 *    oFontNameIndex:
 *      On return, the value provides a 0-based index to the font name
 *      in the font name table.
 *  
 *  Result:
 *    On success, noErr is returned. See MacErrors.h for possible error
 *    codes.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUFindFontName(
  ATSUFontID         iFontID,
  FontNameCode       iFontNameCode,
  FontPlatformCode   iFontNamePlatform,
  FontScriptCode     iFontNameScript,
  FontLanguageCode   iFontNameLanguage,
  ByteCount          iMaximumNameLength,
  Ptr                oName,                    /* can be NULL */
  ByteCount *        oActualNameLength,        /* can be NULL */
  ItemCount *        oFontNameIndex)           /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUFindFontFromName()
 *  
 *  Summary:
 *    Obtains an ATSUI font ID for the first font in a name table that
 *    matches the specified name string, name code, platform, script,
 *    and/or language.
 *  
 *  Discussion:
 *    Because ATSUI cannot guarantee the uniqueness of names among
 *    installed fonts, ATSUFindFontFromName does not necessarily find
 *    the only font that matches these parameters. As a result, you may
 *    want to create a more sophisticated name-matching algorithm or
 *    guarantee the uniqueness of names among installed fonts.
 *  
 *  Parameters:
 *    
 *    iName:
 *      A pointer to a buffer containing the name string of the font
 *      for which to obtain an ATSUI font ID.
 *    
 *    iNameLength:
 *      The length, in bytes, of the name string provided in the iName
 *      parameter.
 *    
 *    iFontNameCode:
 *      A constant specifying the type of name to search for (i.e.,
 *      full name, postcript name). See SFNTTypes.h for a list possible
 *      values to pass for this parameter.
 *    
 *    iFontNamePlatform:
 *      A constant specifying the encoding of the font you are
 *      searching for. See SFNTTypes.h for possible values to pass for
 *      this parameter. Pass kFontNoPlatformCode if you do not want to
 *      limit your search to a particular encoding.
 *    
 *    iFontNameScript:
 *      A constant specifying the script of the font you are searching
 *      for. See SFNTTypes.h for possible values to pass for this
 *      parameter. Pass kFontNoScriptCode if you do not want to limit
 *      your search to a particular script.
 *    
 *    iFontNameLanguage:
 *      A constant specifying the language of the font you are
 *      searching for. See SFNTTypes.h for possible values to pass for
 *      this parameter. Pass kFontNoLanguageCode if you do not want to
 *      limit your search to a particular language.
 *    
 *    oFontID:
 *      On return, the value provides a unique identifier for the
 *      specified font. If no installed font matches the specified
 *      parameters, kATSUInvalidFontID is returned for this parameter.
 *  
 *  Result:
 *    On success, noErr is returned. If the font cannot be found,
 *    kATSUInvalidFontErr is returned. See MacErrors.h for other
 *    possible error codes.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUFindFontFromName(
  const void *       iName,
  ByteCount          iNameLength,
  FontNameCode       iFontNameCode,
  FontPlatformCode   iFontNamePlatform,
  FontScriptCode     iFontNameScript,
  FontLanguageCode   iFontNameLanguage,
  ATSUFontID *       oFontID)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* ---------------------------------------------------------------------------- */
/*  Font features                                                               */
/* ---------------------------------------------------------------------------- */
/*
 *  ATSUCountFontFeatureTypes()
 *  
 *  Summary:
 *    Obtains the number of available feature types in a font.
 *  
 *  Discussion:
 *    This function function obtains the total number of feature types
 *    defined for a font. You can use the count produced by
 *    ATSUCountFontFeatureTypes to determine how much memory to
 *    allocate for the oTypes array in the function
 *    ATSUGetFontFeatureTypes.
 *  
 *  Parameters:
 *    
 *    iFontID:
 *      The font for which to obtain a count of feature types.
 *    
 *    oTypeCount:
 *      On return, the actual number of feature types defined for the
 *      font.
 *  
 *  Result:
 *    On success, noErr is returned. See MacErrors.h for possible error
 *    codes.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUCountFontFeatureTypes(
  ATSUFontID   iFontID,
  ItemCount *  oTypeCount)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUCountFontFeatureSelectors()
 *  
 *  Summary:
 *    Obtains the number of available feature selectors for a given
 *    feature type in a font.
 *  
 *  Discussion:
 *    This function obtains the total number of feature selectors
 *    defined for a given feature type in the font. You can use the
 *    count produced by ATSUCountFontFeatureSelectors to determine how
 *    much memory to allocate for the oSelectors array in the function
 *    ATSUGetFontFeatureSelectors.
 *  
 *  Parameters:
 *    
 *    iFontID:
 *      The font for which to obtain feature selector information.
 *    
 *    iType:
 *      A value specifying one of the font's supported feature types.
 *      To obtain the available feature types for a font, call the
 *      function ATSUGetFontFeatureTypes.
 *    
 *    oSelectorCount:
 *      On return, specifies the actual number of feature selectors
 *      defined for the feature type by the font.
 *  
 *  Result:
 *    On success, noErr is returned. See MacErrors.h for possible error
 *    codes.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUCountFontFeatureSelectors(
  ATSUFontID            iFontID,
  ATSUFontFeatureType   iType,
  ItemCount *           oSelectorCount)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUGetFontFeatureTypes()
 *  
 *  Summary:
 *    Obtains the available feature types of a font.
 *  
 *  Discussion:
 *    A given font may not support all possible feature types and
 *    selectors. If you select features that are not available in a
 *    font, you won't see a change in the glyph's appearance. To
 *    determine the available features of a font, you can call the
 *    functions ATSUGetFontFeatureTypes and
 *    ATSUGetFontFeatureSelectors. The ATSUGetFontFeatureTypes function
 *    reads the font data table for the specified font and obtains its
 *    supported feature types. You can then use this information both
 *    to present the user a list of font features from which to select
 *    and to call such functions as ATSUSetFontFeatures with more
 *    accuracy.
 *  
 *  Parameters:
 *    
 *    iFontID:
 *      The font for which to obtain information about feature types.
 *    
 *    iMaximumTypes:
 *      The maximum number of feature types to obtain for the font.
 *      Typically, this is equivalent to the number of elements in the
 *      oTypes array.
 *    
 *    oTypes:
 *      A pointer to memory you have allocated for an array of
 *      ATSUFontFeatureType values.  You can call the function
 *      ATSUCountFontFeatureTypes to obtain the number of available
 *      feature types for a given font and thus determine the amount of
 *      memory to allocate. On return, the array contains constants
 *      identifying each type of feature that is defined for the font.
 *      The constants that represent font feature types are defined in
 *      the header file SFNTLayoutTypes.h and are described in the
 *      official ATSUI documentation, available on the Apple developer
 *      website.
 *    
 *    oActualTypeCount:
 *      On return, the actual number of feature types defined in the
 *      font. This may be greater than the value you specify in the
 *      iMaximumTypes parameter.
 *  
 *  Result:
 *    On success, noErr is returned. See MacErrors.h for possible error
 *    codes.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUGetFontFeatureTypes(
  ATSUFontID            iFontID,
  ItemCount             iMaximumTypes,
  ATSUFontFeatureType   oTypes[],               /* can be NULL */
  ItemCount *           oActualTypeCount)       /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUGetFontFeatureSelectors()
 *  
 *  Summary:
 *    Obtains the available feature selectors for a given feature type
 *    in a font.
 *  
 *  Discussion:
 *    A given font may not support all possible feature types and
 *    selectors. If you select features that are not available in a
 *    font, you won't see a change in the glyph's appearance. To
 *    determine the available features of a font, you can call the
 *    functions ATSUGetFontFeatureTypes and
 *    ATSUGetFontFeatureSelectors. The ATSUGetFontFeatureSelectors
 *    function reads the font data table for the specified font and
 *    obtains its supported feature selectors for the given feature
 *    types. You can then use this information both to present the user
 *    a list of font features from which to select and to call such
 *    functions as ATSUSetFontFeatures with more accuracy.
 *  
 *  Parameters:
 *    
 *    iFontID:
 *      The font for which to obtain feature selectors.
 *    
 *    iType:
 *      An ATSUFontFeatureType value specifying one of the font's
 *      supported feature types. To obtain the available feature types
 *      for a font, call the function ATSUGetFontFeatureTypes.
 *    
 *    iMaximumSelectors:
 *      An ItemCount value specifying the maximum number of feature
 *      selectors to obtain for the font's specified feature type.
 *      Typically, this is equivalent to the number of elements in the
 *      oSelectors array.
 *    
 *    oSelectors:
 *      A pointer to memory you have allocated for an array of
 *      ATSUFontFeatureSelector values.  You can call the function
 *      ATSUCountFontFeatureSelectors to obtain the number of available
 *      feature selectors for a given font feature type and thus
 *      determine the amount of memory to allocate. On return, the
 *      array contains constants identifying each available feature
 *      selector for the given feature type. The constants that
 *      represent font feature selectors are defined in the header file
 *      SFNTLayoutTypes.h and are described in the official ATSUI
 *      documentation, available on the Apple developer website.
 *    
 *    oSelectorIsOnByDefault:
 *      A pointer to memory you have allocated for an array of Boolean
 *      values. The number of elements in this array should correspond
 *      to the number of elements in the oSelectors array. On return,
 *      the array contains Boolean values indicating whether the
 *      corresponding feature selector in the oSelectors array is on or
 *      off. If true, the feature selector is on by default; if false,
 *      off.
 *    
 *    oActualSelectorCount:
 *      On return, the value specifies the actual number of feature
 *      selectors defined for the given feature type. This value may be
 *      greater than the value you specify in the iMaximumSelectors
 *      parameter.
 *    
 *    oIsMutuallyExclusive:
 *      On return, the value indicates whether the feature selectors
 *      for the given feature type are exclusive or nonexclusive. If a
 *      feature type is exclusive you can choose only one of its
 *      available feature selectors at a time, such as whether to
 *      display numbers as proportional or fixed-width. If a feature
 *      type is nonexclusive, you can enable any number of feature
 *      selectors at once. If true , the feature type is exclusive and
 *      only one selector can be used at a time.
 *  
 *  Result:
 *    On success, noErr is returned. See MacErrors.h for possible error
 *    codes.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUGetFontFeatureSelectors(
  ATSUFontID                iFontID,
  ATSUFontFeatureType       iType,
  ItemCount                 iMaximumSelectors,
  ATSUFontFeatureSelector   oSelectors[],                 /* can be NULL */
  Boolean                   oSelectorIsOnByDefault[],     /* can be NULL */
  ItemCount *               oActualSelectorCount,         /* can be NULL */
  Boolean *                 oIsMutuallyExclusive)         /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUGetFontFeatureNameCode()
 *  
 *  Summary:
 *    btains the name code for a font's feature type or selector that
 *    matches an ASTUI font ID, feature type, and feature selector.
 *  
 *  Discussion:
 *    This function obtains the name code for a font's feature type or
 *    selector that matches an ASTUI font ID, feature type and feature
 *    selector values. By default, ATSUGetFontFeatureNameCode function
 *    obtains the name code of a feature selector. To determine the
 *    name code of a feature type, pass the constant kATSUNoSelector in
 *    the iSelector parameter. You can use the function
 *    ATSUFindFontName to obtain the localized name string for the name
 *    code produced by ATSUGetFontFeatureNameCode.
 *  
 *  Parameters:
 *    
 *    iFontID:
 *      The font for which to obtain the name code for a feature type
 *      or selector.
 *    
 *    iType:
 *      A constant identifying a valid feature type. To obtain the
 *      valid feature types for a font, call the function
 *      ATSUGetFontFeatureTypes.
 *    
 *    iSelector:
 *      A constant identifying a valid feature selector that
 *      corresponds to the feature type passed in the iType parameter.
 *      If you pass the constant kATSUNoSelector, the name code
 *      produced by ATSUGetFontFeatureNameCode is that of the feature
 *      type, not the feature selector. To obtain the valid feature
 *      selectors for a font, call the function
 *      ATSUGetFontFeatureSelectors.
 *    
 *    oNameCode:
 *      On return, the value contains the name code for the font
 *      feature selector or type. See the SFNTTypes.h header file for a
 *      definition of the FontNameCode type and a list of possible
 *      values.
 *  
 *  Result:
 *    On success, noErr is returned. See MacErrors.h for possible error
 *    codes.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUGetFontFeatureNameCode(
  ATSUFontID                iFontID,
  ATSUFontFeatureType       iType,
  ATSUFontFeatureSelector   iSelector,
  FontNameCode *            oNameCode)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* ---------------------------------------------------------------------------- */
/*  Font tracking value & names                                                 */
/* ---------------------------------------------------------------------------- */
/*
 *  ATSUCountFontTracking()
 *  
 *  Summary:
 *    Obtains the number of entries in the font tracking table that
 *    correspond to a given ATSUI font ID and glyph orientation.
 *  
 *  Discussion:
 *    This function obtains the number of font tracking entries defined
 *    in a font tracking table for a given ATSUI font ID and glyph
 *    orientation. You can pass an index value based on this count to
 *    the function ATSUGetIndFontTracking to obtain the name code and
 *    tracking value of a font tracking.
 *  
 *  Parameters:
 *    
 *    iFontID:
 *      The font for which to obtain tracking table information.
 *    
 *    iCharacterOrientation:
 *      A constant identifying the glyph orientation of the font
 *      tracking entries. See the definition of
 *      ATSUVerticalCharacterType for a list of possible values.
 *    
 *    oTrackingCount:
 *      On return, the number of entries in the font tracking table
 *      corresponding to the given ATSUI font ID and glyph orientation.
 *  
 *  Result:
 *    On success, noErr is returned. See MacErrors.h for possible error
 *    codes.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.6 and later
 */
extern OSStatus 
ATSUCountFontTracking(
  ATSUFontID                  iFontID,
  ATSUVerticalCharacterType   iCharacterOrientation,
  ItemCount *                 oTrackingCount)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUGetIndFontTracking()
 *  
 *  Summary:
 *    Obtains the name code and tracking value for the font tracking
 *    that matches an ASTUI font ID, glyph orientation, and tracking
 *    table index.
 *  
 *  Discussion:
 *    You can call the ATSUGetIndFontTracking function to obtain the
 *    name code and tracking value that matches the specified ATSUI
 *    font ID, glyph orientation, and tracking table index value. This
 *    information allows you to manipulate tracking settings for a
 *    style using this font via the kATSUTrackingTag attribute. You can
 *    use the function ATSUFindFontName to obtain the localized name
 *    string for the name code produced by ATSUGetIndFontTracking.
 *  
 *  Parameters:
 *    
 *    iFontID:
 *      The font for which to obtain tracking information.
 *    
 *    iCharacterOrientation:
 *      A constant identifying the glyph orientation of the font
 *      tracking entries. See the definition of
 *      ATSUVerticalCharacterType for a list of possible values.
 *    
 *    iTrackIndex:
 *      An index to the font tracking for which to obtain information.
 *      Because this index must be 0-based, you should pass a value
 *      between 0 and one less than the count produced by the function
 *      ATSUCountFontTracking.
 *    
 *    oFontTrackingValue:
 *      On return, the value contains the font tracking value.
 *    
 *    oNameCode:
 *      On return, the value contains the name code for the font
 *      tracking. See the SFNTTypes.h header file for a definition of
 *      the FontNameCode type and a list of possible values.
 *  
 *  Result:
 *    On success, noErr is returned. See MacErrors.h for possible error
 *    codes.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.6 and later
 */
extern OSStatus 
ATSUGetIndFontTracking(
  ATSUFontID                  iFontID,
  ATSUVerticalCharacterType   iCharacterOrientation,
  ItemCount                   iTrackIndex,
  Fixed *                     oFontTrackingValue,
  FontNameCode *              oNameCode)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* ---------------------------------------------------------------------------- */
/*  Font variations                                                             */
/* ---------------------------------------------------------------------------- */
/*
 *  ATSUCountFontVariations()
 *  
 *  Summary:
 *    Obtains the number of defined variation axes in a font.
 *  
 *  Discussion:
 *    This function function obtains the total number of variation axes
 *    defined for a font. You can use the count produced by
 *    ATSUCountFontVariations to get information about a specific font
 *    variation axis from the function ATSUGetIndFontVariation.
 *  
 *  Parameters:
 *    
 *    iFontID:
 *      The font for which to obtain a count of variation axes.
 *    
 *    oVariationCount:
 *      On return, a count of the number of variation axes defined for
 *      the font.
 *  
 *  Result:
 *    On success, noErr is returned. See MacErrors.h for possible error
 *    codes.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUCountFontVariations(
  ATSUFontID   iFontID,
  ItemCount *  oVariationCount)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUGetIndFontVariation()
 *  
 *  Summary:
 *    Obtains a variation axis and its value range for a font.
 *  
 *  Discussion:
 *    By calling this function, you can obtain a variation axis and its
 *    maximum, minimum, and default values for a font. If you supply
 *    font variation axes and values to the function ATSUSetVariations,
 *    you can change the appearance of a style object's font
 *    accordingly. Note that while you may pass NULL for any of the
 *    output parameters, at least one must be non-NULL or paramErr will
 *    be returned.
 *  
 *  Parameters:
 *    
 *    iFontID:
 *      A font for which to obtain variation information for.
 *    
 *    iVariationIndex:
 *      A value specifying an index into the array of variation axes
 *      for the font. This index identifies the font variation axis to
 *      examine. Because this index is zero-based, you must pass a
 *      value between 0 and one less than the value produced in the
 *      oVariationCount parameter of the function
 *      ATSUCountFontVariations.
 *    
 *    oATSUFontVariationAxis:
 *      On return, a four-character code identifying the font variation
 *      axis corresponding to the specified index.
 *    
 *    oMinimumValue:
 *      On return, the variation axis minimum.
 *    
 *    oMaximumValue:
 *      On return, the variation axis maximum.
 *    
 *    oDefaultValue:
 *      On return, the variation axis default.
 *  
 *  Result:
 *    On success, noErr is returned. See MacErrors.h for possible error
 *    codes.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUGetIndFontVariation(
  ATSUFontID                iFontID,
  ItemCount                 iVariationIndex,
  ATSUFontVariationAxis *   oATSUFontVariationAxis,       /* can be NULL */
  ATSUFontVariationValue *  oMinimumValue,                /* can be NULL */
  ATSUFontVariationValue *  oMaximumValue,                /* can be NULL */
  ATSUFontVariationValue *  oDefaultValue)                /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUGetFontVariationNameCode()
 *  
 *  Summary:
 *    Obtains the name code for the font variation that matches an
 *    ASTUI font ID and font variation axis.
 *  
 *  Discussion:
 *    This function function obtains the name code for the font
 *    variation that matches an ASTUI font ID and font variation axis
 *    tag. You can use the function ATSUFindFontName to obtain the
 *    localized name string for the name code produced by
 *    ATSUGetFontVariationNameCode.
 *  
 *  Parameters:
 *    
 *    iFontID:
 *      The font for which to obtain a font variation name code.
 *    
 *    iAxis:
 *      An ATSUFontVariationAxis value representing a valid variation
 *      axis tag. To obtain a valid variation axis tag for a font, you
 *      can call the functions ATSUGetIndFontVariation or
 *      ATSUGetFontInstance.
 *    
 *    oNameCode:
 *      On return, the value contains the name code for the font
 *      variation. See the SFNTTypes.h header file for a definition of
 *      the FontNameCode type and a list of possible values.
 *  
 *  Result:
 *    On success, noErr is returned. See MacErrors.h for possible error
 *    codes.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUGetFontVariationNameCode(
  ATSUFontID              iFontID,
  ATSUFontVariationAxis   iAxis,
  FontNameCode *          oNameCode)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* ---------------------------------------------------------------------------- */
/*  Font Instances                                                              */
/* ---------------------------------------------------------------------------- */
/*
 *  ATSUCountFontInstances()
 *  
 *  Summary:
 *    Obtains the number of defined font instances in a font.
 *  
 *  Discussion:
 *    This function obtains the total number of font instances defined
 *    in a font. You can use an index value derived from this count to
 *    get information about a specific font instance by calling the
 *    function ATSUGetFontInstance.
 *  
 *  Parameters:
 *    
 *    iFontID:
 *      The font for which to obtain a count of defined instances.
 *    
 *    oInstances:
 *      On return, the value specifies the number of font instances
 *      defined for the font.
 *  
 *  Result:
 *    On success, noErr is returned. See MacErrors.h for possible error
 *    codes.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUCountFontInstances(
  ATSUFontID   iFontID,
  ItemCount *  oInstances)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUGetFontInstance()
 *  
 *  Summary:
 *    Obtains the font variation axis values for a font instance.
 *  
 *  Discussion:
 *    with a minimum value of 0.0, a default of 0.5, and a maximum of
 *    1.0. Additionally, the variation axis 'wdth' is also defined for
 *    the font, with a similar value range. The type designer can then
 *    choose to declare a font instance for a set of specific values
 *    within these axes, such as “Demibold” for a value of 0.8 for the
 *    'wght' axis and 0.5 for the 'wdth' axis. By calling the function
 *    ATSUGetFontInstance , you can obtain the variation axis values
 *    for a given index into an array of font instances. Typically you
 *    use the function ATSUGetFontInstance by calling it twice, as
 *    follows: (1) Pass the ID of the font to examine in the iFont
 *    parameter, a valid pointer to an ItemCount value in the
 *    oActualVariationCount parameter, NULL for the oAxes and oValues
 *    parameters, and 0 for the other parameters. ATSUGetFontInstance
 *    returns the size to use for the oAxes and oValues arrays in the
 *    oActualVariationCount parameter. (2) Allocate enough space for
 *    arrays of the returned size, then call the ATSUGetFontInstance
 *    again, passing pointers to the arrays in the oAxes and oValues
 *    parameters. On return, the arrays contain the font variation axes
 *    and their corresponding values, respectively, for the font
 *    instance.
 *  
 *  Parameters:
 *    
 *    iFontID:
 *      The font for which to obtain instance information.
 *    
 *    iFontInstanceIndex:
 *      An index into an array of instances for the font. This index
 *      identifies the font instance to examine. Because this index is
 *      zero-based, you must pass a value between 0 and one less than
 *      the value produced in the oInstances parameter of the function
 *      ATSUCountFontInstances.
 *    
 *    iMaximumVariations:
 *      The maximum number of font variation axes to obtain for the
 *      font instance. Typically, this is equivalent to the number of
 *      ATSUFontVariationAxis and ATSUFontVariationValue values for
 *      which you have allocated memory in the oAxes and oValues
 *      parameters, respectively. To determine this value, see the
 *      Discussion.
 *    
 *    oAxes:
 *      On return, the array contains tags identifying the font
 *      variation axes that constitute the font instance. If you are
 *      uncertain of how much memory to allocate for this array, see
 *      the Discussion.
 *    
 *    oValues:
 *      On return, the array contains the defined values for the font
 *      variation axes produced in the oAxes array. If you are
 *      uncertain of how much memory to allocate for this array, see
 *      the Discussion.
 *    
 *    oActualVariationCount:
 *      On return, the actual number of font variation axes that
 *      constitute the font instance. This may be greater than the
 *      value you passed in the iMaximumVariations parameter.
 *  
 *  Result:
 *    On success, noErr is returned. See MacErrors.h for possible error
 *    codes.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUGetFontInstance(
  ATSUFontID               iFontID,
  ItemCount                iFontInstanceIndex,
  ItemCount                iMaximumVariations,
  ATSUFontVariationAxis    oAxes[],                     /* can be NULL */
  ATSUFontVariationValue   oValues[],                   /* can be NULL */
  ItemCount *              oActualVariationCount)             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUGetFontInstanceNameCode()
 *  
 *  Summary:
 *    Obtains the name code for the font instance that matches an ASTUI
 *    font ID and font instance index value.
 *  
 *  Discussion:
 *    A font instance consists of a named set of values for each
 *    variation axis in a font. The ATSUGetFontInstanceNameCode
 *    function obtains the name code for the font instance that matches
 *    an ASTUI font ID and font instance index value. You can use the
 *    function ATSUFindFontName to obtain the localized name string for
 *    the name code produced by ATSUGetFontInstanceNameCode. You can
 *    obtain the font variation axis values for a font instance by
 *    calling the function ATSUGetFontInstance.
 *  
 *  Parameters:
 *    
 *    iFontID:
 *      The font for which to obtain a font instance name code.
 *    
 *    iInstanceIndex:
 *      An index to the font instance for which to obtain a name code.
 *      Because this index must be 0-based, you should pass a value
 *      between 0 and one less than the count produced by the function
 *      ATSUCountFontInstances.
 *    
 *    oNameCode:
 *      On return, the name code for the font instance. See the
 *      SFNTTypes.h header file for a definition of the FontNameCode
 *      type and a list of possible values.
 *  
 *  Result:
 *    On success, noErr is returned. See MacErrors.h for possible error
 *    codes.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUGetFontInstanceNameCode(
  ATSUFontID      iFontID,
  ItemCount       iInstanceIndex,
  FontNameCode *  oNameCode)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



#ifdef __cplusplus
}
#endif

#endif /* __ATSUNICODEFONTS__ */

