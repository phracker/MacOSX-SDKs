
/*
 *  AXConstants.h
 *
 *  Created by John Louch on Tue Mar 26 2002.
 *  Copyright (c) 2002 Apple Computer, Inc. All rights reserved.
 *
 */

#ifndef __AXCONSTANTS__
#define __AXCONSTANTS__

#include <CoreFoundation/CoreFoundation.h>

// standard attributes
#define kAXRoleAttribute				CFSTR("AXRole")
#define kAXRoleDescriptionAttribute			CFSTR("AXRoleDescription")
#define kAXSubroleAttribute				CFSTR("AXSubrole")
#define kAXHelpAttribute				CFSTR("AXHelp")
#define kAXTitleAttribute				CFSTR("AXTitle")
#define kAXValueAttribute				CFSTR("AXValue")
#define kAXMinValueAttribute				CFSTR("AXMinValue")
#define kAXMaxValueAttribute				CFSTR("AXMaxValue")
#define kAXEnabledAttribute				CFSTR("AXEnabled")
#define kAXFocusedAttribute				CFSTR("AXFocused")
#define kAXParentAttribute				CFSTR("AXParent")
#define kAXChildrenAttribute				CFSTR("AXChildren")
#define kAXSelectedChildrenAttribute			CFSTR("AXSelectedChildren")
#define kAXVisibleChildrenAttribute			CFSTR("AXVisibleChildren")
#define kAXWindowAttribute				CFSTR("AXWindow")
#define kAXPositionAttribute				CFSTR("AXPosition")
#define kAXSizeAttribute				CFSTR("AXSize")
#define kAXOrientationAttribute				CFSTR("AXOrientation")

// text-specific attributes
#define kAXTextAttribute				CFSTR("AXText")
#define kAXSelectedTextAttribute			CFSTR("AXSelectedText")
#define kAXSelectedTextRangeAttribute			CFSTR("AXSelectedTextRange")
#define kAXVisibleTextAttribute				CFSTR("AXVisibleText")
#define kAXVisibleCharacterRangeAttribute		CFSTR("AXVisibleCharacterRange")
#define kAXNumberOfCharactersAttribute			CFSTR("AXNumberOfCharacters")

// window-specific attributes
#define kAXMainAttribute				CFSTR("AXMain")
#define kAXFocusedAttribute				CFSTR("AXFocused")
#define kAXMinimizedAttribute				CFSTR("AXMinimized")
#define kAXCloseButtonAttribute				CFSTR("AXCloseButton")
#define kAXZoomButtonAttribute				CFSTR("AXZoomButton")
#define kAXMinimizeButtonAttribute			CFSTR("AXMinimizeButton")
#define kAXToolbarButtonAttribute			CFSTR("AXToolbarButton")
#define kAXProxyAttribute				CFSTR("AXProxy")
#define kAXGrowAreaAttribute				CFSTR("AXGrowArea")

// new window-specific attributes
#define kAXModalAttribute				CFSTR("AXModal")
#define kAXDefaultButtonAttribute			CFSTR("AXDefaultButton")
#define kAXCancelButtonAttribute			CFSTR("AXCancelButton")

// menu-specific attributes
#define kAXMenuItemCmdCharAttribute			CFSTR("AXMenuItemCmdChar")
#define kAXMenuItemCmdVirtualKeyAttribute		CFSTR("AXMenuItemCmdVirtualKey")
#define kAXMenuItemCmdGlyphAttribute			CFSTR("AXMenuItemCmdGlyph")
#define kAXMenuItemCmdModifiersAttribute		CFSTR("AXMenuItemCmdModifiers")
#define kAXMenuItemMarkCharAttribute			CFSTR("AXMenuItemMarkChar")

// application-specific attributes
#define kAXMenuBarAttribute				CFSTR("AXMenuBar")
#define kAXWindowsAttribute				CFSTR("AXWindows")
#define kAXFrontmostAttribute				CFSTR("AXFrontmost")
#define kAXHiddenAttribute				CFSTR("AXHidden")
#define kAXMainWindowAttribute				CFSTR("AXMainWindow")
#define kAXFocusedWindowAttribute			CFSTR("AXFocusedWindow")
#define kAXFocusedUIElementAttribute			CFSTR("AXFocusedUIElement") 

