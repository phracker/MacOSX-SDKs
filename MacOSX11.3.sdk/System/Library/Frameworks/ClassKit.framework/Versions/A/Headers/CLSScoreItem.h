//
//  CLSScoreItem.h
//  ClassKit
//
//  Copyright © 2018-2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ClassKit/CLSActivityItem.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract      CLSScoreItem represents user generated score information.
 */

API_AVAILABLE(ios(11.3), macos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(watchos, tvos)
@interface CLSScoreItem : CLSActivityItem

/*!
 @abstract      Score out of @c maxScore.
 @discussion    Should be between zero and @c maxScore [0.0,maxScore].
 */
@property (nonatomic, assign) double score;

/*!
 @abstract      Total score possible.
 @discussion    Must be greater than zero.
 */
@property (nonatomic, assign) double maxScore;

/*!
 @abstract      Create a score item with identifiers, title, score and maximum score.
 @param         identifier      An identifier that is unique within activity.
 @param         title           Title of score. Ex @em Biology- Cellular Division Quiz
 @param         score           The score the user received.
 @param         maxScore        The maximum score possible.
 */
- (instancetype)initWithIdentifier:(NSString *)identifier
                             title:(NSString *)title
                             score:(double)score
                          maxScore:(double)maxScore NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
