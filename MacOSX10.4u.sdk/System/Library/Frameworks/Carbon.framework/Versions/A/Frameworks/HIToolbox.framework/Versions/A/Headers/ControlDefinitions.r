/*
     File:       ControlDefinitions.r
 
     Contains:   Definitions of controls provided by the Control Manager
 
     Version:    HIToolbox-227.3~63
 
     Copyright:  © 1999-2006 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

#ifndef __CONTROLDEFINITIONS_R__
#define __CONTROLDEFINITIONS_R__

#ifndef __CONTROLS_R__
#include <HIToolbox/Controls.r>
#endif

#ifndef __CORESERVICES_R__
#include <CoreServices/CoreServices.r>
#endif

#define kControlTabListResType 			'tab#'				/*  used for tab control (Appearance 1.0 and later) */
#define kControlListDescResType 		'ldes'				/*  used for list box control (Appearance 1.0 and later) */

#define kControlCheckBoxUncheckedValue 	0
#define kControlCheckBoxCheckedValue 	1
#define kControlCheckBoxMixedValue 		2

#define kControlRadioButtonUncheckedValue  0
#define kControlRadioButtonCheckedValue  1
#define kControlRadioButtonMixedValue 	2

#define popupFixedWidth 				0x01
#define popupVariableWidth 				0x02
#define popupUseAddResMenu 				0x04
#define popupUseWFont 					0x08

#define popupTitleBold 					0x0100
#define popupTitleItalic 				0x0200
#define popupTitleUnderline 			0x0400
#define popupTitleOutline 				0x0800
#define popupTitleShadow 				0x1000
#define popupTitleCondense 				0x2000
#define popupTitleExtend 				0x4000
#define popupTitleNoStyle 				0x8000

#define popupTitleLeftJust 				0x00000000
#define popupTitleCenterJust 			0x00000001
#define popupTitleRightJust 			0x000000FF

#define pushButProc 					0
#define checkBoxProc 					1
#define radioButProc 					2
#define scrollBarProc 					16
#define popupMenuProc 					1008

#define kControlLabelPart 				1
#define kControlMenuPart 				2
#define kControlTrianglePart 			4
#define kControlEditTextPart 			5					/*  Appearance 1.0 and later */
#define kControlPicturePart 			6					/*  Appearance 1.0 and later */
#define kControlIconPart 				7					/*  Appearance 1.0 and later */
#define kControlClockPart 				8					/*  Appearance 1.0 and later */
#define kControlListBoxPart 			24					/*  Appearance 1.0 and later */
#define kControlListBoxDoubleClickPart 	25					/*  Appearance 1.0 and later */
#define kControlImageWellPart 			26					/*  Appearance 1.0 and later */
#define kControlRadioGroupPart 			27					/*  Appearance 1.0.2 and later */
#define kControlButtonPart 				10
#define kControlCheckBoxPart 			11
#define kControlRadioButtonPart 		11
#define kControlUpButtonPart 			20
#define kControlDownButtonPart 			21
#define kControlPageUpPart 				22
#define kControlPageDownPart 			23
#define kControlClockHourDayPart 		9					/*  Appearance 1.1 and later */
#define kControlClockMinuteMonthPart 	10					/*  Appearance 1.1 and later */
#define kControlClockSecondYearPart 	11					/*  Appearance 1.1 and later */
#define kControlClockAMPMPart 			12					/*  Appearance 1.1 and later */
#define kControlDataBrowserPart 		24					/*  CarbonLib 1.0 and later */
#define kControlDataBrowserDraggedPart 	25					/*  CarbonLib 1.0 and later */

#define kControlBevelButtonSmallBevelProc  32
#define kControlBevelButtonNormalBevelProc  33
#define kControlBevelButtonLargeBevelProc  34

#define kControlBevelButtonSmallBevelVariant  0
#define kControlBevelButtonNormalBevelVariant  0x01
#define kControlBevelButtonLargeBevelVariant  0x02
#define kControlBevelButtonMenuOnRightVariant  0x04

