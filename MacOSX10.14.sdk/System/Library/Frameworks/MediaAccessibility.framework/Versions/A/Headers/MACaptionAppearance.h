/*!
 @header
 
 @discussion
 Access to user preferences for media caption rendering.
 */

#ifndef MediaAccessibility_MACaptionAppearance_h
#define MediaAccessibility_MACaptionAppearance_h

#include <MediaAccessibility/MADefinitions.h>
#include <AvailabilityMacros.h>
#include <CoreFoundation/CoreFoundation.h>
#include <CoreFoundation/CFBase.h>
#include <CoreText/CoreText.h>
#include <CoreGraphics/CoreGraphics.h>

MA_EXTERN_C_BEGIN

CF_ASSUME_NONNULL_BEGIN

/*!
 @const kMACaptionAppearanceSettingsChangedNotification
 @abstract CFNotification sent when any user-defined captioning settings are changed.
 */
MA_EXPORT const CFStringRef kMACaptionAppearanceSettingsChangedNotification;

/*!
 @enum MACaptionAppearanceDomain
 
 @discussion
 MACaptionAppearanceDomain is used to specify which domain of preferences to access.
 
 @constant kMACaptionAppearanceDomainUser
    The user-defined preferences. This domain should be passed to retrieve settings that should be used to render captions.
 @constant kMACaptionAppearanceDomainDefault
    The system defaults which will not change during a user session. These settings should be used for comparison, not to render captions. For example, when rendering a glyph some caption render engines need to get the user-defined font and the system-defined font to determeine the final pixel size to render a glyph. Most render engines will never need to use this domain.
 */
typedef CF_ENUM(CFIndex, MACaptionAppearanceDomain) {
    kMACaptionAppearanceDomainDefault   = 0,
    kMACaptionAppearanceDomainUser      = 1,
} CF_ENUM_AVAILABLE(10_9, 7_0);


/*!
 @enum MACaptionAppearanceDisplayType
 
 @discussion
 MACaptionAppearanceDisplayType is used to specify the the type of captions that should be displayed
 
 @constant kMACaptionAppearanceDisplayTypeForcedOnly
    Only forced captions for translation should be displayed.
 @constant kMACaptionAppearanceDisplayTypeAutomatic
    If the language of the audio track differs from the system locale then captions matching the system locale should be displayed (if available).
 @constant kMACaptionAppearanceDisplayTypeAlwaysOn
    The best available captioning track should always be displayed, whether it be CC, SDH, or subtitles.
 */
typedef CF_ENUM(CFIndex, MACaptionAppearanceDisplayType) {
    kMACaptionAppearanceDisplayTypeForcedOnly     = 0,
    kMACaptionAppearanceDisplayTypeAutomatic      = 1,
    kMACaptionAppearanceDisplayTypeAlwaysOn       = 2,
} CF_ENUM_AVAILABLE(10_9, 7_0);

/*!
 @enum MACaptionAppearanceBehavior
 
 @discussion
 MACaptionAppearanceBehavior is used to determine how a preference value should be used.

 @constant kMACaptionAppearanceBehaviorUseValue
    The value should override any content, application, or otherwise-defined values.
 @constant kMACaptionAppearanceBehaviorUseContentIfAvailable
    Content, application, or otherwise-defined values should override the returned value. If no other value is defined, then the return value should be used.
 */
typedef CF_ENUM(CFIndex, MACaptionAppearanceBehavior) {
    kMACaptionAppearanceBehaviorUseValue                = 0,
    kMACaptionAppearanceBehaviorUseContentIfAvailable   = 1,
} CF_ENUM_AVAILABLE(10_9, 7_0);

/*!
 @enum MACaptionAppearanceFontStyle
 
 @discussion
 MACaptionAppearanceFontStyle is used to specify a font style
 
 @constant kMACaptionAppearanceFontStyleDefault
    Default font style.
 @constant kMACaptionAppearanceFontStyleMonospacedWithSerif
    Font style for fonts similar to Courier.
 @constant kMACaptionAppearanceFontStyleProportionalWithSerif
    Font style for fonts similar to Times New Roman.
 @constant kMACaptionAppearanceFontStyleMonospacedWithoutSerif
    Font style for fonts similar to Helvetica Monospaced.
 @constant kMACaptionAppearanceFontStyleProportionalWithoutSerif
    Font style for fonts similar to Arial.
 @constant kMACaptionAppearanceFontStyleCasual
    Font style for fonts similar to Dom and Impress.
 @constant kMACaptionAppearanceFontStyleCursive
    Font style for fonts similar to Coronet and Marigold.
 @constant kMACaptionAppearanceFontStyleSmallCapital
    Font style for fonts similar to Engravers Gothic.
 */
