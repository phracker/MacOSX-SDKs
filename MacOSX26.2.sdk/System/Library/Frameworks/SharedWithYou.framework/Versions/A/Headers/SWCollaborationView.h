#import <TargetConditionals.h>
#if !TARGET_OS_TV
//
//  SWCollaborationView.h
//  SocialLayer
//
//  Copyright (c) 2022 Apple. All rights reserved.
//

#import <SharedWithYouCore/SWDefines.h>

#if TARGET_OS_OSX
#import <AppKit/AppKit.h>
#else
#import <UIKit/UIKit.h>
#endif

NS_ASSUME_NONNULL_BEGIN

@class SWCollaborationView;

API_AVAILABLE(ios(16.0), macos(13.0))
@protocol SWCollaborationViewDelegate <NSObject>

@optional
- (BOOL)collaborationViewShouldPresentPopover:(SWCollaborationView *)collaborationView;
- (void)collaborationViewWillPresentPopover:(SWCollaborationView *)collaborationView;
- (void)collaborationViewDidDismissPopover:(SWCollaborationView *)collaborationView;

@end


#if TARGET_OS_OSX
API_AVAILABLE(macos(13.0))
@interface SWCollaborationView : NSView
@property (nullable, weak) id <NSCloudSharingServiceDelegate> cloudSharingDelegate;

- (void)setContentView:(NSView *)detailViewListContentView;
#else
API_AVAILABLE(ios(16.0))
@interface SWCollaborationView : UIView

#if !TARGET_OS_TV
@property (nonatomic, weak) id<UICloudSharingControllerDelegate> cloudSharingDelegate;
#endif

- (void)setContentView:(UIView *)detailViewListContentView;
#endif

- (instancetype)initWithItemProvider:(NSItemProvider *)itemProvider;

@property (nonatomic, assign) NSUInteger activeParticipantCount;

@property (nonatomic, weak) id<SWCollaborationViewDelegate> delegate;

@property (nonatomic, copy) NSString *headerTitle;
@property (nonatomic, copy) NSString *headerSubtitle;
#if TARGET_OS_OSX
@property (nonatomic, strong) NSImage *headerImage;
@property (readonly) NSMenuItem *menuFormRepresentation API_AVAILABLE(macos(13.1));
#else
@property (nonatomic, strong) UIImage *headerImage;
#endif

#if TARGET_OS_OSX
/*!
     @abstract If you are using the built in manage share button, this delegate property will be forwarded along to the NSCloudSharingService that button presents. If you have your own and suppress the provided one via setShowManageButton, this does nothing.
*/
@property (nonatomic, weak) id<NSCloudSharingServiceDelegate> cloudSharingServiceDelegate;
#elif !TARGET_OS_TV
/*!
     @abstract If you are using the built in manage share button, this delegate property will be forwarded along to the UICloudSharingController that button presents. If you have your own and suppress the provided one via setShowManageButton, this does nothing.
*/
@property (nonatomic, weak) id<UICloudSharingControllerDelegate> cloudSharingControllerDelegate;
#endif

/*!
     @abstract Dismisses the popover, if presented.
     @param completion Called when the popover dismissal finishes.
*/
- (void)dismissPopover:(nullable void (^)(void))completion;

/*!
     @abstract sets the title of the manage participants button in the collaboration popover to the given string, defaults to "Manage Share"
*/
@property (nonatomic, copy) NSString *manageButtonTitle;

/*!
     @abstract whether the collaboration popover should show the default manage participants button in the popover, defaults to YES
     @param showManageButton whether the button should be hidden
*/
- (void)setShowManageButton:(BOOL)showManageButton;

@end

NS_ASSUME_NONNULL_END

#endif // !TARGET_OS_TV
