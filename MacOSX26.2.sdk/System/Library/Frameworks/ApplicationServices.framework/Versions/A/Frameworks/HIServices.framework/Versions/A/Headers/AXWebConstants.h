/*
 *  AXWebConstants.h
 *  HIServices
 *
 *  Copyright (c) 2025 Apple Inc. All rights reserved.
 *
 */

#ifndef __AXWEBCONSTANTS__
#define __AXWEBCONSTANTS__

/*! @header AXWebConstants.h
    Accessibility roles, attributes, actions, notifications, etc. that are
    specific to web content.
*/

/*——————————————————————————————————————————————————————————————————————————————————————*/
/* Attributes                                                                           */
/*——————————————————————————————————————————————————————————————————————————————————————*/

// CFBooleanRef
#define kAXARIAAtomicAttribute CFSTR("AXARIAAtomic")

// CFNumberRef, 1-based
#define kAXARIAColumnCountAttribute CFSTR("AXARIAColumnCount")

// CFNumberRef, 1-based
#define kAXARIAColumnIndexAttribute CFSTR("AXARIAColumnIndex")

// CFStringRef
#define kAXARIACurrentAttribute CFSTR("AXARIACurrent")

// CFStringRef
#define kAXARIALiveAttribute CFSTR("AXARIALive")

// CFNumberRef, 1-based
#define kAXARIAPosInSetAttribute CFSTR("AXARIAPosInSet")

// CFStringRef
#define kAXARIARelevantAttribute CFSTR("AXARIARelevant")

// CFNumberRef, 1-based
#define kAXARIARowCountAttribute CFSTR("AXARIARowCount")

// CFNumberRef, 1-based
#define kAXARIARowIndexAttribute CFSTR("AXARIARowIndex")

// CFNumberRef, 1-based
#define kAXARIASetSizeAttribute CFSTR("AXARIASetSize")

// CFStringRef
#define kAXAccessKeyAttribute CFSTR("AXAccessKey")

// AXUIElementRef
#define kAXActiveElementAttribute CFSTR("AXActiveElement")

// CFStringRef
#define kAXBrailleLabelAttribute CFSTR("AXBrailleLabel")

// CFStringRef
#define kAXBrailleRoleDescriptionAttribute CFSTR("AXBrailleRoleDescription")

// CFBooleanRef
#define kAXCaretBrowsingEnabledAttribute CFSTR("AXCaretBrowsingEnabled")

// CFArrayRef of CFStringRef
#define kAXDOMClassListAttribute CFSTR("AXDOMClassList")

// CFStringRef
#define kAXDOMIdentifierAttribute CFSTR("AXDOMIdentifier")

// CFStringRef
#define kAXDatetimeValueAttribute CFSTR("AXDateTimeValue")

// CFArrayRef of AXUIElementRef
#define kAXDescribedByAttribute CFSTR("AXDescribedBy")

// CFArrayRef of CFStringRef
#define kAXDropEffectsAttribute CFSTR("AXDropEffects")

// AXUIElementRef
#define kAXEditableAncestorAttribute CFSTR("AXEditableAncestor")

// CFBooleanRef
#define kAXElementBusyAttribute CFSTR("AXElementBusy")

// AXTextMarkerRef
#define kAXEndTextMarkerAttribute CFSTR("AXEndTextMarker")

// CFArrayRef of AXUIElementRef
#define kAXErrorMessageElementsAttribute CFSTR("AXErrorMessageElements")

// CFBooleanRef
#define kAXExpandedTextValueAttribute CFSTR("AXExpandedTextValue")

// AXUIElementRef
#define kAXFocusableAncestorAttribute CFSTR("AXFocusableAncestor")

// CFBooleanRef
#define kAXGrabbedAttribute CFSTR("AXGrabbed")

// CFBooleanRef
#define kAXHasDocumentRoleAncestorAttribute CFSTR("AXHasDocumentRoleAncestor")

// CFBooleanRef
#define kAXHasPopupAttribute CFSTR("AXHasPopup")

// CFBooleanRef
#define kAXHasWebApplicationAncestorAttribute CFSTR("AXHasWebApplicationAncestor")

// AXUIElementRef
#define kAXHighestEditableAncestorAttribute CFSTR("AXHighestEditableAncestor")

