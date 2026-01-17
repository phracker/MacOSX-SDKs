/*
 * ColorSync - ColorSyncProfile.h
 * Copyright (c)  2008 Apple Inc.
 * All rights reserved.
 */

#ifndef __COLORSYNCPROFILE__
#define __COLORSYNCPROFILE__

#ifdef __cplusplus
extern "C" {
#endif

#include <ColorSync/ColorSyncBase.h>

typedef const struct ColorSyncProfile* ColorSyncProfileRef;

typedef struct ColorSyncProfile* ColorSyncMutableProfileRef;

CSEXTERN CFStringRef kColorSyncGenericGrayProfile;          /* com.apple.ColorSync.GenericGray  */
CSEXTERN CFStringRef kColorSyncGenericGrayGamma22Profile;   /* com.apple.ColorSync.GenericGrayGamma2.2  */
CSEXTERN CFStringRef kColorSyncGenericRGBProfile;           /* com.apple.ColorSync.GenericRGB   */
CSEXTERN CFStringRef kColorSyncGenericCMYKProfile;          /* com.apple.ColorSync.GenericCMYK  */
CSEXTERN CFStringRef kColorSyncSRGBProfile;                 /* com.apple.ColorSync.sRGB         */
CSEXTERN CFStringRef kColorSyncAdobeRGB1998Profile;         /* com.apple.ColorSync.AdobeRGB1998 */
CSEXTERN CFStringRef kColorSyncGenericLabProfile;           /* com.apple.ColorSync.GenericLab */
CSEXTERN CFStringRef kColorSyncGenericXYZProfile;           /* com.apple.ColorSync.GenericXYZ */

CSEXTERN CFStringRef kColorSyncProfileHeader;      /* com.apple.ColorSync.ProfileHeader */
CSEXTERN CFStringRef kColorSyncProfileClass;       /* com.apple.ColorSync.ProfileClass */
CSEXTERN CFStringRef kColorSyncProfileColorSpace;  /* com.apple.ColorSync.ProfileColorSpace */
CSEXTERN CFStringRef kColorSyncProfilePCS;         /* com.apple.ColorSync.PCS */
CSEXTERN CFStringRef kColorSyncProfileURL;         /* com.apple.ColorSync.ProfileURL */
CSEXTERN CFStringRef kColorSyncProfileDescription; /* com.apple.ColorSync.ProfileDescription */
CSEXTERN CFStringRef kColorSyncProfileMD5Digest;   /* com.apple.ColorSync.ProfileMD5Digest */

CSEXTERN CFTypeID ColorSyncProfileGetTypeID(void);
   /*
    * returns the CFTypeID for ColorSyncProfiles.
    */

CSEXTERN ColorSyncProfileRef ColorSyncProfileCreate(CFDataRef data, CFErrorRef* error);
   /*
    *   data   - profile data
    *   error  - (optional) pointer to the error that will be returned in case of failure
    *   
    *   returns ColorSyncProfileRef or NULL in case of failure
    */

CSEXTERN ColorSyncProfileRef ColorSyncProfileCreateWithURL(CFURLRef url, CFErrorRef* error);
   /*
    *   url    - URL to the profile data (caller needs to have privileges to read url).
    *   error  - (optional) pointer to the error that will be returned in case of failure
    *   
    *   returns ColorSyncProfileRef or NULL in case of failure
    */

CSEXTERN ColorSyncProfileRef ColorSyncProfileCreateWithName(CFStringRef name);
   /*
    *   name    - predefined profile name
    *   
    *   returns ColorSyncProfileRef or NULL in case of failure
    */

CSEXTERN ColorSyncProfileRef ColorSyncProfileCreateWithDisplayID (uint32_t displayID);
   /*
    *   displayID - system-wide unique display ID (defined by IOKIt); pass 0 for main display.
    *   
    *   returns ColorSyncProfileRef or NULL in case of failure
    */

CSEXTERN ColorSyncProfileRef ColorSyncProfileCreateDeviceProfile (CFStringRef deviceClass, CFUUIDRef deviceID, CFTypeRef profileID);
   /*
    *   deviceClass - ColorSync device class 
    *   deviceID    - deviceID registered with ColorSync
    *   profileID   - profileID registered with ColorSync; pass kColorSyncDeviceDefaultProfileID to get the default profile.
    *   
    *   See ColorSyncDevice.h for more info on deviceClass, deviceID and profileID
    *
    *   returns ColorSyncProfileRef or NULL in case of failure
    */

CSEXTERN ColorSyncMutableProfileRef ColorSyncProfileCreateMutable(void);
   /*
    *   returns empty ColorSyncMutableProfileRef or NULL in case of failure
    */

CSEXTERN ColorSyncMutableProfileRef ColorSyncProfileCreateMutableCopy(ColorSyncProfileRef prof);
   /*
    *  prof  - profile from which profile data will be copied to the created profile.
    *   
    *   returns ColorSyncMutableProfileRef or NULL in case of failure
    */

CSEXTERN ColorSyncProfileRef ColorSyncProfileCreateLink (CFArrayRef profileInfo, CFDictionaryRef options);
   /*
    *   profileInfo  - array of dictionaries, each one containing a profile object and the
    *                       information on the usage of the profile in the transform.
    *               
    *               Required keys:
    *               ==============
    *                      kColorSyncProfile           : ColorSyncProfileRef
    *                      kColorSyncRenderingIntent   : CFStringRef defining rendering intent
    *                      kColorSyncTransformTag      : CFStringRef defining which tags to use 
    *               Optional key:
    *               =============
    *                    kColorSyncBlackPointCompensation : CFBooleanRef to enable/disable BPC
    *   
    *   options      - dictionary with additional public global options (e.g. preferred CMM, quality,
    *                       etc... It can also contain custom options that are CMM specific.
    *
    *   returns ColorSyncProfileRef or NULL in case of failure
    */

CSEXTERN bool ColorSyncProfileVerify (ColorSyncProfileRef prof, CFErrorRef* errors, CFErrorRef* warnings);
   /*
    *   prof    - profile to be verified
    *
    *   errors  - returns error strings in case problems are found which 
    *                  would prevent use of the profile.
    *  
    *   warnings - returns warning strings indicating problems due to lack of
    *                       conformance with the ICC specification, but not preventing
    *                       use of the profile.
    *
    *   returns true if profile can be used or false otherwise
    */

CSEXTERN float ColorSyncProfileEstimateGammaWithDisplayID (const int32_t displayID, CFErrorRef* error);
   /*
    *   displayID - system-wide unique display ID (defined by IOKIt)
    *   error     - (optional) pointer to the error that will be returned in
    *               case of failure
    *   
    *   returns non-zero value if success or 0.0 in case of error.
    */

CSEXTERN float ColorSyncProfileEstimateGamma (ColorSyncProfileRef prof, CFErrorRef* error);
    /*
    *   prof    - profile to perform estimation on
    *   error   - (optional) pointer to the error that will be returned in
    *             case of failure
    *   
    *   returns non-zero value if success or 0.0 in case of error
    */

#define COLORSYNC_MD5_LENGTH  16

typedef struct { uint8_t digest[COLORSYNC_MD5_LENGTH]; } ColorSyncMD5;

CSEXTERN ColorSyncMD5 ColorSyncProfileGetMD5(ColorSyncProfileRef prof);
   /* 
    *   returns MD5 digest for the profile calculated as defined by
    *           ICC specification or a "zero" signature (filled with zeros)
    *           in case of failure
    */

CSEXTERN CFDataRef ColorSyncProfileCopyData (ColorSyncProfileRef prof, CFErrorRef* error);
   /*
    *   prof    - profile to copy the flattened data from
    *   error  - (optional) pointer to the error that will be returned in case of failure
    *   
    *   returns CFDataRef if success or NULL in case of failure 
    */

CSEXTERN CFURLRef ColorSyncProfileGetURL (ColorSyncProfileRef prof, CFErrorRef* error);
   /*
    *   prof   - profile to get URL from
    *   error  - (optional) pointer to the error that will be returned in case of failure
    *   
    *   returns CFURLRef if success or NULL in case of failure 
    */

CSEXTERN CFDataRef ColorSyncProfileCopyHeader (ColorSyncProfileRef prof);
   /*
    *   prof    - profile from which to copy the header
    *   
    *   returns CFDataRef containing profile header (in host endianess) or NULL in case of failure 
    */

CSEXTERN void ColorSyncProfileSetHeader (ColorSyncMutableProfileRef prof, CFDataRef header);
   /*
    *   prof        - profile in which to set the header
    *   header  - CFDataRef containing the header data (must be in host endianess)
    */

CSEXTERN CFStringRef ColorSyncProfileCopyDescriptionString (ColorSyncProfileRef prof);
   /*
    *   prof    - profile from which to copy description string
    *   
    *   returns CFStringRef containing profile description localized to current locale
    */

CSEXTERN CFArrayRef ColorSyncProfileCopyTagSignatures (ColorSyncProfileRef prof);
   /*
    *   prof    - profile from which to copy tag signatures
    *   
    *   returns CFArray with signatures (CFStringRef) of tags in the profile 
    */

CSEXTERN bool ColorSyncProfileContainsTag (ColorSyncProfileRef prof, CFStringRef signature);
   /*
    *   prof        - profile in which to search for the tag
    *   signature   - signature of the tag to be searched for
    *   
    *   returns true if tag exists or false if does not 
    */

CSEXTERN CFDataRef ColorSyncProfileCopyTag (ColorSyncProfileRef prof, CFStringRef signature);
   /*
    *   prof             - profile from which to copy the tag
    *   signature   - signature of the tag to be copied
    *   
    *   returns CFDataRef containing tag data or NULL in case of failure 
    */

CSEXTERN void ColorSyncProfileSetTag (ColorSyncMutableProfileRef prof, CFStringRef signature, CFDataRef data);
   /*
    *   prof           - profile in which to set the tag
    *   signature - signature of the tag to be set in the profile
    *   data          - CFDataRef containing the tag data
    */

CSEXTERN void ColorSyncProfileRemoveTag (ColorSyncMutableProfileRef prof, CFStringRef signature);
   /*
    *   prof              - profile from which to remove the tag
    *   signature    - signature of the tag to be removed
    *   
    *   returns true if success or false in case of failure 
    */

typedef bool (*ColorSyncProfileIterateCallback)(CFDictionaryRef profileInfo, void* userInfo);
   /*
    * Notes:
    *   1. Only validated profiles will be passed to the caller
    *   2. if the ColorSyncProfileIterateCallback returns false, the iteration stops
    */

CSEXTERN void ColorSyncIterateInstalledProfiles (ColorSyncProfileIterateCallback callBack, 
                                        uint32_t *                      seed,
                                        void*                           userInfo,
                                        CFErrorRef*                     error);
   /*
    * callBack - pointer to a client provided function (can be NULL)
    * seed     - pointer to a cache seed owned by the client
    * error    - (optional) pointer to the error that will be returned in case of failure
    *
    */

    /********************************************************************************************
    *                                                                                           *
    *   For further information on ICC profiles refer to ICC profile specification published    *
    *   by International Color Consortium at www.color.org                                      *
    *                                                                                           *
    *   ICC header file (ICC.h) containing programmatic definitions of ICC data types can be    *
    *   downloaded from the Technical Notes web page of ICC website at                          *
    *   www.color.org/technotes.xalter                                                          *
    *                                                                                           *
    ********************************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* __COLORSYNCPROFILE__ */
