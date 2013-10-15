/*
     File:       QD/ATSUnicodeObjects.h
 
     Contains:   ATSUI object manipulation functions.
 
     Version:    Quickdraw-192.24~58
 
     Copyright:  © 2003-2006 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __ATSUNICODEOBJECTS__
#define __ATSUNICODEOBJECTS__

#ifndef __ATSUNICODETYPES__
#include <QD/ATSUnicodeTypes.h>
#endif


/* ---------------------------------------------------------------------------- */
/*  ATSUI basic style functions                                                 */
/* ---------------------------------------------------------------------------- */

#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ATSUCreateStyle()
 *  
 *  Summary:
 *    Creates an ATSUStyle object with default settings.
 *  
 *  Discussion:
 *    ATSUStyle objects created by this function have a default set of
 *    values for all attributes. The attributes include settings such
 *    as font, point size, color and so on. You can change the
 *    attributes of a style object by calling the function
 *    ATSUSetAttributes. You can also change font features and
 *    variations set in an ATSUStyle by calling the functions
 *    ATSUSetFontFeatures and ATSUSetVariations, respectively.
 *    ATSUStyle objects are used by associating them with a run of
 *    characters in an ATSUTextLayout object. You can do this by
 *    calling functions such as ATSUSetRunStyle or
 *    ATSUCreateTextLayoutWithTextPtr. You are responsible for freeing
 *    memory assoicated with an ATSUStyle object by calling
 *    ATSUDisposeStyle.
 *  
 *  Parameters:
 *    
 *    oStyle:
 *      On return, a reference to an ATSUStyle object with default
 *      settings.
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
ATSUCreateStyle(ATSUStyle * oStyle)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUCreateAndCopyStyle()
 *  
 *  Summary:
 *    Creates a new ATSUStyle object with the same attributes, font
 *    features, and font variation settings as the input style.
 *  
 *  Discussion:
 *    All attributes, font features, and font variation settings of the
 *    input ATSUStyle object are copied over to a newly created
 *    ATSUStyle object. Note that reference constants are not copied.
 *    You are responsible for freeing memory assoicated with the
 *    returned ATSUStyle object by calling ATSUDisposeStyle.
 *  
 *  Parameters:
 *    
 *    iStyle:
 *      The ATSUStyle object you want to copy.
 *    
 *    oStyle:
 *      On return, a newly created ATSUStyle object. This will be an
 *      exact copy of iStyle, except for the reference constant (if
 *      set).
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
ATSUCreateAndCopyStyle(
  ATSUStyle    iStyle,
  ATSUStyle *  oStyle)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUDisposeStyle()
 *  
 *  Summary:
 *    Disposes of the memory associated with a style object.
 *  
 *  Discussion:
 *    The ATSUDisposeStyle function frees the memory associated with
 *    the specified style object and its internal structures, including
 *    style run attributes. It does not dispose of the memory pointed
 *    to by application-defined style run attributes or reference
 *    constants. You are responsible for doing so. You should call this
 *    function after calling the function ATSUDisposeTextLayout to
 *    dispose of any text layout objects associated with the style
 *    object. For best performance, once you create a style object, you
 *    should keep it and use it as often as needed. You should dispose
 *    of the style object only when it is no longer needed in your
 *    application.
 *  
 *  Parameters:
 *    
 *    iStyle:
 *      The style you want to dispose of.
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
ATSUDisposeStyle(ATSUStyle iStyle)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUSetStyleRefCon()
 *  
 *  Summary:
 *    Sets a reference constant for an ATSUStyle object.
 *  
 *  Discussion:
 *    Reference constants are any 32-bit value you wish to associate
 *    with an object. It can be a pointer to application-specific data,
 *    a integer value, or anything you like. If you copy or clear a
 *    style object that contains a reference constant, the reference
 *    constant is neither copied nor removed. To obtain the reference
 *    constant for a particular ATSUStyle object after it has been set,
 *    use the function ATSUGetStyleRefCon.
 *  
 *  Parameters:
 *    
 *    iStyle:
 *      An ATSUStyle object you want to set the reference constant for.
 *    
 *    iRefCon:
 *      Any arbitrary 32-bit value containing or referring to
 *      application-specific data.
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
ATSUSetStyleRefCon(
  ATSUStyle   iStyle,
  UInt32      iRefCon)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUGetStyleRefCon()
 *  
 *  Summary:
 *    Returns the reference constant for an ATSUStyle object.
 *  
 *  Discussion:
 *    Together with ATSUSetStyleRefCon, this function provides a
 *    mechanism for keeping application-specific data associated with
 *    ATSUStyle objects. Note that if an ATSUStyle object is copied or
 *    cleared, its associated reference constant, if any, is not copied
 *    or cleared.
 *  
 *  Parameters:
 *    
 *    iStyle:
 *      The style object for which to obtain application-specific data.
 *    
 *    oRefCon:
 *      On return, the reference constant for iStyle.
 *  
 *  Result:
 *    On success, noErr is returned. If no reference constant is set in
 *    iStyle, paramErr is returned. See MacErrors.h for other possible
 *    error codes.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUGetStyleRefCon(
  ATSUStyle   iStyle,
  UInt32 *    oRefCon)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* ---------------------------------------------------------------------------- */
/*  ATSUI style comparison                                                      */
/* ---------------------------------------------------------------------------- */
/*
 *  ATSUCompareStyles()
 *  
 *  Summary:
 *    Compares two ATSUStyleObjects.
 *  
 *  Discussion:
 *    The ATSUCompareStyles function compares the contents of two style
 *    objects, including their style attributes, font features, and
 *    font variations. It does not consider reference constants or
 *    application-defined style attributes in the comparison. Note that
 *    order is important, as the ATSUStyleComparison constants that can
 *    be returned indicate "contains" vs. "contained by" based on which
 *    style is considered first in the comparsion.
 *  
 *  Parameters:
 *    
 *    iFirstStyle:
 *      The first style to be compared.
 *    
 *    iSecondStyle:
 *      The second style to be compared.
 *    
 *    oComparison:
 *      On return, the value contains the results of the comparison and
 *      indicates whether the two style objects are the same,
 *      different, or if one is a subset of the other. See the
 *      definition of the ATSUStyleComparison type for more information
 *      on possible values returned for this parameter.
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
ATSUCompareStyles(
  ATSUStyle              iFirstStyle,
  ATSUStyle              iSecondStyle,
  ATSUStyleComparison *  oComparison)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* ---------------------------------------------------------------------------- */
/*  ATSUI style attribute manipulation                                          */
/* ---------------------------------------------------------------------------- */
/*
 *  ATSUCopyAttributes()
 *  
 *  Summary:
 *    Copies attributes from one style to another.
 *  
 *  Discussion:
 *    There are three types of settings in a style: attributes, font
 *    features, and font variations. This function copies only the
 *    first. To copy all three types of settings, use the function
 *    ATSUCreateAndCopyStyle. Also note that this function does not
 *    copy reference constants.
 *  
 *  Parameters:
 *    
 *    iSourceStyle:
 *      The style whose attributes you are copying from.
 *    
 *    iDestinationStyle:
 *      The style whose attributes you are copying to.
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
ATSUCopyAttributes(
  ATSUStyle   iSourceStyle,
  ATSUStyle   iDestinationStyle)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUOverwriteAttributes()
 *  
 *  Summary:
 *    Copies to a destination style object the nondefault style
 *    attribute settings of a source style object.
 *  
 *  Discussion:
 *    The ATSUOverwriteAttributes function copies all nondefault style
 *    attribute values from a source style object to a destination
 *    style object. The source object's nondefault values are applied
 *    to the destination object whether or not the destination object
 *    also has nondefault values for the copied attributes. All other
 *    settings in the destination style object are left unchanged.
 *    ATSUOverwriteAttributes does not copy the contents of memory
 *    referenced by pointers within custom style attributes or within
 *    reference constants. You are responsible for ensuring that this
 *    memory remains valid until both the source and destination style
 *    objects are disposed of. To create a style object that contains
 *    all the contents of another style object, call the function
 *    ATSUCreateAndCopyStyle. To copy all the style attributes
 *    (including any default settings) of a style object into an
 *    existing style object, call the function ATSUCopyAttributes. To
 *    copy style attributes that are set in the source but not in the
 *    destination style object, call the function
 *    ATSUUnderwriteAttributes.
 *  
 *  Parameters:
 *    
 *    iSourceStyle:
 *      An ATSUStyle value specifying the style object from which to
 *      copy nondefault style attributes.
 *    
 *    iDestinationStyle:
 *      An ATSUStyle value specifying the style object containing the
 *      style attributes to be overwritten.
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
ATSUOverwriteAttributes(
  ATSUStyle   iSourceStyle,
  ATSUStyle   iDestinationStyle)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUUnderwriteAttributes()
 *  
 *  Summary:
 *    Copies to a destination style object only those nondefault style
 *    attribute settings of a source style object that are at default
 *    settings in the destination object.
 *  
 *  Discussion:
 *    The ATSUUnderwriteAttributes function copies to a destination
 *    style object only those nondefault style attribute values of a
 *    source style object that are not currently set in a destination
 *    style object. Note that the corresponding value in the
 *    destination object must not be set in order for a copied value to
 *    be applied. All other quantities in the destination style object
 *    are left unchanged. ATSUUnderwriteAttributes does not copy the
 *    contents of memory referenced by pointers within custom style
 *    attributes or within reference constants. You are responsible for
 *    ensuring that this memory remains valid until both the source and
 *    destination style objects are disposed of. To create a style
 *    object that contains all the contents of another style object,
 *    call the function ATSUCreateAndCopyStyle. To copy all the style
 *    attributes (including any default settings) of a style object
 *    into an existing style object, call the function
 *    ATSUCopyAttributes. To copy style attributes that are set in the
 *    source whether or not they are set in the destination style
 *    object, call the function ATSUOverwriteAttributes.
 *  
 *  Parameters:
 *    
 *    iSourceStyle:
 *      An ATSUStyle value specifying the style object from which to
 *      copy nondefault style attributes.
 *    
 *    iDestinationStyle:
 *      An ATSUStyle value specifying the style object containing style
 *      attribute values to be set.
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
ATSUUnderwriteAttributes(
  ATSUStyle   iSourceStyle,
  ATSUStyle   iDestinationStyle)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* ---------------------------------------------------------------------------- */
