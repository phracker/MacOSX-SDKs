//
//  UIKit.h
//  UIKit
//
//  Copyright (c) 2005-2018 Apple Inc. All rights reserved.
//

#import <TargetConditionals.h>
#import <UIKit/UIKitDefines.h>

#if __has_include(<UIKit/UIAccelerometer.h>)
#import <UIKit/UIAccelerometer.h>
#import <UIKit/UIAccessibility.h>
#endif

#import <UIKit/UIAccessibilityConstants.h>

#if __has_include(<UIKit/UIAccessibilityContentSizeCategoryImageAdjusting.h>)
#import <UIKit/UIAccessibilityContentSizeCategoryImageAdjusting.h>
#endif

#if TARGET_OS_MACCATALYST
#if __has_include(<UIKit/UIActivity.h>)
#import <UIKit/UIActivity.h>
#import <UIKit/UIActivityItemProvider.h>
#import <UIKit/UIActivityViewController.h>
#import <UIKit/UIDocumentInteractionController.h>
#endif

#import <UIKit/NSToolbar+UIKitAdditions.h>
#import <UIKit/NSTouchBar+UIKitAdditions.h>
#endif

#if __has_include(<UIKit/UIActivityIndicatorView.h>)
#import <UIKit/UIActivityIndicatorView.h>
#import <UIKit/UIActionSheet.h>
#import <UIKit/UIAlertController.h>
#import <UIKit/UIAlertView.h>
#import <UIKit/UIAppearance.h>
#import <UIKit/UIApplication.h>
#import <UIKit/UIBarButtonItem.h>
#import <UIKit/UIBarButtonItemGroup.h>
#import <UIKit/UIBarItem.h>
#endif


#import <UIKit/UIBezierPath.h>

#if __has_include(<UIKit/UIButton.h>)
#import <UIKit/UIButton.h>
#import <UIKit/UICollectionView.h>
#import <UIKit/UICollectionViewCell.h>
#import <UIKit/UICollectionViewController.h>
#import <UIKit/UICollectionViewFlowLayout.h>
#import <UIKit/UICollectionViewLayout.h>
#import <UIKit/UICollectionViewTransitionLayout.h>
#import <UIKit/UICollectionViewCompositionalLayout.h>
#import <UIKit/UIDiffableDataSource.h>
#endif

#import <UIKit/UIColor.h>

#if __has_include(<UIKit/UICommand.h>)
#import <UIKit/UICommand.h>
#import <UIKit/UIKeyCommand.h>
#endif

#if __has_include(<UIKit/UIContentSizeCategoryAdjusting.h>)
#import <UIKit/UIContentSizeCategoryAdjusting.h>
#import <UIKit/UIContentSizeCategory.h>
#import <UIKit/UIControl.h>
#import <UIKit/UIDataDetectors.h>
#import <UIKit/UIDatePicker.h>
#import <UIKit/UIDevice.h>
#import <UIKit/UIDocument.h>
#import <UIKit/UIDocumentPickerViewController.h>
#import <UIKit/UIDocumentMenuViewController.h>
#import <UIKit/UIDocumentPickerExtensionViewController.h>
#import <UIKit/UICloudSharingController.h>
#import <UIKit/NSFileProviderExtension.h>
#import <UIKit/UIVisualEffect.h>
#import <UIKit/UIBlurEffect.h>
#import <UIKit/UIVibrancyEffect.h>
#import <UIKit/UIVisualEffectView.h>
#import <UIKit/UIEvent.h>
#endif

#import <UIKit/UIFont.h>
#import <UIKit/UIFontDescriptor.h>
#import <UIKit/UIFontMetrics.h>
#import <UIKit/UIGeometry.h>

#if __has_include(<UIKit/UIFontPickerViewController.h>)
#import <UIKit/UIFontPickerViewController.h>
#import <UIKit/UIFontPickerViewControllerConfiguration.h>
#endif

#if __has_include(<UIKit/UIGestureRecognizer.h>)
#import <UIKit/UIGestureRecognizer.h>
#endif

#import <UIKit/UIGraphics.h>
#import <UIKit/UIImage.h>
#import <UIKit/UIImageConfiguration.h>
#import <UIKit/UIImageSymbolConfiguration.h>

#if __has_include(<UIKit/UIGraphicsRenderer.h>)
#import <UIKit/UIGraphicsRenderer.h>
#import <UIKit/UIGraphicsImageRenderer.h>
#import <UIKit/UIGraphicsPDFRenderer.h>
#endif

#import <UIKit/NSDataAsset.h>

