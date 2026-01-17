//
//  CLSContext.h
//  ClassKit
//
//  Copyright © 2016-2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CGImage.h>
#import <ClassKit/CLSDefines.h>
#import <ClassKit/CLSObject.h>
#import <ClassKit/CLSProgressReportingCapability.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, CLSContextType) {
    CLSContextTypeNone = 0,

    CLSContextTypeApp,       // Reserved for the main app context

    CLSContextTypeChapter,
    CLSContextTypeSection,
    CLSContextTypeLevel,
    CLSContextTypePage,

    CLSContextTypeTask,
    CLSContextTypeChallenge,
    CLSContextTypeQuiz,
    CLSContextTypeExercise,
    CLSContextTypeLesson,

    CLSContextTypeBook,
    CLSContextTypeGame,

    CLSContextTypeDocument,
    CLSContextTypeAudio,
    CLSContextTypeVideo,

    CLSContextTypeCourse API_AVAILABLE(ios(13.4), macos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(watchos, tvos),
    CLSContextTypeCustom API_AVAILABLE(ios(13.4), macos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(watchos, tvos)
} API_AVAILABLE(ios(11.3), macos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(watchos, tvos);

typedef NSString * CLSContextTopic NS_STRING_ENUM API_AVAILABLE(ios(11.3), macos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(watchos, tvos);

CLS_EXTERN CLSContextTopic const CLSContextTopicMath API_AVAILABLE(ios(11.3), macos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(watchos, tvos);
CLS_EXTERN CLSContextTopic const CLSContextTopicScience API_AVAILABLE(ios(11.3), macos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(watchos, tvos);
CLS_EXTERN CLSContextTopic const CLSContextTopicLiteracyAndWriting API_AVAILABLE(ios(11.3), macos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(watchos, tvos);
CLS_EXTERN CLSContextTopic const CLSContextTopicWorldLanguage API_AVAILABLE(ios(11.3), macos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(watchos, tvos);
CLS_EXTERN CLSContextTopic const CLSContextTopicSocialScience API_AVAILABLE(ios(11.3), macos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(watchos, tvos);
CLS_EXTERN CLSContextTopic const CLSContextTopicComputerScienceAndEngineering API_AVAILABLE(ios(11.3), macos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(watchos, tvos);
CLS_EXTERN CLSContextTopic const CLSContextTopicArtsAndMusic API_AVAILABLE(ios(11.3), macos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(watchos, tvos);
CLS_EXTERN CLSContextTopic const CLSContextTopicHealthAndFitness API_AVAILABLE(ios(11.3), macos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(watchos, tvos);


/*!
 @abstract      Contexts represent activities, documents, and areas within your app.
 @discussion    Contexts have two major components.

                (1) Child contexts, used to model your app hierarchy.
                (2) Activity, holds user generated data that pertains to this context.

 */
API_AVAILABLE(ios(11.3), macos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(watchos, tvos)
@interface CLSContext : CLSObject

+ (instancetype)new NS_UNAVAILABLE;

- (instancetype)init NS_UNAVAILABLE;

/*!
 @abstract      Context identifier path of this context.
 @discussion    The identifier path starts with the main app context object and finishes with the identifier of this context. This is the identifier path that one would use in @code -[CLSDataStore contextsMatchingIdintifierPath:completion:] @endcode to find `this' context.
 */
@property (nonatomic, copy, readonly) NSArray<NSString *> *identifierPath API_AVAILABLE(ios(13.4), macos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 @abstract      App-assigned identifier. This identifier should work across users and devices and be unique with regards to its siblings within its parent.
 @discussion    The identifier could be used to embed information later used for deep linking. For example: @em hydrogen-element, or @em chapter-1.
 */
@property (nonatomic, copy, readonly) NSString *identifier;

/*!
 @abstract      Alternative deep link URL using universal links.
 @discussion    If your app supports universal links, you can supply them here to link the content this context represents.
 */
@property (nonatomic, strong, nullable) NSURL *universalLinkURL API_AVAILABLE(ios(11.4), macos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 @abstract      Type of this context
 @discussion    The type that best describes this context.
 */
@property (nonatomic, assign, readonly) CLSContextType type;

/*!
 @abstract      An optional user-visible name for the context if its type is CLSContextTypeCustom.
 @discussion    This property is relevant only if the type is CLSContextTypeCustom. This string should be localized. If this property is not set for a context of type CLSContextTypeCustom, Schoolwork app will use a default localized string ‘Custom’ as the name of the activity representing this context.
 */
@property (nonatomic, copy, nullable) NSString *customTypeName API_AVAILABLE(ios(13.4), macos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 @abstract      Title of this context.
 @discussion    For example: @em Level 1 @em.
 */
@property (nonatomic, copy) NSString *title;

/*!
 @abstract      The displayOrder is by default sorted ascending.
 @discussion    Set the displayOrder if you want your contexts to be displayed in a particular order. The sort key is used as a way to sort sibling contexts in a particular order.
 */
@property (nonatomic, assign) NSInteger displayOrder;

/*!
 @abstract      Topic associated with this context.
 @discussion    See above for valid, predefined topics.
 */
@property (nonatomic, copy, nullable) CLSContextTopic topic;

/*!
 @abstract      This property is true if the context can be assigned as an activity.
 @discussion    The default value of this property is true. This should be set to false for a context that is used as a container for other contexts, but by itself, is not an assignable activity.
 */
@property (nonatomic, assign, readwrite, getter=isAssignable) BOOL assignable API_AVAILABLE(ios(14), macos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 @abstract      Suggested age range of students, expressed in years, for whom this context is suitable. This information is intended to help teachers to choose age-appropriate activities for their students.
 @discussion    The default value is [0, NSIntegerMax - 1]. This is @em NSRange(0...Int.max-1) in @em Swift or @em NSMakeRange(0,NSIntegerMax) in @em Objective-C. Set the lower bound to 0 to specify no minimum age limit and set the upper bound to NSIntegerMax - 1 to specify no maximum age limit.
 @example       An age range of 4 to 6 years is expressed by @em NSRange(4...6) in @em Swift or by @em NSMakeRange(4,3) in @Objective-C.
 @example       An age range of up 10 years is expressed by @em NSRange(0...10) in @em Swift or by @em NSMakeRange(0,11) in @Objective-C.
 @example       An age range of 18 years or above is expressed by @em NSRange(18...Int.max-1) in @em Swift or by @em NSMakeRange(18,NSIntegerMax-18) in @Objective-C.
 */
@property (nonatomic, assign, readwrite)  NSRange suggestedAge API_AVAILABLE(ios(14), macos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 @abstract      Suggested time range, expressed in minutes, to complete the activity. This information will help teachers as they choose activities for their students.
 @discussion    The default value is [0, NSIntegerMax - 1]. This is @em NSRange(0...Int.max-1) in @em Swift or @em NSMakeRange(0,NSIntegerMax) in @em Objective-C. Set the lower bound value to 0 to specify no minimum time limit and set the upper bound to NSIntegerMax - 1 to specify no maximum time limit.
 @example       An time range of 10 to 15 minutes is expressed by @em NSRange(10...15) in @em Swift or by @em NSMakeRange(10,6) in @Objective-C.
 @example       An time range of up to 10 minutes is expressed by @em NSRange(0...10) in @em Swift or by @em NSMakeRange(0,11) in @Objective-C.
 @example       An time range of at least 20 minutes is expressed by @em NSRange(20...Int.max-1) in @em Swift or by @em NSMakeRange(20,NSIntegerMax-20) in @Objective-C.
 */
@property (nonatomic, assign, readwrite) NSRange suggestedCompletionTime API_AVAILABLE(ios(14), macos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 @abstract      Specifies progress reporting capablities of the app for this context.
 @discussion    This information is intended to help teachers as they choose activities for their students. By default a CLSContext will have one CLSProgressReportingCapability instance of kind CLSProgressReportingCapabilityKindDuration. More progress reporting capabilities can be specified via '-addProgressReportingCapabilities:' to customize this set.
 */
@property (nonatomic, copy, readonly) NSSet<CLSProgressReportingCapability *> *progressReportingCapabilities API_AVAILABLE(ios(14), macos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 @abstract      An optional user-visible summary describing the context limited to 4000 characters in length.
 @discussion    This may be used to provide information about the types of activities available under a given context or the context itself. This string should be localized.
 */
@property (nonatomic, copy, nullable) NSString *summary API_AVAILABLE(ios(13.4), macos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 @abstract      An optional thumbnail image associated with the context.
 @discussion    The size of this image should be equal to or larger than 80x80 pixels and equal to or smaller than 330x330 pixels. Images larger than 330x330 pixels will be scaled down. Images with both dimensions smaller than 80x80 pixels will not be accepted.
 */
@property (nonatomic, nullable) CGImageRef thumbnail API_AVAILABLE(ios(13.4), macos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 @abstract      Initialize and configure the type of content this context represents.
 @param         identifier     App-assigned identifier for this context. 256 characters max length.
 @param         type           The type of content this context represents.
 @param         title          Title for what this context represents. 256 characters max length.
 */
- (instancetype)initWithType:(CLSContextType)type
                  identifier:(NSString *)identifier
                       title:(NSString *)title NS_DESIGNATED_INITIALIZER;

/*!
 @discussion    Returns true if self is the active context.
 */
@property (nonatomic, assign, readonly, getter=isActive) BOOL active;

/*!
 @abstract      Marks contexts as active.
 @discussion    If a context is already active, it will remain active. If another context is active, the other will resign active before this one becomes active.
 */
- (void)becomeActive;

/*!
 @abstract      Resign being active.
 @discussion    This method does nothing if the reciever of the message is not active.
 */
- (void)resignActive;

/*!
 @abstract      Sets the type.
 @discussion    Use this to update a previously saved context.
 */
- (void)setType:(CLSContextType)type API_AVAILABLE(ios(14), macos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 @abstract      Add or replace additional progress reporting capabilities of the app for this context.
 @discussion    If this parameter contains multiple items with the same value for kind, then one of them will be arbitrarily selected and used. If this parameter contains a capability of kind CLSProgressReportingCapabilityKindDuration, it will be ignored.
 @param         capabilities    Progress reporting capabilities to add or replace existing capabilties.
 */
- (void)addProgressReportingCapabilities:(NSSet<CLSProgressReportingCapability *> *)capabilities API_AVAILABLE(ios(14), macos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 @abstract      Clears CLSProgressReportingCapability objects added to the receiver.
 @discussion    Removes all capabilities added via '-addProgressReportingCapabilities:'. The context will have the default progress reporting capability of kind CLSProgressReportingCapabilityKindDuration.
 */
- (void)resetProgressReportingCapabilities API_AVAILABLE(ios(14), macos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(watchos, tvos);

@end

@interface CLSContext (Hierarchy)

/*!
 @abstract      Returns the parent of this context.
 */
@property (nullable, nonatomic, weak, readonly) CLSContext *parent;

/*!
 @abstract      Removes this child context from its parent.
 @discussion    If you remove a context from its parent and do not add it as a child of another context, it will be deleted when you call -save on the dataStore.
 */
- (void)removeFromParent;

/*!
 @abstract      Adds a child context.
 @discussion    A context can only have a single parent.
 @note          objectID of child context may change after it's been added.
 */
- (void)addChildContext:(CLSContext *)child;

/*!
 @abstract      Returns a descendant of this context matching the context path you provide. Context path must start with an identifier of a child context of the context to which this message is sent.
 @discussion    If there are any missing contexts, they will be filled in by calling the following method on the context's data store's delegate: @code -[CLSDataStoreDelegate createContextForIdentifier:parentContext:parentIdentifierPath:] @endcode If the dataStore does not have a delegate and there are missing contexts then an incomplete list of contexts will be passed to the completion handler. Completion block is called on a background thread.
 */
- (void)descendantMatchingIdentifierPath:(NSArray<NSString *> *)identifierPath
                              completion:(void(^)(CLSContext * _Nullable context, NSError * _Nullable error))completion;

/*!
 @abstract      Child contexts that can be navigated to from this context.
 @discussion    Returns all the child contexts added via @code -[CLSContext addNavigationChildContext:] @endcode
*/
@property (nonatomic, copy, readonly) NSArray<CLSContext *> *navigationChildContexts API_AVAILABLE(ios(14.5), macos(11.3), macCatalyst(14.5)) API_UNAVAILABLE(watchos, tvos);

/*!
 @abstract      Adds a child context to specify the user can navigate to the child from this context.
 @discussion    Used only for presentation purpose. Unlike @code -[CLSContext addChildContext:] @endcode, this method does not affect the identifierPath.
*/
- (void)addNavigationChildContext:(CLSContext *)child API_AVAILABLE(ios(14.5), macos(11.3), macCatalyst(14.5)) API_UNAVAILABLE(watchos, tvos);

/*!
 @abstract      Removes the navigation path to the child context from this context.
 @discussion    Used only for presentation purpose. Unlike @code -[CLSContext removeFromParent:] @endcode, this method does not affect the identiferPath.
*/
- (void)removeNavigationChildContext:(CLSContext *)child API_AVAILABLE(ios(14.5), macos(11.3), macCatalyst(14.5)) API_UNAVAILABLE(watchos, tvos);

@end

NS_ASSUME_NONNULL_END