/*  Empty ATSUI styles                                                          */
/* ---------------------------------------------------------------------------- */
/*
 *  ATSUClearStyle()
 *  
 *  Summary:
 *    Restores default values to a style object.
 *  
 *  Discussion:
 *    Clears a style object of all style attributes (including any
 *    application-defined attributes), font features, and font
 *    variations and returns these values to their default settings. To
 *    clear attributes, font features, or font variations individually,
 *    use the functions ATSUClearAttributes, ATSUClearFontVariations,
 *    or ATSUClearFontFeatures, respectively. Note that ATSUClearStyle
 *    does not affect Reference constants.
 *  
 *  Parameters:
 *    
 *    iStyle:
 *      The style to be cleared.
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
ATSUClearStyle(ATSUStyle iStyle)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUStyleIsEmpty()
 *  
 *  Summary:
 *    Indicates whether a style object contains only default values.
 *  
 *  Discussion:
 *    You can call the ATSUStyleIsEmpty function to determine whether a
 *    style object contains only default values for style attributes,
 *    font features, and font variations. ATSUStyleIsEmpty does not
 *    consider reference constants in its evaluation.
 *  
 *  Parameters:
 *    
 *    iStyle:
 *      An ATSUStyle value specifying the style object to examine.
 *    
 *    oIsClear:
 *      On return, the value is set to true if the style object
 *      contains only default values for style attributes, font
 *      features, and font variations. If false , the style object
 *      contains one or more nondefault values for style attributes,
 *      font features, or font variations. Reference constants do not
 *      affect this result.
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
ATSUStyleIsEmpty(
  ATSUStyle   iStyle,
  Boolean *   oIsClear)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* ---------------------------------------------------------------------------- */
/*  ATSUI style attribute getters and setters                                   */
/* ---------------------------------------------------------------------------- */
/*
 *  ATSUCalculateBaselineDeltas()
 *  
 *  Summary:
 *    Obtains the optimal baseline positions for glyphs in a style run.
 *  
 *  Discussion:
 *    Depending on the writing system, a baseline may be above, below,
 *    or through the centers of glyphs. In general, a style run has a
 *    default baseline, to which all glyphs are visually aligned when
 *    the text is laid out. For example, in a run of Roman text, the
 *    default baseline is the Roman baseline, upon which glyphs sit
 *    (except for descenders, which extend below the baseline). You can
 *    call the ATSUCalculateBaselineDeltas function to obtain the
 *    distances from a specified baseline type to that of other
 *    baseline types for a given style object.
 *    ATSUCalculateBaselineDeltas takes into account font and text size
 *    when performing these calculations. ATSUI uses these distances to
 *    determine the cross-stream shifting to apply when aligning glyphs
 *    in a style run. You can use the resulting array to set or obtain
 *    the optimal baseline positions of glyphs in a style run. You can
 *    also set various baseline values to create special effects such
 *    as drop capitals. The functions ATSUSetLineControls and
 *    ATSUSetLayoutControls allow you to set baseline offset values at
 *    the line or layout level, respectively, using the
 *    kATSULineBaselineValuesTag control attribute tag.
 *  
 *  Parameters:
 *    
 *    iStyle:
 *      An ATSUStyle value specifying the style object to examine.
 *    
 *    iBaselineClass:
 *      A BslnBaselineClass constant identifying the primary baseline
 *      from which to measure other baselines. See SFNTLayoutTypes.h
 *      for an enumeration of possible values. Pass the constant
 *      kBSLNNoBaselineOverride to use the standard baseline value from
 *      the current font.
 *    
 *    oBaselineDeltas:
 *      On return, an array that contains baseline offsets, specifying
 *      distances measured in points, from the default baseline to each
 *      of the other baseline types in the style object. Positive
 *      values indicate baselines above the default baseline and
 *      negative values indicate baselines below it. See
 *      SFNTLayoutTypes.h for a description of the BslnBaselineRecord
 *      type.
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
ATSUCalculateBaselineDeltas(
  ATSUStyle            iStyle,
  BslnBaselineClass    iBaselineClass,
  BslnBaselineRecord   oBaselineDeltas)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUSetAttributes()
 *  
 *  Summary:
 *    Sets style attribute values in a style object.
 *  
 *  Discussion:
 *    Style attributes are a collection of values and settings that
 *    specify information about a style such as font, point size, and
 *    color. To specify a style attribute, ATSUI uses a "triple"
 *    consisting of (1) an attribute tag, (2) a value for that tag, and
 *    (3) the size of the value. For a list of possible tags and their
 *    default values, see the ATSUI documentation, or the definition of
 *    ATSUAttributeTag elsewhere in this header file. When you call
 *    ATSUSetAttributes, any style attributes that you do not set
 *    retain their previous values. To set font features and font
 *    variations, call the functions ATSUSetFontFeatures and
 *    ATSUSetVariations, respectively.
 *  
 *  Parameters:
 *    
 *    iStyle:
 *      A style in which to set attributes.
 *    
 *    iAttributeCount:
 *      An ItemCount value specifying the number of attributes to set.
 *      This value should correspond to the number of elements in the
 *      iTag, iValueSize, and iValue arrays.
 *    
 *    iTag:
 *      An array of attribute tags. The number of elements in this
 *      array must not be less than iAttributeCount. Each element in
 *      the array must contain a valid style attribute tag (see the
 *      definition of ATSUAttributeTag for possible values).
 *    
 *    iValueSize:
 *      An array of ByteCount values. The number of elements in this
 *      array must not be less than iAttributeCount. Each ByteCount
 *      value corresoponds to the size of an element referred to by a
 *      pointer in the iValue array.
 *    
 *    iValue:
 *      An array of pointers of type ATSUAttributeValuePtr. Each
 *      pointer referrs to a value that corresponds to a tag specified
 *      by the iTag array. The size of the data referred to is
 *      determined by a corresponding element in the iValueSize array.
 *      The number of elements in this array must not be less than
 *      iAttributeCount.
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
ATSUSetAttributes(
  ATSUStyle                     iStyle,
  ItemCount                     iAttributeCount,
  const ATSUAttributeTag        iTag[],
  const ByteCount               iValueSize[],
  const ATSUAttributeValuePtr   iValue[])                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUGetAttribute()
 *  
 *  Summary:
 *    Obtains a single attribute value for a style object.
 *  
 *  Discussion:
 *    The ATSUGetAttribute function obtains the value of a specified
 *    style attribute for a given style object. Before calling
 *    ATSUGetAttribute, you should call the function
 *    ATSUGetAllAttributes to obtain an array of nondefault style
 *    attribute tags and value sizes for the style object. You can then
 *    pass ATSUGetAttribute the tag and value size for the attribute
 *    value to obtain. This function may return kATSUNotSetErr for some
 *    attributes that have not been set to a non-default via a call to
 *    ATSUSetAttributes.
 *  
 *  Parameters:
 *    
 *    iStyle:
 *      The style object you with to retrieve an attribute value from.
 *    
 *    iTag:
 *      The tag you wish to obtain the value of.
 *    
 *    iExpectedValueSize:
 *      The size of the buffer pointed to by oValue.
 *    
 *    oValue:
 *      On input, a buffer you have allocated to retain the value of
 *      the specified attribute. On return, the value of the requested
 *      attribute will be placed here. You may pass NULL for this
 *      parameter.
 *    
 *    oActualValueSize:
 *      On return, the actual number of bytes written to oValue is
 *      placed here. You may pass NULL for this parameter.
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
ATSUGetAttribute(
  ATSUStyle               iStyle,
  ATSUAttributeTag        iTag,
  ByteCount               iExpectedValueSize,
  ATSUAttributeValuePtr   oValue,                   /* can be NULL */
  ByteCount *             oActualValueSize)         /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUGetAllAttributes()
 *  
 *  Summary:
 *    Obtains an array of style attribute tags and value sizes for a
 *    style object.
 *  
 *  Discussion:
 *    This function returns information as to which attributes have had
 *    non-default values set in a particular ATSUStyle object. It will
 *    also return the size in bytes of the values of these attributes.
 *    Using this information, you can then call ATSUGetAttribute to
 *    obtain the value of a given attribute. Typically you use the
 *    function ATSUGetAllAttributes by calling it twice, as follows:
 *    (1) Pass a reference to the style object to examine in the iStyle
 *    parameter, a valid pointer to an ItemCount value in the
 *    oTagValuePairCount parameter, NULL for the oAttributeInfoArray
 *    parameter, and 0 for the iTagValuePairArraySize parameter.
 *    ATSUGetAllAttributes returns the size of the tag and value-size
 *    arrays in the oTagValuePairCount parameter. (2) Allocate enough
 *    space for an array of the returned size, then call the
 *    ATSUGetAllAttributes function again, passing a valid pointer in
 *    the oAttributeInfoArray parameter. On return, the pointer refers
 *    to an array of the style attribute tag and value-size pairs
 *    contained in the style object.
 *  
 *  Parameters:
 *    
 *    iStyle:
 *      The style object you wish to retrieve a list of attribute tags
 *      from.
 *    
 *    oAttributeInfoArray:
 *      On return, an array of ATSUAttributeInfo structures. Each
 *      structure contains information about an attribute in iStyle
 *      that has a non-default value. You must allocate space for this
 *      array. If you are unsure how much space to allocate, you may
 *      pass NULL for this parameter and use the oTagValuePairCount
 *      parameter to determine how much space to allocate.
 *    
 *    iTagValuePairArraySize:
 *      The size of the array you allocated and are passing in for the
 *      oAttributeInfoArray parameter.
 *    
 *    oTagValuePairCount:
 *      On return, the number of attributes whose information was
 *      stored in the oAttributeInfoArray parameter.
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
ATSUGetAllAttributes(
  ATSUStyle           iStyle,
  ATSUAttributeInfo   oAttributeInfoArray[],        /* can be NULL */
  ItemCount           iTagValuePairArraySize,
  ItemCount *         oTagValuePairCount)           /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUClearAttributes()
 *  
 *  Summary:
 *    Restores default values to the specified style attributes of a
 *    style object.
 *  
 *  Discussion:
 *    Removes those style attribute values identified by the tag
 *    constants in the iTag array and replaces them with the default
 *    values. For a list of possible tags and their default values, see
 *    the ATSUI documentation, or the definition of ATSUAttributeTag
 *    elsewhere in this header file. If you specify that any currently
 *    unset attribute values be removed, ATSUClearAttributes does not
 *    return an error. Note this function only deals with attributes.
 *    To remove all previously set style attributes as well as font
 *    features and font variations from a style object, call the
 *    function ATSUClearStyle.
 *  
 *  Parameters:
 *    
 *    iStyle:
 *      A style whose attributes you want to clear.
 *    
 *    iTagCount:
 *      The number of tags you are passing in via the iTag parameter.
 *      Pass kATSUClearAll to clear all attributes.
 *    
 *    iTag:
 *      An array of ATSUAttributeTag indicating which attributes to
 *      clear. You may pass NULL for this parameter if you are passing
 *      kATSUClearAll for the iTagCount parameter.
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
ATSUClearAttributes(
  ATSUStyle                iStyle,
  ItemCount                iTagCount,
  const ATSUAttributeTag   iTag[])          /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* ---------------------------------------------------------------------------- */
