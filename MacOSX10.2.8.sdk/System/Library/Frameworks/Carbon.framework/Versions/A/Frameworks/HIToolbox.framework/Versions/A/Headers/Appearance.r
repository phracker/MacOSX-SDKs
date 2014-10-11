/*
     File:       Appearance.r
 
     Contains:   Appearance Manager Interfaces.
 
     Version:    HIToolbox-124.14~2
 
     Copyright:  © 1994-2002 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

#ifndef __APPEARANCE_R__
#define __APPEARANCE_R__

#ifndef __CORESERVICES_R__
#include <CoreServices/CoreServices.r>
#endif

#define kAppearanceEventClass 			'appr'				/*  Event Class  */
#define kAEAppearanceChanged 			'thme'				/*  Appearance changed (e.g. platinum to hi-tech)  */
#define kAESystemFontChanged 			'sysf'				/*  system font changed  */
#define kAESmallSystemFontChanged 		'ssfn'				/*  small system font changed  */
#define kAEViewsFontChanged 			'vfnt'				/*  views font changed  */

#define kThemeDataFileType 				'thme'				/*  file type for theme files  */
#define kThemePlatinumFileType 			'pltn'				/*  file type for platinum appearance  */
#define kThemeCustomThemesFileType 		'scen'				/*  file type for user themes  */
#define kThemeSoundTrackFileType 		'tsnd'

#define kThemeBrushDialogBackgroundActive  1				/*  use with kModalWindowClass  */
#define kThemeBrushDialogBackgroundInactive  2				/*  use with kModalWindowClass  */
#define kThemeBrushAlertBackgroundActive  3					/*  use with kAlertWindowClass and kMovableAlertWindowClass  */
#define kThemeBrushAlertBackgroundInactive  4				/*  use with kAlertWindowClass and kMovableAlertWindowClass  */
#define kThemeBrushModelessDialogBackgroundActive  5		/*  use with kDocumentWindowClass  */
#define kThemeBrushModelessDialogBackgroundInactive  6		/*  use with kDocumentWindowClass  */
#define kThemeBrushUtilityWindowBackgroundActive  7			/*  use with kFloatingWindowClass and kUtilityWindowClass  */
#define kThemeBrushUtilityWindowBackgroundInactive  8		/*  use with kFloatingWindowClass and kUtilityWindowClass  */
#define kThemeBrushListViewSortColumnBackground  9			/*  Finder list views  */
#define kThemeBrushListViewBackground 	10
#define kThemeBrushIconLabelBackground 	11
#define kThemeBrushListViewSeparator 	12
#define kThemeBrushChasingArrows 		13
#define kThemeBrushDragHilite 			14
#define kThemeBrushDocumentWindowBackground  15				/*  use with kDocumentWindowClass  */
#define kThemeBrushFinderWindowBackground  16

#define kThemeBrushScrollBarDelimiterActive  17
#define kThemeBrushScrollBarDelimiterInactive  18
#define kThemeBrushFocusHighlight 		19
#define kThemeBrushPopupArrowActive 	20
#define kThemeBrushPopupArrowPressed 	21
#define kThemeBrushPopupArrowInactive 	22
#define kThemeBrushAppleGuideCoachmark 	23
#define kThemeBrushIconLabelBackgroundSelected  24
#define kThemeBrushStaticAreaFill 		25
#define kThemeBrushActiveAreaFill 		26
#define kThemeBrushButtonFrameActive 	27
#define kThemeBrushButtonFrameInactive 	28
#define kThemeBrushButtonFaceActive 	29
#define kThemeBrushButtonFaceInactive 	30
#define kThemeBrushButtonFacePressed 	31
#define kThemeBrushButtonActiveDarkShadow  32
#define kThemeBrushButtonActiveDarkHighlight  33
#define kThemeBrushButtonActiveLightShadow  34
#define kThemeBrushButtonActiveLightHighlight  35
#define kThemeBrushButtonInactiveDarkShadow  36
#define kThemeBrushButtonInactiveDarkHighlight  37
#define kThemeBrushButtonInactiveLightShadow  38
#define kThemeBrushButtonInactiveLightHighlight  39
#define kThemeBrushButtonPressedDarkShadow  40
#define kThemeBrushButtonPressedDarkHighlight  41
#define kThemeBrushButtonPressedLightShadow  42
#define kThemeBrushButtonPressedLightHighlight  43
#define kThemeBrushBevelActiveLight 	44
#define kThemeBrushBevelActiveDark 		45
#define kThemeBrushBevelInactiveLight 	46
#define kThemeBrushBevelInactiveDark 	47

#define kThemeBrushNotificationWindowBackground  48
#define kThemeBrushMovableModalBackground  49				/*  use with kMovableModalWindowClass; available in Mac OS X, and CarbonLib 1.3 and later  */
#define kThemeBrushSheetBackgroundOpaque  50				/*  use with kSheetWindowClass and kSheetAlertWindowClass; available in Mac OS X, and CarbonLib 1.3 and later  */
#define kThemeBrushDrawerBackground 	51					/*  use with kDrawerWindowClass; available in Mac OS X, and CarbonLib 1.3 and later  */
#define kThemeBrushToolbarBackground 	52					/*  use with kToolbarWindowClass; available in Mac OS X, and CarbonLib 1.6 and later  */
#define kThemeBrushSheetBackgroundTransparent  53			/*  use with kSheetWindowClass and kSheetAlertWindowClass; available in Mac OS X 10.1 and CarbonLib 1.6, and later  */
#define kThemeBrushMenuBackground 		54					/*  available in Mac OS X 10.1 and CarbonLib 1.6, and later  */
#define kThemeBrushMenuBackgroundSelected  55				/*  available in Mac OS X 10.1 and CarbonLib 1.6, and later  */

