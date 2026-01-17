
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
#define kAXRoleAttribute						CFSTR("AXRole")
#define kAXRoleDescriptionAttribute				CFSTR("AXRoleDescription")
#define kAXSubroleAttribute						CFSTR("AXSubrole")
#define kAXHelpAttribute						CFSTR("AXHelp")
#define kAXTitleAttribute						CFSTR("AXTitle")
#define kAXValueAttribute						CFSTR("AXValue")
#define kAXMinValueAttribute					CFSTR("AXMinValue")
#define kAXMaxValueAttribute					CFSTR("AXMaxValue")
#define kAXEnabledAttribute						CFSTR("AXEnabled")
#define kAXFocusedAttribute						CFSTR("AXFocused")
#define kAXParentAttribute						CFSTR("AXParent")
#define kAXChildrenAttribute					CFSTR("AXChildren")
#define kAXSelectedChildrenAttribute			CFSTR("AXSelectedChildren")
#define kAXVisibleChildrenAttribute				CFSTR("AXVisibleChildren")
#define kAXWindowAttribute						CFSTR("AXWindow")
#define kAXPositionAttribute					CFSTR("AXPosition")
#define kAXSizeAttribute						CFSTR("AXSize")
#define kAXOrientationAttribute					CFSTR("AXOrientation")

// text-specific attributes
#define kAXTextAttribute						CFSTR("AXText")
#define kAXSelectedTextAttribute				CFSTR("AXSelectedText")
#define kAXSelectedTextRangeAttribute			CFSTR("AXSelectedTextRange")

// window-specific attributes
#define kAXMainAttribute						CFSTR("AXMain")
#define kAXFocusedAttribute						CFSTR("AXFocused")
#define kAXMinimizedAttribute					CFSTR("AXMinimized")
#define kAXCloseButtonAttribute					CFSTR("AXCloseButton")
#define kAXZoomButtonAttribute					CFSTR("AXZoomButton")
#define kAXMinimizeButtonAttribute				CFSTR("AXMinimizeButton")
#define kAXToolbarButtonAttribute				CFSTR("AXToolbarButton")
#define kAXProxyAttribute						CFSTR("AXProxy")
#define kAXGrowAreaAttribute					CFSTR("AXGrowArea")

// menu-specific attributes
#define kAXMenuItemCmdCharAttribute				CFSTR("AXMenuItemCmdChar")
#define kAXMenuItemCmdVirtualKeyAttribute		CFSTR("AXMenuItemCmdVirtualKey")
#define kAXMenuItemCmdGlyphAttribute			CFSTR("AXMenuItemCmdGlyph")
#define kAXMenuItemCmdModifiersAttribute		CFSTR("AXMenuItemCmdModifiers")
#define kAXMenuItemMarkCharAttribute			CFSTR("AXMenuItemMarkChar")

// application-specific attributes
#define kAXMenuBarAttribute						CFSTR("AXMenuBar")
#define kAXWindowsAttribute						CFSTR("AXWindows")
#define kAXFrontmostAttribute					CFSTR("AXFrontmost")
#define kAXHiddenAttribute						CFSTR("AXHidden")
#define kAXMainWindowAttribute					CFSTR("AXMainWindow")
#define kAXFocusedWindowAttribute				CFSTR("AXFocusedWindow")
#define kAXFocusedUIElementAttribute			CFSTR("AXFocusedUIElement") 