/*  ATSUI basic text layout functions                                           */
/* ---------------------------------------------------------------------------- */
/*
 *  ATSUCreateTextLayout()
 *  
 *  Summary:
 *    Creates an opaque text layout object containing only default text
 *    layout attributes.
 *  
 *  Discussion:
 *    This function creates a empty text layout object that has no
 *    styles or text buffer associated with it. Most ATSUI functions
 *    that operate on text layout objects require that the objects be
 *    associated with style information and text. To associate style
 *    objects and text with an empty text layout object, you can call
 *    the functions ATSUSetRunStyle and ATSUSetTextPointerLocation .
 *    Or, to create a text layout object and associate style objects
 *    and text with it at the same time, you can call the function
 *    ATSUCreateTextLayoutWithTextPtr. To provide nondefault line or
 *    layout attributes for a text layout object, you can call the
 *    functions ATSUSetLineControls or ATSUSetLayoutControls . After
 *    setting text attributes, call ATSUDrawText to draw the text. Text
 *    layout objects are readily reusable and should be cached for
 *    later use, if possible. You can reuse a text layout object even
 *    if the text associated with it is altered. Call the functions
 *    ATSUSetTextPointerLocation, ATSUTextDeleted, or ATSUTextInserted
 *    to manage the altered text.
 *  
 *  Parameters:
 *    
 *    oTextLayout:
 *      On return, the value refers to an empty text layout object.
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
ATSUCreateTextLayout(ATSUTextLayout * oTextLayout)            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUCreateAndCopyTextLayout()
 *  
 *  Summary:
 *    Creates a copy of a text layout object.
 *  
 *  Discussion:
 *    This function creates a copy of the source text layout object's
 *    style runs (including references to the associated text buffer
 *    and style objects), line attributes, layout attributes, and
 *    layout caches. ATSUCreateAndCopyTextLayout does not copy
 *    reference constants. To create a text layout object without
 *    copying a source object, you can the function
 *    ATSUCreateTextLayout or the function
 *    ATSUCreateTextLayoutWithTextPtr.
 *  
 *  Parameters:
 *    
 *    iTextLayout:
 *      The layout to be copied.
 *    
 *    oTextLayout:
 *      On return, a reference to a layout object which is a copy of
 *      iTextLayout.
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
ATSUCreateAndCopyTextLayout(
  ATSUTextLayout    iTextLayout,
  ATSUTextLayout *  oTextLayout)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUCreateTextLayoutWithTextPtr()
 *  
 *  Summary:
 *    Creates an opaque text layout object containing default text
 *    layout attributes as well as associated text and text styles.
 *  
 *  Discussion:
 *    This function creates a text layout object and associates the
 *    specified text buffer and style runs with it. All layout
 *    attributes are set to their default values. To provide nondefault
 *    line or layout attributes for a text layout object, you can call
 *    the functions ATSUSetLineControls or ATSUSetLayoutControls. After
 *    setting text attributes, call ATSUDrawText to draw the text.
 *    Because the only way that ATSUI interacts with text is via the
 *    memory references you associate with a text layout object, you
 *    are responsible for keeping these references updated through use
 *    of the functions ATSUTextInserted, ATSUTextDeleted,
 *    ATSUTextMoved, and ATSUSetTextPointerLocation. Note that, because
 *    ATSUI objects retain state information, doing superfluous calling
 *    can degrade performance. For example, you could call
 *    ATSUSetTextPointerLocation rather than ATSUTextInserted when the
 *    user inserts text, but there would be a performance penalty, as
 *    all the layout caches are flushed when you call
 *    ATSUSetTextPointerLocation , rather than just the affected ones.
 *    Text layout objects are readily reusable and should themselves be
 *    cached for later use, if possible. Text objects are thread-safe
 *    starting with ATSUI version 2.4.
 *  
 *  Parameters:
 *    
 *    iText:
 *      A text buffer containing UTF-16Ðencoded text. ATSUI associates
 *      this buffer with the new text layout object and analyzes the
 *      complete text of the buffer when obtaining the layout context
 *      for the current text range. Thus, for paragraph-format text, if
 *      you specify a buffer containing less than a complete paragraph,
 *      some of ATSUI's layout results are not guaranteed to be
 *      accurate. For example, with a buffer of less than a full
 *      paragraph, ATSUI can neither reliably obtain the context for
 *      bidirectional processing nor reliably generate accent
 *      attachments and ligature formations for Roman text.
 *    
 *    iTextOffset:
 *      The offset from the beginning of the text buffer to the first
 *      character of the range to include in the layout. To indicate
 *      that the specified text range starts at the beginning of the
 *      text buffer, you can pass the constant kATSUFromTextBeginning.
 *      To specify the entire text buffer, pass kATSUFromTextBeginning
 *      in this parameter and kATSUToTextEnd in the iTextLength
 *      parameter. For best results, use one layout for each paragraph
 *      within the text buffer.
 *    
 *    iTextLength:
 *      The length of the text range. Note that the sum of iTextOffset
 *      and iTextLength must be less than or equal to the value of the
 *      iTextTotalLength parameter. If you want the range of text to
 *      extend to the end of the text buffer, you can pass the constant
 *      kATSUToTextEnd. For best results, use one layout for each
 *      paragraph within the text buffer.
 *    
 *    iTextTotalLength:
 *      The length of the entire text buffer referred to by iText. This
 *      value should be greater than or equal to the range of text
 *      defined by the iTextLength parameter.
 *    
 *    iNumberOfRuns:
 *      The number of text style runs you want to define within the
 *      overall text range. The number of style objects and style run
 *      lengths passed in the iStyles and iRunLengths parameters,
 *      respectively, should be equal to the number of runs specified
 *      here.
 *    
 *    iRunLengths:
 *      An array providing ATSUI with the lengths of each of the text's
 *      style runs. You can pass kATSUToTextEnd for the last style run
 *      length if you want the style run to extend to the end of the
 *      text range. If the sum of the style run lengths is less than
 *      the total length of the text range, the remaining characters
 *      are assigned to the last style run.
 *    
 *    iStyles:
 *      An array of styles, each corresponding to a style run defined
 *      in iRunLengths. The same ATSUStyle object may be referred to
 *      more than once in this array. The number of elements in this
 *      array must be equal to the value specified by the iNumberOfRuns
 *      parameter.
 *    
 *    oTextLayout:
 *      A valid pointer to an ATSUTextLayout value. On return, the
 *      value refers to the newly created text layout object.
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
ATSUCreateTextLayoutWithTextPtr(
  ConstUniCharArrayPtr   iText,
  UniCharArrayOffset     iTextOffset,
  UniCharCount           iTextLength,
  UniCharCount           iTextTotalLength,
  ItemCount              iNumberOfRuns,
  const UniCharCount     iRunLengths[],
  ATSUStyle              iStyles[],
  ATSUTextLayout *       oTextLayout)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUClearLayoutCache()
 *  
 *  Summary:
 *    Clears the layout cache of a line or an entire text layout object.
 *  
 *  Discussion:
 *    The layout cache contains all the layout information ATSUI
 *    calculates and needs to draw a range of text in a text layout
 *    object. This includes caret positions, the memory locations of
 *    glyphs, and other information needed to lay out the glyphs. ATSUI
 *    uses information in the layout cache to avoid laying out the text
 *    again, thereby improving performance. When you clear the layout
 *    cache of a line or block of text, ATSUI takes longer to redraw a
 *    line, since it must perform the calculations that support glyph
 *    layout again. You should call the function ATSUClearLayoutCache
 *    when you need to decrease the amount of memory your application
 *    uses. This function reclaims memory at the cost of optimal
 *    performance. By default, the ATSUClearLayoutCache function
 *    removes the layout cache of a single line. To clear the layout
 *    cache for multiple lines, you should call ATSUClearLayoutCache
 *    for each line. To clear the layout cache of an entire text layout
 *    object, pass the constant kATSUFromTextBeginning in the
 *    iLineStart parameter. Note that ATSUClearLayoutCache does not
 *    produce a function error if lines do not have a layout cache. The
 *    ATSUClearLayoutCache function flushes the layout cache but does
 *    not alter previously set text layout attributes, soft line break
 *    positions, or the text memory location. If you do not want to
 *    retain these values, you should dispose of the text layout object
 *    by calling the ATSUDisposeTextLayout function.
 *  
 *  Parameters:
 *    
 *    iTextLayout:
 *      The layout for which to clear the layout caches.
 *    
 *    iLineStart:
 *      The offset from the beginning of the text buffer to the
 *      beginning of the line for which to discard the layout cache. If
 *      the range of text spans multiple lines, you should call
 *      ATSUClearLayoutCache for each line, passing the offset
 *      corresponding to the beginning of the new line to draw with
 *      each call. To clear the layout cache of the entire text layout
 *      object, you can pass the constant kATSUFromTextBeginning.
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
ATSUClearLayoutCache(
  ATSUTextLayout       iTextLayout,
  UniCharArrayOffset   iLineStart)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUDisposeTextLayout()
 *  
 *  Summary:
 *    Disposes of the memory associated with a text layout object.
 *  
 *  Discussion:
 *    This function frees the memory associated with the specified text
 *    layout object and its internal structures, including line and
 *    layout control attributes, style runs, and soft line breaks.
 *    ATSUDisposeTextLayout does not dispose of any memory that may be
 *    allocated for the text buffer, style objects, or reference
 *    constants associated with the text layout object. You are
 *    responsible for doing so. For best performance, text layout
 *    objects are readily reusable and should be cached for later use,
 *    if possible. You can reuse a text layout object even if the text
 *    associated with it is altered. Call the functions
 *    ATSUSetTextPointerLocation, ATSUTextDeleted, or ATSUTextInserted
 *    to manage the altered text, rather than disposing of the text
 *    layout object and creating a new one.
 *  
 *  Parameters:
 *    
 *    iTextLayout:
 *      The layout object to dispose of.
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
ATSUDisposeTextLayout(ATSUTextLayout iTextLayout)             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUSetTextLayoutRefCon()
 *  
 *  Summary:
 *    Sets application-specific data for a text layout object.
 *  
 *  Discussion:
 *    This function associates a reference constant (that is,
 *    application-specific data) with a text layout object. You might
 *    typically use ATSUSetTextLayoutRefCon to track user preferences
 *    that can effect layout, for example. If you copy or clear a text
 *    layout object containing a reference constant, the reference
 *    constant is not copied or removed. When you dispose of a text
 *    layout object that contains a reference constant, you are
 *    responsible for freeing any memory allocated for the reference
 *    constant. Calling the function ATSUDisposeTextLayout does not do
 *    so.
 *  
 *  Parameters:
 *    
 *    iTextLayout:
 *      A layout for which you wish to set a reference constant.
 *    
 *    iRefCon:
 *      Any arbitrary 32-bit value you wish to store in association
 *      with iTextLayout.
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
ATSUSetTextLayoutRefCon(
  ATSUTextLayout   iTextLayout,
  UInt32           iRefCon)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUGetTextLayoutRefCon()
 *  
 *  Summary:
 *    Obtains application-specific data for a text layout object.
 *  
 *  Discussion:
 *    This function obtains a reference constant (that is,
 *    application-specific data) associated with a text layout object.
 *    To associate a reference constant with a text layout object, call
 *    the function ATSUSetTextLayoutRefCon.
 *  
 *  Parameters:
 *    
 *    iTextLayout:
 *      A layout for which you wish to retreive the reference constant.
 *    
 *    oRefCon:
 *      On return, the reference constant associated with iTextLayout.
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
ATSUGetTextLayoutRefCon(
  ATSUTextLayout   iTextLayout,
  UInt32 *         oRefCon)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* ---------------------------------------------------------------------------- */