#define kThemeBrushSheetBackground 		50
#define kThemeBrushBlack 				(-1)
#define kThemeBrushWhite 				(-2)
#define kThemeBrushPrimaryHighlightColor  (-3)				/*  available in Mac OS 10.1 and CarbonLib 1.6, and later */
#define kThemeBrushSecondaryHighlightColor  (-4)			/*  available in Mac OS 10.1 and CarbonLib 1.6, and later */

#define kThemeTextColorDialogActive 	1
#define kThemeTextColorDialogInactive 	2
#define kThemeTextColorAlertActive 		3
#define kThemeTextColorAlertInactive 	4
#define kThemeTextColorModelessDialogActive  5
#define kThemeTextColorModelessDialogInactive  6
#define kThemeTextColorWindowHeaderActive  7
#define kThemeTextColorWindowHeaderInactive  8
#define kThemeTextColorPlacardActive 	9
#define kThemeTextColorPlacardInactive 	10
#define kThemeTextColorPlacardPressed 	11
#define kThemeTextColorPushButtonActive  12
#define kThemeTextColorPushButtonInactive  13
#define kThemeTextColorPushButtonPressed  14
#define kThemeTextColorBevelButtonActive  15
#define kThemeTextColorBevelButtonInactive  16
#define kThemeTextColorBevelButtonPressed  17
#define kThemeTextColorPopupButtonActive  18
#define kThemeTextColorPopupButtonInactive  19
#define kThemeTextColorPopupButtonPressed  20
#define kThemeTextColorIconLabel 		21
#define kThemeTextColorListView 		22

#define kThemeTextColorDocumentWindowTitleActive  23
#define kThemeTextColorDocumentWindowTitleInactive  24
#define kThemeTextColorMovableModalWindowTitleActive  25
#define kThemeTextColorMovableModalWindowTitleInactive  26
#define kThemeTextColorUtilityWindowTitleActive  27
#define kThemeTextColorUtilityWindowTitleInactive  28
#define kThemeTextColorPopupWindowTitleActive  29
#define kThemeTextColorPopupWindowTitleInactive  30
#define kThemeTextColorRootMenuActive 	31
#define kThemeTextColorRootMenuSelected  32
#define kThemeTextColorRootMenuDisabled  33
#define kThemeTextColorMenuItemActive 	34
#define kThemeTextColorMenuItemSelected  35
#define kThemeTextColorMenuItemDisabled  36
#define kThemeTextColorPopupLabelActive  37
#define kThemeTextColorPopupLabelInactive  38

#define kThemeTextColorTabFrontActive 	39
#define kThemeTextColorTabNonFrontActive  40
#define kThemeTextColorTabNonFrontPressed  41
#define kThemeTextColorTabFrontInactive  42
#define kThemeTextColorTabNonFrontInactive  43
#define kThemeTextColorIconLabelSelected  44
#define kThemeTextColorBevelButtonStickyActive  45
#define kThemeTextColorBevelButtonStickyInactive  46

#define kThemeTextColorNotification 	47
#define kThemeTextColorSystemDetail 	48
#define kThemeTextColorBlack 			(-1)
#define kThemeTextColorWhite 			(-2)

#define kThemeStateInactive 			0
#define kThemeStateActive 				1
#define kThemeStatePressed 				2
#define kThemeStateRollover 			6
#define kThemeStateUnavailable 			7
#define kThemeStateUnavailableInactive 	8

#define kThemeStateDisabled 			0
#define kThemeStatePressedUp 			2					/*  draw with up pressed     (increment/decrement buttons)  */
#define kThemeStatePressedDown 			3					/*  draw with down pressed (increment/decrement buttons)  */

#define kThemeArrowCursor 				0
#define kThemeCopyArrowCursor 			1
#define kThemeAliasArrowCursor 			2
#define kThemeContextualMenuArrowCursor  3
#define kThemeIBeamCursor 				4
#define kThemeCrossCursor 				5
#define kThemePlusCursor 				6
#define kThemeWatchCursor 				7					/*  Can Animate  */
#define kThemeClosedHandCursor 			8
#define kThemeOpenHandCursor 			9
#define kThemePointingHandCursor 		10
#define kThemeCountingUpHandCursor 		11					/*  Can Animate  */
#define kThemeCountingDownHandCursor 	12					/*  Can Animate  */
#define kThemeCountingUpAndDownHandCursor  13				/*  Can Animate  */
#define kThemeSpinningCursor 			14					/*  Can Animate  */
#define kThemeResizeLeftCursor 			15
#define kThemeResizeRightCursor 		16
#define kThemeResizeLeftRightCursor 	17
#define kThemeNotAllowedCursor 			18					/*  Jaguar or Later  */

#define kThemeMenuBarNormal 			0
#define kThemeMenuBarSelected 			1

#define kThemeMenuSquareMenuBar 		0x01
#define kThemeMenuActive 				0
#define kThemeMenuSelected 				1
#define kThemeMenuDisabled 				3