// misc attributes
#define kAXHeaderAttribute						CFSTR("AXHeader")
#define kAXIsEditableAttribute					CFSTR("AXIsEditable")
#define kAXEditedAttribute						CFSTR("AXEdited")
#define kAXValueIncrementAttribute				CFSTR("AXValueIncrement")
#define kAXValueWrapsAttribute					CFSTR("AXValueWraps")
#define kAXTabsAttribute						CFSTR("AXTabs")
#define kAXTitleUIElementAttribute				CFSTR("AXTitleUIElement")
#define kAXHorizontalScrollBarAttribute			CFSTR("AXHorizontalScrollBar")
#define kAXVerticalScrollBarAttribute			CFSTR("AXVerticalScrollBar")
#define kAXOverflowButtonAttribute				CFSTR("AXOverflowButton")
#define kAXFilenameAttribute					CFSTR("AXFilename")
#define kAXExpandedAttribute					CFSTR("AXExpanded")
#define kAXSelectedAttribute					CFSTR("AXSelected")
#define kAXSplittersAttribute					CFSTR("AXSplitters")
#define kAXNextContentsAttribute				CFSTR("AXNextContents")
#define kAXDocumentAttribute					CFSTR("AXDocument")
#define kAXDecrementButtonAttribute				CFSTR("AXDecrementButton")
#define kAXColumnTitlesAttribute				CFSTR("AXColumnTitles")
#define kAXIncrementButtonAttribute				CFSTR("AXIncrementButton")
#define kAXPreviousContentsAttribute			CFSTR("AXPreviousContents")
#define kAXContentsAttribute					CFSTR("AXContents")

// table/outline view attributes
#define kAXRowsAttribute						CFSTR("AXRows")
#define kAXVisibleRowsAttribute					CFSTR("AXVisibleRows")
#define kAXSelectedRowsAttribute				CFSTR("AXSelectedRows")
#define kAXColumnsAttribute						CFSTR("AXColumns")
#define kAXVisibleColumnsAttribute				CFSTR("AXVisibleColumns")
#define kAXSelectedColumnsAttribute				CFSTR("AXSelectedColumns")
#define kAXSortDirectionAttribute				CFSTR("AXSortDirection")

// outline attributes
#define kAXDisclosingAttribute					CFSTR("AXDisclosing")
#define kAXDisclosedRowsAttribute				CFSTR("AXDisclosedRows")
#define kAXDisclosedByRowAttribute				CFSTR("AXDisclosedByRow")

// system-wide attributes
#define kAXFocusedApplicationAttribute			CFSTR("AXFocusedApplication")

// old and/or obsolete attribute names
#define kAXSubRoleAttribute						kAXSubroleAttribute
#define kAXKeyAttribute							kAXFocusedAttribute
#define kAXMiniaturizedAttribute				kAXMinimizedAttribute
#define kAXCloseBoxUIElementAttribute			kAXCloseButtonAttribute
#define kAXZoomBoxUIElementAttribute			kAXZoomButtonAttribute
#define kAXMiniaturizeBoxUIElementAttribute		kAXMinimizeButtonAttribute
#define kAXToolbarBoxUIElementAttribute			kAXToolbarButtonAttribute
#define kAXWindowProxyUIElementAttribute		kAXProxyAttribute
#define kAXGrowBoxUIElementAttribute			kAXGrowAreaAttribute
#define kAXActiveAttribute						kAXFrontmostAttribute
#define kAXHeaderUIElementAttribute				kAXHeaderAttribute
#define kAXHorizontalScrollerAttribute			kAXHorizontalScrollBarAttribute
#define kAXVerticalScrollerAttribute			kAXVerticalScrollBarAttribute
#define kAXIsDisclosingAttribute				kAXDisclosingAttribute
#define kAXCanDiscloseAttribute					CFSTR("AXCanDisclose") // no longer used

//
// standard values
//

// orientations (see kAXOrientationAttribute)
#define kAXHorizontalOrientationValue			CFSTR("AXHorizontalOrientation")
#define kAXVerticalOrientationValue				CFSTR("AXVerticalOrientation")

// standard actions
#define kAXPressAction							CFSTR("AXPress")
#define kAXIncrementAction						CFSTR("AXIncrement")
#define kAXDecrementAction						CFSTR("AXDecrement")
#define kAXConfirmAction						CFSTR("AXConfirm")
#define kAXPickAction							CFSTR("AXPick")
#define kAXCancelAction							CFSTR("AXCancel")

