#import <Cocoa/Cocoa.h>

#import <PrintCore/PMTicket.h>
#import <cups/cups.h>


/*!
 * @protocol	PDEPlugIn
 * @abstract	An instance implementing methods in the PDEPlugIn informal protocol protocol
 *				acts as a factory for PDEPanels. The factory is provided with the type
 *				of printer panel needed (page setup or print dialog) as well as
 *				the current printer. It can use this information to determine which
 *				PDEPanels should be created.
 *
 */
@interface NSObject(PDEPlugIn)

/*!
 * @method		initWithBundle:
 * @abstract	Called once when the PDE plug-in is loaded.
 *
 * @param theBundle		The plug-in's bundle.
 *
 * @result	Returns YES if initialization succeeded and NO otherwise.
 */
- (BOOL)initWithBundle:(NSBundle*)theBundle;

/*!
 * @method		PDEPanelsForType:withHostInfo:
 * @abstract	Returns an array of instances conforming to the PDEPanel informal protocol.
 *
 * @param		pdeType	The type of print panels that should be returned. These kinds are
 *				defined in PMPrintingDialogExtensions.h and include:
 *					kGeneralPageSetupDialogTypeIDStr
 *						- Panels that should be shown in the page setup dialog.
 *					kGeneralPrintDialogTypeIDStr
 *						- Panels that should be shown in the print dialog.
 *
 * @param	host	A print system provided instance that implements methods from the informal protocol
 *					PDEPlugInCallbackProtocol. The PDEPlugIn can use this parameter to
 *					obtain the current printer or print setting in order to filter the
 *					available panels if there are printer specific PDEPanels in the PDEPlugIn.	
 *
 * @result	An array of instances implementing methods from the PDEPanel informal protocol.
 *			Each instance represents a panel that will be shown in the printer dialog.
 *			The method may return either nil or an empty array if no panels should be used.
 */
- (NSArray*)PDEPanelsForType:(NSString*)pdeType withHostInfo:(id)host;

@end


/*!
 * @protocol	PDEPanel
 * @abstract	A print dialog plugin should have an instance implementing methods
 *				from the PDEPanel informal protocol. Each such instance handles a single
 *				print dialog panel.
 *
 */
@interface NSObject(PDEPanel)

/*!
 * @method		willShow
 * @abstract	The panel should complete any final preperations it needs
 *				before the panel is shown.
 *
 * @discussion	The panel may want to use this method to lazily prepare
 *				its user interface.
 *
 */
- (void)willShow;

/*!
 * @method		shouldHide
 * @abstract	Prepare the panel to be removed from the user's sight.
 *
 * @discussion	This method is invoked by the print system just before the panel is
 *				removed fromthe user's sight. The panel can use this opportunity
 *				for any final interaction with the user, perhaps to check the user's
 *				input. A panel that needs more interaction with the user, perhaps
 *				because some of the input values were invalid, should return NO.
 *				Returning YES indicates that the panel can be hidden, probably to
 *				show another panel or to dismiss the printing dialog.
 *
 * @result		Return YES if it is okay to hide panel and NO otherwise.
 */
- (BOOL)shouldHide;

/*!
 * @method		saveValuesAndReturnError:
 * @abstract	Take the values from the panel's user interface and write them to
 *				the appropriate settings.
 *
 * @discussion	This is the panel's chance to write the values from its user interface
 *				controls to the permanent store. Depending upon the panel type the values may
 *				be stored in the print settings or into the page format. Panels of type
 *				kGeneralPageSetupDialogTypeIDStr will generally store values into the page
 *				format while panels of type kGeneralPrintDialogTypeIDStr will write to
 *				the print settings. The panel should use the provided PDEPlugInCallbackProtocol
 *				to obtain the settings and tickets it needs to write into.
 *
 *				A panel will usually be asked to write its values when the user dismisses
 *				the dialog, other than via cancel, or when the user has asked that a preset
 *				be saved.
 */
- (BOOL)saveValuesAndReturnError:(NSError **)error;

