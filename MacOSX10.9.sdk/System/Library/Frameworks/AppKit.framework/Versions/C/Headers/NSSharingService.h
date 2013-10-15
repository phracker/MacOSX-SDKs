/*
 NSSharingService.h
 Application Kit
 Copyright (c) 2011-2013, Apple Inc.
 All rights reserved.
 */

#import <AppKit/AppKitDefines.h>
#import <AppKit/NSPasteboard.h>
#import <Foundation/NSGeometry.h>
#import <Foundation/NSObject.h>
@class NSString, NSImage, NSArray, NSView, NSError, NSWindow;

/* NSSharing can be used to share items to different kinds of local and remote services. Items are objects which respond to the NSPasteboardWriting protocol, like NSURL, NSImage or NSString. If an NSURL is a file URL (point to a video for example), then the content of the file will be shared. If the URL is remote, then the URL itself will be shared. 
 */

/* built-in sharing services
 */
APPKIT_EXTERN NSString * const NSSharingServiceNamePostOnFacebook NS_AVAILABLE_MAC(10_8);
APPKIT_EXTERN NSString * const NSSharingServiceNamePostOnTwitter NS_AVAILABLE_MAC(10_8);
APPKIT_EXTERN NSString * const NSSharingServiceNamePostOnSinaWeibo NS_AVAILABLE_MAC(10_8);
APPKIT_EXTERN NSString * const NSSharingServiceNamePostOnTencentWeibo NS_AVAILABLE_MAC(10_9);
APPKIT_EXTERN NSString * const NSSharingServiceNamePostOnLinkedIn NS_AVAILABLE_MAC(10_9);
APPKIT_EXTERN NSString * const NSSharingServiceNameComposeEmail NS_AVAILABLE_MAC(10_8);
APPKIT_EXTERN NSString * const NSSharingServiceNameComposeMessage NS_AVAILABLE_MAC(10_8);
APPKIT_EXTERN NSString * const NSSharingServiceNameSendViaAirDrop NS_AVAILABLE_MAC(10_8);
APPKIT_EXTERN NSString * const NSSharingServiceNameAddToSafariReadingList NS_AVAILABLE_MAC(10_8);
APPKIT_EXTERN NSString * const NSSharingServiceNameAddToIPhoto NS_AVAILABLE_MAC(10_8);
APPKIT_EXTERN NSString * const NSSharingServiceNameAddToAperture NS_AVAILABLE_MAC(10_8);
APPKIT_EXTERN NSString * const NSSharingServiceNameUseAsTwitterProfileImage NS_AVAILABLE_MAC(10_8);
APPKIT_EXTERN NSString * const NSSharingServiceNameUseAsFacebookProfileImage NS_AVAILABLE_MAC(10_9);
APPKIT_EXTERN NSString * const NSSharingServiceNameUseAsLinkedInProfileImage NS_AVAILABLE_MAC(10_9);
APPKIT_EXTERN NSString * const NSSharingServiceNameUseAsDesktopPicture NS_AVAILABLE_MAC(10_8);
APPKIT_EXTERN NSString * const NSSharingServiceNamePostImageOnFlickr NS_AVAILABLE_MAC(10_8);
APPKIT_EXTERN NSString * const NSSharingServiceNamePostVideoOnVimeo NS_AVAILABLE_MAC(10_8);
APPKIT_EXTERN NSString * const NSSharingServiceNamePostVideoOnYouku NS_AVAILABLE_MAC(10_8);
APPKIT_EXTERN NSString * const NSSharingServiceNamePostVideoOnTudou NS_AVAILABLE_MAC(10_8);


@protocol NSSharingServiceDelegate;

NS_CLASS_AVAILABLE(10_8, NA)
@interface NSSharingService : NSObject {
@private
    id _reserved;
}
@property (assign) id <NSSharingServiceDelegate> delegate;
@property (readonly, copy) NSString *title;
@property (readonly, retain) NSImage *image;
@property (readonly, retain) NSImage *alternateImage;

/* Title of the service in the Share menu. Can be modified. */
@property (copy) NSString *menuItemTitle NS_AVAILABLE_MAC(10_9); 

/* These properties are used for configuration of the service. They need to be set when the NSSharingService is created or in sharingService:willShareItems:
 */
@property (copy) NSArray *recipients NS_AVAILABLE_MAC(10_9);    // NSArray of NSString objects representing handles (example: email adresses)
@property (copy) NSString *subject NS_AVAILABLE_MAC(10_9);

/* These read-only properties allow for querying of the shared content:
 */
// Message body as string
@property (readonly, copy) NSString *messageBody NS_AVAILABLE_MAC(10_9);
// URL to access the post on Facebook, Twitter, Sina Weibo, etc. (also known as permalink)
@property (readonly, copy) NSURL *permanentLink NS_AVAILABLE_MAC(10_9);
// Account name used for sending on Twitter or Sina Weibo
@property (readonly, copy) NSString *accountName NS_AVAILABLE_MAC(10_9);
// NSArray of NSURL objects representing the file that were shared
@property (readonly, copy) NSArray *attachmentFileURLs NS_AVAILABLE_MAC(10_9);



/* Returns a list of NSSharingServices which could share all the provided items together. sharingServicesForItems can be used to build a custom UI, or to populate a contextual NSMenu. 
 */