// CFBooleanRef
#define kAXInlineTextAttribute CFSTR("AXInlineText")

// CFRange
#define kAXIntersectionWithSelectionRangeAttribute CFSTR("AXIntersectionWithSelectionRange")

// CFStringRef
#define kAXInvalidAttribute CFSTR("AXInvalid")

// CFStringRef
#define kAXKeyShortcutsAttribute CFSTR("AXKeyShortcutsValue")

// CFArrayRef of AXUIElementRef
#define kAXLinkUIElementsAttribute CFSTR("AXLinkUIElements")

// CFBooleanRef
#define kAXLoadedAttribute CFSTR("AXLoaded")

// CFNumber, double, 0.0 - 1.0
#define kAXLoadingProgressAttribute CFSTR("AXLoadingProgress")

// AXUIElementRef
#define kAXMathBaseAttribute CFSTR("AXMathBase")

// CFStringRef
#define kAXMathFencedCloseAttribute CFSTR("AXMathFencedClose")

// CFStringRef
#define kAXMathFencedOpenAttribute CFSTR("AXMathFencedOpen")

// AXUIElementRef
#define kAXMathFractionDenominatorAttribute CFSTR("AXMathFractionDenominator")

// AXUIElementRef
#define kAXMathFractionNumeratorAttribute CFSTR("AXMathFractionNumerator")

// CFNumberRef
#define kAXMathLineThicknessAttribute CFSTR("AXMathLineThickness")

// AXUIElementRef
#define kAXMathOverAttribute CFSTR("AXMathOver")

// CFArrayRef of CFDictionary
#define kAXMathPostscriptsAttribute CFSTR("AXMathPostscripts")

// CFArrayRef of CFDictionary
#define kAXMathPrescriptsAttribute CFSTR("AXMathPrescripts")

// AXUIElementRef
#define kAXMathRootIndexAttribute CFSTR("AXMathRootIndex")

// CFArrayRef of AXUIElementRef
#define kAXMathRootRadicandAttribute CFSTR("AXMathRootRadicand")

// AXUIElementRef
#define kAXMathSubscriptAttribute CFSTR("AXMathSubscript")

// AXUIElementRef
#define kAXMathSuperscriptAttribute CFSTR("AXMathSuperscript")

// AXUIElementRef
#define kAXMathUnderAttribute CFSTR("AXMathUnder")

// CFArrayRef of AXUIElementRef
#define kAXOwnsAttribute CFSTR("AXOwns")

// CFStringRef
#define kAXPopupValueAttribute CFSTR("AXPopupValue")

// CFBooleanRef
#define kAXPreventKeyboardDOMEventDispatchAttribute CFSTR("AXPreventKeyboardDOMEventDispatch")

// AXTextMarkerRangeRef
#define kAXSelectedTextMarkerRangeAttribute CFSTR("AXSelectedTextMarkerRange")

// AXTextMarkerRef
#define kAXStartTextMarkerAttribute CFSTR("AXStartTextMarker")

// AXTextMarkerRangeRef
#define kAXTextInputMarkedTextMarkerRangeAttribute CFSTR("AXTextInputMarkedTextMarkerRange")

// CFBooleanRef
#define kAXValueAutofillAvailableAttribute CFSTR("AXValueAutofillAvailable")

/*——————————————————————————————————————————————————————————————————————————————————————*/
/* Attributed string keys                                                               */
/*——————————————————————————————————————————————————————————————————————————————————————*/

// CFBooleanRef
#define kAXDidSpellCheckStringAttribute CFSTR("AXDidSpellCheck")

// CFBooleanRef
#define kAXHighlightStringAttribute CFSTR("AXHighlight")

// CFBooleanRef
#define kAXIsSuggestedDeletionStringAttribute CFSTR("AXIsSuggestedDeletion")

// CFBooleanRef
#define kAXIsSuggestedInsertionStringAttribute CFSTR("AXIsSuggestedInsertion")

// CFBooleanRef
#define kAXIsSuggestionStringAttribute CFSTR("AXIsSuggestion")

/*——————————————————————————————————————————————————————————————————————————————————————*/
/* Notifications                                                                        */
/*——————————————————————————————————————————————————————————————————————————————————————*/

