/*
 *  CTFontManager.h
 *  CoreText
 *
 *  Copyright (c) 2008-2018 Apple Inc. All rights reserved.
 *
 */

/*!
    @header

    Thread Safety Information

    All functions in this header are thread safe unless otherwise specified.
*/

#ifndef __CTFONTMANAGER__
#define __CTFONTMANAGER__

#include <CoreText/CTFontDescriptor.h>
#include <CoreText/CTFontManagerErrors.h>

CF_IMPLICIT_BRIDGING_ENABLED
CF_EXTERN_C_BEGIN
CF_ASSUME_NONNULL_BEGIN

/*!
    @constant   CTRegisterBundleFonts
    @discussion If this key is defined in the application bundle info dictionary with a boolean value of true, CTFontManager will register all fonts in the Fonts subdirectory of the bundle's Resources directory in the process scope.  
*/

/*!
    @function   CTFontManagerCopyAvailablePostScriptNames
    @abstract   Returns an array of unique PostScript font names.
 
    @result     An array of CFStrings.
*/
CFArrayRef CTFontManagerCopyAvailablePostScriptNames( void ) CT_AVAILABLE(macos(10.6), ios(10.0), watchos(3.0), tvos(10.0));

/*!
    @function   CTFontManagerCopyAvailableFontFamilyNames
    @abstract   Returns an array of visible font family names sorted for UI display.

    @result     An array of CFStrings.
*/
CFArrayRef CTFontManagerCopyAvailableFontFamilyNames( void ) CT_AVAILABLE(macos(10.6), ios(10.0), watchos(3.0), tvos(10.0));

/*!
    @function   CTFontManagerCopyAvailableFontURLs
    @abstract   Returns an array of font URLs.

    @result     An array of CFURLs.
*/
CFArrayRef CTFontManagerCopyAvailableFontURLs( void ) CT_AVAILABLE(macos(10.6)) CT_UNAVAILABLE(ios, watchos, tvos);

/*!
    @function   CTFontManagerCompareFontFamilyNames
    @abstract   A CFComparatorFunction to compare font family names and sort them according to Apple guidelines.
    @discussion This function compares font family names and sorts them in the preferred order for display in user interfaces.
    @param      family1
                The first localized font family name, as CFStringRef.
    @param      family2
                The second localized font family name, as CFStringRef.
    @param      context
                Unused. Can be NULL.
    @result     A CFComparisonResult value indicating the sort order for the two family names. kCFComparisonResultGreaterThan if family1 is greater than family2, kCFComparisonResultLessThan if family1 is less than family2, and kCFComparisonResultEqualTo if they are equal.
*/
CFComparisonResult CTFontManagerCompareFontFamilyNames(
    const void *        family1,
    const void *        family2,
    void * _Nullable   context ) CT_AVAILABLE(macos(10.6)) CT_UNAVAILABLE(ios, watchos, tvos);

/*!
    @function   CTFontManagerCreateFontDescriptorsFromURL
    @abstract   Returns an array of font descriptors representing each of the fonts in the specified URL.
                Note: these font descriptors are not available through font descriptor matching.

    @param      fileURL
                A file system URL referencing a valid font file.

    @result     An array of CTFontDescriptors or NULL if there are no valid fonts.
*/
CFArrayRef _Nullable CTFontManagerCreateFontDescriptorsFromURL(
    CFURLRef            fileURL ) CT_AVAILABLE(macos(10.6), ios(7.0), watchos(2.0), tvos(9.0));

/*!
    @function   CTFontManagerCreateFontDescriptorFromData
    @abstract   Returns a font descriptor representing the font in the supplied data.
                Note: the font descriptor is not available through font descriptor matching.

    @discussion If the data contains a font collection (TTC or OTC), only the first font in the collection will be returned.

    @param      data
                A CFData containing font data.

    @result     A font descriptor created from the data or NULL if it is not a valid font.
*/
CTFontDescriptorRef _Nullable CTFontManagerCreateFontDescriptorFromData(
    CFDataRef               data ) CT_AVAILABLE(macos(10.7), ios(7.0), watchos(2.0), tvos(9.0));