/*  ATSUI text buffer manipulation                                              */
/* ---------------------------------------------------------------------------- */
/*
 *  ATSUSetTextPointerLocation()
 *  
 *  Summary:
 *    Associates a text buffer with a text layout object or updates
 *    previously associated text.
 *  
 *  Discussion:
 *    For ATSUI to render your text, you must associate the text with
 *    both a text layout object and style information. Some functions,
 *    such as ATSUCreateTextLayoutWithTextPtr, create a text layout
 *    object and associate text with it concurrently. However, if you
 *    use the function ATSUCreateTextLayout to create a text layout
 *    object, you must assign text to the object prior to attempting
 *    most ATSUI operations. You can use the function
 *    ATSUSetTextPointerLocation to associate text with a layout
 *    object. When you call this function, you are both assigning a
 *    text buffer to a text layout object and specifying the current
 *    text subrange within the buffer to include in the layout. If
 *    there is already text associated with a text layout object,
 *    calling ATSUSetTextPointerLocation overrides the previously
 *    associated text, as well as clearing the object's layout caches.
 *    You would typically only call this function for a text layout
 *    object with existing associated text if either (a) both the
 *    buffer itself is relocated and a subrange of the buffer's text is
 *    deleted or inserted or (b) when associating an entirely different
 *    buffer with a text layout object. Note that, because ATSUI
 *    objects retain state, doing superfluous calling can degrade
 *    performance. For example, you could call
 *    ATSUSetTextPointerLocation rather than ATSUTextInserted when the
 *    user simply inserts a subrange of text within a text buffer, but
 *    there would be a performance penalty, as all the layout caches
 *    are flushed by ATSUSetTextPointerLocation, rather than just the
 *    affected ones. Similarly, you should not call
 *    ATSUSetTextPointerLocation, when an entire text buffer associated
 *    with a text layout object is relocated, but no other changes have
 *    occurred that would affect the buffer's current subrange.
 *    Instead, you should call ATSUTextMoved, which is a more focused
 *    function and therefore more efficient. After associating text
 *    with a text layout object, use ATSUSetRunStyle to associate style
 *    information with the text. You can then call the function
 *    ATSUDrawText to display the text or a subrange of the text.
 *  
 *  Parameters:
 *    
 *    iTextLayout:
 *      The layout object for which you wish to associate a text buffer.
 *    
 *    iText:
 *      A pointer to a buffer of Unicode text in UTF-16 format. This is
 *      the text that will be associated with iTextLayout.
 *    
 *    iTextOffset:
 *      The starting offset of the subrange of the text buffer you wish
 *      to associate with iTextLayout. To indicate that the specified
 *      text range starts at the beginning of the text buffer, you can
 *      pass the constant kATSUFromTextBeginning . To specify the
 *      entire text buffer, pass kATSUFromTextBeginning in this
 *      parameter and kATSUToTextEnd in the iTextLength parameter.
 *    
 *    iTextLength:
 *      The length of the subrage of the text buffer you wish to
 *      associate with iTextLayout. Note that the sum of iTextOffset
 *      and iTextLength must be less than or equal to the value of the
 *      iTextTotalLength parameter. If you want the range of text to
 *      extend to the end of the text buffer, you can pass the constant
 *      kATSUToTextEnd.
 *    
 *    iTextTotalLength:
 *      The length of the entire text buffer. This value should be
 *      greater than or equal to the range of text defined by the
 *      iTextLength parameter.
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
ATSUSetTextPointerLocation(
  ATSUTextLayout         iTextLayout,
  ConstUniCharArrayPtr   iText,
  UniCharArrayOffset     iTextOffset,
  UniCharCount           iTextLength,
  UniCharCount           iTextTotalLength)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUGetTextLocation()
 *  
 *  Summary:
 *    Returns information about the Unicode text buffer associated with
 *    a layout.
 *  
 *  Discussion:
 *    For a given layout, ATSUGetTextLocation will return information
 *    about the Unicode text buffer associated with it, including its
 *    memory location, its size, and whether it is stored in a handle.
 *    Note that since a layout may refer to a subrange within a text
 *    buffer, parameters defining this subrange are included. oOffset
 *    and oTextLength give information about the subrange, while oText
 *    and oTextTotalLength give information about the entire text
 *    buffer. You may pass NULL for any parameters you are not
 *    interested in. Only iTextLayout is required.
 *  
 *  Parameters:
 *    
 *    iTextLayout:
 *      A text layout whose text buffer you want information regarding.
 *    
 *    oText:
 *      A pointer to data of any type. On return, the pointer is set to
 *      either a pointer or a handle that refers to the text buffer for
 *      the specified text layout object.
 *    
 *    oTextIsStoredInHandle:
 *      On return, the value is set to true if the text buffer referred
 *      to by the oText parameter is accessed by a handle; if false, a
 *      pointer.
 *    
 *    oOffset:
 *      On return, the offset from the beginning of the text buffer to
 *      the first character of the layout's current text range.
 *    
 *    oTextLength:
 *      On return, the value specifies the length of the layout's
 *      current text range.
 *    
 *    oTextTotalLength:
 *      On return, the total length of the text buffer. Note this is
 *      not necessarily the same as the length of the layout's current
 *      range. (A layout may refer to only a subrange within a text
 *      buffer.)
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
ATSUGetTextLocation(
  ATSUTextLayout        iTextLayout,
  void **               oText,                       /* can be NULL */
  Boolean *             oTextIsStoredInHandle,       /* can be NULL */
  UniCharArrayOffset *  oOffset,                     /* can be NULL */
  UniCharCount *        oTextLength,                 /* can be NULL */
  UniCharCount *        oTextTotalLength)            /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUTextDeleted()
 *  
 *  Summary:
 *    Informs ATSUI of the location and length of a text deletion.
 *  
 *  Discussion:
 *    When you call the ATSUTextDeleted function to inform ATSUI of a
 *    text deletion, it shortens the style run(s) containing the
 *    deleted text by the amount of the deletion. If a style run
 *    corresponds entirely to a range of deleted text, that style run
 *    is removed. If the deletion point is between two style runs, the
 *    first style run is shortened (or removed). The ATSUTextDeleted
 *    function also shortens the total length of the text buffer
 *    containing the deleted text by the amount of the deletion. That
 *    is, it shifts the memory location of the text following the
 *    deleted text by iDeletedRangeLength .ATSUTextDeleted also removes
 *    any soft line breaks that fall within the deleted text and
 *    updates affected drawing caches. The ATSUTextDeleted function
 *    does not change the actual memory location of the affected text.
 *    You are responsible for deleting the corresponding text is from
 *    the text buffer. You are also responsible for calling the
 *    function ATSUDisposeStyle to dispose of the memory associated
 *    with any style runs that have been removed. Note that calling the
 *    function ATSUTextDeleted automatically removes previously-set
 *    soft line breaks if the line breaks are within the range of text
 *    that is deleted.
 *  
 *  Parameters:
 *    
 *    iTextLayout:
 *      The text layout containing the deleted text.
 *    
 *    iDeletedRangeStart:
 *      The starting location of the deleted text. To specify a
 *      deletion point at the beginning of the text buffer, you can
 *      pass the constant kATSUFromTextBeginning. To specify that the
 *      entire text buffer has been deleted, pass
 *      kATSUFromTextBeginning in this parameter and kATSUToTextEnd in
 *      the iDeletedRangeLength parameter.
 *    
 *    iDeletedRangeLength:
 *      The length of the deleted text. To specify a deletion length
 *      extending to the end of the text buffer, you can pass the
 *      constant kATSUToTextEnd.
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
ATSUTextDeleted(
  ATSUTextLayout       iTextLayout,
  UniCharArrayOffset   iDeletedRangeStart,
  UniCharCount         iDeletedRangeLength)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUTextInserted()
 *  
 *  Summary:
 *    Informs ATSUI of the location and length of a text insertion.
 *  
 *  Discussion:
 *    When you call the ATSUTextInserted function to inform ATSUI of a
 *    text insertion, it extends the style run containing the insertion
 *    point by the amount of the inserted text. If the insertion point
 *    is between two style runs, the first style run is extended to
 *    include the new text. The ATSUTextInserted function also extends
 *    the total length of the text buffer containing the inserted text
 *    by the amount of the inserted text. That is, it shifts the memory
 *    location of the text following the inserted text by
 *    iInsertionLength. ATSUTextInserted then updates drawing caches.
 *    Note that the ATSUTextInserted function does not change the
 *    actual memory location of the inserted text. You are responsible
 *    for placing the inserted text into the text buffer at the
 *    appropriate location. The ATSUTextInserted function does not
 *    insert style runs or line breaks; to do so, call the functions
 *    ATSUSetRunStyle and ATSUSetSoftLineBreak, respectively. Break
 *    line operations should be redone after you call ATSUTextInserted.
 *  
 *  Parameters:
 *    
 *    iTextLayout:
 *      The text layout in which the text insertion is taking place.
 *    
 *    iInsertionLocation:
 *      The offset corresponding to the beginning of the inserted text.
 *    
 *    iInsertionLength:
 *      The length of the inserted text.
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
ATSUTextInserted(
  ATSUTextLayout       iTextLayout,
  UniCharArrayOffset   iInsertionLocation,
  UniCharCount         iInsertionLength)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUTextMoved()
 *  
 *  Summary:
 *    Informs ATSUI of the new memory location of relocated text.
 *  
 *  Discussion:
 *    You should call the ATSUTextMoved function when a range of text
 *    consisting of less than an entire text buffer has been moved. The
 *    ATSUTextMoved function informs ATSUI of the new memory location
 *    of the text. You are responsible for moving the text. The text
 *    buffer should remain otherwise unchanged.
 *  
 *  Parameters:
 *    
 *    iTextLayout:
 *      The text layout containing the moved text.
 *    
 *    iNewLocation:
 *      The new memory location of the moved text.
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
ATSUTextMoved(
  ATSUTextLayout         iTextLayout,
  ConstUniCharArrayPtr   iNewLocation)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* ---------------------------------------------------------------------------- */