#define kAXActiveElementChangedNotification CFSTR("AXActiveElementChanged")
#define kAXCurrentStateChangedNotification CFSTR("AXCurrentStateChanged")
#define kAXExpandedChangedNotification CFSTR("AXExpandedChanged")
#define kAXInvalidStatusChangedNotification CFSTR("AXInvalidStatusChanged")
#define kAXLayoutCompleteNotification CFSTR("AXLayoutComplete")
#define kAXLiveRegionChangedNotification CFSTR("AXLiveRegionChanged")
#define kAXLiveRegionCreatedNotification CFSTR("AXLiveRegionCreated")
#define kAXLoadCompleteNotification CFSTR("AXLoadComplete")

/*——————————————————————————————————————————————————————————————————————————————————————*/
/* Parameterized Attributes                                                             */
/*——————————————————————————————————————————————————————————————————————————————————————*/

// CFAttributedString, param: AXTextMarkerRangeRef
#define kAXAttributedStringForTextMarkerRangeParameterizedAttribute CFSTR("AXAttributedStringForTextMarkerRange")

// (NSValue *) - (rectValue); param: AXTextMarkerRangeRef
#define kAXBoundsForTextMarkerRangeParameterizedAttribute CFSTR("AXBoundsForTextMarkerRange")

// (NSValue *) - (rectValue); param: (NSValue *) - (rectValue)
#define kAXConvertRelativeFrameParameterizedAttribute CFSTR("AXConvertRelativeFrame")

// CFNumberRef; param: AXTextMarkerRef
#define kAXIndexForTextMarkerParameterizedAttribute CFSTR("AXIndexForTextMarker")

// AXTextMarkerRangeRef; param: AXTextMarkerRef
#define kAXLeftLineTextMarkerRangeForTextMarkerParameterizedAttribute CFSTR("AXLeftLineTextMarkerRangeForTextMarker")

// AXTextMarkerRangeRef; param: AXTextMarkerRef
#define kAXLeftWordTextMarkerRangeForTextMarkerParameterizedAttribute CFSTR("AXLeftWordTextMarkerRangeForTextMarker")

// CFNumberRef; param: AXTextMarkerRangeRef
#define kAXLengthForTextMarkerRangeParameterizedAttribute CFSTR("AXLengthForTextMarkerRange")

// CFNumberRef; param: AXTextMarkerRef
#define kAXLineForTextMarkerParameterizedAttribute CFSTR("AXLineForTextMarker")

// AXTextMarkerRangeRef; param: AXTextMarkerRef
#define kAXLineTextMarkerRangeForTextMarkerParameterizedAttribute CFSTR("AXLineTextMarkerRangeForTextMarker")

// AXTextMarkerRef; param: AXTextMarkerRef
#define kAXNextLineEndTextMarkerForTextMarkerParameterizedAttribute CFSTR("AXNextLineEndTextMarkerForTextMarker")

// AXTextMarkerRef; param: AXTextMarkerRef
#define kAXNextParagraphEndTextMarkerForTextMarkerParameterizedAttribute CFSTR("AXNextParagraphEndTextMarkerForTextMarker")

// AXTextMarkerRef; param: AXTextMarkerRef
#define kAXNextSentenceEndTextMarkerForTextMarkerParameterizedAttribute CFSTR("AXNextSentenceEndTextMarkerForTextMarker")

// AXTextMarkerRef; param: AXTextMarkerRef
#define kAXNextTextMarkerForTextMarkerParameterizedAttribute CFSTR("AXNextTextMarkerForTextMarker")

// AXTextMarkerRef; param: AXTextMarkerRef
#define kAXNextWordEndTextMarkerForTextMarkerParameterizedAttribute CFSTR("AXNextWordEndTextMarkerForTextMarker")

// AXTextMarkerRangeRef; param: AXTextMarkerRef
#define kAXParagraphTextMarkerRangeForTextMarkerParameterizedAttribute CFSTR("AXParagraphTextMarkerRangeForTextMarker")

// AXTextMarkerRef; param: AXTextMarkerRef
#define kAXPreviousLineStartTextMarkerForTextMarkerParameterizedAttribute CFSTR("AXPreviousLineStartTextMarkerForTextMarker")

