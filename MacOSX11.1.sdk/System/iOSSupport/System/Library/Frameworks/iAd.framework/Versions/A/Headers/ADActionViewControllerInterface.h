//
//  ADActionViewControllerInterface.h
//  iAd
//

#import <Foundation/Foundation.h>

@class ADAdSpace;

NS_DEPRECATED(10_14, 10_14, 8_0, 13_0)
@protocol ADActionViewControllerInterface <NSObject>

@property (nonatomic, readonly) BOOL readyForPresentation;
@property (nonatomic, weak, readonly) ADAdSpace *adSpace;

- (void)dismiss;

- (void)clientApplicationDidEnterBackground;
- (void)clientApplicationCancelledAction;

@end

NS_DEPRECATED(10_14, 10_14, 8_0, 13_0)
@protocol ADActionViewControllerChildInterface <NSObject>

- (void)actionViewControllerClosed;

@end