/*  ATSUI layout controls                                                       */
/* ---------------------------------------------------------------------------- */
/*
 *  ATSUCopyLayoutControls()
 *  
 *  Summary:
 *    Copies all layout control attribute settings from a source text
 *    layout object to a destination text layout object.
 *  
 *  Discussion:
 *    This function copies all layout control attribute values to a
 *    destination text layout object from a source text layout object,
 *    including any default (unset) values in the source object. For a
 *    list of tags and their default values, see the definition of
 *    ATSUAttributeTag. Reference constants and the contents of memory
 *    referenced by pointers within custom layout attributes are not
 *    copied. You are responsible for ensuring that this memory remains
 *    valid until both the source and destination text layout objects
 *    are disposed. To copy line control attribute values from one text
 *    layout object to another, call the function ATSUCopyLineControls.
 *  
 *  Parameters:
 *    
 *    iSourceTextLayout:
 *      The text layout to copy layout controls from.
 *    
 *    iDestTextLayout:
 *      The text layout to copy layout controls to.
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
ATSUCopyLayoutControls(
  ATSUTextLayout   iSourceTextLayout,
  ATSUTextLayout   iDestTextLayout)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUSetLayoutControls()
 *  
 *  Summary:
 *    Sets layout control attribute values in a text layout object.
 *  
 *  Discussion:
 *    When you use ATSUI to image your text, you can control the text's
 *    display and formatting at a number of different levels: layout,
 *    line, and run. The level affected by this function is the layout
 *    level, which is that of the entire text range associated with
 *    your text layout object. Attributes at this level affect the
 *    width of the text area from margin to margin, the alignment of
 *    the text, its justification, rotation, and direction, as well as
 *    other layout options. See ATSUSetLineControls for information
 *    about controling text and the line level. Similar to style
 *    attributes, you use a "triple" to specify a line or layout
 *    control attribute. That is, (1) an attribute tag, (2) the size
 *    (in bytes) of the attribute value, and (3) the value of the
 *    attribute it sets. Attribute tags are constants supplied by
 *    ATSUI. Attribute values may be a scalar, a structure, or a
 *    pointer. And as with style attributes, you can also create a
 *    custom attribute for a line or layout attribute for which ATSUI
 *    does not provide a tag. For a list of layout control tags defined
 *    by ATSUI and their default values, see the definition of
 *    ATSUAttributeTag.
 *  
 *  Parameters:
 *    
 *    iTextLayout:
 *      The text layout in which to set layout-level controls.
 *    
 *    iAttributeCount:
 *      The number of attributes to set. This value should correspond
 *      to the number of elements in the iTag, iValueSize, and iValue
 *      arrays.
 *    
 *    iTag:
 *      An array of attribute tags to set. For a list of layout control
 *      tags defined by ATSUI and their default values, see the
 *      definition of ATSUAttributeTag.
 *    
 *    iValueSize:
 *      An array of values indicating the sizes of the values pointed
 *      to by the elements in the iValue array.
 *    
 *    iValue:
 *      An array of attribute value pointers. Each value in the array
 *      must correspond to a tag in the iTag array and be a legal value
 *      for that tag.
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
ATSUSetLayoutControls(
  ATSUTextLayout                iTextLayout,
  ItemCount                     iAttributeCount,
  const ATSUAttributeTag        iTag[],
  const ByteCount               iValueSize[],
  const ATSUAttributeValuePtr   iValue[])                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUGetLayoutControl()
 *  
 *  Summary:
 *    Obtains a single layout control attribute value for a text layout
 *    object.
 *  
 *  Discussion:
 *    Before calling ATSUGetLayoutControl, you should call the function
 *    ATSUGetAllLayoutControls to obtain an array of nondefault layout
 *    control attribute tags and value sizes for the text layout
 *    object. You can then pass the tag and value size for the
 *    attribute value to obtain to ATSUGetLayoutControl. Typically you
 *    use the function ATSUGetLayoutControl by calling it twice, as
 *    follows: (1) Pass a reference to the text layout object to
 *    examine in the iTextLayout parameter, NULL for the oValue
 *    parameter, 0 for the iExpectedValueSize parameter.
 *    ATSUGetLayoutControl returns the actual size of the attribute
 *    value in the oActualValueSize parameter. (2) Allocate enough
 *    space for an array of the returned size, then call the
 *    ATSUGetLayoutControl function again, passing a valid pointer in
 *    the oValue parameter. On return, the pointer refers to the actual
 *    attribute value contained in the text layout object. For a list
 *    of layout control tags defined by ATSUI and their default values,
 *    see the definition of ATSUAttributeTag.
 *  
 *  Parameters:
 *    
 *    iTextLayout:
 *      The text layout for which you wish to obtain a single layout
 *      control value.
 *    
 *    iTag:
 *      An attribute tag specifying the layout control value you wish
 *      to obtain. For a list of layout control tags defined by ATSUI
 *      and their default values, see the definition of
 *      ATSUAttributeTag.
 *    
 *    iExpectedValueSize:
 *      The size in bytes of the buffer you have allocated for the
 *      oValue parameter.
 *    
 *    oValue:
 *      On return, the value assocaited with the layout tag specified
 *      by the iTag parameter.
 *    
 *    oActualValueSize:
 *      On return, the value contains the actual size (in bytes) of the
 *      attribute value. You should examine this parameter if you are
 *      unsure of the size of the attribute value being obtained, as in
 *      the case of custom layout control attributes.
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
ATSUGetLayoutControl(
  ATSUTextLayout          iTextLayout,
  ATSUAttributeTag        iTag,
  ByteCount               iExpectedValueSize,
  ATSUAttributeValuePtr   oValue,                   /* can be NULL */
  ByteCount *             oActualValueSize)         /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUGetAllLayoutControls()
 *  
 *  Summary:
 *    Obtains an array of non-default layout control attribute tags and
 *    value sizes for a text layout object.
 *  
 *  Discussion:
 *    This function function obtains all nondefault layout control
 *    attribute tags and their values sizes for a text layout object.
 *    You can pass a tag and value size pair obtained from
 *    ATSUGetAllLayoutControls to the function ATSUGetLayoutControl to
 *    determine the corresponding attribute value. Typically you use
 *    the function ATSUGetAllLayoutControls by calling it twice, as
 *    follows: (1) Pass a reference to the text layout object to
 *    examine in the iTextLayout parameter, NULL for the
 *    oAttributeInfoArray parameter, a pointer to an ItemCount value in
 *    the oTagValuePairCount parameter, and 0 for the
 *    iTagValuePairArraySize parameter. ATSUGetAllLayoutControls
 *    returns the size of the tag and value size arrays in the
 *    oTagValuePairCount parameter. (2) Allocate enough space for an
 *    array of the returned size, then call the
 *    ATSUGetAllLayoutControls function again, passing a valid pointer
 *    in the oAttributeInfoArray parameter. On return, the pointer
 *    refers to an array of the layout control attribute tag and value
 *    size pairs contained in the text layout object.
 *  
 *  Parameters:
 *    
 *    iTextLayout:
 *      The layout for which you wish to obtain the set of non-default
 *      layout tags.
 *    
 *    oAttributeInfoArray:
 *      On return, this array contains pairs of tags and value sizes
 *      for the object's layout control attributes that are not at
 *      default values. If you are uncertain of how much memory to
 *      allocate for this parameter, see the Discussion.
 *    
 *    iTagValuePairArraySize:
 *      A value specifying the maximum number of tag and value size
 *      pairs to obtain for the text layout object. Typically, this is
 *      equivalent to the number of ATSUAttributeInfo structures for
 *      which you have allocated memory in the oAttributeInfoArray
 *      parameter. To determine this value, see the Discussion.
 *    
 *    oTagValuePairCount:
 *      On return, the value specifies the actual number of
 *      ATSUAttributeInfo structures in the text layout object. This
 *      may be greater than the value you specified in the
 *      iTagValuePairArraySize parameter.
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
ATSUGetAllLayoutControls(
  ATSUTextLayout      iTextLayout,
  ATSUAttributeInfo   oAttributeInfoArray[],
  ItemCount           iTagValuePairArraySize,
  ItemCount *         oTagValuePairCount)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUClearLayoutControls()
 *  
 *  Summary:
 *    Restores default values to the specified layout control
 *    attributes of a text layout object.
 *  
 *  Discussion:
 *    This function removes those layout control attribute values
 *    identified by the tag constants in the iTag array and replaces
 *    them with the default values. If you specify that any currently
 *    unset attribute values be removed, the function does not return
 *    an error. For a list of layout control tags defined by ATSUI and
 *    their default values, see the definition of ATSUAttributeTag.
 *  
 *  Parameters:
 *    
 *    iTextLayout:
 *      The text layout in which you wish to clear layout controls.
 *    
 *    iTagCount:
 *      The number of tags you wish to clear. This value should
 *      correspond to the nuumber of elements in the iTag array. Pass
 *      kATSUClearAll for this parameter if you wish to clear all
 *      layout controls.
 *    
 *    iTag:
 *      An array of layout control tags to be cleared. For a list of
 *      layout control tags defined by ATSUI and their default values,
 *      see the definition of ATSUAttributeTag. You may pass NULL for
 *      this parameter if you are passing kATSUClearAll for the
 *      iTagCount parameter.
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
ATSUClearLayoutControls(
  ATSUTextLayout           iTextLayout,
  ItemCount                iTagCount,
  const ATSUAttributeTag   iTag[])            /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* ---------------------------------------------------------------------------- */