// misc attributes
#define kAXHeaderAttribute				CFSTR("AXHeader")
#define kAXEditedAttribute				CFSTR("AXEdited")
#define kAXValueIncrementAttribute			CFSTR("AXValueIncrement")
#define kAXValueWrapsAttribute				CFSTR("AXValueWraps")
#define kAXTabsAttribute				CFSTR("AXTabs")
#define kAXTitleUIElementAttribute			CFSTR("AXTitleUIElement")
#define kAXHorizontalScrollBarAttribute			CFSTR("AXHorizontalScrollBar")
#define kAXVerticalScrollBarAttribute			CFSTR("AXVerticalScrollBar")
#define kAXOverflowButtonAttribute			CFSTR("AXOverflowButton")
#define kAXFilenameAttribute				CFSTR("AXFilename")
#define kAXExpandedAttribute				CFSTR("AXExpanded")
#define kAXSelectedAttribute				CFSTR("AXSelected")
#define kAXSplittersAttribute				CFSTR("AXSplitters")
#define kAXNextContentsAttribute			CFSTR("AXNextContents")
#define kAXDocumentAttribute				CFSTR("AXDocument")
#define kAXDecrementButtonAttribute			CFSTR("AXDecrementButton")
#define kAXIncrementButtonAttribute			CFSTR("AXIncrementButton")
#define kAXPreviousContentsAttribute			CFSTR("AXPreviousContents")
#define kAXContentsAttribute				CFSTR("AXContents")
#define kAXIncrementorAttribute				CFSTR("AXIncrementor")
#define kAXHourFieldAttribute				CFSTR("AXHourField")
#define kAXMinuteFieldAttribute				CFSTR("AXMinuteField")
#define kAXSecondFieldAttribute				CFSTR("AXSecondField")
#define kAXAMPMFieldAttribute				CFSTR("AXAMPMField")
#define kAXDayFieldAttribute				CFSTR("AXDayField")
#define kAXMonthFieldAttribute				CFSTR("AXMonthField")
#define kAXYearFieldAttribute				CFSTR("AXYearField")
#define kAXColumnTitlesAttribute			CFSTR("AXColumnTitles")
#define kAXURLAttribute					CFSTR("AXURL")

// table/outline view attributes
#define kAXRowsAttribute				CFSTR("AXRows")
#define kAXVisibleRowsAttribute				CFSTR("AXVisibleRows")
#define kAXSelectedRowsAttribute			CFSTR("AXSelectedRows")
#define kAXColumnsAttribute				CFSTR("AXColumns")
#define kAXVisibleColumnsAttribute			CFSTR("AXVisibleColumns")
#define kAXSelectedColumnsAttribute			CFSTR("AXSelectedColumns")
#define kAXSortDirectionAttribute			CFSTR("AXSortDirection")

// outline attributes
#define kAXDisclosingAttribute				CFSTR("AXDisclosing")
#define kAXDisclosedRowsAttribute			CFSTR("AXDisclosedRows")
#define kAXDisclosedByRowAttribute			CFSTR("AXDisclosedByRow")

// system-wide attributes
#define kAXFocusedApplicationAttribute			CFSTR("AXFocusedApplication")

//
// Parameterized Attributes
//

// Text Suite Parameterized Attributes
#define kAXLineForIndexParameterizedAttribute		CFSTR("AXLineForIndex")
#define kAXRangeForLineParameterizedAttribute          	CFSTR("AXRangeForLine")
#define kAXStringForRangeParameterizedAttribute        	CFSTR("AXStringForRange")
#define kAXRangeForPositionParameterizedAttribute	CFSTR("AXRangeForPosition")
#define kAXRangeForIndexParameterizedAttribute 		CFSTR("AXRangeForIndex")
#define kAXBoundsForRangeParameterizedAttribute		CFSTR("AXBoundsForRange")
#define kAXRTFForRangeParameterizedAttribute		CFSTR("AXRTFForRange")
#define kAXStyleRangeForIndexParameterizedAttribute	CFSTR("AXStyleRangeForIndex")

//
// standard values
//

// orientations (see kAXOrientationAttribute)
#define kAXHorizontalOrientationValue			CFSTR("AXHorizontalOrientation")
#define kAXVerticalOrientationValue			CFSTR("AXVerticalOrientation")

// standard actions
#define kAXPressAction					CFSTR("AXPress")
#define kAXIncrementAction				CFSTR("AXIncrement")
#define kAXDecrementAction				CFSTR("AXDecrement")
#define kAXConfirmAction				CFSTR("AXConfirm")
#define kAXPickAction					CFSTR("AXPick")
#define kAXCancelAction					CFSTR("AXCancel")

// new actions
#define kAXRaiseAction					CFSTR("AXRaise")

// standard roles
#define kAXApplicationRole				CFSTR("AXApplication")
#define kAXSystemWideRole				CFSTR("AXSystemWide")
#define kAXWindowRole 					CFSTR("AXWindow")
#define kAXSheetRole					CFSTR("AXSheet")
#define kAXDrawerRole					CFSTR("AXDrawer")
#define kAXGrowAreaRole					CFSTR("AXGrowArea")
#define kAXImageRole					CFSTR("AXImage")
#define kAXUnknownRole					CFSTR("AXUnknown")
#define kAXButtonRole					CFSTR("AXButton")
#define kAXRadioButtonRole				CFSTR("AXRadioButton")
#define kAXCheckBoxRole 				CFSTR("AXCheckBox")
#define kAXPopUpButtonRole 				CFSTR("AXPopUpButton")
#define kAXMenuButtonRole				CFSTR("AXMenuButton")
#define kAXTabGroupRole					CFSTR("AXTabGroup")
#define kAXTableRole					CFSTR("AXTable")
#define kAXColumnRole					CFSTR("AXColumn")
#define kAXRowRole					CFSTR("AXRow")
#define kAXOutlineRole					CFSTR("AXOutline")
#define kAXBrowserRole					CFSTR("AXBrowser")
#define kAXScrollAreaRole 				CFSTR("AXScrollArea")
#define kAXScrollBarRole				CFSTR("AXScrollBar")
#define kAXRadioGroupRole	 			CFSTR("AXRadioGroup")
#define kAXListRole					CFSTR("AXList")
#define kAXGroupRole			    		CFSTR("AXGroup")
#define kAXValueIndicatorRole				CFSTR("AXValueIndicator")
#define kAXComboBoxRole					CFSTR("AXComboBox")
#define kAXSliderRole 					CFSTR("AXSlider")
#define kAXIncrementorRole				CFSTR("AXIncrementor")
#define kAXBusyIndicatorRole				CFSTR("AXBusyIndicator")
#define kAXProgressIndicatorRole		  	CFSTR("AXProgressIndicator")
#define kAXToolbarRole					CFSTR("AXToolbar")