#define kThemeMenuTypePullDown 			0
#define kThemeMenuTypePopUp 			1
#define kThemeMenuTypeHierarchical 		2
#define kThemeMenuTypeInactive 			0x0100

#define kThemeMenuItemPlain 			0
#define kThemeMenuItemHierarchical 		1					/*  item has hierarchical arrow */
#define kThemeMenuItemScrollUpArrow 	2					/*  for scrollable menus, indicates item is scroller */
#define kThemeMenuItemScrollDownArrow 	3
#define kThemeMenuItemAtTop 			0x0100				/*  indicates item is being drawn at top of menu */
#define kThemeMenuItemAtBottom 			0x0200				/*  indicates item is being drawn at bottom of menu */
#define kThemeMenuItemHierBackground 	0x0400				/*  item is within a hierarchical menu */
#define kThemeMenuItemPopUpBackground 	0x0800				/*  item is within a popped up menu */
#define kThemeMenuItemHasIcon 			0x8000				/*  add into non-arrow type when icon present */
#define kThemeMenuItemNoBackground 		0x4000				/*  don't draw the menu background while drawing this item (Mac OS X only) */

#define kThemeBackgroundTabPane 		1
#define kThemeBackgroundPlacard 		2
#define kThemeBackgroundWindowHeader 	3
#define kThemeBackgroundListViewWindowHeader  4
#define kThemeBackgroundSecondaryGroupBox  5

#define kThemeNameTag 					'name'				/*  Str255 */
#define kThemeVariantNameTag 			'varn'				/*  Str255 */
#define kThemeVariantBaseTintTag 		'tint'				/*  RGBColor (10.1 and later) */
#define kThemeHighlightColorTag 		'hcol'				/*  RGBColor */
#define kThemeScrollBarArrowStyleTag 	'sbar'				/*  ThemeScrollBarArrowStyle */
#define kThemeScrollBarThumbStyleTag 	'sbth'				/*  ThemeScrollBarThumbStyle */
#define kThemeSoundsEnabledTag 			'snds'				/*  Boolean */
#define kThemeDblClickCollapseTag 		'coll'				/*  Boolean */

#define kThemeAppearanceFileNameTag 	'thme'				/*  Str255 */
#define kThemeSystemFontTag 			'lgsf'				/*  Str255 */
#define kThemeSmallSystemFontTag 		'smsf'				/*  Str255 */
#define kThemeViewsFontTag 				'vfnt'				/*  Str255 */
#define kThemeViewsFontSizeTag 			'vfsz'				/*  SInt16 */
#define kThemeDesktopPatternNameTag 	'patn'				/*  Str255 */
#define kThemeDesktopPatternTag 		'patt'				/*  <variable-length data> (flattened pattern) */
#define kThemeDesktopPictureNameTag 	'dpnm'				/*  Str255 */
#define kThemeDesktopPictureAliasTag 	'dpal'				/*  <alias handle> */
#define kThemeDesktopPictureAlignmentTag  'dpan'			/*  UInt32 (see the Picture Alignments below) */
#define kThemeHighlightColorNameTag 	'hcnm'				/*  Str255 */
#define kThemeExamplePictureIDTag 		'epic'				/*  SInt16 */
#define kThemeSoundTrackNameTag 		'sndt'				/*  Str255 */
#define kThemeSoundMaskTag 				'smsk'				/*  UInt32 */
#define kThemeUserDefinedTag 			'user'				/*  Boolean (this should _always_ be true if present - used by Control Panel). */
#define kThemeSmoothFontEnabledTag 		'smoo'				/*  Boolean */
#define kThemeSmoothFontMinSizeTag 		'smos'				/*  UInt16 (must be >= 12 and <= 24) */

#define kTiledOnScreen 					1					/*  draws picture repeatedly */
#define kCenterOnScreen 				2					/*  "actual size", shows pattern on sides or clips picture if necessary */
#define kFitToScreen 					3					/*  shrinks if necessary */
#define kFillScreen 					4					/*  messes up aspect ratio if necessary */
#define kUseBestGuess 					5					/*  heuristically determines the best way to display the picture based on picture and monitor sizes */

#define kThemeCheckBoxClassicX 			0					/*  check box with an 'X' */
#define kThemeCheckBoxCheckMark 		1					/*  check box with a real check mark */

#define kThemeScrollBarArrowsSingle 	0					/*  single arrow on each end */
#define kThemeScrollBarArrowsLowerRight  1					/*  double arrows only on right or bottom */

#define kThemeScrollBarThumbNormal 		0					/*  normal, classic thumb size */
#define kThemeScrollBarThumbProportional  1					/*  proportional thumbs */

#define kThemeSystemFont 				0
#define kThemeSmallSystemFont 			1
#define kThemeSmallEmphasizedSystemFont  2
#define kThemeViewsFont 				3					/*  The following ID's are only available with MacOS X or CarbonLib 1.3 and later */
#define kThemeEmphasizedSystemFont 		4
#define kThemeApplicationFont 			5
#define kThemeLabelFont 				6
#define kThemeMenuTitleFont 			100
#define kThemeMenuItemFont 				101
#define kThemeMenuItemMarkFont 			102
#define kThemeMenuItemCmdKeyFont 		103
#define kThemeWindowTitleFont 			104
#define kThemePushButtonFont 			105
#define kThemeUtilityWindowTitleFont 	106
#define kThemeAlertHeaderFont 			107
#define kThemeSystemFontDetail 			7
#define kThemeSystemFontDetailEmphasized  8
#define kThemeCurrentPortFont 			200					/*  Available in JAGUAR or later */
#define kThemeToolbarFont 				108