typedef CF_ENUM(CFIndex, MACaptionAppearanceFontStyle) {
    kMACaptionAppearanceFontStyleDefault                    = 0,
    kMACaptionAppearanceFontStyleMonospacedWithSerif        = 1,
    kMACaptionAppearanceFontStyleProportionalWithSerif      = 2,
    kMACaptionAppearanceFontStyleMonospacedWithoutSerif     = 3,
    kMACaptionAppearanceFontStyleProportionalWithoutSerif   = 4,
    kMACaptionAppearanceFontStyleCasual                     = 5,
    kMACaptionAppearanceFontStyleCursive                    = 6,
    kMACaptionAppearanceFontStyleSmallCapital               = 7,
} CF_ENUM_AVAILABLE(10_9, 7_0);

/*!
 @enum MACaptionAppearanceTextEdgeStyle
 
 @discussion
 MACaptionAppearanceTextEdgeStyle is used to specify a text-edge style.
 
 @constant kMACaptionAppearanceTextEdgeStyleUndefined
    Undefined edge style.
 @constant kMACaptionAppearanceTextEdgeStyleNone
    No edge style.
 @constant kMACaptionAppearanceTextEdgeStyleRaised
    Raised edge style.
 @constant kMACaptionAppearanceTextEdgeStyleDepressed
    Depressed edge style.
 @constant kMACaptionAppearanceTextEdgeStyleUniform
    Uniform edge style.
 @constant kMACaptionAppearanceTextEdgeStyleDropShadow
    Shadow edge style.
 */
typedef CF_ENUM(CFIndex, MACaptionAppearanceTextEdgeStyle) {
    kMACaptionAppearanceTextEdgeStyleUndefined      = 0,
    kMACaptionAppearanceTextEdgeStyleNone           = 1,
    kMACaptionAppearanceTextEdgeStyleRaised         = 2,
    kMACaptionAppearanceTextEdgeStyleDepressed      = 3,
    kMACaptionAppearanceTextEdgeStyleUniform        = 4,
    kMACaptionAppearanceTextEdgeStyleDropShadow     = 5,
} CF_ENUM_AVAILABLE(10_9, 7_0);

/*!
 @constant MAMediaCharacteristicDescribesMusicAndSoundForAccessibility
 @abstract A media characteristic that indicates that a track or media selection option includes legible content in the language of its specified locale that:
 - describes music and
 - describes sound other than spoken dialog, such as sound effects and significant silences, occurring in program audio.
 @discussion
 Legible tracks provided for accessibility purposes are typically tagged both with this characteristic as well as with MAMediaCharacteristicTranscribesSpokenDialogForAccessibility.
 A legible track provided for accessibility purposes that's associated with an audio track without music and without sound other than spoken dialog -- lacking even significant silences -- can be tagged with this characteristic, because it trivially meets these requirements.
 */

MA_EXPORT CFStringRef const MAMediaCharacteristicDescribesMusicAndSoundForAccessibility CF_AVAILABLE(10_9, 7_0);

/*!
 @constant MAMediaCharacteristicTranscribesSpokenDialogForAccessibility
 @abstract A media characteristic that indicates that a track or media selection option includes legible content in the language of its specified locale that:
 - transcribes spoken dialog and
 - identifies speakers whenever other visual cues are insufficient for a viewer to determine who is speaking.
 @discussion
 Legible tracks provided for accessibility purposes are typically tagged both with this characteristic as well as with MAMediaCharacteristicDescribesMusicAndSoundForAccessibility.
 A legible track provided for accessibility purposes that's associated with an audio track that has no spoken dialog can be tagged with this characteristic, because it trivially meets these requirements.
 */
MA_EXPORT CFStringRef const MAMediaCharacteristicTranscribesSpokenDialogForAccessibility CF_AVAILABLE(10_9, 7_0);


#pragma mark Language preferences
/*——————————————————————————————————————————————————————————————————————————————————————*/
/*! @group Language preferences                                                         */
/*——————————————————————————————————————————————————————————————————————————————————————*/
/*!
 @function MACaptionAppearanceAddSelectedLanguage
 @abstract Adds a user's selected caption language to stack of languages.
 @param domain Preference domain, see  @link MACaptionAppearanceDomain @/link
 @param language Canonical language identifier (see @link CFLocale@/link) of the user's preferred caption language.
 @result <code>true</code> if addition was successful. Unsuccessful additions are most liketly the result of invalid language codes.
 @discussion After a language is added it will appear first in the array returned by MACaptionAppearanceCopySelectedLanguages. Applications should call this anytime a user selects a specific languages for captioning tracks.

 For example, an AVFoundation clients may execute the following code in response to a user selecting a captioning track:
 <code>
 // in response to a user selection (from a pop-up menu or any other UI affordance), make the selection effective
 -[AVPlayerItem selectMediaOption:legibleOption inMediaSelectionGroup:legibleGroup];
 
 // now update system-wide captioning preferences by registering the language of the option selected by the user
  MACaptionAppearanceAddSelectedLanguage(kMACaptionAppearanceDomainUser, (CFStringRef)[[legibleOption locale] localeIdentifier]);
</code> 
 */