#if __has_include(<UIKit/UIImageAsset.h>)
#import <UIKit/UIImageAsset.h>
#import <UIKit/UIImagePickerController.h>
#import <UIKit/UIImageView.h>
#import <UIKit/UIInputView.h>
#import <UIKit/UIInputViewController.h>
#import <UIKit/UIInterface.h>
#import <UIKit/UILabel.h>
#import <UIKit/UILexicon.h>
#endif

#if __has_include(<UIKit/UILargeContentViewer.h>)
#import <UIKit/UILargeContentViewer.h>
#endif

#import <UIKit/UILocalNotification.h>

#if __has_include(<UIKit/UIUserNotificationSettings.h>)

#import <UIKit/UIApplicationShortcutItem.h>
#import <UIKit/UIUserNotificationSettings.h>
#import <UIKit/UIFocus.h>
#import <UIKit/UIFocusSystem.h>
#import <UIKit/UIFocusGuide.h>
#import <UIKit/UIFocusAnimationCoordinator.h>
#import <UIKit/UIFocusDebugger.h>
#import <UIKit/UIFocusMovementHint.h>
#import <UIKit/UIHoverGestureRecognizer.h>
#import <UIKit/UILocalizedIndexedCollation.h>
#import <UIKit/UILongPressGestureRecognizer.h>
#import <UIKit/UIManagedDocument.h>
#import <UIKit/UIMenuController.h>
#import <UIKit/UIMotionEffect.h>
#import <UIKit/UINavigationBar.h>
#import <UIKit/UINavigationController.h>
#import <UIKit/UINib.h>
#import <UIKit/UINibDeclarations.h>
#import <UIKit/UINibLoading.h>
#import <UIKit/UIPageControl.h>
#import <UIKit/UIPageViewController.h>
#import <UIKit/UIPanGestureRecognizer.h>
#import <UIKit/UIPasteboard.h>
#import <UIKit/UIPasteConfiguration.h>
#import <UIKit/UIPasteConfigurationSupporting.h>
#import <UIKit/UIPickerView.h>
#import <UIKit/UIPinchGestureRecognizer.h>
#import <UIKit/UIPopoverController.h>
#import <UIKit/UIPopoverBackgroundView.h>
#import <UIKit/UIPress.h>
#import <UIKit/UIPressesEvent.h>
#import <UIKit/UIPrinter.h>
#import <UIKit/UIPrinterPickerController.h>
#import <UIKit/UIPrintError.h>
#import <UIKit/UIPrintFormatter.h>
#import <UIKit/UIPrintInfo.h>
#import <UIKit/UIPrintInteractionController.h>
#import <UIKit/UIPrintPageRenderer.h>
#import <UIKit/UIPrintPaper.h>
#import <UIKit/UIProgressView.h>
#import <UIKit/UIReferenceLibraryViewController.h>
#import <UIKit/UIRefreshControl.h>
#import <UIKit/UIResponder.h>
#import <UIKit/UIRotationGestureRecognizer.h>
#import <UIKit/UIScreen.h>
#import <UIKit/UIScreenEdgePanGestureRecognizer.h>
#import <UIKit/UIScreenMode.h>
#import <UIKit/UIScrollView.h>
#import <UIKit/UISearchBar.h>
#import <UIKit/UISearchContainerViewController.h>
#import <UIKit/UISearchController.h>
#import <UIKit/UISearchDisplayController.h>
#import <UIKit/UISearchTextField.h>
#import <UIKit/UISegmentedControl.h>
#import <UIKit/UISlider.h>
#import <UIKit/UISplitViewController.h>
#import <UIKit/UIStepper.h>
#import <UIKit/UIStoryboard.h>
#import <UIKit/UIStoryboardPopoverSegue.h>
#import <UIKit/UIStoryboardSegue.h>
#import <UIKit/UIStringDrawing.h>
#import <UIKit/UISwipeGestureRecognizer.h>
#import <UIKit/UISwitch.h>
#import <UIKit/UITabBar.h>
#import <UIKit/UITabBarController.h>
#import <UIKit/UITabBarItem.h>
#import <UIKit/UITableView.h>
#import <UIKit/UITableViewHeaderFooterView.h>
#import <UIKit/UITableViewCell.h>
#import <UIKit/UITableViewController.h>
#import <UIKit/UITapGestureRecognizer.h>
#import <UIKit/UITextChecker.h>
#import <UIKit/UITextField.h>
#import <UIKit/UITextInput.h>
#import <UIKit/UITextInputTraits.h>
#import <UIKit/UITextView.h>
#import <UIKit/UIToolbar.h>
#import <UIKit/UITouch.h>
#import <UIKit/UITraitCollection.h>
#import <UIKit/UIUserActivity.h>
#import <UIKit/UIVideoEditorController.h>
#import <UIKit/UIView.h>
#import <UIKit/UIViewController.h>
#import <UIKit/UIWebView.h>
#import <UIKit/UIWindow.h>