#define kPublicThemeFontCount 			17
#define kThemeTabNonFront 				0
#define kThemeTabNonFrontPressed 		1
#define kThemeTabNonFrontInactive 		2
#define kThemeTabFront 					3
#define kThemeTabFrontInactive 			4
#define kThemeTabNonFrontUnavailable 	5
#define kThemeTabFrontUnavailable 		6

#define kThemeTabNorth 					0
#define kThemeTabSouth 					1
#define kThemeTabEast 					2
#define kThemeTabWest 					3

#define kThemeSmallTabHeight 			16					/*  amount small tabs protrude from frame. */
#define kThemeLargeTabHeight 			21					/*  amount large tabs protrude from frame. */
#define kThemeTabPaneOverlap 			3					/*  amount tabs overlap frame. */
#define kThemeSmallTabHeightMax 		19					/*  small tab height + overlap */
#define kThemeLargeTabHeightMax 		24					/*  large tab height + overlap */

#define kThemeMediumScrollBar 			0
#define kThemeSmallScrollBar 			1
#define kThemeMediumSlider 				2
#define kThemeMediumProgressBar 		3
#define kThemeMediumIndeterminateBar 	4
#define kThemeRelevanceBar 				5
#define kThemeSmallSlider 				6
#define kThemeLargeProgressBar 			7
#define kThemeLargeIndeterminateBar 	8

															/*  track states  */
#define kThemeTrackActive 				0
#define kThemeTrackDisabled 			1
#define kThemeTrackNothingToScroll 		2
#define kThemeTrackInactive 			3

															/*  press states (ignored unless track is active)  */
#define kThemeLeftOutsideArrowPressed 	0x01
#define kThemeLeftInsideArrowPressed 	0x02
#define kThemeLeftTrackPressed 			0x04
#define kThemeThumbPressed 				0x08
#define kThemeRightTrackPressed 		0x10
#define kThemeRightInsideArrowPressed 	0x20
#define kThemeRightOutsideArrowPressed 	0x40
#define kThemeTopOutsideArrowPressed 	0x01
#define kThemeTopInsideArrowPressed 	0x02
#define kThemeTopTrackPressed 			0x04
#define kThemeBottomTrackPressed 		0x10
#define kThemeBottomInsideArrowPressed 	0x20
#define kThemeBottomOutsideArrowPressed  0x40

															/*  thumb direction  */
#define kThemeThumbPlain 				0
#define kThemeThumbUpward 				1
#define kThemeThumbDownward 			2

#define kThemeTrackHorizontal 			0x01
#define kThemeTrackRightToLeft 			0x02
#define kThemeTrackShowThumb 			0x04
#define kThemeTrackThumbRgnIsNotGhost 	0x08
#define kThemeTrackNoScrollBarArrows 	0x10
#define kThemeTrackHasFocus 			0x20

#define kThemeWindowHasGrow 			0x01				/*  can the size of the window be changed by the user?  */
#define kThemeWindowHasHorizontalZoom 	0x08				/*  window can zoom only horizontally  */
#define kThemeWindowHasVerticalZoom 	0x10				/*  window can zoom only vertically  */
#define kThemeWindowHasFullZoom 		0x18				/*  window zooms in all directions  */
#define kThemeWindowHasCloseBox 		0x20				/*  window has a close box  */
#define kThemeWindowHasCollapseBox 		0x40				/*  window has a collapse box  */
#define kThemeWindowHasTitleText 		0x80				/*  window has a title/title icon  */
#define kThemeWindowIsCollapsed 		0x0100				/*  window is in the collapsed state  */
#define kThemeWindowHasDirty 			0x0200

#define kThemeDocumentWindow 			0
#define kThemeDialogWindow 				1
#define kThemeMovableDialogWindow 		2
#define kThemeAlertWindow 				3
#define kThemeMovableAlertWindow 		4
#define kThemePlainDialogWindow 		5
#define kThemeShadowDialogWindow 		6
#define kThemePopupWindow 				7
#define kThemeUtilityWindow 			8
#define kThemeUtilitySideWindow 		9
#define kThemeSheetWindow 				10
#define kThemeDrawerWindow 				11

#define kThemeWidgetCloseBox 			0
#define kThemeWidgetZoomBox 			1
#define kThemeWidgetCollapseBox 		2
#define kThemeWidgetDirtyCloseBox 		6

															/*  Old/Obsolete name to be removed */
#define kThemeWidgetABox 				3
#define kThemeWidgetBBox 				4
#define kThemeWidgetBOffBox 			5

#define kThemeArrowLeft 				0
#define kThemeArrowDown 				1
#define kThemeArrowRight 				2
#define kThemeArrowUp 					3

#define kThemeArrow3pt 					0
#define kThemeArrow5pt 					1
#define kThemeArrow7pt 					2
#define kThemeArrow9pt 					3

#define kThemeGrowLeft 					0x01				/*  can grow to the left  */
#define kThemeGrowRight 				0x02				/*  can grow to the right  */
#define kThemeGrowUp 					0x04				/*  can grow up  */
#define kThemeGrowDown 					0x08				/*  can grow down  */