// standard roles
#define kAXApplicationRole						CFSTR("AXApplication")
#define kAXSystemWideRole						CFSTR("AXSystemWide")
#define kAXWindowRole 							CFSTR("AXWindow")
#define kAXSheetRole							CFSTR("AXSheet")
#define kAXDrawerRole							CFSTR("AXDrawer")
#define kAXGrowAreaRole							CFSTR("AXGrowArea")
#define kAXImageRole							CFSTR("AXImage")
#define kAXUnknownRole							CFSTR("AXUnknown")
#define kAXButtonRole							CFSTR("AXButton")
#define kAXRadioButtonRole						CFSTR("AXRadioButton")
#define kAXCheckBoxRole 						CFSTR("AXCheckBox")
#define kAXPopUpButtonRole 						CFSTR("AXPopUpButton")
#define kAXMenuButtonRole						CFSTR("AXMenuButton")
#define kAXTabGroupRole							CFSTR("AXTabGroup")
#define kAXTableRole							CFSTR("AXTable")
#define kAXColumnRole							CFSTR("AXColumn")
#define kAXRowRole								CFSTR("AXRow")
#define kAXOutlineRole							CFSTR("AXOutline")
#define kAXBrowserRole							CFSTR("AXBrowser")
#define kAXScrollAreaRole 						CFSTR("AXScrollArea")
#define kAXScrollBarRole						CFSTR("AXScrollBar")
#define kAXRadioGroupRole	 					CFSTR("AXRadioGroup")
#define kAXListRole								CFSTR("AXList")
#define kAXGroupRole			    			CFSTR("AXGroup")
#define kAXValueIndicatorRole					CFSTR("AXValueIndicator")
#define kAXComboBoxRole							CFSTR("AXComboBox")
#define kAXSliderRole 							CFSTR("AXSlider")
#define kAXIncrementorRole						CFSTR("AXIncrementor")
#define kAXBusyIndicatorRole					CFSTR("AXBusyIndicator")
#define kAXProgressIndicatorRole		  		CFSTR("AXProgressIndicator")
#define kAXRelevanceIndicatorRole				CFSTR("AXRelevanceIndicator")
#define kAXToolbarRole							CFSTR("AXToolbar")

#define kAXTextFieldRole 						CFSTR("AXTextField")
#define	kAXTextAreaRole							CFSTR("AXTextArea")
#define kAXStaticTextRole 						CFSTR("AXStaticText")

#define kAXMenuBarRole							CFSTR("AXMenuBar")
#define kAXMenuRole								CFSTR("AXMenu")
#define kAXMenuItemRole				 			CFSTR("AXMenuItem")

#define kAXSplitGroupRole						CFSTR("AXSplitGroup")
#define kAXSplitterRole							CFSTR("AXSplitter")
#define kAXColorWellRole						CFSTR("AXColorWell")

