//
//  IKFilterUI.h
//  
//
//     Copyright (c) 2006 Apple Inc.
//
/*!
    @header IKFilterUI
    @abstract   Public API that client apps can call to retrieve a view representing the UI for a filter. 
    @discussion Introduction
	
In Leopard we want to fix a shortcoming of Core Image by making it easier for applications to present a UI for a CIFilter. In Tiger applications had to implement this task completely themselves by analyzing the keys of a filter and their attributes. We provided the Core Image Fun House application as sample code. The major shortcomings to overcome here is first to take the burden away from application developers to replicate the code we have in Fun House. Second we also want to allow filter developers to provide the ability to provide their own user interfaces which better reflect the aspects of a filter than a programatic interpretation of the keys and their attributes can do.
The solution here is that a filter can be queried to provide a view, which the application can insert into their UI. The view is a subclass of an NSView and therefore can be inserted easily into any other view as a subview or into an NSWindow as a content view. Even Carbon developers are not left out, as AppKit and Carbon provide bridges to use AppKit views and windows in Carbon apps. Inside the Core Image framework, we will implement an algorithm that can lay out controls for keys in a view, very much in the way as Fun House does today. This will be used for every filter that does not provide its own method of creating a view for its UI. The UI is not tied to one view with one control size. Instead we provide means for applications to retrieve views that match their choosing of size of UI elements as well as limiting the set of keys being represented in that UI. For example an iApp will only show a basic set of parameters for a filter, while a ProApp will allow the user to fiddle around with even more controls - even if only to suggest that the user is more sophisticated and can demand a higher salary. This approach is chosen to bridge the gap between all kinds of UIs applications use today and not having the filter developer to create special case UIs for every single app but on the other hand not to stick out as a sore thumb in an application either.

API in IKFilterUI.h

	Public API that client apps can call to retrieve a view representing the UI for a filter. The client app has to retain the view as long as it needs it but is supposed to release it as soon as it doesn't need it anymore as the view is retaining the filter.

-(IKFilterUIView*)viewForUIConfiguration:(NSDictionary*)inUIConfiguration excludedKeys:(NSArray*)inKeys;
This call is supposed to be called by the client to receive a view for a given filter. The CIFilter class will call the provideViewForUIConfiguration method, which can be overriden by a subclass of CIFilter, otherwise it generates a UI based on the keys and their attributes.
	inUIConfiguration 
		see UIConfiguration Dictionary below
	excludedKeys
		an array of keys that should not be included in the view (for example inputImage will often be excluded). This can be nil, if no keys should be excluded

NOTE: The view retains the filter and therefore should be released before the filter gets released.


IKFilterCustomUIProvider protocol:

-(IKFilterUIView*)provideViewForUIConfiguration:(NSDictionary*)inUIConfiguration excludedKeys:(NSArray*)inKeys;
This call is overriden by a filter to provide a view for the viewForUIConfiguration method.
	inUIConfiguration 
		see UIConfiguration Dictionary below
	excludedKeys
		an array of keys that should not be included in the view (for example inputImage will often be excluded). This can be nil, if no keys should be excluded

	When the filter cannot provide a view, the Core Image framework will generate a view based on the given paramerters (in a manner like CI Fun House does today).

*/

#import <Foundation/Foundation.h>
#import <QuartzCore/QuartzCore.h>
#import <ImageKit/ImageKitBase.h>
#import <ImageKit/IKFilterUIView.h>

/*!
    @const      IKUISizeFlavor
    @abstract   IKUISizeFlavor
    @discussion Key to request the desired size of controls in a filter UIView - defined values are IKUISizeMini, IKUISizeSmall and IKUISizeRegular.
*/
extern NSString *IKUISizeFlavor;

/*!
    @const      IKUISizeMini
    @abstract   IKUISizeMini
    @discussion Constant for requesting controls in mini size.
*/
extern NSString *IKUISizeMini;

/*!
    @const      IKUISizeSmall
    @abstract   IKUISizeSmall
    @discussion Constant for requesting controls in small size.
*/
extern NSString *IKUISizeSmall;