#define kThemePushButton 				0
#define kThemeCheckBox 					1
#define kThemeRadioButton 				2
#define kThemeBevelButton 				3					/*  bevel button (obsolete)  */
#define kThemeArrowButton 				4					/*  popup button without text (no label). See ThemeButtonAdornment for glyphs.  */
#define kThemePopupButton 				5					/*  popup button  */
#define kThemeDisclosureButton 			6
#define kThemeIncDecButton 				7					/*  increment/decrement buttons  (no label)  */
#define kThemeSmallBevelButton 			8					/*  small-shadow bevel button  */
#define kThemeMediumBevelButton 		3					/*  med-shadow bevel button  */
#define kThemeLargeBevelButton 			9					/*  large-shadow bevel button  */
#define kThemeListHeaderButton 			10					/*  sort button for top of list  */
#define kThemeRoundButton 				11					/*  round button  */
#define kThemeLargeRoundButton 			12					/*  large round button  */
#define kThemeSmallCheckBox 			13					/*  small checkbox  */
#define kThemeSmallRadioButton 			14					/*  small radio button  */
#define kThemeRoundedBevelButton 		15					/*  rounded bevel button  */
#define kThemeNormalCheckBox 			1
#define kThemeNormalRadioButton 		2

#define kThemeButtonOff 				0
#define kThemeButtonOn 					1
#define kThemeButtonMixed 				2
#define kThemeDisclosureRight 			0
#define kThemeDisclosureDown 			1
#define kThemeDisclosureLeft 			2

#define kThemeAdornmentNone 			0
#define kThemeAdornmentDefault 			0x01				/*  if set, draw default ornamentation ( for push button and generic well )  */
#define kThemeAdornmentFocus 			0x04				/*  if set, draw focus  */
#define kThemeAdornmentRightToLeft 		0x10				/*  if set, draw right to left label  */
#define kThemeAdornmentDrawIndicatorOnly  0x20				/*  if set, don't draw or erase label ( radio, check, disclosure )  */
#define kThemeAdornmentHeaderButtonLeftNeighborSelected  0x40 /*  if set, draw the left border of the button as selected ( list header button only )  */
#define kThemeAdornmentHeaderButtonRightNeighborSelected  0x80 /*  if set, draw the right border of the button ( list header button only )  */
#define kThemeAdornmentHeaderButtonSortUp  0x0100			/*  if set, draw the sort indicator pointing upward ( list header button only )  */
#define kThemeAdornmentHeaderMenuButton  0x0200				/*  if set, draw as a header menu button ( list header button only )  */
#define kThemeAdornmentHeaderButtonNoShadow  0x0400			/*  if set, draw the non-shadow area of the button ( list header button only )  */
#define kThemeAdornmentHeaderButtonShadowOnly  0x0800		/*  if set, draw the only the shadow area of the button ( list header button only )  */
#define kThemeAdornmentNoShadow 		0x0400				/*  old name  */
#define kThemeAdornmentShadowOnly 		0x0800				/*  old name  */
#define kThemeAdornmentArrowLeftArrow 	0x40				/*  If set, draw a left arrow on the arrow button  */
#define kThemeAdornmentArrowDownArrow 	0x80				/*  If set, draw a down arrow on the arrow button  */
#define kThemeAdornmentArrowDoubleArrow  0x0100				/*  If set, draw a double arrow on the arrow button  */
#define kThemeAdornmentArrowUpArrow 	0x0200				/*  If set, draw a up arrow on the arrow button  */

#define kThemeNoSounds 					0
#define kThemeWindowSoundsMask 			0x01
#define kThemeMenuSoundsMask 			0x02
#define kThemeControlSoundsMask 		0x04
#define kThemeFinderSoundsMask 			0x08

#define kThemeDragSoundNone 			0
#define kThemeDragSoundMoveWindow 		'wmov'
#define kThemeDragSoundGrowWindow 		'wgro'
#define kThemeDragSoundMoveUtilWindow 	'umov'
#define kThemeDragSoundGrowUtilWindow 	'ugro'
#define kThemeDragSoundMoveDialog 		'dmov'
#define kThemeDragSoundMoveAlert 		'amov'
#define kThemeDragSoundMoveIcon 		'imov'
#define kThemeDragSoundSliderThumb 		'slth'
#define kThemeDragSoundSliderGhost 		'slgh'
#define kThemeDragSoundScrollBarThumb 	'sbth'
#define kThemeDragSoundScrollBarGhost 	'sbgh'
#define kThemeDragSoundScrollBarArrowDecreasing  'sbad'
#define kThemeDragSoundScrollBarArrowIncreasing  'sbai'
#define kThemeDragSoundDragging 		'drag'