MA_EXPORT
bool MACaptionAppearanceAddSelectedLanguage(MACaptionAppearanceDomain domain, CFStringRef language) CF_AVAILABLE(10_9, 7_0);

/*!
 @function MACaptionAppearanceCopySelectedLanguages
 
 @abstract Copies the user's preferred caption languages.
 
 @param domain Preference domain, see  @link MACaptionAppearanceDomain @/link.
 
 @result Ordered array of preferred canonical language identifiers.
 
 @discussion Languages added using MACaptionAppearanceAddSelectedLanguage are normalized, and thus the contents of this array may have slightly different strings than those passed into MACaptionAppearanceAddSelectedLanguage.
 */
MA_EXPORT
CFArrayRef MACaptionAppearanceCopySelectedLanguages(MACaptionAppearanceDomain domain) CF_AVAILABLE(10_9, 7_0);

#pragma mark General preferences
/*——————————————————————————————————————————————————————————————————————————————————————*/
/*! @group General preferences                                                          */
/*——————————————————————————————————————————————————————————————————————————————————————*/
/*!
 @function MACaptionAppearanceGetDisplayType
 @abstract User preference representing what type of captions should be displayed
 @param domain Preference domain, see  @link MACaptionAppearanceDomain @/link.
 @result User preference representing what type of captions should be displayed. See @link MACaptionAppearanceDisplayType @/link.
 */
MA_EXPORT
MACaptionAppearanceDisplayType MACaptionAppearanceGetDisplayType(MACaptionAppearanceDomain domain) CF_AVAILABLE(10_9, 7_0);

/*!
 @function MACaptionAppearanceSetDisplayType
 @abstract User preference representing what type of captions should be displayed
 @param domain Preference domain, see  @link MACaptionAppearanceDomain @/link.
 @param displayType Captions display type, see  @link MACaptionAppearanceDisplayType @/link.
 */
MA_EXPORT
void MACaptionAppearanceSetDisplayType(MACaptionAppearanceDomain domain, MACaptionAppearanceDisplayType displayType) CF_AVAILABLE(10_9, 7_0);

/*!
 @function MACaptionAppearanceCopyPreferredCaptioningMediaCharacteristics
 @abstract User preference for captioning media characteristic
 @param domain Preference domain, see  @link MACaptionAppearanceDomain @/link.
 @result An array containing the preferred order of media characteristics for captions.
 */
MA_EXPORT
CFArrayRef MACaptionAppearanceCopyPreferredCaptioningMediaCharacteristics(MACaptionAppearanceDomain domain) CF_AVAILABLE(10_9, 7_0);



#pragma mark Color preferences
/*——————————————————————————————————————————————————————————————————————————————————————*/
/*! @group Color preferences                                                            */
/*——————————————————————————————————————————————————————————————————————————————————————*/
/*!
 @function MACaptionAppearanceCopyForegroundColor
 @abstract User preference for foreground/text color.
 @param domain Preference domain, see  @link MACaptionAppearanceDomain @/link.
 @param *behavior (see @link MACaptionAppearanceBehavior @/link)
 @result User preference for foreground/text color.
 */
MA_EXPORT
CGColorRef MACaptionAppearanceCopyForegroundColor(MACaptionAppearanceDomain domain, MACaptionAppearanceBehavior * __nullable behavior) CF_AVAILABLE(10_9, 7_0);

/*!
 @function MACaptionAppearanceCopyBackgroundColor
 @abstract User preference for background color.
 @discussion The background color is the color behind each caption glyph.
 @param domain Preference domain, see @link MACaptionAppearanceDomain @/link.
 @param *behavior (see @link MACaptionAppearanceBehavior @/link)
 @result User preference for background color.
 */
MA_EXPORT
CGColorRef MACaptionAppearanceCopyBackgroundColor(MACaptionAppearanceDomain domain, MACaptionAppearanceBehavior * __nullable behavior) CF_AVAILABLE(10_9, 7_0);

/*!
 @function MACaptionAppearanceCopyWindowColor
 @abstract User preference for window color.
 @discussion The window color is the color of a box behind all of the caption glyphs.
 @param domain Preference domain, see  @link MACaptionAppearanceDomain @/link.
 @param *behavior (see @link MACaptionAppearanceBehavior @/link)
 @result User preference for window color.
 */