/*  ATSUI line controls                                                         */
/* ---------------------------------------------------------------------------- */
/*
 *  ATSUCopyLineControls()
 *  
 *  Summary:
 *    Copies line control attribute settings from a line in a source
 *    text layout object to a line in a destination text layout object.
 *  
 *  Discussion:
 *    This function copies all line control attribute values to a line
 *    in a destination text layout object from a line in a source text
 *    layout object, including any default (unset) values in the source
 *    line. Unset line control attributes are assigned the default
 *    values. ATSUCopyLineControls does not copy the contents of memory
 *    referenced by pointers within custom line attributes or within
 *    reference constants. You are responsible for ensuring that this
 *    memory remains valid until the source text layout object is
 *    disposed.
 *  
 *  Parameters:
 *    
 *    iSourceTextLayout:
 *      The text layout object from which to copy line control
 *      attributes.
 *    
 *    iSourceLineStart:
 *      The start of the line from which to copy line control
 *      attributes.
 *    
 *    iDestTextLayout:
 *      The text layout object for which to set line control
 *      attributes. This can be the same text layout object passed in
 *      the iSourceTextLayout parameter if you want to copy line
 *      control attributes from one line to another within a text
 *      layout object.
 *    
 *    iDestLineStart:
 *      The start of the line to which to copy line control attributes.
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
ATSUCopyLineControls(
  ATSUTextLayout       iSourceTextLayout,
  UniCharArrayOffset   iSourceLineStart,
  ATSUTextLayout       iDestTextLayout,
  UniCharArrayOffset   iDestLineStart)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUSetLineControls()
 *  
 *  Summary:
 *    Sets one or more line control values for a specified line in a
 *    text layout.
 *  
 *  Discussion:
 *    When you use ATSUI to image your text, you can control the text's
 *    display and formatting at a number of different levels: layout,
 *    line, and run. The level affected by this function is the line
 *    level. These attributes are similar to those that you can apply
 *    on a full-layout basis, but each affects only an individual text
 *    line. Note that setting line control attributes overrides the
 *    corresponding layout-level settings. Also, from a performance
 *    standpoint, it is preferable to work from the layout level and
 *    not specify such controls line by line unless necessary. Lines
 *    are determined by soft breaks that may be set in your layout. You
 *    can specify a line by giving a starting offset into the text
 *    buffer. Attributes at this level affect the width of the text
 *    area from margin to margin, the alignment of the text, its
 *    justification, rotation, and direction, as well as other layout
 *    options. Similar to style attributes, you use a "triple" to
 *    specify a line or layout control attribute. That is, (1) an
 *    attribute tag, (2) the size (in bytes) of the attribute value,
 *    and (3) the value of the attribute it sets. Attribute tags are
 *    constants supplied by ATSUI. Attribute values may be a scalar, a
 *    structure, or a pointer. And as with style attributes, you can
 *    also create a custom attribute for a line or layout attribute for
 *    which ATSUI does not provide a tag. For a list of line control
 *    tags defined by ATSUI and their default values, see the
 *    definition of ATSUAttributeTag.
 *  
 *  Parameters:
 *    
 *    iTextLayout:
 *      The layout in which you wish to set line controls.
 *    
 *    iLineStart:
 *      The starting offset of the line for which you wish to set
 *      controls.
 *    
 *    iAttributeCount:
 *      The number of attributes to set. This value should correspond
 *      to the number of elements in the iTag, iValueSize, and iValue
 *      arrays.
 *    
 *    iTag:
 *      An array of attribute tags to set. For a list of line control
 *      tags defined by ATSUI and their default values, see the
 *      definition of ATSUAttributeTag.
 *    
 *    iValueSize:
 *      An array of values indicating the sizes of the values pointed
 *      to by the elements in the iValue array.
 *    
 *    iValue:
 *      An array of attribute value pointers. Each value in the array
 *      must correspond to a tag in the iTag array and be a legal value
 *      for that tag.
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
ATSUSetLineControls(
  ATSUTextLayout                iTextLayout,
  UniCharArrayOffset            iLineStart,
  ItemCount                     iAttributeCount,
  const ATSUAttributeTag        iTag[],
  const ByteCount               iValueSize[],
  const ATSUAttributeValuePtr   iValue[])                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUGetLineControl()
 *  
 *  Summary:
 *    Obtains a single line control attribute value for a line in a
 *    text layout object.
 *  
 *  Discussion:
 *    Before calling ATSUGetLineControl, you should call the function
 *    ATSUGetAllLineControls to obtain an array of nondefault line
 *    control attribute tags and value sizes for the line. You can then
 *    pass the tag and value size for the attribute value to obtain to
 *    ATSUGetLineControl. Typically you use the function
 *    ATSUGetLineControl by calling it twice, as follows: (1) Pass a
 *    reference to the text layout object to examine in the iTextLayout
 *    parameter, NULL for the oValue parameter, 0 for the
 *    iExpectedValueSize parameter. ATSUGetLineControl returns the
 *    actual size of the attribute value in the oActualValueSize
 *    parameter. (2) Allocate enough space for an array of the returned
 *    size, then call the ATSUGetLineControl function again, passing a
 *    valid pointer in the oValue parameter. On return, the pointer
 *    refers to the actual attribute value contained for the line in
 *    the text layout object.
 *  
 *  Parameters:
 *    
 *    iTextLayout:
 *      The text layout for which to obtain a line control value.
 *    
 *    iLineStart:
 *      The start of the line for which to obtain a line control value.
 *    
 *    iTag:
 *      A tag specifying the line control value to be obtained. For a
 *      list of line control tags defined by ATSUI and their default
 *      values, see the definition of ATSUAttributeTag.
 *    
 *    iExpectedValueSize:
 *      The expected size (in bytes) of the value to obtain.
 *    
 *    oValue:
 *      On return, the actual attribute value. If you are uncertain of
 *      how much memory to allocate, see the Discussion.
 *    
 *    oActualValueSize:
 *      On return, the value contains the actual size (in bytes) of the
 *      attribute value. You should examine this parameter if you are
 *      unsure of the size of the attribute value being obtained, as in
 *      the case of custom line control attributes.
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
ATSUGetLineControl(
  ATSUTextLayout          iTextLayout,
  UniCharArrayOffset      iLineStart,
  ATSUAttributeTag        iTag,
  ByteCount               iExpectedValueSize,
  ATSUAttributeValuePtr   oValue,                   /* can be NULL */
  ByteCount *             oActualValueSize)         /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUGetAllLineControls()
 *  
 *  Summary:
 *    Obtains an array of line control attribute tags and value sizes
 *    for a line in a text layout object.
 *  
 *  Discussion:
 *    This function obtains all nondefault line control attribute tags
 *    and their values sizes for a line in a text layout object. You
 *    can pass a tag and value size pair obtained from
 *    ATSUGetAllLineControls to the function ATSUGetLineControl to
 *    determine the corresponding attribute value. Typically you use
 *    the function ATSUGetAllLineControls by calling it twice, as
 *    follows: (1) Pass a reference to the text layout object to
 *    examine in the iTextLayout parameter, the appropriate
 *    UniCharArrayOffset value in the iLineStart parameter, NULL for
 *    the oAttributeInfoArray parameter, a pointer to an ItemCount
 *    value in the oTagValuePairCount parameter, and 0 for the
 *    iTagValuePairArraySize parameter. ATSUGetAllLineControls returns
 *    the size of the tag and value size arrays in the
 *    oTagValuePairCount parameter. (2) Allocate enough space for an
 *    array of the returned size, then call the ATSUGetAllLineControls
 *    function again, passing a valid pointer in the
 *    oAttributeInfoArray parameter. On return, the pointer refers to
 *    an array of the line control attribute tag and value size pairs
 *    contained in the specified line. To obtain the nondefault layout
 *    control attribute tags and value sizes for a text layout object,
 *    call the function ATSUGetAllLayoutControls.
 *  
 *  Parameters:
 *    
 *    iTextLayout:
 *      The layout for which you wish to obtain line control
 *      information.
 *    
 *    iLineStart:
 *      The beginning of the line for which you wish to obtain line
 *      control information.
 *    
 *    oAttributeInfoArray:
 *      On return, this array contains pairs of tags and value sizes
 *      for the object's line control attributes that are not at
 *      default values. If you are uncertain of how much memory to
 *      allocate for this array, see the Discussion.
 *    
 *    iTagValuePairArraySize:
 *      The size of of the array you allocated for the
 *      oAttributeInfoArray parameter.
 *    
 *    oTagValuePairCount:
 *      On return, the value specifies the actual number of
 *      ATSUAttributeInfo structures in the line. This may be greater
 *      than the value you specified in the iTagValuePairArraySize
 *      parameter.
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
ATSUGetAllLineControls(
  ATSUTextLayout       iTextLayout,
  UniCharArrayOffset   iLineStart,
  ATSUAttributeInfo    oAttributeInfoArray[],        /* can be NULL */
  ItemCount            iTagValuePairArraySize,
  ItemCount *          oTagValuePairCount)           /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUClearLineControls()
 *  
 *  Summary:
 *    Restores default values to the specified line control attributes
 *    of a text layout object.
 *  
 *  Discussion:
 *    This function removes those line control attribute values
 *    identified by the tag constants in the iTag array and replaces
 *    them with the default values. If you specify that any currently
 *    unset attribute values be removed, the function does not return
 *    an error. For a list of line control tags defined by ATSUI and
 *    their default values, see the definition of ATSUAttributeTag.
 *  
 *  Parameters:
 *    
 *    iTextLayout:
 *      The text layout in which you wish to clear line controls.
 *    
 *    iLineStart:
 *      The start of the line in which to clear line controls.
 *    
 *    iTagCount:
 *      The number of tags you wish to clear. This value should
 *      correspond to the nuumber of elements in the iTag array. Pass
 *      kATSUClearAll to clear all line controls.
 *    
 *    iTag:
 *      An array of line control tags to be cleared. For a list of line
 *      control tags defined by ATSUI and their default values, see the
 *      definition of ATSUAttributeTag. You may pass NULL for this
 *      parameter if you are passing kATSUClearAll for the iTagCount
 *      parameter.
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
ATSUClearLineControls(
  ATSUTextLayout           iTextLayout,
  UniCharArrayOffset       iLineStart,
  ItemCount                iTagCount,
  const ATSUAttributeTag   iTag[])            /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* ---------------------------------------------------------------------------- */
/*  ATSUI style run processing                                                  */
/* ---------------------------------------------------------------------------- */
/*
 *  ATSUSetRunStyle()
 *  
 *  Summary:
 *    Defines a style run by associating style information with a run
 *    of text.
 *  
 *  Discussion:
 *    A text run consists of one or more characters that are contiguous
 *    in memory. If you associate these characters with a distinct
 *    style, you define a style run. You can use the ATSUSetRunStyle
 *    function to define a style run, by associating a style object
 *    with a run of text in a text layout object. Each text run must be
 *    assigned a style object, which may or may not differ from other
 *    style objects assigned to other text runs in a given text layout
 *    object. After calling ATSUSetRunStyle, you can call the function
 *    ATSUDrawText to display the styled text. When you call
 *    ATSUDrawText, if you have not previously assigned styles to all
 *    the characters you request to be drawn, ATSUI automatically does
 *    so. Specifically, ATSUI extends the first style it locates
 *    immediately prior (in storage order) to the unstyled characters
 *    to include those unassigned characters. If the unstyled
 *    characters are at the beginning of the text stream, ATSUI finds
 *    the first style run in the stream and extends it backward to the
 *    first character. You should call ATSUSetRunStyle whenever you
 *    create a new text layout object without any associated styles, as
 *    by using the function ATSUCreateTextLayout. You should also call
 *    ATSUSetRunStyle to assign a style to a text run in response to a
 *    user action, such as when the user selects a run of text and
 *    changes the font. You do not need to call ATSUSetRunStyle when
 *    you change style attributes or text layout attributes. In such
 *    cases, ATSUI automatically updates the layout of the text as
 *    appropriate.
 *  
 *  Parameters:
 *    
 *    iTextLayout:
 *      The layout in which you wish to set the style run.
 *    
 *    iStyle:
 *      The style to be assigned to the run of characters.
 *    
 *    iRunStart:
 *      The start of the run of characters. To specify the beginning of
 *      the text buffer, pass kATSUFromTextBeginning for this parameter.
 *    
 *    iRunLength:
 *      The end of the run of characters. To specify a run that
 *      continues to the end of the text buffer, pass kATSUToTextEnd
 *      for this parameter.
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
ATSUSetRunStyle(
  ATSUTextLayout       iTextLayout,
  ATSUStyle            iStyle,
  UniCharArrayOffset   iRunStart,
  UniCharCount         iRunLength)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUGetRunStyle()
 *  
 *  Summary:
 *    Obtains style run information for a character offset in a run of
 *    text.
 *  
 *  Discussion:
 *    You can use the ATSUGetRunStyle function to obtain the style
 *    object assigned to a given text offset. ATSUGetRunStyle also
 *    produces the encompassing text range that shares the style object
 *    with the offset. Note that the style object contains those
 *    previously set style attributes, font features, and font
 *    variations that are continuous for the range of text that
 *    includes the specified text offset. If you want to obtain all
 *    shared style information for a style run, including any unset
 *    attributes, call the function ATSUGetContinuousAttributes
 *    instead. If only one style run is set in the text layout object,
 *    and it does not cover the entire text layout object,
 *    ATSUGetRunStyle uses the style run information for the iOffset
 *    parameter to set the style run information for the remaining text.
 *  
 *  Parameters:
 *    
 *    iTextLayout:
 *      The layout for which to obtain style run information.
 *    
 *    iOffset:
 *      The beginning character for which you want to obtain style run
 *      information.
 *    
 *    oStyle:
 *      On return, the style object assigned to the range of text
 *      containing the character at iOffset. Note that if you pass an
 *      offset in the iOffset parameter that is at a style run
 *      boundary, ATSUGetRunStyle produces style run information for
 *      the following, not preceding, style run.
 *    
 *    oRunStart:
 *      On return, the offset from the beginning of the text buffer to
 *      the first character of the style run containing the character
 *      at iOffset. Note that the entire style run does not necessarily
 *      share the same unset attribute values as the character at
 *      iOffset.
 *    
 *    oRunLength:
 *      On return, the length of the style run containing the character
 *      at iOffset.
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
ATSUGetRunStyle(
  ATSUTextLayout        iTextLayout,
  UniCharArrayOffset    iOffset,
  ATSUStyle *           oStyle,
  UniCharArrayOffset *  oRunStart,
  UniCharCount *        oRunLength)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUGetContinuousAttributes()
 *  
 *  Summary:
 *    Obtains the style attribute values that are continuous over a
 *    given text range.
 *  
 *  Discussion:
 *    This function examines the specified text range to obtain the
 *    style attribute values (including those at default values) that
 *    remain consistent for the entire text range. You should call
 *    ATSUGetContinuousAttributes to determine the style information
 *    that remains constant over text that has been selected by the
 *    user.
 *  
 *  Parameters:
 *    
 *    iTextLayout:
 *      The layout for which you wish to obtain style run information.
 *    
 *    iOffset:
 *      The starting character for which to examine style run
 *      attributes. To specify the beginning of the text buffer, pass
 *      kATSUFromTextBeginning for this parameter.
 *    
 *    iLength:
 *      The length of the range of characters to examine. To specify a
 *      range that continues to the end of the text buffer, pass
 *      kATSUToTextEnd for this parameter.
 *    
 *    oStyle:
 *      On return, a style object containing those attributes which are
 *      the same for the entire text range specified by the iOffset and
 *      iLength parameters.
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
ATSUGetContinuousAttributes(
  ATSUTextLayout       iTextLayout,
  UniCharArrayOffset   iOffset,
  UniCharCount         iLength,
  ATSUStyle            oStyle)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* ---------------------------------------------------------------------------- */