/*!
 * @method		restoreValuesAndReturnError
 * @abstract	Set the panel's user interface elements based upon the appropriate settings.
 *
 * @discussion	The panel should refresh its user interface elements by reading values from
 *				the page format or print settings. The panel should use the provided
 *				PDEPlugInCallbackProtocol to obtain the settings and tickets it needs to read.
 *
 *				A panel will usually be asked to read its setting just before it is first
 *				shown and when the user selects a new preset.
 */
- (BOOL)restoreValuesAndReturnError:(NSError **)error;

/*!
 * @method		supportedPPDOptionKeys
 * @abstract	The panel takes responsability for displaying user interface elements for the
 *				PPD option keys returned from this call.
 *
 * @discussion	Any PPD option keys not claimed by a PDEPanel are provided with a dynamically built
 *				user interface in the Printer Features panel.
 */
- (NSArray *)supportedPPDOptionKeys;

/*!
 * @method		PPDOptionKeyValueDidChange
 * @abstract	Inform the panel that, external to the panel, the specified PPD
 *				choice has been made.
 *
 * @discussion	During PPD conflict resolution the choice for a panel controlled PPD option
 *				may need to be changed by another panel. This call informs the panel
 *				that a setting has been changed. The panel should update any internal data it maintains
 *				in regards to this PPD option key.
 *
 *				The 'option' and 'choice' values are taken from the printer's PPD. For
 *				example the PPD fragment:
 *
 *					*OpenUI *TraySwitch/Tray Switch:	Boolean
 *					*TraySwitch True/On: "1 dict dup /TraySwitch true put setpagedevice"
 *					*TraySwitch False/Off: "1 dict dup /TraySwitch false put setpagedevice"
 *					*CloseUI: *TraySwitch
 *
 *				describes the option 'TraySwitch'. It has 2 choices: 'True' and 'False'.
 *				If another panel caused the choice of the option key 'TraySwitch' to be
 *				altered to 'True'then this method will be called with the 'option' parameter
 *				set to @"TraySwitch" and the 'choice parameter set to @"True".
 */
- (void)PPDOptionKeyValueDidChange:(NSString *)option ppdChoice:(NSString *)choice;

/*!
 * @method		panelView
 * @abstract	Return the panel's view.
 *
 * @discussion	The panel's controls are rendered into a single view. The print system
 *				invokes this method to obtain the panel's view so that it can be embedded
 *				into the print dialog.
 */
- (NSView*)panelView;

/*!
 * @method		panelName
 * @abstract	Return the panel's name.
 *
 * @discussion	This is the localized name of the panel. It will be placed into
 *				the panel menu.
 */
- (NSString*)panelName;

/*!
 * @method		panelKind
 * @abstract	Return the panel's kind.
 *
 * @discussion	A panel's kind is used to allow a plugin to override a system panel.
 *				PMPrintingDialogExtensions.h lists the kinds for the print system provided
 *				panels. If a PDF panel is not supposed to override a print system provided
 *				panel then it should return a unique string for its kind.
 */
- (NSString*)panelKind;

/*!
 * @method		summaryInfo
 * @abstract	Return localized, textual descriptions of the panel's settings.
 *
 * @discussion	Each key in the dictionary must be an NSString providing the name
 *				of the setting. The value for the key must be an NSString describing
 *				the value for the setting. The strings should be localized for the
 *				current user. For example a key in the dictionary for the copies and
 *				pages panel might have the key 'Page Range' and the value 'All'.
 */
- (NSDictionary *)summaryInfo;

@end


/*!
 * @protocol	PDEPlugInCallbackProtocol
 * @abstract	An informal protocol implemented by the print system so
 *				that printing dialog extensions can obtain information
 *				about the current printer and print job.
 *
 * @discussion	An print system created instance implementing the informal protocol,
 *				PDEPlugInCallbackProtocol, is passed to PDEPlugin as part of the PDEPlugIn's
 *				PDEPanelsForType:withHostInfo: message. The PDEPlugIn is expected to
 *				hold on to the passed in instance and to use this PDEPlugInCallbackProtocol
 *				to query the print system for relevant information. The PDEPlugin can
 *				pass the instance implementing PDEPlugInCallbackProtocol to PDEPanels
 *				as needed.
 */
@interface NSObject(PDEPlugInCallbackProtocol)