#define kControlBevelButtonSmallBevel 	0
#define kControlBevelButtonNormalBevel 	1
#define kControlBevelButtonLargeBevel 	2

#define kControlBehaviorPushbutton 		0
#define kControlBehaviorToggles 		0x0100
#define kControlBehaviorSticky 			0x0200
#define kControlBehaviorSingleValueMenu  0
#define kControlBehaviorMultiValueMenu 	0x4000				/*  only makes sense when a menu is attached. */
#define kControlBehaviorOffsetContents 	0x8000

#define kControlBehaviorCommandMenu 	0x2000				/*  menu holds commands, not choices. Overrides multi-value bit. */
#define kControlBevelButtonMenuOnBottom  0
#define kControlBevelButtonMenuOnRight 	0x04

#define kControlKindBevelButton 		'bevl'
#define kControlBevelButtonAlignSysDirection  (-1)			/*  only left or right */
#define kControlBevelButtonAlignCenter 	0
#define kControlBevelButtonAlignLeft 	1
#define kControlBevelButtonAlignRight 	2
#define kControlBevelButtonAlignTop 	3
#define kControlBevelButtonAlignBottom 	4
#define kControlBevelButtonAlignTopLeft  5
#define kControlBevelButtonAlignBottomLeft  6
#define kControlBevelButtonAlignTopRight  7
#define kControlBevelButtonAlignBottomRight  8

#define kControlBevelButtonAlignTextSysDirection  0
#define kControlBevelButtonAlignTextCenter  1
#define kControlBevelButtonAlignTextFlushRight  (-1)
#define kControlBevelButtonAlignTextFlushLeft  (-2)

#define kControlBevelButtonPlaceSysDirection  (-1)			/*  if graphic on right, then on left */
#define kControlBevelButtonPlaceNormally  0
#define kControlBevelButtonPlaceToRightOfGraphic  1
#define kControlBevelButtonPlaceToLeftOfGraphic  2
#define kControlBevelButtonPlaceBelowGraphic  3
#define kControlBevelButtonPlaceAboveGraphic  4

#define kControlBevelButtonContentTag 	'cont'				/*  ButtonContentInfo */
#define kControlBevelButtonTransformTag  'tran'				/*  IconTransformType */
#define kControlBevelButtonTextAlignTag  'tali'				/*  ButtonTextAlignment */
#define kControlBevelButtonTextOffsetTag  'toff'			/*  SInt16 */
#define kControlBevelButtonGraphicAlignTag  'gali'			/*  ButtonGraphicAlignment */
#define kControlBevelButtonGraphicOffsetTag  'goff'			/*  Point */
#define kControlBevelButtonTextPlaceTag  'tplc'				/*  ButtonTextPlacement */
#define kControlBevelButtonMenuValueTag  'mval'				/*  SInt16 */
#define kControlBevelButtonMenuHandleTag  'mhnd'			/*  MenuRef */
#define kControlBevelButtonMenuRefTag 	'mhnd'				/*  MenuRef */
#define kControlBevelButtonCenterPopupGlyphTag  'pglc'		/*  Boolean: true = center, false = bottom right */

#define kControlBevelButtonLastMenuTag 	'lmnu'				/*  SInt16: menuID of last menu item selected from */
#define kControlBevelButtonMenuDelayTag  'mdly'				/*  SInt32: ticks to delay before menu appears */

															/*  Boolean: True = if an icon of the ideal size for */
															/*  the button isn't available, scale a larger or */
															/*  smaller icon to the ideal size. False = don't */
															/*  scale; draw a smaller icon or clip a larger icon. */
															/*  Default is false. Only applies to IconSuites and */
#define kControlBevelButtonScaleIconTag  'scal'				/*  IconRefs. */
#define kControlBevelButtonOwnedMenuRefTag  'omrf'			/*  MenuRef (control will dispose) */
#define kControlBevelButtonKindTag 		'bebk'				/*  ThemeButtonKind ( kTheme[Small,Medium,Large,Rounded]BevelButton ) */