// AXTextMarkerRef; param: AXTextMarkerRef
#define kAXPreviousParagraphStartTextMarkerForTextMarkerParameterizedAttribute CFSTR("AXPreviousParagraphStartTextMarkerForTextMarker")

// AXTextMarkerRef; param: AXTextMarkerRef
#define kAXPreviousSentenceStartTextMarkerForTextMarkerParameterizedAttribute CFSTR("AXPreviousSentenceStartTextMarkerForTextMarker")

// AXTextMarkerRef; param: AXTextMarkerRef
#define kAXPreviousTextMarkerForTextMarkerParameterizedAttribute CFSTR("AXPreviousTextMarkerForTextMarker")

// AXTextMarkerRef; param: AXTextMarkerRef
#define kAXPreviousWordStartTextMarkerForTextMarkerParameterizedAttribute CFSTR("AXPreviousWordStartTextMarkerForTextMarker")

// AXTextMarkerRangeRef; param: AXTextMarkerRef
#define kAXRightLineTextMarkerRangeForTextMarkerParameterizedAttribute CFSTR("AXRightLineTextMarkerRangeForTextMarker")

// AXTextMarkerRangeRef; param: AXTextMarkerRef
#define kAXRightWordTextMarkerRangeForTextMarkerParameterizedAttribute CFSTR("AXRightWordTextMarkerRangeForTextMarker")

// AXTextMarkerRangeRef; param: AXTextMarkerRef
#define kAXSentenceTextMarkerRangeForTextMarkerParameterizedAttribute CFSTR("AXSentenceTextMarkerRangeForTextMarker")

// CFStringRef; param: AXTextMarkerRef
#define kAXStringForTextMarkerRangeParameterizedAttribute CFSTR("AXStringForTextMarkerRange")

// AXTextMarkerRangeRef; param: AXTextMarkerRef
#define kAXStyleTextMarkerRangeForTextMarkerParameterizedAttribute CFSTR("AXStyleTextMarkerRangeForTextMarker")

// AXTextMarkerRef; param: CFNumberRef
#define kAXTextMarkerForIndexParameterizedAttribute CFSTR("AXTextMarkerForIndex")

// AXTextMarkerRef; param: (NSValue *) - (pointValue)
#define kAXTextMarkerForPositionParameterizedAttribute CFSTR("AXTextMarkerForPosition")

// CFBooleanRef; param: AXTextMarkerRef
#define kAXTextMarkerIsValidParameterizedAttribute CFSTR("AXTextMarkerIsValid")

// AXTextMarkerRangeRef; param: CFNumberRef
#define kAXTextMarkerRangeForLineParameterizedAttribute CFSTR("AXTextMarkerRangeForLine")

// AXTextMarkerRangeRef; param: AXUIElementRef
#define kAXTextMarkerRangeForUIElementParameterizedAttribute CFSTR("AXTextMarkerRangeForUIElement")

// AXTextMarkerRangeRef; param: CFArrayRef of AXTextMarkerRef
#define kAXTextMarkerRangeForUnorderedTextMarkersParameterizedAttribute CFSTR("AXTextMarkerRangeForUnorderedTextMarkers")

// AXUIElementRef; param: AXTextMarkerRef
#define kAXUIElementForTextMarkerParameterizedAttribute CFSTR("AXUIElementForTextMarker")

/*——————————————————————————————————————————————————————————————————————————————————————*/
/* Roles                                                                                */
/*——————————————————————————————————————————————————————————————————————————————————————*/

#define kAXImageMapRole CFSTR("AXImageMap")

/*——————————————————————————————————————————————————————————————————————————————————————*/
/* Subroles                                                                             */
/*——————————————————————————————————————————————————————————————————————————————————————*/

