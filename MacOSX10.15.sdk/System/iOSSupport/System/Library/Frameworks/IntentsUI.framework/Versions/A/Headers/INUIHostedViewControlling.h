//
//  INUIHostedViewControlling.h
//  Intents
//
//  Copyright (c) 2016 Apple Inc. All rights reserved.
//

#import <CoreGraphics/CoreGraphics.h>

#import <Foundation/Foundation.h>

@class INInteraction;

@class INParameter;

typedef NS_ENUM(NSUInteger, INUIHostedViewContext) {
    INUIHostedViewContextSiriSnippet,
    INUIHostedViewContextMapsCard,
} API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx, watchos, tvos);

typedef NS_ENUM(NSUInteger, INUIInteractiveBehavior) {
    INUIInteractiveBehaviorNone,
    INUIInteractiveBehaviorNextView, // Show UI representing navigation to a new view, such as a navigation chevron
    INUIInteractiveBehaviorLaunch, // Show UI representing a launch to leave the context, such as a button
    INUIInteractiveBehaviorGenericAction, // Show UI representing a generic follow-on action within the context, such as a large tap target
} API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macosx, watchos, tvos);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx, watchos, tvos)
@protocol INUIHostedViewControlling <NSObject>

@optional

/*!
 @abstract Perform configuration of UI based on the provided INInteraction object.
 @discussion When configuration is complete for the given interaction, the hosted view controller should call the completion block with its view's desired size. This size will be constrained between hostedViewMinimumAllowedSize and hostedViewMaximumAllowedSize of the extension context.
 
 @param  interaction The input interaction
 @param  context The hosting context for this interaction. The hosted view will be displayed alongside this context -- for instance, a Siri result snippet, or a place card within Maps.
 @param  completion The response handling block takes one parameter corresponding the optional desiredSize property of the INUIHostedViewControlling protocol
 
 @see  INInteraction
 */
- (void)configureWithInteraction:(INInteraction *)interaction context:(INUIHostedViewContext)context completion:(void (^)(CGSize desiredSize))completion;

/*!
 @abstract Perform configuration of UI based on the provided INInteraction and INParameter objects.
 @discussion When configuration is complete for the given parameters and interaction, the hosted view controller should call the completion block with whether it was successful, the parameters it configured itself with, and its view's desired size. The size of the view will ultimately be constrained between hostedViewMinimumAllowedSize and hostedViewMaximumAllowedSize of the extension context.
 
 @param  parameters The parameters of the interaction for which to configure the view
 @param  interaction The input interaction
 @param  interactiveBehavior The behavior that will be driven by user interaction of this view
 @param  context The hosting context for this interaction. The hosted view will be displayed within/alongside this context -- for instance, a Siri result snippet, or a place card within Maps.
 @param  completion The response handling block takes the following: A) a success boolean, which tells the hosted view context if this view was successfully configured, B) the set of parameters that this view was successfully configured for, and C) a desiredSize for this view to be sized at within the hosted view context.
 
 @see  INParameter
 @see  INInteraction
 */
- (void)configureViewForParameters:(NSSet <INParameter *> *)parameters ofInteraction:(INInteraction *)interaction interactiveBehavior:(INUIInteractiveBehavior)interactiveBehavior context:(INUIHostedViewContext)context completion:(void (^)(BOOL success, NSSet <INParameter *> *configuredParameters, CGSize desiredSize))completion API_AVAILABLE(ios(11.0));

@end

@interface NSExtensionContext (INUIHostedViewControlling)

@property (nonatomic, assign, readonly) CGSize hostedViewMinimumAllowedSize API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx, watchos, tvos);
@property (nonatomic, assign, readonly) CGSize hostedViewMaximumAllowedSize API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx, watchos, tvos);

- (NSString *)interfaceParametersDescription API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macosx, watchos, tvos);

@end

NS_ASSUME_NONNULL_END