#define kControlBevelButtonIsMultiValueMenuTag  'mult'
#define kControlSliderProc 				48
#define kControlSliderLiveFeedback 		0x01
#define kControlSliderHasTickMarks 		0x02
#define kControlSliderReverseDirection 	0x04
#define kControlSliderNonDirectional 	0x08

#define kControlSliderPointsDownOrRight  0
#define kControlSliderPointsUpOrLeft 	1
#define kControlSliderDoesNotPoint 		2

#define kControlKindSlider 				'sldr'
#define kControlTriangleProc 			64
#define kControlTriangleLeftFacingProc 	65
#define kControlTriangleAutoToggleProc 	66
#define kControlTriangleLeftFacingAutoToggleProc  67

#define kControlKindDisclosureTriangle 	'dist'
#define kControlTriangleLastValueTag 	'last'				/*  SInt16 */
#define kControlProgressBarProc 		80
#define kControlRelevanceBarProc 		81

#define kControlKindProgressBar 		'prgb'
#define kControlKindRelevanceBar 		'relb'

#define kControlProgressBarIndeterminateTag  'inde'			/*  Boolean */
#define kControlProgressBarAnimatingTag  'anim'				/*  Boolean */

#define kControlLittleArrowsProc 		96
#define kControlKindLittleArrows 		'larr'
#define kControlLittleArrowsIncrementValueTag  'incr'
#define kControlChasingArrowsProc 		112
#define kControlKindChasingArrows 		'carr'
#define kControlChasingArrowsAnimatingTag  'anim'			/*  Boolean */
#define kControlTabLargeProc 			128					/*  Large tab size, north facing    */
#define kControlTabSmallProc 			129					/*  Small tab size, north facing    */
#define kControlTabLargeNorthProc 		128					/*  Large tab size, north facing    */
#define kControlTabSmallNorthProc 		129					/*  Small tab size, north facing    */
#define kControlTabLargeSouthProc 		130					/*  Large tab size, south facing    */
#define kControlTabSmallSouthProc 		131					/*  Small tab size, south facing    */
#define kControlTabLargeEastProc 		132					/*  Large tab size, east facing     */
#define kControlTabSmallEastProc 		133					/*  Small tab size, east facing     */
#define kControlTabLargeWestProc 		134					/*  Large tab size, west facing     */
#define kControlTabSmallWestProc 		135					/*  Small tab size, west facing     */

#define kControlTabDirectionNorth 		0
#define kControlTabDirectionSouth 		1
#define kControlTabDirectionEast 		2
#define kControlTabDirectionWest 		3

#define kControlKindTabs 				'tabs'
#define kControlTabContentRectTag 		'rect'				/*  Rect */
#define kControlTabEnabledFlagTag 		'enab'				/*  Boolean */
#define kControlTabFontStyleTag 		'font'				/*  ControlFontStyleRec */

#define kControlTabInfoTag 				'tabi'				/*  ControlTabInfoRec */
#define kControlTabImageContentTag 		'cont'				/*  ControlButtonContentInfo */
#define kControlTabInfoVersionZero 		0					/*  ControlTabInfoRec */
#define kControlTabInfoVersionOne 		1					/*  ControlTabInfoRecV1 */

#define kControlSeparatorLineProc 		144
#define kControlKindSeparator 			'sepa'
#define kControlGroupBoxTextTitleProc 	160
#define kControlGroupBoxCheckBoxProc 	161
#define kControlGroupBoxPopupButtonProc  162
#define kControlGroupBoxSecondaryTextTitleProc  164
#define kControlGroupBoxSecondaryCheckBoxProc  165
#define kControlGroupBoxSecondaryPopupButtonProc  166

#define kControlKindGroupBox 			'grpb'
#define kControlKindCheckGroupBox 		'cgrp'
#define kControlKindPopupGroupBox 		'pgrp'

