/*
 *  AXRoleConstants.h
 *  HIServices
 *
 *  Created by John Louch on Wed Feb 25 2004.
 *  Copyright (c) 2004 Apple Computer, Inc. All rights reserved.
 *
 */

#ifndef __AXROLECONSTANTS__
#define __AXROLECONSTANTS__

/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* Roles                                                                                */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/

/*
	Every role offers a variety of attributes. There are some attributes that must be
	supported by every element, regardless of role. Other attributes will be supported
	by an element if/when appropriate data is supplied by the application. These
	attributes' meanings and values are generally obvious. In order to save space, the
	following attributes are not listed in the role documentation unless the role
	handles them in a special fashion:
	
		AXRole
		AXRoleDescription
		AXDescription
		AXHelp
		AXParent
		AXChildren
		AXWindow
		AXTopLevelUIElement
		AXEnabled
		AXSize
		AXPosition
	
	Every attribute supported by a given role may have one or more symbols after its
	name:
		w means the attribute is writable.
		o means it is an optional attribute that doesn't necessarily need to be
			supported by all elements with that role.

	TBD:
		Add a general section answering the following questions:
			When and why would a developer create a new role?
			When and why would a developer create a new subrole?
		Add a Quick Reference section, like the one at the top of the attributes.
*/

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


/*
	kAXOutlineRole
	
	An element that contains row-based data. It may use disclosure triangles to manage the
	display of hierarchies within the data. It may arrange each row's data into columns and
	offer a header button above each column. The best example is the list view in a Finder
	window or Open/Save dialog.

	Outlines are typically children of AXScrollAreas, which manages the horizontal and/or
	vertical scrolling for the outline. Outlines are expected to follow certain conventions
	with respect to their hierarchy of sub-elements. In particular, if the outline uses
	columns, the data should be accessible via either rows or columns. Thus, the data in a
	given cell will be represented as two diffrent elements. Here's a hierarchy for a
	typical outline:
	
		AXScrollArea (parent of the outline)
			AXScrollBar (if necessary, horizontal)
			AXScrollBar (if necessary, vertical)
			AXOutline
				AXGroup (header buttons, optional)
					AXButton, AXMenuButton, or <Varies> (header button)
					...
				AXRow (first row)
					AXStaticText (just one possible example)
					AXButton (just another possible example)
					AXTextField (ditto)
					AXCheckBox (ditto)
				AXRow (as above)
				...
				AXColumn (first column)
					AXStaticText (assumes the first column displays text)
					AXStaticText
					...
				AXColumn (second column)
					AXButton (assumes the second column displays buttons)
					AXButton
					...
				...
				
    Attributes:
        AXFocused (w)
        AXRows - Array of subset of AXChildren that are rows.
        AXVisibleRows - Array of subset of AXRows that are visible.
        AXSelectedRows (w) Array of subset of AXRows that are selected.
        AXColumns - Array of subset of children that are columns.
        AXVisibleColumns - Array of subset of columns that are visible.
        AXSelectedColumns (o) Array of subset of columns that are selected.
        AXHeader (o) The AXGroup element that contains the header buttons.
*/
#define kAXOutlineRole					CFSTR("AXOutline")


/*
	kAXBrowserRole
	
	An element that contains columns of hierarchical data. Examples include the column view
	in Finder windows and Open/Save dialogs. Carbon's Data Browser in column view mode
	represents itself as an AXBrowser. Cocoa's NSBrowser represents itself as an AXBrowser.
	
	Browser elements are expected to have a particular hierarchy of sub-elements within it.
	In particular, the child of an AXBrowser must be an AXScrollArea that manages the
	horizontal scrolling. The horizontal AXScrollArea must include a child for each column
	the interface displays. Columns can be any role that makes sense. Typically, columns
	are vertical AXScrollAreas with AXList children. Here's a hierarchy for a typical
	browser:
	
		AXBrowser
			AXScrollArea (manages the horizontal scrolling)
				AXScrollBar (horizontal scroll bar)
				AXScrollArea (first column)
					AXScrollBar (column's vertical scroll bar)
					AXList (column content is typically a list, but it could be another role)
						<Varies> (cell)
						...
						<Varies> (cell)
				AXScrollArea (second column)
					...
				AXScrollArea (third column)
					...
				AXGroup (preview column)
					...
	
	Attributes:
		AXFocused (w)
		AXColumns - Array of the grandchild column elements, which are typically
			of the AXScrollArea role.
		AXVisibleColumns - Array of the subset of elements in the AXColumns array
			that are currently visible.
		AXColumnTitles (o)
		AXHorizontalScrollBar - The horizontal AXScrollBar of the browser's child
			AXScrollArea.
*/
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
#define kAXRelevanceIndicatorRole			CFSTR("AXRelevanceIndicator")
#define kAXToolbarRole					CFSTR("AXToolbar")
#define kAXDisclosureTriangleRole 			CFSTR("AXDisclosureTriangle")


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

#define kAXTimeFieldRole				CFSTR("AXTimeField")
#define kAXDateFieldRole				CFSTR("AXDateField")

#define kAXHelpTagRole					CFSTR("AXHelpTag")

#define kAXMatteRole					CFSTR("AXMatteRole")

#define kAXDockItemRole					CFSTR("AXDockItem")

#define kAXRulerRole					CFSTR("AXRuler")
#define kAXRulerMarkerRole				CFSTR("AXRulerMarker")

/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* Subroles                                                                                */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/

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
#define kAXSortButtonSubrole 				CFSTR("AXSortButton")
#define kAXSearchFieldSubrole				CFSTR("AXSearchField")

// dock subroles
#define kAXApplicationDockItemSubrole			CFSTR("AXApplicationDockItem")
#define kAXDocumentDockItemSubrole			CFSTR("AXDocumentDockItem")
#define kAXFolderDockItemSubrole			CFSTR("AXFolderDockItem")
#define kAXMinimizedWindowDockItemSubrole		CFSTR("AXMinimizedWindowDockItem")
#define kAXURLDockItemSubrole				CFSTR("AXURLDockItem")
#define kAXDockExtraDockItemSubrole			CFSTR("AXDockExtraDockItem")
#define kAXTrashDockItemSubrole				CFSTR("AXTrashDockItem")
#define kAXProcessSwitcherListSubrole			CFSTR("AXProcessSwitcherList")


#endif // __AXROLECONSTANTS__

