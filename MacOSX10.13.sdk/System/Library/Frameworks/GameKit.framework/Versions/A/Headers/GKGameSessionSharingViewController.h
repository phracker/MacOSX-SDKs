//
//  GKGameSessionSharingViewController.h
//  Game Center
//
//  Copyright 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#if TARGET_OS_TV

@class GKGameSession;
@protocol GKGameSessionSharingViewControllerDelegate;


NS_ASSUME_NONNULL_BEGIN

@interface GKGameSessionSharingViewController : UIViewController
@property (nonatomic, readonly, strong) GKGameSession *session;
@property (nonatomic, weak, nullable) id<GKGameSessionSharingViewControllerDelegate> delegate;

- (instancetype)initWithSession:(GKGameSession *)session;

@end


@protocol GKGameSessionSharingViewControllerDelegate <NSObject>
- (void)sharingViewController:(GKGameSessionSharingViewController *)viewController didFinishWithError:(NSError * __nullable)error;
@end

NS_ASSUME_NONNULL_END


#endif