#define kAXApplicationAlertDialogSubrole CFSTR("AXApplicationAlertDialog")
#define kAXApplicationAlertSubrole CFSTR("AXApplicationAlert")
#define kAXApplicationDialogSubrole CFSTR("AXApplicationDialog")
#define kAXApplicationGroupSubrole CFSTR("AXApplicationGroup")
#define kAXApplicationLogSubrole CFSTR("AXApplicationLog")
#define kAXApplicationMarqueeSubrole CFSTR("AXApplicationMarquee")
#define kAXApplicationStatusSubrole CFSTR("AXApplicationStatus")
#define kAXApplicationTimerSubrole CFSTR("AXApplicationTimer")
#define kAXAudioSubrole CFSTR("AXAudio")
#define kAXCodeStyleGroupSubrole CFSTR("AXCodeStyleGroup")
#define kAXDefinitionSubrole CFSTR("AXDefinition")
#define kAXDeleteStyleGroupSubrole CFSTR("AXDeleteStyleGroup")
#define kAXDetailsSubrole CFSTR("AXDetails")
#define kAXDocumentArticleSubrole CFSTR("AXDocumentArticle")
#define kAXDocumentMathSubrole CFSTR("AXDocumentMath")
#define kAXDocumentNoteSubrole CFSTR("AXDocumentNote")
#define kAXEmptyGroupSubrole CFSTR("AXEmptyGroup")
#define kAXFieldsetSubrole CFSTR("AXFieldset")
#define kAXFileUploadButtonSubrole CFSTR("AXFileUploadButton")
#define kAXInsertStyleGroupSubrole CFSTR("AXInsertStyleGroup")
#define kAXLandmarkBannerSubrole CFSTR("AXLandmarkBanner")
#define kAXLandmarkComplementarySubrole CFSTR("AXLandmarkComplementary")
#define kAXLandmarkContentInfoSubrole CFSTR("AXLandmarkContentInfo")
#define kAXLandmarkMainSubrole CFSTR("AXLandmarkMain")
#define kAXLandmarkNavigationSubrole CFSTR("AXLandmarkNavigation")
#define kAXLandmarkRegionSubrole CFSTR("AXLandmarkRegion")
#define kAXLandmarkSearchSubrole CFSTR("AXLandmarkSearch")
#define kAXMathFenceOperatorSubrole CFSTR("AXMathFenceOperator")
#define kAXMathFencedSubrole CFSTR("AXMathFenced")
#define kAXMathFractionSubrole CFSTR("AXMathFraction")
#define kAXMathIdentifierSubrole CFSTR("AXMathIdentifier")
#define kAXMathMultiscriptSubrole CFSTR("AXMathMultiscript")
#define kAXMathNumberSubrole CFSTR("AXMathNumber")
#define kAXMathOperatorSubrole CFSTR("AXMathOperator")
#define kAXMathRootSubrole CFSTR("AXMathRoot")
#define kAXMathRowSubrole CFSTR("AXMathRow")
#define kAXMathSeparatorOperatorSubrole CFSTR("AXMathSeparatorOperator")
#define kAXMathSquareRootSubrole CFSTR("AXMathSquareRoot")
#define kAXMathSubscriptSuperscriptSubrole CFSTR("AXMathSubscriptSuperscript")
#define kAXMathTableCellSubrole CFSTR("AXMathTableCell")
#define kAXMathTableRowSubrole CFSTR("AXMathTableRow")
#define kAXMathTableSubrole CFSTR("AXMathTable")
#define kAXMathTextSubrole CFSTR("AXMathText")
#define kAXMathUnderOverSubrole CFSTR("AXMathUnderOver")
#define kAXMeterSubrole CFSTR("AXMeter")
#define kAXRubyInlineSubrole CFSTR("AXRubyInline")
#define kAXRubyTextSubrole CFSTR("AXRubyText")
#define kAXSubscriptStyleGroupSubrole CFSTR("AXSubscriptStyleGroup")
#define kAXSummarySubrole CFSTR("AXSummary")
#define kAXSuperscriptStyleGroupSubrole CFSTR("AXSuperscriptStyleGroup")
#define kAXTabPanelSubrole CFSTR("AXTabPanel")
#define kAXTermSubrole CFSTR("AXTerm")
#define kAXTimeGroupSubrole CFSTR("AXTimeGroup")
#define kAXUserInterfaceTooltipSubrole CFSTR("AXUserInterfaceTooltip")
#define kAXVideoSubrole CFSTR("AXVideo")
#define kAXWebApplicationSubrole CFSTR("AXWebApplication")

 #endif // __AXWEBCONSTANTS__