#define kControlGroupBoxMenuHandleTag 	'mhan'				/*  MenuRef (popup title only) */
#define kControlGroupBoxMenuRefTag 		'mhan'				/*  MenuRef (popup title only) */
#define kControlGroupBoxFontStyleTag 	'font'				/*  ControlFontStyleRec */

#define kControlGroupBoxTitleRectTag 	'trec'				/*  Rect. Rectangle that the title text/control is drawn in. (get only) */
#define kControlGroupBoxFrameRectTag 	'frec'
#define kControlImageWellProc 			176
#define kControlKindImageWell 			'well'
#define kControlImageWellContentTag 	'cont'				/*  ButtonContentInfo */
#define kControlImageWellTransformTag 	'tran'				/*  IconTransformType */
#define kControlImageWellIsDragDestinationTag  'drag'		/*  Boolean */

#define kControlPopupArrowEastProc 		192
#define kControlPopupArrowWestProc 		193
#define kControlPopupArrowNorthProc 	194
#define kControlPopupArrowSouthProc 	195
#define kControlPopupArrowSmallEastProc  196
#define kControlPopupArrowSmallWestProc  197
#define kControlPopupArrowSmallNorthProc  198
#define kControlPopupArrowSmallSouthProc  199

#define kControlPopupArrowOrientationEast  0
#define kControlPopupArrowOrientationWest  1
#define kControlPopupArrowOrientationNorth  2
#define kControlPopupArrowOrientationSouth  3

#define kControlPopupArrowSizeNormal 	0
#define kControlPopupArrowSizeSmall 	1

#define kControlKindPopupArrow 			'parr'
#define kControlPlacardProc 			224
#define kControlKindPlacard 			'plac'
#define kControlClockTimeProc 			240
#define kControlClockTimeSecondsProc 	241
#define kControlClockDateProc 			242
#define kControlClockMonthYearProc 		243

#define kControlClockTypeHourMinute 	0
#define kControlClockTypeHourMinuteSecond  1
#define kControlClockTypeMonthDayYear 	2
#define kControlClockTypeMonthYear 		3

#define kControlClockFlagStandard 		0					/*  editable, non-live */
#define kControlClockNoFlags 			0
#define kControlClockFlagDisplayOnly 	1					/*  add this to become non-editable */
#define kControlClockIsDisplayOnly 		1
#define kControlClockFlagLive 			2					/*  automatically shows current time on idle. only valid with display only. */
#define kControlClockIsLive 			2

#define kControlKindClock 				'clck'
#define kControlClockLongDateTag 		'date'				/*  LongDateRec */
#define kControlClockFontStyleTag 		'font'				/*  ControlFontStyleRec */
#define kControlClockAnimatingTag 		'anim'				/*  Boolean */

#define kControlUserPaneProc 			256
#define kControlKindUserPane 			'upan'
#define kControlUserItemDrawProcTag 	'uidp'				/*  UserItemUPP */
#define kControlUserPaneDrawProcTag 	'draw'				/*  ControlUserPaneDrawUPP */
#define kControlUserPaneHitTestProcTag 	'hitt'				/*  ControlUserPaneHitTestUPP */
#define kControlUserPaneTrackingProcTag  'trak'				/*  ControlUserPaneTrackingUPP */
#define kControlUserPaneIdleProcTag 	'idle'				/*  ControlUserPaneIdleUPP */
#define kControlUserPaneKeyDownProcTag 	'keyd'				/*  ControlUserPaneKeyDownUPP */
#define kControlUserPaneActivateProcTag  'acti'				/*  ControlUserPaneActivateUPP */
#define kControlUserPaneFocusProcTag 	'foci'				/*  ControlUserPaneFocusUPP */
#define kControlUserPaneBackgroundProcTag  'back'			/*  ControlUserPaneBackgroundUPP */

#define kControlEditTextProc 			272
#define kControlEditTextPasswordProc 	274

