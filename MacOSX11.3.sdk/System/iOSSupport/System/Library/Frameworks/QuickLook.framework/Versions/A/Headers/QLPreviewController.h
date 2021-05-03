//
//  QLPreviewController.h
//  Mobile Quick Look
//
//  Copyright 2008 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <QuickLook/QLBase.h>

@protocol QLPreviewItem;
@protocol QLPreviewControllerDelegate;
@protocol QLPreviewControllerDataSource;

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE_IOS(4_0) QL_EXPORT
@interface QLPreviewController : UIViewController

/*!
 * @abstract Returns YES if QLPreviewController can display this preview item.
 */
+ (BOOL)canPreviewItem:(id <QLPreviewItem>)item;

/*
 * Acessing the previewed items
 */

/*!
 * @abstract The Preview Panel data source.
 */
@property(nonatomic, weak, nullable) id <QLPreviewControllerDataSource> dataSource;

/*!
 * @abstract Asks the Preview Controller to reload its data from its data source.
 * @discussion This method does not refresh the visible item if it has not changed.
 */
- (void)reloadData;

/*!
 * @abstract Asks the Preview Controller to recompute the preview of the currently previewed item.
 */
- (void)refreshCurrentPreviewItem;

/*!
 * @abstract The index of the currently previewed item in the preview panel or NSNotFound if there is none.
 */
@property NSInteger currentPreviewItemIndex;

/*!
 * @abstract The currently previewed item in the preview panel or nil if there is none.
 */
@property(readonly, nullable) id <QLPreviewItem> currentPreviewItem;



/*
 * Setting the delegate
 */

/*!
 * @abstract The Preview Controller delegate.
 * @discussion Should implement the <QLPreviewControllerDelegate> protocol
 */
@property(nonatomic, weak, nullable) id <QLPreviewControllerDelegate> delegate;

@end

/*!
 * @abstract The QLPreviewControllerDataSource protocol declares the methods that the Preview Controller uses to access the contents of its data source object.
 */
QL_EXPORT @protocol QLPreviewControllerDataSource

@required

/*!
 * @abstract Returns the number of items that the preview controller should preview.
 * @param controller The Preview Controller.
 * @result The number of items.
 */
- (NSInteger)numberOfPreviewItemsInPreviewController:(QLPreviewController *)controller;

/*!
 * @abstract Returns the item that the preview controller should preview.
 * @param controller The Preview Controller.
 * @param index The index of the item to preview.
 * @result An item conforming to the QLPreviewItem protocol.
 */
- (id <QLPreviewItem>)previewController:(QLPreviewController *)controller previewItemAtIndex:(NSInteger)index;

@end

// QLPreviewItem editing support
typedef NS_ENUM(NSInteger, QLPreviewItemEditingMode) {
    QLPreviewItemEditingModeDisabled = 0,                              // The item won't be editable.
    QLPreviewItemEditingModeUpdateContents,                            // If QLPreviewController supports editing the file type of the preview item, it will automatically overwrite its contents with the edited version of the user.
    QLPreviewItemEditingModeCreateCopy                                 // If QLPreviewController supports editing the file type of the preview item, it will notify its delegate that an edited copy was created. The original document will be unchanged.
} API_AVAILABLE(ios(13.0));

QL_EXPORT @protocol QLPreviewControllerDelegate <NSObject>
@optional


/*!
 * @abstract Invoked before the preview controller is closed.
 */
- (void)previewControllerWillDismiss:(QLPreviewController *)controller;

/*!
 * @abstract Invoked after the preview controller is closed.
 */
- (void)previewControllerDidDismiss:(QLPreviewController *)controller;

/*!
 * @abstract Invoked by the preview controller before trying to open an URL tapped in the preview.
 * @result Returns NO to prevent the preview controller from calling -[UIApplication openURL:] on url.
 * @discussion If not implemented, defaults is YES.
 */
- (BOOL)previewController:(QLPreviewController *)controller shouldOpenURL:(NSURL *)url forPreviewItem:(id <QLPreviewItem>)item;