/*!
    @enum       CTFontManagerScope
    @abstract   Scope for font registration.
    @constant   kCTFontManagerScopeProcess
                The font is available to the current process for the duration of the process unless directly unregistered.
    @constant   kCTFontManagerScopeUser
                The font is available to all processes for the current user session and will be available in subsequent sessions unless unregistered.
                User scope is unsupported in iOS.
    @constant   kCTFontManagerScopeSession
                The font is available to the current user session, and will not be available in subsequent sessions.
                User scope is unsupported in iOS.
*/
typedef CF_ENUM(uint32_t, CTFontManagerScope) {
    kCTFontManagerScopeNone         = 0,
    kCTFontManagerScopeProcess      = 1,
    kCTFontManagerScopeUser         = 2,    /* not supported in iOS */
    kCTFontManagerScopeSession      = 3     /* not supported in iOS */
};

/*!
    @function   CTFontManagerRegisterFontsForURL
    @abstract   Registers fonts from the specified font URL with the font manager. Registered fonts participate in font descriptor matching.

    @param      fontURL
                Font URL.

    @param      scope
                Scope constant defining the availability and lifetime of the registration. See scope constants for more details.

    @param      error
                Pointer to receive CFError in the case of failed registration.

    @result     Returns true if registration of the fonts was successful.
*/
bool CTFontManagerRegisterFontsForURL(
    CFURLRef                fontURL,
    CTFontManagerScope      scope,
    CFErrorRef *            error ) CT_AVAILABLE(macos(10.6), ios(4.1), watchos(2.0), tvos(9.0));

/*!
    @function   CTFontManagerUnregisterFontsForURL
    @abstract   Unregisters fonts from the specified font URL with the font manager. Unregistered fonts do not participate in font descriptor matching.
                iOS note: only fonts registered with CTFontManagerRegisterFontsForURL or CTFontManagerRegisterFontsForURLs can be unregistered with this API.

    @param      fontURL
                Font URL.

    @param      scope
                Scope constant defining the availability and lifetime of the registration. Should match the scope the fonts are registered in. See scope constants for more details.

    @param      error
                Pointer to receive CFError in the case of failed unregistration.

    @result     Returns true if unregistration of the fonts was successful.

*/
bool CTFontManagerUnregisterFontsForURL(
    CFURLRef                fontURL,
    CTFontManagerScope      scope,
    CFErrorRef *            error ) CT_AVAILABLE(macos(10.6), ios(4.1), watchos(2.0), tvos(9.0));

/*!
    @function   CTFontManagerRegisterGraphicsFont
    @abstract   Registers the specified graphics font with the font manager. Registered fonts participate in font descriptor matching.
                Attempts to register a font that is either already registered or contains the same PostScript name of an already registered font will fail.
                This functionality is useful for fonts that may be embedded in documents or present/constructed in memory. A graphics font is obtained
                by calling CGFontCreateWithDataProvider. Fonts that are backed by files should be registered using CTFontManagerRegisterFontsForURL.
 
    @param      font
                Graphics font to be registered.
 
    @param      error
                Pointer to receive CFError in the case of failed registration.
 
    @result     Returns true if registration of the fonts was successful.
*/
bool CTFontManagerRegisterGraphicsFont(
    CGFontRef               font,
    CFErrorRef *            error ) CT_AVAILABLE(macos(10.8), ios(4.1), watchos(2.0), tvos(9.0));
    
/*!
    @function   CTFontManagerUnregisterGraphicsFont
    @abstract   Unregisters the specified graphics font with the font manager. Unregistered fonts do not participate in font descriptor matching.
 
    @param      font
                Graphics font to be unregistered.
 
    @param      error
                Pointer to receive CFError in the case of failed unregistration.
 
    @result     Returns true if unregistration of the font was successful.
*/
bool CTFontManagerUnregisterGraphicsFont(
    CGFontRef               font,
    CFErrorRef *            error ) CT_AVAILABLE(macos(10.8), ios(4.1), watchos(2.0), tvos(9.0));