/*  ATSUI tab support                                                           */
/* ---------------------------------------------------------------------------- */
/*
 *  ATSUSetTabArray()
 *  
 *  Summary:
 *    Sets a tab ruler for a text layout object.
 *  
 *  Discussion:
 *    When a tab ruler is set for a text layout object, ATSUI
 *    automatically aligns text such that any tabs characters in the
 *    text are laid out to follow the tab ruler's specifications. If
 *    you want to use tabs in your text and you also want to use the
 *    function ATSUBatchBreakLines, then you must set tabs by calling
 *    the function ATSUSetTabArray. See the definition of ATSUTab for
 *    more information about setting up a tab ruler.
 *  
 *  Parameters:
 *    
 *    iTextLayout:
 *      The layout in which to set the tab array.
 *    
 *    iTabs:
 *      An array of tabstops. See the definition of ATSUTab for more
 *      inforamation about specifying tabs.
 *    
 *    iTabCount:
 *      The number of tab stops in the iTabs array.
 *  
 *  Result:
 *    On success, noErr is returned. See MacErrors.h for possible error
 *    codes.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSUSetTabArray(
  ATSUTextLayout   iTextLayout,
  const ATSUTab    iTabs[],
  ItemCount        iTabCount)                                 AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  ATSUGetTabArray()
 *  
 *  Summary:
 *    Retrieves the tab ruler associated with a text layout object.
 *  
 *  Discussion:
 *    This function can be used to retrieve all the tabs that were
 *    previously set for a text layout object, using the function
 *    ATSUSetTabArray . All the returned tabs will be in order of
 *    position along the line.Typically you use the ATSUGetTabArray
 *    function by calling it twice, as follows: (1) Pass NULL for the
 *    oTabs parameter, 0 for the iMaxTabCount parameter, and valid
 *    values for the other parameters. The ATSUGetTabArray function
 *    returns the actual number of tabs in the oTabCount parameter. (2)
 *    Allocate enough space for a buffer of the returned size, then
 *    call the function again, passing a valid pointer to the buffer in
 *    the oTabs parameter. On return, the buffer contains the tab
 *    values in order of position along the line from left to right.
 *  
 *  Parameters:
 *    
 *    iTextLayout:
 *      The text layout for which to retrieve the tab ruler.
 *    
 *    iMaxTabCount:
 *      The size of the array you have allocated for the oTabs
 *      parameter. If you are unsure what to pass for this parameter,
 *      see the Discussion.
 *    
 *    oTabs:
 *      On return, an array of ATSUTab structures specifying the
 *      currently set tab ruler for this layout.
 *    
 *    oTabCount:
 *      On return, the number of tabs currently set in this layout.
 *      Note that this may be greater than the value you have passed
 *      for iMaxTabCount.
 *  
 *  Result:
 *    On success, noErr is returned. See MacErrors.h for possible error
 *    codes.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSUGetTabArray(
  ATSUTextLayout   iTextLayout,
  ItemCount        iMaxTabCount,
  ATSUTab          oTabs[],            /* can be NULL */
  ItemCount *      oTabCount)          /* can be NULL */      AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/* ---------------------------------------------------------------------------- */
/* ATSUI font fallback object functions                                         */
/* ---------------------------------------------------------------------------- */
/*
 *  ATSUCreateFontFallbacks()
 *  
 *  Summary:
 *    Creates an opaque object that can be set to contain a font list
 *    and a font-search method.
 *  
 *  Discussion:
 *    After using this fucntion to create an ATSUFontFallbacks object,
 *    you can then use ATSUSetObjFontFallbacks to set the fallback
 *    method for this object, and then use the
 *    kATSULineFontFallbacksTag to apply the object to a layout. You
 *    may then either call ATSUMatchFontsToText to manually perform
 *    font substitution, or call ATSUSetTransientFontMatching to
 *    perform automatic font subtitution.
 *  
 *  Parameters:
 *    
 *    oFontFallback:
 *      On return, a reference to a newly created ATSUFontFallbacks
 *      object. You are responsible for freeing this object with
 *      ATSUDisposeFontFallbacks.
 *  
 *  Result:
 *    On success, noErr is returned. See MacErrors.h for possible error
 *    codes.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSUCreateFontFallbacks(ATSUFontFallbacks * oFontFallback)    AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
 *  ATSUDisposeFontFallbacks()
 *  
 *  Summary:
 *    Disposes of an ATSUDisposeFontFallbacks object.
 *  
 *  Discussion:
 *    This function will only dispose of the ATSUDisposeFontFallbacks
 *    itself. If you have allocated an array of ATSUFontIDs for use
 *    with this ATSUFontFallbacks object, you are responsible for
 *    freeing it separately.
 *  
 *  Parameters:
 *    
 *    iFontFallbacks:
 *      The ATSUFontFallbacks object to be disposed of.
 *  
 *  Result:
 *    On success, noErr is returned. See MacErrors.h for possible error
 *    codes.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSUDisposeFontFallbacks(ATSUFontFallbacks iFontFallbacks)    AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
 *  ATSUSetObjFontFallbacks()
 *  
 *  Summary:
 *    Assigns a font-search method and a font list to a font fallback
 *    object.
 *  
 *  Discussion:
 *    This function allows you to define the settings for a font
 *    fallback object. These settings determine the method ATSUI uses
 *    to perform font fallbacks, as well as the font search list, if
 *    one is needed. Not all fallback methods require a search list.
 *    See the definition of ATSUFontFallbackMethod for more infomation
 *    about the different font fallback methods. Once you have called
 *    this function, you typically will want to associate the font
 *    fallback object with a text layout using ATSUSetLayoutControls
 *    and the kATSULineFontFallbacksTag attribute.
 *  
 *  Parameters:
 *    
 *    iFontFallbacks:
 *      The fallback object for which you wish to set or change
 *      settings.
 *    
 *    iFontFallbacksCount:
 *      The number of fonts contained in the iFonts array. Some font
 *      fallbacks methods do not require such a list. In such cases,
 *      you may pass zero for this paramter.
 *    
 *    iFonts:
 *      A list of fonts for ATSUI to search through when performing
 *      fallbacks. Some font fallbacks methods do not require such a
 *      list. In such cases, you may pass NULL for this parameter.
 *    
 *    iFontFallbackMethod:
 *      The font fallback method for ATSUI to use. See the definition
 *      of ATSUFontFallbackMethod for a list of possible constants to
 *      pass in for this paramater. Note that some fallback modes
 *      require a list of fonts for ATSUI to search. In such cases, use
 *      the iFonts and iFontFallbacksCount parameters to specify this
 *      list.
 *  
 *  Result:
 *    On success, noErr is returned. See MacErrors.h for possible error
 *    codes.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSUSetObjFontFallbacks(
  ATSUFontFallbacks        iFontFallbacks,
  ItemCount                iFontFallbacksCount,
  const ATSUFontID         iFonts[],                  /* can be NULL */
  ATSUFontFallbackMethod   iFontFallbackMethod)               AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
 *  ATSUGetObjFontFallbacks()
 *  
 *  Summary:
 *    Returns information about the current settings in an
 *    ATSUFontFallbacks object.
 *  
 *  Discussion:
 *    Information returned includes the font-search method, and the
 *    font search list, if one is set. Note that some font fallback
 *    modes do not have a client-specified search list. You must
 *    allocate space for this list.
 *  
 *  Parameters:
 *    
 *    iFontFallbacks:
 *      The font fallback object you want to know the current settings
 *      of.
 *    
 *    iMaxFontFallbacksCount:
 *      For this parameter, pass in the size of the array you are
 *      passing in for the oFonts parameter.
 *    
 *    oFonts:
 *      On input, a buffer you have allocated for storing the font
 *      search list. On return, ATSUGetObjFontFallbacks will populate
 *      the list up to iMaxFontFallbacksCount items.
 *    
 *    oFontFallbackMethod:
 *      On return, the font fallback method currently set for this
 *      object. See the definition of ATSUFontFallbackMethod for more
 *      information regarding the different font fallback modes.
 *    
 *    oActualFallbacksCount:
 *      On return, the size of the font search list. You can use this
 *      parameter to determine how much space to allocate for the
 *      oFonts parameter.
 *  
 *  Result:
 *    On success, noErr is returned. See MacErrors.h for possible error
 *    codes.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSUGetObjFontFallbacks(
  ATSUFontFallbacks         iFontFallbacks,
  ItemCount                 iMaxFontFallbacksCount,
  ATSUFontID                oFonts[],                     /* can be NULL */
  ATSUFontFallbackMethod *  oFontFallbackMethod,
  ItemCount *               oActualFallbacksCount)        /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/* ---------------------------------------------------------------------------- */