#define kThemeSoundNone 				0
#define kThemeSoundMenuOpen 			'mnuo'				/*  menu sounds  */
#define kThemeSoundMenuClose 			'mnuc'
#define kThemeSoundMenuItemHilite 		'mnui'
#define kThemeSoundMenuItemRelease 		'mnus'
#define kThemeSoundWindowClosePress 	'wclp'				/*  window sounds  */
#define kThemeSoundWindowCloseEnter 	'wcle'
#define kThemeSoundWindowCloseExit 		'wclx'
#define kThemeSoundWindowCloseRelease 	'wclr'
#define kThemeSoundWindowZoomPress 		'wzmp'
#define kThemeSoundWindowZoomEnter 		'wzme'
#define kThemeSoundWindowZoomExit 		'wzmx'
#define kThemeSoundWindowZoomRelease 	'wzmr'
#define kThemeSoundWindowCollapsePress 	'wcop'
#define kThemeSoundWindowCollapseEnter 	'wcoe'
#define kThemeSoundWindowCollapseExit 	'wcox'
#define kThemeSoundWindowCollapseRelease  'wcor'
#define kThemeSoundWindowDragBoundary 	'wdbd'
#define kThemeSoundUtilWinClosePress 	'uclp'				/*  utility window sounds  */
#define kThemeSoundUtilWinCloseEnter 	'ucle'
#define kThemeSoundUtilWinCloseExit 	'uclx'
#define kThemeSoundUtilWinCloseRelease 	'uclr'
#define kThemeSoundUtilWinZoomPress 	'uzmp'
#define kThemeSoundUtilWinZoomEnter 	'uzme'
#define kThemeSoundUtilWinZoomExit 		'uzmx'
#define kThemeSoundUtilWinZoomRelease 	'uzmr'
#define kThemeSoundUtilWinCollapsePress  'ucop'
#define kThemeSoundUtilWinCollapseEnter  'ucoe'
#define kThemeSoundUtilWinCollapseExit 	'ucox'
#define kThemeSoundUtilWinCollapseRelease  'ucor'
#define kThemeSoundUtilWinDragBoundary 	'udbd'
#define kThemeSoundWindowOpen 			'wopn'				/*  window close and zoom action  */
#define kThemeSoundWindowClose 			'wcls'
#define kThemeSoundWindowZoomIn 		'wzmi'
#define kThemeSoundWindowZoomOut 		'wzmo'
#define kThemeSoundWindowCollapseUp 	'wcol'
#define kThemeSoundWindowCollapseDown 	'wexp'
#define kThemeSoundWindowActivate 		'wact'
#define kThemeSoundUtilWindowOpen 		'uopn'
#define kThemeSoundUtilWindowClose 		'ucls'
#define kThemeSoundUtilWindowZoomIn 	'uzmi'
#define kThemeSoundUtilWindowZoomOut 	'uzmo'
#define kThemeSoundUtilWindowCollapseUp  'ucol'
#define kThemeSoundUtilWindowCollapseDown  'uexp'
#define kThemeSoundUtilWindowActivate 	'uact'
#define kThemeSoundDialogOpen 			'dopn'
#define kThemeSoundDialogClose 			'dlgc'
#define kThemeSoundAlertOpen 			'aopn'
#define kThemeSoundAlertClose 			'altc'
#define kThemeSoundPopupWindowOpen 		'pwop'
#define kThemeSoundPopupWindowClose 	'pwcl'
#define kThemeSoundButtonPress 			'btnp'				/*  button  */
#define kThemeSoundButtonEnter 			'btne'
#define kThemeSoundButtonExit 			'btnx'
#define kThemeSoundButtonRelease 		'btnr'
#define kThemeSoundDefaultButtonPress 	'dbtp'				/*  default button  */
#define kThemeSoundDefaultButtonEnter 	'dbte'
#define kThemeSoundDefaultButtonExit 	'dbtx'
#define kThemeSoundDefaultButtonRelease  'dbtr'
#define kThemeSoundCancelButtonPress 	'cbtp'				/*  cancel button  */
#define kThemeSoundCancelButtonEnter 	'cbte'
#define kThemeSoundCancelButtonExit 	'cbtx'
#define kThemeSoundCancelButtonRelease 	'cbtr'
#define kThemeSoundCheckboxPress 		'chkp'				/*  checkboxes  */
#define kThemeSoundCheckboxEnter 		'chke'
#define kThemeSoundCheckboxExit 		'chkx'
#define kThemeSoundCheckboxRelease 		'chkr'
#define kThemeSoundRadioPress 			'radp'				/*  radio buttons  */
#define kThemeSoundRadioEnter 			'rade'
#define kThemeSoundRadioExit 			'radx'
#define kThemeSoundRadioRelease 		'radr'
#define kThemeSoundScrollArrowPress 	'sbap'				/*  scroll bars  */
#define kThemeSoundScrollArrowEnter 	'sbae'
#define kThemeSoundScrollArrowExit 		'sbax'
#define kThemeSoundScrollArrowRelease 	'sbar'
#define kThemeSoundScrollEndOfTrack 	'sbte'
#define kThemeSoundScrollTrackPress 	'sbtp'
#define kThemeSoundSliderEndOfTrack 	'slte'				/*  sliders  */
#define kThemeSoundSliderTrackPress 	'sltp'
#define kThemeSoundBalloonOpen 			'blno'				/*  help balloons  */
#define kThemeSoundBalloonClose 		'blnc'
#define kThemeSoundBevelPress 			'bevp'				/*  Bevel buttons  */
#define kThemeSoundBevelEnter 			'beve'
#define kThemeSoundBevelExit 			'bevx'
#define kThemeSoundBevelRelease 		'bevr'
#define kThemeSoundLittleArrowUpPress 	'laup'				/*  Little Arrows  */
#define kThemeSoundLittleArrowDnPress 	'ladp'
#define kThemeSoundLittleArrowEnter 	'lare'
#define kThemeSoundLittleArrowExit 		'larx'
#define kThemeSoundLittleArrowUpRelease  'laur'
#define kThemeSoundLittleArrowDnRelease  'ladr'
#define kThemeSoundPopupPress 			'popp'				/*  Popup Buttons  */
#define kThemeSoundPopupEnter 			'pope'
#define kThemeSoundPopupExit 			'popx'
#define kThemeSoundPopupRelease 		'popr'
#define kThemeSoundDisclosurePress 		'dscp'				/*  Disclosure Buttons  */
#define kThemeSoundDisclosureEnter 		'dsce'
#define kThemeSoundDisclosureExit 		'dscx'
#define kThemeSoundDisclosureRelease 	'dscr'
#define kThemeSoundTabPressed 			'tabp'				/*  Tabs  */
#define kThemeSoundTabEnter 			'tabe'
#define kThemeSoundTabExit 				'tabx'
#define kThemeSoundTabRelease 			'tabr'
#define kThemeSoundDragTargetHilite 	'dthi'				/*  drag manager  */
#define kThemeSoundDragTargetUnhilite 	'dtuh'
#define kThemeSoundDragTargetDrop 		'dtdr'
#define kThemeSoundEmptyTrash 			'ftrs'				/*  finder  */
#define kThemeSoundSelectItem 			'fsel'
#define kThemeSoundNewItem 				'fnew'
#define kThemeSoundReceiveDrop 			'fdrp'
#define kThemeSoundCopyDone 			'fcpd'
#define kThemeSoundResolveAlias 		'fral'
#define kThemeSoundLaunchApp 			'flap'
#define kThemeSoundDiskInsert 			'dski'
#define kThemeSoundDiskEject 			'dske'
#define kThemeSoundFinderDragOnIcon 	'fdon'
#define kThemeSoundFinderDragOffIcon 	'fdof'

