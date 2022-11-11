//
//  CPTemplateApplicationInstrumentClusterScene.h
//  CarPlay
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <CarPlay/CarPlay.h>
#import <CarPlay/CPInstrumentClusterController.h>

NS_ASSUME_NONNULL_BEGIN
@class CPTemplateApplicationInstrumentClusterScene;

API_AVAILABLE(ios(15.4)) API_UNAVAILABLE(macos, watchos, tvos)
@protocol CPTemplateApplicationInstrumentClusterSceneDelegate <UISceneDelegate>

@optional

/**
 The instrument cluster navigation scene has connected.
 */
- (void)templateApplicationInstrumentClusterScene:(CPTemplateApplicationInstrumentClusterScene *)templateApplicationInstrumentClusterScene didConnectInstrumentClusterController:(CPInstrumentClusterController *)instrumentClusterController;

/**
 The instrument cluster navigation scene has connected.
 */
- (void)templateApplicationInstrumentClusterScene:(CPTemplateApplicationInstrumentClusterScene *)templateApplicationInstrumentClusterScene didDisconnectInstrumentClusterController:(CPInstrumentClusterController *)instrumentClusterController;

/**
 The CarPlay system suggested content style for this scene has changed.
 */
- (void)contentStyleDidChange:(UIUserInterfaceStyle)contentStyle;

@end

API_AVAILABLE(ios(15.4)) API_UNAVAILABLE(macos, watchos, tvos)
@interface CPTemplateApplicationInstrumentClusterScene : UIScene

/**
 The delegate for a CPTemplateApplicationInstrumentClusterScene must conform to the CPTemplateApplicationInstrumentClusterSceneDelegate protocol.
 */
@property (nullable, nonatomic, strong) id<CPTemplateApplicationInstrumentClusterSceneDelegate> delegate;

/**
 The instrumentClusterController object for this scene.
 */
@property (nonnull, nonatomic, strong, readonly) CPInstrumentClusterController *instrumentClusterController;

/**
 The current content style for this scene suggested by the connected CarPlay system.
 */
@property (nonatomic, readonly) UIUserInterfaceStyle contentStyle;

@end

// A session role which defines a typical interactive application in the CarPlay instrument cluster
extern UISceneSessionRole const CPTemplateApplicationInstrumentClusterSceneSessionRoleApplication API_AVAILABLE(ios(15.4));

NS_ASSUME_NONNULL_END