MA_EXPORT
CGColorRef MACaptionAppearanceCopyWindowColor(MACaptionAppearanceDomain domain,MACaptionAppearanceBehavior * __nullable behavior) CF_AVAILABLE(10_9, 7_0);

/*!
 @function MACaptionAppearanceGetForegroundOpacity
 @abstract User preference for foreground opacity.
 @param domain Preference domain, see @link MACaptionAppearanceDomain @/link.
 @param *behavior (see @link MACaptionAppearanceBehavior @/link)
 @result User preference for foreground opacity.
 */
MA_EXPORT
CGFloat MACaptionAppearanceGetForegroundOpacity(MACaptionAppearanceDomain domain, MACaptionAppearanceBehavior * __nullable behavior) CF_AVAILABLE(10_9, 7_0);

/*!
 @function MACaptionAppearanceGetBackgroundOpacity
 @abstract User preference for background opacity.
 @param domain Preference domain, see  @link MACaptionAppearanceDomain @/link.
 @param *behavior (see @link MACaptionAppearanceBehavior @/link)
 @result User preference for background opacity.
 */
MA_EXPORT
CGFloat MACaptionAppearanceGetBackgroundOpacity(MACaptionAppearanceDomain domain, MACaptionAppearanceBehavior * __nullable behavior) CF_AVAILABLE(10_9, 7_0);

/*!
 @function MACaptionAppearanceGetWindowOpacity
 @abstract User preference for window opacity.
 @param domain Preference domain, see  @link MACaptionAppearanceDomain @/link.
 @param *behavior (see @link MACaptionAppearanceBehavior @/link)
 @result User preference for window opacity.
 */
MA_EXPORT
CGFloat MACaptionAppearanceGetWindowOpacity(MACaptionAppearanceDomain domain,MACaptionAppearanceBehavior * __nullable behavior) CF_AVAILABLE(10_9, 7_0);

/*!
 @function MACaptionAppearanceGetWindowRoundedCornerRadius
 @abstract User preference for caption-window corner radius.
 @param domain Preference domain, see  @link MACaptionAppearanceDomain @/link.
 @param *behavior (see @link MACaptionAppearanceBehavior @/link)
 @result User preference for caption-window corner radius.
 */
MA_EXPORT
CGFloat MACaptionAppearanceGetWindowRoundedCornerRadius(MACaptionAppearanceDomain domain, MACaptionAppearanceBehavior * __nullable behavior) CF_AVAILABLE(10_9, 7_0);

#pragma mark Text Preferences
/*——————————————————————————————————————————————————————————————————————————————————————*/
/*! @group Text preferences                                                             */
/*——————————————————————————————————————————————————————————————————————————————————————*/
/*!
 @function MACaptionAppearanceCopyFontForStyle
 @abstract User font preference for the specified style.
 @param domain Preference domain, see  @link MACaptionAppearanceDomain @/link.
 @param *behavior (see @link MACaptionAppearanceBehavior @/link)
 @param fontStyle Font style, see  @link MACaptionAppearanceFontStyle @/link.
 @result User font preference for the specified style.
 */
MA_EXPORT CTFontDescriptorRef MACaptionAppearanceCopyFontDescriptorForStyle(MACaptionAppearanceDomain domain,  MACaptionAppearanceBehavior * __nullable behavior, MACaptionAppearanceFontStyle fontStyle) CF_AVAILABLE(10_9, 7_0);

/*!
 @function MACaptionAppearanceGetRelativeCharacterSize
 @abstract User preference for font scaling.
 @param domain Preference domain, see  @link MACaptionAppearanceDomain @/link.
 @param *behavior (see @link MACaptionAppearanceBehavior @/link)
 @result User font scaling preference for the specified style.
 */
MA_EXPORT
CGFloat MACaptionAppearanceGetRelativeCharacterSize(MACaptionAppearanceDomain domain,  MACaptionAppearanceBehavior * __nullable behavior) CF_AVAILABLE(10_9, 7_0);

/*!
 @function MACaptionAppearanceGetTextEdgeStyle
 @abstract User preference for text edge style.
 @param domain Preference domain, see  @link MACaptionAppearanceDomain @/link.
 @param *behavior (see @link MACaptionAppearanceBehavior @/link)
 @result User preference for text edge style.
 */
MA_EXPORT
MACaptionAppearanceTextEdgeStyle MACaptionAppearanceGetTextEdgeStyle(MACaptionAppearanceDomain domain, MACaptionAppearanceBehavior * __nullable behavior) CF_AVAILABLE(10_9, 7_0);

CF_ASSUME_NONNULL_END


MA_EXTERN_C_END

#endif /* MediaAccessibility_MACaptionAppearance_h */