#define kThemePopupTabNormalPosition 	0
#define kThemePopupTabCenterOnWindow 	1
#define kThemePopupTabCenterOnOffset 	2

#define kThemeMetricScrollBarWidth 		0
#define kThemeMetricSmallScrollBarWidth  1
#define kThemeMetricCheckBoxHeight 		2
#define kThemeMetricRadioButtonHeight 	3
#define kThemeMetricEditTextWhitespace 	4
#define kThemeMetricEditTextFrameOutset  5
#define kThemeMetricListBoxFrameOutset 	6
#define kThemeMetricFocusRectOutset 	7
#define kThemeMetricImageWellThickness 	8
#define kThemeMetricScrollBarOverlap 	9
#define kThemeMetricLargeTabHeight 		10
#define kThemeMetricLargeTabCapsWidth 	11
#define kThemeMetricTabFrameOverlap 	12
#define kThemeMetricTabIndentOrStyle 	13
#define kThemeMetricTabOverlap 			14
#define kThemeMetricSmallTabHeight 		15
#define kThemeMetricSmallTabCapsWidth 	16
#define kThemeMetricPushButtonHeight 	19
#define kThemeMetricListHeaderHeight 	20
#define kThemeMetricDisclosureTriangleHeight  25
#define kThemeMetricDisclosureTriangleWidth  26
#define kThemeMetricLittleArrowsHeight 	27
#define kThemeMetricLittleArrowsWidth 	28
#define kThemeMetricPopupButtonHeight 	30
#define kThemeMetricSmallPopupButtonHeight  31
#define kThemeMetricLargeProgressBarThickness  32
#define kThemeMetricPullDownHeight 		33
#define kThemeMetricSmallPullDownHeight  34
#define kThemeMetricResizeControlHeight  38
#define kThemeMetricSmallResizeControlHeight  39
#define kThemeMetricHSliderHeight 		41
#define kThemeMetricHSliderTickHeight 	42
#define kThemeMetricVSliderWidth 		45
#define kThemeMetricVSliderTickWidth 	46
#define kThemeMetricTitleBarControlsHeight  49
#define kThemeMetricCheckBoxWidth 		50
#define kThemeMetricRadioButtonWidth 	52
#define kThemeMetricNormalProgressBarThickness  58
#define kThemeMetricProgressBarShadowOutset  59
#define kThemeMetricSmallProgressBarShadowOutset  60
#define kThemeMetricPrimaryGroupBoxContentInset  61
#define kThemeMetricSecondaryGroupBoxContentInset  62
#define kThemeMetricMenuMarkColumnWidth  63
#define kThemeMetricMenuExcludedMarkColumnWidth  64
#define kThemeMetricMenuMarkIndent 		65
#define kThemeMetricMenuTextLeadingEdgeMargin  66
#define kThemeMetricMenuTextTrailingEdgeMargin  67
#define kThemeMetricMenuIndentWidth 	68
#define kThemeMetricMenuIconTrailingEdgeMargin  69

#define kThemeMetricDisclosureButtonHeight  17
#define kThemeMetricRoundButtonSize 	18
#define kThemeMetricSmallCheckBoxHeight  21
#define kThemeMetricDisclosureButtonWidth  22
#define kThemeMetricSmallDisclosureButtonHeight  23
#define kThemeMetricSmallDisclosureButtonWidth  24
#define kThemeMetricPaneSplitterHeight 	29
#define kThemeMetricSmallPushButtonHeight  35
#define kThemeMetricSmallRadioButtonHeight  36
#define kThemeMetricRelevanceIndicatorHeight  37
#define kThemeMetricLargeRoundButtonSize  40
#define kThemeMetricSmallHSliderHeight 	43
#define kThemeMetricSmallHSliderTickHeight  44
#define kThemeMetricSmallVSliderWidth 	47
#define kThemeMetricSmallVSliderTickWidth  48
#define kThemeMetricSmallCheckBoxWidth 	51
#define kThemeMetricSmallRadioButtonWidth  53
#define kThemeMetricSmallHSliderMinThumbWidth  54
#define kThemeMetricSmallVSliderMinThumbHeight  55
#define kThemeMetricSmallHSliderTickOffset  56
#define kThemeMetricSmallVSliderTickOffset  57