#define kControlEditTextInlineInputProc  276				/*  Can't combine with the other variants */
#define kControlKindEditText 			'etxt'
#define kControlEditTextStyleTag 		'font'				/*  ControlFontStyleRec */
#define kControlEditTextTextTag 		'text'				/*  Buffer of chars - you supply the buffer */
#define kControlEditTextTEHandleTag 	'than'				/*  The TEHandle of the text edit record */
#define kControlEditTextKeyFilterTag 	'fltr'
#define kControlEditTextSelectionTag 	'sele'				/*  ControlEditTextSelectionRec */
#define kControlEditTextPasswordTag 	'pass'				/*  The clear text password text */
#define kControlEditTextCharCount 		'chrc'				/*  Count of characters in the control's text */

#define kControlEditTextKeyScriptBehaviorTag  'kscr'		/*  ControlKeyScriptBehavior. Defaults to "PrefersRoman" for password fields, */
															/*        or "AllowAnyScript" for non-password fields. */
#define kControlEditTextLockedTag 		'lock'				/*  Boolean. Locking disables editability. */
#define kControlEditTextFixedTextTag 	'ftxt'				/*  Like the normal text tag, but fixes inline input first */
#define kControlEditTextValidationProcTag  'vali'			/*  ControlEditTextValidationUPP. Called when a key filter can't be: after cut, paste, etc. */
#define kControlEditTextInlinePreUpdateProcTag  'prup'		/*  TSMTEPreUpdateUPP and TSMTEPostUpdateUpp. For use with inline input variant... */
#define kControlEditTextInlinePostUpdateProcTag  'poup'		/*  ...The refCon parameter will contain the ControlRef. */

#define kControlEditTextCFStringTag 	'cfst'				/*  CFStringRef (Also available on CarbonLib 1.5) */
#define kControlEditTextPasswordCFStringTag  'pwcf'			/*  CFStringRef */

#define kControlStaticTextProc 			288
#define kControlKindStaticText 			'stxt'
#define kControlStaticTextStyleTag 		'font'
#define kControlStaticTextTextTag 		'text'
#define kControlStaticTextTextHeightTag  'thei'
#define kControlStaticTextTruncTag 		'trun'
#define kControlStaticTextCFStringTag 	'cfst'
#define kControlStaticTextIsMultilineTag  'stim'

#define kControlPictureProc 			304
#define kControlPictureNoTrackProc 		305					/*  immediately returns kControlPicturePart */

#define kControlKindPicture 			'pict'
#define kControlPictureHandleTag 		'pich'				/*  PicHandle */
#define kControlIconProc 				320
#define kControlIconNoTrackProc 		321					/*  immediately returns kControlIconPart */
#define kControlIconSuiteProc 			322
#define kControlIconSuiteNoTrackProc 	323					/*  immediately returns kControlIconPart */

															/*  icon ref controls may have either an icon, color icon, icon suite, or icon ref. */
															/*  for data other than icon, you must set the data by passing a */
															/*  ControlButtonContentInfo to SetControlData */
#define kControlIconRefProc 			324
#define kControlIconRefNoTrackProc 		325					/*  immediately returns kControlIconPart */

#define kControlKindIcon 				'icon'
#define kControlIconTransformTag 		'trfm'				/*  IconTransformType */
#define kControlIconAlignmentTag 		'algn'				/*  IconAlignmentType */

#define kControlIconResourceIDTag 		'ires'				/*  SInt16 resource ID of icon to use */
#define kControlIconContentTag 			'cont'				/*  accepts a ControlButtonContentInfo */

#define kControlWindowHeaderProc 		336					/*  normal header */
#define kControlWindowListViewHeaderProc  337				/*  variant for list views - no bottom line */

#define kControlKindWindowHeader 		'whed'
#define kControlWindowHeaderIsListHeaderTag  'islh'
#define kControlListBoxProc 			352
#define kControlListBoxAutoSizeProc 	353