#import <UIKit/UIDragInteraction.h>
#import <UIKit/UIDragItem.h>
#import <UIKit/UIDragPreview.h>
#import <UIKit/UIDragPreviewParameters.h>
#import <UIKit/UIDragSession.h>
#import <UIKit/UIDropInteraction.h>
#import <UIKit/UIInteraction.h>
#import <UIKit/UITargetedDragPreview.h>
#import <UIKit/UISpringLoadedInteraction.h>
#import <UIKit/UISpringLoadedInteractionSupporting.h>
#import <UIKit/UITargetedPreview.h>
#import <UIKit/UIPreviewParameters.h>

#import <UIKit/UIBarAppearance.h>
#import <UIKit/UIBarButtonItemAppearance.h>
#import <UIKit/UINavigationBarAppearance.h>
#import <UIKit/UIToolbarAppearance.h>
#import <UIKit/UITabBarAppearance.h>

#import <UIKit/UIActivityItemsConfigurationReading.h>
#import <UIKit/UIActivityItemsConfiguration.h>
#import <UIKit/UIResponder+UIActivityItemsConfiguration.h>

#endif

#import <UIKit/NSAttributedString.h>

#if __has_include(<UIKit/NSItemProvider+UIKitAdditions.h>)
#import <UIKit/NSItemProvider+UIKitAdditions.h>
#endif

#if __has_include(<UIKit/NSLayoutConstraint.h>)
#import <UIKit/NSLayoutConstraint.h>
#import <UIKit/NSLayoutAnchor.h>
#import <UIKit/UILayoutGuide.h>
#import <UIKit/UIStackView.h>
#import <UIKit/NSLayoutManager.h>
#endif

#import <UIKit/NSParagraphStyle.h>


#if __has_include(<UIKit/NSShadow.h>)
#import <UIKit/NSShadow.h>
#endif

#import <UIKit/NSStringDrawing.h>
#import <UIKit/NSText.h>

#if __has_include(<UIKit/NSTextAttachment.h>)
#import <UIKit/NSTextAttachment.h>
#import <UIKit/NSTextContainer.h>
#import <UIKit/NSTextStorage.h>
#import <UIKit/UIStateRestoration.h>
#import <UIKit/UIViewControllerTransitioning.h>
#import <UIKit/UIViewControllerTransitionCoordinator.h>
#import <UIKit/UIPresentationController.h>
#import <UIKit/UIPreviewInteraction.h>
#import <UIKit/UIPopoverPresentationController.h>
#import <UIKit/UIDynamicAnimator.h>
#import <UIKit/UIDynamicBehavior.h>
#import <UIKit/UIPushBehavior.h>
#import <UIKit/UISnapBehavior.h>
#import <UIKit/UIDynamicItemBehavior.h>
#import <UIKit/UIFieldBehavior.h>
#import <UIKit/UIGravityBehavior.h>
#import <UIKit/UIAttachmentBehavior.h>
#import <UIKit/UICollisionBehavior.h>
#import <UIKit/UIRegion.h>
#endif

#if __has_include(<UIKit/UITextDragging.h>)
#import <UIKit/UITextDragging.h>
#import <UIKit/UITextDropping.h>
#import <UIKit/UITextDropProposal.h>
#import <UIKit/UITextDragPreviewRenderer.h>
#import <UIKit/UITextDragURLPreviews.h>
#endif

#if __has_include(<UIKit/UIViewPropertyAnimator.h>)
#import <UIKit/UIViewPropertyAnimator.h>
#endif

#if __has_include(<UIKit/UIFeedbackGenerator.h>)
#import <UIKit/UIFeedbackGenerator.h>
#import <UIKit/UISelectionFeedbackGenerator.h>
#import <UIKit/UIImpactFeedbackGenerator.h>
#import <UIKit/UINotificationFeedbackGenerator.h>
#endif

#if __has_include(<UIKit/UITimingCurveProvider.h>)
#import <UIKit/UITimingCurveProvider.h>
#endif

#if __has_include(<UIKit/NSIndexPath+UIKitAdditions.h>)
#import <UIKit/NSIndexPath+UIKitAdditions.h>
#endif

#if __has_include(<UIKit/UIPopoverSupport.h>)
#import <UIKit/UIPopoverSupport.h>
#endif

#if __has_include(<UIKit/UITextInteraction.h>)
#import <UIKit/UITextInteraction.h>
#endif

#if __has_include(<UIKit/UITextItemInteraction.h>)
#import <UIKit/UITextItemInteraction.h>
#endif

#if __has_include(<UIKit/UIViewAnimating.h>)
#import <UIKit/UIViewAnimating.h>
#endif