#define kAXTextFieldRole 				CFSTR("AXTextField")
#define	kAXTextAreaRole					CFSTR("AXTextArea")
#define kAXStaticTextRole 				CFSTR("AXStaticText")

#define kAXMenuBarRole					CFSTR("AXMenuBar")
#define kAXMenuBarItemRole				CFSTR("AXMenuBarItem")
#define kAXMenuRole					CFSTR("AXMenu")
#define kAXMenuItemRole				 	CFSTR("AXMenuItem")

#define kAXSplitGroupRole				CFSTR("AXSplitGroup")
#define kAXSplitterRole					CFSTR("AXSplitter")
#define kAXColorWellRole				CFSTR("AXColorWell")

#define kAXTimeFieldRole				CFSTR( "AXTimeField" )
#define kAXDateFieldRole				CFSTR( "AXDateField" )

// standard subroles
#define kAXCloseButtonSubrole				CFSTR("AXCloseButton")
#define kAXMinimizeButtonSubrole			CFSTR("AXMinimizeButton")
#define kAXZoomButtonSubrole				CFSTR("AXZoomButton")
#define kAXToolbarButtonSubrole				CFSTR("AXToolbarButton")
#define kAXSecureTextFieldSubrole			CFSTR("AXSecureTextField")
#define kAXTableRowSubrole				CFSTR("AXTableRow")
#define kAXOutlineRowSubrole				CFSTR("AXOutlineRow")
#define kAXUnknownSubrole				CFSTR("AXUnknown")

// new subroles
#define kAXStandardWindowSubrole			CFSTR("AXStandardWindow")
#define kAXDialogSubrole				CFSTR("AXDialog")
#define kAXSystemDialogSubrole				CFSTR("AXSystemDialog")
#define kAXFloatingWindowSubrole			CFSTR("AXFloatingWindow")
#define kAXSystemFloatingWindowSubrole			CFSTR("AXSystemFloatingWindow")
#define kAXIncrementArrowSubrole			CFSTR("AXIncrementArrow")
#define kAXDecrementArrowSubrole			CFSTR("AXDecrementArrow")
#define kAXIncrementPageSubrole				CFSTR("AXIncrementPage")
#define kAXDecrementPageSubrole				CFSTR("AXDecrementPage")

// focus notifications
#define kAXMainWindowChangedNotification		CFSTR("AXMainWindowChanged")
#define kAXFocusedWindowChangedNotification		CFSTR("AXFocusedWindowChanged")
#define kAXFocusedUIElementChangedNotification		CFSTR("AXFocusedUIElementChanged")

// application notifications
#define kAXApplicationActivatedNotification		CFSTR("AXApplicationActivated")
#define kAXApplicationDeactivatedNotification		CFSTR("AXApplicationDeactivated")
#define kAXApplicationHiddenNotification		CFSTR("AXApplicationHidden")
#define kAXApplicationShownNotification			CFSTR("AXApplicationShown")

// window notifications
#define kAXWindowCreatedNotification			CFSTR("AXWindowCreated")
#define kAXWindowMovedNotification			CFSTR("AXWindowMoved")
#define kAXWindowResizedNotification			CFSTR("AXWindowResized")
#define kAXWindowMiniaturizedNotification		CFSTR("AXWindowMiniaturized")
#define kAXWindowDeminiaturizedNotification		CFSTR("AXWindowDeminiaturized")

// new drawer & sheet notifications
#define kAXDrawerCreatedNotification			CFSTR("AXDrawerCreated")
#define kAXSheetCreatedNotification			CFSTR("AXSheetCreated")

// element notifications
#define kAXValueChangedNotification			CFSTR("AXValueChanged")
#define kAXUIElementDestroyedNotification		CFSTR("AXUIElementDestroyed")

// menu notifications
#define kAXMenuOpenedNotification			CFSTR("AXMenuOpened")
#define kAXMenuClosedNotification			CFSTR("AXMenuClosed")
#define kAXMenuItemSelectedNotification			CFSTR("AXMenuItemSelected")


// obsolete constants will be removed soon
#define kAXRelevanceIndicatorRole			CFSTR("AXRelevanceIndicator")
#define kAXIsEditableAttribute				CFSTR("AXIsEditable")


#endif // __AXCONSTANTS__