#define kControlKindListBox 			'lbox'
#define kControlListBoxListHandleTag 	'lhan'				/*  ListHandle */
#define kControlListBoxKeyFilterTag 	'fltr'				/*  ControlKeyFilterUPP */
#define kControlListBoxFontStyleTag 	'font'				/*  ControlFontStyleRec */

#define kControlListBoxDoubleClickTag 	'dblc'				/*  Boolean. Was last click a double-click? */
#define kControlListBoxLDEFTag 			'ldef'				/*  SInt16. ID of LDEF to use. */

#define kControlPushButtonProc 			368
#define kControlCheckBoxProc 			369
#define kControlRadioButtonProc 		370
#define kControlPushButLeftIconProc 	374					/*  Standard pushbutton with left-side icon */
#define kControlPushButRightIconProc 	375					/*  Standard pushbutton with right-side icon */

#define kControlCheckBoxAutoToggleProc 	371
#define kControlRadioButtonAutoToggleProc  372

#define kControlPushButtonIconOnLeft 	6
#define kControlPushButtonIconOnRight 	7

#define kControlKindPushButton 			'push'
#define kControlKindPushIconButton 		'picn'
#define kControlKindRadioButton 		'rdio'
#define kControlKindCheckBox 			'cbox'

#define kControlPushButtonDefaultTag 	'dflt'				/*  default ring flag */
#define kControlPushButtonCancelTag 	'cncl'				/*  cancel button flag (1.1 and later) */

#define kControlScrollBarProc 			384					/*  normal scroll bar */
#define kControlScrollBarLiveProc 		386					/*  live scrolling variant */

#define kControlKindScrollBar 			'sbar'
#define kControlPopupButtonProc 		400
#define kControlPopupFixedWidthVariant 	0x01
#define kControlPopupVariableWidthVariant  0x02
#define kControlPopupUseAddResMenuVariant  0x04
#define kControlPopupUseWFontVariant 	0x08

#define kControlKindPopupButton 		'popb'
#define kControlPopupButtonMenuHandleTag  'mhan'			/*  MenuRef */
#define kControlPopupButtonMenuRefTag 	'mhan'				/*  MenuRef */
#define kControlPopupButtonMenuIDTag 	'mnid'				/*  SInt16 */

#define kControlPopupButtonExtraHeightTag  'exht'			/*  SInt16 - extra vertical whitespace within the button */
#define kControlPopupButtonOwnedMenuRefTag  'omrf'			/*  MenuRef */

#define kControlPopupButtonCheckCurrentTag  'chck'			/*  Boolean    - whether the popup puts a checkmark next to the current item (defaults to true) */
#define kControlRadioGroupProc 			416
#define kControlKindRadioGroup 			'rgrp'
#define kControlScrollTextBoxProc 		432
#define kControlScrollTextBoxAutoScrollProc  433

#define kControlKindScrollingTextBox 	'stbx'
#define kControlScrollTextBoxDelayBeforeAutoScrollTag  'stdl' /*  UInt32 (ticks until autoscrolling starts) */
#define kControlScrollTextBoxDelayBetweenAutoScrollTag  'scdl' /*  UInt32 (ticks between scrolls) */
#define kControlScrollTextBoxAutoScrollAmountTag  'samt'	/*  UInt16 (pixels per scroll) -- defaults to 1 */
#define kControlScrollTextBoxContentsTag  'tres'			/*  SInt16 (resource ID of 'TEXT'/'styl') -- write only! */
#define kControlScrollTextBoxAnimatingTag  'anim'			/*  Boolean (whether the text box should auto-scroll) */

#define kControlKindDisclosureButton 	'disb'
#define kControlDisclosureButtonClosed 	0
#define kControlDisclosureButtonDisclosed  1

#define kControlRoundButtonNormalSize 	0
#define kControlRoundButtonLargeSize 	2

#define kControlRoundButtonContentTag 	'cont'				/*  ControlButtonContentInfo */
#define kControlRoundButtonSizeTag 		'size'				/*  ControlRoundButtonSize */