/*!
    @function   CTFontManagerRegisterFontsForURLs
    @abstract   Registers fonts from the specified font URLs with the font manager. Registered fonts are discoverable through font descriptor matching.

    @param      fontURLs
                Array of font URLs.

    @param      scope
                Scope constant defining the availability and lifetime of the registration. See scope constants for more details.

    @param      errors
                Pointer to CFArrayRef to receive array of CFError references. Each error will contain a CFArray of font URLs corresponding to kCTFontManagerErrorFontURLsKey. These URLs represent the font files that caused the error, and were not successfully registered. Must be released by caller. Can be NULL.

    @result     Returns true if registration of all font URLs was successful. Otherwise false.
*/
bool CTFontManagerRegisterFontsForURLs(
    CFArrayRef              fontURLs,
    CTFontManagerScope      scope,
    CFArrayRef _Nullable * _Nullable errors ) CT_AVAILABLE(macos(10.6), ios(4.1), watchos(2.0), tvos(9.0));

/*!
    @function   CTFontManagerUnregisterFontsForURLs
    @abstract   Unregisters fonts from the specified font URLs with the font manager. Unregistered fonts do not participate in font descriptor matching.
                iOS note: only fonts registered with CTFontManagerRegisterFontsForURL or CTFontManagerRegisterFontsForURLs can be unregistered with this API.

    @param      fontURLs
                Array of font URLs.

    @param      scope
                Scope constant defining the availability and lifetime of the registration. Should match the scope the fonts are registered in. See scope constants for more details.

    @param      errors
                Pointer to CFArrayRef to receive array of CFError references. Each error will contain a CFArray of font URLs corresponding to kCTFontManagerErrorFontURLsKey. These URLs represent the font files that caused the error, and were not successfully unregistered. Must be released by caller. Can be NULL.

    @result     Returns true if unregistration of all font URLs was successful. Otherwise false.
*/
bool CTFontManagerUnregisterFontsForURLs(
    CFArrayRef              fontURLs,
    CTFontManagerScope      scope,
    CFArrayRef _Nullable * _Nullable errors ) CT_AVAILABLE(macos(10.6), ios(4.1), watchos(2.0), tvos(9.0));

/*!
    @function   CTFontManagerEnableFontDescriptors
    @abstract   Enables or disables the matching font descriptors for font descriptor matching.

    @param      descriptors
                Array of font descriptors.

    @param      enable
                Boolean value indicating whether the fonts matching descriptors should be enabled for font descriptor matching.
*/
void CTFontManagerEnableFontDescriptors(
    CFArrayRef              descriptors,
    bool                    enable ) CT_AVAILABLE(macos(10.6)) CT_UNAVAILABLE(ios, watchos, tvos);

/*!
    @function   CTFontManagerGetScopeForURL
    @abstract   Returns the registration scope of the specified URL.

    @param      fontURL
                Font URL.

    @result     Returns the registration scope of the specified URL, will return kCTFontManagerScopeNone if not currently registered.
*/
CTFontManagerScope CTFontManagerGetScopeForURL(
    CFURLRef                fontURL ) CT_AVAILABLE(macos(10.6)) CT_UNAVAILABLE(ios, watchos, tvos);

/*!
    @function   CTFontManagerIsSupportedFontFile
    @abstract   Determines whether the referenced font data (usually by file URL) is supported on the current platform.

    @param      fontURL
                A URL to font data.

    @result     This function returns true if the URL represents a valid font that can be used on the current platform.
*/
bool CTFontManagerIsSupportedFont(
    CFURLRef                fontURL ) CT_AVAILABLE(macos(10.6)) CT_UNAVAILABLE(ios, watchos, tvos);

/*! --------------------------------------------------------------------------
    @group Manager Auto-Activation
*///--------------------------------------------------------------------------

#if defined(__BLOCKS__)
/*!
    @function   CTFontManagerCreateFontRequestRunLoopSource
    @abstract   Creates a CFRunLoopSourceRef that will be used to convey font requests from CTFontManager.
    @param      sourceOrder
                The order of the created run loop source.
    @param      createMatchesCallback
                A block to handle the font request.
    @result     A CFRunLoopSourceRef that should be added to the run loop. To stop receiving requests, invalidate this run loop source. Will return NULL on error, in the case of a duplicate requestPortName or invalid context structure.
*/
CFRunLoopSourceRef _Nullable CTFontManagerCreateFontRequestRunLoopSource(
    CFIndex         sourceOrder,
    CFArrayRef    (^createMatchesCallback)(CFDictionaryRef requestAttributes, pid_t requestingProcess)) CT_AVAILABLE(macos(10.6)) CT_UNAVAILABLE(ios, watchos, tvos);