// OBSOLETE ROLES - Will be removed soon
#define kAXViewRole								kAXUnknownRole
#define kAXUnknownBoxRole						kAXUnknownRole
#define kAXUnknownButtonRole					kAXUnknownRole
#define kAXControlRole							kAXUnknownRole
#define kAXCellRole								CFSTR("AXCell")
#define kAXMatrixRole 							CFSTR("AXMatrix")
#define kAXFormRole								CFSTR("AXForm")
#define kAXWindowTitleRole 						kAXStaticTextRole
#define kAXWindowProxyRole						kAXImageRole
#define kAXCloseBoxRole							kAXButtonRole
#define kAXZoomBoxRole						 	kAXButtonRole
#define kAXToolbarBoxRole						kAXButtonRole
#define kAXPushButtonRole						kAXButtonRole
#define kAXCheckboxRole 						kAXCheckBoxRole
#define kAXPullDownButtonRole 					kAXMenuButtonRole
#define kAXTabViewRole 							kAXTabGroupRole
#define kAXTablessTabViewRole					kAXGroupRole
#define kAXTabRole								kAXRadioButtonRole
#define kAXTableViewRole 						kAXTableRole
#define kAXTableHeaderViewRole					kAXGroupRole
#define kAXTableColumnRole						kAXColumnRole
#define kAXTableRowRole							kAXRowRole
#define kAXOutlineRowRole						kAXRowRole
#define kAXOutlineHeaderRole					kAXGroupRole
#define kAXOutlineHeaderButtonRole				kAXButtonRole
#define kAXOutlineCellRole						kAXStaticTextRole
#define kAXScrollViewRole 						kAXScrollAreaRole
#define kAXScrollerRole							kAXScrollBarRole
#define kAXRadioClusterRole 					kAXRadioGroupRole
#define kAXBoxRole				    			kAXGroupRole
#define kAXMiniaturizeBoxRole					kAXButtonRole
#define kAXMinimizeBoxRole						kAXButtonRole
#define kAXGrowBoxRole						 	kAXGrowAreaRole
#define kAXStepperRole							kAXIncrementorGroupRole
#define kAXToolbarIconRole						kAXButtonRole
#define kAXToolbarOverflowPullDownButtonRole	kAXMenuButtonRole
#define kAXToolbarItemPullDownButtonRole		kAXMenuButtonRole
#define kAXToolbarItemButtonRole				kAXButtonRole
#define kAXToolbarItemTitleRole				 	kAXButtonRole
#define kAXToolbarItemRole						kAXButtonRole
#define kAXLabelRole							kAXStaticTextRole
#define kAXTextRole								kAXStaticTextRole
#define kAXTitledTextFieldRole					kAXTextFieldRole
#define kAXTextViewRole 						kAXTextAreaRole
#define kAXOverflowUIElementAttribute			kAXOverflowButtonAttribute
#define kAXIncrementorGroupRole					kAXIncrementorRole
#define kAXWidthAttribute						CFSTR("AXWidth") // just use Size
#define kAXHeightAttribute              		CFSTR("AXHeight") // just use Size
#define kAXKeyWindowAttribute					kAXFocusedWindowAttribute
#define kAXIndicatorRole						kAXValueIndicatorRole
#define kAXAcceptAction							kAXConfirmAction
#define kAXToolbarDefaultItemsRole				CFSTR("AXToolbarDefaultItems")

// standard subroles
#define kAXCloseButtonSubrole					CFSTR("AXCloseButton")
#define kAXMinimizeButtonSubrole				CFSTR("AXMinimizeButton")
#define kAXZoomButtonSubrole					CFSTR("AXZoomButton")
#define kAXToolbarButtonSubrole					CFSTR("AXToolbarButton")
#define kAXSecureTextFieldSubrole				CFSTR("AXSecureTextField")
#define kAXTableRowSubrole						CFSTR("AXTableRow")
#define kAXOutlineRowSubrole					CFSTR("AXOutlineRow")
#define kAXUnknownSubrole						CFSTR("AXUnknown")

// focus notifications
#define kAXMainWindowChangedNotification		CFSTR("AXMainWindowChanged")
#define kAXFocusedWindowChangedNotification		CFSTR("AXFocusedWindowChanged")
#define kAXFocusedUIElementChangedNotification	CFSTR("AXFocusedUIElementChanged")

// application notifications
#define kAXApplicationActivatedNotification		CFSTR("AXApplicationActivated")
#define kAXApplicationDeactivatedNotification	CFSTR("AXApplicationDeactivated")
#define kAXApplicationHiddenNotification		CFSTR("AXApplicationHidden")
#define kAXApplicationShownNotification			CFSTR("AXApplicationShown")

// window notifications
#define kAXWindowCreatedNotification			CFSTR("AXWindowCreated")
#define kAXWindowMovedNotification				CFSTR("AXWindowMoved")
#define kAXWindowResizedNotification			CFSTR("AXWindowResized")
#define kAXWindowMiniaturizedNotification		CFSTR("AXWindowMiniaturized")
#define kAXWindowDeminiaturizedNotification		CFSTR("AXWindowDeminiaturized")

// element notifications
#define kAXValueChangedNotification				CFSTR("AXValueChanged")
#define kAXUIElementDestroyedNotification		CFSTR("AXUIElementDestroyed")

// menu notifications
#define kAXMenuOpenedNotification				CFSTR("AXMenuOpened")
#define kAXMenuClosedNotification				CFSTR("AXMenuClosed")
#define kAXMenuItemSelectedNotification			CFSTR("AXMenuItemSelected")

// OBSOLETE notifications - Will be removed soon
#define kAXKeyWindowChangedNotification			kAXFocusedWindowChangedNotification

#endif // __AXCONSTANTS__