+ (NSArray *)sharingServicesForItems:(NSArray *)items;


/* Returns an NSSharingService representing one of the built-in services. 
 */
+ (NSSharingService *)sharingServiceNamed:(NSString *)serviceName;


#if NS_BLOCKS_AVAILABLE
/* Creates a custom NSSharingService object. Custom sharing services can be added to the NSSharingServicePicker with the sharingServicePicker:sharingServicesForItems:proposedSharingServices: delegate method. 
 */
- (id)initWithTitle:(NSString *)title image:(NSImage *)image alternateImage:(NSImage *)alternateImage handler:(void (^)(void))block;
#endif


/* Returns whether a service can do something with all the provided items. This can be used to validate a custom UI such as a dedicated Twitter button. If items is nil, the method will return YES when the service is configured. Therefore you could call it once at launch time with nil items to check whether to display the button or not, and then with real items to enable and disable the button depending on the context or selection.
 */
- (BOOL)canPerformWithItems:(NSArray *)items;


/* Manually performs the service on the provided items. In most cases this will display a sharing window.
 */
- (void)performWithItems:(NSArray *)items;

@end


/* Use the sharing scope to specify the nature of the things you are sharing.  
 - NSSharingContentScopeItem: use when sharing a clearly identified item, e.g. a file represented by its icon.  
 - NSSharingContentScopePartial: use when sharing a portion of a more global content, e.g. part of a webpage
 - NSSharingContentScopeFull: use when sharing the whole content of the current document, e.g. the url of the webpage
 
 The sharing scope can be modified from the default value of NSSharingContentScopeItem by setting a different value in the out parameter in sharingService:sourceWindowForShareItems:sharingContentScope:
 */
typedef NS_ENUM(NSInteger, NSSharingContentScope) {
    NSSharingContentScopeItem,
    NSSharingContentScopePartial,
    NSSharingContentScopeFull
}  NS_ENUM_AVAILABLE_MAC(10_8);

@protocol NSSharingServiceDelegate <NSObject>
@optional
- (void)sharingService:(NSSharingService *)sharingService willShareItems:(NSArray *)items;
- (void)sharingService:(NSSharingService *)sharingService didFailToShareItems:(NSArray *)items error:(NSError *)error;
- (void)sharingService:(NSSharingService *)sharingService didShareItems:(NSArray *)items;


/* The following methods are invoked when the service is performed and the sharing window pops up, to present a transition between the original items and the sharing window.
 */
- (NSRect)sharingService:(NSSharingService *)sharingService sourceFrameOnScreenForShareItem:(id <NSPasteboardWriting>)item;
- (NSImage *)sharingService:(NSSharingService *)sharingService transitionImageForShareItem:(id <NSPasteboardWriting>)item contentRect:(NSRect *)contentRect;
- (NSWindow *)sharingService:(NSSharingService *)sharingService sourceWindowForShareItems:(NSArray *)items sharingContentScope:(NSSharingContentScope *)sharingContentScope;

@end





@protocol NSSharingServicePickerDelegate;

NS_CLASS_AVAILABLE(10_8, NA)
@interface NSSharingServicePicker : NSObject 
{
@private
    id _reserved;
}

@property (assign) id <NSSharingServicePickerDelegate> delegate;

/*  Returns a new picker. The items represent the objects to be shared and must conform to the <NSPasteboardWriting> protocol. (e.g. NSString, NSImage, NSURL, etc.)
 */
- (id)initWithItems:(NSArray *)items;


/* Shows the picker, populated with sharing services related to the instance items. When the user selects one of the sharing services, the sharing service will be performed. Note that this method must be called on mouseDown.
 */
- (void)showRelativeToRect:(NSRect)rect ofView:(NSView *)view preferredEdge:(NSRectEdge)preferredEdge;

@end


@protocol NSSharingServicePickerDelegate <NSObject>
@optional

/* Allows the delegate to customize exactly what appears in the sharing service picker by reordering or removing the services before the picker is presented. It's possible to add custom services by mutating the proposedSharingServices array and adding new NSSharingService instances:
        NSMutableArray *sharingServices = [proposedServices mutableCopy];
        NSSharingService * customService = [[[NSSharingService alloc]   initWithTitle:@"Service Title" 
                                                                        image:image alternateImage:alternateImage 
                                                                        handler:^{
                                                                            [self doCustomServiceWithItems:items];
                                           }] autorelease];
        [sharingServices addObject:customService];
        return [sharingServices autorelease];
 */
- (NSArray *)sharingServicePicker:(NSSharingServicePicker *)sharingServicePicker sharingServicesForItems:(NSArray *)items proposedSharingServices:(NSArray *)proposedServices;


/* Invoked when the user has selected a service and the picker is about to execute it.
 */
- (id <NSSharingServiceDelegate>)sharingServicePicker:(NSSharingServicePicker *)sharingServicePicker delegateForSharingService:(NSSharingService *)sharingService;


/* Invoked when the user has selected a service and before it is executed. Service will be nil if the picker was dismissed.
 */
- (void)sharingServicePicker:(NSSharingServicePicker *)sharingServicePicker didChooseSharingService:(NSSharingService *)service;

@end