#endif // defined(__BLOCKS__)

/*!
    @const      kCTFontManagerBundleIdentifier
    @abstract   CTFontManage bundle identifier
    @discussion The CTFontManager bundle identifier to be used with get or set global auto-activation settings.
*/
CT_EXPORT const CFStringRef kCTFontManagerBundleIdentifier CT_AVAILABLE(macos(10.6)) CT_UNAVAILABLE(ios, watchos, tvos);

/*!
    @enum
    @abstract   Auto-activation settings.
    @constant   kCTFontManagerAutoActivationDefault
                Default auto-activation setting. When specified, the application will use the global setting.
    @constant   kCTFontManagerAutoActivationDisabled
                Disables auto-activation.
    @constant   kCTFontManagerAutoActivationEnabled
                Enables auto-activation.
    @constant   kCTFontManagerAutoActivationPromptUser - deprecated and treated as kCTFontManagerAutoActivationDefault on 10.13.
                Requires user input for auto-activation. A dialog will be presented to the user to confirm auto
                activation of the font.
*/
typedef CF_ENUM(uint32_t, CTFontManagerAutoActivationSetting) {
    kCTFontManagerAutoActivationDefault     = 0,
    kCTFontManagerAutoActivationDisabled    = 1,
    kCTFontManagerAutoActivationEnabled     = 2,
    kCTFontManagerAutoActivationPromptUser CT_ENUM_DEPRECATED("Deprecated", macos(10.6, 10.13)) CT_ENUM_UNAVAILABLE(ios, watchos, tvos) = 3
};

/*!
    @function   CTFontManagerSetAutoActivationSetting
    @abstract   Sets the auto-activation for the specified bundle identifier.
    @param      bundleIdentifier
                The bundle identifier. Used to specify a particular application bundle. If NULL,
                the current application bundle will be used. If kCTFontManagerBundleIdentifier is specified,
                will set the global auto-activation settings.
    @param      setting
                The new setting.
    @discussion Function will apply the setting to the appropriate preferences location.
*/
void CTFontManagerSetAutoActivationSetting(
    CFStringRef _Nullable               bundleIdentifier,
    CTFontManagerAutoActivationSetting  setting ) CT_AVAILABLE(macos(10.6)) CT_UNAVAILABLE(ios, watchos, tvos);

/*!
    @function   CTFontManagerGetAutoActivationSetting
    @abstract   Accessor for the auto-activation setting.
    @param      bundleIdentifier
                The bundle identifier. Used to specify a particular application bundle. If NULL,
                the current application bundle will be used. If kCTFontManagerBundleIdentifier is specified,
                will set the global auto-activation settings.
    @result     Will return the auto-activation setting for specified bundle identifier.
*/
CTFontManagerAutoActivationSetting CTFontManagerGetAutoActivationSetting(
    CFStringRef _Nullable bundleIdentifier ) CT_AVAILABLE(macos(10.6)) CT_UNAVAILABLE(ios, watchos, tvos);

/*! --------------------------------------------------------------------------
    @group Manager Notifications
*///--------------------------------------------------------------------------

/*!
    @constant   kCTFontManagerRegisteredFontsChangedNotification
    @abstract   Notification name for font registry changes.
    @discussion This is the string to use as the notification name when subscribing
                to CTFontManager notifications.  This notification will be posted when fonts are added or removed.
                OS X clients should register as an observer of the notification with the distributed notification center
                for changes in session or user scopes and with the local notification center for changes in process scope.
                iOS clients should register as an observer of the notification with the local notification center for all changes.
*/
CT_EXPORT const CFStringRef kCTFontManagerRegisteredFontsChangedNotification CT_AVAILABLE(macos(10.6), ios(7.0), watchos(2.0), tvos(9.0));

CF_ASSUME_NONNULL_END
CF_EXTERN_C_END
CF_IMPLICIT_BRIDGING_DISABLED

#endif