/*  ATSUI font matching                                                         */
/* ---------------------------------------------------------------------------- */
/*
 *  ATSUMatchFontsToText()
 *  
 *  Summary:
 *    Examines a text range for characters that cannot be drawn with
 *    the current font and suggests a substitute font, if necessary.
 *  
 *  Discussion:
 *    When you call the ATSUMatchFontsToText function, ATSUI scans the
 *    given range of text for characters that cannot be drawn with the
 *    currently assigned font. When ATSUI finds such a character, it
 *    identifies a substitute font for drawing the character. ATSUI
 *    then continues scanning the text range for subsequent characters
 *    that cannot be drawn, stopping when it finds a character that can
 *    be drawn with the currently assigned font, or finds a character
 *    that cannot be drawn with either the currently assigned font or
 *    the substitute font, or reaches the end of the text range you
 *    have specified. ATSUI's default behavior for finding a substitute
 *    font is to recommend the first valid font that it finds when
 *    scanning the fonts in the user's system. ATSUI first searches in
 *    the standard application fonts for various languages. If that
 *    fails, ATSUI searches through the remaining fonts on the system
 *    in the order in which the Font Manager returns the fonts. After
 *    ATSUI has searched all the fonts in the system, any unmatched
 *    text is drawn using the last-resort font. That is, missing glyphs
 *    are represented by and empty box to indicate to the user that a
 *    valid font for that character is not installed on their system.
 *    You can alter ATSUI's default search behavior by calling the
 *    function ATSUCreateFontFallbacks and defining your own font
 *    fallback settings for the text layout object. Because ATSUI does
 *    not necessarily completely scan the text range you specify with
 *    each call to ATSUMatchFontsToText, if ATSUI does find any
 *    characters that cannot be rendered with their current font, you
 *    should call ATSUMatchFontsToText again and update the input range
 *    to check that all the subsequent characters in the range can be
 *    drawn. For that reason, you should call ATSUMatchFontsToText from
 *    within a loop to assure that the entire range of text is checked.
 *    Note that calling ATSUMatchFontsToText does not cause the
 *    suggested font substitution to be performed. If you want ATSUI to
 *    perform font substitution automatically, you can call the
 *    function ATSUSetTransientFontMatching.
 *  
 *  Parameters:
 *    
 *    iTextLayout:
 *      The text layout object to examine.
 *    
 *    iTextStart:
 *      The first character of the range to examine. To start at the
 *      beginning of the text buffer, pass the constant
 *      kATSUFromTextBeginning.
 *    
 *    iTextLength:
 *      The length of the text range to examine. If you want the range
 *      of text to extend to the end of the text buffer, you can pass
 *      the constant kATSUToTextEnd.
 *    
 *    oFontID:
 *      On return, the value provides a font ID for the suggested
 *      substitute font or kATSUInvalidFontID, if no substitute font is
 *      available.
 *    
 *    oChangedOffset:
 *      On return, this value specifies the offset from the beginning
 *      of the text buffer to the first character that cannot be drawn
 *      with the current font.
 *    
 *    oChangedLength:
 *      On return, this value specifies the length of the text range
 *      that cannot be drawn with the current font.
 *  
 *  Result:
 *    The result code noErr indicates that all the characters in the
 *    given range can be rendered with their current font(s) and no
 *    font substitution is needed. If you receive either of the result
 *    codes kATSUFontsMatched or kATSUFontsNotMatched, you should
 *    update the input range and call ATSUMatchFontsToText again to
 *    ensure that all the characters in the range can be drawn. See
 *    MacErrors.h for other possible error codes.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUMatchFontsToText(
  ATSUTextLayout        iTextLayout,
  UniCharArrayOffset    iTextStart,
  UniCharCount          iTextLength,
  ATSUFontID *          oFontID,
  UniCharArrayOffset *  oChangedOffset,
  UniCharCount *        oChangedLength)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUSetTransientFontMatching()
 *  
 *  Summary:
 *    Sets the current transient font matching state for a given layout.
 *  
 *  Discussion:
 *    Transient font matching allows ATSUI to automatically substitute
 *    glyphs from other fonts if the specified styles do not contain
 *    glyphs for all the characters in the text. You can change the
 *    behavior of this font substitution by calling the function
 *    ATSUCreateFontFallbacks and defining your own font fallback
 *    settings for the text layout object.
 *  
 *  Parameters:
 *    
 *    iTextLayout:
 *      A layout for which to set the current transient font matching
 *      state.
 *    
 *    iTransientFontMatching:
 *      A boolean value indicating if the current transient font
 *      matching state to set.
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
ATSUSetTransientFontMatching(
  ATSUTextLayout   iTextLayout,
  Boolean          iTransientFontMatching)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUGetTransientFontMatching()
 *  
 *  Summary:
 *    Obtains the current transient font matching state for a given
 *    layout.
 *  
 *  Discussion:
 *    Transient font matching allows ATSUI to automatically substitute
 *    glyphs from other fonts if the specified styles do not contain
 *    glyphs for all the characters in the text. You can change the
 *    behavior of this font substitution by calling the function
 *    ATSUCreateFontFallbacks and defining your own font fallback
 *    settings for the text layout object.
 *  
 *  Parameters:
 *    
 *    iTextLayout:
 *      A layout for which to obtain the current transient font
 *      matching state.
 *    
 *    oTransientFontMatching:
 *      On return, a boolean value indicating the current transient
 *      font matching state.
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
ATSUGetTransientFontMatching(
  ATSUTextLayout   iTextLayout,
  Boolean *        oTransientFontMatching)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Functions listed beyond this point are either deprecated or not recommended */

/* ---------------------------------------------------------------------------- */
/* ATSUI global font fallback functions                                        */
/* ---------------------------------------------------------------------------- */
/*
 *  ATSUSetFontFallbacks()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    Use ATSUSetObjFontFallbacks object API instead.
 *  
 *  Summary:
 *    Sets font fallback behavior on a global basis.
 *  
 *  Discussion:
 *    Control of font fallback behavior on a global basis is no longer
 *    recommended. Object based font fallbacks are preferred. See the
 *    functions ATSUCreateFontFallbacks, ATSUDisposeFontFallbacks,
 *    ATSUSetObjFontFallbacks, and ATSUGetObjFontFallbacks, as well as
 *    the kATSULineFontFallbacksTag attribute for more information
 *    about object based font fallbacks.
 *  
 *  Result:
 *    On success, noErr is returned. See MacErrors.h for possible error
 *    codes.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.3
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.6 and later
 */
extern OSStatus 
ATSUSetFontFallbacks(
  ItemCount                iFontFallbacksCount,
  const ATSUFontID         iFontIDs[],
  ATSUFontFallbackMethod   iFontFallbackMethod)               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_3;


/*
 *  ATSUGetFontFallbacks()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    Use ATSUGetObjFontFallbacks object API instead.
 *  
 *  Summary:
 *    Gets the current global font fallback behavior.
 *  
 *  Discussion:
 *    Control of font fallback behavior on a global basis is no longer
 *    recommended. Object based font fallbacks are preferred. See the
 *    functions ATSUCreateFontFallbacks, ATSUDisposeFontFallbacks,
 *    ATSUSetObjFontFallbacks, and ATSUGetObjFontFallbacks, as well as
 *    the kATSULineFontFallbacksTag attribute for more information
 *    about object based font fallbacks.
 *  
 *  Result:
 *    On success, noErr is returned. See MacErrors.h for possible error
 *    codes.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.3
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.6 and later
 */
extern OSStatus 
ATSUGetFontFallbacks(
  ItemCount                 iMaxFontFallbacksCount,
  ATSUFontID                oFontIDs[],
  ATSUFontFallbackMethod *  oFontFallbackMethod,
  ItemCount *               oActualFallbacksCount)            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_3;


/* ---------------------------------------------------------------------------- */
/*  Handle-based functions                                                      */
/* ---------------------------------------------------------------------------- */
/*
 *  ATSUCreateTextLayoutWithTextHandle()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    Use ATSUCreateTextLayoutWithTextPtr instead.
 *  
 *  Discussion:
 *    This function is no longer recommended. Please use
 *    ATSUCreateTextLayoutWithTextPtr instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.0
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUCreateTextLayoutWithTextHandle(
  UniCharArrayHandle   iText,
  UniCharArrayOffset   iTextOffset,
  UniCharCount         iTextLength,
  UniCharCount         iTextTotalLength,
  ItemCount            iNumberOfRuns,
  const UniCharCount   iRunLengths[],
  ATSUStyle            iStyles[],
  ATSUTextLayout *     oTextLayout)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;


/*
 *  ATSUSetTextHandleLocation()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    Use ATSUSetTextPointerLocation instead.
 *  
 *  Discussion:
 *    This function is no longer recommended. Please use
 *    ATSUSetTextPointerLocation instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.0
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUSetTextHandleLocation(
  ATSUTextLayout       iTextLayout,
  UniCharArrayHandle   iText,
  UniCharArrayOffset   iTextOffset,
  UniCharCount         iTextLength,
  UniCharCount         iTextTotalLength)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;


/* ---------------------------------------------------------------------------- */
/*  ATSUI idle processing (deprecated)                                          */
/* ---------------------------------------------------------------------------- */
/*
 *  ATSUIdle()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    No longer needed on MacOS X.
 *  
 *  Summary:
 *    Performs background processing.
 *  
 *  Discussion:
 *    Current versions of ATSUI do not implement background processing
 *    for text layout objects. In Mac OS X, the function ATSUIdle does
 *    nothing.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.0
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUIdle(ATSUTextLayout iTextLayout)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;


/* ---------------------------------------------------------------------------- */
/*  ATSUI Memory allocation specification functions (not in Carbon)             */
/* ---------------------------------------------------------------------------- */
/*
 *  ATSUCreateMemorySetting()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    No longer needed on MacOS X.
 *  
 *  Discussion:
 *    ATSUI memory setting functions are not necessary on MacOS X.
 *  
 *  Availability:
 *    Mac OS X:         not available but deprecated in 10.0
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.6 and later
 */


/*
 *  ATSUSetCurrentMemorySetting()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    No longer needed on MacOS X.
 *  
 *  Discussion:
 *    ATSUI memory setting functions are not necessary on MacOS X.
 *  
 *  Availability:
 *    Mac OS X:         not available but deprecated in 10.0
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.6 and later
 */


/*
 *  ATSUGetCurrentMemorySetting()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    No longer needed on MacOS X.
 *  
 *  Discussion:
 *    ATSUI memory setting functions are not necessary on Mac OS X.
 *  
 *  Availability:
 *    Mac OS X:         not available but deprecated in 10.0
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.6 and later
 */


/*
 *  ATSUDisposeMemorySetting()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    No longer needed on MacOS X.
 *  
 *  Discussion:
 *    ATSUI memory setting functions are not necessary on MacOS X.
 *  
 *  Availability:
 *    Mac OS X:         not available but deprecated in 10.0
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.6 and later
 */



#ifdef __cplusplus
}
#endif

#endif /* __ATSUNICODEOBJECTS__ */