/*!
    @const      IKUISizeRegular
    @abstract   IKUISizeRegular
    @discussion Constant for requesting controls in regular or normal size.
*/
extern NSString *IKUISizeRegular;

/*!
    @const      IKUImaxSize
    @abstract   IKUImaxSize
    @discussion Maximum allowed dimensions of the view for the filter UI. If width or height is zero it means that that dimension of the view is not restricted.
*/
extern NSString *IKUImaxSize;

/*!
    @const      IKUIFlavorAllowFallback
    @abstract   IKUIFlavorAllowFallback
    @discussion Allow the filter to provide a view with controls of a different size and set than requested, if it cannot provide a view for the requested flavor.
*/
extern NSString *IKUIFlavorAllowFallback;


/*!
    @category	IKFilterUIAddition
    @abstract    The IKFilterUIAddition category to IKFilter provides the API for the Image Unit UI generation.
    @discussion  (comprehensive description)
*/

@interface CIFilter (IKFilterUIAddition) 

/*!
    @method     viewForUIConfiguration:excludedKeys:
    @abstract   The viewForUIConfiguration returns a IKFilterView for the filter. The UI is either created by the filter or automatically generated by the CoreImageKit framework.
    @discussion The viewForUIConfiguration first requests that the filter provides a UI by calling provideViewForUIConfiguration. If this method is not implemented or the filter cannot provide a UI for the given configuration, the CoreImageKit framework will generate a UI.
		The UIConfiguration dictionary is an NSDictionary with the following defined keys:
	@param	UIConfiguration	Dictionary with the IKUISizeFlavor and the kCIUIParameterSet information - see below.
	@param	excludedKeys	An array of keys that should not be included in the view (for example inputImage will often be excluded). This can be nil, if no keys should be excluded

IKUISizeFlavor:

	mini:		IKUISizeMini
	
	small:		IKUISizeSmall
	
	regular:	IKUISizeRegular
	
These sizes follow the size conventions available in Tiger IB

kCIUIParameterSet:

	basic:			kCIUISetBasic
	
	intermediate:		kCIUISetIntermediate
	
	advanced:		kCIUISetAdvanced
	
	development:	kCIUISetDevelopment
	
When a client app requests a UI for a parameter set, all keys for that set and below will be included - example: advanced consists of all parameters in the basic, intermediate and advanced set.
The development set is targeted towards the development of filters and client apps. Parameters in this set are either experimental or for debugging purposes and should not be shown in a shipping product.
IKUImaxSize:(NSSize)maxSize;	Maximum allowed dimension of the returned view. If the size requested is too small, the filter is expected to return a view as small as possible. It is up to the client to verify that the returned view fits into his context.
IKUIFlavorAllowFallback:Boolean	If a requested flavor set-size combination is not supported, the filter can return a view for a different set-size combination. If this is set to no (which is the default), NULL should be returned by the filter


*/
-(IKFilterUIView*)viewForUIConfiguration:(NSDictionary*)inUIConfiguration excludedKeys:(NSArray*)inKeys;

@end


/*!
    @protocol	IKFilterCustomUIProvider
    @abstract    The IKFilterCustomUIProvider needs to be implemented by a filter to implement its own UI. 
    @discussion  When a filter wants to provide its own UI for all or only some configurations, it has to implement the provideViewForUIConfiguration method.
*/
@protocol IKFilterCustomUIProvider

/*!
    @method     provideViewForUIConfiguration:excludedKeys:
    @abstract   The provideViewForUIConfiguration gets called, when a client requests a filter UI by calling viewForUIConfiguration:excludedKeys.
    @discussion See description in viewForUIConfiguration:excludedKeys for details on the parameters. If a filter cannot provide a IKFilterUIView for a given UIConfiguration, it can return nil and the CoreImageKit framework will try to provide a UI for it instead.
*/
-(IKFilterUIView*)provideViewForUIConfiguration:(NSDictionary*)inUIConfiguration excludedKeys:(NSArray*)inKeys;

@end