/*!
 * @abstract Invoked when the preview controller is about to be presented full screen or dismissed from full screen, to provide a zoom effect.
 * @discussion Return the origin of the zoom. It should be relative to view, or screen based if view is not set. The controller will fade in/out if the rect is CGRectZero.
 */
- (CGRect)previewController:(QLPreviewController *)controller frameForPreviewItem:(id <QLPreviewItem>)item inSourceView:(UIView * _Nullable * __nonnull)view;

/*!
 * @abstract Invoked when the preview controller is about to be presented full screen or dismissed from full screen, to provide a smooth transition when zooming.
 * @param contentRect The rect within the image that actually represents the content of the document. For example, for icons the actual rect is generally smaller than the icon itself.
 * @discussion Return an image the controller will crossfade with when zooming. You can specify the actual "document" content rect in the image in contentRect.
 */
- (UIImage * _Nullable)previewController:(QLPreviewController *)controller transitionImageForPreviewItem:(id <QLPreviewItem>)item contentRect:(CGRect *)contentRect;

/*!
 * @abstract Invoked when the preview controller is about to be presented full screen or dismissed from full screen, to provide a smooth transition when zooming.
 * @discussion  Return the view that will crossfade with the preview.
 */
- (UIView* _Nullable)previewController:(QLPreviewController *)controller transitionViewForPreviewItem:(id <QLPreviewItem>)item NS_AVAILABLE_IOS(10_0);

/*!
 * @abstract Invoked when the preview controller is loading its data. It is called for each preview item passed to the data source of the preview controller.
 * @discussion The preview controller does not offer the users to edit previews by default, but it is possible to activate this functionality if its delegate either allows it to overwrite the contents of the preview item, or if it takes care of the updated version of the preview item by implementing previewController:didSaveEditedCopyOfPreviewItem:atURL:.
   If the returned value is QLPreviewItemEditingModeUpdateContents and the previewController:didSaveEditedCopyOfPreviewItem:atURL: delegate method is implemented, the preview controller will overwrite the contents of the preview item if this is possible. If not (because the new version of the preview item is of a different type for instance), it will instead call previewController:didSaveEditedCopyOfPreviewItem:atURL:.
 * @param previewItem The preview item for which the controller needs to know how its delegate wants edited versions of the preview item to be handled.
 * @result A value indicating how the preview controller should handle edited versions of the preview item.
 */
- (QLPreviewItemEditingMode)previewController:(QLPreviewController *)controller editingModeForPreviewItem:(id <QLPreviewItem>)previewItem API_AVAILABLE(ios(13.0));

/*!
 * @abstract Called after the preview controller has successfully overwritten the contents of the file at previewItemURL for the preview item with the edited version of the users.
 * @discussion May be called multiple times in a row when overwriting the preview item with the successive edited versions of the preview item (whenever the users save the changes).
 */
- (void)previewController:(QLPreviewController *)controller didUpdateContentsOfPreviewItem:(id<QLPreviewItem>)previewItem API_AVAILABLE(ios(13.0));

/*!
 * @abstract This method will be called with an edited copy of the contents of the preview item at previewItemURL.
 * @discussion This can be called after the users save changes in the following cases:
 
               - If the returned editing mode of the preview item is QLPreviewItemEditingModeCreateCopy.
 
               - If the returned editing mode of the preview item is QLPreviewItemEditingModeUpdateContents and its previewItemURL could not be successfully overwritten. In this case, modifiedContentsURL will point to a temporary file on disk containing the edited copy.
 
               - If the returned editing mode of the preview item is QLPreviewItemEditingModeUpdateContents and its content type and the content type of the edited version don't match.
                 This means that the file type of modifiedContentsURL may be different from the one of the preview item.
 
               Note that this may be called multiple times in a row with the successive edited versions of the preview item (whenever the users save the changes).
 * @param modifiedContentsURL NSURL of a temporary file on disk containing the edited copy of the preview item.
 */
- (void)previewController:(QLPreviewController *)controller didSaveEditedCopyOfPreviewItem:(id <QLPreviewItem>)previewItem atURL:(NSURL *)modifiedContentsURL API_AVAILABLE(ios(13.0));

@end

NS_ASSUME_NONNULL_END