#define appearanceBadBrushIndexErr 		(-30560)			/*  pattern index invalid  */
#define appearanceProcessRegisteredErr 	(-30561)
#define appearanceProcessNotRegisteredErr  (-30562)
#define appearanceBadTextColorIndexErr 	(-30563)
#define appearanceThemeHasNoAccents 	(-30564)
#define appearanceBadCursorIndexErr 	(-30565)

#define kThemeActiveDialogBackgroundBrush  1
#define kThemeInactiveDialogBackgroundBrush  2
#define kThemeActiveAlertBackgroundBrush  3
#define kThemeInactiveAlertBackgroundBrush  4
#define kThemeActiveModelessDialogBackgroundBrush  5
#define kThemeInactiveModelessDialogBackgroundBrush  6
#define kThemeActiveUtilityWindowBackgroundBrush  7
#define kThemeInactiveUtilityWindowBackgroundBrush  8
#define kThemeListViewSortColumnBackgroundBrush  9
#define kThemeListViewBackgroundBrush 	10
#define kThemeIconLabelBackgroundBrush 	11
#define kThemeListViewSeparatorBrush 	12
#define kThemeChasingArrowsBrush 		13
#define kThemeDragHiliteBrush 			14
#define kThemeDocumentWindowBackgroundBrush  15
#define kThemeFinderWindowBackgroundBrush  16

#define kThemeActiveScrollBarDelimiterBrush  17
#define kThemeInactiveScrollBarDelimiterBrush  18
#define kThemeFocusHighlightBrush 		19
#define kThemeActivePopupArrowBrush 	20
#define kThemePressedPopupArrowBrush 	21
#define kThemeInactivePopupArrowBrush 	22
#define kThemeAppleGuideCoachmarkBrush 	23

#define kThemeActiveDialogTextColor 	1
#define kThemeInactiveDialogTextColor 	2
#define kThemeActiveAlertTextColor 		3
#define kThemeInactiveAlertTextColor 	4
#define kThemeActiveModelessDialogTextColor  5
#define kThemeInactiveModelessDialogTextColor  6
#define kThemeActiveWindowHeaderTextColor  7
#define kThemeInactiveWindowHeaderTextColor  8
#define kThemeActivePlacardTextColor 	9
#define kThemeInactivePlacardTextColor 	10
#define kThemePressedPlacardTextColor 	11
#define kThemeActivePushButtonTextColor  12
#define kThemeInactivePushButtonTextColor  13
#define kThemePressedPushButtonTextColor  14
#define kThemeActiveBevelButtonTextColor  15
#define kThemeInactiveBevelButtonTextColor  16
#define kThemePressedBevelButtonTextColor  17
#define kThemeActivePopupButtonTextColor  18
#define kThemeInactivePopupButtonTextColor  19
#define kThemePressedPopupButtonTextColor  20
#define kThemeIconLabelTextColor 		21
#define kThemeListViewTextColor 		22

#define kThemeActiveDocumentWindowTitleTextColor  23
#define kThemeInactiveDocumentWindowTitleTextColor  24
#define kThemeActiveMovableModalWindowTitleTextColor  25
#define kThemeInactiveMovableModalWindowTitleTextColor  26
#define kThemeActiveUtilityWindowTitleTextColor  27
#define kThemeInactiveUtilityWindowTitleTextColor  28
#define kThemeActivePopupWindowTitleColor  29
#define kThemeInactivePopupWindowTitleColor  30
#define kThemeActiveRootMenuTextColor 	31
#define kThemeSelectedRootMenuTextColor  32
#define kThemeDisabledRootMenuTextColor  33
#define kThemeActiveMenuItemTextColor 	34
#define kThemeSelectedMenuItemTextColor  35
#define kThemeDisabledMenuItemTextColor  36
#define kThemeActivePopupLabelTextColor  37
#define kThemeInactivePopupLabelTextColor  38

#define kAEThemeSwitch 					'thme'				/*  Event ID's: Theme Switched  */
#define kThemeNoAdornment 				0
#define kThemeDefaultAdornment 			0x01
#define kThemeFocusAdornment 			0x04
#define kThemeRightToLeftAdornment 		0x10
#define kThemeDrawIndicatorOnly 		0x20

#define kThemeBrushPassiveAreaFill 		25
#define kThemeMetricCheckBoxGlyphHeight  2
#define kThemeMetricRadioButtonGlyphHeight  3
#define kThemeMetricDisclosureButtonSize  17
#define kThemeMetricBestListHeaderHeight  20
#define kThemeMetricSmallProgressBarThickness  58			/*  obsolete  */
#define kThemeMetricProgressBarThickness  32				/*  obsolete  */

#define kThemeScrollBar 				0
#define kThemeSlider 					2
#define kThemeProgressBar 				3
#define kThemeIndeterminateBar 			4


#endif /* __APPEARANCE_R__ */