#define kControlKindRoundButton 		'rndb'
#define kControlKindDataBrowser 		'datb'
#define kDataBrowserNoView 				'????'				/*  Error State  */
#define kDataBrowserListView 			'lstv'
#define kDataBrowserColumnView 			'clmv'

#define kDataBrowserDragSelect 			0x01				/*  Å ListMgr lNoRect  */
#define kDataBrowserSelectOnlyOne 		0x02				/*  Å ListMgr lOnlyOne  */
#define kDataBrowserResetSelection 		0x04				/*  Å ListMgr lNoExtend  */
#define kDataBrowserCmdTogglesSelection  0x08				/*  Å ListMgr lUseSense  */
#define kDataBrowserNoDisjointSelection  0x10				/*  Å ListMgr lNoDisjoint  */
#define kDataBrowserAlwaysExtendSelection  0x20				/*  Å ListMgr lExtendDrag  */
#define kDataBrowserNeverEmptySelectionSet  0x40			/*  Å ListMgr lNoNilHilite  */

#define kDataBrowserOrderUndefined 		0					/*  Not currently supported  */
#define kDataBrowserOrderIncreasing 	1
#define kDataBrowserOrderDecreasing 	2

															/*  == Corresponding data type or structure ==  */
#define kDataBrowserCustomType 			'????'				/*  No associated data, custom callbacks used  */
#define kDataBrowserIconType 			'icnr'				/*  IconRef, IconTransformType, RGBColor  */
#define kDataBrowserTextType 			'text'				/*  CFStringRef  */
#define kDataBrowserDateTimeType 		'date'				/*  DateTime or LongDateTime  */
#define kDataBrowserSliderType 			'sldr'				/*  Min, Max, Value  */
#define kDataBrowserCheckboxType 		'chbx'				/*  ThemeButtonValue  */
#define kDataBrowserProgressBarType 	'prog'				/*  Min, Max, Value  */
#define kDataBrowserRelevanceRankType 	'rank'				/*  Min, Max, Value  */
#define kDataBrowserPopupMenuType 		'menu'				/*  MenuRef, Value  */
#define kDataBrowserIconAndTextType 	'ticn'				/*  IconRef, CFStringRef, etc  */

#define kDataBrowserPropertyEnclosingPart  0
#define kDataBrowserPropertyContentPart  '----'
#define kDataBrowserPropertyDisclosurePart  'disc'
#define kDataBrowserPropertyTextPart 	'text'
#define kDataBrowserPropertyIconPart 	'icnr'
#define kDataBrowserPropertySliderPart 	'sldr'
#define kDataBrowserPropertyCheckboxPart  'chbx'
#define kDataBrowserPropertyProgressBarPart  'prog'
#define kDataBrowserPropertyRelevanceRankPart  'rank'

#define kDataBrowserUniversalPropertyFlagsMask  0xFF
#define kDataBrowserPropertyIsMutable 	0x01
#define kDataBrowserDefaultPropertyFlags  0x00
#define kDataBrowserUniversalPropertyFlags  0xFF			/*  support for an old name */
#define kDataBrowserPropertyIsEditable 	0x01				/*  support for an old name */