#if __has_include(<UIKit/UISwipeActionsConfiguration.h>)
#import <UIKit/UISwipeActionsConfiguration.h>
#endif

#if __has_include(<UIKit/UIAccessibilityZoom.h>)
#import <UIKit/UIAccessibilityZoom.h>
#endif

#if __has_include(<UIKit/UIAccessibilityCustomAction.h>)
#import <UIKit/UIAccessibilityCustomAction.h>
#endif

#if __has_include(<UIKit/UIDataSourceTranslating.h>)
#import <UIKit/UIDataSourceTranslating.h>
#endif

#if __has_include(<UIKit/UIAccessibilityElement.h>)
#import <UIKit/UIAccessibilityElement.h>
#endif

#if __has_include(<UIKit/UITextPasteDelegate.h>)
#import <UIKit/UITextPasteDelegate.h>
#endif

#if __has_include(<UIKit/UITextPasteConfigurationSupporting.h>)
#import <UIKit/UITextPasteConfigurationSupporting.h>
#endif

#if __has_include(<UIKit/UIAlert.h>)
#import <UIKit/UIAlert.h>
#endif

#if __has_include(<UIKit/UIAccessibilityLocationDescriptor.h>)
#import <UIKit/UIAccessibilityLocationDescriptor.h>
#endif

#if __has_include(<UIKit/UINavigationItem.h>)
#import <UIKit/UINavigationItem.h>
#endif

#if __has_include(<UIKit/UIAccessibilityAdditions.h>)
#import <UIKit/UIAccessibilityAdditions.h>
#endif

#if __has_include(<UIKit/UITimingParameters.h>)
#import <UIKit/UITimingParameters.h>
#endif

#if __has_include(<UIKit/UIBarCommon.h>)
#import <UIKit/UIBarCommon.h>
#endif

#if __has_include(<UIKit/UIGuidedAccessRestrictions.h>)
#import <UIKit/UIGuidedAccess.h>
#import <UIKit/UIGuidedAccessRestrictions.h>
#endif

#if __has_include(<UIKit/UIAccessibilityCustomRotor.h>)
#import <UIKit/UIAccessibilityCustomRotor.h>
#endif

#if __has_include(<UIKit/UIContextualAction.h>)
#import <UIKit/UIContextualAction.h>
#endif

#if __has_include(<UIKit/UIAccessibilityContainer.h>)
#import <UIKit/UIAccessibilityContainer.h>
#endif

#if __has_include(<UIKit/UIAccessibilityIdentification.h>)
#import <UIKit/UIAccessibilityIdentification.h>
#endif

#if __has_include(<UIKit/UIGestureRecognizerSubclass.h>)
#import <UIKit/UIGestureRecognizerSubclass.h>
#endif

#if __has_include(<UIKit/UIGraphicsRendererSubclass.h>)
#import <UIKit/UIGraphicsRendererSubclass.h>
#endif

#if __has_include(<UIKit/UIFocusMovementHint.h>)
#import <UIKit/UIFocusMovementHint.h>
#endif

#if __has_include(<UIKit/UIPencilInteraction.h>)
    #import <UIKit/UIPencilInteraction.h>
#endif

#if __has_include(<UIKit/UIScene.h>)
    #import <UIKit/UISceneDefinitions.h>
    #import <UIKit/UISceneOptions.h>
    #import <UIKit/UIScene.h>
    #import <UIKit/UIWindowScene.h>
    #import <UIKit/UISceneSession.h>
    #import <UIKit/UISceneActivationConditions.h>
    #import <UIKit/UIOpenURLContext.h>
    #import <UIKit/UIStatusBarManager.h>
    #import <UIKit/UIScreenshotService.h>
#endif

#if __has_include(<UIKit/NSUserActivity+NSItemProvider.h>)
    #import <UIKit/NSUserActivity+NSItemProvider.h>
#endif

#if __has_include(<UIKit/UNNotificationResponse+UIKitAdditions.h>)
    #import <UIKit/UNNotificationResponse+UIKitAdditions.h>
#endif
	
#if __has_include(<UIKit/UIAction.h>)
#import <UIKit/UIAction.h>
#endif

#if __has_include(<UIKit/UIMenu.h>)
#import <UIKit/UIMenu.h>
#import <UIKit/UIMenuBuilder.h>
#import <UIKit/UIMenuElement.h>
#import <UIKit/UIMenuSystem.h>
#endif

#if __has_include(<UIKit/UIContextMenuInteraction.h>)
#import <UIKit/UIContextMenuInteraction.h>
#import <UIKit/UIContextMenuConfiguration.h>
#endif

#if __has_include(<UIKit/UITextFormattingCoordinator.h>)
#import <UIKit/UITextFormattingCoordinator.h>
#endif