/*!
 * @method		printSession
 * @abstract	Return a reference to the current print session.
 */
- (PMPrintSession) printSession;

/*!
 * @method		printSettings
 * @abstract	Return a reference to the print settings object that is
 *				being modified by the printer dialog.
 *
 * @discussion	This method will return nil if the current print dialog is
 *				not operating on a print settings. The page setup dialog is
 *				the most obvious case where this method will return nil.
 */
- (PMPrintSettings) printSettings;

/*!
 * @method		pageFormat
 * @abstract	Return a reference to the page format that is being used
 *				by the printer dialog.
 *
 * @discussion	The caller should be prepared for this method to return nil
 *				if the current print dialog is operating without a page format
 *				instance. Today both the print and page setup dialogs will return
 *				a reference to a page format object.
 */
- (PMPageFormat) pageFormat;

/*!
 * @method		PMPrinter
 * @abstract	Return a reference to the current printer instance.
 *
 * @discussion	When the page setup dialog is displayed this method will return
 *				the user's default printer. When the print dialog is displayed this
 *				method will return the printer currently selected in the print dialog.
 */
- (PMPrinter) PMPrinter;

/*!
 * @method		jobTemplate
 * @abstract	Return a reference to the current printer's job template.
 *
 * @discussion	The returned job template describes user options of the
 *				current printer. This method should
 *				only be used by printer dialog plugins associated with Tioga
 *				based printer drivers. CUPS based printer drivers should use
 *				the ppdFile method to obtain printer information.
 */
- (PMTemplateRef) jobTemplate;

/*!
 * @method		printerInfoTicket
 * @abstract	Return a reference to the current printer's printer information
 *				ticket.
 *
 * @discussion	The printer information ticket describes the current printer with
 *				information such as its model name. This method should
 *				only be used by printer dialog plugins associated with Tioga
 *				based printer drivers. CUPS based printer drivers should use
 *				the ppdFile method to obtain printer information.
 */
- (PMTicketRef) printerInfoTicket;

/*!
 * @method		ppdFile
 * @abstract	Return a pointer to the CUPS ppd information for the current printer.
 *
 * @discussion	Once the caller has the pointer to the CUPS PPD structure the CUPS
 *				PPD functions can be used to query the PPD and to set PPD options.
 *				A description of some of the CUPS PPD functions is here:
 *				http://127.0.0.1:631/spm.html#3_3
 */
- (ppd_file_t*) ppdFile;

/*!
 * @method		changePPDOptionKeyValue:ppdChoiceKey:
 * @abstract	A PDEPlugIn makes this call to let the print system know that
 *				the plugin intends to alter the choice for a PPD option. 
 *
 * @discussion	When a print dialog plugin intends to change the choice for a
 *				PPD option it notifies the print system with this call. If the
 *				desired choice is in conflict with other currently selected PPD options
 *				then the print system will try to do conflict resolution. This may
 *				include presenting the user with a dialog explaining the conflict
 *				and allowing the user to cancel the change.
 *
 *				The 'option' parameter names a main key from the printer's PPD.
 *				As an example take the following PPD fragment:
 *
 *					*OpenUI *MediaType/Paper Type: PickOne
 *					*MediaType Plain/Plain: ""
 *					*MediaType Transparency/Transparency: ""
 *					*CloseUI: *MediaType
 *
 *				If a panel wishes to switch the value of the option key 'MediaType'
 *				to the choice 'Transparency' then it should invoke this callback
 *				passing @"MediaType" and @"Transparency" as the 'option' and
 *				'choice' parameters. If that choice is allowed then YES will be
 *				returned otherwise NO.
 
 * @result 		Returns YES if the plugin should make the change and returns NO if the
 *				user or the print system would like the change not to occur.
 */	
- (BOOL)willChangePPDOptionKeyValue:(NSString *)option ppdChoice:(NSString *)choice;

/*!
 * @method		panelViewDidResize
 * @abstract	A PDEPlugIn calls this method to inform the print system that the plugin's
 *				view size has changed. In response the print system will resize the printer
 *				dialog to show as much as possible of the view.
 */
- (void)panelViewDidResize;


@end