#define kDataBrowserPropertyFlagsOffset  8
#define kDataBrowserPropertyFlagsMask 	0xFF00
#define kDataBrowserCheckboxTriState 	0x0100				/*  kDataBrowserCheckboxType */
#define kDataBrowserDateTimeRelative 	0x0100				/*  kDataBrowserDateTimeType  */
#define kDataBrowserDateTimeDateOnly 	0x0200				/*  kDataBrowserDateTimeType  */
#define kDataBrowserDateTimeTimeOnly 	0x0400				/*  kDataBrowserDateTimeType  */
#define kDataBrowserDateTimeSecondsToo 	0x0800				/*  kDataBrowserDateTimeType  */
#define kDataBrowserSliderPlainThumb 	0x00				/*  kDataBrowserSliderType  */
#define kDataBrowserSliderUpwardThumb 	0x0100				/*  kDataBrowserSliderType  */
#define kDataBrowserSliderDownwardThumb  0x0200				/*  kDataBrowserSliderType  */
#define kDataBrowserDoNotTruncateText 	0x0300				/*  kDataBrowserTextType && kDataBrowserIconAndTextType  */
#define kDataBrowserTruncateTextAtEnd 	0x0200				/*  kDataBrowserTextType && kDataBrowserIconAndTextType  */
#define kDataBrowserTruncateTextMiddle 	0x00				/*  kDataBrowserTextType && kDataBrowserIconAndTextType  */
#define kDataBrowserTruncateTextAtStart  0x0100				/*  kDataBrowserTextType && kDataBrowserIconAndTextType  */
#define kDataBrowserPopupMenuButtonless  0x0100				/*  kDataBrowserPopupMenuType */
#define kDataBrowserPropertyModificationFlags  0xFF00		/*  support for an old name */
#define kDataBrowserRelativeDateTime 	0x0100				/*  support for an old name */

#define kDataBrowserViewSpecificFlagsOffset  16
#define kDataBrowserViewSpecificFlagsMask  0x00FF0000
#define kDataBrowserViewSpecificPropertyFlags  0x00FF0000	/*  support for an old name */

#define kDataBrowserClientPropertyFlagsOffset  24
#define kDataBrowserClientPropertyFlagsMask  0xFF000000

															/*  kDataBrowserTableView DataBrowserPropertyFlags  */
#define kDataBrowserTableViewSelectionColumn  0x00010000
#define kDataBrowserListViewSelectionColumn  0x00010000
#define kDataBrowserListViewMovableColumn  0x00020000
#define kDataBrowserListViewSortableColumn  0x00040000
#define kDataBrowserListViewTypeSelectColumn  0x00080000
#define kDataBrowserListViewNoGapForIconInHeaderButton  0x00100000
#define kDataBrowserListViewDefaultColumnFlags  0x00060000

#define kControlEditUnicodeTextProc 	912
#define kControlEditUnicodeTextPasswordProc  914

#define kControlKindEditUnicodeText 	'eutx'
#define kControlEditTextSingleLineTag 	'sglc'				/*  data is a Boolean; indicates whether the control should always be single-line */
#define kControlEditTextInsertTextBufferTag  'intx'			/*  data is an array of char; get or set the control's text as WorldScript-encoded text */
#define kControlEditTextInsertCFStringRefTag  'incf'		/*  data is a CFStringRef; get or set the control's text as a CFStringRef. Caller should release CFString if getting. */
#define kControlEditUnicodeTextPostUpdateProcTag  'upup'	/*  data is a UnicodePostUpdateUPP; get or set the post-update proc */


/*--------------------------ldes ¥ List Box Description Template------------------------*/
/*  Used in conjunction with the list box control.                                    */

type 'ldes'
{
    switch
 {
      case versionZero:
          key integer = 0;    /* version */

         integer;                                                /* Rows                 */
         integer;                                                /* Columns              */
         integer;                                                /* Cell Height          */
         integer;                                                /* Cell Width           */
         byte            noVertScroll, hasVertScroll;            /* Vert Scroll          */
         fill byte;                                              /* Filler Byte          */
         byte            noHorizScroll, hasHorizScroll;          /* Horiz Scroll         */
         fill byte;                                              /* Filler Byte          */
         integer;                                                /* LDEF Res ID          */
         byte            noGrowSpace, hasGrowSpace;              /* HasGrow?             */
         fill byte;
 };
};


/*-------------------------------tab# ¥ Tab Control Template-----------------------------*/
type 'tab#'
{
 switch
 {
      case versionZero:
          key integer = 0;    /* version */

         integer = $$Countof(TabInfo);
          array TabInfo
          {
              integer;                                            /* Icon Suite ID        */
             pstring;                                            /* Tab Name             */
             fill long;                                          /* Reserved             */
             fill word;                                          /* Reserved             */
         };
 };
};


#endif /* __CONTROLDEFINITIONS_R__ */

