//
//  SWHighlightCenter.h
//  SWHighlightCenter
//
//  Copyright (c) 2021 Apple. All rights reserved.
//
#import <Foundation/Foundation.h>
#import <SharedWithYouCore/SWDefines.h>
#import <SharedWithYou/SWHighlight.h>
#import <SharedWithYou/SWHighlightEvent.h>
#import <SharedWithYouCore/SWCollaborationMetadata.h>

NS_ASSUME_NONNULL_BEGIN
@class SWCollaborationHighlight;
@class SWHighlight;
@class SWHighlightCenter;
@class SWSignedPersonIdentityProof;

/*!
     @protocol SWHighlightCenterDelegate
     @abstract The delegate is notified when there are changes to the list of surfaced highlights, or when the enablement settings change.
 */
@protocol SWHighlightCenterDelegate <NSObject>

@required
/*!
    @abstract Notifies the delegate that the list, or rank order of surfaced highlights has changed.
    @discussion When this method is called, it is the app's responsibility to update any displayed highlights to match the updated list. Only the highlights provided should have an indication of having been shared. If no highlights are provided in the list, any links previously indicated as shared should be removed. The array is a priority-ordered list, where the first element in the array is deemed to be most relevant to the user at the time this method is called. The list of provided highlights will be empty if there are no highlights, or when the user has not given permission for a particular app to display highlights.
 */
- (void)highlightCenterHighlightsDidChange:(SWHighlightCenter *)highlightCenter;

@end

/*!
     @class SWHighlightCenter
     @abstract Provides the application with a priority-ordered list of universal links which have been shared with the current user.
     @discussion The system decides which links should be surfaced. The app is responsible for updating its UI to reflect the latest provided list.
 */
API_AVAILABLE(ios(16.0), macos(13.0), tvos(16.0))
SW_EXTERN @interface SWHighlightCenter : NSObject

/*!
    @abstract The highlight center's delegate
 */
@property (nullable, weak, nonatomic, readwrite) id<SWHighlightCenterDelegate> delegate;

@property (copy, nonatomic, readonly) NSArray<SWHighlight *> *highlights;

/*!
    @abstract Localized title to display with a collection of highlights
    @discussion Use this string as the title for a collection of shared highlight links displayed to the user.
 */
@property (class, nonatomic, readonly) NSString *highlightCollectionTitle;

/*!
    @abstract Whether the current software version has full support for Messages collaboration features.
    @discussion Use this property at runtime to conditionally enable Messages collaboration features in your app. This property will be permantently set to YES on a software version with full support for these features.
 */
@property (class, nonatomic, readonly, getter=isSystemCollaborationSupportAvailable) BOOL systemCollaborationSupportAvailable;

/*!
 @abstract A convenience method to get a SWHighlight for a given URL
 @param URL The URL used to find the SWHighlight
 @param completionHandler an SWHighlight if it  was fetched. The completion handler will always be invoked on the main queue
 */
- (void)getHighlightForURL:(NSURL *)URL completionHandler:(void (^)(SWHighlight * _Nullable highlight, NSError * _Nullable fetchError))completionHandler;

/*!
    @abstract A convenience method to get a SWCollaborationHighlight for a given collaboration Identifier
    @param collaborationIdentifier The unique identifier used to find the SWCollaborationHighlight
    @param error The error describing the failure.
*/
#if !TARGET_OS_TV
- (SWCollaborationHighlight * __nullable)collaborationHighlightForIdentifier:(SWCollaborationIdentifier)collaborationIdentifier error:(NSError **)error;

/*!
 @abstract A convenience method to get an SWCollaborationHighlight for a given URL
 @param URL The URL used to find the SWCollaborationHighlight
 @param completionHandler  an SWCollaborationHighlight if it was fetched. The completion handler will always be invoked on the main queue
 */
- (void)getCollaborationHighlightForURL:(NSURL *)URL completionHandler:(void (^)(SWCollaborationHighlight * _Nullable highlight, NSError * _Nullable fetchError))completionHandler API_AVAILABLE(ios(16.0), macos(13.0));

/*!
    @abstract Post a given event to the highlight center for display in Messages.
    @param event The event to add for a specific highlight
 */
- (void)postNoticeForHighlightEvent:(id<SWHighlightEvent>)event API_AVAILABLE(ios(16.0), macos(13.0));

/*!
    @abstract Clear notices for a given collaboration highlight in Messages.
    @param highlight The highlight to clear notices from.
 */
- (void)clearNoticesForHighlight:(SWCollaborationHighlight *)highlight API_AVAILABLE(ios(16.1), macos(13.0)); 

/*!
    @abstract Method to sign passed in data with local device's private key
    @param data NSData that needs to be signed
    @param collaborationHighlight The corresponding collaboration highlight.
    @param completionHandler Signed data along with proof of inclusion for merkle if signing succeeded, otherwise an error. The completion handler will always be invoked on main queue
 */
- (void)getSignedIdentityProofForCollaborationHighlight:(SWCollaborationHighlight *)collaborationHighlight usingData:(NSData *)data completionHandler:(void (^)(SWSignedPersonIdentityProof * _Nullable, NSError * _Nullable))completionHandler NS_SWIFT_ASYNC_NAME(signedIdentityProof(for:using:)) API_AVAILABLE(ios(16.0), macos(13.0));
#endif // !TARGET_OS_TV

@end

NS_ASSUME_NONNULL_END

